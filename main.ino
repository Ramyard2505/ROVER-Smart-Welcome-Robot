#include <Arduino.h>

/* ---------------- PIN DEFINITIONS ---------------- */
// Ultrasonic
#define TRIG_PIN 5
#define ECHO_PIN 18

// L298N Motor Driver
#define IN1 12
#define IN2 13
#define IN3 14
#define IN4 27
#define ENA 25   // PWM Motor A
#define ENB 26   // PWM Motor B

// DFPlayer (NO 16/17)
#define DF_RX 4    // ESP32 TX -> DFPlayer RX (via resistor)
#define DF_TX 2    // ESP32 RX <- DFPlayer TX

HardwareSerial mp3Serial(2);

/* ---------------- PWM SETTINGS ---------------- */
#define PWM_FREQ 5000
#define PWM_RES 8   // 0–255

/* ---------------- SPEED SETTINGS (60 RPM) ---------------- */
#define MAX_SPEED 255
#define MID_SPEED 200
#define LOW_SPEED 120

/* ---------------- DISTANCE SETTINGS (cm) ---------------- */
#define SEARCH_DISTANCE    150
#define APPROACH_DISTANCE  80
#define SLOW_DISTANCE      40
#define GREET_DISTANCE     35

unsigned long lastGreeting = 0;
const unsigned long greetingCooldown = 6000;

/* ---------------- DFPLAYER FUNCTION ---------------- */
void sendDF(uint8_t cmd, uint8_t p1, uint8_t p2) {
  uint8_t frame[10] = {0x7E, 0xFF, 0x06, cmd, 0x00, p1, p2, 0, 0, 0xEF};
  uint16_t sum = 0;
  for (int i = 1; i < 7; i++) sum += frame[i];
  uint16_t checksum = 0 - sum;
  frame[7] = (checksum >> 8) & 0xFF;
  frame[8] = checksum & 0xFF;
  mp3Serial.write(frame, 10);
}

/* ---------------- ULTRASONIC ---------------- */
long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 999;
  return (duration / 2) / 29.1;
}

/* ---------------- MOTOR FUNCTIONS ---------------- */
void motorsForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, speed);
  ledcWrite(ENB, speed);
}

void motorsBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(ENA, speed);
  ledcWrite(ENB, speed);
}

void rotateLeft(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, speed);
  ledcWrite(ENB, speed);
}

void motorsStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);
}

/* ---------------- SEARCH NEXT PERSON ---------------- */
void searchNext() {
  motorsBackward(MAX_SPEED);
  delay(700);
  motorsStop();

  rotateLeft(MAX_SPEED);
  delay(700);
  motorsStop();
}

/* ---------------- SETUP ---------------- */
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // PWM attach (ESP32 core 3.x)
  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);

  // DFPlayer UART
  mp3Serial.begin(9600, SERIAL_8N1, DF_TX, DF_RX);
  delay(500);

  sendDF(0x06, 0x00, 25); // Volume (0–30)

  Serial.println("🤖 College Greeting Robot Ready");
}

/* ---------------- LOOP ---------------- */
void loop() {
  long d = readDistanceCM();
  Serial.println(d);

  if (d > SEARCH_DISTANCE) {
    rotateLeft(MID_SPEED);              // searching
  }
  else if (d > APPROACH_DISTANCE) {
    motorsForward(MAX_SPEED);           // fast approach
  }
  else if (d > SLOW_DISTANCE) {
    motorsForward(MID_SPEED);           // slow approach
  }
  else if (d <= GREET_DISTANCE &&
           millis() - lastGreeting > greetingCooldown) {

    motorsStop();
    sendDF(0x03, 0x00, 0x01);            // play 001.mp3
    lastGreeting = millis();

    delay(3500);                        // greeting time
    searchNext();                       // find next person
  }

  delay(120);
}
