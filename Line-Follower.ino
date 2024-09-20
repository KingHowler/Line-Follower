// Motor Connections
const int RF =  7;     // Left Forward
const int RS =  6;     // Left Speed
const int RB =  8;     // Left Backward
const int LF =  9;     // Right Forward
const int LS =  5;     // Right Speed
const int LB =  10;     // Right Backward

// IR Array Connections
const int LH_IR = 11;    // Very Left IR   
const int LM_IR = 12;    // Slight Left IR
const int M_IR  = 13;    // Middle IR
const int RM_IR = 3;    // Slight Right IR
const int RH_IR = 4;    // Very Right IR

// IR Value containers
int LH_V;
int LM_V;
int M_V;
int RM_V;
int RH_V;

//Motor Speed Values
const int Max = 255; //Maximum Speed
const int TurnSensitivity = 0.72; // Speed = k * Wobble
int TurnSpeed; // Speed of non-dominant side when turning


void setup() {
  // put your setup code here, to run once:
  pinMode(LF , OUTPUT);
  pinMode(LB , OUTPUT);
  pinMode(LS , OUTPUT);
  pinMode(RF , OUTPUT);
  pinMode(RB , OUTPUT);
  pinMode(RS , OUTPUT);
  // TurnSpeed = TurnSensitivity * Max; Use with Gyro and Maths to caluclate on the run | Code for Gyro to be added soon
  // TurnSpeed = 115; Use to manually set in case of use without sensors
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
        forward(TurnSpeed, Max);
        M_V = digitalRead(M_IR);
        LH_V = digitalRead(LH_IR);
      }
    }
    if (RM_V == 0) {                      // Slight Right IR is on track
      while(M_V != 0 && RH_V != 0) {      // Turn slighly right until middles sensor is back on track or car has offshooted
        forward(Max, TurnSpeed);
        M_V = digitalRead(M_IR);
        RH_V = digitalRead(RH_IR);
      }
    }
    if (LH_V == 0) {                      // Very Left IR is on track
      while(M_V != 0) {                   // Rotate left at TurnSpeed until middles sensor is back on track
        left(TurnSpeed, TurnSpeed);
        M_V = digitalRead(M_IR);
      }
    }
    if (RH_V == 0) {                      // Very Right IR is on track
      while(M_V != 0) {                   // Rotate right at TurnSpeed speed until middles sensor is back on track
        right(TurnSpeed, TurnSpeed);
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