#include <Servo.h>

Servo myservo; 
int pos=0;


void setup() {
  
  myservo.attach(9);
  
}

void loop() {
  
  myservo.write(pos);
  
  if(pos==150)
    pos=-30;
  
  delay(1000);
  pos= pos+30;
  
  
}
