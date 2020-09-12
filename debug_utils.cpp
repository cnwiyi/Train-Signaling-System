//
// Created by Chinedu Nwiyi on 2020-09-09.
//

// general utilities functions

#include "debug_utils.h"

void display_1D_vector_info(const vector<int> &vec, char between) {
    for (int j = 0; j < vec.size(); j++) {
        cout << between << vec[j];
    }
}

void display_2D_vector_info(const vector<vector<int>> &vData) {
    for (int i = 0; i < vData.size(); i++) {
        cout << " ";
        display_1D_vector_info(vData[i], ' ');
        cout << endl;
    }
    cout << endl;
}

// train tracks specific utilities functions

void display_track_info(const vector<vector<int>> &vTracks) {
    cout << "Tracks (chain of segments in train tracks - " << vTracks.size()-1 << " paths and " << vTracks[0][0] << " segments):" << endl;
    for (int i = 1; i < vTracks.size(); i++) {
        cout << "  Path " << i << ": " ;
        display_1D_vector_info(vTracks[i], '-');
        cout << endl;
    }
    cout << endl;
}

void display_train_info(const vector<string> &tNames, const vector<vector<int>> &vTrains) {
    cout << "Train names, start and stop stations (" << vTrains.size() << " trains):" << endl;
    for (int i = 0; i < vTrains.size(); i++ ) {
        cout << "  Train " << tNames[i] << ": Going from segment " << vTrains[i][0] << " to segment " << vTrains[i][1] << endl;
    }
    cout << endl;
}