#include <LiquidCrystal.h>  // Лобавляем необходимую библиотеку
#include <IRremote.h>

#include <Wire.h>
#include <LiquidCrystal.h>   // Лобавляем необходимую библиотеку
// Битовая маска символа улыбки

//#include <SimpleTimer.h>
// defines pins numbers
// defines pins numbers
const int trigPin = 12;
const int echoPin = 13;

int d = 0;

long duration;
int distance;
boolean m = true;
int index = 0;
String target = "";
byte smile[8] =
{
  B00010,
  B00001,
  B11001,
  B00001,
  B11001,
  B00001,
  B00010,
};    
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)
int angle = 0;
int sec = 0;
int radio = 87;
int volume = 0;
int RECV_PIN = 8;
int disa;
int direct = 1;

boolean t = true;
IRrecv irrecv(RECV_PIN);
decode_results results;
#include <Servo.h> //используем библиотеку для работы с сервоприводом

Servo servo; //объявляем переменную servo типа Servo
void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  servo.attach(11);
  servo.write(0);
  lcd.begin(16, 2);                  // Задаем размерность экрана
  lcd.setCursor(0, 0);              // Устанавливаем курсор в начало 1 строки
  lcd.print("Madi Yussupov");       // Выводим текст
  lcd.setCursor(0, 1);              // Устанавливаем курсор в начало 2 строки
  lcd.print("3En04e");
//  lcd.setCursor(7, 1);  /
//  lcd.createChar(smile);
  
  servo.attach(11); //привязываем привод к порту 10
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {


  if(sec%1000==0){
  if(!t){
     if(m){
        servo.write(angle);
        if(angle <= 0){
        direct = 1;
      }
      if(angle >= 180 ){
        direct = -1;
      }
      angle = angle + direct;
       disa = measure();
       if(disa < 35){
        m = false;
        lcd.setCursor(0,1);
        String res = "";
        res = "P:" + String(angle)+"* D:" +String(disa)+"cm";
//        res = res + ;
//        Serial.println(res);
        lcd.print(res);
      }
    }
  }
  }
  else if (irrecv.decode(&results)) { 
              method();
              irrecv.resume(); // Receive the next value
              delay(200);

    
  }

  sec = sec +1 ;

 
}

int measure(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    return distance;
  }

void changeMod(boolean t){
  
  Serial.println("changeMOd     "+t); 
    if(t){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("M:");
    }else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("T:35");
      }
  }

void madik(int sool){
  servo.write(0);
  int st = 1;
  for(int i=angle;i <= sool;i=i+st){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("P:"+String(sool));
    lcd.setCursor(0,1);
    lcd.print("P:"+String(i));
    servo.write(i);
    delay(50);
  }
  int res = measure();
  lcd.setCursor(7,1);
  lcd.print("D:"+String(res)+"cm");
  }

void method(){
//  Serial.println(results.value);
  switch(results.value)

  {

  case 0xFFA25D:  
  //CH - 
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("M:");
//    Serial.println(radio);
    break;

  case 0xFF629D:  
  
    Serial.println(" CH             "); 
    break;

  case 0xFFE21D:  
  //CH +
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("T:");
//    Serial.println(radio);
    break;

  case 0xFF22DD:  
      t = false;
      m = true;
      changeMod(t);
//    lcd.setCursor(0, 0);
    Serial.println("prev     "); 
    lcd.setCursor(0,1);
    lcd.print("PLAY");
    break;

  case 0xFF02FD:  
      t = true;
      d = 0;
      changeMod(t);
//    lcd.setCursor(0, 0);
      Serial.println("next     "); 
      index = 0;
      target = "";
    break;

  case 0xFFC23D:  
    Serial.println(" PLAY/PAUSE     "); 
    if(!t){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("T:35");
      if(m){
        m = false;
        lcd.setCursor(0,1);
        lcd.print("PAUSE");
      }else{
        m = true;  
        lcd.setCursor(0,1);
        lcd.print("PLAY");
      }
    }else{
      madik(d);
      }
    break;

  case 0xFFE01F:
    if(volume > 0 ){
        volume = volume -1;
      }
    Serial.println(volume);
    break;

  case 0xFFA857:  
    volume = volume + 1;
    Serial.println(volume);
    break;

  case 0xFF906F:  
    Serial.println(" EQ             "); 
    break;

  case 0xFF6897:  
    tar("0");
    break;

  case 0xFF9867:  
    Serial.println(" 100+           "); 
    break;

  case 0xFFB04F:  
    Serial.println(" 200+           "); 
    break;
  case 0xFF30CF:  
    tar("1");
    break;

  case 0xFF18E7:  
    tar("2");
    break;

  case 0xFF7A85:  
    tar("3");
    break;

  case 0xFF10EF:  
    tar("4");
    break;

  case 0xFF38C7:  
    tar("5");
    break;

  case 0xFF5AA5:  
    tar("6");
    break;

  case 0xFF42BD:  
    tar("7");
    break;

  case 0xFF4AB5:  
    tar("8");
    break;

  case 0xFF52AD:  
    tar("9");
    break;


  }

 
}
 void tar(String ad){
  index = index + 1;
    if(index > 2){
      index = 0;
      target = "";
      } 
    target = target + ad;
    d = target.toInt();
    if(d > 180){
      d = 180;
      }
    lcd.clear();
    lcd.print("M:"+String(d));
    }

