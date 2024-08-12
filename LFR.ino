// Motor Connections
const int LF =  2;     // Left Forward
const int LS =  3;     // Left Speed
const int LB =  4;     // Left Backward
const int RF =  5;     // Right Forward
const int RS =  6;     // Right Speed
const int RB =  7;     // Right Backward

// IR Array Connections
const int LH_IR =  8;    // Very Left IR   
const int LM_IR =  9;    // Slight Left IR
const int M_IR  = 10;    // Middle IR
const int RM_IR = 11;    // Slight Right IR
const int RH_IR = 12;    // Very Right IR

// IR Value containers
int LH_V;
int LM_V;
int M_V;
int RM_V;
int RH_V;

//Motor Speed Values
const int Max = 255; //Maximum Speed
const int TurnSensitivity = 0.42; // Speed / Wobble
int TurnSpeed;


void setup() {
  // put your setup code here, to run once:
  pinMode(LF , OUTPUT);
  pinMode(LB , OUTPUT);
  pinMode(LS , OUTPUT);
  pinMode(RF , OUTPUT);
  pinMode(RB , OUTPUT);
  pinMode(RS , OUTPUT);
  TurnSpeed = TurnSensitivity * Max;
}

void loop() {
  // put your main code here, to run repeatedly:
  LH_V = digitalRead(LH_IR);
  LM_V = digitalRead(LM_IR);
  M_V  = digitalRead(M_IR );
  RM_V = digitalRead(RM_IR);
  RH_V = digitalRead(RH_IR); // 0 means Black

  if (M_V == 1) {                         // Middle sensor is not on track
    if (LM_V == 0) {                      // Slight Left IR is on track
      while(M_V != 0 && LH_V != 0) {      // Turn slighly left until middles sensor is back on track or car has offshooted
        left(Max, TurnSpeed);
        M_V = digitalRead(M_IR);
      }
    }
    if (RM_V == 0) {                      // Slight Right IR is on track
      while(M_V != 0 && RH_V != 0) {      // Turn slighly right until middles sensor is back on track or car has offshooted
        right(TurnSpeed, Max);
        M_V = digitalRead(M_IR);
      }
    }
    if (LH_V == 0) {                      // Very Left IR is on track
      while(M_V != 0) {                   // Turn left at max speed until middles sensor is back on track
        left(Max, Max);
        M_V = digitalRead(M_IR);
      }
    }
    if (RH_V == 0) {                      // Very Right IR is on track
      while(M_V != 0) {                   // Turn right at max speed until middles sensor is back on track
        right(Max, Max);
        M_V = digitalRead(M_IR);
      }
    }
  }
  forward(Max, Max);                      // Go forward once all errors have been corrected
}

void forward(int L_Speed, int R_Speed) {
  analogWrite(LS, L_Speed);
  analogWrite(RS, R_Speed);
  digitalWrite(LF , HIGH);
  digitalWrite(LB , LOW);
  digitalWrite(RF , HIGH);
  digitalWrite(RB , LOW);
}

void backward(int L_Speed, int R_Speed) {
  analogWrite(LS, L_Speed);
  analogWrite(RS, R_Speed);
  digitalWrite(LF , LOW);
  digitalWrite(LB , HIGH);
  digitalWrite(RF , LOW);
  digitalWrite(RB , HIGH);
}

void left(int L_Speed, int R_Speed) {
  analogWrite(LS, L_Speed);
  analogWrite(RS, R_Speed);
  digitalWrite(LF , HIGH);
  digitalWrite(LB , LOW);
  digitalWrite(RF , LOW);
  digitalWrite(RB , HIGH);
}

void right(int L_Speed, int R_Speed) {
  analogWrite(LS, L_Speed);
  analogWrite(RS, R_Speed);
  digitalWrite(LF , LOW);
  digitalWrite(LB , HIGH);
  digitalWrite(RF , HIGH);
  digitalWrite(RB , LOW);
}
