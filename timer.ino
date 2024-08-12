#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define botao1 12
#define botao2 13
#define led 8

#define endereco 0x27
#define colunas 16
#define linhas 2

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

float timer = 0;

// Cria uma variável para evitar o time de reiniciar sozinho após o comando para parar (evita entrar no bloco 'if')
bool verifica_loop = true;

// Variáveis utilizada pela Milis()
unsigned long previousMillis = 0;
const long interval = 20; // 10 = 0.01 seconds

void setup()
{
  pinMode(botao1, INPUT);
  pinMode(botao2, INPUT);
  pinMode(led, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  if (digitalRead(botao1) == 1 && digitalRead(botao2) == 1 && verifica_loop) {
    verifica_loop = false; // Altera a variável para false para evitar de entrar nesse bloco de código após a parada.
    timer = 0;
    delay(150);
    digitalWrite(led, HIGH);

    // Inicia um loop para rodar o timer até que os dois botões sejam pressionados simultaneamente.
    while (!(digitalRead(botao1) == 1 && digitalRead(botao2) == 1)) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        lcd.setCursor(6, 1);
        lcd.print(timer);
        timer = timer + 0.02;
        previousMillis = currentMillis;
      }
    }
    // Retorna a variável 'verifica_loop' para true para permitir que o bloco 'if' rode novamente após a parada.
    verifica_loop = true;
    digitalWrite(led, LOW); 
    delay(150);
  }
}
