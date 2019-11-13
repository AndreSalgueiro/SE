#include <U8glib.h>
#include <RF24.h>
//#include <printf.h>

//#define LED2_PIN 10
//#define DIST_OBSTACULO 15
#define BOTAO_SISTEMA_PIN 6
#define BOTAO_BOMBA_PIN 2
#define BOTAO_CONTROLE_MANUAL_PIN A0
#define POTENCIOMETRO_PIN A1
//#define LED_PIN_5 5

int i =0;
int estadoBotaoSistema = 0;
int estadoBotaoBomba = 0;
int estadoBotaoSistemaAnt = 1;
int estadoBotaoBombaAnt = 1;
int estadoBotaoDesligaAnt = 1;
int start = 0;
int estado = 1;
int estadoAnterior = 1000;
int botaoControleManualAcionado = 1;
//int nivelLiquido = 0;
int alturaReservatorio = 30;//30cm
int nivelCheio = 10;//10cm
int nivelVazio = alturaReservatorio - nivelCheio;//10cm
int botaoControleManualAcionadoAnterior = 1;
int refinoNivelBaixoAnterior = 10;
boolean controleManualAcionado = false;
boolean estadoControleManualAlterado = false;
char nivelLiquidoDisplay [5];
char refinoNivelBaixoDisplay [5];
const char *controleManualDisplay = "";
const char *estadoBombaDisplay = ""; 

byte enderecos[][7] = {"1Nody","2Nody"}; 

struct estruturaDadosRF{

  int nivelLiquidoRF = 0;
  int refinoNivelBaixoRF = 10;
  boolean bombaLigadaRF = false;
  boolean dispositivoOperanteRF = false;
  boolean botaoBombaAcionadoRF = false;
  boolean controleManualAcionadoRF = false;
  };

typedef struct estruturaDadosRF tipoDadosRF;
tipoDadosRF dadosRecebidoRF;
tipoDadosRF dadosEnvioRF;

