#define LED_PIN 13
#define BUT_ACEL_PIN 2
#define BUT_DESAC_PIN 4
#define TEMPO_BOUNCE 200
#define habilitaDebugSerial false //define se envia informações do funcionamento para o monitor serial. "true" envia e "false" não envia. Utilizado apenas para debug

//////////////////
//GLOBAIS
/////////////////

int state = 1;
unsigned long old;
int velocPisca = 1000;
int estadoBotaoAcelAnt = 1;
int estadoBotaoDesacAnt = 1;
int estadoBotaoDuploAcelAnt = 1; 
int estadoBotaoDuploDesacAnt = 1;
unsigned long delayBotaoDuplo = 0;
unsigned long temp = 0;
int estado;
unsigned long t0;

///////////////////
//ESTADOS
//////////////////

void estado_1(unsigned long agora){
  digitalWrite(LED_PIN, HIGH);
  t0 = agora;
  estado = 1
}

void estado_2(unsigned long agora){
    digitalWrite(LED_PIN, LOW);
    t0 = agora;
    estado = 2;
  }

void estado_3(unsigned long agora){
    digitalWrite(LED_PIN, HIGH);
    t0 = agora;
    estado = 3;
  }

void estado_4(unsigned long agora){
    digitalWrite(LED_PIN, LOW);
    t0 = agora;
    estado = 4;    
  }
  
void estado_5(unsigned long agora){
    digitalWrite(LED_PIN, HIGH);
    t0 = agora;
    estado = 5;
  }

void estado_6(unsigned long agora){
    digitalWrite(LED_PIN, LOW);
    t0 = agora;
    estado = 6;
  }

void estado_7(unsigned long agora){
  digitalWrite(LED_PIN, HIGH);
  t0 = agora;
  estado = 7;
  }

void estado_8(){
    digitalWrite(LED_PIN, LOW);
    t0 = agora;
    estado = 8
  }
  
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_ACEL_PIN, INPUT);
  pinMode(BUT_DESAC_PIN, INPUT);

  #if habilitaDebugSerial == true
  Serial.begin(9600);
  #endif
}

//////////////////
//LOOP
/////////////////

void loop() {

}
