#ifndef debug_h
#define debug_h

#ifdef DEBUG_MODE
    #define DEBUG(msg) Serial.println(msg)
#else
    #define DEBUG(msg)
#endif


#endif