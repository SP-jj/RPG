#!/bin/bash

# Name: Stef Pollo
# Date: 19 May 2021
# Program Name: 
# Purpose:


#send msg that contdown is in progress to gameLogs
echo "hello"
echo "timeIsUp:False" > "../../gameLog"


# do countdown in seperate terminal tab

osascript -e 'tell app "Terminal"
do script "echo && echo hello player, continue your game here. && echo  "
end tell'

echo ''
echo ''
echo ''
echo ''
echo ''
echo ''
echo 'This terminal window is going to be used as a countdown counter now.'
echo 'In the new Terminal that just opened, cd into the JAIL directory and continue the game from there.'
echo ''
echo 'Tip: you can quickly cd into any directory/folder by typing cd into the terminal, and then dragging the folder into the terminals window.'
echo 'This pastes the entire pathway of the file into the command'
echo ''

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
RESET='\033[0m'
hour=0
min=20
sec=00
tput civis
echo -ne "${GREEN}"
        while [ $hour -ge 0 ]; do
                while [ $min -ge 0 ]; do
                        while [ $sec -ge 0 ]; do
                                if [ "$hour" -eq "0" ] && [ "$min" -eq "0" ]; then
                                        echo -ne "${YELLOW}"
                                fi
                                if [ "$hour" -eq "0" ] && [ "$min" -eq "0" ] && [ "$sec" -le "10" ]; then
                                        echo -ne "${RED}"
                                fi
                                echo -ne "$(printf "%02d" $hour):$(printf "%02d" $min):$(printf "%02d" $sec)\033[0K\r"
                                let "sec=sec-1"
                                sleep 1
                        done
                        sec=59
                        let "min=min-1"
                done
                min=59
                let "hour=hour-1"
        done
#echo -e "${RESET}"
tput cnorm

echo -e "${YELLOW}The transport arrived and arrested you. They are bringing you to the dungeons and there is no escape. You failed."
echo ''
echo ''
echo -e "${RED}GAME OVER${RESET}"


#set gameLog that time ran out
echo "timeIsUp:True" > "../../gameLog"



# echo msg explainging time ran out

# call resetGame

# unhide file in BEGIN explaining that time ran out
