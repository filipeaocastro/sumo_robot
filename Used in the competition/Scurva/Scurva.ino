// PINOS
// Motor esquerdo
#define ENA 6
#define IN1 7 // Positivo do motor esquerdo
#define IN2 8
// Motor direito
#define IN3 9     // Positivo motor direito
#define IN4 10
#define ENB 11

// Sensores
#define BORDA_ESQ A7
#define BORDA_DIR A0
#define TSSOP_DIR A1
#define TSSOP_ESQ A5
#define SENSOR_DISTANCIA A2

// Misc
#define BOT_BEGIN 2
#define LED 13

// CONSTANTES
#define LIMIAR_BORDA 300

bool borda_direita = false, borda_esquerda = false;
bool inimigo_esquerda = false, inimigo_direita = false, inimigo_centro = false;
bool ninguem_ai = true;

float distancia = 0;

long time_borda = 0;
const int intervalo_borda = 10;

long time_search = 0;
const int intervalo_search = 30;

long time_now = 0;

const int nmedias = 5;
int medias[nmedias];



void setup()
{
    Serial.begin(9600);
    for(int i = 6; i < 12; i++)
        pinMode(i, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(BOT_BEGIN, INPUT_PULLUP);

    for(int i = 0; i < nmedias; i++)
      medias[i] = 0;
    
    while(digitalRead(BOT_BEGIN) != 0);

    delay(5000);
}
void loop()
{
  verificaBorda();
  search();
}

void praFrente(int velocidade, char qual)
{
    velocidade = prct(velocidade);

    if(qual == 'D')
    {
        // Velocidade
        analogWrite(ENB, velocidade);

        // Motor direito
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW); 
    }
    else if(qual == 'E')
    {
        // Velocidade
        analogWrite(ENA, velocidade);
        
        // Motor esquerdo
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else
    {
        // Velocidade
        analogWrite(ENA, velocidade);
        analogWrite(ENB, velocidade);
        
        // Motor esquerdo
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);

        // Motor direito
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW); 
    }

}

void praTras(int velocidade, char qual)
{
    velocidade = prct(velocidade);

    if(qual == 'D')
    {
        // Velocidade
        analogWrite(ENB, velocidade);

        // Motor direito
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH); 
    }
    else if(qual == 'E')
    {
        // Velocidade
        analogWrite(ENA, velocidade);
        
        // Motor esquerdo
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    else
    {
        // Velocidade
        analogWrite(ENA, velocidade);
        analogWrite(ENB, velocidade);
        
        // Motor esquerdo
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);

        // Motor direito
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }

}

void parar(char qual)
{
    if(qual == 'D')
    {
        // Velocidade
        analogWrite(ENB, 0);

        // Motor direito
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH); 
    }
    else if(qual == 'E')
    {
        // Velocidade
        analogWrite(ENA, 0);
        
        // Motor esquerdo
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
    }
    else
    {
        // Velocidade
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
        
        // Motor esquerdo
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);

        // Motor direito
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH); 
    }
}

// Muda de porcentagem pra pwm
int prct(int perc)
{
    int pwm = map(perc, 0, 100, 0, 255);
    return pwm;
}

// Verfica os sensores de borda
void verificaBorda()
{
    int bordaD = analogRead(BORDA_DIR);
    int bordaE = analogRead(BORDA_ESQ);

    //Serial.print(bordaD); Serial.print("\t");
    //Serial.println(bordaE);
    //Serial.println(distancia);

    if( (bordaD <= LIMIAR_BORDA) && (bordaE <= LIMIAR_BORDA) )
    {
        borda_direita = true;
        borda_esquerda = true;
    }
    else if(bordaD <= LIMIAR_BORDA)
    {
        borda_direita = true;
        borda_esquerda = false; 
    }
     else if(bordaE <= LIMIAR_BORDA)
    {
        borda_direita = false;
        borda_esquerda = true;
    }
    else
    {
        borda_direita = false;
        borda_esquerda = false;
    }
    saiDaBorda(borda_direita, borda_esquerda);
    
}

