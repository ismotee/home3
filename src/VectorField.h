#pragma once
#include "ofMain.h"


struct VectorField {
    int w,h;
    float xScale,yScale;
    float xHalfScale, yHalfScale;
    
    vector<ofVec2f> field;
    
    void setup(int w_,int h_);
    void draw();
    
    ofVec2f& getElement(float x,float y);
    ofVec2f& getElementScaled(float x, float y);
    
};
