#ifndef _CONFIG_
#define _CONFIG_


// SPI 0
#define SPI_CLK 2
#define SPI_TX 3
#define SPI_RX 4

// SPI 1
#define SPI1_CLK 10
#define SPI1_TX NOPIN
#define SPI1_RX 12



// Screen
#define OLED_SPI SPI
#define OLED_DC     6
#define OLED_CS     5
#define OLED_RESET  7

// Joystick
#define JOYX_PIN 27
#define JOYY_PIN 28
#define JOY_BUTTON_PIN 22
#define JOY_RESPONSE_TIME 10


// Shift registers
#define N_SHIFT_REG 3
#define SR_LOAD_PIN 11



#endif