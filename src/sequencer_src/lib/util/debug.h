#ifndef debug_h
#define debug_h

#ifdef DEBUG_MODE
    #define DEBUG(...) Serial.println(__VA_ARGS__);
#else
    #define DEBUG(...)
#endif

#define INFO(...) Serial.println(__VA_ARGS__);

#define ERROR(...) Serial.println(__VA_ARGS__);

#endif