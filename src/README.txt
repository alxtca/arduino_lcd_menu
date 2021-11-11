Overview:

Game - game.h, game.cpp
LCD display - lcd.h, lcd.cpp
Main program - main()
Music:
  notes and tracks   - music.h
  play function      - music.cpp
Pins                 - pinlayout.h
Pin setup functions  - pinlayout.cpp
Interrupt functions  - interrupt.h, interrupt.cpp


Menus:

0 Main menu: (in lcd.h variable main_menu)
  1 Play Game (in game.h variable game_menu)
    1.1 start new game
    1.2 exit to main menu
  2 Play Music (in music.h variable music_menu)
    2.1 Song #1
    2.2 Song #2
    2.3 Song #n
    2.4 exit to main menu

    play_music = true //now makeSelected() should run playM()
    menu_state = 2
    menu_selection = 0 //to show items from the top


(I did not move all menus to one header file to make each header file selfsufficient)