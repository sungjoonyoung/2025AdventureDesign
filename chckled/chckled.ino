#define MAX_LED 24 // LED 개수

const int LED_PIN[MAX_LED] = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48};
const int YEL_PIN[MAX_LED] = {3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49};

void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작
  for(int i=0;i<MAX_LED;i++)
    pinMode(LED_PIN[i], OUTPUT);
}
void loop() {

  
  
  for (int i = 0; i < MAX_LED; i++) {
    digitalWrite(LED_PIN[i], HTGH);
    digitalWrite(YEL_PIN[i], HTGH);

    delay(500);

    digitalWrite(LED_PIN[i], LOW);
    digitalWrite(YEL_PIN[i], LOW);
  }
  delay(500);
}