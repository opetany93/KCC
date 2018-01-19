

// ================= PORTS DEFINITIONS ==============
#define LED_PORT 	LEDS_BASE
#define PIO_PORT 	PIO_BASE

// ================== LEDS DEFINITIONS ==============
#define LED_0	0x01
#define LED_1	0x02
#define LED_2	0x04
#define LED_3	0x08

// ================= PINS DEFINITIONS ===============
#define PIN_0	0x0001
#define PIN_1	0x0002
#define PIN_2	0x0004
#define PIN_3	0x0008
#define PIN_4	0x0010
#define PIN_5	0x0020
#define PIN_6	0x0040
#define PIN_7	0x0080
#define PIN_8	0x0100
#define PIN_9	0x0200
#define PIN_10	0x0400
#define PIN_11	0x0800
#define PIN_12	0x1000
#define PIN_13	0x2000
#define PIN_14	0x4000
#define PIN_15	0x8000

// ======================= Functions definitions ================================
void PIO_Write(int port, int value);
int  PIO_Read(int port);
void PIO_SetBit(int port, int value);
void PIO_ClearBit(int port, int value);
int PIO_ReadBit(int port, int pin);
void PIO_Direction(int port, int value);
