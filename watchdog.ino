#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
SoftwareSerial mySerial(9,10);//Rx TX

int sensor=7;
int speaker=8;
int gas_value,Gas_alert_val, Gas_shut_val;
int Gas_Leak_Status;
int bl_data=0;
int bt_confirm=1;
int scandelay=500;
int led=13;
void setup()
{


pinMode(sensor,INPUT);
pinMode(speaker,OUTPUT);
pinMode(led,OUTPUT);


lcd.begin(16,2);
lcd.clear();
mySerial.begin(9600);   
mySerial.println("Bluetooth Connected..");//


digitalWrite(speaker,HIGH);
delay(250); 
digitalWrite(speaker,LOW); 
delay(100);            //microcontroller reset buzz
digitalWrite(speaker,HIGH);
delay(250); 
digitalWrite(speaker,LOW); 
}

void loop()
{
	
CheckGas();

}

void CheckGas()
{

lcd.clear();
scannning_lcd_ani();
Gas_alert_val=ScanGasLevel();
if(Gas_alert_val==LOW)
{
 SetAlert(); 
}
}

int ScanGasLevel()
{
gas_value=digitalRead(sensor); // reads the sensor output

return gas_value; 
}

void SetAlert()

{
  
  set_alert_display_and_beep();
  
  if(CheckShutDown()!=0){
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("BLUETOOTH");
    lcd.setCursor(4,1);
    lcd.print("ALERTING");
    led_alert();
	delay(1000);

    if(bl_data==0){
    serial_bluetooth();
    }
	else{
	lcd.clear();
	lcd.print("BLUETOOTH");
    lcd.setCursor(0,1);
    lcd.print("ALERTED");
    led_alert();
	delay(1000);
	}
    
    
    CheckShutDown();
  }
  
  
}

int CheckShutDown()
{
Gas_shut_val=ScanGasLevel();
if(Gas_shut_val==HIGH)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("NO GAS LEAKING");
lcd.setCursor(6,1);
lcd.print("Now");
delay(5000);
return 0;
}
else 
  return 1;
}

void scannning_lcd_ani(){
  
    lcd.setCursor(0,0);
    lcd.print("    SCANNING");
    delay(scandelay);
    lcd.setCursor(7,1);
    lcd.print("()");
    delay(scandelay);
    lcd.setCursor(6,1);
    lcd.print("(())");
    delay(scandelay);
    lcd.setCursor(5,1);
    lcd.print("((()))");
    delay(scandelay);
    lcd.setCursor(4,1);
    lcd.print("(((())))");
    delay(scandelay);
    
}
void set_alert_display_and_beep(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("!!GAS LEAKED!!");
  int count=20;
  while(count>0){
    led_alert();
    digitalWrite(speaker,HIGH);
    delay(150);
    digitalWrite(speaker,LOW);
    count--;
    delay(1000);
  }
  
 
  
}

void serial_bluetooth(){

    led_alert();
    mySerial.println("!!GAS LEAKED ON KITCHEN!!");
    if(mySerial.available()){
		bl_data = mySerial.read();
	}
    delay(100);
    
    
   }
  
    
void led_alert(){

  digitalWrite(13,HIGH);  
  delay(25);             
  digitalWrite(13,LOW); 
  digitalWrite(13,HIGH);  
  delay(25);             
  digitalWrite(13, LOW);   
  
}
  
  
