class Onchange {
  public:
    Onchange(int pin);

    void ignorefirst();
    void debounce(int debounce_ms);
    void strict(int strict);
    void pullup();
     int changed(int to);

  private:
    int _strict = HIGH;
    int _pin;

    int _debounce_ms = 50;


    int _last_state_low;
    int _last_state_high;

    int _buttonState_low;             
    int _buttonState_high;             

    unsigned long _lastDebounceTime_Low;
    unsigned long _lastDebounceTime_High;

};

Onchange::Onchange(int pin) {
  _pin = pin;
}

void Onchange::pullup()
{
  pinMode(_pin, INPUT_PULLUP);
}
void Onchange::ignorefirst()
{
    _last_state_low = digitalRead(_pin);
    _last_state_high= digitalRead(_pin);

    _buttonState_low= digitalRead(_pin);             
    _buttonState_high= digitalRead(_pin);   
}

void Onchange::strict(int strict)
{
  _strict = strict;
}

int Onchange::changed(int to)
{

  // button value when starting check
  int reading = digitalRead(_pin);



  // Check for pin change for separate HIGH and LOW:

  if (to == HIGH)
  {
    if (reading != _last_state_high) {
      // reset the debouncing timer
      _lastDebounceTime_High = millis();
      // reset the debouncing timer

    }

  }
  if (to == LOW)
  {
    if (reading != _last_state_low) {
      // reset the debouncing timer
      _lastDebounceTime_Low = millis();
      // reset the debouncing timer

    }
  }



  //BEGIN lookout for HIGH value
  if (to == HIGH)
  {
    if ((millis() - _lastDebounceTime_High) > _debounce_ms) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:


      //For strict - only ONCE
      if (_strict == HIGH)
      {
        // if the button state has changed:
        if (reading != _buttonState_high) {
          _buttonState_high = reading;

          //return true only for HIGH
          if (_buttonState_high == to) {
            _last_state_high = reading;
            return HIGH;
          }
        }
      }
      else
      {
        _buttonState_high = reading;

        //return true only for HIGH
        if (_buttonState_high == to) {
          _last_state_high = reading;
          _lastDebounceTime_High = millis();
          return HIGH;
        }
      }

    }
    _last_state_high = reading;

  }
  //END lookout for HIGH value

  //BEGIN lookout for LOW value
  if (to == LOW)
  {
    if ((millis() - _lastDebounceTime_Low) > _debounce_ms) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:


      //For strict - only ONCE
      if (_strict == HIGH)
      {
        // if the button state has changed:
        if (reading != _buttonState_low) {
          _buttonState_low = reading;

          //return true only for LOW
          if (_buttonState_low == to) {
            _last_state_low = reading;
            return HIGH;
          }
        }

      }
      else
      {

        _buttonState_low = reading;

        //return true only for LOW
        if (_buttonState_low == to) {
          _last_state_low = reading;
          _lastDebounceTime_Low = millis();
          return HIGH;
        }
      }
      //For strict




    }
    _last_state_low = reading;

  }
  //END lookout for LOW value

  return LOW;
}
void Onchange::debounce(int debounce_ms)
{
  _debounce_ms = debounce_ms;
}



