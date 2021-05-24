#! /bin/bash

# Name: Stef Pollo
# Date: 24 May 2021
# Program Name: .setupGame.sh
# Purpose: resets the game by hiding all of the directories again



#for later implementation:
# if this is the first time playing, the jail dir will be hidden
if  ls -a | grep -q ".JAIL" ; then
#     echo ".jail does not exist"		
	mv .JAIL JAIL

    echo '
    Since this is your first time playing, you will need to enter the command that compiles cpp code on your computer.
    Please enter that command, and for the file to be compiled please insert {{FILEcpp}}, 
    and for the specified name of its executable, please insert: {{FILE}}

    Example: clang++ {{FILEcpp}} -std=c++17 -o {{FILE}}
    '

    echo -n "Please enter the command:  "
    read compileCMD

    #save compileCMD so that user doesnt need to be asked everytime they reset game
    clirpgPath=$(dirname $PWD)
    echo "compileCMD:$compileCMD" > "$clirpgPath/config"

fi

#go to TOWN_SQUARE to hide all directories in it
if [ -d JAIL ]; then
    cd JAIL
    if [ -d TOWN_SQUARE ]; then
        cd TOWN_SQUARE
    fi
fi

for location in DUKES_MANOR TAVERN FOREST
do 
	if [ -d $location ]; then
	
	mv $location .$location   #files and folders with . prefix are hidden files in mac	
	fi

done

# if current dir is town square(whether its hidden or not deosnt matter)
if [ $PWD == "*TOWN_SQUARE" ]; then
    #go to jail to hide the town square dir
    cd ..

    # if town square is shown, hide it
    if [ -d TOWN_SQUARE ]; then
        mv TOWN_SQUARE .TOWN_SQUARE
    fi
fi





# #needed so that the source code can be compiled locally

# filename=thefile
# filenamecpp=thefile.cpp



# #substitute {{FILEcpp}} string with variable $FILEcpp
# compileCMD2=${compileCMD//"{{FILEcpp}}"/$filenamecpp}

# compileCMD3=${compileCMD2//"{{FILE}}"/$filename}

