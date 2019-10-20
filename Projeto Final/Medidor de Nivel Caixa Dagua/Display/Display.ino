#include <U8glib.h>
#include <RF24.h>
//#include <printf.h>

//#define LED2_PIN 10
//#define DIST_OBSTACULO 15
#define BOTAO_SISTEMA_PIN 6
#define BOTAO_BOMBA_PIN 7

int i =0;
int estadoBotaoSistema = 0;
int estadoBotaoBomba = 0;
int estadoBotaoSistemaAnt = 1;
int estadoBotaoBombaAnt = 1;
int estadoBotaoDesligaAnt = 1;
int start = 0;
int estado = 0;
int estadoAnterior = 1000;

byte enderecos[][6] = {"1Node","2Node"}; 

struct estruturaRecebidoRF{

  boolean bombaLigada = false;
  boolean dispositivoOperanteRF = false;
  int nivelAgua = 0;
  
  };

typedef struct estruturaRecebidoRF tipoRecebidoRF;
tipoRecebidoRF dadosRecebidoRF;

U8GLIB_ST7920_128X64_1X u8g( 10,  //E
                             9,  //R/W
                             8,  //RS
                             11); //RST

RF24 radio(2,//CE(enable)
           3//CSN (select)
            );

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
 
  //pinMode(LED2_PIN, OUTPUT);
  //pinMode(PIEZO_PIN,OUTPUT);
  pinMode(BUT_LIGA_PIN,INPUT);
  pinMode(BUT_DESLIGA_PIN,INPUT);
  
  Serial.begin(9600); 
  //printf_begin();
  radio.begin();

  radio.openWritingPipe(enderecos[0]);//abre canal de comunicacao de escrita
  //Serial.println("Configurei escrita radio 0");
  radio.openReadingPipe(1,enderecos[1]);//abre canal de comunicacao de leitura
  //Serial.println("Configurei leitura radio 0");

  radio.startListening();//habilita a escuta

  /*Imprime detalhes do sistema necessario incluir a biblioteca <printf.h>
   * e definir printf.begin() no setup
   */
   //radio.printDetails();
}

void loop() {

  switch(estado){
     case 0:{
      imprimeEstadoAtual(estado);
      estadoBotaoSistema = digitalRead(BOTAO_SISTEMA_PIN);
      
      if(estadoBotaoSistema != estadoBotaoSistemaAnt){
        estadoBotaoSistemaAnt = estadoBotaoSistema;
        if(!estadoBotaoSistema == HIGH){
          break;
          }
       // start = true;
        estado_1();
        break;
      }
      estado_0();
      break;
     }
     case 1: {
      
      imprimeEstadoAtual(estado);
      
      estadoBotaoSistema = digitalRead(BOTAO_SISTEMA_PIN);
      
      if(estadoBotaoSistema != estadoBotaoDesligaAnt){
        estado_0();
        break;
        }

       radio.startListening();
      
      if(radio.available()){ //verifica se estou recebendo alguma informacao
        radio.read(&dadosRecebidoRF, sizeof(tipoRecebidoRF));//recebendo dado
        Serial.print("Dados Recebido Medidor Nivel = ");
        Serial.println(dadosRecebidoRF);
        
        estado_2();
        break;
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
