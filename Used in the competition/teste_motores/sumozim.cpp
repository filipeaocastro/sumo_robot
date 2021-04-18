#define ENA 6
#define IN1 7 // Positivo do motor esquerdo
#define IN2 8
// Motor direito
#define IN3 9     // Positivo motor direito
#define IN4 10
#define ENB 11
#define BORDA_ESQ A7
#define BORDA_DIR A0
#define LIMIAR_BORDA 400
int state_pointer;
int temp_init, temp_atual, delta;
enum States {Initialize, Go_ahead, Detect_border, Go_back, Search, Rotate};
char Direction;

void setup() {
  pinMode(2, INPUT_PULLUP);
  for(int i = 6; i < 12; i++)
        pinMode(i, OUTPUT);
  while (digitalRead(2) != 0)
  {
    state_pointer = Initialize;
  }
  temp_init = millis();
}

void loop() {
  switch (state_pointer)
  {
    case Initialize:
      Conta_5s();
      break;

    case Go_ahead:
      praFrente(50, Direction);
      state_pointer = Detect_border;
      break;

    case Search:
      state_pointer = Detect_border;
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
    
    default:
      break;
  }
}

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
    }

}

void verificaBorda()
{
    int bordaD = analogRead(BORDA_DIR);
    int bordaE = analogRead(BORDA_ESQ);

    Serial.print(bordaD); Serial.print("\t");
    Serial.println(bordaE);

    /*if( (bordaD <= LIMIAR_BORDA) && (bordaE <= LIMIAR_BORDA) )
    {
        Direction = 'T';
        state_pointer = Go_back;
    }*/
    if(bordaD <= LIMIAR_BORDA)
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
    }

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



