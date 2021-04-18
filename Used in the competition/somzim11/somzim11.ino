#define ENA 6
#define IN1 7 // Positivo do motor esquerdo
#define IN2 8
// Motor direito
#define IN3 9     // Positivo motor direito
#define IN4 10
#define ENB 11
#define BORDA_ESQ A7
#define BORDA_DIR A0
#define LIMIAR_BORDA 350
#define SENSOR_DIST A2


int state_pointer;
int temp_init, temp_atual, delta;
enum States {Initialize, Go_ahead, Detect_border, Go_back, Search, Rotate, Atropela_Piranha};
char Direction;

long time_init_curva = 0;
long time_curva = 0;
const int time_limit_curva = 500;

int distancia;

bool curvando = false;
bool nao_vejo_ninguem = true;

long time_serial = 0;
const int intervalo_serial = 700;

void setup() {
  pinMode(2, INPUT_PULLUP);
  for(int i = 6; i < 12; i++)
        pinMode(i, OUTPUT);
  while (digitalRead(2) != 0)
  {
    state_pointer = Initialize;
  }
  temp_init = millis();
  Serial.begin(9600);
}

void loop() {
    switch (state_pointer)
    {
    case Initialize:
        Conta_5s();
        break;

    case Go_ahead:
        Direction = 'T';
        praFrente(50, Direction);
        state_pointer = Detect_border;
        break;

    case Search:
        verificaSensor();
        if(nao_vejo_ninguem && !curvando)
            state_pointer = Go_ahead;
        else if (!nao_vejo_ninguem)
            state_pointer = Atropela_Piranha;

        break;

    case Detect_border:
        verificaBorda();
        break;

    case Go_back:
        praTras(50, Direction);
        state_pointer = Detect_border;
        break;

    case Rotate:
        curva(100, 100, Direction);
        state_pointer = Search;
        break;

    case Atropela_Piranha:
        Direction = 'T';
        praFrente(100, Direction);
        state_pointer = Detect_border;

    default:
        break;
    }

  timers();

  /*if(millis() - time_serial >= intervalo_serial)
  {
      plotaCoisas();
      time_serial = millis();
  }*/
  
}

void curva(int nivel, int vel, char lado)
{
    time_init_curva = millis();
    int desnivel = vel - nivel;

    if(lado == 'E')
    {
        praTras(vel, 'E');
        praTras(desnivel, 'D');
    }
    else
    {
        praTras(vel, 'D');
        praTras(desnivel, 'E');
    }
    curvando = true;
    
}

void Conta_5s()
{
  temp_atual = millis();
  delta = temp_atual - temp_init;
  if (delta >= 5000)
  {
    Direction = 'T';
    state_pointer = Go_ahead;
  }
}

int prct(int perc)
{
    int pwm = map(perc, 0, 100, 0, 255);
    return pwm;
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

        curvando = false;
    }

}

void verificaBorda()
{
    int bordaD = analogRead(BORDA_DIR);
    int bordaE = analogRead(BORDA_ESQ);

    

    if(millis() - time_serial >= intervalo_serial)
    {
        Serial.print(bordaD); Serial.print("\t");
        Serial.println(bordaE);
    }

    if( (bordaD <= LIMIAR_BORDA) && (bordaE <= LIMIAR_BORDA) )
    {
        Direction = 'E';
        praTras(80, 'T');
        delay(150);
        state_pointer = Rotate;
    }
    else if(bordaD <= LIMIAR_BORDA)
    {
        Direction = 'E';
        state_pointer = Rotate;
    }
     else if(bordaE <= LIMIAR_BORDA)
    {
        Direction = 'D';
        state_pointer = Rotate;
    }
    else
    {
        state_pointer = Search;
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

        curvando = false;
    }

}

void timers()
{
    time_curva = millis() - time_init_curva;

    if( (time_curva >= time_limit_curva) && nao_vejo_ninguem && curvando )
    {
        state_pointer = Go_ahead;
        curvando = false;
        Serial.println("PASSOU POR AQUI");
    }
}

void verificaSensor()
{
    int leitura_dist = analogRead(SENSOR_DIST);

    // Obtenção do valor em Volts através da formula ( valorAnalógico * (5/1023) )
    float valorVolts = leitura_dist * (5.0/1023.0); 

    // Formula para cálculo da distância levando em consideração o valor em volts
    distancia = 4800 / (valorVolts * 200 - 20 ); 

    if( (distancia <= 30) && (distancia > 0))
        nao_vejo_ninguem = false;
    else
        nao_vejo_ninguem = true;

}
void plotaCoisas()
{
    Serial.print("Distância: "); Serial.println(distancia);
    Serial.print("N vejo ninguem: "); Serial.println(nao_vejo_ninguem);
    Serial.print("Curvando: "); Serial.println(curvando);
    Serial.print("state_pointer: ");Serial.println(state_pointer);
    Serial.println();
}
