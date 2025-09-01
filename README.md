# CerraduraArduinoUno

# Cerradura Electronica con Arduino / Arduino Electronic Lock

## Descripcion / Description

Este proyecto es una cerradura electronica usando Arduino Uno R3, con:
This project is an electronic lock using Arduino Uno R3, with:

- 4 pulsadores para ingresar la clave (0,1,2,3)
  4 buttons to enter the code (0,1,2,3)
- Buzzer activo / Active buzzer
- LEDs verde y rojo / Green and red LEDs
- Display LCD I2C 16x2
- Boton de reset para desbloquear tras 3 intentos fallidos / Reset button to unlock after 3 failed attempts

## Funcionamiento / How it works

- Se ingresa la clave usando los pulsadores.
  The code is entered using the buttons.
- Si la clave es correcta:
  - LED verde encendido / Green LED ON
  - Buzzer suena / Buzzer sounds
  - LCD muestra "Desbloqueado" / LCD shows "Unlocked"
- Si la clave es incorrecta:
  - LED rojo y buzzer un instante / Red LED and buzzer for a short time
  - Se muestran intentos incorrectos / Shows incorrect attempts
- Si se ingresan 3 claves incorrectas:
  - LEDs rojo y verde alternan como sirena / Red and green LEDs alternate like a siren
  - Buzzer suena permanentemente / Buzzer sounds permanently
  - Se presiona boton de reset para volver a intentar / Press reset button to try again

## Archivos / Files

- `cerradura.ino`: codigo principal / main code

## Notas / Notes

- No se incluyen diagramas de conexion / Connection diagrams not included
- Comentarios en el codigo explican paso a paso / Comments in the code explain step by step
