
#define trigPin 37 // PC4
#define echoPin 36 // PC5

void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly: 

  double dist;
  int dur;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  //
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  //
  dur = pulseIn(echoPin, HIGH);
  delay(10000);
  dist = (dur/58); // [cm]

  //
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.print(" [cm]  ");

  //
  Serial.print((dur/148));
  Serial.print(" [in]");  
  
}
