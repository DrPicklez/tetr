#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    tetris.setup();



}
//--------------------------------------------------------------
void ofApp::update(){
    tetris.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    tetris.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_LEFT){
        tetris.control(TETRIS_MOVE_LEFT, true);
    }
    else if(key == OF_KEY_RIGHT){
        tetris.control(TETRIS_MOVE_RIGHT, true);
    }
    else if(key == OF_KEY_DOWN){
        tetris.control(TETRIS_MOVE_DOWN, true);
    }
    else if(key == OF_KEY_UP){
        tetris.move(TETRIS_ROTATE);
    }
    else if(key == OF_KEY_CONTROL){
        tetris.blockSpeed -= 10;
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == OF_KEY_LEFT){
        tetris.control(TETRIS_MOVE_LEFT, false);
    }
    else if(key == OF_KEY_RIGHT){
        tetris.control(TETRIS_MOVE_RIGHT, false);
    }
    else if(key == OF_KEY_DOWN){
        tetris.control(TETRIS_MOVE_DOWN, false);
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
