#ifndef TETRIS_H
#define TETRIS_H

#include "ofMain.h"

#define TETRIS_MOVE_DOWN 0
#define TETRIS_MOVE_LEFT 1
#define TETRIS_MOVE_RIGHT 2
#define TETRIS_MOVE_UP 3
#define TETRIS_ROTATE 4


class Tetris
{
public:
    void setup();
    void rotate();
    void draw();
    void move(int dir);
    void update();
    bool detectCollision();
    void nextShape();
    void reset();
    void sitShape();

    int gridX = 10;
    int gridY = 20;
    bool grid[10][20];
    int shape[4][2] = {0, 0, 0, 1, 1, 1, 2, 1};
    int phantomShape[4][2] = {0, 0, 0, 1, 1, 1, 2, 1};
    int resetShape [4][2] = {0, 0, 0, 1, 0, 2, 0, 3};

    ofFbo shapeFbo;
    int position[2];
    int blocker;

    int square [4][2] = {1, 1, 2, 1, 1, 2, 2, 2};
    int line[4][2] = {2, 0, 2, 1, 2, 2, 2, 3};
    int ez [4][2] = {0, 1, 1, 1, 1, 0, 2, 0};
    int ze [4][2] = {0, 0, 1, 0, 1, 1, 2, 1};
    int el [4][2] = {0, 0, 0, 1, 1, 1, 2, 1};
    int le [4][2] = {2, 0, 0, 1, 1, 1, 2, 1};
    vector<int*> shapes;


//    int lle [4][2] = {1, 0, 1, 1, 1, 1, 1, 2};
    bool controlBlocker;


};

#endif // TETRIS_H
