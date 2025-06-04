#define MAX_PIN 55  // 0~54번 핀 사용

String inputString = "";  // 입력 버퍼
bool stringComplete = false;

void setup() {
  Serial.begin(9600);

  // 0~54번 핀을 모두 출력으로 설정
  for (int i = 0; i < MAX_PIN; i++) {
    pinMode(i, OUTPUT);
  }

  inputString.reserve(10);  // 버퍼 확보 (선택)
}

void loop() {
  // if (stringComplete) {
  //   int pin = inputString.toInt();  // 문자열 → 정수

  //   if (pin >= 0 && pin < MAX_PIN) {
  //     digitalWrite(pin, HIGH);
  //     delay(500);
  //     digitalWrite(pin, LOW);
  //   } else {
  //     Serial.println("잘못된 핀 번호입니다. (0~54)");
  //   }

  //   inputString = "";
  //   stringComplete = false;
  // }
  for(int i=2;i<=55;i++){
    digitalWrite(i, HIGH);
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    if (inChar == '\n') {
      stringComplete = true;
    } else if (isDigit(inChar)) {
      inputString += inChar;
    }
  }
}
