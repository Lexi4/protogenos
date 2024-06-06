#include <Adafruit_GFX.h> 
#include <Max72xxPanel.h>

// Sprites
#define JAWS_MODE 3 
#define EYE_MODE  0 
#define NOSE_MODE 4 
#define ASTONISHMENT_MODE 2 
#define ANGRY_MODE 3 
#define DEATH_MODE 4 
#define ASTONISHMENT_MOUTH 3 
#define ANGER_MOUTH 1 
#define DEATH_MOUTH 1 

// Timings
int astonishmentDuration = 6000;
int angerDuration = 8000;
int deathDuration = 12000;
int heartSpeed = 800;
int angerTouchCount = 4;
int deathTouchCount = 10;
int winkSpeed = 15;

// Connection
int touchPin = 2;
int micPin = 7;
int brightness = 10;

Max72xxPanel matrix = Max72xxPanel(9, 1, 14); 

// Vars
bool blink, smile, angry, nose, gen3I = 0, gen3O = 0, timer3I = 0, gen4I = 0, gen4O = 0, gen2I = 0, timer5I = 0, gen2O = 0, gen7I = 0, gen7O = 0, count3I = 0;
bool count3_SCST = 0, timer2I = 0, timer2O = 0, timer4I = 0, timer4O = 0, trigger3 = 0, trigger3I = 0, count1I = 0, trigger8 = 0, trigger8I = 0, gen5I = 0, gen5O = 0; 
bool gen1I = 0, count4I = 0, count4MaxLO = 0, trigger1 = 0, count1MaxLO = 0, trigger1I = 0, trigger5 = 0, trigger5I = 0, timer7I = 0, trigger4 = 0;
bool timer7O = 0, trigger4I = 0, timer1I = 0, timer1O = 0, trigger2 = 0, trigger2I = 0, temp, measure;
unsigned long gen3P = 0UL, timer3P = 0UL, gen4P = 0UL, gen2P = 0UL, timer5P = 0UL, gen7P = 0UL, timer2P = 0UL, timer4P = 0UL, gen5P = 0UL, gen1P = 0UL, timer7P = 0UL, timer1P = 0UL;
int array[100];
int death, x = 0, y = 0, _PWDC = 0, gtv1 = 1000, count4Value = 0, count3Value = 0, count1Value = 0, index = 0, output, input, maxSnach = 1000, maxSnach2 = 1000, m1, spriteSmile, rot;

#if (NOSE_MODE == 7)
const byte  nose[16] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000001,
    0b11000011,
    0b01100110,
    0b00111100,
    0b00011000,
    
    0b00011000,
    0b00111100,
    0b01100110,
    0b11000011,
    0b10000001,
    0b00000000,
    0b00000000,
    0b00000000,
};

#elif (NOSE_MODE == 6)
const byte  nose[16] = {
    0b00000000,
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00011000,
    
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b00000000,
};

#elif (NOSE_MODE == 5)
const byte  nose[16] = {
    0b00100000,
    0b01110000,
    0b11111000,
    0b11111100,
    0b11111100,
    0b01111100,
    0b00111000,
    0b00010000,
    
    0b00010000,
    0b00111000,
    0b01111100,
    0b11111100,
    0b11111100,
    0b11111000,
    0b01110000,
    0b00100000,
};
#elif (NOSE_MODE == 4)
const byte  nose[16] = {
    0b10000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b01111100,
    0b00111110,
    
    0b00111110,
    0b01111100,
    0b11110000,
    0b11100000,
    0b11100000,
    0b11100000,
    0b11000000,
    0b10000000,
};
#elif (NOSE_MODE == 3)
const byte  nose[16] = {
    0b00000000,
    0b10000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11110000,
    0b01111000,
    
    0b01111100,
    0b11111000,
    0b11100000,
    0b11100000,
    0b11100000,
    0b11000000,
    0b10000000,
    0b00000000,
};
#elif (NOSE_MODE == 2)
const byte  nose[16] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000000,
    0b11000000,
    0b01110000,
    
    0b01110000,
    0b11100000,
    0b10000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};
#elif (NOSE_MODE == 1)
const byte  nose[16] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11000000,
    
    0b10000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};
#elif (NOSE_MODE == 0)
const byte  nose[16] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000000,
    0b01000000,
    
    0b01000000,
    0b10000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Eyes spites 

