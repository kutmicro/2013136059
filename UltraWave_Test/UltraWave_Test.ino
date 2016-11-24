// UltraWave_Test.ino : 초음파 센서 테스트 코드

// 초음파 센서 핀번호 설정
int echoPin = 12;
int trigPin = 13;

void setup() {
  Serial.begin(9600);     // 시리얼 통신속도 설정
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float duration;       // 초음파가 되돌아도는 데까지 걸리는 시간
  float distance;       // 측정한 거리

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  // echoPin 이 HIGH를 유지한 시간을 저장한다.
  duration = pulseIn(echoPin, HIGH);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance = ((float)(340 * duration) / 10000) / 2;

  // 계산한 거리 시리얼 모니터에 출력
  Serial.print(distance);
  Serial.println("cm");
  delay(1000);
}
