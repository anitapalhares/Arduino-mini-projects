// Atividade Edge 001

int SensorTemp = A2;
int SensorLuz = A3;
int Botao = 12;
int Ilumina = 4;
int Aquece = 2;

int val1 = 0;
int val2 = 0;
int val3 = 0;

void setup() {
  Serial.begin(9600);
  pinMode (SensorTemp ,INPUT); // ENTRADA
  pinMode (SensorLuz ,INPUT);  // ENTRADA
  pinMode (Botao ,INPUT);      // ENTRADA
  pinMode (Ilumina ,OUTPUT);   // SAIDA
  pinMode (Aquece ,OUTPUT);    // SAIDA
}

void loop() {
  val1 = analogRead(SensorTemp); // le o pino de entrada
  float celsius = (val1 * 0.48828125) - 50.0;
  Serial.println("sensor temp: ");
  Serial.println(val1);         // imprime o valor na porta serial
  
  val2 = analogRead(SensorLuz); // le o pino de entrada
  Serial.println("Sensor luz: "); 
  Serial.println(val2);         // imprime o valor na porta serial

  val3 = digitalRead(Botao);    // le pino de entrada
  digitalWrite(Ilumina, val3);  // aciona o LED com o valor lido do botao

  if (val3 == HIGH || val2 < 950) { // se botao aperteado ou maior que 95 
  	digitalWrite(Ilumina, HIGH); // liga
  } else {
  	digitalWrite(Ilumina, LOW);  // desliga
  }
  
  if (celsius < 36){		// se maior liga
  	digitalWrite(Aquece, HIGH); // liga
  }
  if (celsius > 40){		///se enor desliga
    digitalWrite(Aquece, LOW);  // desliga
  }
  delay(2000);					// tempo de 2 segundos
}