//
//  oneImage.cpp
//  FunWithFiles
//
//  Created by Caroline Record on 8/19/16.
//
//

#include "oneImage.h"

void oneImage::destroyEverything(){
    //ofLog()<<"the prestend destruction";
    stopThread();
    img.clear();
    image.clear();
    //this->~ofThread();
    //this->~oneImage();
    //pTp.clear();
    //pBttm.clear();
    filePath.clear();

}


void oneImage::setup(string fPath){
    //clean up from what was in here before
    stopThread();
    img.clear();
    image.clear();
    image.update();
    
    int screenW = 1080;
    int screenH = 1920;
    
    img.allocate(screenW,screenH,OF_PIXELS_RGB);
    tempPix.allocate(screenW,screenH,OF_PIXELS_RGB);
    
    filePath = fPath;
    startThread();
    isLoading = true;
    isLoaded = false;
    //vectorField.setup(2048,2048, 15);
    isFlowField = false; 
    
    
}


void oneImage::reImageLoad(){
    ofLoadImage(img, filePath);
    // is it less than ten seconds. Do not recurse longer than that.
    
    bool isTimeOut = (ofGetElapsedTimeMillis() - startTime) > 3000;
    if (!img.isAllocated() & !isTimeOut ){
        sleep(100);
        img.clear(); 
        reImageLoad();
    }
    
}


void oneImage::threadedFunction(){
    
    //startTime = ofGetElapsedTimeMillis();
    //reImageLoad();
    //ofLoadImage(img, filePath);
    ofLoadImage(img, filePath);

}

void oneImage::update(){
    if(!isThreadRunning() && isLoading){
        if(img.isAllocated()){
            
            image.setFromPixels(img);
            
            image.update();
            isLoading = false;
            isLoaded = true;
            img.clear();
            stopThread();
        }
    }

}

void oneImage::draw(int x, int y, int wid, int hi){
    
        if (isLoaded){
           // ofLog()<< img.getHeight();
           // tempPix =image.getPixels();
            image.draw(x,y,wid, hi);
        }
 
}

ofImage oneImage::getImage(){
    if (isLoaded){
        return image;
    }
    //return null;
}

bool oneImage::closeThread(){
   return isLoaded;

}
