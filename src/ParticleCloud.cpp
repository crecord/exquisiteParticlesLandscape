//
//  particle.cpp
//  vectorField
//
//  Created by Caroline Record on 10/2/16.
//
//

#include "ParticleCloud.h"

ParticleCloud::ParticleCloud() : sprink(true){
    //sprink = _sprink;
    /*
    accel = startAcceleration;
    vel = startVelocity;
    pos = startPos;
     */
    duration = 0;
    isDie = false;
    isPass = false;
    randomSeedX = ofRandom(1000);
    randomSeedY = ofRandom(1000);
    
    blur.load("brush1.png");
    blur.setAnchorPercent(0.5,0.5);
    size = int(ofRandom(75,210));
    
    screenW = 1080;
    screenH = 1920;
    maxY = screenH / float(screenW);
}


ParticleCloud::ParticleCloud(const ofxOscMessage &m) : sprink(m){
    //sprink = _sprink;
    /*
     accel = startAcceleration;
     vel = startVelocity;
     pos = startPos;
     */
    
    duration = 0;
    isDie = false;
    isPass = false;
    randomSeedX = ofRandom(1000);
    randomSeedY = ofRandom(1000);
    
    blur.load("brush1.png");
    blur.setAnchorPercent(0.5,0.5);
    size = int(ofRandom(75,210));
    
    screenW = 1080;
    screenH = 1920;
    maxY = screenH / float(screenW);
}


/*
void ParticleCloud::setup(){
    screenW = ofGetWidth();
    screenH = ofGetHeight();
    maxY = screenH / float(screenW);
    //pos.x = ofGetWidth();
    //pos.y = ofRandom(ofRandom(ofGetHeight()));
    pos.x = 1.0;
    pos.y= ofRandom(maxY);
    duration = 0;
    isDie = false;
    isPass = false;
    
    vel.x = ofRandom(-0.001,-0.01);
    vel.y = ofRandom(-0.01,0.01);
    
    accel.x = ofRandom(-0.001,0.001);
    accel.y = ofRandom(-0.001,0.001);
    
    randomSeedX = ofRandom(1000);
    randomSeedY = ofRandom(1000);
    
    blur.load("brush1.png");
    blur.setAnchorPercent(0.5,0.5);
    size = int(ofRandom(75,210));
}
*/

float ParticleCloud::limitVel(float vel,float limit){
    
    //float newDirX = ofMap(ofNoise(randomSeedX, ofGetElapsedTimef()),0,1,.5,2);
    float desiredVel = limit - abs(vel);
    float desiredAcc = 0;
    if(desiredVel < 0){
        desiredAcc = -1 * vel / 2.0;
    }
    return desiredAcc;
}

void ParticleCloud::move(){
    float newDirY = ofMap(ofNoise(randomSeedY, ofGetElapsedTimef()),0,1,-0.003,.003);
    //sprink.yAcc = (sprink.yAcc + dir.y) /2.0;
    float desiredAcc = limitVel(sprink.yVel, .003);
    sprink.yAcc = newDirY + desiredAcc;
    desiredAcc = limitVel(sprink.xVel, .003);
    //sprink.xAcc = desiredAcc;
    //sprink.xAcc = (sprink.xAcc + dir.x) /2.0;
    sprink.update(.05, .005);
}

void ParticleCloud::draw(){
    blur.draw(sprink.x * screenW, sprink.y * screenW, size, size);
    /*
    ofSetColor(255);
    ofDrawEllipse(pos, 6, 6);
     */ 
}

void ParticleCloud::stayOnScreen(){
    
    float sz = size/float(screenW)/2;
    if(sprink.x < sz*-1){
        isPass =true;
        isDie = true;
        
    }
    if( sprink.x > 1 + sz){
        isDie = true;

    }
    if( sprink.y < sz*-1 ){
        sprink.y = maxY + sz;
    }
    if( sprink.y > maxY+ sz ){
        sprink.y = sz*-1;
        
    }
    
    
}

bool ParticleCloud::isOffScreen(){

}

bool ParticleCloud::isDead(){
    return duration >= 20000;
}
