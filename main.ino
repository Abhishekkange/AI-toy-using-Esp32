
enum State { 
    IDLE, 
    BLINK, 
    HAPPY_TOUCH, 
    LISTENING, 
    SLEEP, 
    SURPRISED, 
    ANNOYED, 
    DANCE_MODE 
  };
  
  //required functions 

  //EYE Animation functions



  //Sensor involment functions
  void showNeutralEyes(){};
  void isTouchDetected(){};
  void isLoudSoundDetected(){};
  void showBlinkEyes(){};
  void showSurprisedEyes(){};
  void showListeningEyes(){};
  void activateVibration(){};
  void showHappyEyes();
  void reactToSoundDirection(){};
  void isDarkForLong(){};
  void isSuddenLightChange(){};
  void deactivateVibration(){};







  
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
    }
  }
  