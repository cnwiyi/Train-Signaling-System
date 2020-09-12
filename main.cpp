//
// Created by Chinedu Nwiyi on 2020-09-09.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "train_tracks.h"
#include "debug_utils.h"
#include "simulation.h"
#include <chrono>

using namespace std;

// globals for simulation
int nTracks = 0;
int nTrains = 0;
vector<vector<int>> vTracks; // for track info
vector<vector<int>> vTrains;  // for train info
vector<string> tNames; // for train names
vector<int> tRunTimes; // for time of trains on tracks

/**
 * Function converts a line of string passed in to numbers in a vector. Uses a
 * delimiter char (size 1) as parser.
 *
 * @param line
 * @param delimiter
 * @return
 */
vector<int> convert_line_string_to_int(string line, char delimiter) {
#ifdef DEBUG
    cout << "line: " << line << " delimiter: '" << delimiter << "'" << endl;
#endif
    vector<int> vInt;
    int digit = 0, number = 0;

    while (line[digit] != '\0') {
        if (line[digit] == delimiter) {
            vInt.push_back(number);
            number=0; // reset for next number

            digit++;
            continue;
        }

        if ((line[digit] < '0') || (line[digit] > '9')) {
            cout << "\nNone integer value found '" << line[digit] << "'" << endl;
            return vInt;
        }

        number = (number * 10) + (line[digit] - '0'); // convert to numeric number

        digit++;
    }

    vInt.push_back(number);
    return vInt;
}

/**
 *  Function to read string matrix from a file provided and return in a vector.
 *
 * @param txtFile
 * @return
 */
vector<vector<int>> read_from_file (const string txtFile) {
    string line;
    ifstream file(txtFile);
    vector<vector<int>> vData;

    if (file.is_open()) {
        cout << "Successfully opened file (" << txtFile << ")" << endl;

        while (getline(file, line)) {
            vector<int> vline = convert_line_string_to_int(line, ' ');
            vData.push_back(vline);
            vline.clear();
        }
        file.close();
#ifdef DEBUG
        display_2D_vector_info(vData); // debug: display 2d vector for correctness check
#endif
    }
    else {
        cout << "Unable to open file" << endl;
    }

    return vData;
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv) {
    // validate that user passed in info.
    if (argc != 3) {
        cout << "Provide input files." << endl;
        return 0;
    }

    // get tracks info
    vTracks = read_from_file(argv[1]);
    nTracks = vTracks[0][0]; // todo: consider removing vTracks[0][0] from required input

    if (vTracks.empty()) {
        cout << "No info found in " << argv[1] << " or issue reading file. Exiting simulation." << endl;
        return 0;
    }
#ifdef DISPLAY
    display_track_info(vTracks); // display track info
#endif
    // get trains info
    vTrains = read_from_file(argv[2]);
    nTrains = vTrains.size();
#ifdef DISPLAY
    cout << "Number of Trains: " << nTrains << endl;
#endif
    if (vTrains.empty()) {
        cout << "No info found in " << argv[2] << " or issue reading file. Exiting simulation." << endl;
        return 0;
    }

    // name trains todo: add to trains.txt file, limited now from a-z
    tNames.resize(nTrains);
    for (int i = 0; i < nTrains; i++) {
        char c = 'A' + i;
        tNames[i] = c;
    }

    // for times trains will take to run
    tRunTimes.resize(nTrains);
#ifdef DISPLAY
    cout << endl;
    display_train_info(tNames, vTrains);
#endif
    // build tree using tracks info
    TrainTracks tTrainTracks = create_train_tracks_vector(vTracks);

    cout << "\nBegin simulation..." << endl;

    thread task[nTrains]; // todo: [Optimization] - use a worker thread to dispach and share resources (better simulation?)

    for (int trainNumber = 0; trainNumber < nTrains; trainNumber++)
        task[trainNumber] = thread(simulate_train_on_tracks, trainNumber, tNames, vTrains, vTracks, &tTrainTracks, &tRunTimes[trainNumber]);

    for (int trainNumber = 0; trainNumber < nTrains; trainNumber++)
        task[trainNumber].join();

    cout << "Simulation complete.\n\nSimulation Report:" << endl;
    for (int i = 0; i < nTrains; i++ ) {
        // todo: add tracks that experienced delays in summary and or stations delayed?
        cout << " Train " << tNames[i] << " took " <<  tRunTimes[i] << "s to travel from Station " << vTrains[i][START] << " to Station " << vTrains[i][END] << "." << endl;
    }

    return 0;
}