#include "ofApp.h"

//static const int PALLOT_MAX = 20000;


//--------------------------------------------------------------

void ofApp::setup() {

    //ofSetDepthTest(true);
    ofResetElapsedTimeCounter();


    ofBackground(0, 0, 0);
    ofSetBackgroundAuto(false);
    ofSetFrameRate(60);

    the_itiot.setup(500, 500);
    //field.setup(500, 500);
    mustaa = false;

    mustausIntervalli = 4;

}

//--------------------------------------------------------------

void ofApp::update() {
    pallot = the_itiot.getPallot();
}

//--------------------------------------------------------------

void ofApp::draw() {
    // field.draw();
    mustausLaskuri++;
    // mustaa = !mustaa;
    if (mustaa && mustausLaskuri % mustausIntervalli == 0) {
        mustausLaskuri = 1;
        ofSetColor(0, 0, 0, 1500 / (pallot.size() + 1));
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }

    for (auto& pallo : pallot)
        pallo.draw();


    //ofSetColor(ofColor::white);
    //ofDrawBitmapString(ofToString(pallot.size()), 20, 20);



}

//--------------------------------------------------------------

void ofApp::keyPressed(int key) {
    /*
        if (key == OF_KEY_RETURN) {

            for (int i = 0; i < 30; i++) {
                float x = ofClamp(ofGetMouseX(), 0, ofGetWidth());
                float y = ofClamp(ofGetMouseY(), 0, ofGetHeight());
                pallot.push_back(pallo());
                pallot.back().setup(ofVec3f(x, y));
                pallot.back().piirretaan = false;
            }
        }
     */
    if (key == ' ')
        mustaa = !mustaa;

}

//--------------------------------------------------------------

void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button) {
    /*
        if (pallot.size() < PALLOT_MAX) {
            for (int i = 0; i < 5; i++) {
                pallot.push_back(pallo());
                pallot.back().setup(ofVec3f(x, y));
                pallot.back().piirretaan = false;
            }
        }
     */
    if (x != 0 && y != 0)
        the_itiot.uusiItio(x, y);
}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button) {
    /*
        if (pallot.size() < PALLOT_MAX) {
            for (int i = 0; i < 30; i++) {
                pallot.push_back(pallo());
                pallot.back().setup(ofVec3f(x, y));
                pallot.back().piirretaan = false;
            }
        }
     */
}

//--------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------

void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------

void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------

void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------

void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------

void ofApp::dragEvent(ofDragInfo dragInfo) {

}