#include <LiquidCrystal.h> 

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

const int sensor = A0; 
const int buzzer = 8;
const int led = 9;
const int seco = 10;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Hello There");
  delay(3000);
  lcd.clear();

}

void loop() {
  int umidade = analogRead(sensor);
  Serial.print("Umidade: ");
  Serial.println(umidade);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umidade: ");
  lcd.print(umidade);
  lcd.print("%");

  if (umidade < seco) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Solo muito seco, regar");
    } else {

    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Solo umido");
    }
    delay(50);
}