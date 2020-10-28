
// Teensy Pins
#define SPI_CS_PIN 10
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 12
#define SPI_SCLK_PIN 13
#define OLED_CS_PIN 10
#define OLED_RESET_PIN 18
#define OLED_DC_PIN 19
#define MATRIX_CLOCK_PIN 6
#define MATRIX_DATA_PIN 9
#define KEYBOARD_LED_MATRIX_RX_PIN 34
#define KEYBOARD_LED_MATRIX_TX_PIN 35

#define STICK_SWITCH_PIN 2
#define ENCODER_PIN1 3
#define ENCODER_PIN2 4
#define ENCODER_SWITCH_PIN 5

#define KEY_ROWS 6
#define KEY_COLS 4
#define KEY_ROW_PINS {20, 21, 30, 31, 32, 33}; //28,29 don't work for some reason
#define KEY_COL_PINS {24, 25, 26, 27};

// Analog Pins
#define STICK_X_PIN 22
#define STICK_Y_PIN 23

// Other config
#define SERIAL_BAUD 115200
#define MIDI_BAUD 31250
