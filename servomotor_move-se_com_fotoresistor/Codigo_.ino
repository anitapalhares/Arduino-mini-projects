/* O que é esse projeto? 
- A ideia é que o servomotor faça o papel de mover "placas solares"
  em direção ao "sol", sendo ele o lado mais luminoso 
  identificado pelos 2 fotoresistores.
*/

#define RS 12
#define E 7
#define Erro1_ADDR 0x0A
#define Erro2_ADDR 0x0B

#include <EEPROM.h>
#include <Servo.h>
#include <LiquidCrystal.h>
// bibliotecas

LiquidCrystal lcd(RS, E, 5, 4, 3, 2);

Servo MeuServo;

int SensorLuz1 = A1; 
int SensorLuz2 = A0; 
const int ServoMotor = 9;
int AnguloAtual = 90;
unsigned long Tempo;
unsigned long UltimoTempo = 0; 

uint8_t Cont_Erro1;
uint8_t Cont_Erro2;

uint8_t Register_Erro1 = false;
uint8_t Register_Erro2 = false;

void setup() {
  Serial.begin(9600);
  pinMode (SensorLuz1, INPUT);
  pinMode (SensorLuz2, INPUT);
  
  MeuServo.attach(ServoMotor); 
  MeuServo.write(AnguloAtual);
  
  lcd.begin(16,2);
  
  Cont_Erro1 = EEPROM.read(0x0A);
  Serial.println("Contador erro de numeros de erro do sensor 1: ");
  Serial.println(Cont_Erro1);
  Serial.println("----------------------------------------------");
  Cont_Erro1 = EEPROM.read(0x0B);
  Serial.println("Contador erro de numeros de erro do sensor 2: ");
  Serial.println(Cont_Erro2);
  Serial.println("----------------------------------------------");
}

void loop() {
  Tempo = millis(); 
  
  int Erro1 = false;
  int Erro2 = false;
  
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
    Serial.print(" |Angulo: ");
    Serial.println(AnguloAtual);
   
    int Tolerancia = 15; 
    
    if ( Leitura1 > 679 || Leitura1 < 6 ){
      if (!Register_Erro1) {
        lcd.setCursor(0,0);
      	lcd.write("Erro Leitura 1");	
        Cont_Erro1++;
        EEPROM.write(0x0A, Cont_Erro1);
        Register_Erro1 = true;
      }
     Erro1 = true;
    }

    if ( Leitura2 > 679 || Leitura2 < 6 ){
    	if (!Register_Erro2) {
         lcd.setCursor(0,1);
      	lcd.write("Erro Leitura 2");	
        Cont_Erro2++;
        EEPROM.write(0x0B, Cont_Erro2);
        Register_Erro2 = true;
      }
      Erro2 = true;
    }
    
    if (Erro1 == true || Erro2 == true){
      MeuServo.write(90); 
    } else {
      lcd.clear();
      lcd.write("GS");
      if (Leitura1 - Leitura2 > Tolerancia) {
          if (AnguloAtual < 180) {
            AnguloAtual = AnguloAtual + 2; 
            MeuServo.write(AnguloAtual);
          }
        }
        else if (Leitura2 - Leitura1 > Tolerancia) {
          if (AnguloAtual > 0) { 
            AnguloAtual = AnguloAtual - 2;
            MeuServo.write(AnguloAtual);
          }
        }
    }
  }
}