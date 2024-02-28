#include <LiquidCrystal_I2C.h>

int LED_VERDE = 11;  
int LED_ROSU = 12;  
int BUZZER = 3;  
int GAS_VAL = 0; 
int VENTILATOR_PIN = 7;
int POTENTIOMETRU_VAL = 0; 

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()  
{  
   pinMode(A0, INPUT); 
   pinMode(A3, INPUT); 
   pinMode(VENTILATOR_PIN, OUTPUT); 
   digitalWrite(VENTILATOR_PIN, LOW);
   digitalWrite(BUZZER, LOW);
   Serial.begin(9600);
   lcd.init();
   lcd.backlight();   
   pinMode(LED_VERDE, OUTPUT); 
   pinMode(LED_ROSU, OUTPUT); 
   pinMode(BUZZER, OUTPUT);   
}  

void loop()  
{  
  GAS_VAL = analogRead(A0);
  POTENTIOMETRU_VAL = analogRead(A3);

  if (POTENTIOMETRU_VAL < 341)  
  {                  
    POTENTIOMETRU_VAL = (POTENTIOMETRU_VAL * 3) / 4;
  }
  else if (POTENTIOMETRU_VAL < 682) 
  {
    POTENTIOMETRU_VAL = ( (POTENTIOMETRU_VAL-341) * 3) / 4;
  }
  else
  {
    POTENTIOMETRU_VAL = ( (POTENTIOMETRU_VAL-683) * 3) / 4; 
  }
  
  Serial.print("valoare gaz ");
  Serial.println(GAS_VAL);
  Serial.print("valoare potentiometru ");
  Serial.println(POTENTIOMETRU_VAL);
  
  lcd.clear(); 
  lcd.setCursor(0,0);
  digitalWrite(VENTILATOR_PIN, LOW);
  
  if (GAS_VAL > POTENTIOMETRU_VAL)
  {      
     Serial.println("Scurgere de gaz detectata!");  
     Serial.println("Nu sunteti in siguranta!"); 
     lcd.print("GAS LEAKAGE!");
     lcd.setCursor(0,1);
     lcd.print("You are NOT safe!");
     digitalWrite(LED_ROSU, HIGH);
     delay(5);
     digitalWrite(LED_ROSU, LOW);
     digitalWrite(LED_VERDE, LOW);   
     digitalWrite(BUZZER, HIGH);
     digitalWrite(VENTILATOR_PIN, HIGH);
  }  
  else
  {    
     Serial.println("Nu exista scurgeri de gaz..."); 
     Serial.println("Esti in siguranta"); 
     lcd.print("No leakage!"); 
     lcd.setCursor(0,1);
     lcd.print("You are safe!");
     digitalWrite(LED_ROSU, LOW); 
     digitalWrite(LED_VERDE, HIGH);  
     digitalWrite(BUZZER, LOW);
 } 
 delay(100);
}
