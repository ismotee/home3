#include "pallo.h"




pallo::pallo(ofPoint paikka_, int lapsia_): paikka(paikka_), lapsia(lapsia_), osuSeinaan(false), vari(ofColor::cyan) {
    setup();
}

ofColor asetaHSLnMukaan(float lh, float ls, float ll) {
    float bh = lh;
    if (ll <= 0.5)
        ls *= ll;
    else
        ls *= 1 - ll;

    float bb = ll + ls;
    float bs = (2 * ls) / (ll + ls);

    ofColor col = ofColor::white;
    col.setHsb(bh, bs * 255, bb * 255);

    return col;
}

void pallo::setup() {
    //    paikka = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
    liike = ofVec2f();
    mass = ofRandom(0.001, 1);
    vari = ofColor::cyan;
    vari.setHue(vari.getHue() + ofRandom(-40, 40));
    vari.a = 6;

    time = ofGetElapsedTimef();
    timeLast = time;
    piirretaan = true;
    elinaika = 1 + ofRandomuf() * 5;
}

/*
void pallo::setup(ofVec3f paikka_) {
    paikka = paikka_;
    setup();
}
*/
void pallo::update(VectorField& field) {
    
    float timeDelta =ofGetElapsedTimef()-timeLast;
    timeLast = ofGetElapsedTimef();
    
    liike += field.getElementScaled(paikka.x, paikka.y) / mass*timeDelta;
    liike *= 0.995;
    paikka += liike;

    paikka.x = ofClamp(paikka.x, 0, ofGetWidth() - 1);
    paikka.y = ofClamp(paikka.y, 0, ofGetHeight() - 1);

    if (paikka.x == ofGetWidth() - 1 || paikka.x == 0) {
        liike.x = 0;
        osuSeinaan = true;
    }
    if (paikka.y == ofGetHeight() - 1 || paikka.y == 0) {
        liike.y = 0;
        osuSeinaan = true;
    }
    vari.setBrightness(50 + liike.length()*400);
    vari.setSaturation(200 - liike.length()*200);
}

void pallo::draw() {
    if (piirretaan) {
        float radius = lapsia / 20 + 1.5;
        float halfR = radius * 0.5;
        ofSetColor(vari);
        ofDrawCircle(paikka.x - halfR, paikka.y - halfR, 0, radius);
    }
}