#if (EYE_MODE == 11)
const byte  eyes[16] = {
    0b00000001,
    0b00000011,
    0b00000111,
    0b00001110,
    0b00011100,
    0b00111000,
    0b01110001,
    0b11100011,
    0b11000111,
    0b10001110,
    0b00011100,
    0b00111000,
    0b01110000,
    0b11100000,
    0b11000000,
    0b10000000,
};
#elif (EYE_MODE == 10)
const byte  eyes[16] = {
    0b00100000,
    0b00010000,
    0b00011000,
    0b00001100,
    0b00000110,
    0b00000110,
    0b00000010,
    0b00000011,
    0b00000011,
    0b00000111,
    0b00001110,
    0b00001110,
    0b00011100,
    0b00111000,
    0b11110000,
    0b11000000,
};
#elif (EYE_MODE == 9)
const byte  eyes[16] = {
    0b00000001,
    0b00000011,
    0b00000111,
    0b00001110,
    0b00011100,
    0b00111000,
    0b01110000,
    0b11100000,
    0b11100000,
    0b01110000,
    0b00111000,
    0b00011100,
    0b00001110,
    0b00000111,
    0b00000011,
    0b00000001,
};
#elif (EYE_MODE == 8)
const byte  eyes[16] = {
    0b00110000,
    0b00011000,
    0b00111000,
    0b01111100,
    0b01111110,
    0b01111110,
    0b11111110,
    0b11111110,
    0b11111110,
    0b11111110,
    0b11111100,
    0b11111000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b10000000,
};
#elif (EYE_MODE == 7)
const byte  eyes[16] = {
    0b01000000,
    0b11100000,
    0b11110000,
    0b11111000,
    0b11111100,
    0b11111110,
    0b11111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111110,
    0b11111110,
    0b11111100,
    0b11111100,
    0b11111000,
    0b01110000,
};
#elif (EYE_MODE == 6)
const byte  eyes[16] = {
    0b00000010,
    0b00001111,
    0b00011111,
    0b00111110,
    0b00111100,
    0b01111100,
    0b01111000,
    0b11111000,
    0b11111000,
    0b11111000,
    0b11111100,
    0b11111110,
    0b01111111,
    0b00111111,
    0b00011111,
    0b00001110,
};
#elif (EYE_MODE == 5)
const byte  eyes[16] = {
    0b00011000,
    0b00011000,
    0b00111100,
    0b00111100,
    0b01111110,
    0b01111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b00111100,
    0b10000001,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100,
}; 
#elif (EYE_MODE == 4)
const byte  eyes[16] = {
    0b00000011,
    0b00001111,
    0b00011111,
    0b00111111,
    0b00111111,
    0b01111111,
    0b01111111,
    0b11111111,
    0b11111111,
    0b01111111,
    0b01111111,
    0b00111111,
    0b00111111,
    0b00011111,
    0b00001111,
    0b00000011,
};
#elif (EYE_MODE == 3)
const byte  eyes[16] = {
    0b11000000,
    0b11100000,
    0b11111000,
    0b11111100,
    0b11111111,
    0b11111111,
    0b11111110,
    0b11111100,
    0b11111100,
    0b11111000,
    0b11110000,
    0b11110000,
    0b11100000,
    0b11000000,
    0b11000000,
    0b10000000,
};
#elif (EYE_MODE == 2)
const byte  eyes[16] = {
    0b11100000,
    0b11111000,
    0b11111100,
    0b11111110,
    0b11111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111110,
    0b11111110,
    0b11111100,
    0b11111000,
    0b11110000,
    0b11100000,
    0b11000000,
};
#elif (EYE_MODE == 1)
const byte  eyes[16] = {
    0b00000110,
    0b00001111,
    0b00001111,
    0b00011111,
    0b00011111,
    0b00111111,
    0b00111110,
    0b01111110,
    0b01111110,
    0b01111110,
    0b11111100,
    0b11111100,
    0b11111100,
    0b11111000,
    0b11111000,
    0b01110000,
};
#else
const byte  eyes[16] = {
    0b00000111,
    0b00100110,
    0b00101110,
    0b01001100,
    0b01011100,
    0b10011100,
    0b10111000,
    0b00111000,
    0b01111000,
    0b01111000,
    0b11111000,
    0b11111100,
    0b11111100,
    0b01111100,
    0b00111100,
    0b00011000,  
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Angry eyes sprites

#if (ANGRY_MODE == 3)
const byte  ang_eyes[16] = {
    0b00100000,
    0b00100011,
    0b01000111,
    0b01000111,
    0b10000111,
    0b10001111,
    0b00001111,
    0b00011111,
    0b00011110,
    0b00111110,
    0b01111100,
    0b11111100,
    0b11111000,
    0b01110000,
    0b00000000,
    0b00000000,
};
#elif (ANGRY_MODE == 2)
const byte  ang_eyes[16] = {
    0b00110000,
    0b01111010,
    0b01111011,
    0b01111011,
    0b11111011,
    0b11111011,
    0b11111011,
    0b11111001,
    0b11111000,
    0b11111000,
    0b11111000,
    0b11110000,
    0b11110000,
    0b01100000,
    0b00000000,
    0b00000000,
};
#elif (ANGRY_MODE == 1)
const byte  ang_eyes[16] = {
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00111100,
    0b00100010,
    0b00100001,
    0b00100001,
    0b01000001,
    0b01000001,
    0b01000010,
    0b01111100,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
};
#elif (ANGRY_MODE == 0)
const byte  ang_eyes[16] = {
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00111100,
    0b00111110,
    0b00111111,
    0b00111111,
    0b01111111,
    0b01111111,
    0b01111110,
    0b01111100,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Astonishment eyes sprites

#if (ASTONISHMENT_MODE == 4)
const byte  owo_eyes[16] = {
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00111100,
    0b00100100,
    0b00100100,
    0b01100110,
    0b01100110,
    0b01000010,
    0b11000011,
    0b11000011,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
};
#elif (ASTONISHMENT_MODE == 3)
const byte  owo_eyes[16] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00111100,
    0b01000010,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b01000010,
    0b00111100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};
#elif (ASTONISHMENT_MODE == 2)
const byte  owo_eyes[16] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00111100,
    0b01111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};
