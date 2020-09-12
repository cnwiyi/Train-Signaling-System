//
// Created by Chinedu Nwiyi on 2020-09-09.
//

// File: Headers for simulation

#ifndef TRAIN_SIGNALING_SYSTEM_SIMULATION_H
#define TRAIN_SIGNALING_SYSTEM_SIMULATION_H

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "train_tracks.h"

using namespace std;

#define START 0
#define END 1

/**
 * This function moves the trains along the train tracks from start station to the end station.
 *
 * @param trainNumber
 * @param tNames
 * @param vTrains
 * @param vTracks
 * @param tTrainTracks
 */
void simulate_train_on_tracks(int trainNumber,
                              const vector<string> &tNames,
                              const vector<vector<int>> &vTrains,
                              const vector<vector<int>> &vTracks,
                              TrainTracks *tTrainTracks,
                              int *runTimes);

#endif //TRAIN_SIGNALING_SYSTEM_SIMULATION_H
