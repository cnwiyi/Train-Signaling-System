//
// Created by Chinedu Nwiyi on 2020-09-09.
//

// Implements necessary functions for simulation.

#include "simulation.h"
#include "debug_utils.h"
#include <unistd.h> // sleep
#include <ctime> // timer

mutex mtx;

/**
 * Searches a tree (vTracks) and gets the path between two points (trainInfo[START]
 * and trainInfo[END]). Returns a sub-tree from main tree.
 *
 * @param trainInfo
 * @param vTracks
 * @return
 */
static vector<int> find_train_path(const vector<int> &trainInfo, const vector<vector<int>> &vTracks) {
    // todo: [Optimization]: Find best path from the start and end point using shortest part (DFS or Dijkstra).
    //       May need to represent binary tree as a adjacency matrix, for performance improvements.
    //       This function still works if all points are not unique. current code struct: acylic tree & uni dir.

    vector<int> trainPath, path;
    bool found = false;

    for (int i = 1; i < vTracks.size(); i++) {
#ifdef DEBUG
        cout << " " << trainInfo[START] << " " << trainInfo[END] << " vs " << vTracks[i][START] << " " << vTracks[i][last] << endl;
#endif
        if ((trainInfo[END] == vTracks[i][vTracks[i].size()-1])) {
            path = vTracks[i];

            // resize vector to start and end
            for (int j = 0; j < path.size(); j++) {
                found = true;
                if (path[j] == trainInfo[START]) {
                    for (int k = j; k < path.size(); k++) {
                        trainPath.push_back(path[k]);
                    }
                }
            }

            if (found)
                break;
        }
    }
#ifdef DEBUG
    display_1D_vector_info(trainPath, ' ');
#endif
    return trainPath;
}

void simulate_train_on_tracks(int trainNumber, const vector<string> &tNames, const vector<vector<int>> &vTrains,
                              const vector<vector<int>> &vTracks, TrainTracks *tTrainTracks, int *runTimes) {

    time_t sTime, eTime;
    time(&sTime);

    // find path between start and end points
    vector<int> trainPath = find_train_path(vTrains[trainNumber], vTracks);

    if (trainPath.empty()) {
        cout << "Train path not found in file provided. Exiting simulation." << endl;
        return;
    }

    mtx.lock();
    Segment *currPtr = tTrainTracks->getPtrToSegmentAtSegmentNumber(trainPath[START]);
    mtx.unlock();

    int i = 0;
    bool trainNotifiedToHold = false;

    while (currPtr->left != nullptr || currPtr->right != nullptr) {

        mtx.lock();
        if ((currPtr->segmentNumber == trainPath[START]) && (currPtr->signal)) {
            cout << " Train " << tNames[trainNumber] << " is at Base Station " << currPtr->segmentNumber << endl;
            currPtr->signal = false;
        }
        else {
            if ((currPtr->left != nullptr) && (trainPath[i + 1] == currPtr->left->segmentNumber) && (currPtr->left->signal)) {
                trainNotifiedToHold = false;
                cout << " Train " << tNames[trainNumber] << " is moving to Station " << currPtr->left->segmentNumber << endl;
                currPtr->signal = true;
                currPtr->left->signal = false;
                currPtr = currPtr->left;
                i++;
            }
            else if ((currPtr->right != nullptr) && (trainPath[i + 1] == currPtr->right->segmentNumber) && (currPtr->right->signal)) {
                trainNotifiedToHold = false;
                cout << " Train " << tNames[trainNumber] << " is moving to Station " << currPtr->right->segmentNumber
                     << endl;
                currPtr->signal = true;
                currPtr->right->signal = false;
                currPtr = currPtr->right;
                i++;
            }
            else {
                if (!trainNotifiedToHold) {
                    if ((currPtr->segmentNumber == trainPath[START]) && (!currPtr->signal))
                        cout << " Train " << tNames[trainNumber] << " is waiting to enter tracks via Base Station " << currPtr->segmentNumber << endl;
                    else
                        cout << " Train " << tNames[trainNumber] << " is waiting at Station " << currPtr->segmentNumber << endl;
                    trainNotifiedToHold = true;
                }
            }
        }
        mtx.unlock();
        sleep(1); // time to travel per segment
    }

    mtx.lock();
    if (currPtr->segmentNumber == trainPath[i]) {
        cout << " Train " << tNames[trainNumber] << " is at Terminal Station " << currPtr->segmentNumber << endl;
        currPtr->signal = true;
    }
    mtx.unlock();

    time(&eTime);
    *runTimes = eTime - sTime;
}