#include <U8glib.h>
#include <RF24.h>
//#include <printf.h>

//#define LED2_PIN 10
//#define DIST_OBSTACULO 15
#define BOTAO_SISTEMA_PIN 6
#define BOTAO_BOMBA_PIN 2

int i =0;
int estadoBotaoSistema = 0;
int estadoBotaoBomba = 0;
int estadoBotaoSistemaAnt = 1;
int estadoBotaoBombaAnt = 1;
int estadoBotaoDesligaAnt = 1;
int start = 0;
int estado = 1;
int estadoAnterior = 1000;
int nivelLiquido = 0;

byte enderecos[][6] = {"1Andre","2Erika"}; 

struct estruturaDadosRF{

  boolean bombaLigadaRF = false;
  boolean dispositivoOperanteRF = false;
  int nivelLiquidoRF = 0;
  boolean botaoBombaAcionadoRF = false;
  boolean botaoControleManualAcionadoRF = false;
  
  };

typedef struct estruturaDadosRF tipoDadosRF;
tipoDadosRF dadosRecebidoRF;
tipoDadosRF dadosEnvioRF;

U8GLIB_ST7920_128X64_1X u8g( 10,  //E
                             9,  //R/W
                             8,  //RS
                             11); //RST

RF24 radio(7,//CE(enable)
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
 // digitalWrite(LED_PIN, LOW);
  start = LOW;
  estado = 0;
  }

void estado_1(){
  start = HIGH;
  //digitalWrite(LED_PIN, HIGH);
  estado = 1;
 }

void estado_2(){
  estado = 2;
}

void estado_3(){
  //Faz algo com a distância aqui?
  estado = 3;
  }

void interrupcaoBotaoBomba();

void setup() {
 
  //pinMode(LED2_PIN, OUTPUT);
  //pinMode(PIEZO_PIN,OUTPUT);
  pinMode(BOTAO_SISTEMA_PIN,INPUT);
  pinMode(BOTAO_BOMBA_PIN,INPUT);

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

   //Configura Interrupcao

  /*LOW acionar a interrupção quando o estado do pino for LOW,
  CHANGE acionar a interrupção quando o sempre estado do pino mudar
  RISING acionar a interrupção quando o estado do pino for de LOW para HIGH apenas,
  FALLING acionar a interrupção quando o estado do pino for de HIGH para LOW apenas.

  Placas Due, Zero e MKR1000 suportam também:
  HIGH acionar a interrupção quando o estado do pino for HIGH.*/
 // attachInterrupt(digitalPinToInterrupt(BOTAO_BOMBA_PIN), interrupcaoBotaoBomba,  RISING);
}

void loop() {
  //delay(700);
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
    //  Serial.println("entrei no estado 1");
      imprimeEstadoAtual(estado);

      /*if(radio.isChipConnected()){
      Serial.println("Dispositivo de radio operante");
      dadosEnvioRF.dispositivoOperanteRF = true;
      }else{
      Serial.println("Dispositivo de radio inoperante");
      dadosEnvioRF.dispositivoOperanteRF = false;
      }*/ 
      
      estadoBotaoSistema = digitalRead(BOTAO_SISTEMA_PIN);
      estadoBotaoBomba = digitalRead(BOTAO_BOMBA_PIN);
      
      if(estadoBotaoSistema != estadoBotaoDesligaAnt){
        estado_0();
        break;
        }

      // radio.startListening();
      
      if(radio.available()){ //verifica se estou recebendo alguma informacao
        radio.read(&dadosRecebidoRF, sizeof(tipoDadosRF));//recebendo dado
        Serial.println("[SUCESSO]- Dados Recebido Medidor Nivel");
        Serial.print("Estatos bomba - " );
        Serial.println(dadosRecebidoRF.bombaLigadaRF);
        Serial.print("Nivel liquido - ");
        Serial.println(dadosRecebidoRF.nivelLiquidoRF);

        estado_2();
      }
        //Monitora botao desligar bomba
        if(estadoBotaoBomba != estadoBotaoBombaAnt){

          dadosEnvioRF.botaoBombaAcionadoRF = true;
          
          if(dadosRecebidoRF.bombaLigadaRF){
            dadosEnvioRF.bombaLigadaRF = false;
            
          }else{
            dadosEnvioRF.bombaLigadaRF = true;
            }

          radio.stopListening();  
        
          if(radio.write(&dadosEnvioRF, sizeof(tipoDadosRF))){//enviando a informacao
            Serial.println("[SUCESSO]-Envio comando desligar/ligar bomba");
          }else{
            Serial.println("[ERROR]-Envio comando desligar/ligar bomba");
          } 
          
          radio.startListening();
        
      } 

        break;
      }
      case 2:{
        imprimeEstadoAtual(estado);
        //chama estado 3 que envia os dados para LCD
         
        Serial.print("Estado botao bomba - ");
        Serial.println(estadoBotaoBomba);
        Serial.print("Estado botao bomba ANTERIOR - ");
        Serial.println(estadoBotaoBombaAnt);
        
        //Dados Display
        nivelLiquido = dadosRecebidoRF.nivelLiquidoRF;
        Serial.println("################");
        Serial.println("////////////////");
        Serial.println("///Dados Display////");
        Serial.println("////////////////");
        Serial.print("Nivel de liquido no reservatorio - ");
        Serial.println(nivelLiquido);
        Serial.print("Estato da bomba - ");
        Serial.println(dadosRecebidoRF.bombaLigadaRF);
        Serial.println("################");
        
        estado_1();
        break;
      }
      case 3:{
        imprimeEstadoAtual(estado);
        //break;
          
       }
  }
}
//Aciona bomba ao precioanar botao utilizando interrupcao
void interrupcaoBotaoBomba(){
  
  Serial.print("Disparei Interrupcao botao liga/desliga Bomba - ");
  
  if(dadosRecebidoRF.bombaLigadaRF){
    dadosEnvioRF.bombaLigadaRF = false;
  }else{
    dadosEnvioRF.bombaLigadaRF = true;
  }
  Serial.println(dadosEnvioRF.bombaLigadaRF);
  
  }
