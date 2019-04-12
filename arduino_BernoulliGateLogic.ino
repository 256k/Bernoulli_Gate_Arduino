//TBD:
//==================================//

//1. introduce a new switch that enables/disables step skipping
//2. create the logic (another if condition) when the the values are equal set gate A high.
//(Step skipping is when the random number and the knob number are equal, if you enable step skipping:
// when the values are equal, do nothing, if disabled, then gate A will be high.


//=================================//
//* I define here the input and output pins:
int GateIn = 2;
int GateOutA = 3;
int GateOutB = 4;
int ProbKnob = A0;
int ProbCVin = A1;

// define the value variables:
int GateInVal = 0;
int gateRef = 0;
int ProbKnobVal = 0;
int ProbCVinVal = 0;

// create a variable for the random reference number
// for the comparison
int randomNumRef = 0;

// define Randomization range:
int RandValStart = 0;
int RandValEnd = 0;

void setup() {


  // debug code:
  Serial.begin(9600);
  // end of debug code

pinMode(GateIn, INPUT);
  // resetting the gates to low
  pinMode(GateOutA, OUTPUT);
  digitalWrite(GateOutA, LOW);
  pinMode(GateOutB, OUTPUT);
  digitalWrite(GateOutB, LOW);


}

void loop() {
// randomSeed(random(0,1000));

  GateInVal = digitalRead(GateIn);

  // if the gate input is high and the previous cycle the gate was low
  // so out gate reference was at 0
  if (digitalRead(GateIn) == HIGH && gateRef == 0) {




    // debug code:  
    Serial.println("==============");
    Serial.println("GATE ACTIVATED");
    // end of debug code




    //  set the gateRef to 1 to indicate a gate has started
    gateRef = 1;


    //  read the knob values
    ProbKnobVal = map (analogRead(ProbKnob), 0, 1023, 0, 20);
    ProbCVinVal = analogRead(ProbCVin);

    Serial.println("KNOB VALUE: ");
    Serial.print(ProbKnobVal);
    Serial.println("");


    //  Generate a new random value:
    randomNumRef = random(0, 20);

    Serial.println("RANDOM REFERENCE: ");
    Serial.print(randomNumRef);
    Serial.println("");



    // compare values to see which Gate output to trigger:
    if (randomNumRef > ProbKnobVal ) {

      Serial.println("GATE A OUTPUT");

      // Reset the opposite gate:
      digitalWrite(GateOutB, LOW);

      // output HIGH on GateOutA:
      digitalWrite(GateOutA, HIGH);

    }

    if (randomNumRef < ProbKnobVal ) {

      Serial.println("GATE B OUTPUT");

      // Reset the opposite gate:
      digitalWrite(GateOutA, LOW);

      // output HIGH on GateOutB
      digitalWrite(GateOutB, HIGH);
    }
  } else if (digitalRead(GateIn) == LOW && gateRef == 1) {


    //  if the GateIn is low & GateRef is 1 meaning last cycle it was high (like i am now, kek), then reset both gates

    digitalWrite(GateOutA, LOW);
    digitalWrite(GateOutB, LOW);

    //  reset the gateRef
    gateRef = 0;

    Serial.println("GATE DEACTIVATED");
  }

}
