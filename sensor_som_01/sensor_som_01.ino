const int ledPin = 10;
const int MicroPin = A0;

int level;
const int volume = 150;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(MicroPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  level = analogRead(MicroPin);
 // printf(analogRead(MicroPin));
  if (level > volume){
    // delay (1000);]
    if (digitalRead (ledPin) == HIGH){
    digitalWrite (ledPin, LOW);
    }
  
  else {
    digitalWrite (ledPin, HIGH);
  }
  delay(2000);   
 }
 
}
