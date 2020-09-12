//
// Created by Chinedu Nwiyi on 2020-09-09.
//

// this file implements debug utility functions

#ifndef TRAIN_SIGNALING_SYSTEM_DEBUG_UTILS_H
#define TRAIN_SIGNALING_SYSTEM_DEBUG_UTILS_H

#include <iostream>
#include <vector>

using namespace std;

/**
 * Function displays 1D vector.
 *
 * @param vec
 * @param between
 */
void display_1D_vector_info(const vector<int> &vec, char between);

/**
 * Function displays 2D vector.
 *
 * @param vData
 */
void display_2D_vector_info(const vector<vector<int>> &vData);

/**
 * Function display train tracks or paths.
 *
 * @param vTracks
 */
void display_track_info(const vector<vector<int>> &vTracks);

/**
 * Function displays track information.
 *
 * @param tNames
 * @param vTrains
 */
void display_train_info(const vector<string> &tNames, const vector<vector<int>> &vTrains);

#endif //TRAIN_SIGNALING_SYSTEM_DEBUG_UTILS_H
