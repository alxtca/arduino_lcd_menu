#include <Arduino.h>
#include "variables.h"
#include "game.h"
#include "lcd.h"
#include "music.h"
#include "button.h"

int menu_selection{0}; //current item number in the displayed menu list. Updates when scrolling menu.
bool selection_updated = true; //true - to reprint menu on lcd once.
//state of current menu to display
int menu_state = {0}; //to print different menus 0 - main_menu, 1 - game_menu, 2 - music menu
//states to know when to stop displaying new menus and perform some action
bool play_music = false;
bool play_game = false;

void menuUp();
void menuDown();
void makeSelected();
void displayMenu();
void printMenu(const char menu_to_print[][16]);
void runOnClick(Btn & btn, int & led_state, void(*f)()); //why it does not come with button.h?
 
void setup()
{ 
  pinMode(btn1.pin, INPUT);
  pinMode(btn2.pin, INPUT);
  pinMode(btn3.pin, INPUT);
  pinMode(led_pin, OUTPUT);
  lcdSetup();

  //attachInterrupt(digitalPinToInterrupt(button1_pin), changeScore1, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(button2_pin), changeScore2, CHANGE);
  //how to use same buttons but to run different interrupts depending on menu level?
  //states?
}

void loop()
{
  runOnClick(btn2, led_state, menuDown);
  runOnClick(btn3, led_state, menuUp);
  runOnClick(btn1, led_state, makeSelected);
// display appropriate menu based on current state
  if (selection_updated)
  {
    selection_updated = false;
    displayMenu();
  };
}
//-----------------------------------------------------------------

void menuUp(){
  if (menu_selection > 0){
    menu_selection--; //make it impossible to be negative
    selection_updated = true; 
  }
}
void menuDown(){
  //determine current menu list size(based on menu_state).
  int menu_size;
  if (menu_state == 0) menu_size = sizeof(main_menu)/sizeof(*main_menu);
  if (menu_state == 1) menu_size = sizeof(game_menu)/sizeof(*game_menu);
  if (menu_state == 2) menu_size = sizeof(music_menu)/sizeof(*music_menu);
  //if end of menu items is reached, don't scroll anymore
  if (menu_selection < (menu_size-1)){
    menu_selection++;
    selection_updated = true;
  }
}

void makeSelected(){
  //"BACK TO MAIN" (for music menu and game menu)
  if ((menu_state == 2 && menu_selection == (sizeof(music_menu)/sizeof(*music_menu)-1)) || 
    (menu_state == 1 && menu_selection == (sizeof(game_menu)/sizeof(*game_menu)-1))){
    //to go automatically back to main menu need to reset these state variables
    menu_selection = 0;//to go on top of menu
    menu_state = 0; //to go to main menu
    selection_updated = true; //to enable menu print
    play_game = false; //
    play_music = false;
  }
  //PLAY TRACK
  else if (play_music == true){
    playM(menu_selection); //this should indicate visually that playing music is in progress
    //when melody is finished menu with music track are visible
  }

  else if (play_game){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No game yet made");
    lcd.setCursor(0,1);
    lcd.print("redirecting...");
    delay(5000);
    //to go automatically back to main menu need to reset these state variables
    menu_selection = 0;
    selection_updated = true;
    menu_state = 0;
    play_game = false;
  }

  else {
    selection_updated = true;
    //change/update menu_state
    menu_state = menu_selection + 1; //example: play game selected: menu_state = 0+1 = 1. play music is selected: menu_state = 1+1 =2
    //make next menu to show from first item
    menu_selection = 0;
  }

}
//what menu will be printed depends on menu_State value (0, 1 or 2)
void displayMenu(){
  if (menu_state == 0)
  {
    printMenu(main_menu);
  }

  if (menu_state == 1){
    play_game = true; //now it should be possible to activate runGame() in makeSelected()
    printMenu(game_menu);
  }

  if (menu_state == 2){
    play_music = true; // to run playM() with makeSelected() EXCEPT !!!!!!!!!!
                      // when hitting last option "exit to main menu"
    printMenu(music_menu);
  }
}
void printMenu(const char menu_to_print[][16]){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">");
  lcd.setCursor(1,0);
  lcd.print(menu_to_print[menu_selection]);

  //if last line is empty print(" 16 spaces ")
    //determine current menu list size(based on menu_state).
  int menu_size;
  if (menu_state == 0) menu_size = sizeof(main_menu)/sizeof(*main_menu);
  if (menu_state == 1) menu_size = sizeof(game_menu)/sizeof(*game_menu);
  if (menu_state == 2) menu_size = sizeof(music_menu)/sizeof(*music_menu);

  if (menu_selection == menu_size-1){
    lcd.setCursor(1,1);
    lcd.print("------end------");
  } else {
    lcd.setCursor(1,1);
    lcd.print(menu_to_print[menu_selection+1]);
  }
}








/*
• I denne oppgaven skal du lage et reaksjonsspill.
• Koble opp to knapper på hver sin pinne som kan håndtere interrupt
• Koble opp en buzzer og en led.
• To spillere skal ha hver sin knapp.
• I hver runde skal led’en tennes i en tilfeldig tid mellom 3 og 15 sekunder.
– Hvordan du får et tilfeldig tall kan du lese om her: 
https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
• Når led’en slukkes skal buzzeren begynne å pipe.
• Den første spilleren som trykker på knappen sin etter at buzzeren har begynt å pipe får et 
poeng.
• Om en spiller trykker for tidlig får han/hun et minuspoeng og runden avsluttes.
• Hvem som får poeng og stillingen skal skrives til LCD.
• Første spiller som får 5 poeng vinner spillet. 

– La buzzeren spille en liten melodi når en vinner er kåret.
*/