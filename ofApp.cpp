#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    tetris.setup();



}
//--------------------------------------------------------------
uint64_t updateTimes = 0;
uint64_t controlTimesOne = 0;
uint64_t controlTimesTwo = 0;
void ofApp::update(){
    if(ofGetElapsedTimeMillis() > updateTimes + 200){
            updateTimes = ofGetElapsedTimeMillis();
            tetris.update();
    }
    /////////////PRESS/////////////////
    if(ofGetElapsedTimeMillis() > controlTimesOne + 300){
            controlTimesOne = ofGetElapsedTimeMillis();

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
    if(ofGetElapsedTimeMillis() > controlTimesTwo + 50){
            controlTimesTwo = ofGetElapsedTimeMillis();

            if(cDown == 2){
                tetris.move(TETRIS_MOVE_DOWN);
            }
            if(cLeft == 2){
                tetris.move(TETRIS_MOVE_LEFT);
            }
            if(cRight == 2){
                tetris.move(TETRIS_MOVE_RIGHT);
            }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    tetris.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //ofKeyEventArgs
//    controlBlock = 1;
    if(key == OF_KEY_LEFT){
        tetris.move(TETRIS_MOVE_LEFT);
        cLeft = 1;
    }
    else if(key == OF_KEY_RIGHT){
        tetris.move(TETRIS_MOVE_RIGHT);
        cRight = 1;
//        cout << "RIGHT" << endl;
    }
    else if(key == OF_KEY_UP){
        tetris.move(TETRIS_ROTATE);
//        cUp = true;
    }
    else if(key == OF_KEY_DOWN){
//        cout << "DOWN  " << endl;
        tetris.move(TETRIS_MOVE_DOWN);
        cDown = 1;
    }
//    controlBlock = 0;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == OF_KEY_LEFT){
        cLeft = false;
    }
    else if(key == OF_KEY_RIGHT){
        cRight = false;
    }
    else if(key == OF_KEY_UP){
        cUp = false;
    }
    else if(key == OF_KEY_DOWN){
        cDown = false;
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
