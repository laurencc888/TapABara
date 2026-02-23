// CAPYBARA FUN!!

#include <LiquidCrystal.h>
#include <Servo.h>

int pos = 0;
int baraToTurn = 0;
int score = 0;
int roundsLeft = 10; // games last 10 rounds
unsigned long forwardTime; // tracks time when capybara first turns forward
unsigned long backwardTime; // tracks time when capybara turns back around
unsigned long buttonTime; // tracks time button is pressed
boolean isPressed = false;

// CAPYBARA MOTORS
Servo bara1;
Servo bara2;
Servo bara3;

// BUTTON PINS
int button1 = 7;
int button2 = 13;
int button3 = 8;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  
  bara1.attach(9);
  bara2.attach(10);
  bara3.attach(6);
  
  bara1.write(0);
  bara2.write(0);
  bara3.write(0);
  
  lcd.begin(16, 2); // Set up the number of columns and rows on the LCD.
}

void loop(){
  
  // Will only display at the start of the game
  if (roundsLeft != -1) {
    // Print starting message to the LCD.
    for (int i = 0; i < 10; i += 1) {
      lcd.clear();
      delay(100);
      lcd.print("GAME TIME!");
      delay(400);
    }
    delay(1000);
    
    // Limits player to 10 rounds
    while (roundsLeft >= 0) {
      isPressed = false;
      displayRounds();
      delay(1000);

      // randomly turn a capybara
      int randomBara = random(1, 4);

      // prevents the same capybara from turning multiple times in a row
      while (randomBara == baraToTurn) {
        randomBara = random(1, 4);
      }
      baraToTurn = randomBara;

      // records time that capybara first turns around
      forwardTime = millis();
      
      if (baraToTurn == 1) {
        for (pos = 0; pos <= 180; pos += 1) {
          bara1.write(pos);
          delay(3);
        }
      }

      else if (baraToTurn == 2) {
        for (pos = 0; pos <= 180; pos += 1) {
          bara2.write(pos);
          delay(3);
        }
      }
      
      else { // if baraToTurn is 3
        for (pos = 0; pos <= 180; pos += 1) {
          bara3.write(pos);
          delay(3);
        }
      }
      
      
      // allows time for user to press correct button
      for (int i = 0; i < 2500; i += 1) {
        // checks if user presses appropriate button
        if (baraToTurn == 1 && digitalRead(button1) == HIGH && !isPressed) {
          buttonTime = millis();
          isPressed = true;
        }
        
        else if (baraToTurn == 2 && digitalRead(button2) == HIGH && !isPressed) {
          buttonTime = millis();
          isPressed = true;
        }
        
        else if (baraToTurn == 3 && digitalRead(button3) == HIGH && !isPressed) {
          buttonTime = millis();
          isPressed = true;
        }
        delay(1);
      }

      delay(15);

      // records time capybara begins to turn back around
      backwardTime = millis();
      
      if (baraToTurn == 1) {
        for (pos = 180; pos >= 0; pos -= 1) {
          bara1.write(pos);
          delay(2);
        }
      }
      else if (baraToTurn == 2) {
        for (pos = 180; pos >= 0; pos -= 1) {
          bara2.write(pos);
          delay(2);
        }
      }
      else {
        for (pos = 180; pos >= 0; pos -= 1) {
          bara3.write(pos);
          delay(2);
        }
      }
      
      // checks if button was pressed during time capybara was turned around
      if (buttonTime > forwardTime && buttonTime < backwardTime) {
        score++;
      }
      roundsLeft--;
      delay(1000);
    }
  }
  displayScore(score);
  delay(2000);
} 

void displayScore(int score) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAME OVER!");
  
  lcd.setCursor(0,-1);
  lcd.print("Your score is: ");
  lcd.print(score);
}

void displayRounds() {
  lcd.clear();
  lcd.setCursor(0,0);
  
  if (roundsLeft == 0) {
    lcd.print("FINAL ROUND!");
  }
  else {
    lcd.print("ROUNDS LEFT: ");
  	lcd.print(roundsLeft);
  }

  lcd.setCursor(0,-1);
  lcd.print("SCORE: ");
  lcd.print(score);
}
