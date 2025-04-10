#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 13
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,16,2);
int Tint;
char key = 'b';
int IN1 = 12;//ให้น้ำ
int IN2 = 11;
int IN3 = 10;//ให้อาหาร
int IN4 = 9;
int IN1_2 = 8;//น้ำลดTEMP
int IN2_2 = 7;
long now1,last1;

void setup() 
{
  Serial.begin(9600);
  sensors.begin();
  lcd.begin();  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(IN1_2,OUTPUT);
  pinMode(IN2_2,OUTPUT);
  delay(1000);
}
void loop() 
{
    if(Serial.available())
        key = Serial.read();  
    else
        key = 'z';
    //******************************   
    if (key == 'a')//ให้น้ำ
    {
        digitalWrite(IN1,LOW);//เปิดน้ำ  
        digitalWrite(IN2,HIGH);     
        delay(3000);
        digitalWrite(IN1,LOW);  
        digitalWrite(IN2,LOW);
        delay(3000);//สมมุติว่าเปิดใว้3นาที
        digitalWrite(IN1,HIGH);//ปิดน้ำ  
        digitalWrite(IN2,LOW);     
        delay(3000);
        digitalWrite(IN1,LOW);  
        digitalWrite(IN2,LOW);
    }    
    if (key == 'b')//ให้อาหาร
    {
        digitalWrite(IN3,LOW);//เปิด  
        digitalWrite(IN4,HIGH);     
        delay(3000);
        digitalWrite(IN3,LOW);  
        digitalWrite(IN4,LOW);
        delay(3000);//สมมุติว่าเปิดใว้3นาที
        digitalWrite(IN3,HIGH);//ปิด  
        digitalWrite(IN4,LOW);     
        delay(3000);
        digitalWrite(IN3,LOW);  
        digitalWrite(IN4,LOW);
    }
    if (key == 'c')//เปิดน้ำลดอุณหภูมิ
    {
        digitalWrite(IN1_2,LOW); 
        digitalWrite(IN2_2,HIGH);     
        delay(3000);
        digitalWrite(IN1_2,LOW);  
        digitalWrite(IN2_2,LOW);
    }
        if (key == 'd')//ปิดน้ำลดอุณหภูมิ
    {
        digitalWrite(IN1_2,HIGH); 
        digitalWrite(IN2_2,LOW);     
        delay(3000);
        digitalWrite(IN1_2,LOW);  
        digitalWrite(IN2_2,LOW);
    } 
    //******************************
    now1 = millis();
    if((now1-last1) > 2500)
    {
    sensors.requestTemperatures(); 
    Tint = sensors.getTempCByIndex(0);
    if ((Tint > 0) && (Tint < 50))
    {
        Serial.print("tp");
        Serial.println(Tint);
        lcd.setCursor(0,0);
        lcd.print("T = ");
        lcd.setCursor(4,0);
        lcd.print(Tint);
    }
    last1=now1;
    } 
}
