#include <Arduino.h>

enum PHASE {PHASE1, PHASE2, PHASE3, PHASE4};
PHASE phase = PHASE1;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (phase) {
    case PHASE1:
      // Line following
      while (true) {
        // line_following() returns false when sensors read 111
        if (line_follwing()==false) break;
      }
      phase = PHASE(phase+1);
      break;
    case PHASE2:
      // Going up the ramp
      while (true) {
        // approaching_block() is a line following function but returns false when the distance sensor reads certain distance
        if (ramp_climbing()==false) break;
      }
      phase = PHASE(phase+1);
    case PHASE3:
      while (true) {
        // approaching_block() is a line following function but returns false when the distance sensor reads certain distance
        if (approaching_block()==false) break;
      }
      phase = PHASE(phase+1);
      
  }
}