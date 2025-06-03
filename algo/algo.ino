#define MAX_POT 6 // 조도 센서 개수
#define MAX_LED 24 // LED 개수
#define L_LIMIT 20 // 조도 어디까지 인식으로 볼 건지
#define T_LIMIT 10 // 조도 어디까지 시간차이를 씹을 건지
#define N 10 // 속도를 정수화? 하는 느낌
#define M 1 //LED 어디만큼 킬까
#define RESET 30 //초기화 임시 변수
#define LED_ON_DURATION 10
#define MINUS_TIME 1

int connect[MAX_LED][MAX_LED] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
};
int POT_PIN[MAX_POT]={A0,A1,A2,A3,A4,A5};
int POT_TIME[MAX_POT];
int POT_to_LED[MAX_POT]={3,4,12,15,21,22};
const int LED_PIN[MAX_LED] = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48};
const int YEL_PIN[MAX_LED] = {3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49};
void init_connect() {
    connect[0][2] = connect[2][0] = 1;  // 2-6
    connect[0][14] = connect[14][0] = 1; // 2-30
    connect[0][3] = connect[3][0] = 1;  // 2-8

    connect[2][0] = connect[0][2] = 1;  // 6-2
    connect[2][1] = connect[1][2] = 1;  // 6-4
    connect[2][18] = connect[18][2] = 1; // 6-38

    connect[18][1] = connect[1][18] = 1; // 38-4
    connect[18][2] = connect[2][18] = 1; // 38-6
    connect[18][19] = connect[19][18] = 1; // 38-40

    connect[19][20] = connect[20][19] = 1; // 40-42
    connect[19][21] = connect[21][19] = 1; // 40-44
    connect[19][22] = connect[22][19] = 1; // 40-46

    connect[20][21] = connect[21][20] = 1; // 42-44
    connect[20][19] = connect[19][20] = 1; // 42-40

    connect[21][20] = connect[20][21] = 1; // 44-42
    connect[21][19] = connect[19][21] = 1; // 44-40

    connect[22][21] = connect[21][22] = 1; // 46-44
    connect[22][23] = connect[23][22] = 1; // 46-48

    connect[23][22] = connect[22][23] = 1; // 48-46

    connect[17][19] = connect[19][17] = 1; // 36-40
    connect[17][16] = connect[16][17] = 1; // 36-34

    connect[16][17] = connect[17][16] = 1; // 34-36
    connect[16][15] = connect[15][16] = 1; // 34-32

    connect[12][15] = connect[15][12] = 1; // 26-32
    connect[12][13] = connect[13][12] = 1; // 26-28
    connect[12][11] = connect[11][12] = 1; // 26-24

    connect[11][12] = connect[12][11] = 1; // 24-26
    connect[11][10] = connect[10][11] = 1; // 24-22

    connect[10][11] = connect[11][10] = 1; // 22-24
    connect[10][9] = connect[9][10] = 1;   // 22-20

    connect[9][10] = connect[10][9] = 1;   // 20-22
    connect[9][8] = connect[8][9] = 1;     // 20-18

    connect[8][9] = connect[9][8] = 1;     // 18-20
    connect[8][7] = connect[7][8] = 1;     // 18-16

    connect[7][8] = connect[8][7] = 1;     // 16-18
    connect[7][6] = connect[6][7] = 1;     // 16-14

    connect[6][5] = connect[5][6] = 1;     // 14-12
    connect[6][7] = connect[7][6] = 1;     // 14-16

    connect[5][6] = connect[6][5] = 1;     // 12-14
    connect[5][4] = connect[4][5] = 1;     // 12-10
}


int LED_TIME[MAX_LED] = {0};
int dx[2]={-1,1};
int visited[MAX_LED];
typedef struct {
  int x;
  int t;
} Point;

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

void bfs(int t,int x,int before){
  x=POT_to_LED[x];
  before=POT_to_LED[before];

  for(int i=0;i<MAX_LED;i++)visited[i]=0;
  front=rear=0;
  t=N/(t+1);

  enqueue({x,t});
  visited[x]=1;
  visited[before]=1;
  while(!isEmpty()){
    struct Point tmp = dequeue();
    //나중에 자동으로 꺼지게끔. 근데 지금은 귀찮아.
    if(tmp.t<=0)break;



    if (tmp.t >= 2 * t / 3) {
      digitalWrite(LED_PIN[tmp.x], HIGH);
      LED_TIME[tmp.x] = LED_ON_DURATION-tmp.t;
    }
    else {
      digitalWrite(YEL_PIN[tmp.x], HIGH);
      LED_TIME[tmp.x] = LED_ON_DURATION-tmp.t;
    }
    
    // if(tmp.t>=2*t/3) digitalWrite(LED_PIN[tmp.x], HIGH);
    // else digitalWrite(YEL_PIN[tmp.x], HIGH);

    for(int i=0;i<MAX_LED;i++){
      if(!connect[tmp.x][i])continue;
      if(tmp.x==i)continue;
      if(visited[i])continue;
      //if(tmp.x==before)continue;
      if(tmp.x<0||tmp.x>=MAX_LED)continue;
      enqueue({i,tmp.t-M});
      visited[i]=1;
    }

    // for(int i=0;i<2;i++){
    //   int tmpx=tmp.x+dx[i];
    //   int tmpt=tmp.t;
    //   if(tmpx==before)continue;
    //   if(tmpx<0||tmpx>=MAX_LED)continue;
    //   if(visited[tmpx])continue;
    //   enqueue({tmpx,tmpt-M});
    //   visited[tmpx]=1;
    // }
  }
}




