#include <NewPing.h>
#define LED_PIN 13
#define LED2_PIN 10
#define SENSOR_DIST_TRIG 7
#define SENSOR_DIST_ECHO 6
#define DIST_OBSTACULO 15
#define TEMPO_LEITURA 1000
#define PIEZO_PIN 5
#define BUT_LIGA_PIN 2
#define BUT_DESLIGA_PIN 4
//#define LDR_PIN A0

int i =0;
int distanciaAgora;
int distanciaAnt;
int estadoBotaoLiga;
int estadoBotaoDesLiga;
int estadoBotaoAnt = 1;
int start = 0;
int estado = 1;
int luminosidade;
const int delayBip = 1;
unsigned long tempoMedida;

NewPing sonar(SENSOR_DIST_TRIG, SENSOR_DIST_ECHO, DIST_OBSTACULO);

void estado_1(){
  estado = 1;
  start = LOW;
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
 }

void estado_2(){
  estado = 2;
  start = HIGH;
  digitalWrite(LED2_PIN, HIGH);
  digitalWrite(LED_PIN, LOW);
}

void estado_3(unsigned distanciaAgora){
 estado = 3;
 for (i=0;i<50;i++){
  digitalWrite(LED_PIN, HIGH);

 // digitalWrite(PIEZO_PIN, LOW);
  delay(delayBip);
 // digitalWrite(PIEZO_PIN, HIGH);
  delay(delayBip);
  
  if(distanciaAgora != distanciaAnt){
    Serial.print("Distanccia = ");
    Serial.print(distanciaAgora);
    Serial.println(" cm");
    distanciaAnt = distanciaAgora; 
   }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SENSOR_DIST_TRIG, INPUT);
  pinMode(SENSOR_DIST_ECHO , INPUT);
 // pinMode(PIEZO_PIN,OUTPUT);
  pinMode(BUT_LIGA_PIN,INPUT);
  pinMode(BUT_DESLIGA_PIN,INPUT);
  Serial.begin(9600);

  noInterrupts();           // disable all interrupts
//////////////
// Timer1
/////////////

//16MHz - 1/16.000000 = 0,00000000625 s - 0,0000625 ms
//16 bits - 65535 * 0,0000625 ms = 4,0959375 ms(tempo total até o overflow do contador)

/*Utilizando o prescaler de 256

16MHz - 1s     
256   - x

16*10^6 - 10^6
256     - x

x= 256*10^6 / 16*10^6 = 16 micros - 0,016 ms (para cada incremento no contador)

Para tempo limite 50 ms - 50/0,016 = 3125 (o contador de 16 bits conta ate 65535. Vai ser incrementado até 3125 para atingir os 50 ms)*/

 TCCR1A = 0; // controle os modos de comparacao
 TCNT1  = 0;//registrador de timer 16bits
 TCCR1B = 0;//Registrador de controle do timer 1
  
  OCR1A = 3125;            // inicializa o valor da comparacao compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // habilita o modo de geração de onda CTC no registrador do timer

  TCCR1B |= (1 << CS12);    // configura o timer com prescaler = 256  

  TIMSK1 |= (1 << OCIE1A);  // abilita a interrupção CTC timer 1

//////////////
//Timer0
/////////////

/*Utilizando o prescaler de 256

16MHz - 1s     
256   - x

16*10^6 - 10^6
1024     - x

x= 1024*10^6 / 16*10^6 = 64 micros - 0,064 ms (para cada incremento no contador)

Para tempo limite 500 ms - 500/0,064 = 7.812 (o contador de 8 bits conta ate 256. Vai ser incrementado até 31250 para atingir os 500 ms)*/

/*DDRD |= (1 << 5);
TCNT0 = 0; // inicializa o contador
TCCR0B |= (1 << WGM01);//configura modo CTC

// configura o timer com prescaler = 1024 
TCCR0B |= (1 << CS10); 
TCCR0B |= (1 << CS12);

// inicial'iza o valor de comparação
OCR0B = 220;

TIMSK0 =0;//| = (1 << OCIE0B); // ativar interrupção de comparação

TCCR0B |= (1<<COM0A0); //Configura o pino OC0B do temporizador no modo de alternência*/


  interrupts();             // enable all interrupts

}

ISR(TIMER1_COMPA_vect){          // rotina de interrupção Compara o timer 
  
  distanciaAgora = sonar.ping_cm();

}


void loop() {
  estadoBotaoLiga = digitalRead(BUT_LIGA_PIN);
  estadoBotaoDesLiga = digitalRead(BUT_DESLIGA_PIN);

  switch(estado){
    case 1:{
      //Serial.println("Estou no estado 1");
      if(estadoBotaoLiga != estadoBotaoAnt){
        estado_2();
        break;
      }
      estado_1();
      break;
     }
     case 2: {
      //Serial.println("Estou no estado 2");
      if(estadoBotaoDesLiga != estadoBotaoAnt){
        estado_1();
        break;
        }
        if(start){

       //   if((millis() >= TEMPO_LEITURA + tempoMedida)){
             // distanciaAgora = sonar.ping_cm();
            // digitalWrite(distanciaAgora);
              if(distanciaAgora != 0 && distanciaAgora <= DIST_OBSTACULO){
                // Serial.println("Entri no sensor");
                 if(estadoBotaoDesLiga != estadoBotaoAnt){
                    estado_1();
                    break;
                }      
                estado_3(distanciaAgora);
                break;
              }else{
                digitalWrite(LED_PIN, LOW);
                estado_2();
                break;
               }
             // tempoMedida = millis();
         //   }
         }
         break;
      }
      case 3:{
        //Serial.println("Estou no estado 3");
       // distanciaAgora = sonar.ping_cm();
        estadoBotaoDesLiga = digitalRead(BUT_DESLIGA_PIN);
        
        if(estadoBotaoDesLiga != estadoBotaoAnt){
          estado_1();
          break;
        }
        if(distanciaAgora != 0 && distanciaAgora <= DIST_OBSTACULO){     
           estado_3(distanciaAgora);
           break;
        }
        estado_2();
        break;      
      }
  } 
}
