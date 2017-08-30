#include "VectorField.h"

void VectorField::setup(int w_, int h_) {
    w = w_;
    h = h_;
    xScale = (float)w / ofGetWidth();
    yScale = (float)h / ofGetHeight();
    xHalfScale = ofGetWidth() / w * 0.5;
    yHalfScale = ofGetHeight() / h * 0.5;

    field.resize(w*h, ofVec2f(1, 0));
    for (ofVec2f& vec : field)
        vec.rotate(ofRandom(-180, 180));
}

void VectorField::draw() {
    ofSetColor(ofColor::white);
    for(int y = 0; y < h;y++) {
        for(int x = 0; x < w; x++) {
            int i = x + y*w;
            ofPoint place(x/xScale+xHalfScale,y/yScale+yHalfScale);
            ofDrawArrow(place,place+field[i]*10,2);
        }
    }
}

ofVec2f& VectorField::getElement(float x, float y) {
    return field[x + y * w];
}

ofVec2f& VectorField::getElementScaled(float x, float y) {
    int xScaled = ofClamp((int) x * xScale,0,w-1);
    int yScaled = ofClamp((int) y * yScale,0,h-1);

    return field.at(xScaled + yScaled * w);
}

