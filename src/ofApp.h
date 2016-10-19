#pragma once

#include "ofMain.h"
#include "oneImage.h"
#include "ofxCv.h"
#include "ofxVectorField.h"
#include "Particle.h"
#include "ParticleCloud.h"
#include "ofxOpenCv.h"

#include "ofxOsc.h"
#include "sprinkle.h"
#include "donut_cop.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        // returns the next Index in the folder
        int nextIndex();
        int nextIndexReverse();
    
        int nxtIndex;
        int nxtIndexReverse;
    
        void createNewVectorField(ofPixels pix);
    
        // doing the threaded image loading 
        vector<unique_ptr<oneImage>> poolOfThreads;
        deque<int> indexOfThreads;
        //deque <ofxVectorField> fields;
        vector<unique_ptr<oneImage>> poolOfThreadsBottom;
        deque<int> indexOfThreadsBottom;
    
        ofDirectory topLayer;
        ofDirectory bottomLayer;
        int posX;
        int posXBottom;
    
    ofFbo drawInto;
    ofPixels tempPix;
    
    /*
    
    ofPixels tempPixInvert;
    
    ofVideoGrabber cam;
    ofxCv::ContourFinder contourFinder;
    
    ofxBox2d box2d;   // the box2d world
    vector   <shared_ptr<ofxBox2dCircle> > circles; // default box2d circles
    vector <shared_ptr<ofxBox2dEdge> >   edges;
    
    vector <ofPolyline> contourPoly;
     */
    
    ofxVectorField vectorFieldOne;
    ofxVectorField vectorFieldTwo;
    ofxVectorField vectorFieldThree;
    
    ofImage tempImg;
    
    ofShader shaderBlurX;
    ofShader shaderBlurY;
    ofShader alphaShade; 
    
    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;
    
    ofFbo finalImage;
    ofFbo drawLines;
    ofFbo flowRight; 
    
    ofPixels drawLinesTemp;
    ofxCvGrayscaleImage drawLinesCv;
    ofxCvColorImage drawLinesCvColor;
    
    vector <Particle> particles;
    
    
    vector <ParticleCloud> particlesClds;
    
    ofImage underneath;
    
    // donut stuff
    DonutCop donutCop;
    std::vector<Sprinkle> sprinkles;  // The vector of sprinkles
    
    void createSprinkles();
    void removeSprinkles();
    
    bool isUseMessages;
    
    int screenW;
    int screenH;
		
};
