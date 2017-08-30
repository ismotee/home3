#pragma once
#include "ofMain.h"
#include "VectorField.h"

struct pallo {
    ofColor vari;
    ofVec2f liike;
    ofPoint paikka;
    float mass;
    float time;
    float timeLast;
    int lapsia;
    bool piirretaan;
    bool osuSeinaan;
    float elinaika;
    
    
    pallo(ofPoint paikka_, int lapsia_);
    
    
    //void setup(ofVec3f paikka_);
    void setup();
    void update(VectorField& field);
    void draw();
    
};

