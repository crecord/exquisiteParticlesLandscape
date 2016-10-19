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

class ParticleCloud {
public:
    
    
    ParticleCloud();
    ParticleCloud(const ofxOscMessage &m);
    
    float limitVel(float vel,float limit);
    void setup(); 
    void move();
    void draw();
    void stayOnScreen();
    bool isOffScreen();
    bool isDead();
    bool isDie;
    
    bool isPass;
    
    
    ofVec2f pos;
    int duration;
    
    ofPolyline poly;
    vector<ofPoint> tempVerts;
    
    bool isFadeTime;
    int greyCount;
    //int velocity;
    
    int randomSeedX;
    int randomSeedY;
    
    ofImage blur;
    
    int size;
    
    int sprinkleId;
    
    ofVec2f accel;
    ofVec2f vel;
    
    float maxY;
    int screenW;
    int screenH;
    
    Sprinkle sprink;
    
};