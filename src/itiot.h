#pragma once
#include "ofMain.h"
#include "pallo.h"
#include "VectorField.h"

struct itiot: public ofThread {
    
    VectorField field;
    std::vector<pallo> pallot;
    ofMutex mutex;
    
    void setup(int x, int y);
    void threadedFunction();
    void update();
    std::vector<pallo> getPallot();
    void draw();
    void uusiItio(int x,int y);
    ofTimer timer;
    

    bool mustaa;
    int mustausLaskuri;
    int mustausIntervalli;
    
};
