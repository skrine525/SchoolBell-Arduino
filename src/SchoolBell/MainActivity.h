#ifndef MainActivity_h
#define MainActivity_h

#include <LedControl.h>
#include <Keypad.h>

void Init(); // Аналог setup()
void Main(); // Основная циклическая функция

void controlManager(Keypad &key, LedControl &lc, byte &selectedMode); // Функция управления устройством

#endif
