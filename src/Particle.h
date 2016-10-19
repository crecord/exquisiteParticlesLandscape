//
//  particle.hpp
//  vectorField
//
//  Created by Caroline Record on 10/2/16.
//
//

#pragma once

#include "ofMain.h"
#include "sprinkle.h"

class Particle {
public:
    
    Particle();
    Particle(const ofxOscMessage &m);
    
    void setup(ofVec2f startPos);
    void move(ofVec2f dir);
    void draw();
    void stayOnScreen();
    bool isOffScreen();
    bool isDead();
    bool isDie;
    float limitVel(float vel,float limit);
    float matchVel(float vel,float desiredVel);
    
    ofVec2f pos;
    int duration;
    
    ofPolyline poly;
    vector<ofPoint> tempVerts;
    
    bool isFadeTime;
    bool isAddNew;
    int greyCount;
    
    int velocity;
    
    bool isPass;
    
    int sprinkleId; 
    
    Sprinkle sprink; 

    int screenW;
    int screenH;
    float maxY;
    
    int randomSeedX;
    int randomSeedY;
    
};