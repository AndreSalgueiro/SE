#include <RF24.h>
#define RADIO_ID 1

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
String mensagem;
boolean deuCerto;
         
void setup() {
  
  Serial.begin(9600);
  radio.begin();
  
  Serial.print("Entrei na Funcao Radio = ");
  Serial.println(entreiFuncaoRadio);
  
  #if RADIO_ID == 0 // Arduino 0
   // Serial.println("entrei no radio 0");
    radio.openWritingPipe(enderecos[0]);//abre canal de comunicacao de escrita
    Serial.println("Configurei escrita radio 0");
    radio.openReadingPipe(1,enderecos[1]);//abre canal de comunicacao de leitura
     Serial.println("Configurei leitura radio 0");

  #else // Arduino 1
   Serial.println("entrei no radio 1");
    radio.openWritingPipe(enderecos[1]);
    radio.openReadingPipe(1,enderecos[0]);
  #endif
  
  radio.startListening();//habilita a escuta
}

void loop() {

   if(radio.available()){ //verifica se estou recebendo alguma informacao
     
      Serial.println("Dado recebido com sucesso do Emissor");
      
      radio.read(&dadosRecebidos, sizeof(int)); //recebendo dado
      Serial.println("Valor dado recebido do Emissor");
      Serial.println(dadosRecebidos);
      
        radio.stopListening();
        dadoDeEnvio = dadosRecebidos;
        
      if(radio.write(&dadoDeEnvio, sizeof(int))){//enviando a informacao
        Serial.println("Dado enviado com sucesso do Receptor");
      }
      else{
        Serial.println("Erro de envio do Receptor");
      } 
  radio.startListening();
    }
}
