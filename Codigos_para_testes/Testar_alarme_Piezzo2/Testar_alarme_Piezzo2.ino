#define PIEZO_PIN 5
int i;
void setup() {
  // put your setup code here, to run once:
pinMode(PIEZO_PIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
for (i=0;i<255;i++){
  digitalWrite(PIEZO_PIN, LOW);
  delay(1);
  digitalWrite(PIEZO_PIN, HIGH);
  delay(1);
}
}