#elif (ASTONISHMENT_MODE == 1)
const byte  owo_eyes[16] = {
    0b00000010,
    0b00000111,
    0b00001110,
    0b00011100,
    0b00111100,
    0b00111000,
    0b01111000,
    0b01110000,
    0b11110000,
    0b11110000,
    0b11110000,
    0b01111000,
    0b01111100,
    0b00111110,
    0b00011110,
    0b00001100,
};
#elif (ASTONISHMENT_MODE == 0)
const byte  owo_eyes[32] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01110000,
    0b11111000,
    0b11111100,
    0b01111110,
    0b00111111,
    0b01111110,
    0b11111100,
    0b11111000,
    0b01110000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00111000,
    0b01111100,
    0b01111110,
    0b00111111,
    0b01111110,
    0b01111100,
    0b00111000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Jaws sprites

#if (JAWS_MODE == 0)
 byte jaws[160] = {
    
    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b10000000,
    0b11000000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00001100,
    0b00000110,
    0b00011100,
    0b01110000,
    0b11000000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00001100,
    0b00000110,
    0b00000011,

    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b10000000,
    0b11000000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00001100,
    0b00000110,
    0b00011110,
    0b01111000,
    0b11100000,
    0b01110000,
    0b00111000,
    0b00011100,
    0b00001110,
    0b00000111,
    0b00000011,

    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b10000000,
    0b11000000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00001100,
    0b00000110,
    0b00011110,
    0b01111100,
    0b11111000,
    0b01111000,
    0b00111100,
    0b00011110,
    0b00001111,
    0b00000111,
    0b00000011,

    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b11100000,
    0b11100000,
    0b01110000,
    0b00111000,
    0b00011100,
    0b00001110,
    0b00000111,
    0b00011111,
    0b01111110,
    0b11111100,
    0b01111100,
    0b00111110,
    0b00011111,
    0b00001111,
    0b00000111,
    0b00000011,

    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00111000,
    0b00110000,
    0b01110000,
    0b01100000,
    0b11100000,
    0b11100000,
    0b11100000,
    0b11110000,
    0b01111000,
    0b00111100,
    0b00011110,
    0b00001111,
    0b00000111,
    0b00011111,
    0b01111111,
    0b11111110,
    0b01111110,
    0b00111111,
    0b00011111,
    0b00001111,
    0b00000111,
    0b00000011,
 };
