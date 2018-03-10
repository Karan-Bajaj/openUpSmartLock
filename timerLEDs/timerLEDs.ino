/*Karan's blink*/

void setup()
{
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
}

double led(double x,int y)
{
  if(y<17)
  {
    digitalWrite(2,HIGH);
    delay(x);
    digitalWrite(2,LOW);
    delay(x);
    
    if(y==16)
    {
      turnGreen();
    }
    return led(x/1.2,y+1);
  }
  else
    return 0;
}

void turnGreen()
{
  digitalWrite(4,HIGH);
  delay(1000);
  digitalWrite(4,LOW);
  delay(1000);
}

void loop()
{
  led(1000,1);
}

