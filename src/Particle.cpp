//
//  particle.cpp
//  vectorField
//
//  Created by Caroline Record on 10/2/16.
//
//

#include "Particle.h"


Particle::Particle() : sprink(false){
    poly.clear();
    duration = 0;
    isDie = false;
    isPass = false;
    
    isFadeTime = false;
    greyCount = 255;
    velocity = int(ofRandom(2,9));
    
    screenW = 1080;
    screenH = 1920;
    maxY = screenH / float(screenW);
    
    randomSeedX = ofRandom(1000);
    randomSeedY = ofRandom(1000);
    
}


Particle::Particle(const ofxOscMessage &m) : sprink(m){
    poly.clear();
    duration = 0;
    isDie = false;
    isPass = false;
    
    isFadeTime = false;
    greyCount = 255;
    velocity = int(ofRandom(2,9));
    
    screenW = 1080;
    screenH = 1920;
    maxY = screenH / float(screenW);
    
    randomSeedX = ofRandom(1000);
    randomSeedY = ofRandom(1000);
}



void Particle::setup(ofVec2f startPos){
    poly.clear();
    pos = startPos;
    duration = 0;
    isDie = false;
    isPass = false;
    
    isFadeTime = false;
    greyCount = 255;
    velocity = int(ofRandom(2,9));
    
    randomSeedX = ofRandom(1000);
    randomSeedY = ofRandom(1000);
}

void Particle::move(ofVec2f dir){
    
    //old way: 
    //pos += velocity * dir ;
    bool isPerlin = true;
    if(isPerlin){
         dir.x = ofMap(ofNoise(randomSeedY, ofGetElapsedTimef()),0,1,.5,1);
         dir.y = ofMap(ofNoise(randomSeedY, ofGetElapsedTimef()),0,1,-1,1);
    }
    
    float directionScale = .01;
    float desiredAcc = matchVel(sprink.xVel, dir.x*directionScale);
    sprink.xAcc = desiredAcc;
    desiredAcc = matchVel(sprink.yVel, dir.y*directionScale);
    sprink.yAcc = desiredAcc;
    
    sprink.update(.05, .005);
    
}


float Particle::limitVel(float vel, float limit){
    
    //float newDirX = ofMap(ofNoise(randomSeedX, ofGetElapsedTimef()),0,1,.5,2);
    float desiredVel = limit - abs(vel);
    float desiredAcc = 0;
    if(desiredVel < 0){
        desiredAcc = 1 * vel / 2.0;
    }
    return desiredAcc;
}


float Particle::matchVel(float vel, float velDesired){
    //float newDirX = ofMap(ofNoise(randomSeedX, ofGetElapsedTimef()),0,1,.5,2);
    float desiredAcc = velDesired - vel;
    desiredAcc *= .5;
    return desiredAcc;
}

void Particle::draw(){
    ofSetLineWidth(10);
    if (isFadeTime){
        greyCount -= 12;
        if(greyCount < 1){
            if (isAddNew){
                //setup(ofVec2f(ofRandom(50, ofGetWidth() -50), ofRandom(50, ofGetWidth() -50)));
                Particle();
            }
            else{
                isDie = true;
                poly.clear();
                tempVerts.clear();
            }
            
        }
    }
    ofSetColor(greyCount);

    
    for(int i=0; i < poly.size(); i++){
        poly[i].x -= 1;
        if(poly[i].x < 0){
            poly.getVertices().erase(poly.getVertices().begin() + i);
            poly.flagHasChanged();
        }

    }

   poly.curveTo(sprink.x * screenW, sprink.y * screenW);
   poly.flagHasChanged();

    poly.draw();
    duration ++;
}

void Particle::stayOnScreen(){
    if( sprink.x < 0 ){
        isFadeTime = true;
        isAddNew = true;
        isPass = false;
    }
    if( sprink.x > 1.0){
        isFadeTime = true;
        isAddNew = false;
        isPass = true;
    }
    if( sprink.y< 0 ){
        //isDie = true;
        isFadeTime = true;
        isAddNew = true;
        isPass = false;
        poly.clear();
        tempVerts.clear();
    }
    if( sprink.y >= maxY ){
        //isDie = true;
        isAddNew = true;
        isPass = false;
        isFadeTime = true;
        poly.clear();
        tempVerts.clear();
    }
    
    
}


