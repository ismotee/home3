#include "itiot.h"

static const int PALLOT_MAX = 20000;

void itiot::setup(int x, int y) {

    mustausLaskuri = 0;
    mustausIntervalli = 4;
    mustaa = true;

    field.setup(x, y);
    startThread(true);

    timer.setPeriodicEvent(50000000);
    pallot.clear();

}

void itiot::update() {



    float timeNow = ofGetElapsedTimef();
    vector<int> tuhottavat;
    
    for (int i = 0; i < pallot.size(); i++) {
        ofScopedLock lock(mutex);
        
        
        if (pallot[i].lapsia <= 0) {
            tuhottavat.push_back(i);
            continue;
        }


        if (pallot[i].osuSeinaan) {
            tuhottavat.push_back(i);
            continue;
        }
        ofVec3f entinenPaikka = pallot[i].paikka;

        pallot[i].update(field);

        ofVec3f uusiPaikka = pallot[i].paikka;

        ofVec3f muutos = (uusiPaikka - entinenPaikka);

        ofVec3f oikea = muutos.getRotated(ofRandom(55, 75), ofVec3f(0, 0, 1));
        ofVec3f vasen = muutos.getRotated(-ofRandom(50, 70), ofVec3f(0, 0, 1));
        oikea.normalize();
        vasen.normalize();

        ofVec3f oikeaPaikka = entinenPaikka + muutos + oikea;
        ofVec3f vasenPaikka = entinenPaikka + muutos + vasen;

        field.getElementScaled(oikeaPaikka.x, oikeaPaikka.y).interpolate(oikea.normalized(), 0.10).normalize();
        field.getElementScaled(vasenPaikka.x, vasenPaikka.y).interpolate(vasen.normalized(), 0.10).normalize();

        if (timeNow - pallot[i].time > pallot[i].elinaika) {

            if (pallot[i].lapsia) {
                pallot[i].lapsia--;

                if (pallot.size() < PALLOT_MAX) {
                    pallo p(pallot[i].paikka,pallot[i].lapsia-2); 
                    pallot.push_back(p);
                }
            }

        }
    }
    
    for(int i=0 ;i < tuhottavat.size();i++)
        pallot.erase(pallot.begin() + tuhottavat[i]);


}

void itiot::threadedFunction() {


    while (isThreadRunning()) {
        timer.waitNext();


        float timeNow = ofGetElapsedTimef();

    vector<int> tuhottavat;
            ofScopedLock lock(mutex);

        for (int i = 0; i < pallot.size(); i++) {
                        

        if (pallot[i].lapsia <= 0) {
            tuhottavat.push_back(i);
            continue;
        }


        if (pallot[i].osuSeinaan) {
            tuhottavat.push_back(i);
            continue;
        }

            ofVec3f entinenPaikka = pallot[i].paikka;
            pallot[i].update(field);

            ofVec3f uusiPaikka = pallot[i].paikka;

            ofVec3f muutos = (uusiPaikka - entinenPaikka);

            ofVec3f oikea = muutos.getRotated(ofRandom(55, 85), ofVec3f(0, 0, 1));
            ofVec3f vasen = muutos.getRotated(-ofRandom(50, 80), ofVec3f(0, 0, 1));
            oikea.normalize();
            vasen.normalize();

            ofVec3f oikeaPaikka = entinenPaikka + muutos + oikea;
            ofVec3f vasenPaikka = entinenPaikka + muutos + vasen;

            field.getElementScaled(oikeaPaikka.x, oikeaPaikka.y).interpolate(oikea.normalized(), 0.10).normalize();
            field.getElementScaled(vasenPaikka.x, vasenPaikka.y).interpolate(vasen.normalized(), 0.10).normalize();

            
            if (timeNow - pallot[i].time > pallot[i].elinaika) {

                if (pallot[i].lapsia) {
                    pallot[i].lapsia--;

                    if (pallot.size() < PALLOT_MAX)
                        pallot.push_back(pallo(pallot[i].paikka, pallot[i].lapsia - 1));

                }

            }
        }
        for(int i=0 ;i < tuhottavat.size();i++)
        pallot.erase(pallot.begin() + tuhottavat[i]);

    }
}

void itiot::draw() {

    //field.draw();
    mustausLaskuri++;
    // mustaa = !mustaa;
    if (mustaa && mustausLaskuri % mustausIntervalli == 0) {
        mustausLaskuri = 1;
        ofSetColor(0, 0, 0, 15);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }

    {
        ofScopedLock lock(mutex);

        for (auto& pallo : pallot)
            pallo.draw();
    }
}

void itiot::uusiItio(int x, int y) {

    ofScopedLock lock(mutex);

    if (pallot.size() < PALLOT_MAX) {
        for (int i = 0; i < 5; i++) {
            pallot.push_back(pallo(ofPoint(x,y),25));
            // pallot.back().piirretaan = false;
        }
    }
}

std::vector<pallo> itiot::getPallot() {
    ofScopedLock lock(mutex);
    return pallot;
}
