#include <SPI.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define PUSH_UP 5
#define PUSH_DOWN 6
#define PUSH_LEFT 7
#define PUSH_RIGHT 8
#define PUSH_ENTER 9  
#define RELAY_PIN 3
#define BUZZER_PIN 10
#define GREEN_LED 11 
#define RED_LED 12
  byte i = 0;
  byte j = 0;
  byte Hours = 0;
  byte Mins = 0;
  byte Seconds = 5;
  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{  
   
   pinMode(PUSH_UP, INPUT_PULLUP);
   
   pinMode(PUSH_DOWN, INPUT_PULLUP);
   
   pinMode(PUSH_LEFT, INPUT_PULLUP);
   
   pinMode(PUSH_RIGHT, INPUT_PULLUP);
   
   pinMode(PUSH_ENTER, INPUT_PULLUP);

   pinMode(BUZZER_PIN,OUTPUT);

   pinMode(RELAY_PIN,OUTPUT);
   
   Serial.begin(9600);
   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
   Serial.println(F("SSD1306 allocation failed"));
   for (;;);
   }

}

void loop()
{  
   digitalWrite(RELAY_PIN,LOW);
   display.clearDisplay();
   printText();
   delay(2000);
    ModeCheck();
 
    delay(500);
    SetTime();
       if(i==0 || i==2){
      digitalWrite(RELAY_PIN,LOW);
    }
    else if(i==3){
      digitalWrite(RELAY_PIN,HIGH);
    }
    StartTimer();
     if(i==0 || i==2){
      digitalWrite(RELAY_PIN,HIGH);
    }
    else if(i==3){
      digitalWrite(RELAY_PIN,LOW);
    }
    ProgramComplete();
    i=0;
   while(digitalRead(PUSH_ENTER)==HIGH){
     
    }
     digitalWrite(BUZZER_PIN,HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN,LOW);
    delay(100);
    digitalWrite(BUZZER_PIN,HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN,LOW);
    delay(100);
}
void SetTime(){
  display.clearDisplay();
    display.setTextSize(2);             
    display.setTextColor(WHITE); 
    display.setCursor(12,10);
    display.print("Set Timer");
    display.setCursor(15, 40);
CheckHourFormat();
Serial.print(Hours);
Serial.print(':');
    display.print(Hours); 
    display.print(':');
CheckMinFormat();
Serial.print(Mins);
Serial.print(':');
    display.print(Mins); 
    display.print(':');
CheckSecFormat();
Serial.println(Seconds);
    display.print(Seconds);
    if(j == 0){
    display.setCursor(15, 48);
    display.print("__"); 
    }
    else if(j==1){
       display.setCursor(51, 48);
    display.print("__"); 
    }
    else if(j == 2){

       display.setCursor(87, 48);
    display.print("__"); 
    }
    else{
         display.setCursor(20, 48);
    display.print("__"); 
    }
     display.display();
    
delay(200);

    while(digitalRead(PUSH_UP) && digitalRead(PUSH_DOWN) && digitalRead(PUSH_LEFT) && digitalRead(PUSH_RIGHT) && digitalRead(PUSH_ENTER) == HIGH){}
    
 digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);
    if(digitalRead(PUSH_ENTER) == LOW){
        delay(100);
  digitalWrite(BUZZER_PIN,HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN,LOW);
    delay(100);
  digitalWrite(BUZZER_PIN,HIGH);
  delay(300);
  digitalWrite(BUZZER_PIN,LOW);
      return;
    }
    
    if(digitalRead(PUSH_UP) == LOW){
      if(j == 2)
      if(Seconds<59)
      Seconds++;

      if(j == 1)
      if(Mins<59)
      Mins++;

      if(j == 0)
      if(Hours<25)
      Hours++;

      SetTime();

      delay(100);
      
    }
    else if(digitalRead(PUSH_DOWN) == LOW){
       if(j == 2)
      if(Seconds>0)
      Seconds--;

      if(j == 1)
      if(Mins>0)
      Mins--;

      if(j == 0)
      if(Hours>0)
      Hours--;
      
      SetTime();
      delay(100); 
    
    } else if(digitalRead(PUSH_LEFT) == LOW){
      if(j>0)
      j--;
      SetTime();
      delay(100);
    } else if(digitalRead(PUSH_RIGHT) == LOW){
      if(j<2)
      j++;
      SetTime();
      delay(100);
    } else {
      SetTime();
    }
    
  delay(500);
}

 void ModeStart(){
  display.clearDisplay();
  display.setTextSize(2);            
  display.setTextColor(WHITE);
  display.setCursor(5, 25);  
  display.print("*");         
  display.print("Power ON");  
  display.setCursor(15, 45); 
  display.print("Power OFF");

}

