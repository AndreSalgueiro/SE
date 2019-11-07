#include <NewPing.h>
#include <RF24.h>
//#include <printf.h>

#define BOMBA_PIN 5
#define SENSOR_DIST_TRIG 7
#define SENSOR_DIST_ECHO 6
#define TEMPO_ESPERA_LEITURA 200

int nivelAguaAnterior = 0;
int dadosRecebidos = 0;
int alturaReservatorio = 40;//30cm
int nivelCheio = 10;//10cm
int nivelVazio = alturaReservatorio - 10;//10cm
int nivelLiquidoAgora = 0;
int estado = 3;
unsigned long tempoCorrido = 0;

byte enderecos[][7] = {"1Nody","2Nody"};

struct estruturaDadosRF{

  int nivelLiquidoRF = 0;
  boolean bombaLigadaRF = false;
  boolean dispositivoOperanteRF = false;
  boolean botaoBombaAcionadoRF = false;
  boolean controleManualAcionadoRF = false;
  };

typedef struct estruturaDadosRF tipoDadosRF;
tipoDadosRF dadosEnvioRF;
tipoDadosRF dadosRecebidoRF;


NewPing sonar(SENSOR_DIST_TRIG, SENSOR_DIST_ECHO);
RF24 radio(8,//CE(enable)
           9//CSN (select)
            );

void setup() {
  
  pinMode(BOMBA_PIN, OUTPUT);
  pinMode(SENSOR_DIST_TRIG, INPUT);
  pinMode(SENSOR_DIST_ECHO , INPUT);

  digitalWrite(BOMBA_PIN, LOW);//bomba desligada
  
  Serial.begin(9600); 
  //printf_begin();
  radio.begin();
  
  //Abrindo um canal de comunicacao
  radio.openWritingPipe(enderecos[1]);
  radio.openReadingPipe(1,enderecos[0]);

  radio.startListening();//habilita a escuta

   /*Imprime detalhes do sistema necessario incluir a biblioteca <printf.h>
   * e definir printf.begin() no setup
   */
  // radio.printDetails();
}

void loop() {
  switch(estado){
    case 3:{
      //Serial.print("Tempo espera = ");
      //Serial.println(TEMPO_ESPERA_LEITURA);
      //Serial.print("Tempo corrido = ");
      //Serial.println(tempoCorrido);
      //Serial.print("Tempo millis = ");
      //Serial.println(millis());
      //if((millis() >= TEMPO_ESPERA_LEITURA + tempoCorrido)){
        
      //Verifica se o transmissor de radio esta funcionando
     /* if(radio.isChipConnected()){
        Serial.println("Dispositivo de radio operante");
        dadosEnvioRF.dispositivoOperanteRF = true;
      }else{
        Serial.println("Dispositivo de radio inoperante");
        dadosEnvioRF.dispositivoOperanteRF = false;
        }*/
        
      nivelLiquidoAgora = sonar.ping_cm();
      //Serial.println(nivelLiquidoAgora);  
      //if(nivelLiquidoAgora != nivelAguaAnterior){
        //Serial.println("Teste");
        nivelAguaAnterior != nivelLiquidoAgora; 
  
        /////////////////////////////
       //Controle Manual da Bomba
       /////////////////////////////
       if(dadosRecebidoRF.controleManualAcionadoRF){
        Serial.println("Entrei no modo manual no sensor caixa dagua");
          if(dadosRecebidoRF.botaoBombaAcionadoRF){
            Serial.println("Entrei no modo MANUAL");
              //Se a bomba estava desligada entao liga
              Serial.println(dadosRecebidoRF.bombaLigadaRF);
              if(dadosRecebidoRF.bombaLigadaRF){
                dadosEnvioRF.bombaLigadaRF = true;
                digitalWrite(BOMBA_PIN, HIGH);
                  //Desliga a bomba se o nivel maximo foi atingido
                  if(nivelLiquidoAgora <= nivelCheio){
                    dadosEnvioRF.bombaLigadaRF = false;
                    digitalWrite(BOMBA_PIN, LOW); 
                   } 
                }
              else if(!dadosRecebidoRF.bombaLigadaRF){
                dadosEnvioRF.bombaLigadaRF = false;
                digitalWrite(BOMBA_PIN, LOW);   
              }
          }
         /////////////////////////////
         //Controle Automatico Bomba
         /////////////////////////////
        }else {
          //Lig a bomba caso tenha atingido o nivel vazio
          Serial.println("Entrei no modo AUTOMATICO");
          if(nivelLiquidoAgora > nivelCheio){
            dadosEnvioRF.bombaLigadaRF = true;
            digitalWrite(BOMBA_PIN, HIGH);
            }
            //Desliga a bomba caso tenha atingido o nivel cheio
            else if(nivelLiquidoAgora <= nivelCheio){
              dadosEnvioRF.bombaLigadaRF = false;
              digitalWrite(BOMBA_PIN, LOW);
              }
        }
        
        dadosEnvioRF.nivelLiquidoRF = nivelLiquidoAgora;
  
        Serial.print("Nivel liquido enviado ao display - ");
        Serial.println(dadosEnvioRF.nivelLiquidoRF);
        
        radio.stopListening();  
        //Envia dados ao estado 1
        if(radio.write(&dadosEnvioRF, sizeof(tipoDadosRF))){//enviando a informacao
          Serial.println("[SUCESSO]-Envio dados display");
       }else{
          Serial.println("[ERRO]-Envio dados display");
          } 
  
        radio.startListening();
          
       //}
       tempoCorrido = millis();
     // }
  
      radio.startListening();
      //Recebe dados do estado 1 
      if(radio.available()){ //verifica se estou recebendo alguma informacao
        radio.read(&dadosRecebidoRF, sizeof(tipoDadosRF)); //recebendo dado
        Serial.println("[SUCESSO]-Recebido comando ligar/desligar bomba");
        Serial.print("Ligar/Desligar bomba - ");
        Serial.println(dadosRecebidoRF.bombaLigadaRF);
        //dadosEnvioRF.bombaLigadaRF = dadosRecebidoRF.bombaLigadaRF;
  
      }
      
      }
    }
  }
