//
// Created by Chinedu Nwiyi on 2020-09-09.
//

// This file implements the necessary functions to build a tree (network of train tracks)

#ifndef TRAIN_SIGNALING_SYSTEM_TRAIN_TRACKS_H
#define TRAIN_SIGNALING_SYSTEM_TRAIN_TRACKS_H

#include <iostream>
#include <vector>

using namespace std;

struct Segment {
    Segment *left; // holds info for next track
    Segment *right; // holds info for other track if node is a junction
    int segmentNumber; // segment or track number
    bool signal; // true: green/go & false: red/stop
};

class TrainTracks {
public:
    TrainTracks();
    ~TrainTracks();

    int isEmpty();
    void displayTrainTracksTree();
    void displayTrainTracksTree2D();
    bool searchIfSegmentExists(int key);
    Segment* getPtrToSegmentAtSegmentNumber(int key);
    void insertPathInTrainTrack(vector<int> path); // todo: success and failure
    Segment* getRootSegment();

private:
    Segment *root;

    static void _displayTrainTracksTree(Segment *root); // inorder traversal
    static void _displayTrainTracksTree2D(Segment *root, int space); // reverse inorder traversal
    bool _searchIfSegmentExists(Segment *root, int key);
    Segment* _getPtrToSegmentAtSegmentNumber(Segment *node, int key);
    void _destroyTrainTracks(Segment *root);
};

// other train track specific functions

/**
 * Function builds a binary tree of train tracks network.
 *
 * @param vTrainTracks
 * @return
 */
TrainTracks create_train_tracks_vector(const vector<vector<int>> &vTrainTracks);

#endif //TRAIN_SIGNALING_SYSTEM_TRAIN_TRACKS_H
