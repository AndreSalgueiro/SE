#define LED_PIN 13
#define BUT_CONTROLE_MANUAL_PIN A0
#define BUT_BOMBA_PIN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_CONTROLE_MANUAL_PIN, INPUT);
   pinMode(BUT_BOMBA_PIN, INPUT);
   Serial.begin(9600);
   digitalWrite(LED_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int butonControleManual = analogRead(BUT_CONTROLE_MANUAL_PIN);
  int butonBomba = digitalRead(BUT_BOMBA_PIN);

  Serial.print("Valor botao CONTROLE MANUAL - ");
  Serial.println(butonControleManual);
  Serial.println();
  Serial.print("Valor botao BOMBA - ");
  Serial.println(butonBomba);
  Serial.println();
  
  
  if(!butonControleManual){
   // digitalWrite(LED_PIN, HIGH);
   Serial.print("Apertei botao CONTROLE MANUAL -  ");
    Serial.println(butonControleManual);
    }
    if(!butonBomba){
    Serial.print("Apertei botao BOMBA -  ");
    Serial.println(butonBomba);
    }
    
 /* if(!butonDesac){
    digitalWrite(LED_PIN, HIGH);
    Serial.println(butonDesac);
    }
  if(butonDesac){
    digitalWrite(LED_PIN, LOW);
    Serial.println(butonDesac);
    }*/
  
}