U8GLIB_ST7920_128X64_1X u8g( 10,  //E (6)
                             9,  //R/W (5)
                             8,  //RS (4)
                             4); //RST (7)

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
  pinMode(BOTAO_CONTROLE_MANUAL_PIN, INPUT);
  pinMode(POTENCIOMETRO_PIN, INPUT);
  
 // digitalWrite(LED_PIN_5, LOW);

  Serial.begin(9600); 
  //printf_begin();

  u8g.setFont(u8g_font_courB10); //seleciona fonte Display
  u8g.setColorIndex(1);            //desenhar com pixels on

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
      botaoControleManualAcionado = digitalRead(BOTAO_CONTROLE_MANUAL_PIN);
      dadosEnvioRF.refinoNivelBaixoRF = analogRead(POTENCIOMETRO_PIN);
      //Alterando escala potenciometro
      dadosEnvioRF.refinoNivelBaixoRF = map(dadosEnvioRF.refinoNivelBaixoRF,0,981,40,20);
      Serial.print("Potenciometro = ");
      Serial.println(dadosEnvioRF.refinoNivelBaixoRF);
      //lendo o potenciometro
      
      if(estadoBotaoSistema != estadoBotaoDesligaAnt){
        estado_0();
        break;
        }

      // radio.startListening();
      //Recebe dados do estado 3
      if(radio.available()){ //verifica se estou recebendo alguma informacao
        radio.read(&dadosRecebidoRF, sizeof(tipoDadosRF));//recebendo dado
        Serial.println("[SUCESSO]- Dados Recebido Medidor Nivel");
       // Serial.print("Estatos bomba - " );
        //Serial.println(dadosRecebidoRF.bombaLigadaRF);
        //Serial.print("Nivel liquido - ");
        //Serial.println(dadosRecebidoRF.nivelLiquidoRF);

        estado_2();
      }
        //Monitora botao controle manual bomba
        if(botaoControleManualAcionado == HIGH && (botaoControleManualAcionado != botaoControleManualAcionadoAnterior) ){
         
          //Se já estava no controle manual entao desliga
          if(controleManualAcionado){
            controleManualAcionado = false;
          
          //Se nao estava no controle manual entao entre no modo liga/desliga bomba manual  
          }else{
            controleManualAcionado = true;
             }

             dadosEnvioRF.controleManualAcionadoRF = controleManualAcionado;
             estadoControleManualAlterado = true;
          }

          botaoControleManualAcionadoAnterior = botaoControleManualAcionado;

        Serial.print("Controle MANUAL foi alterado? = ");
        Serial.println(estadoControleManualAlterado);
        
        if(estadoControleManualAlterado){
        //  digitalWrite(LED_PIN_5, HIGH);
          
          if(controleManualAcionado){
            
            //Enquanto estiver no controle MANUAL monitora o botao de liga/desliga bomba
            if(estadoBotaoBomba == HIGH && (estadoBotaoBomba != estadoBotaoBombaAnt) ){
              Serial.println("Acionei botao bomba");
              dadosEnvioRF.botaoBombaAcionadoRF = true;

              //Se a bomba estava ligada entao desliga
              if(dadosRecebidoRF.bombaLigadaRF){
                dadosEnvioRF.bombaLigadaRF = false;
                
              //Se a bomba estava desligada entao liga  
              }else{
                dadosEnvioRF.bombaLigadaRF = true;
                }
            }

            estadoBotaoBombaAnt = estadoBotaoBomba;
            
          }
          //So envia dados para o medidor de nivel se houve acionamento do controle manual
          radio.stopListening();  
          //Envia dados ao Estado 3
          if(radio.write(&dadosEnvioRF, sizeof(tipoDadosRF))){//enviando a informacao
            Serial.println("[SUCESSO]-Envio comando desligar/ligar bomba");
          }else{
            Serial.println("[ERROR]-Envio comando desligar/ligar bomba");
          } 
          radio.startListening();

          if(controleManualAcionado == false){
              estadoControleManualAlterado = false;
            }
        }else if(dadosEnvioRF.refinoNivelBaixoRF != refinoNivelBaixoAnterior){
         
          //Se hove alteracao no potenciometro
          radio.stopListening();  
          
          if(radio.write(&dadosEnvioRF, sizeof(tipoDadosRF))){//enviando a informacao
            Serial.println("[SUCESSO]-Envio comando desligar/ligar bomba");
          }else{
            Serial.println("[ERROR]-Envio comando desligar/ligar bomba");
          } 
          radio.startListening();
          
          refinoNivelBaixoAnterior = dadosEnvioRF.refinoNivelBaixoRF;
          
          }
        break;
      }
      case 2:{
        imprimeEstadoAtual(estado);
        //chama estado 3 que envia os dados para LCD
         
      //  Serial.print("Estado botao bomba - ");
      //  Serial.println(estadoBotaoBomba);
      //  Serial.print("Estado botao bomba ANTERIOR - ");
      //  Serial.println(estadoBotaoBombaAnt);
      
        if(dadosRecebidoRF.bombaLigadaRF){
           estadoBombaDisplay = "ON";
          }else{
            estadoBombaDisplay = "OFF";
            }

         if(controleManualAcionado){
            controleManualDisplay= "ON";
          }else{
            controleManualDisplay = "OFF";
            }
          
        //Dados Display
        Serial.println("################");
        Serial.println("////////////////");
        Serial.println("///Dados Display////");
        Serial.println("////////////////");
        Serial.print("Nivel de liquido no reservatorio - ");
        Serial.println(dadosRecebidoRF.nivelLiquidoRF);
        Serial.print("Estato da bomba - ");
        Serial.println(dadosRecebidoRF.bombaLigadaRF);
        Serial.print("Controle manual ativado = ");
        Serial.println(controleManualAcionado);
        Serial.print("Nivel Vazio = ");
        Serial.println(dadosEnvioRF.refinoNivelBaixoRF);
        Serial.println("################");

        
        u8g.firstPage();
        do {   
         desenhar();
        } while( u8g.nextPage() );

        
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

  void desenhar(){

   u8g.drawFrame(0,0,127,42);            //desenha retângulo superior
   u8g.drawFrame(0,44,127,20);           //desenha retângulo inferior

   // converte float para strings char u8g
   u8g.drawStr(5, 13, "Manual");       //mostra temperatura
   u8g.drawStr(60, 13, "-");
   //dtostrf(controleManualAcionadoDisplay, 3, 1, controleManualDisplay);
   u8g.drawStr(74,13, controleManualDisplay);
  // u8g.drawStr(70,27, " C");

  // converte float para strings char u8g
   u8g.drawStr(5, 26, "Bomba");       //mostra temperatura
   u8g.drawStr(60, 26, "-");
   //dtostrf(bombaLigadaDisplay, 3, 1, estadoBombaDisplay);
   u8g.drawStr(74,26, estadoBombaDisplay);
  // u8g.drawStr(70,27, " C"); 

   // converte float para strings char u8g
   u8g.drawStr(5, 39, "Vazio");       //mostra temperatura
   u8g.drawStr(60, 39, "-");
   dtostrf(dadosEnvioRF.refinoNivelBaixoRF, 3, 1, refinoNivelBaixoDisplay);
   u8g.drawStr(74,39, refinoNivelBaixoDisplay);

   u8g.drawStr(5,58, "Nivel"); 
   u8g.drawStr(60, 58, "-");//mostra umidade
   dtostrf(dadosRecebidoRF.nivelLiquidoRF, 3, 1, nivelLiquidoDisplay);
   u8g.drawStr(74,58, nivelLiquidoDisplay);
   //u8g.drawStr(75,60, "%");
   /*
   char nivelLiquidoDisplay = "";
char controleManualDisplay = "";
char estadoBombaDisplay = ""; */

    }
