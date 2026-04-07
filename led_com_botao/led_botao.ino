// C++ code
// Botão led
#define LED1 4
#define BOTAO 3
#define TEMPO_LEITURA 100

void setup()
{
  pinMode(BOTAO, INPUT);
  pinMode(LED1, OUTPUT);
}

void loop ()
{
  digitalWrite(PIN_LED, HIGH);
  delay(300);
  digitalWrite(PIN_LED, LOW);
  delay(300);
}
