int i =0;
void setup() {
Serial.begin(9600);
pinMode(5,OUTPUT);

}

void loop() {
for (i=0;i<25;i++){
analogWrite(5,i);
delay(5);
}
/*for (i=255;i>-1;i--){
analogWrite(5,i);
delay(5);
}*/

}
