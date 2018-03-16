
#include <Servo.h>

Servo myservo; 

int buttonPin=2;
int piezoPin=3;
int servoPin=9;


const int minKnockSound= 70;

void setup() {

  Serial.begin(9600); //FOR BUTTON
  pinMode(2,INPUT);

  myservo.attach(9); // FOR MOTOR
  

  
}

void openUp()
{
  myservo.write(180);
  delay(200);         //To let it move to the position
  
}


void lockIt()
{
  myservo.write(0);
  delay(200);
}


/*

int storePassword(int &pswrdAr, int cnt)
{
  if(pswrdAr[0]!=0)
  {
    timeStart=millis(); 
  }

  int val=analogRead(piezoPin);
  
  while(val<minKnockSound)
  {
    val=analogRead(piezoPin);
  }
  while(val>minKnockSound)
  {
    val=analogRead(piezoPin);
  }

  int timeEnd=millis();
  
  pswrdAr[cnt]=timeEnd-timeStart;

  
}*/


void loop()
{
  bool readState=digitalRead(2);
  int val = analogRead(piezoPin);
  Serial.println(val);

  if (val>minKnockSound)
    delay(500);

  //int *pswrdAr = new int[10];   Extra Feature: Dynamic memmory allocation if size goes beyond specified
  
  int pswrdAr[10]={0};
  int cnt=0;
  int timeStart=0;
  int timeEnd=0;

  if(readState)
  {
    Serial.println("ok");
    delay(1000);
    readState=digitalRead(2);

    

    if(!readState)  //User attempts knocking pattern to open lock
    {
      
    }
    
    else
    {
      Serial.println("ok");
      while(readState)
      {
    
        while(val<minKnockSound)  //Rising edge of sound wave signal
        {
          val=analogRead(piezoPin);
          Serial.println("In1");
        }
    
        while(val>minKnockSound)  //Falling edge of sound wave signal
        {
          val=analogRead(piezoPin);
          Serial.println("In2");
        }
        timeStart=millis();  

        val=analogRead(piezoPin);
        
        while(val<minKnockSound)
        {
          val=analogRead(piezoPin);
          Serial.println("In3");
        }
        
        Serial.println("In4");
        delay(2000);
        int timeEnd=millis();
        pswrdAr[cnt]=timeEnd-timeStart; 
    
        cnt++;
       
      }
      
    }
    
  }

  for(int i=0; i<10;i++)
  {
    Serial.println(pswrdAr[i]);
  }
  /*
  if (readState||val>80)
  {
    Serial.println("Reading");
    openUp();
    delay(2000);
    lockIt();

  }
  
  else 
    Serial.println("Ignoring");
  
  
  delay(1);
  */
}





/*
//FOR Button
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}


void loop() {
  bool readState = digitalRead(2);
  if (readState)
    Serial.println("Reading");
  else 
    Serial.println("Ignoring");

  delay(1);
}
*/



/*
//#FOR Piezo
int analogPin = 3  ;     // potentiometer wiper (middle terminal) connected to analog pin 
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read

void setup()
{
  Serial.begin(9600);              //  setup serial
}

void loop()
{
  val = analogRead(analogPin);     // read the input pin
  Serial.println(val);             // debug value
  delay(100);
}
*/


/*
//FOR MOTOR
#include <Servo.h>

Servo myservo; 

int pos=0;

void setup() {
  
  myservo.attach(9);
  
}

void loop() {
  myservo.write(pos);
  delay(700);
  pos+=10;
  myservo.write(180-pos);  
  delay(700);
  pos+=10;
  if(pos>=90)
    pos=0;
}
*/
