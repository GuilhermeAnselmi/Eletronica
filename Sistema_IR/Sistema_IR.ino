#include <IRremote.h>

#define sensor 11
#define buz 12
#define s4 8
#define s3 7
#define s2 6
#define s1 5

IRrecv IR (sensor);
decode_results comando;

int volume = 25;

void setup() {
  Serial.begin(9600);
  IR.enableIRIn();

  pinMode(buz, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s1, OUTPUT);
  
  Serial.println("IR Iniciado");

  analogWrite(buz, volume);
  digitalWrite(s4, 1);
  digitalWrite(s3, 1);
  digitalWrite(s2, 1);
  digitalWrite(s1, 1);
}

void loop() {
  if(IR.decode(&comando)){
    Serial.println(comando.value, HEX);

    switch(comando.value){
      case(0x77E1D0A3): {
        if(volume < 25){
          buzzer(volume += 5);
        }
        break;
      }
      case(0x77E1B0A3): {
        if(volume > 0){
          buzzer(volume -= 5);
        }
        break;
      }
    }

    if(volume == 25){
      digitalWrite(s4, 1);
    } else if(volume < 25){
      digitalWrite(s4,  0);
    }

    if(volume == 20){
      digitalWrite(s3, 1);
    } else if(volume < 20){
      digitalWrite(s3,  0);
    }

    if(volume == 15){
      digitalWrite(s2, 1);
    } else if(volume < 15){
      digitalWrite(s2,  0);
    }

    if(volume == 10){
      digitalWrite(s1, 1);
    } else if(volume < 10){
      digitalWrite(s1,  0);
    }
    
    IR.resume();
  }
}

void buzzer(int vol){
  analogWrite(buz, vol);
  Serial.println(vol);
}
