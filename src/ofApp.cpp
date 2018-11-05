#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    unit.openPort();
    {   armUnit _arm(&unit,1,2,3);
        arm.push_back(_arm);    }
    {   armUnit _arm(&unit,4,5,6);
        arm.push_back(_arm);    }
    /*{   armUnit _arm(&unit,7,8,9);
        arm.push_back(_arm);    }
    {   armUnit _arm(&unit,10,11,12);
        arm.push_back(_arm);    }
    */
    abc.open(ALENBIC_FILE_PATH);

    k.setArmLength(LENGTH_0,LENGTH_1);
    ofSetBackgroundColor(0);
    ofSetFrameRate(30);
    mode=MODE_USE_ALEMBIC;
    //mode=MODE_USE_MOVEPOOINT;
    ofxSubscribeOsc(PORT, "/pos", posFromOsc);
    ofxSubscribeOsc(PORT, "/speed", [=](int val){
        speedFromOsc=val;
        for (int i=0; i<arm.size(); i++) {
            arm[i].setVelosity(speedFromOsc);
        }


    });
    ofxSubscribeOsc(PORT, "/accel", [=](int val){
        accelFromOsc=val;
    for (int i=0; i<arm.size(); i++) {
        
            arm[i].setAccelation(accelFromOsc);
    }
    });

    ofVec3f pos[NUM_ARMS];
    ofMatrix4x4 mat;
    abc.get("/Sphere_01_Offset/Sphere_01", mat);
    pos[0]=mat.getTranslation()*10;
    abc.get("/Sphere_02", mat);
    pos[1]=mat.getTranslation()*10;

    
    posFromOsc.set(30,30,30);
    arm[0].setOffSetPos(ofVec3f(-140,250,150));
    arm[1].setOffSetPos(ofVec3f(-370,890,20));
    //arm[2].setOffSetPos(ofVec3f(-100,0,-200));
    //arm[3].setOffSetPos(ofVec3f(-100,0,200));

}

//--------------------------------------------------------------
void ofApp::update(){
    

    if(mode==MODE_USE_MOVEPOOINT){
            mPoint.update();
            ofVec3f pos=mPoint.getPos();
            arm[0].goPosition(pos);

    }else if(mode==MODE_USE_OSC){
            ofVec3f pos=posFromOsc;
            arm[0].goPosition(pos);

    }else if(mode==MODE_USE_ALEMBIC){
        
        float t = fmodf(ofGetElapsedTimef(), abc.getMaxTime());
        ofVec3f pos[NUM_ARMS];
        abc.setTime(t);
        
        ofMatrix4x4 mat;
        abc.get("/Sphere_01_Offset/Sphere_01", mat);
        pos[0]=mat.getTranslation()*10;
        abc.get("/Sphere_02_Offset/Sphere_02", mat);
        pos[1]=mat.getTranslation()*10;
        //cout<<pos[0]<<endl;
        arm[0].goPosition(pos[0]);
        arm[1].goPosition(pos[1]);

        /*
        for (int i=0; i<arm.size(); i++) {
            arm[i].goPosition(pos[i]);
        }
*/
        

    }
    
    
    
    
 
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();

    ofDrawGrid(100, 5, true, 0,1,0);
    for (int i=0; i<arm.size(); i++) {
        arm[i].draw();
        
    }
    
   // mPoint.draw();
    cam.end();
    
    string s="mode:";
    s+=ofToString(mode);
    //s+=ofToString("\nposFromOsc:");
    //s+=ofToString(posFromOsc);

    ofDrawBitmapString(s, 50, 50);



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='c')unit.closePort();
    if(key=='m'){
        
        mode=MODE_USE_MOVEPOOINT;
        for (int i=0; i<arm.size(); i++) arm[i].initArmUnit();

    }
    if(key=='o'){
        mode=MODE_USE_OSC;
        for (int i=0; i<arm.size(); i++) arm[i].initArmUnit(20,10);
        
    }
    
    if(key=='a'){
        mode=MODE_USE_ALEMBIC;
        for (int i=0; i<arm.size(); i++) arm[i].initArmUnit(DINAMIXEL_SPEED,DINAMIXEL_ACCEL);

        
    }

    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //unit.goPosition(x*2);
   //k.setPosition(ofVec3f(mouseX,abs( mouseY),mouseY));
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
