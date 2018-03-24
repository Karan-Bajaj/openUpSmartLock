#include <Servo.h>

Servo myservo; 

int buttonPin=2;
int piezoPin=3;
int servoPin=9;
int redPin=10;
int greenPin=11;


void setup() 
{
  Serial.begin(9600); //FOR BUTTON
  pinMode(2,INPUT);

  myservo.attach(9); // FOR MOTOR  
}


void openUp()
{
  myservo.write(180);
  delay(500);         //To let it move to the position
}


void lockIt()
{
  myservo.write(0);
  delay(500);
}


void blinkGrFast(int times)
{
  for(int i=0;i<times;i++)
  {
    analogWrite(greenPin,255);
    delay(200);
    analogWrite(greenPin,0);
    delay(200);
  }
}


void blinkRdFast(int times)
{
  for(int i=0;i<times;i++)
  {
    analogWrite(redPin,255);
    delay(200);
    analogWrite(redPin,0);
    delay(200);
  }
}


void fadeGr(int times)
{
  for(int i=0;i<times;i++)
  {
    for(int j=0; j<=255; j++)
    {
      analogWrite(greenPin,j);
      delay(1);
    }

    for(int j=255; j>=0; j--)
    {
      analogWrite(greenPin,j);
      delay(1);
    }
  }
}


void fadeRd()
{
  for(int i=0;i<times;i++)
  {
    for(int j=0; j<=255; j++)
    {
      analogWrite(redPin,j);
      delay(1);
    }

    for(int j=255; j>=0; j--)
    {
      analogWrite(redPin,j);
      delay(1);
    }
  }  
}


/*
int storePassword(int &pswrdAr, int cnt) <--- Consider placing here for neatness
*/

const int minKnockSound= 90;
const int adjFact = 400; //In millisec for accuracy of knock

int cnt=0;
int cnt2=0;
const int numKnocks=4;

int timeStart=0;
int timeEnd=0;
int timeStart2=0;
int timeEnd2=0;

bool pswrdStored=false;
int pswrdAr[numKnocks]={0};
bool pwCor=false;

 
void loop()
{
  bool readState=digitalRead(2);
  int val = analogRead(piezoPin);
  Serial.println(val);

  if (val>minKnockSound)  //To get an idea of value of different levels of knocks
    delay(500);

  //int *pswrdAr = new int[10];   Extra Feature: Dynamic memmory allocation if size goes beyond specified
  
 
  if(readState)
  {
    
    Serial.println("Listening");
    delay(1000);
    readState=digitalRead(2);

    
    if(readState && !pswrdStored)
    {
      Serial.println("Programming password");
      delay(500);

      while(val<minKnockSound)  //Rising edge of sound wave signal
      {
        val=analogRead(piezoPin);
        Serial.println("In1");
      }
      
      while(cnt<numKnocks)     //Reading critical information
      {
        while(val>=minKnockSound)  //Falling edge of sound wave signal
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
        
        int timeEnd=millis();
        Serial.println("In4");
        
        pswrdAr[cnt]=timeEnd-timeStart;
        cnt++;
       
      }

      for(int i=0; i<numKnocks; i++)
      {
        Serial.println("Stored value is: ");
        Serial.println(pswrdAr[i]);
        Serial.println(".");
      }
      
      delay(5000);
      pswrdStored=true;
            
    }

    
    
    else if(pswrdStored)  //User attempts knocking pattern to open lock
    {
      
      cnt2=0;
 
      while(val<minKnockSound)  //Rising edge of sound wave signal
      {
        val=analogRead(piezoPin);
        Serial.println("In1.1");
      }

      while(cnt2<numKnocks)
      {
        
        while(val>=minKnockSound)  //Falling edge of sound wave signal
        {
          val=analogRead(piezoPin);
          Serial.println("In2.1");
        }
  
        int timeStart2=millis();  
  
        val=analogRead(piezoPin);
          
        while(val<minKnockSound)
        {
          val=analogRead(piezoPin);
          Serial.println("In3.1");  
        }
          
        timeEnd2=millis();
        Serial.println("In4.1");
          
        int foo=timeEnd2-timeStart2; 
        if( (pswrdAr[cnt2]-adjFact)>=foo || foo>=(pswrdAr[cnt2]+adjFact))
        {
          Serial.println("False.Your entry: ");
          Serial.println(foo);
          Serial.println("Expected: ");
          Serial.println(pswrdAr[cnt2]);
          Serial.println(".");
          delay(2000);
          pwCor=false;
          return 0;
        }
  
        else
        {
          Serial.println("Correct...");
          Serial.println(foo);
          Serial.println(pswrdAr[cnt2]);
          Serial.println(".");
          pwCor=true;
        }

        cnt2++;
      
      }
      
      if(pwCor)
      {
          Serial.println("Correct password. Welcome! ");
          openUp();
          delay(2000);
          lockIt();
          delay(2000);
      }
      
      else
        Serial.println("False password.");
    }     
  }
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
  delay(1);
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
