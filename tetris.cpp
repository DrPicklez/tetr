#include "tetris.h"
//--------------------------------------------------------------
void Tetris::setup(){
    reset();
    nextShape();
}


//--------------------------------------------------------------
void Tetris::rotate(){
    /* rotate shape, use a box of 5 wide,
     * 90^ flip x / y
     * then - centrepoint of 5 (3)
     * ???????????????????????
    */
    for(int i = 0; i < 4; i ++){
        int xA = phantomShape[i][0];
        int yA = phantomShape[i][1];
        phantomShape[i][1] = xA;
        phantomShape[i][0] = 3 - yA;
        shape[i][0] = phantomShape[i][0] + position[0];
        shape[i][1] = phantomShape[i][1] + position[1];
    }

    /*
    bool shapeGrid[4][4] = {0,0,0,0,
                            0,0,0,0,
                            0,0,0,0,
                            0,0,0,0};

    for( int i = 0; i < 4; i ++){
        shapeGrid[phantomShape[i][0]][phantomShape[i][1]] = 1;
    }

    //backward---------------------------------------
    int i = 0;
    for(int x = 0; x < 4; x ++){
        for(int y = 0; y < 4; y ++){
            if(shapeGrid[x][y]){
                phantomShape[i][1] = 4-x;
                phantomShape[i][0] = 4-y;
                i ++;
                cout << x << "  " << y << endl;
            }
        }
    }
    //flip---------------------------------------
    cout << "  "  << endl;
    for(int i = 0; i < 4; i ++){
        int x = phantomShape[i][0];
        int y = phantomShape[i][1];

        phantomShape[i][0] = y;
        phantomShape[i][1] = x;
    }

    for(int x = 0; x < 4; x ++){
        for(int y = 0; y < 4; y ++){
            shapeGrid[x][y] = false;
        }
    }

    for(int i = 0; i < 4; i ++){
        shape[i][0] = phantomShape[i][0] + position[0];
        shape[i][1] = phantomShape[i][1] + position[1];
        shapeGrid[phantomShape[i][0]][phantomShape[i][1]] = true;
    }

*/
}
//--------------------------------------------------------------
bool Tetris::detectCollision(){
    for(auto block : shape){
        if((block[1] >= gridY) || (block[0] >= gridX) || (block[0] < 0)){
            return true;
        }
        else if (grid[block[0]][block[1]]) {
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------
void Tetris::update(){
    move(TETRIS_MOVE_DOWN);
}
//--------------------------------------------------------------
void Tetris::reset(){
    for(int x = 0; x < gridX; x ++){
        for(int y = 0; y < gridY; y ++){
            grid[x][y] = 0;
        }
    }
}

//--------------------------------------------------------------
int nShape = 0;
void Tetris::nextShape(){
    position[0] = gridX /2;
    position[1] = 0;
    for(int i = 0; i < 4; i ++){
        grid[shape[i][0]][shape[i][1]] = 1; //block to stay

        phantomShape[i][0] = line[i][0];
        phantomShape[i][1] = line[i][1];

        shape[i][0] = phantomShape[i][0] + position[0];
        shape[i][1] = phantomShape[i][1] + position[1];
//        shapeGrid[phantomShape[i][0]][phantomShape[i][1]] = true;
    }
    //nShape ++;
    //nShape = nShape % shapes.size();
}

//--------------------------------------------------------------
void Tetris::draw(){
    for(int x = 0; x < gridX; x ++){
        for(int y = 0; y < gridY; y ++){
            ofSetColor(ofColor::black);
            ofNoFill();
            for(auto block : shape){
                if(x == block[0] && y == block[1]){
                    ofFill();
                }
            }
            if(grid[x][y]){
                ofSetColor(ofColor::white);
                ofFill();
            }
            int posX = ofGetWidth() / 10;
            int posY = ofGetHeight() / 20;
            ofDrawRectangle(posX * x, posY * y, posX, posY);
        }
    }
}
//--------------------------------------------------------------

void Tetris::move(int dir){
//    cout << dir << endl;
    switch(dir){
    case TETRIS_MOVE_DOWN:
    {
//        cout << "moving down" << endl;
        position[1] += 1;
        for(int i = 0; i < 4; i ++){
            shape[i][1] = phantomShape[i][1] + position[1];  //y
        }
        if(detectCollision()){
            position[1] -= 1;
            for(int i = 0; i < 4; i ++){
                shape[i][1] = phantomShape[i][1] + position[1];  //y
            }

            if(detectCollision()){
                nextShape();
                reset();
            }
            else{
                nextShape();
            }
        }
        break;
    }

    case TETRIS_MOVE_LEFT:
    {
//        cout << "moving left" << endl;
        position[0] -= 1;
        for(int i = 0; i < 4; i ++){
            shape[i][0] = phantomShape[i][0] + position[0];  //y
        }
        if(detectCollision()){
            position[0] += 1;
            for(int i = 0; i < 4; i ++){
                shape[i][0] = phantomShape[i][0] + position[0];  //y
            }
        }
        break;
    }

    case TETRIS_MOVE_RIGHT:
    {
        position[0] += 1;
        for(int i = 0; i < 4; i ++){
            shape[i][0] = phantomShape[i][0] + position[0];  //y
        }
        if(detectCollision()){
            position[0] -= 1;
            for(int i = 0; i < 4; i ++){
                shape[i][0] = phantomShape[i][0] + position[0];  //y
            }
        }
        break;
    }

    case TETRIS_MOVE_UP:
    {
        for(auto block : shape){
            block[1] -= 1;
        }
        break;
    }
    case TETRIS_ROTATE:
    {
        for(auto block : shape){
            block[1] -= 1;
        }
        break;
    }
    }
}
