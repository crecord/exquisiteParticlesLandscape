#include "sprinkle.h"



//--------------------------------------------------------------
// Generate the sprinkle with random parameters

Sprinkle::Sprinkle(float maxVel, float maxAcc) {
    
    screenW = 1080;
    screenH = 1920;
    
    maxY = float(screenH) / float(screenW);
    
    x = ofRandomuf();
    y = ofMap(ofRandomuf(),0.0,1.0,0.0,maxY);
    xVel = ofRandomf() * maxVel;
    yVel = ofRandomf() * maxVel;
    xAcc = ofRandomf() * maxAcc;
    yAcc = ofRandomf() * maxAcc;
    free1 = ofRandomuf();
    free2 = ofRandomuf();
    
    
}
//--------------------------------------------------------------
// Generate the sprinkle with random parameters
Sprinkle::Sprinkle(bool isCloud) {
    screenW = 1080;
    screenH = 1920;
    maxY = float(screenH) / float(screenW);
    if(isCloud) {
        float maxVel = 0.001;
        float maxAcc = 0.001;
        
        x = 1.0;
        y = ofMap(ofRandomuf(),0.0,1.0,0.0,maxY);
        xVel = ofRandom(0,-1) * maxVel;
        yVel = ofRandomf() * maxVel;
        xAcc = ofRandomf() * maxAcc;
        yAcc = ofRandomf() * maxAcc;
        free1 = ofRandomuf();
        free2 = ofRandomuf();
    }
    
    else{
        float maxVel = 0.001;
        float maxAcc = 0.001;
        x = 0.0;
        y = ofMap(ofRandomuf(),0.0,1.0,0.0,maxY);
        xVel = ofRandom(0,1) * maxVel;
        yVel = ofRandomf() * maxVel;
        xAcc = ofRandomf() * maxAcc;
        yAcc = ofRandomf() * maxAcc;
        free1 = ofRandomuf();
        free2 = ofRandomuf();
    }
    
}

//--------------------------------------------------------------
// Generate the sprinkle from an OSC message
Sprinkle::Sprinkle(const ofxOscMessage &m) {
        screenW = 1080;
        screenH = 1920;
        // Handle starting on the right
        message =m;
        maxY = float(screenH) / float(screenW);
        y = m.getArgAsFloat(0);
        xVel = m.getArgAsFloat(1);
        yVel = m.getArgAsFloat(2);
        xAcc = m.getArgAsFloat(3);
        yAcc = m.getArgAsFloat(4);
        free1 = m.getArgAsFloat(5);
        free2 = m.getArgAsFloat(6);
    
    if (xVel < 0 ) {
        x = 1.0;
    }
    else{
        x = 0;
    }
    
}

//--------------------------------------------------------------
void Sprinkle::update(float maxVel, float maxAcc) {
  
    /*
  // bounce off top and bottom
  if (y >= maxY || y <= 0.0) {
    yVel *= -1.0;
    yAcc *= -1.0;
  }
     */ 

  x += xVel;
  y += yVel;
  xVel += xAcc;
  yVel += yAcc;
  xVel = ofClamp(xVel,-maxVel, maxVel);
  yVel = ofClamp(yVel, -maxVel, maxVel);
  //xAcc = maxAcc*ofRandomf();
  //yAcc = maxAcc*ofRandomf();
}

//--------------------------------------------------------------
void Sprinkle::draw() {
  ofFill();
  ofSetColor(ofMap(free1,0.0,1.0,0,255));
  float xPos = ofMap(x,0.0, 1.0, 0.0, screenW);
  float yPos = ofMap(y,0.0, maxY, 0.0, screenH);
  ofDrawCircle(xPos,yPos,ofMap(free2,0.0,1.0,1,10));
}

//--------------------------------------------------------------
bool Sprinkle::isOffScreen() {
  return x > 1 || x < 0;
}

void Sprinkle::setVariables(float passY, float velX, float velY, float accX, float accY){
    y = passY;
    xVel = velX;
    yVel = velY;
    xAcc = accX;
    yAcc = accY; 
}

//--------------------------------------------------------------
ofxOscMessage Sprinkle::createOSCMessage() const {

  ofxOscMessage m;
  m.addFloatArg(y);
  m.addFloatArg(xVel);
  m.addFloatArg(yVel);
  m.addFloatArg(xAcc);
  m.addFloatArg(yAcc);
  m.addFloatArg(free1);
  m.addFloatArg(free2);
  return m;
}