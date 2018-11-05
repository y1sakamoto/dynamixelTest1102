//
//  movePoint.h
//  dynamixelTest
//
//  Created by YouichiSakamoto on 2018/09/25.
//
//

#ifndef movePoint_h
#define movePoint_h

class movePoint{
public:
    movePoint(){counter=0;};
    
    void update(){
        counter+=0.2;
        pos.x=cos(counter*1.00)*30-100;
        pos.y=cos(counter*1.07)*30+300;
        pos.z=sin(counter*1.00)*30-100;
    };
    void draw(){ofDrawSphere(pos,5);};
    ofVec3f getPos(){return pos;};
private:
    float counter;
    ofVec3f pos;
    
    
};



#endif /* movePoint_h */
