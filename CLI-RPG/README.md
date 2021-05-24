# CLI-RPG
Command Line RPG Game:

Main Objective:   Defeat Main Boss(MB) before time runs out
    Prereq: Reach Lvl 5
    
Raise lvl by earning XP

Main Objective - Complete your court-mandated community service:
      Complete 5 tasks for your town

      Once one task is completed, the next is presented to the player. they are to be completed in a linear order.

-Context: character wakes up hungover in a jail cell. They have been arrested for public intoxication and for starting a massive bar fight. To avoid doing time in prison, they agree to do 5 acts of community service.

Tasks:
      1 - Hunt and kill monster bear(pokemon battle-style fight)
      2 - Reach the heart of The Math Maze by getting 10 correct answers in a row so that you can the Abacus(magical relic)
      3 - Chase and catch a lost kitten(??)
      4 - Solve the Sphinx's riddle so that it will leave the town in peace
      5 - Defeat the evil duke stealing from the town(through "taxes") in a tic tac toe game

- navigate through game with terminal commands "cd" and "ls"
- use "cat" on files with a "Scroll" suffix to get instructions/context/immersive descriptions for the plot
- interact with game by running pre-compiled files( this may have to change so that the player compiles the source code themselves, for the game to be playable on OS other than mac) using "./file_name"
    


 
Features for later on(subject to change, ignore for now, Mr. Tombs)

{
  Login:
    Each player creates a profile before starting in order to save their progress.
    Profiles contain the username, password, the current stats of the character, and their position in the progression of the plotline

    On starting the program, users are prompted to login or create an account

  Player:
    Race Options(chosen upon character creation): Human,  Orc, Elf
      Initial Stats:
        Human:
          Health- 3/15
          Strength- 2/10
          Stealth- 1/10
          Luck- 4/10
        Orc:
          Health- 5/15
          Strength- 5/10
          Stealth- 0/10
          Luck- 0/10
        Elf:
          Health- 2/15
          Strength- 0/10
          Stealth- 5/10
          Luck- 3/10
          
      

  Activities To DO outside of plot:
    Fishing: 
            - Requirements: own fishing rod
            - You select it, then after a few seconds(period is randomized) you reel in an object
            - objects retrieved vary in worth and can be sold in the shop for cash
            - player's success in this activity is solely affected by their LUCK stat

    Pickpocket:
            - requirements: None
            - objects retrieved vary in worth and can be sold in the shop for cash
            - affected mainly by player's STEALTH skill, secondly by their LUCK skill
    
    Trade information for money:
            - this is done in the tavern area
            - you answer trivia questions for travelers passing through and they reward you with cash
    Tavern Fight:
          - straight forward
          - once player enters bar fight, log short descriptive messages to console(ex, oof, *grunt*, *crash*, "no dont throw that! thats an ANTIQUE",etc.)
          - ^that goes on for a couple seconds
          - when its over, player loses some health(how much is dependent on their strength, luck, & rand)
          - player also gains some XP(based on strength)
          - player is told how much XP they gain, how much health points they lose, and how long its going to take for their health to fill up to capacity again


  Plotline Activities:
    * examples of starts: "A villager approaches you, you hear a loud roar coming from the woods and go to investigate,etc.
    * these start without prompt, but the player is given the option to turn away from them at their beginning
    

}