#elif (JAWS_MODE == 1)
 byte jaws[160] = {
    
    0b00000001,
    0b00000001,
    0b00000001,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000100,
    0b00000100,
    0b00000100,
    0b00001000,
    0b00001000,
    0b00001000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,

    0b00000001,
    0b00000001,
    0b00000001,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000100,
    0b00000100,
    0b00000100,
    0b00001000,
    0b00001000,
    0b00001000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00011000,
    0b00110000,
    0b01100000,
    0b11000000,

    0b00000001,
    0b00000001,
    0b00000001,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000100,
    0b00000100,
    0b00000100,
    0b00001000,
    0b00001000,
    0b00001000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b10000000,
    0b11000000,
    0b11000000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00001100,
    0b00011100,
    0b00111000,
    0b01110000,
    0b11100000,

    0b00000001,
    0b00000001,
    0b00000001,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000100,
    0b00000100,
    0b00000100,
    0b00001000,
    0b00001000,
    0b00001000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00110000,
    0b00110000,
    0b00100000,
    0b01100000,
    0b01100000,
    0b01000000,
    0b11000000,
    0b11000000,
    0b11100000,
    0b01110000,
    0b00111000,
    0b00011100,
    0b00001110,
    0b00011110,
    0b00111100,
    0b01111000,
    0b11111000,

    0b00000001,
    0b00000001,
    0b00000001,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000100,
    0b00000100,
    0b00000100,
    0b00001100,
    0b00001000,
    0b00001000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b01110000,
    0b01110000,
    0b01100000,
    0b11100000,
    0b11100000,
    0b11110000,
    0b01111000,
    0b00111100,
    0b00011110,
    0b00001111,
    0b00011111,
    0b00111110,
    0b01111110,
    0b11111110,
 };
#elif (JAWS_MODE == 2)

 byte jaws[160] = {
    
    0b00011100,
    0b00011110,
    0b00010011,
    0b00010110,
    0b00010110,
    0b00011100,
    0b00011100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b10000000,
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,

    0b00011100,
    0b00011110,
    0b00010011,
    0b00010110,
    0b00010110,
    0b00011100,
    0b00011100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b10000000,
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00001100,
    0b00001100,
    0b00011100,
    0b00011000,
    0b00111000,
    0b00111000,
    0b01110000,
    0b01110000,
    0b11100000,

    0b00011100,
    0b00011110,
    0b00010011,
    0b00010110,
    0b00010110,
    0b00011100,
    0b00011100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11100000,
    0b01100000,
    0b01110000,
    0b00110000,
    0b00111000,
    0b00011000,
    0b00011100,
    0b00001100,
    0b00001110,
    0b00011110,
    0b00011110,
    0b00111100,
    0b00111100,
    0b01111000,
    0b01111000,
    0b11110000,

    0b00011100,
    0b00011110,
    0b00010011,
    0b00010110,
    0b00010110,
    0b00011100,
    0b00011100,
    0b00011000,
    0b00011000,
    0b00111000,
    0b00110000,
    0b01110000,
    0b01100000,
    0b11100000,
    0b11100000,
    0b11100000,
    0b11110000,
    0b01110000,
    0b01111000,
    0b00111000,
    0b00111100,
    0b00011100,
    0b00011110,
    0b00001110,
    0b00001111,
    0b00011111,
    0b00011111,
    0b00111110,
    0b00111110,
    0b01111100,
    0b01111100,
    0b11111100,

    0b00011100,
    0b00011110,
    0b00010011,
    0b00010110,
    0b00010110,
    0b00011100,
    0b00011100,
    0b00011100,
    0b00011100,
    0b00111000,
    0b00111000,
    0b01110000,
    0b01110000,
    0b11110000,
    0b11100000,
    0b11110000,
    0b11110000,
    0b01111000,
    0b01111000,
    0b00111100,
    0b00111100,
    0b00011110,
    0b00011111,
    0b00001111,
    0b00001111,
    0b00011111,
    0b00011111,
    0b00111111,
    0b00111111,
    0b01111111,
    0b01111111,
    0b11111111,
 };

