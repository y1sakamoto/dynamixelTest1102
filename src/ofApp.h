#pragma once

#include "ofMain.h"

#include "dynamixelUnit.h"

#include "inverseKinetics.h"
#include "config.h"
#include "movePoint.h"


#include "ofxOscSubscriber.h"

#include "ofxAlembic.h"
#include "armUnit.h"

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
        dynamixelUnit unit;
        inverseKinetics k;
        ofEasyCam cam;
        float t0,t1,t2;
    
        movePoint mPoint;
        int mode;
        ofVec3f posFromOsc;
        int speedFromOsc;
        int accelFromOsc;
        ofxAlembic::Reader abc;
        vector<armUnit> arm;


};
