
#include <Servo.h>

Servo myservo; 

int buttonPin=2;
int piezoPin=3;
int servoPin=9;


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

void loop()
{
  bool readState=digitalRead(2);
  int val = analogRead(piezoPin);
  Serial.println(val);
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
#FOR Piezo
int analogPin = 0  ;     // potentiometer wiper (middle terminal) connected to analog pin 
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