#elif (JAWS_MODE == 3)
  byte jaws[160] = {
    
    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00001100,
    0b00011000,
    0b00110000,
    0b01100000,
    0b11000000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00001100,

    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00001100,
    0b00011000,
    0b00110000,
    0b01110000,
    0b11110000,
    0b01110000,
    0b00111000,
    0b00011100,
    0b00001110,

    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00011100,
    0b00001100,
    0b00011100,
    0b00111000,
    0b01111000,
    0b11111000,
    0b01111000,
    0b00111100,
    0b00011110,
    0b00001111,

    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b11100000,
    0b11100000,
    0b01100000,
    0b01110000,
    0b00111000,
    0b00011100,
    0b00011110,
    0b00001110,
    0b00011110,
    0b00111110,
    0b01111100,
    0b11111100,
    0b01111110,
    0b00111110,
    0b00011111,
    0b00001111,

    0b00000111,
    0b00001001,
    0b00001011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00111000,
    0b00110000,
    0b01110000,
    0b01100000,
    0b11100000,
    0b11100000,
    0b11110000,
    0b11110000,
    0b01111000,
    0b01111000,
    0b00111100,
    0b00011110,
    0b00011111,
    0b00001111,
    0b00011111,
    0b00111111,
    0b01111111,
    0b11111111,
    0b01111111,
    0b00111111,
    0b00011111,
    0b00001111,
 };
#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Dead eyes sprites

