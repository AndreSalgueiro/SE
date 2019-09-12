#define LED_PIN 13
#define BUT_ACEL_PIN 2
#define BUT_DESAC_PIN 4
#define TEMPO_BOUNCE 200

//////////////////
//GLOBAIS
/////////////////

int estadoLed = 1; 
int velocPisca = 1000;
int aux = 200;
int estadoBotaoAcelAnt = 1;
int estadoBotaoAcel = 1;
int estadoBotaoDesacAnt = 1;
int estadoBotaoDesac = 1;
int estado = 1;
int estadoBotaoAcelAux = 0;
int estadoBotaoDesacAux = 0;
unsigned long tempoEspera = 500;
unsigned long controleTempoPiscaLed;
unsigned long controleTempBotao;

///////////////////
//ESTADOS
//////////////////

void estado_1(){
  controlePiscaLed();
  estado = 1;
  
}
void estado_2(){
  controlePiscaLed();
  estado = 2;
  
}
void estado_3(){ 
  controlePiscaLed();
  estado = 3;
  
}
void estado_4(){
  digitalWrite(LED_PIN, estadoLed);
  estado = 4;   
    
}
void controlePiscaLed(){
  // Serial.println("Entrei no controle de pisca LED");
   
  if(millis() - controleTempoPiscaLed >= velocPisca){
    if(estadoLed == HIGH){
      estadoLed = LOW;
      digitalWrite(LED_PIN, estadoLed);
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
  Serial.begin(9600);
  
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
      //Serial.println("Botao Acelera estado 1");
    
      if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoAcelAnt)){
      Serial.println("Apertei botao acelera LED");
		    controleTempBotao = millis();
        estadoBotaoAcelAux = HIGH;
        estado_2();
        break;
        
      }
      if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDesacAnt)){
          Serial.println("Apertei botao desacelera LED");
		      controleTempBotao = millis();
          estadoBotaoDesacAux = HIGH;
          estado_3();
          break;
      }
      
      estadoBotaoAcelAnt = estadoBotaoAcel;
      estadoBotaoDesacAnt = estadoBotaoDesac;
      estado_1();
      break;
      
    }
    case 2:{
      Serial.println("Estou no estado 2");
      Serial.println("estadoBotaoAcelAux");
      Serial.println(estadoBotaoAcelAux);

      if(estadoBotaoAcelAux == HIGH ){
        Serial.println("Entrei no 1º if aumenta velocidade pisca");
        estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
        estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
      
         if(!estadoBotaoAcel == LOW){
          Serial.println("Entrei no 2º if aumenta velocidade pisca");
          velocPisca = velocPisca - aux;
          estadoBotaoAcelAnt = estadoBotaoAcel;
          
          estado_1();
          break;
          
         }
         //Se estou no estado 2 e cliquei no outro botao vai para o estado final
         if(!estadoBotaoDesac == HIGH){
          estado_4();
          break;
        
        }
        
      }
      //se passou os 500ms deste quando cliquei no botão retorna para estado 1
      if((millis() - controleTempBotao) >= tempoEspera){
        estadoBotaoAcelAnt = estadoBotaoAcel;
        
        estado_1();
        break;
        
      }
      
      estado_2();
      break;
      
    }
    case 3:{
      Serial.println("Estou no estado 3");
      Serial.println("estadoBotaoDesacAux");
      Serial.println(estadoBotaoDesacAux);
      
      if(estadoBotaoDesacAux == HIGH){
         Serial.println("Entrei no 1º if diminui velocidade pisca");
         estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
         estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
         
         if(!estadoBotaoDesac == LOW){
           Serial.println("Entrei no 2º if diminui velocidade pisca");
           velocPisca = velocPisca + aux;
           estadoBotaoDesacAnt = estadoBotaoDesac;
           
           estado_1();
           break;
           
         }
        //Se estou no estado 2 e cliquei no outro botao vai para o estado final
        if(!estadoBotaoAcel == HIGH){
        
          estado_4();
          break;
  
      }    
    }
    //se passou os 500ms retorna para estado 1
    if((millis() - controleTempBotao) >= tempoEspera){
      estadoBotaoDesacAnt = estadoBotaoDesac;
      
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
