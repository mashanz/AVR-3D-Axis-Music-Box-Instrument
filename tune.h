#include <Arduino.h>
// TONES  ==========================================
// Start by defining the relationship between 
//       note, period, &  frequency. 
#define  _c     3830    // 261 Hz 
#define  _d     3400    // 294 Hz 
#define  _e     3038    // 329 Hz 
#define  _f     2864    // 349 Hz 
#define  _g     2550    // 392 Hz 
#define  _a     2272    // 440 Hz 
#define  _b     2028    // 493 Hz 
#define  _C     1912    // 523 Hz 
// Define a special note, 'R', to represent a rest
#define  _R     0

/*************************************************
 * Public Constants
 *************************************************/

#define _B0  31
#define _C1  33
#define _CS1 35
#define _D1  37
#define _DS1 39
#define _E1  41
#define _F1  44
#define _FS1 46
#define _G1  49
#define _GS1 52
#define _A1  55
#define _AS1 58
#define _B1  62
#define _C2  65
#define _CS2 69
#define _D2  73
#define _DS2 78
#define _E2  82
#define _F2  87
#define _FS2 93
#define _G2  98
#define _GS2 104
#define _A2  110
#define _AS2 117
#define _B2  123
#define _C3  131
#define _CS3 139
#define _D3  147
#define _DS3 156
#define _E3  165
#define _F3  175
#define _FS3 185
#define _G3  196
#define _GS3 208
#define _A3  220
#define _AS3 233
#define _B3  247
#define _C4  262
#define _CS4 277
#define _D4  294
#define _DS4 311
#define _E4  330
#define _F4  349
#define _FS4 370
#define _G4  392
#define _GS4 415
#define _A4  440
#define _AS4 466
#define _B4  494
#define _C5  523
#define _CS5 554
#define _D5  587
#define _DS5 622
#define _E5  659
#define _F5  698
#define _FS5 740
#define _G5  784
#define _GS5 831
#define _A5  880
#define _AS5 932
#define _B5  988
#define _C6  1047
#define _CS6 1109
#define _D6  1175
#define _DS6 1245
#define _E6  1319
#define _F6  1397
#define _FS6 1480
#define _G6  1568
#define _GS6 1661
#define _A6  1760
#define _AS6 1865
#define _B6  1976
#define _C7  2093
#define _CS7 2217
#define _D7  2349
#define _DS7 2489
#define _E7  2637
#define _F7  2794
#define _FS7 2960
#define _G7  3136
#define _GS7 3322
#define _A7  3520
#define _AS7 3729
#define _B7  3951
#define _C8  4186
#define _CS8 4435
#define _D8  4699
#define _DS8 4978
// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note) 
int melody[] = {  _C,  _b,  _g,  _C,  _b,   _e,  _R,  _C,  _c,  _g, _a, _C };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
int hits = 0;
int melody_1[] = { _c,_d,_e,_f,_g,_a,_b,_C,_R };
int beats_1[]  = {  8, 8, 8, 8, 8, 8, 8, 8, 8 }; 
int MAX_COUNT_1 = sizeof(melody_1) / 2; // Melody length, for looping.
//gundul pacul
int melody_2[] = { _c,_e,_c,_e,_f,_g,_g,_b,_C,_b,_C,_b,_g,_c,_e,_c,_e,_f,_g,_g,_b,_C,_b,_C,_b,_g,_c,_e,_g,_f,_f,_g,_f,_e,_c,_f,_e,_c,_c,_e,_g,_f,_f,_g,_f,_e,_c,_f,_e,_c };
int beats_2[]  = { 32,32,32,32,32,32,64,32,32,32,32,32,64,32,32,32,32,32,32,64,32,32,32,32,32,64,64,64,63,32,32,32,32,32,32,32,32,64,64,64,63,32,32,32,32,32,32,32,32,64 }; 
int MAX_COUNT_2 = sizeof(melody_2) / 2; // Melody length, for looping.
//ibu kartini
int melody_3[] = { _c,_d,_e,_f,_g,_e,_c, _a,_C,_b,_a,_g, _f,_a,_g,_f,_e,_c, _d,_f,_e,_d,_c };
int beats_3[]  = { 64,32,64,64,64,32,96, 64,32,64,64,96, 64,32,64,64,64,96, 64,32,64,64,96 }; 
int MAX_COUNT_3 = sizeof(melody_3) / 2; // Melody length, for looping.
//durundung
int melody_4[] = { _c,_e,_g,_c,_e,_g, _f,_a,_C,_f,_a,_C, _c,_e,_g,_c,_e,_g, _f,_a,_C,_f,_a,_C };
int beats_4[]  = { 16,16,16,16,16,16, 16,16,16,16,16,16, 16,16,16,16,16,16, 16,16,16,16,16,16 }; 
int MAX_COUNT_4 = sizeof(melody_4) / 2; // Melody length, for looping.

