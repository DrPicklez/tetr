#include "tetris.h"
//--------------------------------------------------------------
void Tetris::setup(){
//    shapes.push_back((int*)&square);
//    shapes.push_back((int*)&line);
//    shapes.push_back((int*)&ell);
    shapeFbo.allocate(4, 4);
}
//--------------------------------------------------------------

void Tetris::rotate(){
    int i = 0;
    for(int x = 0; x < 4; x ++){
        for(int y = 0; y < 4; y ++){
            cout << shapeGrid[x][y];
            int xPos = 4-x;
            int yPos = 4-y;
            if(shapeGrid[xPos][yPos]){
                phantomShape[i][0] = x;
                phantomShape[i][1] = y;
                i ++;
            }
        }
        cout << endl;
    }
    cout << "  "  << endl;

    for(int x = 0; x < 4; x ++){
        for(int y = 0; y < 4; y ++){
            cout << shapeGrid[x][y];
//            int xPos = x;
//            int yPos = y;
//            if(shapeGrid[xPos][yPos]){
//                phantomShape[i][0] = xPos;
//                phantomShape[i][1] = yPos;
//                i ++;
            }
        cout << endl;
        }


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

        phantomShape[i][0] = le[i][0];
        phantomShape[i][1] = le[i][1];
        shape[i][0] = phantomShape[i][0] + position[0];
        shape[i][1] = phantomShape[i][1] + position[1];
        shapeGrid[phantomShape[i][0]][phantomShape[i][1]] = true;
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
    }
}
