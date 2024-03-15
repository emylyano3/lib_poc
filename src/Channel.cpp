#include "Channel.h"

Channel::Channel(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState) {
  init(id, name, pin, pinMode, currState, false, NO_TIMER);
}
Channel::Channel(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState, bool analog) {
  init(id, name, pin, pinMode, currState, analog, NO_TIMER);
}
Channel::Channel(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState, uint32_t timer) {
  init(id, name, pin, pinMode, currState, false, timer);
}
Channel::Channel(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState, bool analog, uint32_t timer) {
  init(id, name, pin, pinMode, currState, analog, timer);
}

void Channel::init(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState, bool analog, uint32_t timer) {
  this->id = id;
  this->pin = pin;
  this->currState = currState;
  this->analog = analog;
  this->timer = timer;
  this->enabled = true;
  this->pinMode = pinMode;
  this->name = new char[CHANNEL_NAME_MAX_LENGTH + 1];
  // This is because if it is an input channel we want timerControl not to be 0 in order to timer check works properly
  this->timerControl = pinMode == OUTPUT ? 0 : timer;
  updateName(name);
}

void Channel::updateName (const char *v) {
  String(v).toCharArray(this->name, CHANNEL_NAME_MAX_LENGTH);
}

void Channel::updateTimerControl() {
  this->timerControl = millis() + this->timer;
}

bool Channel::timeIsUp() {
  return this->timerControl > 0 && millis() > this->timerControl;
}

bool Channel::isEnabled () {
  return this->enabled && this->name != NULL && strlen(this->name) > 0;
}

bool Channel::isOutput() {
  return this->pinMode == OUTPUT;
}

void Channel::write(int value) {
  this->prevState = this->currState;
  if (this->analog) {
    this->currState = value;
    #ifdef LOGGING
    // debug(F("Changing channel state to"), this->currState);
    #endif
    analogWrite(this->pin, this->currState);
  } else {
    if (this->binary) {
      if (value == HIGH) {
        this->updateTimerControl();
      }
      if (this->inverted) {
        value = value == LOW ? HIGH : LOW;
      }
    } 
    this->currState = value;
    #ifdef LOGGING
    // debug(F("Changing channel state to"), this->currState == HIGH ? "[ON]" : "[OFF]");
    #endif
    digitalWrite(this->pin, this->currState);
  }
}

void Channel::setStateMapper(std::function<int(int)> mapper) {
  this->valueMapper = mapper;
}

int Channel::getStateMapped() {
  if (this->valueMapper) {
    return this->valueMapper(this->currState);
  }
  return this->currState;
}

bool Channel::read() {
  this->prevState = this->currState;
  if (this->timeIsUp()) {
    if (this->analog) {
      this->currState = analogRead(this->pin);
    } else {
      int read = digitalRead(this->pin);
      if (this->binary) {
        if (this->inverted) {
          read = read == LOW ? HIGH : LOW;
        }
      }
      this->currState = read;
    }
    this->updateTimerControl();
    return true;
  }
  return false;
}