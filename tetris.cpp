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
    int min[2]{0, 0};
    int max[2]{0, 0};

    for(auto block : shape){
        shapeGrid[block[0]][block[1]] = 1;
    }


//        if(min[0] < x){
//           min[0] = x;
//        }

//        if(min[1] < y){
//           min[1] = y;
//        }

//        if(max[0] > x){
//           max[0] = x;
//        }

//        if(max[1] > y){
//           max[1] = y;
//        }
//    }

//    for(int i = 0; i < 4; i ++){
//        int x = shape[i][0];
//        int y = shape[i][1];

//        shape[i][1] = shape[i][0] + min[0];
//        shape[i][0] = shape[i][1] + min[1];
//    }
//    cout << min[0] << "minX" << endl;
//    cout << min[1] << "minY" << endl;

//    for(int i = 0; i < 4; i ++){
//        int x = shape[i][0];
//        shape[i][0] = x;
////        shape[i][0] = y;
//    }

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
//    move(TETRIS_MOVE_DOWN);
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
    for(int i = 0; i < 4; i ++){
        grid[shape[i][0]][shape[i][1]] = 1;
        shape[i][0] = le[i][0];
        shape[i][1] = le[i][1];
        shape[i][0] += (gridX / 2);
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
        for(auto block : shape){
            block[1] += 1;  //y
        }
        if(detectCollision()){
            for(auto block : shape){
                block[1] -= 1;  //y
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
        for(auto block : shape){
            block[0] -= 1;  //y
        }
        if(detectCollision()){
            for(auto block : shape){
                block[0] += 1;  //y
            }
        }
        break;
    }

    case TETRIS_MOVE_RIGHT:
    {
//        cout << "moving right" << endl;
        for(auto block : shape){
            block[0] += 1;  //y
        }
        if(detectCollision()){
            for(auto block : shape){
                block[0] -= 1;  //y
            }
//            move(TETRIS_MOVE_LEFT);   //switch use inside switch fucks up
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
