// 초음파 센서 핀번호 설정
int RTrigPin = 13;    // Volume trig pin      |         13 | Trig
int REchoPin = 12;    // Volume echo pin      |         12 | Echo
int LTrigPin = 11;    // Scale  trig pin      |         11 | Trig
int LEchoPin = 10;    // Scale  echo pin      |         10 | Echo
int switchRecPin = 9; // Record switch pin    |          9 | +
int switchPlyPin = 8; // Play switch pin      |          8 | +
int LEDPin = 7;       // LED pin              |          7 | +
int piezoPin = 6;     // Piezo buzzer pin     |          6 | +
// 초음파센서로 받은 값 저장
float valueR;  // Right value (volume)
float valueL;  // Left value (scale)
// 음계와 음량 값
int valueV;   // Volume value
int valueS;   // Scale value
// 녹음 스위치 Debounce 설정
int stateLED = LOW;    // state of LED
int readSR;            // state of switchRec
int prevSR = LOW;      // prevoius state of switchRec
long timeTg = 0;       // time LED toggled at
long debounce = 100;   // debounce time
// 작업 상태
char work;       // now work state : 'n' - normal, 'r' - record
                 //                  'p' - play record file
// 음계
char scale;      // a : 도   b : 레   c : 미   d : 파
                 // e : 솔   f : 파   g : 시   h : (높은)도
                 // x : 없음
// 녹음 저장 공간
int recordVolume[1000];  // record volume here
char recordScale[1000];  // record scale here
int recordN = 0;         // recordFile array index

void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(RTrigPin, OUTPUT);
  pinMode(REchoPin, INPUT);
  pinMode(LTrigPin, OUTPUT);
  pinMode(LEchoPin, INPUT);
  // switch 입력모드로 설정, 아두이노 내부 풀업저항 사용
  pinMode(switchRecPin, INPUT_PULLUP);
  pinMode(switchPlyPin, INPUT_PULLUP);
  // LED 출력모드로 설정
  pinMode(LEDPin, OUTPUT);
  // piezo 출력모드로 설정
  pinMode(piezoPin, OUTPUT);
} // setup()

  void loop() {

    // switchPly가 눌려지면 녹음 파일 재생
    if(digitalRead(switchPlyPin) == LOW) {
      for(int i = 0; i <= recordN; i++)
        readRecord(recordVolume[i], recordScale[i]);
    }
    
    readSR = digitalRead(switchRecPin);   // switchRec 상태 읽음
    // switchRec가 눌려졌고 스위치 토글 경과 시간이 debounce 시간보다 크면 실행
    if(readSR == HIGH && prevSR == LOW && (millis() - timeTg > debounce)) {
      if(stateLED == HIGH) { // LED가 HIGH면 LOW로 바꿔준다
        stateLED = LOW;
        work = 'n';
      }
      else {                 // LED가 LOW면 HIGH로 바꿔준다
        stateLED = HIGH;
        work = 'r';
        recordN = 0;        // work가 'n' -> 'r'로 바뀌면 recordN 초기화
      }
      timeTg = millis();
    }
    digitalWrite(LEDPin, stateLED);
    prevSR = readSR;

    // 초음파센서R, 초음파를 보냄, 다 보낸 후 echoPin이 HIGH 상태로 대기
    digitalWrite(RTrigPin, HIGH);
    delay(5);
    digitalWrite(RTrigPin, LOW);
    // echoPin이 HIGH를 유지한 시간을 저장
    valueR = pulseIn(REchoPin, HIGH);

    // 초음파센서L
    digitalWrite(LTrigPin, HIGH);
    delay(5);
    digitalWrite(LTrigPin, LOW);
    valueL = pulseIn(LEchoPin, HIGH);

    // 읽은 초음파 값 시리얼 출력
    Serial.print(valueR);
    Serial.print(", ");
    Serial.println(valueL);

    // 읽은 초음파 값을 음계와 음량으로 변환
    getVolume();
    scale = getScale();
    Serial.print(valueV);
    Serial.print(" => ");
    Serial.println(scale);

    // 작업상태가 record이면 연주 기록 저장
    if(work == 'r') {
      recordN++;
      recordVolume[recordN] = valueV;
      recordScale[recordN] = scale;
    }
    
} // loop()

void getVolume() {
  if(valueR < 200)
    valueV = 0;
  else if (valueR > 1400)
    valueV = 300;
  else
    valueV = map(valueR, 200, 1400, 0, 300);
}
char getScale() {
  if( (valueL > 200) && (valueL <= 350) ) { // 거리가 200 ~ 350 이면 '도'
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1911 - valueV);
    }
      return 'a';
  }
  else if( (valueL > 350) && (valueL <= 500) ) { // 거리가 350 ~ 500 이면 '레'
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1702 - valueV);
    }
      return 'b';
  }
  else if( (valueL > 500) && (valueL <= 650) ) { // 거리가 500 ~ 650 이면 '미'
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1517 - valueV);
    }
      return 'c';
  }
  else if( (valueL > 650) && (valueL <= 800) ) { // 거리가 650 ~ 800 이면 '파'
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1431 - valueV);
    }
      return 'd';
  }
  else if( (valueL > 800) && (valueL <= 950) ) { // 거리가 800 ~ 950 이면 '솔'
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1276 - valueV);
    }
      return 'e';
  }
  else if( (valueL > 950) && (valueL <= 1100) ) { // 거리가 950 ~ 1100 이면 '라'
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1137 - valueV);
    }
      return 'f';
  }
  else if( (valueL > 1100) && (valueL <= 1250) ) { // 거리가 1100 ~ 1250 이면 '시'
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1012 - valueV);
    }
      return 'g';
  }
  else if( (valueL > 1250) && (valueL <= 1400) ) { // 거리가 1250 ~ 1400 이면 '(높은)도'
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 965 - valueV);
    }
      return 'h';
  }
  else {
    delayMicroseconds(1000);
    return 'x';
  }
} // getScale()
void readRecord(int vol, char sc) {
  if( sc == 'a' ) {   // 'a'를 읽으면 '도'재생
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(vol);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1911 - valueV);
    }
  }
  else if( sc == 'b' ) { // 'b'를 읽으면 '레'재생
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(vol);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1702 - valueV);
    }
  }
  else if( sc == 'c' ) { // 'c'를 읽으면 '미'재생
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(vol);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1517 - valueV);
    }
  }
  else if( sc == 'd' ) { // 'd'를 읽으면 '파'재생
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1431 - valueV);
    }
  }
  else if( sc == 'e' ) { // 'e'를 읽으면 '솔'재생
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(vol);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1276 - valueV);
    }
  }
  else if( sc == 'f' ) { // 'f'를 읽으면 '라'재생
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(vol);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1137 - valueV);
    }
  }
  else if( sc == 'g' ) { // 'g'를 읽으면 '시'재생
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(vol);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1012 - valueV);
    }
  }
  else if( sc == 'h' ) { // 'h'를 읽으면 '도'재생
    for(long i = 0; i < 1000000; i = i + 2552) {
      digitalWrite(piezoPin, 1);
      delayMicroseconds(vol);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 965 - valueV);
    }
  }
    else if(sc == 'x') { // 'x'를 읽으면 1초 쉼
      delayMicroseconds(1000);
  }
} // readRecord()

