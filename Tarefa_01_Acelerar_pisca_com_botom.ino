#define LED_PIN 13
#define BUT_ACEL_PIN 2
#define BUT_DESAC_PIN 4
#define TEMPO_BOUNCE 200
#define habilitaDebugSerial false //define se envia informações do funcionamento para o monitor serial. "true" envia e "false" não envia. Utilizado apenas para debug

int state = 1;
unsigned long old;
int velocPisca = 1000;
int estadoBotaoAcelAnt = 1;
int estadoBotaoDesacAnt = 1;
int estadoBotaoDuploAcelAnt = 1; 
int estadoBotaoDuploDesacAnt = 1;
unsigned long delayBotaoDuplo = 0;
unsigned long temp = 0;

void piscaLed(int velocPisca){
  
  if(millis() >= old+velocPisca){
    old = millis();
    state = !state;
    digitalWrite(LED_PIN, state);
  }
}

//Método usado somente em caso de debug
#if habilitaDebugSerial == true
void debug(String pontoParada, String nomeVariavel1, String valorVariavel1, String nomeVariavel2, String valorVariavel2, int tempoParada) { 
  
  if(millis() - temp >= tempoParada){
    Serial.print("(");
    Serial.print(pontoParada);
    Serial.print(") ");

    Serial.print(nomeVariavel1);  
    Serial.print(":");
    Serial.print(valorVariavel1);    
    Serial.println();

    Serial.print("(");
    Serial.print(pontoParada);
    Serial.print(") ");
    
    Serial.print(nomeVariavel2);  
    Serial.print(":");
    Serial.print(valorVariavel2);    
    Serial.println();
    
    temp = millis();
  }  
}
#endif
//*********************************************************************************************************

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_ACEL_PIN, INPUT);
  pinMode(BUT_DESAC_PIN, INPUT);

 #if habilitaDebugSerial == true
  Serial.begin(9600);
 #endif
}

void loop() {

  int estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
  int estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
  piscaLed(velocPisca);
  

  if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoAcelAnt) ){
      
    #if habilitaDebugSerial == true
    Serial.println("Aumentando pisca led");
    #endif
      
    velocPisca = velocPisca - 100;
    piscaLed(velocPisca);
  }
  
  estadoBotaoAcelAnt = estadoBotaoAcel;
    
  if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDesacAnt) ){

    #if habilitaDebugSerial == true
    Serial.println("Diminuindo pisca led");
    #endif
      
    velocPisca = velocPisca + 100;
    piscaLed(velocPisca);
  }
  
  estadoBotaoDesacAnt = estadoBotaoDesac;

  if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoDuploAcelAnt) ){
    
    delayBotaoDuplo = millis();
    
    while(millis() - delayBotaoDuplo < 500){
     estadoBotaoDesac = digitalRead(BUT_DESAC_PIN);
     piscaLed(velocPisca);
     
     #if habilitaDebugSerial == true
     debug("while", "estadoBotaoDesac", String(!estadoBotaoDesac), "estadoBotaoAcel", String (!estadoBotaoAcel), 0);
     #endif
     
     if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDuploDesacAnt)){
        digitalWrite(LED_PIN, state);
        while(!digitalRead(LED_PIN) || digitalRead(LED_PIN));
      }
    } 
      
  }
  if(!estadoBotaoDesac == HIGH && (estadoBotaoDesac != estadoBotaoDuploDesacAnt) ){
    
    delayBotaoDuplo = millis();
    
    while(millis() - delayBotaoDuplo < 500){
     estadoBotaoAcel = digitalRead(BUT_ACEL_PIN);
     piscaLed(velocPisca);
     
     #if habilitaDebugSerial == true
     debug("while", "estadoBotaoDesac", String(!estadoBotaoDesac), "estadoBotaoAcel", String (!estadoBotaoAcel), 0);
     #endif
     
      if(!estadoBotaoAcel == HIGH && (estadoBotaoAcel != estadoBotaoDuploAcelAnt)){
        digitalWrite(LED_PIN, state);
        while(!digitalRead(LED_PIN) || digitalRead(LED_PIN));
       }
     }  
  }

  estadoBotaoDuploAcelAnt = estadoBotaoAcel; 
  estadoBotaoDuploDesacAnt = estadoBotaoDesac;
}

