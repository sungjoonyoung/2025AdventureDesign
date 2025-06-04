#define MAX_POT 6 // 조도 센서 개수
#define MAX_LED 24 // LED 개수
#define L_LIMIT 58 // 조도 어디까지 인식으로 볼 건지
#define T_LIMIT 6 // 조도 어디까지 시간차이를 씹을 건지
#define N 10 // 속도를 정수화? 하는 느낌
#define M 1 //LED 어디만큼 킬까
#define RESET 30 //초기화 임시 변수
#define LED_ON_DURATION 10
#define MINUS_TIME 1
#define Npair 40
typedef struct Point{
  int x;
  int t;
} Point;
int connect[MAX_LED][MAX_LED];
//int POT_PIN[MAX_POT]={A0,A1,A2,A3,A4,A5};
int POT_PIN[6]={A3,A4,A8,A10,A9,A11};
int POT_TIME[MAX_POT];
int POT_to_LED[MAX_POT]={22,21,12,15,4,3};
// const int LED_PIN[MAX_LED] = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48}; 
// const int YEL_PIN[MAX_LED] = {3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49};
const int LED_PIN[MAX_LED] = {10, 8, 5, 11, 4, 19, 26, 16, 14, 28, 32, 3, 30, 35, 36, 42, 48, 46, 12, 38, 40, 43, 52, 53};
const int YEL_PIN[MAX_LED] = {25, 6, 7, 9, 23, 20, 31, 17, 15, 18, 2, 22, 29, 34, 37, 54, 47, 45, 13, 39, 51, 44, 50, 49};


int LED_TIME[MAX_LED] = {0};
int dx[2]={-1,1};
int visited[MAX_LED];

long long my_time=101;

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
Point connectarr[Npair] = {
  {2, 6},
  {2, 30},
  {2, 8},
  {6, 2},
  {6, 4},
  {6, 38},
  {38, 4},
  {38, 6},
  {38, 40},
  {40, 42},
  {40, 44},
  {40, 46},
  {42, 44},
  {42, 40},
  {44, 42},
  {44, 40},
  {46, 44},
  {46, 48},
  {48, 46},
  {36, 40},
  {36, 34},
  {34, 36},
  {34, 32},
  {26, 32},
  {26, 28},
  {26, 24},
  {24, 26},
  {24, 22},
  {22, 24},
  {22, 20},
  {20, 22},
  {20, 18},
  {18, 20},
  {18, 16},
  {16, 18},
  {16, 14},
  {14, 12},
  {14, 16},
  {12, 14},
  {12, 10}
};
void init_connect() {
  for(int i=0;i<Npair;i++){
    connect[connectarr[i].x/2-1][connectarr[i].t/2-1]=connect[connectarr[i].t/2-1][connectarr[i].x/2-1]=1;
  } 
}
void bfs(int t,int x,int before){
  x=POT_to_LED[x];
  before=POT_to_LED[before];

  for(int i=0;i<MAX_LED;i++)visited[i]=0;
  front=rear=0;
  t=N/(t+1);
  struct Point p = {x, t};
  enqueue(p);

  visited[x]=1;
  visited[before]=1;
  while(!isEmpty()){
    struct Point tmp = dequeue();
    if(tmp.t<=0)break;



    if (tmp.t >= 2 * t / 3) {
      digitalWrite(LED_PIN[tmp.x], HIGH);
      LED_TIME[tmp.x] = LED_ON_DURATION-tmp.t;
    }
    else {
      digitalWrite(YEL_PIN[tmp.x], HIGH);
      LED_TIME[tmp.x] = LED_ON_DURATION-tmp.t;
    }

    for(int i=0;i<MAX_LED;i++){
      if(tmp.x<0||tmp.x>=MAX_LED)continue;
      if(!connect[tmp.x][i])continue;
      if(tmp.x==i)continue;
      if(visited[i])continue;
      //if(tmp.x==before)continue;
      // struct Point p = {x, t};
      // enqueue(p);
      // enqueue({i,tmp.t-M});
      struct Point pp = {i, tmp.t - M};
      enqueue(pp);


      visited[i]=1;
    }
  }
}




void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작
  for(int i=0;i<MAX_LED;i++){
    pinMode(LED_PIN[i], OUTPUT);  
    pinMode(YEL_PIN[i], OUTPUT);  
  }

  init_connect();

}
void loop() {

  
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  for(int i=0;i<MAX_POT;i++){
    int val = analogRead(POT_PIN[i]); 

    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(val);

    if(val<L_LIMIT){
      if(my_time - POT_TIME[i]<T_LIMIT)continue;
      Serial.println("CAR!");
      Serial.println((int)my_time);
      Serial.println();
      POT_TIME[i]=my_time;
      for(int j=0;j<2;j++){
        if(i+dx[j]<0 || i+dx[j]>=MAX_POT)continue;
        if(i%2!=0 && i+dx[j]>i)continue;
        if(i%2==0 && i+dx[j]<i)continue;
        if(POT_TIME[i]-POT_TIME[i+dx[j]]<=T_LIMIT){
          bfs(my_time-POT_TIME[i+dx[j]],i,i+dx[j]);
        }
      }
    }
  }


  for (int i = 0; i < MAX_LED; i++) {
    if (LED_TIME[i] > 0) {
      LED_TIME[i]-=MINUS_TIME;
      if (LED_TIME[i] <= 0) {
        digitalWrite(LED_PIN[i], LOW);
        digitalWrite(YEL_PIN[i], LOW);
      }
    }
  }
  delay(500);
  my_time++;
}

