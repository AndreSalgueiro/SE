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
  /* Serial.println("Entrei no controle de pisca LED");
   Serial.println("millis = ");
   Serial.println(millis());
   Serial.println("controleTempoPiscaLed = ");
   Serial.println(controleTempoPiscaLed);
   Serial.print("velocPisca = ");
   Serial.println(velocPisca);*/
   
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
     /* Serial.println("Botao Acelera estado 1");
      Serial.println(estadoBotaoAcel);
      Serial.println("Botao Acelera anterior estado 1");
      Serial.println(estadoBotaoAcelAnt);
      Serial.println("Botao desacelera estado 1");
      Serial.println(estadoBotaoDesac);
      Serial.println("Botao desacelera anterior estado 1");
      Serial.println(estadoBotaoDesacAnt);*/  
      if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoAcelAnt)){
      /*  Serial.println("Apertei botao acelera LED");
        Serial.println("Botao Acelera estado 1");
        Serial.println(estadoBotaoAcel);
        Serial.println("Botao Acelera anterior estado 1");
        Serial.println(estadoBotaoAcelAnt);*/
        estado_2();
        break;
      }
      if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDesacAnt)){
          Serial.println("Apertei botao desacelera LED");
         /* Serial.println("Botao desacelera estado 1");
          Serial.println(estadoBotaoDesac);
          Serial.println("Botao desacelera anterior estado 1");
          Serial.println(estadoBotaoDesacAnt);
          //estadoBotaoDesacAnt = estadoBotaoDesac;*/
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
     /* estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
      estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
      Serial.println("Botao Acelera estado 2");
      Serial.println(estadoBotaoAcel);
      Serial.println("Botao Acelera anterior estado 2");
      Serial.println(estadoBotaoAcelAnt);
      Serial.println("Botao desacelera estado 2");
      Serial.println(digitalRead(BUT_DESAC_PIN));*/
      if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoAcelAnt)){
        Serial.println("Entrei no metodo aumenta velocidade pisca");
        velocPisca = velocPisca - aux;
        estadoBotaoAcelAnt = estadoBotaoAcel;
        
        //Se estou no estado 2 e cliquei no outro botao vai para o estado final
        if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDesacAnt)){
        estadoBotaoDesacAnt = estadoBotaoDesac;
        estado_4();
        break;
        
      }
      estado_1();
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
      //estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
      //estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
      if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDesacAnt)){
          Serial.println("Entrei no metodo diminui velocidade pisca");
          velocPisca = velocPisca + aux;
          estadoBotaoDesacAnt = estadoBotaoDesac;
          
        //Se estou no estado 2 e cliquei no outro botao vai para o estado final
        if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoAcelAnt)){
        estadoBotaoAcelAnt = estadoBotaoAcel;
        estado_4();
        break;
          
      }
      estado_1();
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
