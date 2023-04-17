#include "tetris.h"
//--------------------------------------------------------------
void Tetris::setup(){
    reset();
    nShape = int(ofRandom(0, 4));
    nextShape(nShape);
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
    currentTime = ofGetElapsedTimeMillis();
    if(currentTime > blockSpeed + 200){
            blockSpeed = currentTime;
            move(TETRIS_MOVE_DOWN);
    }
    /////////////PRESS/////////////////
    if(currentTime > controlTimesPress + 100){
//        controlTimesHold = currentTime;
//        controlTimesPress  = currentTime;
//            if(cDown || cLeft || cRight){
//                controlTimesHold  = ofGetElapsedTimeMillis();
//            }

        if(cDown == 1){
            cDown = 2;
        }
        if(cLeft == 1){
            cLeft = 2;
        }
        if(cRight == 1){
            cRight = 2;
        }
    }
    /////////////HOLD/////////////////
    if(currentTime > controlTimesHold + 20){
            controlTimesHold  = currentTime;

            if(cDown == 2){
                move(TETRIS_MOVE_DOWN);
            }
            if(cLeft == 2){
                move(TETRIS_MOVE_LEFT);
            }
            if(cRight == 2){
                move(TETRIS_MOVE_RIGHT);
            }
    }
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

    int nFullLines = 0;
    for(int y = gridY; y > 0; y--){     //check lines to shift down
        int sum=0;
        for(int x = 0; x < gridX; x++){
            sum += grid[x][y];
        }
        if(sum == gridX){
            for(int y2 = y; y2 > 1; y2 --){
                for(int x= 0; x < gridX; x++){
                    grid[x][y2] = grid[x][y2 - 1];
                }
            }
            y = y +1;   //check back over shifted shapes (it was missing on multiple lines)
            nFullLines ++;
        }

    }
//    blockSpeed += 500;
    cout << nFullLines << endl;

}

//--------------------------------------------------------------
void Tetris::nextShape(int currntShape){
    int rShape = int(ofRandom(0, 4));
    if(rShape != currntShape){
        controlTimesHold = currentTime + 500;
//        cDown = 0;
//        cLeft = 0;
//        cRight = 0;

        nShape = rShape;
        position[0] = gridX /2;
        position[1] = 0;
        for(int i = 0; i < 4; i ++){
            phantomShape[i][0] = shapes[nShape][i][0];
            phantomShape[i][1] = shapes[nShape][i][1];//////// make 1 nShape <<<< TESTING

            shape[i][0] = phantomShape[i][0] + position[0];
            shape[i][1] = phantomShape[i][1] + position[1];
    //        shapeGrid[phantomShape[i][0]][phantomShape[i][1]] = true;
        }
    }
    else {
        nextShape(currntShape);
    }

    //nShape ++;
    //nShape = nShape % shapes.size();
}

//--------------------------------------------------------------
void Tetris::draw(){
    ofPushStyle();
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

            ofNoFill();
            ofSetColor(ofColor::black);
            ofDrawRectangle(posX * x, posY * y, posX, posY);
        }
    }
    ofPopStyle();
}
//--------------------------------------------------------------
void Tetris::control(int dir, bool onOff){
    //    cout << dir << endl;
        switch(dir){
        case TETRIS_MOVE_DOWN:
        {
            if((onOff) && (cDown == 0)){
                move(TETRIS_MOVE_DOWN);
                cDown = 1;
//                cout << "TETRIS_MOVE_DOWN" << onOff << endl;
            }
            else if(!onOff){
                cDown = 0;
//                cout << "TETRIS_MOVE_DOWN" << onOff << endl;
            }
            break;
        }

        case TETRIS_MOVE_LEFT:
        {
            if((onOff) && (cLeft == 0)){
                move(TETRIS_MOVE_LEFT);
//                cout << "TETRIS_MOVE_LEFT" << onOff << endl;
                cLeft = 1;
            }
            else if(!onOff){
                cLeft = 0;
//                cout << "TETRIS_MOVE_LEFT" << onOff << endl;
            }
            break;
        }

        case TETRIS_MOVE_RIGHT:
        {
            if((onOff) && (cRight == 0)){
//                cout << "TETRIS_MOVE_RIGHT" << onOff << endl;
                move(TETRIS_MOVE_RIGHT);
                cRight = 1;
            }
            else if(!onOff){
//                cout << "TETRIS_MOVE_RIGHT" << onOff << endl;
                cRight = 0;}
            break;
        }
    }
        controlTimesPress = currentTime;
}
//--------------------------------------------------------------
void Tetris::move(int dir){
//    cout << dir << endl;
    switch(dir){
    case TETRIS_MOVE_DOWN:
    {
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
                nextShape(nShape);
                reset();
            }
            else{
                sitShape();
                nextShape(nShape);
            }
        }

        break;
    }

    case TETRIS_MOVE_LEFT:
    {
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
        break;
    }
}
