int tenSeconds = 0;
int seconds = 0;
int tenthSeconds = 0;

//int LED_Pin = 6;

//   f                         0: a,b,d,h,f,g    1: h,d    2: f,h,e,a,b    3:f,h,e,d,b
// g   h                       4: g,e,h,d        5: f,g,e,d,b              6: f,g,e,a,b,d
//   e                         7: f,h,d          8: a,b,d,e,g,h,f          9: f,h,g,d
// a   d
//   b    c

//for small displays
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


int a[] = {2,32,18};
int b[] = {3,34,19};
int c[] = {4,36,20};
int d[] = {5,38,21};
int e[] = {6,40,22};
int f[] = {7,42,24};
int g[] = {8,44,26};
int h[] = {9,46,28};


int buttonPin = 0;

int state = 0;
boolean Counting = LOW;

int times[] ={0, 0, 0}; //times[0] = tenseconds     times[1] = seconds      times[2] = tenthseconds
void setup() {
  //pinMode(LED_Pin, OUTPUT);
  Serial.begin(9600);

  for(int i = 2; i <=46 ; i++){
      pinMode(i, OUTPUT);
  }

  pinMode(buttonPin, INPUT);
  clearDisplay();
  displayTime();
}

void loop() {
   count();
   //digitalWrite(a[1],HIGH);
   //digitalWrite(b[1],HIGH);
   //count();
   //digitalWrite(a[1], LOW);
   //digitalWrite(b[1],LOW);
   displayTime();
   checkInput();
   if(Counting){
      clearDisplay();
      displayTime();
      updateTime();
      }
      
   //Serial.print(tenSeconds);
   //Serial.print(seconds);
   //Serial.print(tenthSeconds);
   //Serial.println(Counting);
}

void count(){
   delay(100);
   Serial.println(state);
}

void checkInput(){
  //Serial.println(analogRead(buttonPin));
  if(state > 5){
    resetTime();
    clearDisplay();
    displayTime();
    state = 0;
    delay(100);
  }
    switch(state){
      case 5:
         if(analogRead(buttonPin) < 800){
           delay(100);
           state = 0;
           resetTime();
           clearDisplay();
           displayTime();
         }
         
      case 4:
        if(analogRead(buttonPin) > 800){
          delay(100);
          state+=1;
        }
      break;
      
      case 3:
        if(analogRead(buttonPin) < 800){
          delay(100);
          state+=1;
        }
      break;
      
      case 2:
        if(analogRead(buttonPin) > 800){
          Counting = LOW;
          delay(100);
          state+=1;
        }
      break;
      
      case 1:
        if(analogRead(buttonPin)<8000){
          delay(100);
          state+=1;
        }
      break;
      
      case 0:
        if(analogRead(buttonPin) > 800){
          delay(100);
          state+=1;
          Counting = HIGH;
         }
      break;
    }
}
    
void resetTime(){
  times[0] = 0;
  times[1] = 0;
  times[2] = 0;
}

void updateTime(){
   times[2] +=1;
   if(times[2] == 10){
       times[1] +=1;
       times[2] = 0;
   }
   if(times[1] == 10){
       times[0] +=1;
       times[1] = 0;
   }
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
    for(int i = 2; i <= 46 ; i++){
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
