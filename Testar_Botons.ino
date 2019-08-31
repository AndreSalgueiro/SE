#define LED_PIN 13
#define BUT_ACEL_PIN 2
#define BUT_DESAC_PIN 4

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_ACEL_PIN, INPUT);
   pinMode(BUT_DESAC_PIN, INPUT);
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int butonAcel = digitalRead(BUT_ACEL_PIN);
  int butonDesac = digitalRead(BUT_DESAC_PIN);
  
  if(!butonAcel){
    digitalWrite(LED_PIN, HIGH);
    Serial.println(butonAcel);
    }
    if(butonAcel){
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
