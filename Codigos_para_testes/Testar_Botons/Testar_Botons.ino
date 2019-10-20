#define LED_PIN 13
#define BUT_ACEL_PIN 6
#define BUT_DESAC_PIN 7

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_ACEL_PIN, INPUT);
   pinMode(BUT_DESAC_PIN, INPUT);
   Serial.begin(9600);
   digitalWrite(LED_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int butonAcel = digitalRead(BUT_ACEL_PIN);
  int butonDesac = digitalRead(BUT_DESAC_PIN);

  Serial.print("Valor botao 1 - ");
  Serial.println(butonAcel);
  Serial.print("Valor botao 2 - ");
  Serial.println(butonDesac);
  
  
  if(!butonAcel){
    digitalWrite(LED_PIN, HIGH);
    Serial.println(butonAcel);
    }
    if(!butonDesac){
    Serial.println(butonAcel);  
    digitalWrite(LED_PIN, LOW);
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
