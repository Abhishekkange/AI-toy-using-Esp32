enum State { 
    IDLE, 
    BLINK, 
    HAPPY_TOUCH, 
    LISTENING, 
    SLEEP, 
    SURPRISED, 
    ANNOYED, 
    DANCE_MODE, 
    WALKING,       // New state
    FOLLOWING,     // New state
    PLAYING        // New state
};

// Required functions

// EYE Animation functions
void showNeutralEyes(){};
void showBlinkEyes(){};   
void showSurprisedEyes(){};
void showListeningEyes(){};
void showHappyEyes(){};
void showSleepEyes(){};
void showDancingEyes(){};

// Sensor involvement functions
void isTouchDetected(){};
void isLoudSoundDetected(){};
void isDarkForLong(){};
void isSuddenLightChange(){};
void isBright(){};

// Movement and action functions
void activateVibration(){};
void deactivateVibration(){};
void reactToSoundDirection(){};
void playSurpriseReaction(){};
void playDanceAnimation(){};

// New function for Walking State
void startWalking(){};
void stopWalking(){};

// New function for Following State
void startFollowing(){};
void stopFollowing(){};

// New function for Playing State
void startPlaying(){};
void stopPlaying(){};

State currentState = IDLE;
unsigned long lastBlinkTime = 0;
unsigned long nextBlinkDelay = random(5000, 15000); // 5–15s

void loop() {
  unsigned long now = millis();

  switch (currentState) {
    case IDLE:
      showNeutralEyes();

      if (isTouchDetected()) {
          currentState = HAPPY_TOUCH;
      } else if (isLoudSoundDetected()) {
          currentState = LISTENING;
      } else if (isDarkForLong()) {
          currentState = SLEEP;
      } else if (isSuddenLightChange()) {
          currentState = SURPRISED;
      } else if (now - lastBlinkTime > nextBlinkDelay) {
          currentState = BLINK;
      } else if (isMovementDetected()) {
          currentState = WALKING;  // Transition to walking if movement is detected
      }
      break;

    case BLINK:
      showBlinkEyes();
      delay(200); // short blink
      lastBlinkTime = now;
      nextBlinkDelay = random(5000, 15000);
      currentState = IDLE;
      break;

    case HAPPY_TOUCH:
      activateVibration();
      showHappyEyes();
      delay(2000);
      deactivateVibration();
      currentState = IDLE;
      break;

    case LISTENING:
      showListeningEyes();
      reactToSoundDirection();  // turn eyes or react subtly
      delay(2000);
      currentState = IDLE;
      break;

    case SLEEP:
      showSleepEyes();
      if (isBright()) {
          currentState = IDLE;
      }
      break;

    case SURPRISED:
      showSurprisedEyes();
      playSurpriseReaction(); // optional motor wiggle or sound
      delay(2000);
      currentState = IDLE;
      break;

    case ANNOYED:
      showAnnoyedEyes();
      activateVibration();
      delay(2000);
      deactivateVibration();
      currentState = IDLE;
      break;

    case DANCE_MODE:
      showDancingEyes();
      playDanceAnimation();  // LED/motor wiggle
      delay(5000);
      currentState = IDLE;
      break;

    case WALKING:
      startWalking();  // Start walking when in walking state
      delay(500);      // Simulate walking duration
      stopWalking();   // Stop walking after delay
      currentState = IDLE;  // Return to idle state after walking
      break;

    case FOLLOWING:
      startFollowing();  // Start following the user
      delay(3000);       // Simulate following duration
      stopFollowing();   // Stop following after a while
      currentState = IDLE;  // Return to idle state after following
      break;

    case PLAYING:
      startPlaying();  // Start playing (e.g., dancing, playful movements)
      delay(3000);     // Simulate playing duration
      stopPlaying();   // Stop playing after a while
      currentState = IDLE;  // Return to idle state after playing
      break;
  }
}
