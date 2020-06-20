#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define engine 2
#define heating 3
#define cold 4
#define uv 5

#define start 12
#define done 11
#define select 10
#define up 9
#define down 8

#define security 7

LiquidCrystal_I2C lcd(0x3F, 16, 2);

unsigned long timer = 0;

int menu = 0, intership = 0;

long engineTime = 60;
long heatingTime = 60;
long coldTime = 60;
long uvTime = 60;

long saveTimeEngine;
long saveTimeHeating;
long saveTimeCold;
long saveTimeUv;

void engineControl(){
  if(digitalRead(engine) == 0){
    digitalWrite(engine, 1);
  }else if(digitalRead(engine) == 1){
    digitalWrite(engine, 0);
  }
}

void heatingControl(){
  if(digitalRead(heating) == 0){
    digitalWrite(heating, 1);
  }else if(digitalRead(heating) == 1){
    digitalWrite(heating, 0);
  }
}

void coldControl(){
  if(digitalRead(cold) == 0){
    digitalWrite(cold, 1);
  }else if(digitalRead(cold) == 1){
    digitalWrite(cold, 0);
  }
}

void uvControl(){
  if(digitalRead(uv) == 0){
    digitalWrite(uv, 1);
  }else if(digitalRead(uv) == 1){
    digitalWrite(uv, 0);
  }
}

int botoes(){
  if(digitalRead(start) == 0){
    return 1;
  }else if(digitalRead(done) == 0){
    return 2;
  }else if(digitalRead(select) == 0){
    return 3;
  }else if(digitalRead(up) == 0){
    return 4;
  }else if(digitalRead(down) == 0){
    return 5;
  }

  return 0;
}

void displayInit(){
  int pcm = 0;

  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("CPM");
  lcd.setCursor(0, 1);
  lcd.print("Circuital Printing Machine");

  delay(2500);

  for(int c = 0; c < 10; c++){
    lcd.setCursor(pcm, 0);
    lcd.print("       CPM");
    lcd.scrollDisplayLeft();

    delay(500);

    pcm++;
  }

  delay(500);

  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("CPM");
  lcd.setCursor(0, 1);
  lcd.print("Version: 1.5");

  delay(1500);

  displayMenu(menu);
}

void displayMenu(int type){
  switch(type){
    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Motor");
      lcd.setCursor(0, 1);
      lcd.print("Tempo:");
      lcd.setCursor(7, 1);
      lcd.print(engineTime / 60);
      lcd.setCursor(10, 1);
      lcd.print("Minuto");
      break;

    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Aquecer");
      lcd.setCursor(0, 1);
      lcd.print("Tempo:");
      lcd.setCursor(7, 1);
      lcd.print(heatingTime / 60);
      lcd.setCursor(10, 1);
      lcd.print("Minuto");
      break;

    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Esfriar");
      lcd.setCursor(0, 1);
      lcd.print("Tempo:");
      lcd.setCursor(7, 1);
      lcd.print(coldTime / 60);
      lcd.setCursor(10, 1);
      lcd.print("Minuto");
      break;

    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Luz UV");
      lcd.setCursor(0, 1);
      lcd.print("Tempo:");
      lcd.setCursor(7, 1);
      lcd.print(uvTime / 60);
      lcd.setCursor(10, 1);
      lcd.print("Minuto");
      break;
  }
}

void displayEnter(int type){
  switch(type){
    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alterar Motor");
      lcd.setCursor(0, 1);
      lcd.print("Tempo:");
      lcd.setCursor(7, 1);
      lcd.print(engineTime / 60);
      lcd.setCursor(10, 1);
      lcd.print("Minuto");
      break;

    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alterar Aquecer");
      lcd.setCursor(0, 1);
      lcd.print("Tempo:");
      lcd.setCursor(7, 1);
      lcd.print(heatingTime / 60);
      lcd.setCursor(10, 1);
      lcd.print("Minuto");
      break;

    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alterar Esfriar");
      lcd.setCursor(0, 1);
      lcd.print("Tempo:");
      lcd.setCursor(7, 1);
      lcd.print(coldTime / 60);
      lcd.setCursor(10, 1);
      lcd.print("Minuto");
      break;

    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alterar Luz UV");
      lcd.setCursor(0, 1);
      lcd.print("Tempo:");
      lcd.setCursor(7, 1);
      lcd.print(uvTime / 60);
      lcd.setCursor(10, 1);
      lcd.print("Minuto");
      break;
  }
}

void displayDone(){
  intership = 0;

  engineTime = saveTimeEngine;
  heatingTime = saveTimeHeating;
  coldTime = saveTimeCold;
  uvTime = saveTimeUv;
  
  displayMenu(menu);
}

