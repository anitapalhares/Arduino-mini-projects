// ANITA, KAUÃ e VITÓRIA


/* O que é esse projeto? 
- A ideia é que o servomotor faça o papel de mover "placas solares"
  em direção ao "sol", sendo ele o lado mais luminoso 
  identificado pelos 2 fotoresistores.
*/

#include <Servo.h>
// biblioteca

Servo MeuServo;

int SensorLuz1 = A1; 
int SensorLuz2 = A0; 
const int ServoMotor = 9;
int AnguloAtual = 90;
unsigned long Tempo;
unsigned long UltimoTempo = 0; 


void setup() {
  Serial.begin(9600);
  pinMode (SensorLuz1, INPUT);
  pinMode (SensorLuz2, INPUT);
  
  MeuServo.attach(ServoMotor); 
  MeuServo.write(AnguloAtual);
}

void loop() {
  Tempo = millis(); 
  
  if (Tempo - UltimoTempo >= 50) {
    UltimoTempo = Tempo;
    
    int Leitura1 = analogRead(SensorLuz1);
    int Leitura2 = analogRead(SensorLuz2);
    
    Serial.print("Tempo: ");
    Serial.print(Tempo);
    Serial.print(" | Esq (A1): ");
    Serial.print(Leitura1);
    Serial.print(" | Dir (A0): ");
    Serial.print(Leitura2);
    Serial.print(" | Angulo: ");
    Serial.println(AnguloAtual);
    
    int Tolerancia = 15; 
    
    if (Leitura1 - Leitura2 > Tolerancia) {
      if (AnguloAtual < 180) {
        AnguloAtual = AnguloAtual + 2; 
        MeuServo.write(AnguloAtual);
      }
    }
    else if (Leitura2 - Leitura1 > Tolerancia) {
      if (AnguloAtual > 0) { 
        AnguloAtual = AnguloAtual - 1;
        MeuServo.write(AnguloAtual);
      }
    }
  }
}