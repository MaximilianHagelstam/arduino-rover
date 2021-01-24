#include <dht.h>

dht DHT;
#define DHT11_PIN 9

int trig = 11;
int echo = 12;

int duration = 0;
int distance = 0;

const int buzzer = 6;

int tiltSensor = 10;

int tiltValue;

const int leftForward = 2;
const int leftBackward = 3;
const int rightForward = 4;
const int rightBackward = 5;

int redLED = 7;
int blueLED = 8;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);

  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
    
  Serial.flush();

  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);
  distance= (duration/2)/28.5;

  if (distance < 20)
  {
    digitalWrite(leftForward , LOW);
    digitalWrite(leftBackward , HIGH);
    digitalWrite(rightForward , HIGH);
    digitalWrite(rightBackward , LOW);
    delay(100);
  } else {
    digitalWrite(leftForward , HIGH);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightForward , HIGH);
    digitalWrite(rightBackward , LOW);
  }

  if (digitalRead(tiltSensor) == 1)
  {
    bool a = true;
    
    while (a == true)
    {
      digitalWrite(leftForward , LOW);
      digitalWrite(leftBackward , LOW);
      digitalWrite(rightForward , LOW);
      digitalWrite(rightBackward , LOW);
      
      delay(500);
      digitalWrite(redLED, LOW);
      
      tone(buzzer, 1000);
      digitalWrite(blueLED, HIGH);
      
      delay(500);
      digitalWrite(blueLED, LOW);
      
      tone(buzzer, 500);
      digitalWrite(redLED, HIGH);

      if (digitalRead(tiltSensor) == 0)
      {
        break;
      }
    }
  } else {
    noTone(buzzer);

    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
  }

  Serial.flush();
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  Serial.print("Temperature: ");
  Serial.print(DHT.temperature);
  Serial.println("°C");
  
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.println("%");

  Serial.println("");

  delay(1000);
}
