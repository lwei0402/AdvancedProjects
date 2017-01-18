#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <Wire.h>

RF24 radio(9,10);

struct data{
 char click_status;
 char battery_status; 
 int16_t ax,ay,az;
 bool drag_status;
}mouse;
 char previous_status;
 int elapsedTime;
 int lasttime;
void radioInit()
{
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setPayloadSize(32);
  radio.setChannel(21);
  radio.setCRCLength(RF24_CRC_16);
  radio.setAddressWidth(5);
  radio.setRetries(10,15);
  
  radio.openWritingPipe(0xBEBEBEBE44);
  radio.openReadingPipe(1,0xBEBEBEBE77);
 // radio.startListening();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  while(!Serial);
  //printf_begin();
  radioInit();
  //radio.printDetails();
  pinMode(18,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(19,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    radio.startListening();
    while(!radio.available());
      
    if(radio.available())
    {
      radio.read(&mouse, sizeof(mouse));
//      Serial.print("Ax: ");
//      Serial.println(mouse.ax*0.002);
//      Serial.print("Ay: ");
//      Serial.println(mouse.ay*0.002);
//      Serial.print("Az: ");
//      Serial.println(mouse.az*0.002);
//      Serial.print("\n");
      
//      if(abs(-mouse.ax*0.002-1)>2 && abs(mouse.ay*0.002-7)>2)
//      {
//      Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
//      }

        Serial.println(mouse.drag_status);
//      elapsedTime = millis()- lasttime;
//      Serial.println(elapsedTime);
//      //Serial.println(mouse.click_status);
//      if (mouse.click_status == 'L' && previous_status == 'L' && elapsedTime < 250)
//      {
//        Mouse.set_buttons(1,0,0);  
//        Serial.println("LOOP1");
//        delay(500);
//        if(abs(-mouse.ax*0.002-1)>2 && abs(mouse.ay*0.002-7)>2)
//        {
//         Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
//        }
//        Mouse.set_buttons(0,0,0);
//        lasttime = millis();    
//        previous_status = mouse.click_status;  
//      }
//      else if (mouse.click_status == 'R' && previous_status == 'R' && elapsedTime < 250)
//      {
//        Mouse.set_buttons(0,0,1);
//        Serial.println("LOOP1");
//        delay(500);
//        if(abs(-mouse.ax*0.002-1)>2 && abs(mouse.ay*0.002-7)>2)
//        {
//         Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
//        }
//        Mouse.set_buttons(0,0,0);
//        lasttime = millis();
//        previous_status = mouse.click_status;
//      }
//      else if(mouse.click_status == 'L')
//      {
//        Mouse.set_buttons(0,0,1);
//        Mouse.set_buttons(0,0,0);
//        if(abs(-mouse.ax*0.002-1)>2 && abs(mouse.ay*0.002-7)>2)
//        {
//         Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
//        }
//        lasttime = millis();
//        previous_status = mouse.click_status;  
//
//      }
//      else if(mouse.click_status == 'R')
//      {
//        Mouse.set_buttons(1,0,0);
//        Mouse.set_buttons(0,0,0);
//        if(abs(-mouse.ax*0.002-1)>2 && abs(mouse.ay*0.002-7)>2)
//        {
//         Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
//        }
//        lasttime = millis();
//        previous_status = mouse.click_status;  
//      }
//      else
//      {
//        if(abs(-mouse.ax*0.002-1)>2 && abs(mouse.ay*0.002-7)>2)
//        {
//         Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
//        }
//      }
//      

   if(mouse.click_status == 'L')
      {
        Mouse.set_buttons(1,0,0);
        if(mouse.drag_status == 1)
        {
          if(abs(-mouse.ax*0.002-1)>1 && abs(mouse.ay*0.002-7)>1)
            {
               Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
               delay(200);
            }
         }
        Mouse.set_buttons(0,0,0);
      }
      else if(mouse.click_status == 'R')
      {
        Mouse.set_buttons(1,0,0);
        if(abs(-mouse.ax*0.002-1)>1 && abs(mouse.ay*0.002-7)>1)
            {
               Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
               delay(200);
            }
        Mouse.set_buttons(0,0,0);
      }
      else 
      {
        if(abs(-mouse.ax*0.002-1)>1 && abs(mouse.ay*0.002-7)>1)
        {
         Mouse.move(-mouse.ax*0.002-1,mouse.ay*0.002-7);
        }
      }
      
        //Serial.print(mouse.battery_status);
      if (mouse.battery_status == 'R')
      {
        digitalWrite(18,HIGH);
        digitalWrite(19,LOW);        
        digitalWrite(17,LOW);
      }
      else if (mouse.battery_status == 'G')
      {
        digitalWrite(19,HIGH);
        digitalWrite(18,LOW);
        digitalWrite(17,LOW);
      }
      else if (mouse.battery_status == 'Y')
      {
        digitalWrite(17,HIGH);
        digitalWrite(18,LOW);
        digitalWrite(19,LOW);
      }
    }
}

  

 

