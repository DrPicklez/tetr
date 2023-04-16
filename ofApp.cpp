#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    tetris.setup();



}
//--------------------------------------------------------------
uint64_t times = 0;
void ofApp::update(){
    if(!controlBlock){
        if(ofGetElapsedTimeMillis() > times + 200){
            times = ofGetElapsedTimeMillis();
            tetris.update();
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
    }
    else if(key == OF_KEY_RIGHT){
        tetris.move(TETRIS_MOVE_RIGHT);
//        cout << "RIGHT" << endl;
    }
    else if(key == OF_KEY_UP){
        tetris.move(TETRIS_ROTATE);
    }
    else if(key == OF_KEY_DOWN){
//        cout << "DOWN  " << endl;
        tetris.move(TETRIS_MOVE_DOWN);
    }
//    controlBlock = 0;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
