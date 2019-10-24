#define LDR_PIN A5

int sensorValue;

void setup() {
    pinMode(LDR_PIN, INPUT);
    Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(LDR_PIN);
  
  if(sensorValue > 600){
    Serial.println(sensorValue);
  }
    
}
