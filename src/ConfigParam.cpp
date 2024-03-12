#include "ConfigParam.h"

ConfigParam::ConfigParam (InputType type, const char* name, const char* label, const char* defVal, uint8_t length, const char* html) {
  _type = type;
  _name = name;
  _label = label;
  _customHTML = html;
  _length = length;
  _value = new char[length + 1];
  updateValue(defVal);
}

ConfigParam::~ConfigParam() {
  if (_value != NULL) {
    delete[] _value;
  }
}

InputType ConfigParam::getType() {
  return _type;
}

const char* ConfigParam::getName() {
  return _name;
}

const char* ConfigParam::getValue() {
  return _value;
}

const char* ConfigParam::getLabel() {
  return _label;
}

int ConfigParam::getValueLength() {
  return _length;
}

const char* ConfigParam::getCustomHTML() {
  return _customHTML;
}

std::vector<char*> ConfigParam::getOptions() {
  return _options;
}

void ConfigParam::updateValue (const char *v) {
  std::string s = std::string(v);
  //FIXME s.toCharArray(_value, _length);
}