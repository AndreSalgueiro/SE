#include <RF24.h>
#include <printf.h>

#define RADIO_ID 0

//Configura os pinos de controle
#if RADIO_ID == 0
  RF24 radio(8,//CE(enable)
           9//CSN (select)
            );
#define entreiFuncaoRadio 0
#else 
  RF24 radio(2,//CE(enable)
           3//CSN (select)
            );
#define entreiFuncaoRadio 1
#endif
          
byte enderecos[][6] = {"1Node","2Node"};         
int dadoDeEnvio;
int dadosRecebidos;
         
void setup() {
  
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  //radio.setPALevel(RF24_PA_LOW);
    
  Serial.print("Entrei na Funcao Radio = ");
  Serial.println(entreiFuncaoRadio);
  
  #if RADIO_ID == 0 // Arduino 0
   // Serial.println("entrei no radio 0");
    radio.openWritingPipe(enderecos[0]);//abre canal de comunicacao de escrita
    Serial.println("Configurei escrita radio 0");
    radio.openReadingPipe(1,enderecos[1]);//abre canal de comunicacao de leitura
     Serial.println("Configurei leitura radio 0");
    // delay(1000);
  #else // Arduino 1
   Serial.println("entrei no radio 1");
    radio.openWritingPipe(enderecos[1]);
    radio.openReadingPipe(1,enderecos[0]);
  #endif
  
  radio.startListening();//habilita a escuta
  /*Imprime detalhes do sistema necessario incluir a biblioteca <printf.h>
   * e definir printf.begin() no setup
   */
  radio.printDetails();
}

void loop() {

  if(radio.isChipConnected()){
    Serial.println("Dispositivo de radio conectado");
    }else{
      Serial.println("Dispositivo de radio Desconectado");
      }
  dadoDeEnvio = 255; 
   delay(3000);
   
  radio.stopListening();
  
  if(radio.write(&dadoDeEnvio, sizeof(int))){//enviando a informacao
      Serial.println("Dado enviado com sucesso - Emissor");
    }else{
        Serial.println("Erro de envio do Emissor");
      } 
  radio.startListening();

  if(radio.available()){ //verifica se estou recebendo alguma informacao
     
      radio.read(&dadosRecebidos, sizeof(int)); //recebendo dado
      Serial.println("Valor dados recebido - Receptor");
      Serial.println(dadosRecebidos);
    }
}
