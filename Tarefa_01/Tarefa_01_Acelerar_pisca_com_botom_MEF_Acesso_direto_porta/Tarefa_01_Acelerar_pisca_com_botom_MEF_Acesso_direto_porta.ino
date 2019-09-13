//#define LED_PIN 13
//#define BUT_ACEL_PIN 2
//#define BUT_DESAC_PIN 4
//#define TEMPO_BOUNCE 200

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
  //digitalWrite(LED_PIN, estadoLed);
  if(estadoLed == LOW){
    // digitalWrite(LED_PIN, estadoLed);
    PORTB &= ~(1 << 5);//porta 13
   }else if(estadoLed == HIGH){
     //digitalWrite(LED_PIN, estadoLed);
     PORTB |= 1 << 5;//porta 13
   }
  estado = 4;   
    
}
void controlePiscaLed(){
  // Serial.println("Entrei no controle de pisca LED");
   
  if(millis() - controleTempoPiscaLed >= velocPisca){
    if(estadoLed == HIGH){
      estadoLed = LOW;
     // digitalWrite(LED_PIN, estadoLed);
     PORTB &= ~(1 << 5);//porta 13
   }else if(estadoLed == LOW){
     estadoLed = HIGH;
      //digitalWrite(LED_PIN, estadoLed);
      PORTB |= 1 << 5; //porta 13
   }
   
  controleTempoPiscaLed = millis();
  }
  
}
void setup() {
  
  //pinMode(LED_PIN, OUTPUT);
  DDRB |= 1 << 5; //porta 13
  //pinMode(BUT_ACEL_PIN, INPUT);
  DDRD &= ~(1 << 2); //porta 2
  //pinMode(BUT_DESAC_PIN, INPUT);
  DDRD &= ~(1 << 4);//porta 4
  //digitalWrite(LED_PIN, estadoLed);
  PORTB |= estadoLed << 5; //porta 13
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
      
      estadoBotaoAcel = PIND & (1 << 2);//digitalRead(BUT_ACEL_PIN);
      estadoBotaoDesac = PIND & (1 << 4);//digitalRead(BUT_DESAC_PIN);
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
     
      if(estadoBotaoAcelAux == HIGH ){
        Serial.println("Entrei no 1º if aumenta velocidade pisca");
        estadoBotaoAcel = PIND & (1 << 2);//digitalRead(BUT_ACEL_PIN);
        estadoBotaoDesac = PIND & (1 << 4);//digitalRead(BUT_DESAC_PIN);
        
         //Se estou no estado 2 e soltei o botão de acelera
         if(!estadoBotaoAcel == LOW){
          Serial.println("Entrei no 2º if aumenta velocidade pisca");
          velocPisca = velocPisca - aux;
          estadoBotaoAcelAnt = estadoBotaoAcel;
          
          estado_1();
          break;
          
         }
         //Se estou no estado 2 e cliquei no outro botao vai para o estado final
         if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDesacAnt)){
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
      
      if(estadoBotaoDesacAux == HIGH){
         Serial.println("Entrei no 1º if diminui velocidade pisca");
         estadoBotaoAcel = PIND & (1 << 2);//digitalRead(BUT_ACEL_PIN);
         estadoBotaoDesac = PIND & (1 << 4);//digitalRead(BUT_DESAC_PIN);
         
         //Se estou no estado 2 e soltei o botão de desacelera
         if(!estadoBotaoDesac == LOW){
           Serial.println("Entrei no 2º if diminui velocidade pisca");
           velocPisca = velocPisca + aux;
           estadoBotaoDesacAnt = estadoBotaoDesac;
           
           estado_1();
           break;
           
         }
        //Se estou no estado 2 e cliquei no outro botao vai para o estado final
        if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoAcelAnt)){
        
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
