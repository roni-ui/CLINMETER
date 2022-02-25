#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>

//Suhu
#define SENSOR 12 // define pint 2 for sensor

//Pompa
const int A1A = 2;//define pin 2 for A1A
const int A1B = 3;//define pin 3 for A1B

//LCD
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

//buzzer
int buzzer = 11;

//Suhu
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
 float suhuSekarang, suhuJadi;

void setup() 
{
  Serial.begin(9600);

  //suhu
  pinMode(SENSOR, INPUT_PULLUP);

  //Pompa
  pinMode(A1A,OUTPUT);
  pinMode(A1B,OUTPUT);

  //buzzer
  pinMode(buzzer, OUTPUT);
  
  //suhu
  mlx.begin();

  //lcd
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
 
  lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
 
  
}

void loop() 
{
  //Suhu
  suhuJadi = mlx.readObjectTempC(); 
  if (suhuJadi<=30){
    suhuJadi=0;
  }else {
    suhuJadi;
  }
  
  if (suhuJadi>30){
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
//    delay(2000);
  }else if (suhuJadi>=37){
     digitalWrite(buzzer, HIGH);
  } else{
    digitalWrite(buzzer, LOW);
  }

  //Tampilkan di Serial Screen
  Serial.println(suhuJadi);

  
  //LCD
  lcd.setCursor(5,0);
  lcd.print("Suhu:");
  delay(500);
  lcd.setCursor(4,1);
  lcd.print(suhuJadi);
  lcd.setCursor(10,1);
  lcd.print("C");
//  delay(500);

  //suhu dan pompa
  int L =digitalRead(SENSOR);// read the sensor

  if(L == 0){
    Serial.print(L);
    Serial.println(" Obstacle detected");
    digitalWrite(A1A,HIGH);
    digitalWrite(A1B,LOW);
    //delay(1000);
     
  }else{
    Serial.print(L);
    Serial.println("  === All clear==");
    digitalWrite(A1A,LOW);
    digitalWrite(A1B,LOW);
  }

}
