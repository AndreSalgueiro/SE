#define LED_PIN 13
#define BUT_PIN 2

int state = 1;
unsigned long old;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    /*digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);*/

  int buton = digitalRead(BUT_PIN);
  /*if(!buton){
    digitalWrite(LED_PIN, HIGH);
    while(1);
  }*/
  
  unsigned long now  = millis();
  if(now >= old+1000){
    old = now;
    state = !state;
    digitalWrite(LED_PIN, state);
  }

  while(!buton){
    digitalWrite(LED_PIN, HIGH);
    }
}
