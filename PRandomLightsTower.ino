/**
 * Non blocking class for controlling many lights turning off and on
 */

class Flasher
{
    int ledPin;  //digital output that controls relay
    long OnTime; //time light should stay on
    long OffTime; //time light should stay off
    long pulseTime; //time in between turning lights on and off
    long delayTime;// time before we pulse each strand

    int count; //pulse counter
    int bigPause; //big pause counter

    bool pauseForABit = false; //big pause state
    bool shouldBlink = false; //pulse pause state

    int ledState; //state of the light

    unsigned long previousMillis; //
    unsigned long previousMillisLong;
    unsigned long previoustMillisPreDelay;

  //define flasher object
  public:
    Flasher(int pin) {
      ledPin = pin;
      pinMode(ledPin, OUTPUT);

      ledState = LOW;
      previousMillis = 0;
      previousMillisLong = 0;
      previoustMillisPreDelay = 0;

      pulseTime = 10000;
      delayTime = random(1000, 1500);
    }

    void Update(long on, long off)
    {
      OnTime = on;
      OffTime = off;

      unsigned long currentMillis = millis();
      unsigned long currentMillisLong = millis();
      unsigned long currentMillisPreDelay = millis();

      //check to see if it's time to turn the light on/off
      if (currentMillisPreDelay - previoustMillisPreDelay >= delayTime) {
        previoustMillisPreDelay = currentMillisPreDelay;
        shouldBlink = true;
      }


      //pulse twice at rate picked randomly from array
      if (count < 2 && shouldBlink) {
        if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
        {
          ledState = LOW;  // Turn it off
          previousMillis = currentMillis;  // Remember the time
          digitalWrite(ledPin, ledState);  // Update the actual LED
          count++; //increment the big pause counter

        }
        else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
        {
          ledState = HIGH;  // turn it on
          previousMillis = currentMillis;   // Remember the time
          digitalWrite(ledPin, ledState);   // Update the actual LED
        }
      }
      //after two pulses we pause for a bit
      else if (count >= 2) {
        pauseForABit = true;
      }

      //pause for a bit this is where we would
      if (pauseForABit) {
        pauseForABit = false;
        //check big pause time 
        if (currentMillisLong - previousMillisLong >= pulseTime) {
          previousMillisLong = currentMillisLong;
          shouldBlink = false;
          count = 0;
          bigPause++;
          if (bigPause > 10) {
            pulseTime = 20000;
            bigPause = 0;
          } else {
            pulseTime = random(10000, 12000);
          }
            //Serial.println(pulseTime);
        }
      }
    }
};



//arry of time the light should stay on
int onTimeOne[] = {900, 900, 900, 900, 900, 900};
int onTimeTwo[] = {1000, 1000, 1000, 1000, 1000, 1000};

//array of time the light should stay off
int offTimeOne[] = {1000, 1000, 1000, 1000, 1000, 1000};
int offTimeTwo[] = {1100, 1100, 1100, 1100, 1100, 1100};

//initial values
int oTime = 1000;
int ofTime = 1100;
float prob = 0;


//all the pins we're using
int allPins[] = {
  2,  3,   4, 5,   6,
  7,  8,  9, 10, 11,
  12, 13, 14, 15, 16,
  17, 18, 19, 52, 53,
  22, 23, 24, 25, 26,
  27, 28, 29, 30, 31,
  32, 33, 34, 35, 36,
  37, 38, 39, 40, 41,
  42, 43, 44, 45, 46,
  47, 48, 49, 50, 51
};

