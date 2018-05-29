#include "ofApp.h"

//---------------------------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(100);
    ofBackground(0);
    myTrack.load("SlowLight(MapsRemix).mp3");
    myTrack.play();
    //myTrack.setPosition(0.075);
    counter1 = 0;
    counter2 = 0;
    counting1 = true;
    counting2 = true;
    
    //timer
    timerRunning = false;
    timerMax = 10;
    timerCounter = 0;
    
    intersection = new ofxIntersection2D::Circle2D();
    
    total = 80;
    for (int i = 0; i < total; i++) {
        baseCircleCentralPosList.push_back(ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));
        baseCircleRadList.push_back(ofRandom(50, 300));
        
        circleCentralPosList.push_back(baseCircleCentralPosList[i]);
        circleRadList.push_back(baseCircleRadList[i]);
    }
}

//-------------------------------------------------------------------------------
void ofApp::update() {
    
    // GET SOUND SPECTRUM DATA
    //-------------------------------------------------------------------------------
    spectrum=ofSoundGetSpectrum(NUM_BANDS);
    
    
    // (INTERSECTION) CLEAR
    //-------------------------------------------------------------------------------
    intersection->clear();
    
    
    // (INTERSECTION) ADD
    //-------------------------------------------------------------------------------
    ofVec2f v;
    float rad;
    
    for (int i = 0; i < total; i++) {
        v.x = cos((ofGetElapsedTimef() + 1.0 * i) * 1.0) * 40;
        v.y = sin((ofGetElapsedTimef() + 1.0 * i) * 1.0) * 40;
        circleCentralPosList[i] = baseCircleCentralPosList[i] + v;
        
        rad = cos((ofGetElapsedTimef() + 1.0 * i) * 1.0) * (circleRadList[i] * 0.1);
        circleRadList[i] = baseCircleRadList[i] + rad;
        
        intersection->addCircle(circleCentralPosList[i], circleRadList[i]);
    }
    
    
    // (INTERSECTION) UPDATE
    //--------------------------------------------------------------------------------
    intersection->update();
}



//--------------------------------------------------------------------------------
void ofApp::draw() {
    
    
    // GET INTERSECTION DATA
    //--------------------------------------------------------------------------
    vector<ofVec2f> tmpIntersectionList = intersection->getIntersections();
    
    
    // DRAW INTERSECTIONS
    //------------------------------------------------------------------------------
    int totalIntersection = intersection->getIntersectionTotal();
    
    //create array of circles
    Circle myCircles[totalIntersection];
    
    ofSetColor(255,50);
    ofFill();
    for (int i = 0; i < totalIntersection; i++) {
        ofDrawCircle(tmpIntersectionList[i], ofRandom(5,10));
    }
    
    // OUTER CIRLCES
    ofSetColor(255,60);
    ofNoFill();
    for (int i = 0; i < total; i++) {
        ofDrawCircle(circleCentralPosList[i], circleRadList[i]);
        
    }
    
    
    // VOICE
    //------------------------------------------------------------------------------
    int myBand=0;
    if(spectrum[myBand]*(myBand+1)>0.8){
        if(counting1){
            counter1++;
            cout << counter1 << endl;
            if(counter1 % 4 == 0) cout << "multiple" << endl;
            ofSetColor(255,75);
            ofFill();
            for (int i = 0; i < totalIntersection; i++) {
                ofDrawCircle(tmpIntersectionList[i], 10);
            }
        }
        counting1 = false;
        
    }else{
        counting1 = true;
    }
    
    
    // SNARE
    //------------------------------------------------------------------------------
    float trigger;
    (counter1<100 && counter1>61)? trigger = 0.2 : trigger = 0.9;
    if(spectrum[2]*(3)>trigger){
        if(counting2){
            counter2++;
            counting2 = false;
            //cout << "snare" << endl;
            if(counter2 % 2 == 0) cout << "2multiple2" << endl;
            timerRunning=true;
        }
    }else{
        counting2 = true;
    }
    //TIMER FOR TRIGGERED CIRCLES
    //for (int i = 0; i < totalIntersection; i++) {
    
    
    if(timerRunning){
        timerCounter++;
        
        //DRAW FOR A CERTAIN TIME (TIMERMAX)
        
        ofSetColor(255,25);
        ofNoFill();

        for (int i = 0; i < totalIntersection; i++) {
            ofDrawCircle(tmpIntersectionList[i], 25);
            ofDrawCircle(tmpIntersectionList[i], 20);
            ofDrawCircle(tmpIntersectionList[i], 15);
        }
        
        //END DRAW FOR A CERTAIN TIME (TIMERMAX)
        
        if(timerCounter==timerMax){
            timerCounter = 0;
            timerRunning=false;
        }
    }
}
