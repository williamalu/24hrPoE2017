// include motor stuff
// include relevant motor variables
#include <stdio.h>
#include <Servo.h>

Servo Drinker1; // creating the servos
Servo Drinker2;
Servo Drinker3;
Servo Drinker4;

byte drink1pos; // these hold the position of the three servos (one for each drink)
byte drink2pos;
byte drink3pos;
byte drink4pos;

#define ORIGIN 0
#define FULL_OFF 130
#define FULL_ON 180

// include LCD screen stuff

// this script should take in whatever button is pressed and use 
// that information to turn on the various motors to pour drinks when the car is present

const int buttonPin1 = 9; // confirm these are true
const int buttonPin2 = 8;

int buttonState1;
int buttonState2;
int buttonState3;
int highlightedDrink = 1;
int selectedDrink = 0;

int counter = 0;

int threshold = 330; // closer == higher number

int pos = 60;
int pos2 = 90;

const byte pinDrink1 = A0;
const byte pinDrink2 = A1;
const byte pinDrink3 = A2;
const byte pinDrink4 = A3;
int sensD1;
int sensD2;
int sensD3;
int sensD4;

long previousMillis = 0;
long lastPress1 = 0;
long lastDebounceTime1 = 0;
long lastPress2 = 0;
long lastDebounceTime2 = 0;

long delayMillis = 200;
long fulloff = 130;
long fullon = 180;

long debounceDelay = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin1, INPUT);  // make three input buttons
  pinMode(buttonPin2, INPUT);

  Drinker1.attach(5); // double check all attachments
  Drinker2.attach(6);
  Drinker3.attach(7);
  Drinker4.attach(4);

  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:



  // Display the three drink options on the screen
  Serial.print("Button State 1 Val = ");
  Serial.print(buttonState1);
  Serial.println();
  sensD1 = analogRead(pinDrink1);
  Serial.print("Sensor 1,");
  Serial.print(sensD1);
  Serial.println();
  Serial.print("Counter = ");
  Serial.print(counter);
  Serial.println();
    sensD2 = analogRead(pinDrink2);

  Serial.print("Sensor 2,");
  Serial.print(sensD2);
  Serial.println();
  
  if (buttonState1 == HIGH){
    //lastPress1 = millis(); // if the button is being pressed get the current time
    //if((lastPress1 - lastDebounceTime1)>debounceDelay){ //check if the last time the reading changed was longer ago than the debounceDelay
      //lastDebounceTime1 = millis();  
      Serial.print("Button1pressed");
      ++ counter;
      // Only display which option you selected on the LCD screen (1 minute and then go back to options?)
      // go to whichever drink function you were on
      if (counter == 1){
        selectedDrink = highlightedDrink; 
        Serial.print(", Selected Drink = ");
        Serial.print(selectedDrink);    
      }
      else if (counter == 2){
         selectedDrink = 0;
         counter = 0;      
      }
    //}
  }
  int reading1 = digitalRead(buttonPin1); //gets now reading from the button
  if (reading1 != buttonState1){
    lastDebounceTime1 = millis(); //if the reading changes get the current time
  }

  
  if (buttonState2 == HIGH){
    Serial.print("Selected Button 2");
    Serial.println();
   // if((lastPress2 - lastDebounceTime2)>debounceDelay){ //check if the last time the reading changed was longer ago than the debounceDelay
     // lastDebounceTime2 = millis();      
    // move down which option is currently highlighted
    ++ highlightedDrink;
   // }
        Serial.print(highlightedDrink);

  }

  int reading2 = digitalRead(buttonPin2); //gets now reading from the button
  if (reading2 != buttonState2){
    lastDebounceTime2 = millis(); //if the reading changes get the current time
  }


  if (selectedDrink == 1){
      Drink1(); 
  }

  if (selectedDrink == 2){
      Drink2();      
  }
  if (selectedDrink == 3){
      Drink3();
  }
  if (selectedDrink == 4){
    selectedDrink = random(1,3);
  }
  if (selectedDrink == 5){
    Drink4();
  }
  if (selectedDrink > 5){
      selectedDrink = 0;
      highlightedDrink = 0;
  }
  buttonState1 = digitalRead(buttonPin1); //gets button state so we can check next time through the loop if it's different
  buttonState2 = digitalRead(buttonPin2); //gets button state so we can check next time through the loop if it's different
  delay(1000);

}

void Drink1(){
  // Drink1 is liquids 1 and 3
  // questions about how timing works on these
  sensD1 = analogRead(pinDrink1);
  sensD3 = analogRead(pinDrink3);
  Serial.print("this is sensor 1");
  Serial.print(sensD1);
  if (sensD1 > threshold){
    Serial.println();
    Serial.println("Sensor 1 is bigger than threshold");
     // turn on motor1 for 1 sec or something
      Drinker1.write(FULL_ON);
      delay(100);
      Drinker1.write(FULL_OFF);
  }
//  if (sensD3 > threshold){
//      Drinker3.write(FULL_ON);
//      delay(delayMillis);
//      Drinker3.write(FULL_OFF);
//      
//  }
}

void Drink2(){
  // Drink2 is liquids 1 and 2
 // sensD1 = analogRead(pinDrink1);
 // sensD2 = analogRead(pinDrink2);
  if (sensD1 > threshold){
           Drinker1.write(fullon);
      delay(delayMillis);
      Drinker1.write(fulloff);
  }
  if (sensD2 > threshold){
            Drinker2.write(FULL_ON);
      delay(delayMillis);
      Drinker2.write(FULL_OFF);
  }

}

void Drink3(){
  // Drink3 is liquids 2 and 3
  sensD2 = analogRead(pinDrink2);
  sensD3 = analogRead(pinDrink3);
  if (sensD2 > threshold){
      Drinker2.write(FULL_ON);
      delay(delayMillis);
      Drinker2.write(FULL_OFF);
  }
//  if (sensD3 > threshold){
//      Drinker3.write(FULL_ON);
//      delay(delayMillis);
//      Drinker3.write(FULL_OFF);
//  }
  
}


void Drink4(){
  // Drink3 is liquids 2 and 3
  sensD1 = analogRead(pinDrink1);
  sensD4 = analogRead(pinDrink4);
  if (sensD1 > threshold){
      Drinker1.write(FULL_ON);
      delay(delayMillis);
      Drinker1.write(FULL_OFF);
  }
//  if (sensD4 > threshold){
//      Drinker4.write(FULL_ON);
//      delay(delayMillis);
//      Drinker4.write(FULL_OFF);
//  }
  
}

