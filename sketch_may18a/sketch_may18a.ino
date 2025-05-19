#define MAX_POT 2 // 조도 센서 개수
#define MAX_LED 3 // LED 개수
#define L_LIMIT 300 // 조도 어디까지 인식으로 볼 건지
#define T_LIMIT 10 // 조도 어디까지 시간차이를 씹을 건지
#define N 3 // 속도를 정수화? 하는 느낌
#define M 1 //LED 어디만큼 킬까
#define RESET 10 //초기화 임시 변수


const int POT_PIN[MAX_POT] = {A0,A1};
int POT_TIME[MAX_POT]={0};
const int LED_PIN[MAX_LED] = {4,3,2};
int LED_TIME[MAX_LED] = {0};
int dx[2]={-1,1};
int visited[MAX_LED];
struct Point {
  int x;
  int t;
};

long long time=101;

const int MAX_SIZE = 100;
struct Point queue[MAX_SIZE];
int front = 0, rear = 0;

void enqueue(struct Point val) {
  if (rear < MAX_SIZE) {
    queue[rear++] = val;
  }
}

struct Point dequeue() {
  if (front < rear) {
    return queue[front++];
  }
  struct Point empty = {-1, -1};
  return empty; // 빈 큐
}

bool isEmpty() {
  return front == rear;
}

void bfs(int t,int x){
  for(int i=0;i<MAX_LED;i++)visited[i]=0;
  front=rear=0;
  t=(t+1)/N;
  enqueue({x,t});
  visited[x]=1;
  while(!isEmpty()){
    struct Point tmp = dequeue();
    //나중에 자동으로 꺼지게끔. 근데 지금은 귀찮아.
    if(tmp.t<=0)break;
    digitalWrite(LED_PIN[tmp.x], HIGH);
    for(int i=0;i<2;i++){
      int tmpx=tmp.x+dx[i];
      int tmpt=tmp.t;
      if(tmpx<0||tmpx>=MAX_LED)continue;
      if(visited[tmpx])continue;
      enqueue({tmpx,tmpt-M});
      visited[tmpx]=1;
    }
  }
}




void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작
  for(int i=0;i<MAX_LED;i++)
    pinMode(LED_PIN[i], OUTPUT);  
}
void loop() {

  
  for(int i=0;i<MAX_POT;i++){
    int val = analogRead(POT_PIN[i]);  // POT_PIN에서 아날로그 값 읽기
    Serial.println(val);            // 시리얼 모니터에 값 출력
    if(val<L_LIMIT){
      POT_TIME[i]=time;
      for(int j=0;j<2;j++){
        if(i+dx[j]<0 || i+dx[j]>=MAX_POT)continue;
        if(time-POT_TIME[i+dx[j]]<=T_LIMIT){
          bfs(time-POT_TIME[i+dx[j]],i);
        }
      }
    }
  }
  

  // if (val < 100) {
  //   digitalWrite(LED_PIN, HIGH);  // 밝기가 낮으면 LED 켜기
  // } else {
  //   digitalWrite(LED_PIN, LOW);   // 밝기가 높으면 LED 끄기
  // }
  if(time%RESET==0){
    for(int i=0;i<MAX_LED;i++) digitalWrite(LED_PIN[i], LOW); 
  }
  delay(500);
  time++;
}












