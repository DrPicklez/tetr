#include "tetris.h"
//--------------------------------------------------------------
void Tetris::setup(int width, int height){
    tetrisFBO.allocate(width, height, GL_RGBA);
    ttf.load("ARCADECLASSIC.TTF", 32);
    tetrisScoreFBO.allocate(ttf.getSize() * 6, ttf.getSize() + 5, GL_RGBA);


//    ofClear(255,255,255, 0);
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
    if(currentTime > blockTime + blockSpeed){
            blockTime = currentTime;
            if((cDown == 0) || (satDown)){
                move(TETRIS_MOVE_DOWN);
            }
    }
    /////////////PRESS/////////////////     add seperate control presses
    if(currentTime > controlTimesPressD + blockSpeed/2){
        controlTimesPressD = currentTime;
        if(cDown == 1){
            cDown = 2;
        }
    }
    if(currentTime > controlTimesPressL + blockSpeed/2){
        controlTimesPressL = currentTime;
        if(cLeft == 1){
            cLeft = 2;
        }
    }
    if(currentTime > controlTimesPressR + blockSpeed/2){
        controlTimesPressR = currentTime;
        if(cRight == 1){
            cRight = 2;
        }
    }
    /////////////HOLD/////////////////
    if(currentTime > controlTimesHoldD + blockSpeed/4){
        controlTimesHoldD  = currentTime;
        if((cDown == 2) && (!satDown)){
            move(TETRIS_MOVE_DOWN);
        }
    }
    if(currentTime > controlTimesHoldL + blockSpeed/4){
        controlTimesHoldL = currentTime;
        if(cLeft == 2){
            move(TETRIS_MOVE_LEFT);
        }
    }
    if(currentTime > controlTimesHoldR + blockSpeed/4){
        controlTimesHoldR = currentTime;
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
//    cout << nFullLines << endl;
    score += nFullLines;

}

//--------------------------------------------------------------
void Tetris::nextShape(int currntShape){
    int rShape = int(ofRandom(0, 7));
    if(rShape != currntShape){
        controlTimesHoldD = currentTime + 250;
        controlTimesHoldL = currentTime + 250;
        controlTimesHoldR = currentTime + 250;

        nShape = rShape;
        position[0] = gridX /2;
        position[1] = 0;
        for(int i = 0; i < 4; i ++){
            phantomShape[i][0] = shapes[nShape][i][0];
            phantomShape[i][1] = shapes[nShape][i][1];//////// make 1 nShape <<<< TESTING

            shape[i][0] = phantomShape[i][0] + position[0];
            shape[i][1] = phantomShape[i][1] + position[1];
        }
    }
    else {
        nextShape(currntShape);
    }

    //nShape ++;
    //nShape = nShape % shapes.size();
}

//--------------------------------------------------------------
void Tetris::drawScore(int x, int y, int wid, int hig){
    tetrisScoreFBO.begin();
    ofPushStyle();
//    ofDisableSmoothing();
    ofBackground(ofColor::purple);

    ofSetColor(ofColor::yellow);
    string original_string = ofToString(score);
    int leadingZeros = score / 10;
    std::string dest = std::string( 6 - leadingZeros, '0').append( original_string);
    ttf.drawString(dest, 0, ttf.getSize());
    ofPopStyle();
    tetrisScoreFBO.end();

    ofPushStyle();
////    ofDisableSmoothing();
////    ofDisableAntiAliasing();
////    ofDisableTextureEdgeHack();
    ofSetRectMode(OF_RECTMODE_CORNER);
    tetrisScoreFBO.draw(x, y);

    ofPopStyle();
}
//--------------------------------------------------------------
void Tetris::draw(int x, int y, int wid, int hig){
    tetrisFBO.begin();
    ofPushStyle();
//    ofClear(255,255,255, 0);
    ofFill();
    if((cDown == 2) || (cLeft == 2) || (cRight == 2)){
        ofSetColor(ofColor::black, 85);
    }
    else {
        ofSetColor(ofColor::black, 255);
    }
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()); // motion
    ofPopStyle();

    ofPushStyle();

    int posX = tetrisFBO.getWidth() / 10;
    int posY = tetrisFBO.getHeight()/ 20;
    for(int x = 0; x < gridX; x ++){
        for(int y = 0; y < gridY; y ++){
            ofSetColor(ofColor::yellow);
            ofNoFill();
            for(auto block : shape){
                if(x == block[0] && y == block[1]){
                    ofFill();
                }
            }
            if(grid[x][y]){
                ofSetColor(ofColor::purple);
                ofFill();
            }

            ofDrawRectangle(posX * x, posY * y, posX, posY);


            ofNoFill();
            ofSetColor(ofColor::black);
            ofDrawRectangle(posX * x, posY * y, posX, posY);
        }
    }
    ofPopStyle();
    tetrisFBO.end();

    tetrisFBO.draw(x, y, wid, hig);
}
//--------------------------------------------------------------
void Tetris::control(int dir, bool onOff){
    //    cout << dir << endl;
        switch(dir){
        case TETRIS_MOVE_DOWN:
        {
            if((onOff) && (cDown == 0) && (!satDown)){
                move(TETRIS_MOVE_DOWN);
                controlTimesPressD = currentTime;
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
                controlTimesPressL = currentTime;
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
                controlTimesPressR = currentTime;
                cRight = 1;
            }
            else if(!onOff){
//                cout << "TETRIS_MOVE_RIGHT" << onOff << endl;
                cRight = 0;}
            break;
        }
    }
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
            if(satDown){    //flip** to allow final move once hit floor
                sitShape();
                nextShape(nShape);
                satDown = false;
                break;
            }

            if(detectCollision()){  //hit the top
                sitShape();
                nextShape(nShape);
                reset();
            }
            else{
                satDown = true; //flop**
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