void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작
  for(int i=0;i<MAX_LED;i++)
    pinMode(LED_PIN[i], OUTPUT);  
  init_connect();

}
void loop() {

  
  for(int i=0;i<MAX_POT;i++){
    int val = analogRead(POT_PIN[i]);  // POT_PIN에서 아날로그 값 읽기
    
    // 조도 센서 값 시리얼 모니터에 출력
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(val);

    if(val<L_LIMIT){
      if(time - POT_TIME[i]<T_LIMIT)continue;
      Serial.println("CAR!");
      Serial.println((int)time);
      Serial.println();
      POT_TIME[i]=time;
      for(int j=0;j<2;j++){
        if(i+dx[j]<0 || i+dx[j]>=MAX_POT)continue;
        if(time-POT_TIME[i+dx[j]]<=T_LIMIT){
          bfs(time-POT_TIME[i+dx[j]],i,i+dx[j]);
        }
      }
    }
  }
  

  // if (val < 100) {
  //   digitalWrite(LED_PIN, HIGH);  // 밝기가 낮으면 LED 켜기
  // } else {
  //   digitalWrite(LED_PIN, LOW);   // 밝기가 높으면 LED 끄기
  // }
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
  time++;
}


















// #define MAX_POT 6 // 조도 센서 개수
// #define MAX_LED 24 // LED 개수
// #define L_LIMIT 20 // 조도 어디까지 인식으로 볼 건지
// #define T_LIMIT 10 // 조도 어디까지 시간차이를 씹을 건지
// #define N 10 // 속도를 정수화? 하는 느낌
// #define M 1 //LED 어디만큼 킬까
// #define RESET 30 //초기화 임시 변수



// int connect[MAX_LED][MAX_LED] = {
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
// };
// int POT_PIN[MAX_POT]={A0,A1,A2,A3,A4,A5};
// int POT_TIME[MAX_POT];
// int POT_to_LED[MAX_POT]={3,4,12,15,21,22};
// const int LED_PIN[MAX_LED] = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48};
// const int YEL_PIN[MAX_LED] = {3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49};
// void init_connect() {
//     connect[0][2] = connect[2][0] = 1;  // 2-6
//     connect[0][14] = connect[14][0] = 1; // 2-30
//     connect[0][3] = connect[3][0] = 1;  // 2-8

//     connect[2][0] = connect[0][2] = 1;  // 6-2
//     connect[2][1] = connect[1][2] = 1;  // 6-4
//     connect[2][18] = connect[18][2] = 1; // 6-38

//     connect[18][1] = connect[1][18] = 1; // 38-4
//     connect[18][2] = connect[2][18] = 1; // 38-6
//     connect[18][19] = connect[19][18] = 1; // 38-40

//     connect[19][20] = connect[20][19] = 1; // 40-42
//     connect[19][21] = connect[21][19] = 1; // 40-44
//     connect[19][22] = connect[22][19] = 1; // 40-46

//     connect[20][21] = connect[21][20] = 1; // 42-44
//     connect[20][19] = connect[19][20] = 1; // 42-40

//     connect[21][20] = connect[20][21] = 1; // 44-42
//     connect[21][19] = connect[19][21] = 1; // 44-40

//     connect[22][21] = connect[21][22] = 1; // 46-44
//     connect[22][23] = connect[23][22] = 1; // 46-48

//     connect[23][22] = connect[22][23] = 1; // 48-46

//     connect[17][19] = connect[19][17] = 1; // 36-40
//     connect[17][16] = connect[16][17] = 1; // 36-34

//     connect[16][17] = connect[17][16] = 1; // 34-36
//     connect[16][15] = connect[15][16] = 1; // 34-32

//     connect[12][15] = connect[15][12] = 1; // 26-32
//     connect[12][13] = connect[13][12] = 1; // 26-28
//     connect[12][11] = connect[11][12] = 1; // 26-24

//     connect[11][12] = connect[12][11] = 1; // 24-26
//     connect[11][10] = connect[10][11] = 1; // 24-22

