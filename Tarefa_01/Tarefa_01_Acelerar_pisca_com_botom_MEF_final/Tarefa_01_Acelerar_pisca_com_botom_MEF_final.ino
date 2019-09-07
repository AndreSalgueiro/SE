#define LED_PIN 13
#define BUT_ACEL_PIN 2
#define BUT_DESAC_PIN 4
#define TEMPO_BOUNCE 200
#define habilitaDebugSerial false //define se envia informações do funcionamento para o monitor serial. "true" envia e "false" não envia. Utilizado apenas para debug

//////////////////
//GLOBAIS
/////////////////

int estadoLed = 1; 
int velocPisca = 1000;
int aux = 100;
int estadoBotaoAcelAnt = 1;
int estadoBotaoAcel = 1;
int estadoBotaoDesacAnt = 1;
int estadoBotaoDesac = 1;
int estado = 1;
unsigned long tempoEspera = 500;
unsigned long controleTempoPiscaLed;
unsigned long controleTempBotao;

///////////////////
//ESTADOS
//////////////////

void estado_1(){
 // Serial.println("Entrei metodo estado 1");
  controlePiscaLed();
  estado = 1;
  
}
void estado_2(){
  
  controleTempBotao = millis();
  controlePiscaLed();
  estado = 2;
  
}
void estado_3(){
  
  controleTempBotao = millis();
  controlePiscaLed();
  estado = 3;
  
}
void estado_4(){
  digitalWrite(LED_PIN, estadoLed);
  estado = 4;   
    
}
void controlePiscaLed(){
  // Serial.println("Entrei no controle de pisca LED");
  // Serial.println("millis = ");
  // Serial.println(millis());
   //Serial.println("controleTempoPiscaLed = ");
   //Serial.println(controleTempoPiscaLed);
  // Serial.print("velocPisca = ");
 //  Serial.println(velocPisca);
   
  if(millis() - controleTempoPiscaLed >= velocPisca){
    //Serial.println("Entrei controleTempoPiscaLed");
    if(estadoLed == HIGH){
    //  Serial.println("Entrei no if = HIGH LED");
      estadoLed = LOW;
      digitalWrite(LED_PIN, estadoLed);
    //  Serial.println("Entrei no if - HIGH LED");
   }else if(estadoLed == LOW){
     estadoLed = HIGH;
      digitalWrite(LED_PIN, estadoLed);
   }
   
  controleTempoPiscaLed = millis();
  }
  
}
void setup() {
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_ACEL_PIN, INPUT);
  pinMode(BUT_DESAC_PIN, INPUT);
  digitalWrite(LED_PIN, estadoLed);
  //#if habilitaDebugSerial == true
  Serial.begin(9600);
 // #endif
  
}
//////////////////
//LOOP
/////////////////
void loop() {
 
  //transicao entre estados - Inicia no estado 1
  switch(estado){
    case 1:{
      Serial.println("Estou no estado 1");
      estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
      estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
      Serial.println("Botao Acelera estado 1");
      Serial.println(digitalRead(BUT_ACEL_PIN));
      Serial.println("Botao desacelera estado 1");
      Serial.println(digitalRead(BUT_DESAC_PIN));
        
      if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoAcelAnt)){
        Serial.println("Apertei botao acelera LED");
          estadoBotaoAcelAnt = estadoBotaoAcel;
          estado_2();
          break;
      }
      if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDesacAnt)){
          Serial.println("Apertei botao desacelera LED");
          estadoBotaoDesacAnt = estadoBotaoDesac;
          estado_3();
          break;
      }
      estado_1();
      break;
    }
    case 2:{
      Serial.println("Estou no estado 2");
      estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
      estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
      
      //se eu larguei o botao de acelerar aumenta a velocidade que o led pisca
      if(!estadoBotaoAcel == LOW && (estadoBotaoAcel != estadoBotaoAcelAnt)){
        Serial.println("Entrei no metodo aumenta velocidade pisca");
        velocPisca = velocPisca - aux;
        estadoBotaoAcelAnt = estadoBotaoAcel;
        estado_1();
        break;
        
      }
      //Se estou no estado 2 e cliquei no outro botao vai para o estado final
      if(!estadoBotaoDesac == HIGH && (estadoBotaoDesacAnt != estadoBotaoDesacAnt)){
        estadoBotaoDesacAnt = estadoBotaoDesac;
        estado_4();
        break;
        
      }
      
      //se passou os 500ms deste quando cliquei no botão retorna para estado 1
      if(millis() - controleTempBotao <= tempoEspera){
        estado_1();
        break;
        
      }
      estado_2();
      break;
      
    }
    case 3:{
      Serial.println("Estou no estado 3");
      estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
      estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
    
      //se eu larguei o botao de desacelerar diminui a velocidade que o led pisca
      if(!estadoBotaoDesac == LOW && (estadoBotaoAcel != estadoBotaoDesacAnt)){
          velocPisca = velocPisca + aux;
          estadoBotaoAcelAnt = estadoBotaoAcel;
          estado_1();
          break;
          
        }
      //Se estou no estado 2 e cliquei no outro botao vai para o estado final
      if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoAcelAnt)){
        estadoBotaoDesacAnt = estadoBotaoDesac;
        estado_4();
        break;
          
      }
      
      //se passou os 500ms retorna para estado 1
      if(millis() - controleTempBotao <= tempoEspera){
        estado_1();  
        break;
          
      }
      estado_3();
      break;
    
    }
    case 4:{
      Serial.println("Estado Final");
      break;
            
    }
    
  }
  
}
