#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    donutCop.setId(9);
    
    isUseMessages = true;
    
    ofSetFullscreen(true);
    
    screenW = 1080;
    screenH = 1920;
    
    shaderBlurX.load("shadersGL3/shaderBlurX");
    shaderBlurY.load("shadersGL3/shaderBlurY");
    alphaShade.load("alphaShader/shader");
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    bottomLayer.listDir("bottom/");
    bottomLayer.sort();
    
    topLayer.listDir("top/");
    topLayer.sort();
    //ofLog()<< topLayer.size();
    
    posX = 0;
    nxtIndex =0;
    nxtIndexReverse =0;
    
    ofImage testSz;
    if(topLayer.size()){
        testSz.load(topLayer.getPath(0));
    }
    
    posXBottom = (screenH * 2 - screenW) *-1;
    
    for(int i =0; i < 3; i++){
        //testQ.push_back(move(shared_ptr<oneImage>(new oneImage)));
        poolOfThreads.push_back(move(unique_ptr<oneImage>(new oneImage)));
        poolOfThreadsBottom.push_back(move(unique_ptr<oneImage>(new oneImage)));
        //ofLog() << topLayer.getPath(i);
        poolOfThreads.back()->setup(topLayer.getPath(i));
        
        poolOfThreadsBottom.back()->setup(bottomLayer.getPath(nxtIndexReverse));
        nextIndexReverse();
        ////ofLog()<<"next file to load: " << nextFileToLoad;
        indexOfThreads.push_back(i);
        indexOfThreadsBottom.push_back(i);
        nxtIndex ++;
        
        //fields.push_back(temp);
    }
    
    fboBlurOnePass.allocate(screenW, screenH, GL_RGB);
    fboBlurTwoPass.allocate(screenW, screenH, GL_RGB);
    drawInto.allocate(screenW, screenH, GL_RGB);
    drawInto.begin();
    ofClear(0,0,0);
    drawInto.end();
    tempPix.allocate(screenW,screenH,OF_PIXELS_RGB);
    
    drawLines.allocate(screenW, screenH, GL_RGB);
    drawLines.begin();
    ofClear(0,0,0);
    drawLines.end();
    finalImage.allocate(screenW, screenH);
    finalImage.begin();
    ofClear(0,0,0,255);
    finalImage.end();
    flowRight.allocate(screenW, screenH);
    flowRight.begin();
    ofClear(0,0,0);
    flowRight.end();
    
    drawLinesTemp.allocate(screenW,screenH,OF_PIXELS_RGB);
    drawLinesCv.allocate(screenW,screenH);
    drawLinesCvColor.allocate(screenW,screenH);
    vectorFieldTwo.setup(screenW,screenH, 5);
    
    underneath.load("one.jpg");
    
    
}

int ofApp::nextIndexReverse(){
    if(nxtIndexReverse > 0){
        nxtIndexReverse --;
    }
    else{
        nxtIndexReverse = bottomLayer.size()-1;
    }
}


int ofApp::nextIndex(){
    if(nxtIndex < topLayer.size()-1){
        nxtIndex ++;
    }
    else{
        nxtIndex = 0;
    }
}

