#include <Servo.h>
#include <LiquidCrystal.h>

#define IR1 3
#define IR2 2
Servo myservo; 

const int rs = 11, en = 10, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pos = 0;  
int t1,t2;
int gate_off;
int start;
int velocity;
int n1;
int n2;
int flag;
int duration;
int LED = 12;
void setup() {
  Serial.begin(9600);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(LED,OUTPUT);
  myservo.attach(9);

}

void loop() {
  
  int x = digitalRead(IR1);
  int y = digitalRead(IR2);

  if(flag==0){
    Serial.println("Everything is clear !!!");
    lcd.begin(16,2);
    lcd.print("Everything is ");
    lcd.setCursor(0,1);
    lcd.print("clear!!!"); 
  }
  if(x==LOW && y==LOW){
    if(n1==0){
      n1=0;
      n2=0;
      t1=0;
      t2=0;
      start=0;
      velocity=0;
      duration=0;
      flag=0;
    }
  }
  if(x==LOW && y==HIGH){
    if(n1==0){
      n1=0;
      n2=0;
      t1=0;
      t2=0;
      start=0;
      velocity=0;
      duration=0;
      flag=0;
    }
    if(n1==1){
      t2++;
    }
  }
  if(x==HIGH && y==LOW){   
    t1++;      
  }
  if(x==HIGH && y==HIGH){
    n1=0;
    n2=0;
    t1=0;
    t2=0;
    start=0;
    velocity=0;
    duration=0;
    flag=0;
  }

  if(n1==1 && n2==0){
    start++;
  }
  if(t1>30){/// if greater than 30 than it's a train
    n1=1;   
  }
  if(t2>30){ /// if greater than 30 than it's a train
    n2=1;    
  }
  if(duration > gate_off && y==LOW){
    digitalWrite(LED,LOW);    
    Serial.println("Everything is clear!!!");
    lcd.begin(16,2);
    lcd.print("Everything is");
    lcd.setCursor(0,1);
    lcd.print("Clear !!!");
    
    myservo.write(0);
    duration=0;
    n1=0;
    n2=0;
    t1=0;
    t2=0;
    start=0;
    flag=0;
  }
  if(n1==1 && n2==1){
    if(t1>80){
      gate_off =200;
    }
    else if(t1>60){
      gate_off= 100;
    }
    else if(t1>30){
      gate_off = 50 ; 
    }
   
    flag=1;
    Serial.println("Train arrived!!! Please be safe ");
    duration++; 
    digitalWrite(LED,HIGH); // gate off ;
    myservo.write(120);
    lcd.begin(16,2);
    lcd.print("Train arrived!!!");
      
    
  }
  Serial.print("t1 = ");
  Serial.print(t1);
  Serial.print(" t2 = ");
  Serial.print(t2);
  Serial.print(" n1 = ");
  Serial.println(n1);
//  Serial.print(" n2 = ");
//  Serial.print(n2);
//  Serial.print(" start =");
//  Serial.println(start);
  delay(1);
  



}  