void displaySelect(){
  if(intership == 0){
    saveTimeEngine = engineTime;
    saveTimeHeating = heatingTime;
    saveTimeCold = coldTime;
    saveTimeUv = uvTime;
    
    displayEnter(menu);
    intership = 1;
  }else if(intership == 1){
    intership = 0;

    saveTimeEngine = engineTime;
    saveTimeHeating = heatingTime;
    saveTimeCold = coldTime;
    saveTimeUv = uvTime;
    
    displayMenu(menu);
  }
}

void displayUp(){
  if(menu > 0){
    menu--;
  }else{
    menu = 3;
  }

  displayMenu(menu);
}

void displayDown(){
  if(menu < 3){
    menu++;
  }else{
    menu = 0;
  }

  displayMenu(menu);
}

void timeUp(){
  switch(menu){
    case 0:
      if(engineTime < 600){
        engineTime += 60;
      }
      break;

    case 1:
      if(heatingTime < 600){
        heatingTime += 60;
      }
      break;

    case 2:
      if(coldTime < 600){
        coldTime += 60;
      }
      break;

    case 3:
      if(uvTime < 600){
        uvTime += 60;
      }
      break;
  }

  displayEnter(menu);
}

void timeDown(){
  switch(menu){
    case 0:
      if(engineTime > 60){
        engineTime -= 60;
      }
      break;

    case 1:
      if(heatingTime > 60){
        heatingTime -= 60;
      }
      break;

    case 2:
      if(coldTime > 60){
        coldTime -= 60;
      }
      break;

    case 3:
      if(uvTime > 60){
        uvTime -= 60;
      }
      break;
  }

  displayEnter(menu);
}

void startProcess(){
  long timeOne = engineTime * 1000;
  long timeTwo = heatingTime * 1000;
  long timeThree = coldTime * 1000;
  long timeFour = uvTime * 1000;

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Processo em");
  lcd.setCursor(2, 1);
  lcd.print("Andamento...");

  delay(3000);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Processo de");
  lcd.setCursor(1, 1);
  lcd.print("Centrifugacao");

  timer = millis();
  
  while(true){
    if(digitalRead(security) == 0){
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Processo");
      lcd.setCursor(2, 1);
      lcd.print("Interrompido");

      digitalWrite(engine, 1);
      
      while(digitalRead(security) == 0){
        
      }
    }
    
    if((millis() - timer) < timeOne){
      digitalWrite(engine, 0);
    }else{
      digitalWrite(engine, 1);
      break;
    }
  }

  delay(500);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Processo de");
  lcd.setCursor(3, 1);
  lcd.print("Aquecimeto");

  timer = millis();
  
  while(true){
    if((millis() - timer) < timeTwo){
      digitalWrite(heating, 0);
    }else{
      digitalWrite(heating, 1);
      break;
    }
  }

  delay(500);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Processo de");
  lcd.setCursor(2, 1);
  lcd.print("Esfriamento");

  timer = millis();

  while(true){
    if((millis() - timer) < timeThree){
      digitalWrite(cold, 0);
    }else{
      digitalWrite(cold, 1);
      break;
    }
  }

  delay(500);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Processo de");
  lcd.setCursor(4, 1);
  lcd.print("Raios UV");

  timer = millis();

  while(true){
    if((millis() - timer) < timeFour){
      digitalWrite(uv, 0);
    }else{
      digitalWrite(uv, 1);
      break;
    }
  }

  delay(500);

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Processo");
  lcd.setCursor(3, 1);
  lcd.print("Finalizado");

  delay(5000);

  displayMenu(menu);
}

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  pinMode(engine, OUTPUT);
  pinMode(heating, OUTPUT);
  pinMode(cold, OUTPUT);
  pinMode(uv, OUTPUT);
  
  pinMode(start, INPUT_PULLUP);
  pinMode(done, INPUT_PULLUP);
  pinMode(select, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);

  pinMode(security, INPUT_PULLUP);

  digitalWrite(engine, 1);
  digitalWrite(heating, 1);
  digitalWrite(cold, 1);
  digitalWrite(uv, 1);

  displayInit();
}

void loop() {
  int menu = 0;
  boolean sec = digitalRead(security);

  menu = botoes();
  
  switch(menu){
    case 1:
      if(intership == 0){
        if(sec == 0){
          startProcess();
        }
      }
      break;
      
    case 2:
      displayDone();
      delay(250);
      break;
      
    case 3:
      displaySelect();
      delay(250);
      break;
      
    case 4:
      if(intership == 0){
        displayUp();
      }else if(intership == 1){
        timeUp();
      }
      
      delay(250);
      break;
      
    case 5:
      if(intership == 0){
        displayDown();
      }else if(intership == 1){
        timeDown();
      }
      
      delay(250);
      break;
  }
}
