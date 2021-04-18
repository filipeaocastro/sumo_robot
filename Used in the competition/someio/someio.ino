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
#define LIMIAR_BORDA 550

bool borda_direita = false, borda_esquerda = false;
bool inimigo_esquerda = false, inimigo_direita = false, inimigo_centro = false;
bool ninguem_ai = true;

float distancia = 0;

long time_borda = 0;
const int intervalo_borda = 10;
long time_search = 0;
const int intervalo_search = 10;

long time_now = 0;


void setup()
{
    Serial.begin(9600);
    for(int i = 6; i < 12; i++)
        pinMode(i, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(BOT_BEGIN, INPUT_PULLUP);
    
    while(digitalRead(BOT_BEGIN) != 0);

    delay(5000);
}
void loop()
{
    praFrente(100, 'T');
    time_now = millis();
    arrumaFlags();

    // Verifica Borda
    if(time_now - time_borda >= intervalo_borda)
    {
        verificaBorda();
        time_now = millis();
        time_borda = time_now;
    }

    if(time_now - time_search >= intervalo_search)
    {
        search();
        time_now = millis();
        time_borda = time_now;
    }
    arrumaFlags();


    if(ninguem_ai)*/
        praFrente(100, 'T');
    else
    {
        if(inimigo_esquerda && !inimigo_centro && !inimigo_direita)
            curva(40, 60, 'E');
        if(!inimigo_esquerda && !inimigo_centro && inimigo_direita)
            curva(40, 60, 'D');
        if(inimigo_esquerda && inimigo_centro && !inimigo_direita)
        {
            if(distancia >= 20)
                curva(30, 60, 'E');
            else if(distancia >= 10)
                curva(40, 70, 'E');
            else
                curva(20, 100, 'E');
        }
        if(!inimigo_esquerda && inimigo_centro && inimigo_direita)
        {
            if(distancia >= 20)
                curva(30, 60, 'D');
            else if(distancia >= 10)
                curva(40, 70, 'D');
            else
                curva(20, 100, 'D');
        }
        if(!inimigo_esquerda && inimigo_centro && !inimigo_direita)
        {
            if(distancia >= 20)
                praFrente(50, 'T');
            else if(distancia >= 10)
                praFrente(70, 'T');
            else
                praFrente(100, 'T');
        }
    }
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

    Serial.print(bordaD); Serial.print("\t");
    Serial.println(bordaE);

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

    /*if( (bordaD == true) && (bordaE == true) )
    {   
        //parar('T');
        //delay(100);
        praTras(70, 'T');
        delay(300);
        praFrente(70, 'D');
        praTras(70, 'E');
        delay(300);

    }*/
    if(bordaD)
    {
        //parar('T');
        //delay(100);
        praTras(70, 'T');
        delay(250);
        praFrente(50, 'D');
        praTras(70, 'E');
        delay(340);
    }
    else if(bordaE)
    {
        //parar('T');
        //delay(100);
        praTras(70, 'T');
        delay(250);
        praFrente(50, 'E');
        praTras(70, 'D');
        delay(340);
    }

}

void meiaVolta(int nivel_vel, char lado)
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
    
}

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
    int leitura_tssop_e, leitura_tssop_d, leitura_distancia;

    leitura_tssop_e = digitalRead(TSSOP_ESQ);
    leitura_tssop_d = digitalRead(TSSOP_DIR);
    leitura_distancia = analogRead(SENSOR_DISTANCIA);

    // Obtenção do valor em Volts através da formula ( valorAnalógico * (5/1023) )
    float valorVolts = leitura_distancia * (5.0/1023.0); 

    // Formula para cálculo da distância levando em consideração o valor em volts
    distancia = 4800 / (valorVolts * 200 - 20 ); 

    /*if(leitura_tssop_e != 0)
        inimigo_esquerda = true;
    else
        inimigo_esquerda = false;
    
    if(leitura_tssop_d != 0)
        inimigo_direita = true;
    else
        inimigo_direita = false;*/

    if(distancia <= 40)
        inimigo_centro = true;
    else
        inimigo_centro = false;
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