void ofApp::createNewVectorField(ofPixels pix){

    // create the vector field from an image
    
    vectorFieldTwo.setFromImage(pix);
    
    // adjust the vector field by normalizing, scaling, biasing & blurring (to make it look nice)
    vectorFieldTwo.normalize();
    vectorFieldTwo.scale(5);
    vectorFieldTwo.bias(1.2, 0);
    vectorFieldTwo.blur();
    
    
  
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(isUseMessages){
        donutCop.update(sprinkles.size());
        
        /*
        for (auto& p : sprinkles) {
            p.update(donutCop.maxVelocity(),donutCop.maxAcceleration());
        }*/
        
        // don't update because I am only dealing with them as they leave and come back
        /*
        // Update the sprinkle system
        for (auto& p : sprinkles) {
            //p.update();
        }*/ 
        // add new sprinkles from messages
        
        while (donutCop.hasNewSprinkles()) {
            Sprinkle newSprinkle = donutCop.getSprinkle();
            if(particlesClds.size() + particles.size() < 200){
            //Sprinkle tempSprink = donutCop.getSprinkle();
            if(newSprinkle.xVel > 0){
                // it is coming from the left and you should add a river
                Particle newParticle(newSprinkle.message);
                //ofVec2f pos(1, ofRandom( screenH));
                //newParticle.setup(pos);
               // newParticle.sprinkleId = sprinkles.size()-1;
                particles.push_back(newParticle);
            }
            else{
                // it is coming from the right and you should add a cloud
                ParticleCloud nParticle(newSprinkle.message);
                particlesClds.push_back(nParticle);
            }
            }
        }
        
        //createSprinkles();
        //removeSprinkles();
    }
    else{
    // auto generation mode
    
    if( ofGetFrameNum() % 10 == 0 && particles.size() < 300 ){
        
        Particle newParticle;
        particles.push_back(newParticle);
    }
    
    
    if( ofGetFrameNum() % 10 == 0 && particlesClds.size() < 300 ){
        ofLog()<< particlesClds.size();
        ParticleCloud nParticle;
        particlesClds.push_back(nParticle);
    }
    }
    
    
    for( int i=0; i<particles.size(); i++){
        
        /*
        particles[i].move(vectorFieldTwo.getVectorInterpolated(particles[i].sprink.x*screenW, particles[i].sprink.y*screenW, screenW, screenH));
         */
        particles[i].move(ofVec2f(1,1));
        particles[i].stayOnScreen();
    }
    
    for(int i = 0; i<particles.size(); i++){
        if(particles[i].isDie){
            if(isUseMessages){
                if(particles[i].isPass){
                    donutCop.broadcastSprinkle(particles[i].sprink);
                }
            }
            particles.erase(particles.begin() + i);
        }
    }
    
    for( int i=0; i<particlesClds.size(); i++){
        
        particlesClds[i].move();
        particlesClds[i].stayOnScreen();
        
    }
    
    for(int i = 0; i<particlesClds.size(); i++){
        if(particlesClds[i].isDie){
            
            if(isUseMessages){
                if(particlesClds[i].isPass){
                    donutCop.broadcastSprinkle(particlesClds[i].sprink);
                }
                //sprinkles.erase(sprinkles.begin() + particlesClds[i].sprinkleId);
            }
            particlesClds.erase(particlesClds.begin() + i);
        }
    }
    
    
    
    

    for (int i=0; i < poolOfThreads.size(); i++){
        poolOfThreads.at(i)->update();
        poolOfThreadsBottom.at(i)->update();

    }
    
    posX -= 1;
    posXBottom += 5;
    
    if(posXBottom + 2*screenH > screenW){
        posXBottom -= screenH;
        int indexOnTheMove = indexOfThreadsBottom.back();
        if(poolOfThreadsBottom.at(indexOnTheMove)->isLoaded){
            indexOfThreadsBottom.pop_back();
            indexOfThreadsBottom.push_front(indexOnTheMove);
            poolOfThreadsBottom.at(indexOnTheMove)->setup(bottomLayer.getPath(nxtIndexReverse));
            nextIndexReverse();
        }
    }
    
    if(posX < screenH*-1){
        
        posX += screenH;
        int indexOnTheMove = indexOfThreads.front();
        if(poolOfThreads.at(indexOnTheMove)->isLoaded){
        
            indexOfThreads.pop_front();
            
            indexOfThreads.push_back(indexOnTheMove);
            
            //ofLog()<< topLayer.getPath(nxtIndex);
            poolOfThreads.at(indexOnTheMove)->setup(topLayer.getPath(nxtIndex));
            nextIndex();
        }
    }
        /*
        
        fboBlurTwoPass.readToPixels(tempPix);
        createNewVectorField(tempPix);
         */


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0,0,0);
    ofDrawEllipse(50,50,100,100);
    
    float blur = ofMap(ofNoise(ofGetElapsedTimef()), 0, 1, 0, 10, true);

    
    ofSetColor(255);
    
    
    
    
    drawInto.begin();
    for(int i=0; i < indexOfThreads.size(); i++){
        int tempIndex = indexOfThreads.at(i);
        //ofLog() << " index: " << ofToString(i) << "value: " <<ofToString(tempIndex);
        poolOfThreads.at(tempIndex)->draw(posX + (i * screenH), 0, screenH, screenH);
    }
    drawInto.end();
    
    flowRight.begin();
    ofClear(0,0,0);
    for(int i=0; i < indexOfThreadsBottom.size(); i++){
        int tempIndex = indexOfThreadsBottom.at(i);
        //ofLog() << " index: " << ofToString(i) << "value: " <<ofToString(tempIndex);
        poolOfThreadsBottom.at(tempIndex)->draw(posXBottom + (i * screenH), 0, screenH, screenH);
    }
    flowRight.end();
    
    
    fboBlurOnePass.begin();
    
    shaderBlurX.begin();
    shaderBlurX.setUniform1f("blurAmnt", blur);
    
    drawInto.draw(0,0);
    
    shaderBlurX.end();
    
    fboBlurOnePass.end();
    
    //----------------------------------------------------------
    fboBlurTwoPass.begin();
    
    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnt", blur);
    
    fboBlurOnePass.draw(0, 0);
    
    shaderBlurY.end();
    
    fboBlurTwoPass.end();
    
    //fboBlurTwoPass.draw(0, 0);
    drawInto.draw(0,0);
    
    
    drawLines.begin();
    ofClear(0,0,0);
    for( int i=0; i<particles.size(); i++){
        particles[i].draw();
    }
    drawLines.end();
    
    drawLines.readToPixels(drawLinesTemp);
    drawLinesCvColor.setFromPixels(drawLinesTemp);
    drawLinesCv = drawLinesCvColor;
    drawLinesCv.dilate_3x3();
    drawLinesCv.dilate_3x3();
    drawLinesCv.dilate_3x3();
    //drawLinesCv.dilate_3x3();
    //drawLinesCv.dilate_3x3();
    drawLinesCv.blur();
    drawLinesCv.blur();
    //drawLinesCv.erode_3x3();
    drawLinesCv.blur();
    drawLinesCv.invert();
    
    //drawLinesCv.dilate_3x3();
    drawLinesCv.draw(0, 0, screenW, screenH);
    ofClear(0, 0, 0, 0);
    finalImage.begin();
        alphaShade.begin();
            alphaShade.setUniformTexture("maskTex", drawLinesCv.getTexture(), 1 );
            drawInto.draw(0,0);
        alphaShade.end();
    finalImage.end();
    flowRight.draw(0,0);
    finalImage.draw(0,0);
    
    for( int i=0; i<particlesClds.size(); i++){
        particlesClds[i].draw();
    }
    //underneath.draw(0,0, screenH, screenH);
    //flowRight.draw(0,0);
    //vectorFieldTwo.draw();
    
    //for (auto& p : sprinkles) { p.draw();}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    if(key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::createSprinkles() {
    /*
    // Check with the donut cop if you're allowed to create a new sprinkle
    if (donutCop.allowedToCreateSprinkle(sprinkles.size())) {
        
        // Create a new sprinkle
        Sprinkle p(donutCop.maxVelocity(), donutCop.maxAcceleration());
        
        // Add it to the sprinkles list
        sprinkles.push_back(p);
        
        // Tell the cop that we created one, so it can keep track
        // of how many have been created.
        donutCop.mentionNewSprinkle();
    }
     */
}

//--------------------------------------------------------------
void ofApp::removeSprinkles() {
    
    // Loop through and broadcast offscreen sprinkles
    for (auto& p : sprinkles) {
        if (p.isOffScreen()){
            donutCop.broadcastSprinkle(p);
        }
    }
    
    // Loop through and remove offscreen sprinkles
    sprinkles.erase(
                    remove_if(sprinkles.begin(), sprinkles.end(), [](Sprinkle p) { return p.isOffScreen();}),
                    sprinkles.end());
}
