/*
 * Ultrasonic sensor:
  VCC: VBus (+5v)
  GND: Ground
  TrigPin: PC4 37 Black
  EchoPin: PC5 36 Brown
 */

#define TrigPin 37 // PF1
#define EchoPin 36 // PF2

void setup() {
  // put your setup code here, to run once:
    pinMode(EchoPin,INPUT);
    pinMode(TrigPin,OUTPUT);

    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 

  Serial.print(" Getting distance ");
    double distance;
    int duration;
    //
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(TrigPin, LOW);
    duration = pulseIn(EchoPin, HIGH);
    delay(1000);
    distance = ((duration/29)/2);
    //
  Serial.print("distance: ");
  Serial.println(distance);
  
}
