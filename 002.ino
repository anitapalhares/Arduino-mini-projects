// C++ code
//
#define LED1 4
#define BOTAO 3
#define TEMPO_LEITURA 100

void setup()
{
	pinMode(LED1, OUTPUT);
  pinMode(BOTAO, INPUT);
}

void loop ()
{
  
 digitalWrite(PIN_LED, HIGH);
  delay(300);
  digitalWrite(PIN_LED, LOW);
  delay(300);
}
