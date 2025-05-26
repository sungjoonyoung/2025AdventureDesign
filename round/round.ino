#include<Wire.h>
#include<LiquidCrystal_I2C.h>

int trigPin[] = {4,7};
int echoPin[] = {3,6};
int led=13;
int MAX=2;
int dist_ind=1000;

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  Serial.begin(9600);
  for(int i=0;i<MAX;i++){
    pinMode(echoPin[i], INPUT);
    pinMode(trigPin[i], OUTPUT);
  }

  pinMode(led, OUTPUT);


  lcd.init();              // LCD 초기화
  lcd.backlight();         // 백라이트 켜기

  lcd.setCursor(0, 0);     // 첫 줄 첫 번째 칸
  lcd.print("Hello, Arduino!");

  lcd.setCursor(0, 1);     // 둘째 줄 첫 번째 칸
  lcd.print("I2C LCD Test");

}

void loop() {
  long duration[10];
  float distance[10];

  for (int i = 0; i < MAX; i++) {
    digitalWrite(trigPin[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[i], LOW);

    duration[i] = pulseIn(echoPin[i], HIGH);
    distance[i] = duration[i] * 0.17;

    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" - Duration: ");
    Serial.print(duration[i]);
    Serial.print(" us, Distance: ");
    Serial.print(distance[i]);
    Serial.println(" mm");
  }

  if (distance[0] < dist_ind && distance[1] < dist_ind) {
  lcd.setCursor(0, 0);     // 첫 줄 첫 번째 칸
  lcd.print("CAR!             ");

  lcd.setCursor(0, 1);     // 둘째 줄 첫 번째 칸
  lcd.print("CAR!             ");
  delay(5000);
  } 
  else if(distance[0] < dist_ind || distance[1] < dist_ind) {
  lcd.setCursor(0, 0);     // 첫 줄 첫 번째 칸
  lcd.print("HUMAN!             ");

  lcd.setCursor(0, 1);     // 둘째 줄 첫 번째 칸
  lcd.print("HUMAN!             ");
  delay(5000);
  } 
  else {
  lcd.setCursor(0, 0);     // 첫 줄 첫 번째 칸
  lcd.print("EMPTY!             ");

  lcd.setCursor(0, 1);     // 둘째 줄 첫 번째 칸
  lcd.print("EMPTY!             ");
  }

  delay(50);
}








// // int trigPin[] = {4,7};
// // int echoPin[] = {3,6};
// // int led=13;
// // int MAX=2;
// // int dist_ind=1000;

// // void setup() {
// //   Serial.begin(9600);
// //   for(int i=0;i<MAX;i++){
// //     pinMode(echoPin[i], INPUT);
// //     pinMode(trigPin[i], OUTPUT);
// //   }

// //   pinMode(led, OUTPUT);
// // }

// // void loop() {
// //   long duration[10];
// //   float distance[10];

// //   for (int i = 0; i < MAX; i++) {
// //     digitalWrite(trigPin[i], LOW);
// //     delayMicroseconds(2);
// //     digitalWrite(trigPin[i], HIGH);
// //     delayMicroseconds(10);
// //     digitalWrite(trigPin[i], LOW);

// //     duration[i] = pulseIn(echoPin[i], HIGH);
// //     distance[i] = duration[i] * 0.17;

// //     Serial.print("Sensor ");
// //     Serial.print(i);
// //     Serial.print(" - Duration: ");
// //     Serial.print(duration[i]);
// //     Serial.print(" us, Distance: ");
// //     Serial.print(distance[i]);
// //     Serial.println(" mm");
// //   }

// //   if (distance[0] < dist_ind && distance[1] < dist_ind) {
// //     digitalWrite(led, HIGH);
// //   } else {
// //     digitalWrite(led, LOW);
// //   }

// //   delay(100);
// // }

