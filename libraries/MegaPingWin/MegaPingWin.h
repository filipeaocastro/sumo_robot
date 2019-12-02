/*
    Created by Filipe Augusto
    Github: /filipeaocastro
*/

#ifndef SumoRobot_h
#define SumoRobot_h

#include "Arduino.h"

class SumoRobot{

    public:

        SumoRobot(uint8_t INA, uint8_t IN1, uint8_t IN2, uint8_t IN3, uint8_t IN4, uint8_t INB, 
        uint8_t dist_sensor, uint8_t tssop_right, uint8_t tssop_left, uint8_t border_right, 
        uint8_t border_left);

        void goAhead(uint8_t speed, char wheel);
        void goBack(uint8_t speed, char wheel);
        void curve(uint8_t speed, uint8_t level, char direction);
        int readTSSOP(char side);
        int readBorder();
        int defineInitButton(int pin);
        int readFrontSensors();
        int readDistance();

        int setBorderTH(int threshold);
        


    private:

        uint8_t = _INA, _IN1, _IN2, _IN3, _IN4, _INB, _dist_sensor, _tssop_right, _tssop_left,
        _border_right, _border_left;


        int percentToPWM(uint8_t val);

};

#endif