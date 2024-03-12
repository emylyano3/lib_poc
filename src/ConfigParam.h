#ifndef ESP_CONFIG_PARAM_H
#define ESP_CONFIG_PARAM_H

#include <vector>
#include <string>

enum InputType {Combo, Text};

class ConfigParam {

    public:
        ConfigParam (InputType type, const char* name, const char* label, const char* defVal, uint8_t length, const char* html);
        ~ConfigParam();

        InputType           getType();
        const char*         getName();
        const char*         getLabel();
        const char*         getValue();
        int                 getValueLength();
        const char*         getCustomHTML();
        std::vector<char*>  getOptions();

        void                updateValue(const char *v);

    private:
        const char*         _name;       // identificador
        const char*         _label;      // legible por usuario
        char*               _value;      // valor default
        uint8_t             _length;     // longitud limite
        const char*         _customHTML; // html custom
        InputType           _type;       // tipo de control en formularion
        std::vector<char*>  _options;    // optciones para el combo
};

#endif