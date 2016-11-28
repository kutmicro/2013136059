// Piezo_Test.ino : 피에조부저 테스트 코드

// 피에조부저 핀번호 설정
int piezoPin = 6;

// 음량 설정(0 ~ 1023)
int valueV = 30;

void setup() {
  pinMode(piezoPin, OUTPUT);  // fiezoPin 출력모드 설정
}

void loop() {
  
  for(long i = 0; i < 1000000; i = i + 2552) {  // '도'
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1911 - valueV);
  }
  delay(500);
  for(long i = 0; i < 1000000; i = i + 2552) {  // '레'
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1702 - valueV);
  }
  delay(500);
  for(long i = 0; i < 1000000; i = i + 2552) {  // '미'
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1517 - valueV);
  }
  delay(500);
  for(long i = 0; i < 1000000; i = i + 2552) {  // '파'
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1431 - valueV);
  }
  delay(500);
  for(long i = 0; i < 1000000; i = i + 2552) {  // '솔'
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1276 - valueV);
  }
  delay(500);
  for(long i = 0; i < 1000000; i = i + 2552) {  // '라'
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1137 - valueV);
  }
  delay(500);
  for(long i = 0; i < 1000000; i = i + 2552) {  // '시'
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 1012 - valueV);
  }
    delay(500);
  for(long i = 0; i < 1000000; i = i + 2552) {  // '도'
      digitalWrite(piezoPin, 1);
      delayMicroseconds(valueV);
      digitalWrite(piezoPin, 0);
      delayMicroseconds(2 * 965 - valueV);
  }
  delay(500);
} // loop()
