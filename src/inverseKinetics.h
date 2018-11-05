//
//  inverseK.h
//  dynamixelTest
//
//  Created by YouichiSakamoto on 2018/09/18.
//
//

#ifndef inverseK_h
#define inverseK_h
#include "ofMain.h"
#include "config.h"

class inverseKinetics{
    
public:
    
    inverseKinetics(){};
    inverseKinetics(const float _L0,const float _L1){
        L0=_L0;
        L1=_L1;
        
    };
    void setArmLength(const float _L0,const float _L1){
        L0=_L0;
        L1=_L1;
    };
    void setPosition(ofVec3f _p){
        pos=_p;
        const float L=getLxz(_p.x,_p.z);
        theta0=getTheta0 (_p.x,_p.z);
        theta2=getTheta2 (L,_p.y);
        theta1=getTheta1 (L,_p.y);

    };
    
    const float getTheta0(){return theta0;};
    const float getTheta1(){return theta1;};
    const float getTheta2(){return theta2;};
    const int getRadToInt(const double _theta,const int _min,const int _max,const bool _inverse){
        double _s=((_theta+PI)/(PI*2))*ROTATION_VALUE_MAX;
        if(_s>_max)_s=_max;
        else if(_s<_min)_s=_min;
        
        if(_inverse)_s=ROTATION_VALUE_MAX-_s;
        
        return (int)_s;
        
    };

private:
    float L0;
    float L1;
    float theta0;

    float theta1;
    float theta2;

    ofVec3f pos;
    
    const float getTheta0(const double _x,const double _z){
        const double _theta0= atan2(_x,_z);
        return _theta0;
        
    };

    

    const float getTheta1(const double _x,const double _y){
        const double s0=pow(_x,2)+pow(_y,2)-pow(L0,2)-pow(L1,2);
        const double s1=pow(s0,2);
        const double s2=pow(L0,2)*pow(L1,2);
        
        const double s=L1*sqrt(4-s1/s2);
        const double t=2*(L0+   s0 /    (2*L0));
        //const double _theta1= atan2(_y,_x)-atan(s/t);//LEFT
        const double _theta1= atan2(_y,_x)+atan(s/t);

        return _theta1;
        


    };
    
    const double getTheta2(const double _x,const double _y){
        double s0=pow(_x,2)+pow(_y,2);
        double s1=pow(L0,2)+pow(L1,2);
        double t =2*L0*L1;
       // double _theta2=acos((s0-s1)/t);//LEFT
        double _theta2=-acos((s0-s1)/t);

        return _theta2;
        
        
    };

    
 
    
    
    



    const float getLxz(const double _x,const double _z){
        return ofDist(0, 0, _x, _z);
        
    };
    
    
};


#endif /* inverseK_h */