void saiDaBorda(bool bordaD, bool bordaE)
{

    if( (bordaD == true) && (bordaE == true) )
    {   

        praTras(20, 'T');
        delay(100);

        praTras(70, 'T');
        delay(250);
        praFrente(50, 'E');
        praTras(70, 'D');
        delay(200);
        praFrente(40, 'E');
        praTras(40, 'D');
        //delay(600);
        for(int i = 0; i < 300  ; i++)
        {
          search();
          if(inimigo_centro)
          {
            praFrente(100, 'T');
            break;
          }
          else
            delay(1);
        }

    }
    else if((bordaD == true) && (bordaE == false))
    {
        //parar('T');
        //delay(100);
        praTras(70, 'T');
        delay(250);
        praFrente(50, 'D');
        praTras(70, 'E');
        delay(200);
        praFrente(40, 'D');
        praTras(40, 'E');
        //delay(600);
        for(int i = 0; i < 300; i++)
        {
          search();
          if(inimigo_centro)
          {
            praFrente(100, 'T');
            break;
          }
          else
            delay(1);
        }
    }
    else if((bordaD == false) && (bordaE == true))
    {
        //parar('T');
        //delay(100);
        praTras(70, 'T');
        delay(250);
        praFrente(50, 'E');
        praTras(70, 'D');
        delay(200);
        praFrente(40, 'E');
        praTras(40, 'D');
        //delay(600);
        for(int i = 0; i < 300; i++)
        {
          search();
          if(inimigo_centro)
          {
            praFrente(100, 'T');
            break;
          }
          else
            delay(1);
        }
    }
    else if ((bordaD == false) && (bordaE == false))
    {
      if(inimigo_centro)
      {
        praFrente(100, 'T');
      }
      else
      {
        praFrente(50, 'T');
      }
        
    }

}

/*void meiaVolta(int nivel_vel, char lado)
{
    int roda_1, roda_2;
    if(nivel_vel == 1)
    {
        roda_1 = 0;
        roda_2 = 50;
    }
    if(nivel_vel == 2)
    {
        roda_1 = 35;
        roda_2 = 70;
    }
    if(nivel_vel == 3)
    {
        roda_1 = 100;
        roda_2 = 100;
    }

    char lado_1, lado_2;
    if(lado == 'E')
    {
        lado_1 = 'E';
        lado_2 = 'D';
    }
    else
    {
        lado_1 = 'D';
        lado_2 = 'E';
    }

    praFrente(roda_2, lado_2);
    praTras(roda_1, lado_1);
    
}*/

// nivel e vel de 0 a 100
void curva(int nivel, int vel, char lado)
{
    int desnivel = vel - nivel;

    if(lado == 'E')
    {
        praFrente(vel, 'D');
        praFrente(desnivel, 'E');
    }
    else
    {
        praFrente(vel, 'E');
        praFrente(desnivel, 'D');
    }
    
}

void search()
{
    if(millis() - time_search >= intervalo_search)
    {
      int leitura_distancia;
      int _nmedias = nmedias - 1;
      leitura_distancia = analogRead(SENSOR_DISTANCIA);
      

      for(int i = 0; i < _nmedias; i++)
      {
        medias[i] = medias[i + 1];
      }
      medias[_nmedias] = leitura_distancia;
      int soma = 0;
      for (int i = 0; i < nmedias; i++)
        soma += medias[i];

      leitura_distancia = soma / nmedias;
      // Obtenção do valor em Volts através da formula ( valorAnalógico * (5/1023) )
      float valorVolts = leitura_distancia * (5.0/1023.0); 
  
      // Formula para cálculo da distância levando em consideração o valor em volts
      distancia = 4800 / (valorVolts * 200 - 20 );
      if(distancia < 0)
        distancia = 0;
      if(distancia > 100)
        distancia = 100;
      
      Serial.print(leitura_distancia); Serial.print("\t");
      Serial.println(distancia);
  
      if( (distancia <= 40) && (distancia > 0))
          inimigo_centro = true;
      else
          inimigo_centro = false;
      time_search = millis();
    }
    
}

void arrumaFlags()
{
    if(inimigo_esquerda || inimigo_direita || inimigo_centro)
    {
        ninguem_ai = false;
        digitalWrite(LED, HIGH);
    }
        
    else
    {
        ninguem_ai = true;
        digitalWrite(LED, LOW);
    }
        
}
