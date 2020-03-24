#ifndef Modes_h
#define Modes_h

#include <LedControl.h> // Библиотека управления дисплеем

class ClockMode{
private:
	unsigned long timestamp;
  //unsigned long lastTimestamp;

  // Анимация
  bool animationEnabled;
  byte animationStep;
  unsigned long lastAnimationUpdateTime;

  void drawAnimation(LedControl &lc);

public:

  ClockMode(/*unsigned long timestamp, */bool animation); // Конструктор
	bool draw(LedControl &lc, unsigned long timestamp); // Функция отрисовки времени на дисплее
};

#endif
