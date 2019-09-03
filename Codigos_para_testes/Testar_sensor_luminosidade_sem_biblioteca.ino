#define uint8_t trig_pin = 10;
#define  uint8_t echo_pin = 9;
 
uint32_t print_timer;
 
void setup() {
  Serial.begin(9600); // Habilita Comunicação Serial a uma taxa de 9600 bauds.
 
  // Configuração do estado inicial dos pinos Trig e Echo.
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
}
 
void loop() {
  // Espera 0,5s (500ms) entre medições.
  if (millis() - print_timer > 500) {
    print_timer = millis();
   
    // Pulso de 5V por pelo menos 10us para iniciar medição.
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(11);
    digitalWrite(trig_pin, LOW);
     
    /* Mede quanto tempo o pino de echo ficou no estado alto, ou seja,
    o tempo de propagação da onda. */
    uint32_t pulse_time = pulseIn(echo_pin, HIGH);
     
    /* A distância entre o sensor ultrassom e o objeto será proporcional a velocidade
    do som no meio e a metade do tempo de propagação. Para o ar na
    temperatura ambiente Vsom = 0,0343 cm/us. */
    double distance = 0.01715 * pulse_time;
     
    // Imprimimos o valor na porta serial;
    Serial.print(distance);
    Serial.println(" cm");
  }
}