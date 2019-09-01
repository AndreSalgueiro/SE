#include <NewPing.h>
#define LED_PIN 13
#define LED2_PIN 10
#define SENSOR_DIST_TRIG 7
#define SENSOR_DIST_ECHO 6
#define DIST_OBSTACULO 15
#define TEMPO_LEITURA 50
#define PIEZO_PIN 5
#define BUT_LIGA_PIN 2
#define BUT_DESLIGA_PIN 4

int i =0;
int distanciaAgora;
int distanciaAnt;
int estadoBotaoLiga;
int estadoBotaoDesLiga;
int estadoBotaoAnt = 1;
int start = 0;
const int delayBip = 1;
unsigned long tempoMedida;

NewPing sonar(SENSOR_DIST_TRIG, SENSOR_DIST_ECHO, DIST_OBSTACULO);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SENSOR_DIST_TRIG, INPUT);
  pinMode(SENSOR_DIST_ECHO , INPUT);
  pinMode(PIEZO_PIN,OUTPUT);
  pinMode(BUT_LIGA_PIN,INPUT);
  pinMode(BUT_DESLIGA_PIN,INPUT);
  Serial.begin(9600);
}
void loop() { 
estadoBotaoLiga = digitalRead(BUT_LIGA_PIN);
estadoBotaoDesLiga = digitalRead(BUT_DESLIGA_PIN);
Serial.println(estadoBotaoLiga);
Serial.println(estadoBotaoDesLiga);

 if(estadoBotaoLiga != estadoBotaoAnt){
    start = HIGH;
    digitalWrite(LED2_PIN, HIGH);
    //Serial.println(start);
  } 
  if(estadoBotaoDesLiga != estadoBotaoAnt){
    start = LOW;
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    //Serial.println(start); 
    }
  if(start){
    if(millis() >= TEMPO_LEITURA + tempoMedida){
        distanciaAgora = sonar.ping_cm();
        if(distanciaAgora != 0 && distanciaAgora <= DIST_OBSTACULO){       
            for (i=0;i<256;i++){
              digitalWrite(LED_PIN, HIGH);
              analogWrite(5,i);
              delay(delayBip);
              if(distanciaAgora != distanciaAnt){
                Serial.print("Distanccia = ");
                Serial.print(distanciaAgora);
                Serial.println(" cm");
                distanciaAnt = distanciaAgora; 
               }
            }  
        }else{
            digitalWrite(LED_PIN, LOW);
         }
        tempoMedida = millis();
      }
  }
}
