//
//  armUnit.h
//  dynamixelTest1016
//
//  Created by YouichiSakamoto on 2018/10/23.
//
//

#ifndef armUnit_h
#define armUnit_h

#include "dynamixelUnit.h"
#include "config.h"
#include "inverseKinetics.h"


class armUnit{
public:
    armUnit(dynamixelUnit *_unit,const int motorNum0,const int motorNum1,const int motorNum2){
        unit=_unit;
        joint[0]=motorNum0;
        joint[1]=motorNum1;
        joint[2]=motorNum2;
        
        initArmUnit();
        k.setArmLength(LENGTH_0,LENGTH_1);
        setVelosity(DINAMIXEL_SPEED);
        setAccelation(DINAMIXEL_ACCEL);
    };
    armUnit(){};
    ~armUnit(){};
    
    void initArmUnit(){
        unit->initDynamyxel(joint[0]);
        unit->initDynamyxel(joint[1]);
        unit->initDynamyxel(joint[2]);
        
        

    };
    
    
    void initArmUnit(const int _spd,const int _accel){
        unit->initDynamyxel(joint[0],_spd,_accel);
        unit->initDynamyxel(joint[1],_spd,_accel);
        unit->initDynamyxel(joint[2],_spd,_accel);

    };
    void setOffSetPos(const ofVec3f _offset){
        offset=_offset;
    };
    
    void setVelosity(const int _spd){
        unit->setVelosity(joint[0], _spd);
        unit->setVelosity(joint[1], _spd);
        unit->setVelosity(joint[2], _spd);
    };
    void setAccelation(const int _accel){
        unit->setAccelation(joint[0], _accel);
        unit->setAccelation(joint[1], _accel);
        unit->setAccelation(joint[2], _accel);

        
    };
    
    void goPosition(ofVec3f _pos){
        targetPos=_pos-offset;
        k.setPosition(targetPos);
        theta[0]=k.getTheta0();
        theta[1]=k.getTheta1();
        theta[2]=k.getTheta2();
       // cout<<k.getTheta1()<<endl;

        
        int i0=k.getRadToInt(-theta[0],0,ROTATION_VALUE_MAX,1);
        int i1=k.getRadToInt(theta[1]-PI/2,1024,3071,1);
        int i2=k.getRadToInt(-theta[2]-theta[1]-PI/2,400,3583,1);
        
        unit->goPosition(joint[0],i0);
        unit->goPosition(joint[1],i1);
        unit->goPosition(joint[2],i2);

    };
    
    void draw(){
        ofVec3f p0(0,0,0);
        ofVec3f p1;
        ofVec3f p2;
        ofPushMatrix();
        ofTranslate(offset);
        ofDrawSphere(targetPos, 5);

        ofRotate(ofRadToDeg(theta[0]-PI/2), 0, 1, 0);
        ofNoFill();
        ofDrawBox(0, 0, 0, 20, 20, 20);
        ofFill();
        
        //cout<<t0<<endl;
        p1.x=LENGTH_0*cos(theta[1])+p0.x;
        p1.y=LENGTH_0*sin(theta[1])+p0.y;
        
        p2.x=LENGTH_1*cos(theta[1]+theta[2])+p1.x;
        p2.y=LENGTH_1*sin(theta[1]+theta[2])+p1.y;
        ofDrawLine(p0, p1);
        ofDrawLine(p1, p2);

        ofPopMatrix();
  
    
    
    };
private:
    int joint[3];
    ofVec3f offset;
    dynamixelUnit *unit;
    inverseKinetics k;
    float theta[3];
    ofVec3f targetPos;
    
    
    
    
    
};



#endif /* armUnit_h */
