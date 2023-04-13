#include "tetris.h"
//--------------------------------------------------------------
void Tetris::setup(){
    reset();
    nextShape();
}


//--------------------------------------------------------------
void Tetris::rotate(){
    int colShape[4][2];
    for(int i = 0; i < 4; i ++){
        colShape[i][0] = phantomShape[i][0];
        colShape[i][1] = phantomShape[i][1];
        int xA = phantomShape[i][0];
        int yA = phantomShape[i][1];
        phantomShape[i][1] = xA;
        phantomShape[i][0] = 3 - yA;
        shape[i][0] = phantomShape[i][0] + position[0];
        shape[i][1] = phantomShape[i][1] + position[1];
    }
    if(detectCollision()){
        for(int i = 0; i < 4; i ++){
            phantomShape[i][0] = colShape[i][0];
            phantomShape[i][1] = colShape[i][1];
            shape[i][0] = phantomShape[i][0] + position[0];
            shape[i][1] = phantomShape[i][1] + position[1];
        }
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
void Tetris::sitShape(){
    for(int i = 0; i < 4; i ++){
        grid[shape[i][0]][shape[i][1]] = 1; //block to stay in grid
    }


    int yDown = 0;      //shift blocks down on full line
    for(int y = gridY; y > 0; y--){
        int sum=0;
        for(int x = 0; x < gridX; x++){
//            grid[x][y] = grid[x][y - yDown];    //this does not work
            sum += grid[x][y];
        }
        if(sum == gridX){
            for(int x = 0; x < gridX; x++){
                grid[x][y] = 0;
            }
            yDown ++;
        }

        for(int y2 = y; y2 > 0; y2 --){
            for(int x2 = 0; x2 < gridX; x2++){
                grid[x2][y2] = grid[x2][y2 - yDown];    //this does not work
            }
        }
    }

}
//--------------------------------------------------------------
int nShape = 0;
void Tetris::nextShape(){
    position[0] = gridX /2;
    position[1] = 0;
    for(int i = 0; i < 4; i ++){
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
                sitShape();
                nextShape();
                reset();
            }
            else{
                sitShape();
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
