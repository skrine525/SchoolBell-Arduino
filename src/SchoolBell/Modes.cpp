#include <LedControl.h> // Библиотека управления дисплеем
#include "Modes.h" // Библиотека для управления временем

ClockMode::ClockMode(/*unsigned long timestamp,*/ bool animation){
  //this->timestamp = timestamp;
  //this->lastTimestamp = 0;
  this->animationEnabled = animation;
  this->animationStep = 0;
}

bool ClockMode::draw(LedControl &lc, unsigned long timestamp){
  bool result = false;
	if(timestamp != this->timestamp){
      this->timestamp = timestamp;
      Serial.println(this->timestamp);
		  unsigned long time = this->timestamp % 86400; // Время в секундах начиная с 00:00
	  	unsigned int hours, minutes, seconds, dozens, units; // Переменные: часы, минуты, секунды, десятки и единцы соответственно

	  	seconds = time % 60; // Расчитываем секунды
	  	minutes = (time % 3600) / 60; // Расчитываем минуты
	  	hours = time / 3600; // Расчитываем часы

	  	// Отображаем часы
	  	units = hours % 10;
	  	dozens = (hours - units) / 10;
	  	lc.setDigit(0, 1, dozens, false);
	  	lc.setDigit(0, 2, units, true);

	  	// Отображаем минуты
	  	units = minutes % 10;
	 	  dozens = (minutes - units) / 10;
	  	lc.setDigit(0, 3, dozens, false);
		  lc.setDigit(0, 4, units, true);

		  // Отображаем минуты
	  	units = seconds % 10;
	  	dozens = (seconds - units) / 10;
	  	lc.setDigit(0, 5, dozens, false);
		  lc.setDigit(0, 6, units, false);

		  result = true;
	}
  if(this->animationEnabled)
        drawAnimation(lc);
	return result;
}

void ClockMode::drawAnimation(LedControl &lc){
  unsigned long uptime = millis();
  if(uptime - this->lastAnimationUpdateTime >= 40){
    this->lastAnimationUpdateTime = uptime;

    switch(this->animationStep){
      case 1:
      lc.setLed(0, 7, 1, false);
      lc.setLed(0, 7, 2, true);
      break;

      case 2:
      lc.setLed(0, 7, 2, false);
      lc.setLed(0, 7, 3, true);
      break;

      case 3:
      lc.setLed(0, 7, 3, false);
      lc.setLed(0, 7, 4, true);
      break;

      case 4:
      lc.setLed(0, 7, 4, false);
      lc.setLed(0, 0, 4, true);
      break;

      case 5:
      lc.setLed(0, 0, 4, false);
      lc.setLed(0, 0, 5, true);
      break;

      case 6:
      lc.setLed(0, 0, 5, false);
      lc.setLed(0, 0, 6, true);
      break;

      case 7:
      lc.setLed(0, 0, 6, false);
      lc.setLed(0, 0, 1, true);
      break;

      default:
      lc.setLed(0, 0, 1, false);
      lc.setLed(0, 7, 1, true);
      this->animationStep = 0;
    }
    this->animationStep++;
  }
}
