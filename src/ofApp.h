#pragma once

#include "ofMain.h"
#include "ofxIntersection2D.hpp"
#include "Circle.h"

#define NUM_BANDS 8

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    

    
        ofxIntersection2D::BaseIntersection *intersection;
    
        int total;
        vector<ofVec2f> baseCircleCentralPosList;
        vector<float> baseCircleRadList;
        vector<ofVec2f> circleCentralPosList;
        vector<float> circleRadList;
    
    ofSoundPlayer myTrack;
    float *spectrum;
    int counter1, counter2;
    bool counting1, counting2;
    bool timerRunning;
    int timerCounter;
    int timerMax;

    
		
};