#if (DEATH_MODE == 4)
const byte  dead_eyes[16] = {
    0b10000001,
    0b10000001,
    0b01000010,
    0b01000010,
    0b00100100,
    0b00100100,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00100100,
    0b00100100,
    0b01000010,
    0b01000010,
    0b10000001,
    0b10000001,
};
#elif (DEATH_MODE == 3)
const byte  dead_eyes[16] = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001,
};
#elif (DEATH_MODE == 2)
const byte  dead_eyes[16] = {
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
};
#elif (DEATH_MODE == 1)
const byte  dead_eyes[16] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000001,
    0b11000011,
    0b01100110,
    0b00111100,
    0b00011000,
    0b00011000,
    0b00111100,
    0b01100110,
    0b11000011,
    0b10000001,
    0b00000000,
    0b00000000,
    0b00000000,
};
#elif (DEATH_MODE == 0)
const byte  dead_eyes[16] = {
    0b00100000,
    0b00010000,
    0b00011000,
    0b00001100,
    0b00000110,
    0b00000110,
    0b00000010,
    0b00000011,
    0b00000011,
    0b00000111,
    0b00001110,
    0b00001110,
    0b00011100,
    0b00111000,
    0b11110000,
    0b11000000,
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Daed jaws sprites

#if (DEATH_MOUTH == 3)
  byte k[64] = {
    0b11000000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    
    0b00011000,
    0b00011000,
    0b00011000,
    0b01111000,
    0b10011000,
    0b11011000,
    0b10011000,
    0b01111000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00110000,
    0b01100000,
    0b11000000,
  };
#elif (DEATH_MOUTH == 2)
  byte k[64] = {
    0b11000000,
    0b01100000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00110000,
    0b01100000,
    0b11000000,
  };
#elif ((DEATH_MOUTH == 1)||(DEATH_MOUTH == 0))
  byte k[64] = {
    0b11000000,
    0b10100000,
    0b10100000,
    0b01100000,
    0b01100000,
    0b01110000,
    0b00110000,
    0b00110000,
    0b00111000,
    0b00011000,
    0b00011000,
    0b00011100,
    0b00001100,
    0b00001100,
    0b00001110,
    0b00000110,
    0b00000110,
    0b00000111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00111100,
    0b01001100,
    0b10010110,
    0b11100110,
    0b10001111,
    0b01110011,
    0b00000011,
    0b00000111,
    0b00000110,
    0b00000110,
    0b00001110,
    0b00001100,
    0b00001100,
    0b00011100,
    0b00011000,
    0b00011000,
    0b00111000,
    0b00110000,
    0b00110000,
    0b01110000,
    0b01100000,
    0b01100000,
    0b10100000,
    0b10100000,
    0b11000000,
  };
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Astonishment jaws sprites

#if (ASTONISHMENT_MOUTH == 3)
  byte o[32] = {
    0b00110000,
    0b00111000,
    0b00011100,
    0b00001110,
    0b00000111,
    0b00000111,
    0b00001110,
    0b00011100,
    0b00111000,
    0b01110000,
    0b11100000,
    0b11100000,
    0b01110000,
    0b00111000,
    0b00011100,
    0b00001110,
    0b00000111,
    0b00000111,
    0b00001110,
    0b00011100,
    0b00111000,
    0b01110000,
    0b11100000,
    0b11100000,
    0b01110000,
    0b00111000,
    0b00011100,
    0b00001110,
    0b00000111,
    0b00000111,
    0b00001110,
    0b00011100,
  };

#elif (ASTONISHMENT_MOUTH == 2)
  byte o[32] = {
    0b00000111,
    0b00001110,
    0b00011100,
    0b00111000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
  };
#elif ((ASTONISHMENT_MOUTH == 1)||(ASTONISHMENT_MOUTH == 0))
  byte  o[32] = {
    0b00000001,
    0b00000001,
    0b00000010,
    0b00000010,
    0b00000100,
    0b00000100,
    0b00001000,
    0b00001000,
    0b00010000,
    0b00010000,
    0b00100000,
    0b00100000,
    0b01000000,
    0b01000000,
    0b10000000,
    0b10000000,
    0b01000000,
    0b01000000,
    0b00100000,
    0b00100000,
    0b00010000,
    0b00010000,
    0b00001000,
    0b00001000,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b01000000,
    0b00100000,
 };
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Sprite of anger: mouth.    

#if (ANGER_MOUTH == 3)
  byte z[32] = {
    0b00011000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b00110000,
    0b00001100,
    0b00000011,
    0b00000011,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
  };
#elif (ANGER_MOUTH == 2)
  byte z[32] = {
    0b11000000,
    0b10100000,
    0b10100000,
    0b01100000,
    0b01100000,
    0b01110000,
    0b00110000,
    0b00110000,
    0b00111000,
    0b00011000,
    0b00011000,
    0b00011100,
    0b00001100,
    0b00001100,
    0b00001110,
    0b00000110,
    0b00000110,
    0b00000111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00000110,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
  };
#elif ((ANGER_MOUTH == 1)||(ANGER_MOUTH == 0))
  byte z[32] = {
    0b11000000,
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00011100,
    0b00011100,
    0b00011100,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b01100000,
    0b01100000,
    0b11000000,
    0b11000000,
    0b10000000,
    0b11000000,
    0b01100000,
    0b01100000,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00001100,
    0b00011000,
    0b00110000,
    0b01100000,
    0b11000000,
  };
#endif

void setup() {
  pinMode(touchPin, INPUT); 
  matrix.setIntensity(brightness); 
  matrix.setRotation(4);
}

void loop() {
  _PWDC = 0;

  if (((analogRead(micPin)) - gtv1) > (maxSnach - (analogRead(micPin)))) {
    if (timer4I) {
      if (isTimer(timer4P, 50)) {
        timer4O = 1;
      }
    } else {
      timer4I = 1;
      timer4P = millis();
    }
  } else {
    timer4O = 0;
    timer4I = 0;
  }

  if (timer4O) {
    if (!gen2I) {
      gen2I = 1;
      gen2O = 1;
      gen2P = millis();
    }
  } else {
    gen2I = 0;
    gen2O = 0;
  }

  if (gen2I) {
    if (isTimer(gen2P, 10)) {
      gen2P = millis();
      gen2O = !gen2O;
    }
  }

  if (!(timer4O)) {
    if (!gen3I) {
      gen3I = 1;
      gen3O = 1;
      gen3P = millis();
    }
  } else {
    gen3I = 0;
    gen3O = 0;
  }

  if (gen3I) {
    if (isTimer(gen3P, 10)) {
      gen3P = millis();
      gen3O = !gen3O;
    }
  }

  if (gen2O) {
    if (!count3I) {
      count3I = 1;
      if (rot < 4) {
        rot = rot + 1;
      }
    }
  } else {
    count3I = 0;
  }

  if (gen3O) {
    if (!count3_SCST) {
      count3_SCST = 1;
      if (rot > 0) {
        rot = rot - 1;
      }
    }
  } else {
    count3_SCST = 0;
  }

  if (digitalRead(touchPin)) {
    timer7O = 1;
    timer7I = 1;
  } else {
    if (timer7I) {
      timer7I = 0;
      timer7P = millis();
    } else {
      if (timer7O) {
        if (isTimer(timer7P, 3500)) timer7O = 0;
      }
    }
  }

  if (!(timer7O)) {
    if (trigger3I) {
      trigger3 = 0;
    } else {
      trigger3 = 1;
      trigger3I = 1;
    }
  } else {
    trigger3 = 0;
    trigger3I = 0;
  }

  if (trigger3) {
    count1Value = 0;
  } else {
    if (digitalRead(touchPin)) {
      if (!count1I) {
        count1I = 1;
        count1Value = count1Value + 1;
      }
    } else {
      count1I = 0;
    }
  }

  count1MaxLO = count1Value >= deathTouchCount;
  if (count1MaxLO) {
    death = 1;
    timer1I = 1;
  } else {
    if (timer1I) {
      timer1I = 0;
      timer1P = millis();
    } else {
      if (death) {
        if (isTimer(timer1P, deathDuration)) death = 0;
      }
    }
  }

  if (!(trigger8)) {
    if (trigger8I) {
      trigger8 = 0;
    } else {
      trigger8 = 1;
      trigger8I = 1;
    }
  } else {
    trigger8 = 0;
    trigger8I = 0;
  }

  if (trigger3) {
    count4Value = 0;
  } else {
    if (digitalRead(touchPin)) {
      if (!count4I) {
        count4I = 1;
        count4Value = count4Value + 1;
      }
    } else {
      count4I = 0;
    }
  }

  count4MaxLO = count4Value >= angerTouchCount;
  if (count4MaxLO) {
    angry = 1;
    timer5I = 1;
  } else {
    if (timer5I) {
      timer5I = 0;
      timer5P = millis();
    } else {
      if (angry) {
        if (isTimer(timer5P, angerDuration)) angry = 0;
      }
    }
  }

  if ((digitalRead(touchPin)) && (!angry)) {
    smile = 1;
    timer3I = 1;
  } else {
    if (timer3I) {
      timer3I = 0;
      timer3P = millis();
    } else {
      if (smile) {
        if (isTimer(timer3P, astonishmentDuration)) smile = 0;
      }
    }
  }

  if (!(smile)) {
    if (trigger2I) {
      trigger2 = 0;
    } else {
      trigger2 = 1;
      trigger2I = 1;
    }
  } else {
    trigger2 = 0;
    trigger2I = 0;
  }

  if (!((smile || angry || death))) {
    if (!gen7I) {
      gen7I = 1;
      gen7O = 1;
      gen7P = millis();
    }
  } else {
    gen7I = 0;
    gen7O = 0;
  }

  if (gen7I) {
    if (gen7O) {
      if (isTimer(gen7P, 80)) {
        gen7P = millis();
        gen7O = 0;
      }
    } else {
      if (isTimer(gen7P, 80)) {
        gen7P = millis();
        gen7O = 1;
      }
    }
  }

  if (gen7O) {
    blink = 1;
  } else {
    blink = 0;
  }

  if (blink) {
    matrix.fillScreen(LOW);
    matrix.write();
  } else {
    if (death) {
      renderDeath();
    } else {
      if (angry) {
        renderAngry();
      } else {
        if (smile) {
          renderSmile();
        } else {
          renderNormal();
        }
      }
    }
  }
}

// Timer expired checker
bool isTimer(unsigned long previousMillis, unsigned long interval) {
  return (millis() - previousMillis >= interval);
}

void renderDeath() {
  matrix.clear();
  renderEyes(DEATH_MODE, 0);
  renderNose(NOSE_MODE);
  renderMouth(DEATH_MOUTH, 1);
  matrix.write();
}

void renderAngry() {
  matrix.clear();
  renderEyes(ANGRY_MODE, 0);
  renderNose(NOSE_MODE);
  renderMouth(ANGER_MOUTH, 1);
  matrix.write();
}

void renderSmile() {
  matrix.clear();
  renderEyes(ASTONISHMENT_MODE, 0);
  renderNose(NOSE_MODE);
  renderMouth(ASTONISHMENT_MOUTH, 1);
  matrix.write();
}

void renderNormal() {
  matrix.clear();
  renderEyes(EYE_MODE, 0);
  renderNose(NOSE_MODE);
  renderMouth(JAWS_MODE, 0);
  matrix.write();
}

void renderEyes(int x, int y) {
  matrix.drawPixel(4 + x, 5 + y, HIGH);
  matrix.drawPixel(5 + x, 5 + y, HIGH);
  matrix.drawPixel(4 + x, 4 + y, HIGH);
  matrix.drawPixel(5 + x, 4 + y, HIGH);
}

void renderNose(int y) {
  matrix.drawPixel(7, 7 + y, HIGH);
}

void renderMouth(int y, int z) {
  for (int i = 2; i < 6; i++) {
    matrix.drawPixel(i + 1, 11 - y, HIGH);
  }
  if (z == 1) {
    matrix.drawPixel(6, 10 - y, HIGH);
    matrix.drawPixel(7, 9 - y, HIGH);
  }
}