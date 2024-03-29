#define ledPin 13


void setup()

{

  pinMode(ledPin, OUTPUT);

  

  // initialize timer1 

 // noInterrupts();           // disable all interrupts

  TCCR1A = 0;

  TCCR1B = 0;

  TCNT1  = 0;


  OCR1A = 31250;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler 

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

 // interrupts();             // enable all interrupts

}


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine

{

  PORTB ^= (1 << PINB5);   // toggle LED pin

}


void loop()

{

  delay(9000);

}
