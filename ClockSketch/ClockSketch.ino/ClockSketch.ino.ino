#define LED_PIN 2
#define LED_PIN2 3
#define rfReceivePin A1

unsigned int data = 0;
 
int tenSeconds = 0;
int seconds = 0;
int tenthSeconds = 0;

//int LED_Pin = 6;

//   f                         0: a,b,d,h,f,g    1: h,d    2: f,h,e,a,b    3:f,h,e,d,b
// g   h                       4: g,e,h,d        5: f,g,e,d,b              6: f,g,e,a,b,d
//   e                         7: f,h,d          8: a,b,d,e,g,h,f          9: f,h,g,d
// a   d
//   b    c

//for the mini seven segment displays
/*
int a[] = {2,10,18};
int b[] = {3,11,19};
int c[] = {4,12,20};
int d[] = {5,13,21};
int e[] = {6,14,22};
int f[] = {7,15,24};
int g[] = {8,16,26};
int h[] = {9,17,28};
*/

/* switched ssd 1 and 3
int a[] = {2,32,18};
int b[] = {3,34,19};
int c[] = {4,36,20};
int d[] = {5,38,21};
int e[] = {6,40,22};
int f[] = {7,42,24};         
int g[] = {48,44,26};
int h[] = {50,46,28};
*/

int a[] = {18,32,2};
int b[] = {19,34,3};
int c[] = {20,36,4};
int d[] = {21,38,5};
int e[] = {22,40,6};
int f[] = {24,42,7};         
int g[] = {26,44,48};
int h[] = {28,46,50};

int buttonPins[] = {52,53,51,49,47};
int Count = 0;
int FailCount = 0;
int numReceived = 0;

int currentButton = 0;
int currentButtonWireless = 0;
int state = 0;
int wirelessState = 0;

int timeOutCount = 0;

boolean Counting = LOW;

int wiredEnabled = HIGH;

int times[] ={0, 0, 0, 0}; //times[0] = tenseconds     times[1] = seconds      times[2] = tenthseconds      times[3] = (1/100) tenthseconds
void setup() {
  Serial.begin(9600);

  for(int i = 2; i <=50 ; i++){
      pinMode(i, OUTPUT);
  }
  
  for(int i = 0; i < 5; i++) //(46-52) Each of the digital outputs from the receiver module.
    pinMode(buttonPins[i],INPUT);             //14 is the wired button

  clearDisplay();
  displayTime();
}

void loop() {
  updateDisplay(); 

}

void count(){
   //delay(100);
   //Serial.println(state);
   delay(1);
}

void updateDisplay(){
     count();
     clearDisplay();
     displayTime();

   //if(wiredEnabled)
    checkInput();
        
   if(Counting){
      clearDisplay();
      displayTime();
      updateTime();
   }
}


void checkInput(){
  if(state > 5){
    resetTime();
    clearDisplay();
    displayTime();
    state = 0;
    delay(100);
  }
    switch(state){
      case 5:
         if(digitalRead(buttonPins[currentButton]) == LOW){
           state = 0;
           resetTime();
           clearDisplay();
           displayTime();
         }
      break;
        
      case 4:
        if(digitalRead(buttonPins[0])||digitalRead(buttonPins[1])){
          delay(100);
          state+=1;
          currentButton = getButtonNumber();
        }
      break;
      
      case 3:
        if(digitalRead(buttonPins[currentButton]) == LOW){
          state+=1;
        }
      break;
      
      case 2:
        if(digitalRead(buttonPins[0])||digitalRead(buttonPins[1])){
          Counting = LOW;
          delay(100);
          state+=1;
          currentButton = getButtonNumber();
        }
      break;
      
      case 1:
        if(digitalRead(buttonPins[currentButton]) == LOW){
          state+=1;
        }
      break;
      
      case 0:
        if(digitalRead(buttonPins[0])||digitalRead(buttonPins[1])){
          delay(100);
          state+=1;
          Counting = HIGH;
          currentButton = getButtonNumber();
         }
      break;
    }


    switch(wirelessState){
      case 1:
        if(digitalRead(buttonPins[currentButtonWireless]) == LOW)
          wirelessState = 0;
      break;
      case 0:
        if(digitalRead(buttonPins[2]) && Counting == LOW){ //start button
          delay(100);
          state = 2;
          wirelessState+=1;
          Counting = HIGH;
          currentButtonWireless = getButtonNumber();
        }
        if(digitalRead(buttonPins[3])){ //stop button
          delay(100);
          state = 4;
          wirelessState+=1;
          Counting = LOW;
          currentButtonWireless = getButtonNumber();
        }
        
        if(digitalRead(buttonPins[4])){ //reset button
          delay(100);
          state = 0;
          wirelessState+=1;
          resetTime();
          clearDisplay();
          displayTime();
          currentButtonWireless = getButtonNumber();
        }
      break;
    }
}

