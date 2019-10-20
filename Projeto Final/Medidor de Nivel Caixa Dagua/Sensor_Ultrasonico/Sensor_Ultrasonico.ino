#include <NewPing.h>
#include <RF24.h>
//#include <printf.h>

#define BOMBA_PIN 5
#define SENSOR_DIST_TRIG 7
#define SENSOR_DIST_ECHO 6
#define TEMPO_ESPERA_LEITURA 50

int nivelAguaAnterior = 0;
int dadosRecebidos = 0;
int nivelVazio = 15;
int nivelCheio = 5;
int nivelAguaAgora = 0;

unsigned long tempoCorrido = 0;

byte enderecos[][6] = {"1Node","2Node"};

struct estruturaEnvioRF{

  boolean bombaLigada = false;
  boolean dispositivoOperanteRF = false;
  int nivelAgua = 0;
  
  };

typedef struct estruturaEnvioRF tipoDadosEnvioRF;
tipoDadosEnvioRF dadosEnvioRF;

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
  //Serial.print("Tempo espera = ");
  //Serial.println(TEMPO_ESPERA_LEITURA);
  //Serial.print("Tempo corrido = ");
  //Serial.println(tempoCorrido);
  //Serial.print("Tempo millis = ");
  //Serial.println(millis());
  if((millis() >= TEMPO_ESPERA_LEITURA + tempoCorrido)){
      
    //Verifica se o transmissor de radio esta funcionando
    if(radio.isChipConnected()){
      Serial.println("Dispositivo de radio operante");
      dadosEnvioRF.dispositivoOperanteRF = true;
    }else{
      Serial.println("Dispositivo de radio inoperante");
      dadosEnvioRF.dispositivoOperanteRF = false;
      }
      
    nivelAguaAgora = sonar.ping_cm();
    Serial.println(nivelAguaAgora);  
    if(nivelAguaAgora != nivelAguaAnterior){
      Serial.println("Teste");
      nivelAguaAnterior != nivelAguaAgora; 

      //Aciona a bomba caso tenha atingido o nivel vazio
      if(nivelAguaAgora >= nivelVazio){
        
        dadosEnvioRF.bombaLigada = true;
        digitalWrite(BOMBA_PIN, HIGH);
        }
        else if(nivelAguaAgora <= nivelCheio){
          dadosEnvioRF.bombaLigada = false;
          digitalWrite(BOMBA_PIN, LOW);
          }
        
      dadosEnvioRF.nivelAgua = nivelAguaAgora;
      
      radio.stopListening();  
      
      if(radio.write(&dadosEnvioRF, sizeof(tipoDadosEnvioRF))){//enviando a informacao
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
     tempoCorrido = millis();
    }
  }