//define strands and pins on Arduino 
Flasher strandOne[]   =   {(2),   (3),    (4),  (5),  (6)};
Flasher strandTwo[] =     {(7),   (8),    (9),  (10), (11)};
Flasher strandThree[] =   {(12),  (13),   (14), (15), (16)};
Flasher strandFour[] =    {(17),  (18),   (19), (52), (53)};
Flasher strandFive[] =    {(22),  (23),   (24), (25), (26)};
Flasher strandSix[] =     {(27),  (28),   (29), (30), (31)};
Flasher strandSeven[] =   {(32),  (33),   (34), (35), (36)};
Flasher strandEight[] =   {(37),  (38),   (39), (40), (41)};
Flasher strandNine[] =    {(42),  (43),   (44), (45), (46)};
Flasher strandTen[] =     {(47),  (48),   (49), (50), (51)};

void setup() {
  //set all pins to output and low
  for (int i = 0; i < 54; i++) {
    pinMode(allPins[i], OUTPUT);
    digitalWrite(i, LOW);
  }
  //Serial.begin(9600);
}


void loop() {
  //Debug Time
  //Serial.println(oTime);

  //Adds and subtracts time based on probability
  if (pick() >= 7 && oTime < 1800) {
    oTime += 25;
  } else if (pick() <= 6 && oTime > 250) {
    oTime -= 25;
  }

  if (pick() >= 7 && ofTime < 2500) {
    ofTime += 25;
  } else if (pick() <= 6 && ofTime > 1000) {
    ofTime -= 25;
  }


  rain();
  
  //bubbleUp();

}

//picks a random number
float pick() {
  prob = random(0, 10);
  //Serial.println(prob);
  return prob;
}


//random starting point
void rain() {
  for (int j = 5; j > 0; j--) {
    strandOne[j].Update(random(200, oTime), random(900, ofTime));
    strandTwo[j].Update(random(200, oTime), random(900, ofTime));
    strandThree[j].Update(random(200, oTime), random(900, ofTime));
    strandFour[j].Update(random(200, oTime), random(900, ofTime));
    strandFive[j].Update(random(200, oTime), random(900, ofTime));
    strandSix[j].Update(random(200, oTime), random(900, ofTime));
    strandSeven[j].Update(random(200, oTime), random(900, ofTime));
    strandEight[j].Update(random(200, oTime), random(900, ofTime));
    strandNine[j].Update(random(200, oTime), random(900, ofTime));
    strandTen[j].Update(random(200, oTime), random(900, ofTime));
  }

}


//starts at bottom of strand and turns lights on going towards the top
void bubbleUp() {

  strandOne[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandTwo[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandThree[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandFour[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandFive[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandSix[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandSeven[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandEight[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandNine[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));
  strandTen[0].Update(random(onTimeOne[0], onTimeTwo[0]), random(offTimeOne[0], offTimeTwo[0]));

  strandOne[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandTwo[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandThree[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandFour[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandFive[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandSix[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandSeven[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandEight[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandNine[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));
  strandTen[1].Update(random(onTimeOne[1], onTimeTwo[1]), random(offTimeOne[1], offTimeTwo[1]));

  strandOne[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandTwo[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandThree[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandFour[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandFive[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandSix[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandSeven[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandEight[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandNine[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));
  strandTen[2].Update(random(onTimeOne[2], onTimeTwo[2]), random(offTimeOne[2], offTimeTwo[2]));

  strandOne[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandTwo[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandThree[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandFour[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandFive[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandSix[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandSeven[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandEight[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandNine[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));
  strandTen[3].Update(random(onTimeOne[3], onTimeTwo[3]), random(offTimeOne[3], offTimeTwo[3]));

  strandOne[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandTwo[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandThree[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandFour[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandFive[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandSix[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandSeven[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandEight[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandNine[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));
  strandTen[4].Update(random(onTimeOne[4], onTimeTwo[4]), random(offTimeOne[4], offTimeTwo[4]));

  strandOne[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandTwo[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandThree[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandFour[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandFive[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandSix[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandSeven[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandEight[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandNine[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));
  strandTen[5].Update(random(onTimeOne[5], onTimeTwo[5]), random(offTimeOne[5], offTimeTwo[5]));

}