void ModeCheck()
{
  display.setCursor(5, 3);  
  display.print("Select To:");
   
  if(i == 0){
  ModeStart();
  i = 2;
  }
  
  if(digitalRead(PUSH_UP) == LOW && digitalRead(PUSH_DOWN) == HIGH ){
 digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);
  display.clearDisplay();
  display.setTextSize(2);            
  display.setTextColor(WHITE);
   display.setCursor(5, 3);  
  display.print("Select To:");
  
  display.setCursor(5, 25);  
  display.print("*");         
  display.print("Power ON");  
  display.setCursor(15, 45); 
  display.print("Power OFF");
  i = 2;
  }
   else if(digitalRead(PUSH_DOWN) == LOW && digitalRead(PUSH_UP) == HIGH){
     digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);
  display.clearDisplay();
  display.setTextSize(2);            
  display.setTextColor(WHITE);
   display.setCursor(5, 3);  
  display.print("Select To:");
  display.setCursor(15, 25);  
  display.print("Power ON");
  display.setCursor(5, 45); 
  display.print("*");         
  display.print("Power OFF");
  i = 3;
   }
  display.display();



  if(digitalRead(PUSH_ENTER) == LOW){
   digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);

  return;
  }  else
  ModeCheck();
}

void PrintTime(){
    display.clearDisplay();
    display.setTextSize(2);             // The fontsize
    display.setTextColor(WHITE); 
     display.setCursor(28, 2);           // Start at top-left corner
     display.print("Timer"); 
     display.setCursor(20, 19);           // Start at top-left corner
     display.print("Running");
    display.setCursor(15, 42);
CheckHourFormat();
Serial.print(Hours);
Serial.print(':');
    display.print(Hours); 
    display.print(':');
CheckMinFormat();
Serial.print(Mins);
Serial.print(':');
    display.print(Mins); 
    display.print(':');
CheckSecFormat();
Serial.println(Seconds);
    display.print(Seconds); 
    display.display();
delay(992);
ClearScreen();
display.clearDisplay();
}


void ClearScreen(){  
    Serial.write(0x0C);
}

void CheckHourFormat(){
  if(Hours<=9){
     Serial.print('0');
     display.print('0');
  }
}

void CheckMinFormat(){

  if(Mins<=9){
     Serial.print('0');
     display.print('0');
  }
}


void CheckSecFormat(){

  if(Seconds<=9){
     Serial.print('0');
     display.print('0');
  }
}


void StartTimer(){
  if(Hours == 0 && Mins == 0 && Seconds == 0){
     Serial.println("Time Reached");
     display.clearDisplay();
     display.setTextSize(2);             // The fontsize
     display.setTextColor(WHITE);       // Draw white text
     display.setCursor(40, 15);           // Start at top-left corner
     display.print("Time"); 
     display.setCursor(20, 35);           // Start at top-left corner
     display.print("Reached"); 
     display.display();

     digitalWrite(BUZZER_PIN,HIGH);
     delay(1000);
     digitalWrite(BUZZER_PIN,LOW);
     
  
  }else{

    while(Seconds > 0){
        Seconds--;
        PrintTime();
        if(digitalRead(PUSH_ENTER)==LOW){
           digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);
       delay(100);
  digitalWrite(BUZZER_PIN,HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN,LOW);
          return;
        }
    }
    if(Seconds == 0 && Mins >0){
      Mins--;
      Seconds = 60;
      StartTimer();
      
    }
   if(Seconds == 0 && Mins == 0 && Hours>0){
     Hours--;
     Mins=60; 
     StartTimer();
   } 
  StartTimer();
  } 
}


void printText() {
  display.clearDisplay();
  display.setTextSize(2);             // The fontsize
  display.setTextColor(WHITE);       // Draw white text
  display.setCursor(5, 5);           // Start at top-left corner
  display.print("Investor's");  
  display.setCursor(20, 30);           // Start at top-left corner
  display.print("Logo");
  display.display();
  display.startscrollright(0x00, 0x07);
  digitalWrite(BUZZER_PIN,HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN,LOW);
  display.stopscroll();
  delay(500);
    digitalWrite(BUZZER_PIN,HIGH);
  display.startscrollleft(0x00, 0x07);
  delay(100);
    digitalWrite(BUZZER_PIN,LOW);
     delay(100);
  digitalWrite(BUZZER_PIN,HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN,LOW);
  delay(100);
  digitalWrite(BUZZER_PIN,HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN,LOW);
  display.stopscroll();
 
  display.clearDisplay();
}

void ProgramComplete(){
  if(i == 2){
  display.clearDisplay();
  display.setTextSize(2);             // The fontsize
  display.setTextColor(WHITE);       // Draw white text
  display.setCursor(20, 5);           // Start at top-left corner
  display.print("POWER IS");  
  display.setCursor(50, 30);           // Start at top-left corner
  display.print("ON");
  display.display();
  }
  else if(i == 3){
      display.clearDisplay();
  display.setTextSize(2);             // The fontsize
  display.setTextColor(WHITE);       // Draw white text
  display.setCursor(20, 5);           // Start at top-left corner
  display.print("POWER IS");  
  display.setCursor(45, 30);           // Start at top-left corner
  display.print("OFF");
  display.display();
  }
 digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);
 delay(100);
 digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);
  delay(100);
 digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);
       delay(100);
 digitalWrite(BUZZER_PIN,HIGH);
     delay(100);
     digitalWrite(BUZZER_PIN,LOW);
  
}
