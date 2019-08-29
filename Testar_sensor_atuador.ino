#include <NewPing.h>

#define LED_PIN 13
#define SENSOR_DIST_TRIG 7
#define SENSOR_DIST_ECHO 6
#define DIST_OBSTACULO 15
#define TEMPO_LEITURA 50

int distanciaAgora;
unsigned long tempoMedida;

NewPing sonar(SENSOR_DIST_TRIG, SENSOR_DIST_ECHO, DIST_OBSTACULO);
  

void setup() {

  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_DIST_TRIG, INPUT);
  pinMode(SENSOR_DIST_ECHO , INPUT);
  Serial.begin(9600);
}

void loop() {
  
  
  if(millis() >= TEMPO_LEITURA + tempoMedida){
      distanciaAgora = sonar.ping_cm();
      Serial.print("Distanccia = ");
      Serial.print(distanciaAgora);
      Serial.println(" cm");
      
      if(distanciaAgora != 0 && distanciaAgora <= DIST_OBSTACULO){
        digitalWrite(LED_PIN, HIGH);
        }else{
          digitalWrite(LED_PIN, LOW);
          }
      tempoMedida = millis();
    }
  
  
}