int getButtonNumber(){
  for(int i =0; i < 2; i++){
    if(digitalRead(buttonPins[i]))
      return i;
  }
}

int getButtonNumberWireless(){
  for(int i = 2; i < 5; i++){
    if(digitalRead(buttonPins[i]))
      return i;
  }
}
    
void resetTime(){
  times[0] = 0;
  times[1] = 0;
  times[2] = 0;
  times[3] = 0;
}

void updateTime(){
   times[3] +=1;
   if(times[3] == 100){
       times[2]+=1;
       times[3] = 0;
   }
   if(times[2] == 10){
       times[1] +=1;
       times[2] = 0;
   }
   if(times[1] == 10){
       times[0] +=1;
       times[1] = 0;
   }
   if(times[0] == 10)
    resetTime();
}

void displayTime(){
    for(int index = 0; index < 3; index++){
      switch(times[index]){
        case 0:
          DispZero(index, 1);
          break;
        case 1:
          DispOne(index, 1);
          break;
        case 2:
          DispTwo(index, 1);
          break;
        case 3:
          DispThree(index, 1); 
          break;
        case 4:
          DispFour(index, 1);
          break;
        case 5:
          DispFive(index, 1);    
          break;   
        case 6:
          DispSix(index, 1);
          break;
        case 7:
          DispSeven(index, 1);    
          break;   
        case 8:
          DispEight(index, 1);
          break;
        case 9:
          DispNine(index, 1);    
          break;   
      }
    }
}

void clearDisplay(){
    for(int i = 2; i <= 50 ; i++){
      digitalWrite(i, LOW);
    }
}

void DispZero(int num, int on){
    digitalWrite(b[num], on);
    digitalWrite(a[num], on);
    digitalWrite(d[num], on);
    digitalWrite(h[num], on);
    digitalWrite(f[num], on);
    digitalWrite(g[num], on);
}

void DispOne(int num, int on){
    digitalWrite(h[num], on);
    digitalWrite(d[num], on);
}

void DispTwo(int num, int on){
    digitalWrite(f[num], on);
    digitalWrite(h[num], on);
    digitalWrite(e[num], on);
    digitalWrite(a[num], on);
    digitalWrite(b[num], on);
}

void DispThree(int num, int on){
    digitalWrite(f[num], on);
    digitalWrite(h[num], on);
    digitalWrite(e[num], on);
    digitalWrite(d[num], on);
    digitalWrite(b[num], on);
}

void DispFour(int num, int on){
    digitalWrite(g[num], on);
    digitalWrite(e[num], on);
    digitalWrite(h[num], on);
    digitalWrite(d[num], on);
}

void DispFive(int num, int on){
    digitalWrite(f[num], on);
    digitalWrite(g[num], on);
    digitalWrite(e[num], on);
    digitalWrite(d[num], on);
    digitalWrite(b[num], on);
}

void DispSix(int num, int on){
    digitalWrite(f[num], on);
    digitalWrite(g[num], on);
    digitalWrite(e[num], on);
    digitalWrite(a[num], on);
    digitalWrite(b[num], on);
    digitalWrite(d[num], on);
}

void DispSeven(int num, int on){
    digitalWrite(f[num], on);
    digitalWrite(h[num], on);
    digitalWrite(d[num], on);
}

void DispEight(int num, int on){
    digitalWrite(a[num], on);
    digitalWrite(b[num], on);
    digitalWrite(d[num], on);
    digitalWrite(e[num], on);
    digitalWrite(g[num], on);
    digitalWrite(h[num], on);
    digitalWrite(f[num], on);
}

void DispNine(int num, int on){
    digitalWrite(f[num], on);
    digitalWrite(h[num], on);
    digitalWrite(g[num], on);
    digitalWrite(d[num], on);
    digitalWrite(e[num], on);
}


