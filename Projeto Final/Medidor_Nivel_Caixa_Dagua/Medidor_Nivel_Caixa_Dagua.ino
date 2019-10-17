#include <U8glib.h>
#include <NewPing.h>
#define LED_PIN 5
//#define LED2_PIN 10
#define SENSOR_DIST_TRIG 7
#define SENSOR_DIST_ECHO 6
//#define DIST_OBSTACULO 15
#define TEMPO_ESPERA_LEITURA 50
#define BUT_LIGA_PIN 2
#define BUT_DESLIGA_PIN 4

int i =0;
int distanciaAgora = 0;
int distanciaAnt = 0;
int estadoBotaoLiga = 0;
int estadoBotaoDesLiga = 0;
int estadoBotaoAnt = 1;
int start = 0;
int estado = 0;
unsigned long tempoCorrido = 0;
int estadoAnterior = 1000;

NewPing sonar(SENSOR_DIST_TRIG, SENSOR_DIST_ECHO);
U8GLIB_ST7920_128X64_1X u8g( 10,  //E
                             9,  //R/W
                             8,  //RS
                             11); //RST

void imprimeEstadoAtual(int estadoAtual){

    if (estadoAnterior != estadoAtual){
        Serial.print("Estou no estado = ");
        Serial.println(estadoAtual);
        estadoAnterior = estadoAtual;
      }
  }

void estado_0(){
  digitalWrite(LED_PIN, LOW);
  start = LOW;
  estado = 0;
  }

void estado_1(){
  start = HIGH;
  digitalWrite(LED_PIN, HIGH);
  estado = 1;
 }

void estado_2(){
  estado = 2;
}

void estado_3(unsigned distanciaAgora){
  //Faz algo com a distância aqui?
  estado = 3;
  }

void setup() {
  pinMode(LED_PIN, OUTPUT);
  //pinMode(LED2_PIN, OUTPUT);
  pinMode(SENSOR_DIST_TRIG, INPUT);
  pinMode(SENSOR_DIST_ECHO , INPUT);
  //pinMode(PIEZO_PIN,OUTPUT);
  pinMode(BUT_LIGA_PIN,INPUT);
  pinMode(BUT_DESLIGA_PIN,INPUT);
  //pinMode(LDR_PIN, INPUT);
  Serial.begin(9600); 
  
}

void loop() {

  switch(estado){
     case 0:{
      imprimeEstadoAtual(estado);
      estadoBotaoLiga = digitalRead(BUT_LIGA_PIN);
      
      if(estadoBotaoLiga != estadoBotaoAnt){
        estado_1();
        break;
      }
      estado_0();
      break;
     }
     case 1: {
      imprimeEstadoAtual(estado);
      estadoBotaoDesLiga = digitalRead(BUT_DESLIGA_PIN);
      //Serial.print("Estado botao Desliga = ");
     // Serial.println(estadoBotaoDesLiga);
      
      if(estadoBotaoDesLiga != estadoBotaoAnt){
        estado_0();
        break;
        }
        if(start){
          //Serial.print("Luminosidade = ");
          //Serial.println(luminosidade);
          if((millis() >= TEMPO_ESPERA_LEITURA + tempoCorrido)){     
                estado_2();
                break;
              }
              tempoCorrido = millis();
            }
        break;
      }
      case 2:{
        imprimeEstadoAtual(estado);
        distanciaAgora = sonar.ping_cm();
       //chama estado 3 que envia os dados para LCD
        if(distanciaAgora != distanciaAnt){
          distanciaAnt != distanciaAgora;     
           estado_3(distanciaAgora);
           break;
        }
        estado_2();
        break;      
      }
      case 3:{
          imprimeEstadoAtual(estado);
          //Trata os dados e envia para o LCD
          Serial.println("Enviando os dados para LCD");
          estado_1();
          break;
       }
  } 
}
