#define BLYNK_TEMPLATE_ID "TMPL3Ppiq5Scz"
#define BLYNK_TEMPLATE_NAME "WIFI REMOTE"
#define BLYNK_AUTH_TOKEN "qh26r9IUxsOGrgipyWty7Y3AvHsluhWJ"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//motor pins
#define EN_A D0
#define A1 D1
#define A2 D2
#define B1 D3
#define B2 D4
#define EN_B D5
#define LED D6
#define CONNECTIONLED D7
#define CONVEYOR D8

// Variables for the Blynk widget values
int x = 50;
int y = 50;
int Speed;
int CON;

char auth[] = "qh26r9IUxsOGrgipyWty7Y3AvHsluhWJ";
char ssid[] = "Couldn't connect";
char pass[] = "RAKESHDINESH";


void setup() 
{
  Serial.begin(9600);
  pinMode(EN_A, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(CONNECTIONLED, OUTPUT);
  pinMode(CONVEYOR, OUTPUT);


  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

//joystick values
BLYNK_WRITE(V0) 
{
  x = param[0].asInt();
}

BLYNK_WRITE(V1)
{
  y = param[0].asInt();
}

//slider values
BLYNK_WRITE(V2) 
{
  Speed = param.asInt();
}
BLYNK_WRITE(V3)
{
  CON = param.asInt();
}


void smartboat()
{
  if ( (WiFi.status() == WL_CONNECTED) )
  {
    digitalWrite(CONNECTIONLED, HIGH);
  }
  if ( (WiFi.status() != WL_CONNECTED) )
  {
    digitalWrite(CONNECTIONLED, LOW);
  }
  
  if (y > 70) 
  {
    boatForward();
    Serial.println("boatForward");
    digitalWrite(LED, LOW);
  } 
  else if (y < 30) 
  {
    boatBackward();
    Serial.println("boatBackward");
    digitalWrite(LED, HIGH);
  }
  else if (x < 30) 
  {
    boatLeft();
    Serial.println("boatLeft");
    digitalWrite(LED, LOW);
  } 
  else if (x > 70)
  {
    boatRight();
    Serial.println("boatRight");
    digitalWrite(LED, LOW);
  } 
  else if (x < 70 && x > 30 && y < 70 && y > 30) {
    boatStop();
    Serial.println("boatstop");
    digitalWrite(LED, LOW);
  }
}
void loop() 
{
  Blynk.run();
  if (CON==1)
  {
    digitalWrite(CONVEYOR,HIGH);
  }
  else if (CON==0)
  {
    digitalWrite(CONVEYOR,LOW);
  }
  smartboat();
}

/*Motor movement functions*/
void boatForward()
{
  analogWrite(EN_A, Speed);
  analogWrite(EN_B, Speed);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(B1, HIGH);
  digitalWrite(B2, LOW);
}
void boatBackward() 
{
  analogWrite(EN_A, Speed);
  analogWrite(EN_B, Speed);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, HIGH);
  
}
void boatLeft() 
{
  analogWrite(EN_A, Speed);
  analogWrite(EN_B, Speed);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(B1, HIGH);
  digitalWrite(B2, LOW);
}
void boatRight()
{
  analogWrite(EN_A, Speed);
  analogWrite(EN_B, Speed);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(B1, LOW);
  digitalWrite(B2, HIGH);
}
void boatStop() 
{
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
}
