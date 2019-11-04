/*
    Created by Filipe Augusto
    Github: /filipeaocastro
*/

#ifndef MegaPingWin_h
#define MegaPingWin_h

#include "Arduino.h"

class MegaPingWin{

    public:

        MegaPingWin(uint8_t INA, uint8_t IN1, uint8_t IN2, uint8_t IN3, uint8_t IN4, uint8_t INB, 
        uint8_t dist_sensor, uint8_t tssop_dir, uint8_t tssop_esq, uint8_t linha_dir, 
        uint8_t linha_esq);

        void praFrente(uint8_t velocidade, char lado);
        void praTras(uint8_t velocidade, char lado);
        void curva(uint8_t velocidade, uint8_t freio, char lado);
        int lerTSSOP(char lado);
        int lerLinha();
        int defineBotInicio(int _pino);

        int setLimiarLinha(int _limiar);
        


    private:

        uint8_t = _INA, _IN1, _IN2, _IN3, _IN4, _INB, _dist_sensor, _tssop_dir, _tssop_esq,
        _linha_dir, _linha_esq;


        int percentToPWM(uint8_t val);

};

#endif