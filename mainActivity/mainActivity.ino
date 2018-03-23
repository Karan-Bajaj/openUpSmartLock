
#include <Servo.h>

Servo myservo; 

int buttonPin=2;
int piezoPin=3;
int servoPin=9;


const int minKnockSound= 90;
const int adjFact = 1000; //In percent for accuracy of knock


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
  myservo.write(20);
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

int cnt=0;
int cnt2=0;
int numKnocks=2;

int timeStart=0;
int timeEnd=0;
int timeStart2=0;
int timeEnd2=0;

bool pswrdStored=false;
int pswrdAr[5]={0};
bool pwCor=false;


 
void loop()
{
  bool readState=digitalRead(2);
  int val = analogRead(piezoPin);
  Serial.println(val);

  if (val>minKnockSound)
    delay(500);

  //int *pswrdAr = new int[10];   Extra Feature: Dynamic memmory allocation if size goes beyond specified
  
 

  
  if(readState)
  {
    
    Serial.println("ok");
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
      
      while(cnt<numKnocks)
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

      for(int i=0; i<2; i++)
      {
        Serial.println("Stored value is: ");
        Serial.println(pswrdAr[i]);
        Serial.println(".");
      }
      
      delay(2000);
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
          Serial.println(pswrdAr[cnt2]);
          Serial.println(".");
          delay(2000);
          pwCor=false;
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
  /*
  if(pswrdStored)
  {
    for(int i=0; i<=cnt;i++)
    {
      Serial.println(pswrdAr[i]);
    }
    delay(20000);
  }
  */
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
