#ifndef debug_h
#define debug_h

#ifdef DEBUG_MODE
    #define DEBUGINFO \
        Serial.print(millis()); \
        Serial.print(":"); \
        Serial.print(__FILE__); \
        Serial.print(":"); \
        Serial.print(__FUNCTION__); \
        Serial.print(":"); \
        Serial.print(__LINE__); \
        Serial.println(": ");
    #define DEBUGLN(...) \
        Serial.print(" "); \
        Serial.println(__VA_ARGS__);
    #define DEBUG(...) \
        Serial.print(" "); \
        Serial.print(__VA_ARGS__);
#else
    #define DEBUGINFO
    #define DEBUG(...)
    #define _(...)
    #define LN
#endif

#define INFO(...) Serial.println(__VA_ARGS__);

#define ERROR(...) Serial.println(__VA_ARGS__);

#endif