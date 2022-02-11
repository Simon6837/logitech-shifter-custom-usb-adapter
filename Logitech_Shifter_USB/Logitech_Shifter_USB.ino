
//Logitech Driving Force Shifter USB Adapter
//By Armandoiglesias 2018
//Based on Jason Duncan functionreturnfunction Project
//Video tutorial https://www.youtube.com/watch?v=dLpWEu8kCec
//Use Arduino Leonardo
//Install Joystick Library
//Attribution-NonCommercial-NoDerivatives 4.0 International

#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick;

// H-shifter mode analog axis thresholds
#define HS_XAXIS_12        400
#define HS_XAXIS_56        600
#define HS_YAXIS_135       800
#define HS_YAXIS_246       300

int gear = 0;                 // Default value is neutral

void setup() {
  // G29 shifter analog inputs configuration
  pinMode(A0, INPUT_PULLUP);  // X axis
  pinMode(A2, INPUT_PULLUP);  // Y axis
  pinMode(2, INPUT);          // push stick down
  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  int x = analogRead(0);      // X axis
  int y = analogRead(2);      // Y axis

  int _isreverse = digitalRead(2);
  int _gear_ = 0;

  if ( _isreverse == 1 and x > HS_XAXIS_56 and y < HS_YAXIS_246) {
    _gear_ = 8;
  } else {
    if (x < HS_XAXIS_12)               // Shifter on the left?
    {
      if (y > HS_YAXIS_135) _gear_ = 1;  // 1st gear
      if (y < HS_YAXIS_246) _gear_ = 2;  // 2nd gear
    }
    else if (x > HS_XAXIS_56)          // Shifter on the right?
    {
      if (y > HS_YAXIS_135) _gear_ = 5;  // 5th gear
      if (y < HS_YAXIS_246) _gear_ = 6;  // 6th gear
    }
    else                               // Shifter is in the middle
    {
      if (y > HS_YAXIS_135) _gear_ = 3;  // 3rd gear
      if (y < HS_YAXIS_246) _gear_ = 4;  // 4th gear
    }
  }

  if (_gear_ != gear ) {
    gear = _gear_;
    desactivar();
    Joystick.setButton(gear - 1, HIGH);
  }
}

void desactivar() {
  // Depress virtual button for current gear
  for (int i = 0; i <= 7 ; i++ )  Joystick.setButton(i, LOW);
}
