//
//  dynamixelUnit.h
//  dynamixelTest
//
//  Created by YouichiSakamoto on 2018/09/12.
//
//

#ifndef dynamixelUnit_h
#define dynamixelUnit_h
#include "dynamixel_sdk.h"                                  // Uses Dynamixel SDK library
#include "ofMain.h"                                  // Uses Dynamixel SDK library



// Control table address
#define ADDR_PRO_TORQUE_ENABLE          562                 // Control table address is different in Dynamixel model
#define ADDR_PRO_GOAL_POSITION          596
#define ADDR_PRO_PRESENT_POSITION       611

// Protocol version
#define PROTOCOL_VERSION                2.0                 // See which protocol version is used in the Dynamixel

// Default setting
//#define DXL_ID                          1                   // Dynamixel ID: 1
#define BAUDRATE                        57600
#define DEVICENAME                      "/dev/tty.usbserial-E160"
//#define DEVICENAME                      "/dev/ttyUSB0"      // Check which port is being used on your controller
// ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque


#define ESC_ASCII_VALUE                 0x1b

#define READ_MAX_POSITION_LIMIT 48
#define READ_MIN_POSITION_LIMIT 52
#define READ_PRESENT_POSITION 132
#define WRITE_TORQUE_ENABLE 64
#define WRITE_GOAL_POSITION 116
#define WRITE_PROFILE_ACCERATION 108
#define WRITE_PROFILE_VELOCITY 112



#include "config.h"

class dynamixelUnit{
public:
    
    dynamixelUnit(){};
    ~dynamixelUnit(){};

    
    void openPort(){
        openPort(DEVICENAME,BAUDRATE,PROTOCOL_VERSION);
    };
    void initDynamyxel(const int _id);
    void initDynamyxel(const int _id,int _speed,int _accel);

    void goPosition(const int _id,const int _pos){
        uint8_t dxl_error = 0;
        packetHandler->write4ByteTxRx(portHandler, _id, WRITE_GOAL_POSITION, _pos, &dxl_error);
    }
    
    void setAccelation(const int _id,const int _accel);
    void setVelosity(const int _id,const int _speed);

    
    inline void closePort(){portHandler->closePort();};

 

    
private:
    dynamixel::PortHandler *portHandler;
    dynamixel::PacketHandler *packetHandler;
    
    void openPort(const char *deviceName,int baourate,int protcolVersion);
    void getInitialValue(const int _id);


    
    
    
    
};


#endif /* dynamixelUnit_h */



/*
 void goPosition(const int _pos){
 uint8_t dxl_error = 0;
 packetHandler->write4ByteTxRx(portHandler, DXL_ID, WRITE_GOAL_POSITION, _pos, &dxl_error);
 }*/



/*void setup(){
 
 getInitialValue();
 uint8_t dxl_error = 0;
 
 packetHandler->write4ByteTxRx(portHandler, DXL_ID, WRITE_PROFILE_ACCERATION, 1000, &dxl_error);
 packetHandler->write1ByteTxRx(portHandler, DXL_ID, WRITE_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
 
 goPosition(1000);
 
 
 };*/

