/*
    Created by Filipe Augusto
*/

#include "Arduino.h"
#include "MegaPingWin.h"

MegaPingWin::MegaPingWin(uint8_t INA, uint8_t IN1, uint8_t IN2, uint8_t IN3, uint8_t IN4, uint8_t INB, 
        uint8_t dist_sensor, uint8_t tssop_dir, uint8_t tssop_esq, uint8_t linha_dir, 
        uint8_t linha_esq)
        {
            pinMode(INA, OUTPUT);
            pinMode(IN1, OUTPUT);
            pinMode(IN2, OUTPUT);
            pinMode(IN3, OUTPUT);
            pinMode(IN4, OUTPUT);
            pinMode(INB, OUTPUT);

            pinMode(dist_sensor, INPUT);
            pinMode(tssop_dir, INPUT);
            pinMode(tssop_esq, INPUT);
            pinMode(linha_dir, INPUT);
            pinMode(linha_esq, INPUT);


            _INA = INA;
            _IN1 = IN1;
            _IN2 = IN2;
            _IN3 = IN3;
            _IN4 = IN4;
            _INB = INB;

            _dist_sensor = dist_sensor;
            _tssop_dir = tssop_dir;
            _tssop_esq = tssop_esq;
            _linha_dir = linha_dir;
            _linha_esq = linha_esq;
        }

void MegaPingWin::praFrente(uint8_t velocidade, char lado)
{
    velocidade = percentToPWM(velocidade);

    if(lado == 'D')
    {
        // Velocidade
        analogWrite(_ENB, velocidade);

        // Motor direito
        digitalWrite(_IN3, HIGH);
        digitalWrite(_IN4, LOW); 
    }
    else if(lado == 'E')
    {
        // Velocidade
        analogWrite(_ENA, velocidade);
        
        // Motor esquerdo
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, HIGH);
    }
    else
    {
        // Velocidade
        analogWrite(_ENA, velocidade);
        analogWrite(_ENB, velocidade);
        
        // Motor esquerdo
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, HIGH);

        // Motor direito
        digitalWrite(_IN3, HIGH);
        digitalWrite(_IN4, LOW); 
    }
}

void MegaPingWin::praTras(uint8_t velocidade, char lado)
{
    velocidade = percentToPWM(velocidade);

    if(lado == 'D')
    {
        // Velocidade
        analogWrite(_ENB, velocidade);

        // Motor direito
        digitalWrite(_IN3, LOW);
        digitalWrite(_IN4, HIGH); 
    }
    else if(lado == 'E')
    {
        // Velocidade
        analogWrite(_ENA, velocidade);
        
        // Motor esquerdo
        digitalWrite(_IN1, HIGH);
        digitalWrite(_IN2, LOW);
    }
    else
    {
        // Velocidade
        analogWrite(_ENA, velocidade);
        analogWrite(_ENB, velocidade);
        
        // Motor esquerdo
        digitalWrite(_IN1, HIGH);
        digitalWrite(_IN2, LOW);

        // Motor direito
        digitalWrite(_IN3, LOW);
        digitalWrite(_IN4, HIGH);
    }
}
void MegaPingWin::curva(uint8_t velocidade, uint8_t freio, char lado)
{
    int desnivel = velocidade - freio;

    if(lado == 'E')
    {
        praFrente(velocidade, 'D');
        praFrente(freio, 'E');
    }
    else
    {
        praFrente(velocidade, 'E');
        praFrente(freio, 'D');
    }
}
int MegaPingWin::lerTSSOP(char lado)
{

}
int MegaPingWin::lerLinha()
{

}
int MegaPingWin::defineBotInicio(int _pino)
{

}
int MegaPingWin::lerTodosFrente()
{

}
int MegaPingWin::lerDistancia()
{

}