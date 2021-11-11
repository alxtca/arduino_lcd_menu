#include <Arduino.h>
#include "game.h"
#include "variables.h"

//lcd related functions here
void lcdSetup(){
  lcd.begin(16,2);  
  // Print on first row
  lcd.setCursor(0,0);
  lcd.print("Welcome to my");  
  // Wait 1 second
  delay(1000);  
  // Print on second row
  lcd.setCursor(0,1);
  lcd.print("arduino project");  
  // Wait 3 seconds
  delay(3000);  
  // Clear the display
  lcd.clear();
}

void displayScore(){
  lcd.setCursor(0,0);
  lcd.print("Player 1 :");
  lcd.print(player1_score);
  lcd.setCursor(0,1);
  lcd.print("Player 2 :");
  lcd.print(player2_score);  
  delay(3000);
  lcd.clear();
}