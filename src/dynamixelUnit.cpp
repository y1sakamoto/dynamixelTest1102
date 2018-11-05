//
//  dynamixelUnit.cpp
//  dynamixelTest
//
//  Created by YouichiSakamoto on 2018/09/12.
//
//

#include "dynamixelUnit.h"
void dynamixelUnit::openPort(const char *deviceName,int baourate,int protcolVersion)
{
    portHandler= dynamixel::PortHandler::getPortHandler(deviceName);
    packetHandler = dynamixel::PacketHandler::getPacketHandler(protcolVersion);
    
    
    
    int dxl_comm_result = COMM_TX_FAIL;             // Communication result
    
    uint8_t dxl_error = 0;                          // Dynamixel error
    int32_t dxl_present_position = 0;               // Present position
    
    // Open port
    if (portHandler->openPort())
    {
        printf("Succeeded to open the port!\n");
    }
    else
    {
        printf("Failed to open the port!\n");
        return 0;
    }
    
    // Set port baudrate
    if (portHandler->setBaudRate(baourate))
    {
        printf("Succeeded to change the baudrate!\n");
    }
    else
    {
        printf("Failed to change the baudrate!\n");
        return 0;
    }

}


void dynamixelUnit::initDynamyxel(const int _id){
    uint8_t dxl_error = 0;
    packetHandler->write4ByteTxRx(portHandler, _id, WRITE_PROFILE_ACCERATION, 300, &dxl_error);
    packetHandler->write4ByteTxRx(portHandler, _id, WRITE_PROFILE_VELOCITY, 300, &dxl_error);

    packetHandler->write1ByteTxRx(portHandler, _id, WRITE_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
    //goPosition(_id,ROTATION_VALUE_HALF);

}


void dynamixelUnit::initDynamyxel(const int _id,int _speed,int _accel){
    uint8_t dxl_error = 0;
    packetHandler->write4ByteTxRx(portHandler, _id, WRITE_PROFILE_ACCERATION, _accel, &dxl_error);
    packetHandler->write4ByteTxRx(portHandler, _id, WRITE_PROFILE_VELOCITY, _speed, &dxl_error);
    
    packetHandler->write1ByteTxRx(portHandler, _id, WRITE_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
    
}

void dynamixelUnit::getInitialValue(const int _id){
    
    int32_t max_position = 0;
    int32_t min_position = 0;
    int32_t preset_position = 0;
    uint8_t dxl_error = 0;                          // Dynamixel error
    
    
    packetHandler->read4ByteTxRx(portHandler, _id, READ_MAX_POSITION_LIMIT, (uint32_t*)&max_position, &dxl_error);
    packetHandler->read4ByteTxRx(portHandler, _id, READ_MIN_POSITION_LIMIT, (uint32_t*)&min_position, &dxl_error);
    packetHandler->read4ByteTxRx(portHandler, _id, READ_PRESENT_POSITION, (uint32_t*)&preset_position, &dxl_error);
    cout<<"max_position:\t"<<max_position<<endl;
    cout<<"min_position:\t"<<min_position<<endl;
    cout<<"preset_position:\t"<<preset_position<<endl;

    
};


void dynamixelUnit::setAccelation(const int _id,const int _accel){
    uint8_t dxl_error = 0;
    packetHandler->write4ByteTxRx(portHandler, _id, WRITE_PROFILE_ACCERATION, _accel, &dxl_error);
    
};
void dynamixelUnit::setVelosity(const int _id,const int _speed){
    uint8_t dxl_error = 0;
    packetHandler->write4ByteTxRx(portHandler, _id, WRITE_PROFILE_VELOCITY, _speed, &dxl_error);

    
};







