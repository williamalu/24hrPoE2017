// include motor stuff
// include relevant motor variables
// include relevant sensing variables
// include motorshield stuff
// include LCD screen stuff

bool buttonState1 = 0;
bool buttonState2 = 0;
bool buttonState3 = 0;
int highlightedDrink = 1;
int selectedDrink = 0;

const byte pinDrink1 = A0;
const byte pinDrink2 = A1;
const byte pinDrink3 = A2;
int sensD1;
int sensD2;
int sensD3;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin1, INPUT); 
  // make three buttons - button1 = select, button2 = move down, button3= i'm feeling lucky

}

void loop() {
  // put your main code here, to run repeatedly:

  // Display the three drink options on the screen
  
  if (buttonState1 == HIGH){
  // if button 1 is pressed
    // Only display which option you selected on the LCD screen (1 minute and then go back to options?)
    // go to whichever drink function you were on
    selectedDrink = highlightedDrink;
  }
  if (buttonState2 == HIGH){
    // move down which option is currently highlighted
    ++ highlightedDrink;
  }
  if (buttonState3 == HIGH){
    selectedDrink = random(1,3);
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
  if (selectedDrink > 3){
      selectedDrink = 0;
      highlightedDrink = 0;
  }
    
}

void Drink1(){
  // Drink1 is liquids 1 and 3
  // questions about how timing works on these
  sensD1 = analogRead(pinDrink1);
  sensD3 = analogRead(pinDrink3);
  if (sensD1 > threshold){
     // turn on motor1 for 1 sec or something

  }
  if (sensD3 > threshold){
  
  //if SENSOR3 detects something
    // turn on motor3 for 1 sec or something 
  }
}

void Drink2(){


}

void Drink3(){
  
}