int lagu =0;
// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {
      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);
      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);
      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);//aslinya duration  
    }                                
  }                                 
}

//====================================================================
//====================================================================
//====================================================================
void doremi(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("GANTI GAN");
  delay(1000);
  // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT_1; i++) {
    tone_ = melody_1[i];
    beat = beats_1[i];
    duration = beat * tempo; // Set up timing
    playTone();
    // A pause between notes...
    delayMicroseconds(pause);
  }
}
void n_do(){
  tone_ = melody_1[0];
  beat = beats_1[0];
  duration = beat * tempo; // Set up timing
  playTone(); 
  // A pause between notes...
  //delayMicroseconds(pause);
}
void n_re(){
  tone_ = melody_1[1];
  beat = beats_1[0];
  duration = beat * tempo; // Set up timing
  playTone(); 
  // A pause between notes...
  //delayMicroseconds(pause);
}
void n_mi(){
  tone_ = melody_1[2];
  beat = beats_1[0];
  duration = beat * tempo; // Set up timing
  playTone(); 
  // A pause between notes...
  //delayMicroseconds(pause);
}
void n_fa(){
  tone_ = melody_1[3];
  beat = beats_1[0];
  duration = beat * tempo; // Set up timing
  playTone(); 
  // A pause between notes...
  //delayMicroseconds(pause);
}
void n_so(){
  tone_ = melody_1[4];
  beat = beats_1[0];
  duration = beat * tempo; // Set up timing
  playTone(); 
  // A pause between notes...
  //delayMicroseconds(pause);
}
void n_la(){
  tone_ = melody_1[5];
  beat = beats_1[0];
  duration = beat * tempo; // Set up timing
  playTone(); 
  // A pause between notes...
  //delayMicroseconds(pause);
}
void n_si(){
  tone_ = melody_1[6];
  beat = beats_1[0];
  duration = beat * tempo; // Set up timing
  playTone(); 
  // A pause between notes...
  //delayMicroseconds(pause);
}
void n_Do(){
  tone_ = melody_1[7];
  beat = beats_1[0];
  duration = beat * tempo; // Set up timing
  playTone(); 
  // A pause between notes...
  //delayMicroseconds(pause);
}
void gundulpacul(){
  // Set up a counter to pull from melody[] and beats[]
  for (hits=0; hits<MAX_COUNT_2; hits++) {
    tone_ = melody_2[hits];
    beat = beats_2[hits];
    duration = beat * tempo; // Set up timing
    //compass.enableDefault();
    compass.read();
    if(((compass.a.x / 10) <= 0)&&((compass.a.y / 10) <= 0)&&((compass.a.z / 10) <= 0)){
        digitalWrite(3,HIGH);
        hits=MAX_COUNT_2;
        lagu=lagu+1;
    }else{
      playTone();
    }
    // A pause between notes...
    delayMicroseconds(pause);
  }  
}
void ibukartini(){
  // Set up a counter to pull from melody[] and beats[]
  for (hits=0; hits<MAX_COUNT_3; hits++) {
    tone_ = melody_3[hits];
    beat = beats_3[hits];
    duration = beat * tempo; // Set up timing
    //compass.enableDefault();
    compass.read();
    if(((compass.a.x / 10) <= 0)&&((compass.a.y / 10) <= 0)&&((compass.a.z / 10) <= 0)){
        digitalWrite(3,HIGH);
        hits=MAX_COUNT_3;
        lagu=lagu+1;
    }else{
      playTone();
    }
    // A pause between notes...
    delayMicroseconds(pause);
  }  
}
void durun(){
  // Set up a counter to pull from melody[] and beats[]
  for (hits=0; hits<MAX_COUNT_4; hits++) {
    tone_ = melody_4[hits];
    beat = beats_4[hits];
    duration = beat * tempo; // Set up timing
    //compass.enableDefault();
    compass.read();
    if(((compass.a.x / 10) <= 0)&&((compass.a.y / 10) <= 0)&&((compass.a.z / 10) <= 0)){
        digitalWrite(3,HIGH);
        hits=MAX_COUNT_4;
        lagu=lagu+1;
    }else{
      playTone();
    }
    // A pause between notes...
    delayMicroseconds(pause);
  }  
}
