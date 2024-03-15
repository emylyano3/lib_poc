#ifndef Channel_h
#define Channel_h

#include <Arduino.h>

#ifndef CHANNEL_NAME_MAX_LENGTH 
#define CHANNEL_NAME_MAX_LENGTH 20
#endif

static const uint32_t   NO_TIMER = -1;

class Channel {
    
    public:
        Channel(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState);
        Channel(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState, bool analog);
        Channel(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState, uint32_t timer);
        Channel(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState, bool analog, uint32_t timer);

        const char*             id;
        char*                   name;
        uint8_t                 pin;
        uint8_t                 pinMode;
        int                     currState;
        int                     prevState;
        bool                    analog;
        unsigned long           timer;
        bool                    enabled;
        bool                    binary = true;
        bool                    inverted = true;
        std::function<int(int)> valueMapper;

        unsigned long   timerControl;
        
        void    init(const char* id, const char* name, uint8_t pin, uint8_t pinMode, int currState, bool analog, uint32_t timer);

        // Updates the channel´s name
        void    updateName (const char *v);
        // Updates the timer control setting it to timer time ftom now
        void    updateTimerControl();

        bool    timeIsUp();

        bool    isOutput();

        bool    isEnabled();

        // Set the value in channel and writes it over the device pin
        void    write(int value);

        /*
            Read the value from the pin related to the channel, and updates the channel state.
            Returns true if value is read from pin, false otherwise.
        */
        bool    read();

        // Sets the mapper to map the channel state
        void    setStateMapper(std::function<int(int)> mapper);

        /* 
            Returns the channel current state mapped, according to the mapper function defined.
            If no mapper defined, plain value is returned instead
        */
        int     getStateMapped();
};

#endif