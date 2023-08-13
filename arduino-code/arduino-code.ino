// Motor A connections
int enA = 6;
int in1 = 5;
int in2 = 7;

// Motor B connections
int enB = 3;
int in3 = 2;
int in4 = 4;

// Motor C connections
int enC = 10;
int in5 = 8;
int in6 = 9;

// Motor D connections
int enD = 11;
int in7 = 12;
int in8 = 13;

int state = 5;

// Function to set motors for forward direction
void forward() {
  analogWrite(enA, 255);  // Set Motor A speed (0-255)
  analogWrite(enB, 255);  // Set Motor B speed (0-255)
  analogWrite(enC, 255);  // Set Motor C speed (0-255)
  analogWrite(enD, 255);  // Set Motor D speed (0-255)

  // Set motor directions for forward movement
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}

// Function to set motors for backward direction
void backward() {
  analogWrite(enA, 255);  // Set Motor A speed (0-255)
  analogWrite(enB, 255);  // Set Motor B speed (0-255)
  analogWrite(enC, 255);  // Set Motor C speed (0-255)
  analogWrite(enD, 255);  // Set Motor D speed (0-255)

  // Set motor directions for backward movement
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}

// Function to set motors for left direction
void left() {
  analogWrite(enA, 150);  // Set Motor A speed (0-255)
  analogWrite(enB, 150);  // Set Motor B speed (0-255)
  analogWrite(enC, 150);  // Set Motor C speed (0-255)
  analogWrite(enD, 150);  // Set Motor D speed (0-255)

  // Set motor directions for left movement
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}

// Function to set motors for right direction
void right() {
  analogWrite(enA, 150);  // Set Motor A speed (0-255)
  analogWrite(enB, 150);  // Set Motor B speed (0-255)
  analogWrite(enC, 150);  // Set Motor C speed (0-255)
  analogWrite(enD, 150);  // Set Motor D speed (0-255)

  // Set motor directions for right movement
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}

// Function to stop the motors
void stopMotors() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  analogWrite(enC, 0);
  analogWrite(enD, 0);
}

void setup() {
  // Set all the motor control pins to OUTPUT
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(enD, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);

  // Stop the motors initially
  stopMotors();
  Serial.begin(9600);
}

void loop() {
  // Test each direction for 2 seconds
  if (Serial.available() > 0) {
    int numb = Serial.parseInt();  // Read the incoming number
    Serial.print("Received: ");
    Serial.println(numb);

    if (numb != 0) {
      state = numb;
    }

    switch (state) {
      case 1:
        forward();
        Serial.println("f");
        break;
      case 2:
        backward();
        Serial.println("b");
        break;
      case 3:
        left();
        Serial.println("l");
        break;
      case 4:
        right();
        Serial.println("r");
        break;
      case 5:
        stopMotors();
        Serial.println("s");
        break;
    }
  }
  switch (state) {
    case 1:
      forward();
      Serial.println("f");
      break;
    case 2:
      backward();
      Serial.println("b");
      break;
    case 3:
      left();
      Serial.println("l");
      break;
    case 4:
      right();
      Serial.println("r");
      break;
    case 5:
      stopMotors();
      Serial.println("s");
      break;
  }
}
