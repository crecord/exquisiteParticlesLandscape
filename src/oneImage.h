//
//  oneImage.hpp
//  FunWithFiles
//
//  Created by Caroline Record on 8/19/16.
//
//

#include "ofMain.h"
//#include "ofxVectorField.h"

class oneImage: public ofThread{
public:
    
    oneImage(){
       // ofLog()<< "calling empty constructor";
    }

/*
    ~oneImage(){
        ofLog()<<"the destructor is being called";
        stopThread();
        img.clear();
        image.clear();
        //filePath.clear();

    };
    */

    bool closeThread();
    
    //ofxThreadedImageLoader loader;
    
    //ofxThreadedImageLoader* loadTwo;
    void setup(string fPath);
    void threadedFunction();
    void draw(int x, int y, int wid, int hi);
    void update();
    // recursive image load for images that are forming themselves.
    void reImageLoad();

    void destroyEverything();
    
    ofImage getImage(); 
    
    string filePath;
    ofPixels img;
    ofPixels tempPix;

    ofImage image;
    
    bool isLoading;
    bool isLoaded;
    bool isFlowField;
    
    /*
    int startDay;
    int endDay;
*/

   // ofxVectorField vectorField;
    
private:
    
    int startTime; 
};
