#define en 2
#define rele 4
#define led 3

void setup() {
  pinMode(rele, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(en, INPUT);

  digitalWrite(rele, 0);
  digitalWrite(led, 0);
}
boolean est = 0;

void loop() {
  if(digitalRead(en) == 0){
    if(est == 1){
      est = 0;
    }else{
      est = 1;
    }

    delay(50);
  }

  if(est == 0){
    digitalWrite(rele, 1);
    digitalWrite(led, 1);
  }else{
    digitalWrite(rele, 0);
    digitalWrite(led, 0);
  }
}