//     connect[10][11] = connect[11][10] = 1; // 22-24
//     connect[10][9] = connect[9][10] = 1;   // 22-20

//     connect[9][10] = connect[10][9] = 1;   // 20-22
//     connect[9][8] = connect[8][9] = 1;     // 20-18

//     connect[8][9] = connect[9][8] = 1;     // 18-20
//     connect[8][7] = connect[7][8] = 1;     // 18-16

//     connect[7][8] = connect[8][7] = 1;     // 16-18
//     connect[7][6] = connect[6][7] = 1;     // 16-14

//     connect[6][5] = connect[5][6] = 1;     // 14-12
//     connect[6][7] = connect[7][6] = 1;     // 14-16

//     connect[5][6] = connect[6][5] = 1;     // 12-14
//     connect[5][4] = connect[4][5] = 1;     // 12-10
// }


// int LED_TIME[MAX_LED] = {0};
// int dx[2]={-1,1};
// int visited[MAX_LED];
// typedef struct {
//   int x;
//   int t;
// } Point;

// long long time=101;

// const int MAX_SIZE = 100;
// struct Point queue[MAX_SIZE];
// int front = 0, rear = 0;

// void enqueue(struct Point val) {
//   if (rear < MAX_SIZE) {
//     queue[rear++] = val;
//   }
// }

// struct Point dequeue() {
//   if (front < rear) {
//     return queue[front++];
//   }
//   struct Point empty = {-1, -1};
//   return empty; // 빈 큐
// }

// bool isEmpty() {
//   return front == rear;
// }

// void bfs(int t,int x,int before){
//   x=POT_to_LED[x];
//   before=POT_to_LED[before];

//   for(int i=0;i<MAX_LED;i++)visited[i]=0;
//   front=rear=0;
//   t=N/(t+1);
//   enqueue({x,t});
//   visited[x]=1;
//   visited[before]=1;
//   while(!isEmpty()){
//     struct Point tmp = dequeue();
//     //나중에 자동으로 꺼지게끔. 근데 지금은 귀찮아.
//     if(tmp.t<=0)break;
//     if(tmp.t>=2*t/3) digitalWrite(LED_PIN[tmp.x], HIGH);
//     else digitalWrite(YEL_PIN[tmp.x], HIGH);
//     for(int i=0;i<MAX_LED;i++){
//       if(!connect[tmp.x][i])continue;
//       if(tmp.x==i)continue;
//       if(visited[i])continue;
//       //if(tmp.x==before)continue;
//       if(tmp.x<0||tmp.x>=MAX_LED)continue;
//       enqueue({i,tmp.t-M});
//       visited[i]=1;
//     }

//     // for(int i=0;i<2;i++){
//     //   int tmpx=tmp.x+dx[i];
//     //   int tmpt=tmp.t;
//     //   if(tmpx==before)continue;
//     //   if(tmpx<0||tmpx>=MAX_LED)continue;
//     //   if(visited[tmpx])continue;
//     //   enqueue({tmpx,tmpt-M});
//     //   visited[tmpx]=1;
//     // }
//   }
// }




// void setup() {
//   Serial.begin(9600);           // 시리얼 통신 시작
//   for(int i=0;i<MAX_LED;i++)
//     pinMode(LED_PIN[i], OUTPUT);  
//   init_connect();

// }
// void loop() {

  
//   for(int i=0;i<MAX_POT;i++){
//     int val = analogRead(POT_PIN[i]);  // POT_PIN에서 아날로그 값 읽기
    
//     // 조도 센서 값 시리얼 모니터에 출력
//     Serial.print("Sensor ");
//     Serial.print(i);
//     Serial.print(": ");
//     Serial.println(val);

//     if(val<L_LIMIT){
//       if(time - POT_TIME[i]<T_LIMIT)continue;
//       Serial.println("CAR!");
//       Serial.println((int)time);
//       Serial.println();
//       POT_TIME[i]=time;
//       for(int j=0;j<2;j++){
//         if(i+dx[j]<0 || i+dx[j]>=MAX_POT)continue;
//         if(time-POT_TIME[i+dx[j]]<=T_LIMIT){
//           bfs(time-POT_TIME[i+dx[j]],i,i+dx[j]);
//         }
//       }
//     }
//   }
  

//   // if (val < 100) {
//   //   digitalWrite(LED_PIN, HIGH);  // 밝기가 낮으면 LED 켜기
//   // } else {
//   //   digitalWrite(LED_PIN, LOW);   // 밝기가 높으면 LED 끄기
//   // }
//   if(time % RESET == 0){
//     for(int i = 0; i < MAX_LED; i++){
//       digitalWrite(LED_PIN[i], LOW);
//       digitalWrite(YEL_PIN[i], LOW);
//     }
//   }
//   delay(500);
//   time++;
// }



