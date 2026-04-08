#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define ALTURA_RECIPIENTE 19 
#define LARGURA_RECIPIENTE 9.2 
#define COMPRIMENTO_RECIPIENTE 8.4
#define VEL_SOM 0.034

const int trig = 5;
const int echo = 18;
float distancia, volume_agua, volume_vazio;
const float volume_total = ALTURA_RECIPIENTE * LARGURA_RECIPIENTE * COMPRIMENTO_RECIPIENTE;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  
  lcd.init();
  lcd.backlight();

  lcd.print("=Nivel de agua=");
  lcd.setCursor(0,1);
  lcd.print("Nivel: ");
  
}

void loop() {

  distancia = calcula_distancia(trig, echo);
  //Serial.println(distancia);
  
  //emcm³
  //volume_vazio = distancia * PERIMETRO;
  volume_vazio = distancia * LARGURA_RECIPIENTE * COMPRIMENTO_RECIPIENTE;

  //em mL
  volume_agua = ((volume_total - volume_vazio)/1000) < 0 ? 0 : (volume_total - volume_vazio)/1000;

  Serial.println(volume_agua);

  lcd.setCursor(7, 1);
  lcd.print(volume_agua);
  lcd.setCursor(11, 1);
  lcd.print(" L");
  delay(100);
  

}

float calcula_distancia (int trig, int echo){

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int duracao = pulseIn(echo, HIGH);
  float distancia = (duracao * (VEL_SOM / 2))+0.1;

  return distancia;
}
