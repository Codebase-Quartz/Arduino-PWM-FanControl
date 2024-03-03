//Use pins 9 and 10 for PWM signal
//Connect potentiometer to pin A0 and supply with 5v


int timer;            // timer variable for led delay

int potPin = 7;       // analog input pin that the potentiometer is attached to
int potValue = 0;     // value read from the pot

const word pwmA = 9;  // sets pin 9 with variable
const word pwmB = 10; // sets pin 10 with variable

void setup() {
  //Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(pwmA, OUTPUT); //pwmA
  pinMode(pwmB, OUTPUT); //pwmB

  TCCR1A = 0;            //clear timer registers
  TCCR1B = 0;
  TCNT1 = 0;

  TCCR1B |= _BV(CS10);   //no prescaler
  ICR1 = 320;            //PWM mode counts up 320 then down 320 counts (25kHz)

  OCR1A = pwmA;          //0-320 = 0-100% duty cycle
  TCCR1A |= _BV(COM1A1); //output A clear rising/set falling

  OCR1B = pwmB;          //0-320 = 0-100% duty cycle
  TCCR1A |= _BV(COM1B1); //output B clear rising/set falling

  TCCR1B |= _BV(WGM13);  //PWM mode with ICR1 Mode 10
  TCCR1A |= _BV(WGM11);  //WGM13:WGM10 set 1010
}

void loop() {

  potValue = analogRead(potPin);             // read the pot value
  potValue = map(potValue, 0, 1023, 0, 255); //Map value 0-1023 to 0-255 (PWM)
  
  analogWrite(pwmA, potValue);      // PWM the LED with the pot value (divided by 4 to fit in a byte)
  analogWrite(pwmB, potValue);      // PWM the LED with the pot value (divided by 4 to fit in a byte)

  //Serial.print("Potentiometer");
  //Serial.println(potValue);         // print the pot value back to the debugger pane
  //Serial.println(" ");
  //Serial.print("Timer");
  //Serial.println(timer);            // print the timer value to the debugger pane

  timer = map(0, 0, 255, 255, 0);   // maps values to reverse variable
  timer = 255 - potValue;           // applies reversed value to variable (timer)
  
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(timer);                     // delay for variable in (timer)
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(timer);                     // delay for variable in (timer)
}
