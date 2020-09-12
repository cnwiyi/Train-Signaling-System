//
// Created by Chinedu Nwiyi on 2020-09-09.
//

// This file implements the necessary functions to build a tree (network of train tracks)

#include "train_tracks.h"

#define SPACING 8

// class implementations

/**
 *
 */
TrainTracks::TrainTracks() {
    root = nullptr;
}

/**
 *
 */
TrainTracks::~TrainTracks()
{
    _destroyTrainTracks(root);
}

/**
 *
 * @return
 */
int TrainTracks::isEmpty() {
    return(root == nullptr);
}

/**
 *
 * @param node
 */
void TrainTracks::_destroyTrainTracks(Segment *node)
{
    if(node != nullptr)
    {
        _destroyTrainTracks(node->left);
        _destroyTrainTracks(node->right);
        delete node;
    }
}

/**
 *
 */
void TrainTracks::displayTrainTracksTree(){
    _displayTrainTracksTree(root);
}

/**
 *
 */
void TrainTracks::_displayTrainTracksTree(Segment *ptr){
    if(ptr!= nullptr){
        _displayTrainTracksTree(ptr->left);
        cout<<"  "<<ptr->segmentNumber<<" ";
        _displayTrainTracksTree(ptr->right);
    }
}

/**
 *
 */
void TrainTracks::displayTrainTracksTree2D(){
    _displayTrainTracksTree2D(root, 0);
}

/**
 *
 * @param ptr
 * @param space
 */
void TrainTracks::_displayTrainTracksTree2D(Segment *ptr, int space)
{
    if (ptr == nullptr)
        return;

    space += SPACING;

    _displayTrainTracksTree2D(ptr->right, space);

    cout << endl;
    for (int i = SPACING; i < space; i++)
        cout<<" ";
    cout << ptr->segmentNumber << "\n";

    _displayTrainTracksTree2D(ptr->left, space);
}

/**
 *
 * @param key
 * @return
 */
bool TrainTracks::searchIfSegmentExists(int key) {
    return _searchIfSegmentExists(root, key);
}

/**
 *
 * @param node
 * @param key
 * @return
 */
bool TrainTracks::_searchIfSegmentExists(Segment *node, int key) {
    if (node == nullptr)
        return false;

    if (node->segmentNumber == key)
        return true;

    bool res1 = _searchIfSegmentExists(node->left, key);
    if (res1)
        return true;

    bool res2 = _searchIfSegmentExists(node->right, key);
    return res2;
}

/**
 *
 * @param key
 * @return
 */
Segment* TrainTracks::getPtrToSegmentAtSegmentNumber(int key) {
    return _getPtrToSegmentAtSegmentNumber(root, key);
}

/**
 *
 * @param node
 * @param key
 * @return
 */
Segment* TrainTracks::_getPtrToSegmentAtSegmentNumber(Segment *node, int key) {
    if(node != nullptr)
    {
        if(node->segmentNumber == key) {return node;}

        Segment *temp = this->_getPtrToSegmentAtSegmentNumber(node->right, key);
        if (temp != nullptr)
            return temp;
        return this->_getPtrToSegmentAtSegmentNumber(node->left, key);
    }
    return nullptr;
}

/**
 *
 * @param path
 */
void TrainTracks::insertPathInTrainTrack(vector<int> path) {
    for (int i = 0; i<path.size(); i++) {
        Segment *p = new Segment;
        p->segmentNumber = path[i];
        p->left = nullptr;
        p->right = nullptr;
        p->signal = true;

        if (isEmpty()) {
            root = p;
        }
        else {
            Segment *parent;

            // grab parent node and add segment if not yet added
            if (!searchIfSegmentExists(path[i])) {
                parent = getPtrToSegmentAtSegmentNumber(path[i-1]);

                if (parent->left == nullptr)
                    parent->left = p;
                else if (parent->right == nullptr)
                    parent->right = p;
                else
                    cout << "Error with track format or data" << endl;
            }
        }
    }
}

/**
 *
 */
Segment* TrainTracks::getRootSegment() {
    return this->root;
}

/**
 *  Wrapper to insert call.
 *
 * @param tTrainTrack
 * @param path
 */
static void insert_path_on_track(TrainTracks *tTrainTrack, vector<int> path)
{
    tTrainTrack->insertPathInTrainTrack(path);
}

TrainTracks create_train_tracks_vector(const vector<vector<int>> &vTrainTracks)
{
    TrainTracks tTrainTracks;

    for (int i = 1; i < vTrainTracks.size(); i++) {
        insert_path_on_track(&tTrainTracks, vTrainTracks[i]);
    }

#ifdef DISPLAY
    cout << "Display train tracks (Inorder DF Traversal): ";
    tTrainTracks.displayTrainTracksTree();
    cout << endl;

    cout << endl;
    cout << "Display train tracks (Web): ";
    tTrainTracks.displayTrainTracksTree2D();
#endif

    return tTrainTracks;
}
