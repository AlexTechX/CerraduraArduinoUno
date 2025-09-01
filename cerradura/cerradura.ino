#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Pines
int botones[4] = {2,3,4,5}; // pulsadores 0-3
int resetPin = 11;
int ledVerde = 8;
int ledRojo = 9;
int buzzer = 10;

// Clave
int clave[4] = {0,1,2,3};
int ingreso[4];
int indice = 0;
int intentos = 0;
bool bloqueado = false;
bool desbloqueado = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ingrese clave:");

  for(int i=0;i<4;i++) pinMode(botones[i], INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Pulsador de reseteo
  if(digitalRead(resetPin) == LOW){
    intentos = 0;
    bloqueado = false;
    desbloqueado = false;
    digitalWrite(buzzer,LOW);
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledRojo,LOW);
    lcd.setCursor(0,1);
    lcd.print("                "); // limpiar línea
    delay(300); // debounce
  }

  // Si está bloqueado, hacer sirena LED + buzzer
  if(bloqueado){
    lcd.setCursor(0,1);
    lcd.print("Botones bloqueados");
    digitalWrite(buzzer,HIGH);
    digitalWrite(ledRojo,HIGH);
    digitalWrite(ledVerde,LOW);
    delay(300);
    digitalWrite(ledRojo,LOW);
    digitalWrite(ledVerde,HIGH);
    delay(300);
    return;
  }

  // Si desbloqueado, mantener LED verde encendido
  if(desbloqueado){
    lcd.setCursor(0,1);
    lcd.print("Desbloqueado   ");
    digitalWrite(ledVerde,HIGH);
    return;
  }

  // Leer botones 0-3
  for(int i=0;i<4;i++){
    if(digitalRead(botones[i]) == LOW){
      ingreso[indice] = i;
      lcd.setCursor(indice,1);
      lcd.print("*");
      indice++;
      delay(300); // debounce

      if(indice == 4){
        verificarClave();
        indice = 0;
        if(!desbloqueado && !bloqueado){
          lcd.setCursor(0,1);
          lcd.print("    "); // limpiar línea
        }
      }
    }
  }
}

void verificarClave(){
  bool correcta = true;
  for(int i=0;i<4;i++){
    if(ingreso[i] != clave[i]){
      correcta = false;
      break;
    }
  }

  if(correcta){
    desbloqueado = true;
    digitalWrite(ledVerde,HIGH);
    digitalWrite(buzzer,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Desbloqueado   ");
    delay(1000);
    digitalWrite(buzzer,LOW);
    intentos = 0;
  } else {
    intentos++;
    digitalWrite(ledRojo,HIGH);
    digitalWrite(buzzer,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Clave Incorrecta");
    delay(1000);
    digitalWrite(ledRojo,LOW);
    digitalWrite(buzzer,LOW);

    if(intentos >= 3){
      bloqueado = true; // activa sirena
    }
  }
}
