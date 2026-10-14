// =====================
// L298N Motor Driver Pins
// =====================
#define ENA 9      // Enable pin Right Motor
#define IN1 7      // Right motor input 1
#define IN2 8      // Right motor input 2

#define ENB 10      // Enable pin Left Motor
#define IN3 11     // Left motor input 1
#define IN4 12     // Left motor input 2

// =====================
// 5 DIGITAL IR SENSORS
// =====================
// S1 = Leftmost, S2 = Left, S3 = Center, S4 = Right, S5 = Rightmost
#define S1 2
#define S2 3
#define S3 4
#define S4 5
#define S5 6

int baseSpeed = 90; // speed between 0–255

void setup() {

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensor pins
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  Serial.begin(9600);
}


// =====================================
// Motor control functions
// =====================================
void forward() {
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, 0);
  analogWrite(ENB, baseSpeed);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, 0);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);
}

void stopRobot() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}


// =====================================
// MAIN LOOP
// =====================================
void loop() {

  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  // Print sensor values to Serial Monitor
  Serial.print(s1); Serial.print(" ");
  Serial.print(s2); Serial.print(" ");
  Serial.print(s3); Serial.print(" ");
  Serial.print(s4); Serial.print(" ");
  Serial.println(s5);

  // ===== SIMPLE LOGIC =====

  // If center sees the line → go forward
  if (s3 == 0 || (s1 == 0 && s2== 0 && s3 == 0 && s4 == 0 && s5 ==0) || (s2 == 0 && s3 == 0 && s4 == 0)) {
    forward();
  }
  // If right-most or right sensors detect line → turn right
  else if (s4 == 0 || s5 == 0 || (s4 == 0 || s5 == 0 && s3 == 0)) {
    turnLeft();
  }
  // If left-most or left sensors detect line → turn left
  else if (s1 == 0 || s2 == 0 || (s1 == 0 || s2 == 0 && s3 == 0) ) {
    turnRight();
  }
  // If none detect → stop
  else {
    stopRobot();
  }
}
