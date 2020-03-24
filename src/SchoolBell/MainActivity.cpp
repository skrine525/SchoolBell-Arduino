#include <LedControl.h> // Библиотека управления дисплеем
#include <Keypad.h> // Библиотека для Keypad'а
//#include "TimeManager.h" // Библиотека для отображения времени на дисплее
#include "Modes.h" // Заголовочный файл, описывающий режимы устройства
#include "MainActivity.h" // Основной заголовочный файл

LedControl lc = LedControl(13,12,11,1); // Объект управления дисплеем
/*
 * PIN 13 - DataIn
 * PIN 12 - CLC
 * PIN 11 - LOAD
*/

////////////////////////////////////////////////////////////////////////////////////////////
/// Настройка Keypad'а
#define KEYPAD_ROWS 4 // Константа кол-ва рядов
#define KEYPAD_COLS 4 // Константа кол-ва столбцов

// Карта символов Keypad'а
char hexaKeys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[KEYPAD_ROWS] = {9, 8, 7, 6}; // Пины рядов
byte colPins[KEYPAD_COLS] = {5, 4, 3, 2}; // Пины столбцов

Keypad key = Keypad(makeKeymap(hexaKeys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS); // Объект управления Keypad'ом

////////////////////////////////////////////////////////////////////////////////////////////

unsigned long timestamp = 36000;
unsigned long lastUpdateTime = millis();
ClockMode clockMode(/*timestamp, */true); // Объект управления 1-ым режимом устройства

byte selectedMode = 0; // Выбранный режим устройства
#define NUMBER_OF_MODES 3 // Количесво режимов устройства

void Init(){
  lc.shutdown(0, false);
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);
  Serial.begin(9600);
}

void Main(){
  unsigned int uptime = millis();
  if(uptime - lastUpdateTime >= 1000){
    lastUpdateTime = uptime;
    timestamp++;
  }
  
  switch(selectedMode){
    case 0:
    clockMode.draw(lc, timestamp);
    break;

    case 1:
    lc.setDigit(0, 3, 0, false);
    lc.setDigit(0, 4, 2, false);
    break;

    case 2:
    lc.setDigit(0, 3, 0, false);
    lc.setDigit(0, 4, 3, false);
    break;
  }
  controlManager(key, lc, selectedMode);
}

void controlManager(Keypad &key, LedControl &lc, byte &selectedMode){
  char ch = key.getKey();
  if(ch == 'A'){
    // Смена режима устройства
    lc.clearDisplay(0);
    selectedMode++;
    if(selectedMode >= NUMBER_OF_MODES)
      selectedMode = 0;
  }
  else if(ch != NO_KEY){
    Serial.println(ch);
  }
}
