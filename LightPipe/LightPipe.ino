// 초음파 센서 핀번호 설정
int RTrigPin = 13;    // Volume trig pin      |         13 | Trig
int REchoPin = 12;    // Volume echo pin      |         12 | Echo
int LTrigPin = 11;    // Scale  trig pin      |         11 | Trig
int LEchoPin = 10;    // Scale  echo pin      |         10 | Echo
int switchRec = 9;    // Record switch pin    |          9 | +
int switchPly = 8;    // Play switch pin      |          8 | +
int LED = 7;          // LED pin              |          7 | +
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

void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(RTrigPin, OUTPUT);
  pinMode(REchoPin, INPUT);
  pinMode(LTrigPin, OUTPUT);
  pinMode(LEchoPin, INPUT);
  // switch 입력모드로 설정, 아두이노 내부 풀업저항 사용
  pinMode(switchRec, INPUT_PULLUP);
  pinMode(switchPly. INPUT_PULLUP);
  // LED 출력모드로 설정
  pinMode(LED, OUTPUT);
}

  void loop() {

    readSR = digitalRead(switchRec);   // switchRec 상태 읽음
    // switchRec가 눌려졌고 스위치 토글 경과 시간이 debounce 시간보다 크면 실행
    if(readSR == HIGH && prevSR == LOW && (millis() - timeTg > debounce) {
      if(stateLED == HIGH) { // LED가 HIGH면 LOW로 바꿔준다
        stateLED = LOW;
      }
      else                  // LED가 LOW면 HIGH로 바꿔준다
        stateLED = HIGH;
      timeTg = millis();
    }
    digitalWrite(LED, stateLED);
    previous = readSR;

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

    Serial.print(valueR);
    Serial.print(", ");
    Serial.println(valueL);
    
}
