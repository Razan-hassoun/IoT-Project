// Ultrasonic Sensor
#define TRIG 5
#define ECHO 18

// L298N Motor Driver
#define ENA 25
#define IN1 26
#define IN2 27

#define ENB 33
#define IN3 14
#define IN4 12

// PWM settings
#define freq 5000
#define resolution 8

long duration;
int distance;

void setup() {
  Serial.begin(115200);

  // Ultrasonic
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Motors
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // PWM for ESP32
  ledcAttach(ENA, freq, resolution);
  ledcAttach(ENB, freq, resolution);

  // Speed (0-255)
  ledcWrite(ENA, 180);
  ledcWrite(ENB, 180);
}

void loop() {

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 20) {
    stopCar();
    delay(500);

    turnRight();
    delay(700);
  }
  else {
    forward();
  }

}


// Read distance
int getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  return duration * 0.034 / 2;
}


// Move forward
void forward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// Stop
void stopCar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// Turn right
void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}