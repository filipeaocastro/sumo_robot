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
        uint8_t dist_sensor, uint8_t tssop_dir, uint8_t tssop_esq, uint8_t border_dir, 
        uint8_t border_esq);

        INA, IN1, IN2, IN3, IN4, INB, dist_sensor, tssop_dir, tssop_esq, linha_dir, linha_esq

        void goAhead(uint8_t velocidade, char lado);
        void goBack(uint8_t velocidade, char lado);
        void curve(uint8_t velocidade, uint8_t freio, char lado);
        int readTSSOP(char lado);
        int readBorder();
        int defineInitBotton(int _pin);
        int readFrontSensors();
        int readDistance();

        int setBorderTH(int _threshold);
        


    private:

        uint8_t = _INA, _IN1, _IN2, _IN3, _IN4, _INB, _dist_sensor, _tssop_dir, _tssop_esq,
        _border_dir, _border_esq;


        int percentToPWM(uint8_t val);

};

#endif