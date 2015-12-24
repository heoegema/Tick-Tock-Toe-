//Tick Tock Toe
//by Holly Oegema & Alex Blackmore
//June, 2015

#include <iostream.h> 
#include "apstring.h"   
#include <apmatrix.h> 
#include <apvector.h> 
#include <stdlib.h>
#include <time.h> 
#include <stdio.h>

//Prototypes
void SpaceOutput(int intRowNumber, int intBoardSize);
void Yaxis(int intBoardSize);
void SolidLine(int intBoardSize, char chrBoard);
void VerticalLineSegment(int intBoardSize, int intRowNumber, char chrBoard,
      	apvector< apmatrix<char> > Board, int intBoardNumber);
void BoardConstruction(char chrBoard, int intBoardSize, apvector< apmatrix<char> > Board);
void PlayerTurn(apvector< apmatrix<char> > &Board, int &intSpacesUsed, char &chrTurn, 
  	int intBoardSize, apstring strPlayer1, apstring strPlayer2, time_t EndTime, bool &TimeOut);
int CollectValue(apstring Type, int intBoardSize);
void ChainReaction(apvector < apmatrix<char> > &Board , char &chrTurn, int intBoardSize,
   	int intSpacesUsed);
void ChainReactionCreation(apvector < apmatrix<char> > &Board, int intBoardSize);
int CheckWin(apvector< apmatrix<char> > Board, int intBoardSize, char chrWinCharacter, 
  	int intSpacesUsed);
void StartScreen();
int CollectBoardSize();
char CollectBoardCharacter();
int ClockTime(time_t StartTime, time_t EndTime, int intBoardSize);
void Instructions();
bool CheckTime(char &chrTurn, time_t deadline, time_t EndTime, bool &TimeOut);

void Instructions()
{ 
 //This function will display the intro and the instructions for the game 
 
 //Intro for the game
 cout << "\n\nImagine yourself in a large metal room," 
   << " filled with buttons and switches and levers "
   << " and screens and flashing lights, all screaming "
   << " one unifying message: \nDANGER.\n\nYou are standing "
   << "inside one of the largest nuclear reactors in the"
   << " world, and it's about to explode.\n"
   << "\nBut you are no ordinary drekec pekec:"
   << "\nYou are the world's foremost nuclear reactor"
   << " and hacking expert and you have been tasked to"
   << " diffuse this plant and save the lives of the "
   << "millions of \nunaware citizens in a nearby city.\n"  
   << "To defuse the explosives, you must hack the"
   << " reactors main frame and release the safety mechanisms" 
   << " by connecting a line of circuits." 
   << "\n\nAre you up for the task?";   
 
 //Instructions for the game
 cout << "\n\nHow To Play: " << endl
   << "\nAt the beginning of the game you will be asked to enter a number up to"
   << "9, this will be used to create an n by n by n board." 
   << "\nYou will have a certain amount of time to complete the game."
   << "\n\nDuring each player's turn you will be asked to enter:"
   << "\n1. A Board Number (indicated by the z)"
   << "\n2. The Column Number (indicated by the y)"
   << "\n3. The Row Number (indicated by the x)"
   << "\nIf the spot is valid, a marker (either X or O depending on the player's turn"
   << "will be placed on the board."
   << "\nIf you do not complete your turn within 30 seconds, your turn will be missed"
   << "\n\nThere are hidden spots that are randomly generated called 'Chain Reaction Spots.'"
   << "These spots will either cause the player to miss a turn or\n"
   << "will randomly remove a random amount of player markers from the board."
      << "\n\nThere are three ways for the game to end:"
      << "\n1. Player 1 Wins"
   << "\n2. Player 2 Wins"
   << "\n3. Time Runs out (Nuclear Meltdown occurs)" 
   << "\n\nHow to Win"
   << "\nConnect one corner of a board to another corner of a board in any dimension."; 
}

void StartScreen()
{

 //This function will display the game's title
 //and an option to start the game
 //Displaying the game's title
 cout << "  ______   __     ______     __  __        ______   ______     ______     __  __      "
   << "  ______   ______     ______"  << endl;    
 cout << " /\\__  __\\/\\ \\   /\\  ___\\   /\\ \\/ /       /\\__  _\\ /\\  __ \\   /\\  ___\\  "
   << " /\\ \\/ /       /\\__  _\\ /\\  __ \\   /\\  ___\\"  << endl;    
 cout << " \\/_/\\ \\/ \\ \\ \\  \\ \\ \\____  \\ \\  _\" -.    \\/_/\\ \\/ \\ \\ \\/\\ \\  \\ "
   << "\\ \\____ \\ \\  _\" -.     \\/_/\\ \\/ \\ \\ \\/\\ \\  \\ \\  __\\"  << endl;    
 cout << "    \\ \\_\\  \\ \\_\\  \\ \\_____\\  \\ \\_\\ \\_\\       \\ \\_\\  \\ \\_____\\  \\ "
   << "\\_____\\  \\ \\_\\ \\_\\       \\ \\_\\  \\ \\_____\\  \\ \\_____\\"  << endl;  
 cout << "     \\/_/   \\/_/   \\/_____/   \\/_/\\/_/        \\/_/   \\/_____/   \\/_____/   "
   << "\\/_/\\/_/        \\/_/   \\/_____/   \\/_____/ "  << endl;
 cout << "\n\n\t\t\t\t\t\t\t\t\t\tCreated by Holly Oegema & Alex Blackmore, June 2015";

}

int CollectBoardSize() 
{ 
    
    //This function will collect the desired board size for the game
    //The board size will serve as the variable n in the n by n by n
    //board
    
    //Declarations 
    int intBoardSize; 
 
  	cout << "\n\nPlease enter your desired board size. WARNING: board sizes greater than 5 are "
    << "extremely slow and challenging to play. Some patience is required. ";
    while (!(std::cin >> intBoardSize) || intBoardSize < 0 || intBoardSize > 9) 
      //If the number is less than 0 or greater than 9
    {
        cout << "Please enter an integer number between 1 and 9: "; //Ask the user to enter a new 		number  
        cin.clear();  //Clear current value  
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore current value                 
    } //Loop is terminated once a valid value is collected
    
    cin.clear();  //Clear current value  
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore current value 
   
    return intBoardSize; //Return the intBoardSize size

}

char CollectBoardCharacter()
{
 //This function collects a character from the user with which the board is created
 char chrInput;
 
 //Asks the user for a character input, which is placed into chrInput
 cout << "What character would you like the board to be made of? We recommend @, #, or *, but "
   << "anything can be used: ";
 cin >> chrInput;
 
 //Any inputs following the first character are ignored 
 std::cin.clear();   
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   
 return chrInput;
}

void SpaceOutput(int intRowNumber, int intBoardSize)
{
 //This function outputs a series of spaces which precede various segments of the board
    int intCount=0;
 
    //The amount of spaces output for the top line of the board is 4*intBoardSize +3 (to account for
    //the z=_). For every line output, the number of spaces output is decreased by 1, using
    //intRowNumber.
    while (intCount<(4*intBoardSize-intRowNumber)+3)
    {
  cout << " ";
  intCount++;
      
  //During certain rows, the number of spaces output needs to be decreased by 2, to account for
  //the x-axis numbers. So, when the intRowNumber%4 is 2 and intCount is a specific number,
  //intCount is increased by 2 so that two-less spaces are output
  if ((intRowNumber)%4==2 and intCount==4*intBoardSize-intRowNumber+1)
   intCount=intCount+2;
    }
}



void Yaxis(int intBoardSize)
{
 //Outputs the y-axis above the board
 int intCount=1;
 
 //intCount followed by 5 spaces is output intBoardSize number of times
 while (intCount<=intBoardSize)
 {
  cout << intCount << "     ";
  intCount++;
 }
 
 //A "y" is output to indicate the y-axis, and then a new line is created
 cout <<"y\n";
}

void SolidLine(int intBoardSize, char chrBoard)
{
 //Outputs a solid line of characters
 int intCount=0;
 
 //Every square space on the board is 6 characters long, so 6*intBoardSize characters are output
 while (intCount<6*intBoardSize)
 {
  cout << chrBoard;
  intCount++;
 }
 
 cout << chrBoard <<"\n";
}

//Outputs vertical lines, spaces, and player markers.
void VerticalLineSegment(int intBoardSize, int intRowNumber, char chrBoard, 
 apvector< apmatrix<char> > Board, int intBoardNumber)
{
 //Outputs vertical lines, spaces, and player markers.
 int intCount=0;
 
 //Every 4 lines, another part of the x-axis is output, as determined by intRowNumber
 if (intRowNumber%4==2)          
  cout << (intRowNumber/4)+1 << " ";
   
 //This while loop runs intBoardSize number of times. Each time, a board character is output as 
 //part of the vertical lines on the board, followed by a space. The contents of Board
 //which correspond with that position is then output. This is either a blank space, an X/O
 //marker, or a C for a chain reaction spot. If it is a C, Board is ignored and a blank space
 //is output. This is then followed by a space. 
 while (intCount<intBoardSize)
 {
  cout << chrBoard << "  ";
  
  if (intRowNumber%4==2 and Board[intRowNumber/4][intCount][intBoardNumber-1]!='C')         
   cout << Board[intRowNumber/4][intCount][intBoardNumber-1];
  else
   cout << " ";
  
  cout <<"  ";
  intCount++;
 }
 
 cout << chrBoard << "\n";
}

void BoardConstruction(char chrBoard, int intBoardSize, apvector< apmatrix<char> > Board)
{
 //This function controls board construction using the functions above
 int intBoardNumber=1;
    int intCount=0;
    int intRowNumber=0;
 
    while (intBoardNumber<=intBoardSize)
    {
  //This while loop controls the amount of boards which are output
  //Outputs the board number (z) in the top left of each board
  cout << "z=" << intBoardNumber;
  intRowNumber=0;
  
  //Outputs the y-axis above each board
  SpaceOutput(intRowNumber,intBoardSize);
  Yaxis(intBoardSize);
  
  while (intRowNumber<4*intBoardSize)
  {
   //Controls the amount of boxes which are output
   //First, the upper line of a box is output, via SolidLine()
   SpaceOutput(intRowNumber,intBoardSize);
   SolidLine(intBoardSize,chrBoard);
   
   while(intRowNumber%4!=3)
   {
    //Controls the specific row output for each box on the board
    //Three rows of vertical line segments are output for each box on the board
    intRowNumber++;
    SpaceOutput(intRowNumber,intBoardSize);
    VerticalLineSegment(intBoardSize, intRowNumber, chrBoard, Board, intBoardNumber);
   }
     
   intRowNumber++;
  }
  
  //Finally, at the bottom of each board, an x is output the indicate the x-axis, and a solid
  //line closes off the last row of boxes
  cout <<" x ";
  SolidLine(intBoardSize,chrBoard);
  cout << endl;
      
  intBoardNumber++;
 }
}
void ChainReactionCreation(apvector < apmatrix<char> > &Board, int intBoardSize)
{
    //This function will create and generate the ChainReactionSpots
    //We will generate a random number of spaces to be created based on
    //the board size
    //Next we will, generate a set of coordinates for each chain reaction spot
   
    //Declarations
    
    //Generate a random number of chain reaction spots between the board size and 0.
    int intChainReactionSpots = rand()% intBoardSize + 0; 
    int intCount = 0; //Looping variable
    int intRow = 0; 
    int intColumn = 0;
    int intBoard =0;
    
    while (intCount <= intChainReactionSpots)
    {
        //Generate a random set of coordinates
        
        intRow = (rand() % intBoardSize + 1) - 1;
        intColumn = (rand() % intBoardSize + 1)-1;
        intBoard = (rand() % intBoardSize + 1)-1;
       
        //Assign a value of 'C' to the matrix based on these randomly generated coordinates
       
        if (Board[intRow][intColumn][intBoard] != 'C')
        {
            Board[intRow][intColumn][intBoard] = 'C'; //Assign a 'C' value to the matrix
            intCount = intCount + 1; //Increase intCount by 1
        }
        
    }
}
void PlayerTurn(apvector< apmatrix<char> > &Board, int &intSpacesUsed, char &chrTurn, int intBoardSize, 
  apstring strPlayer1, apstring strPlayer2, time_t EndTime, bool &TimeOut) 
  //Basically this is what the player's turn will look like
{
    //Basically we'll collect 'values from the user-[intRow][intColumn][intBoard]
    //Then assign a value of either 1 or 2 to the matrix depending on whose turn it is
    //We also have to count how many spaces are taken
    //As well as check to see if the space is taken or not
    //For reference Board[intRow][intColumn][intBoard]
    //Each turn will also be timed (30 seconds) 
    //If the user exceeds this designated amount of time
    //then their turn will be skipped
    
    //Declarations
    int intBoard;
    int intRow;
    int intColumn;
    int Flag = 0; //This marks whether or not a player has completed their turn
    apstring strNumberType;
    bool ContinueGame = true; 
    //Setting up timer variables
    clock_t Now = clock(); //current system time in "ticks"
    //We set the Player Turn 'Deadline' (Time they must complete the turn by)
    //by adding the current time plus 30 seconds 
    //in other words will player will have 30 seconds to complete their turn
    clock_t Deadline = Now + 30*CLOCKS_PER_SEC;
   
    
    //This loop will run until either the turn is complete or the player runs out of time
   while (clock() <= Deadline && Flag != 1)
   {
     //If the current time is not the deadline
        if (clock() != Deadline) 
        { 
            if (chrTurn == 'X') //If it's Player 1's turn (X)
           cout << "\n" << strPlayer1 << ", it's your turn! You have 30 seconds.\n"; 
                
            else //It's Player 2's Turn (O) 
             cout << "\n" << strPlayer2 << ", it's your turn! You have 30 seconds.\n"; 
         
         //Collecting the board number (z)
            strNumberType = "Board Number";
            intBoard = CollectValue(strNumberType, intBoardSize);
                
            //Check to see if the game or player time has been exceeded
            if (ContinueGame == CheckTime(chrTurn, Deadline,EndTime, TimeOut)) 
                 break; //break out of the player turn loop
                
            //Collecting the Column number coordinate (y)
            strNumberType = "Column Number(Down)";
            intColumn = CollectValue(strNumberType, intBoardSize);
                
            //Check to see if the game or player time has been exceeded
            if (ContinueGame == CheckTime(chrTurn, Deadline,EndTime, TimeOut)) 
                 break; 
                        
            //Collecting the Row Number coordinate (x) 
            strNumberType = "Row Number(Across)";
            intRow = CollectValue(strNumberType, intBoardSize);
                
            //Check to see if the game or player time has been exceeded
            if (ContinueGame == CheckTime(chrTurn, Deadline,EndTime, TimeOut)) 
                 break; 
                        
            Flag = 1; //Set the player turn flag to 1. 
    
         //Now that we have collected valid values, let's see if the space is taken
         if (chrTurn == 'X' && Board[intRow][intColumn][intBoard] == ' ') //The space is free
         {  
             Board[intRow][intColumn][intBoard] = 'X'; //We assign a value of '1' to the matrix (x)
             intSpacesUsed = intSpacesUsed + 1; //We need this to check how much spaces are used...
             chrTurn = 'O'; //And finally we make it Player 2's turn  
         }
         else if (chrTurn == 'O' && Board[intRow][intColumn][intBoard] == ' ') //The space is free
         {
        
             Board[intRow][intColumn][intBoard] = 'O'; //We assign a value of 'O' to the matrix (O}
             intSpacesUsed = intSpacesUsed + 1; //Increase the amount of spaces used
             chrTurn = 'X'; //Switch the turn
         }
         else if (Board[intRow][intColumn][intBoard] == 'C')
         {
            //If the player hits a chain reaction spot 'C'-call on teh chain reaction function
             ChainReaction(Board, chrTurn, intBoardSize, intSpacesUsed);
             //Erase the Chain Reaction Spot and set it to blank
             Board[intRow][intColumn][intBoard] = ' '; 
         }    
         
         else //The space is taken
         {
           
             cout << "Sorry that space is taken! Please choose another one!\n";
             //Recall the player turn function
             PlayerTurn(Board, intSpacesUsed, chrTurn, intBoardSize, strPlayer1, strPlayer2, 
                              EndTime, TimeOut);
         }
         
      } 
     
     else //If the player turn deadline has been exceeded switch the turns
     { 
              
         if (chrTurn == 'X')
             chrTurn = 'O';
         else 
             chrTurn = 'X';
     
     } 
    
    }

   
}

bool CheckTime(char &chrTurn, time_t Deadline, time_t EndTime, bool &TimeOut)
{ 
    //If the current time is greater than the deadline for the player turn 
    if (clock() >= Deadline) 
    { 
        //Inform the user that their turn took too long
        cout << "You took too long. Turn missed.\n\n";
        
        //Switch the turns 
        if (chrTurn == 'X')
            chrTurn = 'O'; 
        else    
            chrTurn = 'X';

        return true; //Return a true value 
    }

    else if (clock() >= EndTime) //This means that the game is finished (run out of time) 
    { 
        //Set the Timeout Value to true
        TimeOut = true; 
        return true; //Return a true value
    } 
    
    else  //Else if the player time and game time is still remaining return a false value 
        return false;

} 
int CollectValue(apstring Type, int intBoardSize)
{
    //This function will collect and return coordinate values
   
    //Declarations
    int intNumber;
    
    cout << "Please enter a " << Type << ": ";
    while (!(std::cin >> intNumber) || intNumber < 1 || intNumber > intBoardSize) 
     //If the number is less than 0 or greater than the board size
    {
       cout << "Please enter an integer number between 1 and  " << intBoardSize << ": "; 
       //Ask the user to enter a new number 
       cin.clear();  //Clear current value 
       cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore current value               
    } //Loop is terminated once a valid value is collected
   
 //We return a number 1 less than what the user entered because the matrix starts at 0, but
    //the user's 'choices' start at 1, so if they choose 1,1-we need to enter a value in '0,0'
    
    cin.clear();  //Clear current value  
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore current value 
        
    return intNumber-1; //Return this value
}

void ChainReaction(apvector < apmatrix<char> > &Board, char &chrTurn, int intBoardSize, int intSpacesUsed)
{
    //This function is called upon when the user tries to enter a space where
    //a 'C' value is stored
    //We will determine how many of the character's pieces will be removed
   
   
    //Declarations
    int RemovalSpots = 0; //This will track how many pieces we are to remove
    int intCount = 0; //Looping variable
    int intColumn = 0; //Looping variable
    int intRow = 0; //Looping variable
    int intBoard = 0; //Looping variable
    
    //If the amount of spaces used is less than 2, we can't remove any markers so we'll
    //have the player skip a turn
    if (intSpacesUsed < 2)
    {
        cout << "\n\nYou've hit a glitch! Chain Reaction Occurs! Miss a Turn!";
    }
   
    else 
    {
        //If the amount of spaces used is greater than 2
        //we will generate a random number between 1 and intspacesused/2
        //and remove those spots
        
        cout << "\n\nYou've hit a glitch! Chain Reaction Occurs! Miss a Turn!"; 
        //Generate a random number between 1 and the spaces used/2 (player's turns)
        RemovalSpots = (rand() % intSpacesUsed/2 + 1); 
       
        //Now that we've generated the number of markers to be removed.
        //We remove them
        
        //This nested loop will run until either it has searched the board
        //or has removed the right amount of markers 
        while (intBoard < intBoardSize-1 && intCount < RemovalSpots)
        {
            if (Board[intRow][intColumn][intBoard] == chrTurn)
            {
                Board[intRow][intColumn][intBoard] = ' '; //Erase the marker
                intCount = intCount + 1; //Increase the amount of markers removed by 1
                intSpacesUsed = intSpacesUsed - 1; //decrease the amount of spaces taken
            }
           
            while (intRow < intBoardSize-1 && intCount < RemovalSpots)
            {
                if (Board[intRow][intColumn][intBoard] == chrTurn)
                {
                        Board[intRow][intColumn][intBoard] = ' '; //Erase the marker
                        intCount = intCount + 1; //Increase the amount of spots removed by 1
                        intSpacesUsed = intSpacesUsed -1; //decrease the amount of spaces taken
                }
           
                while (intColumn < intBoardSize-1 && intCount < RemovalSpots)
                {
                    if (Board[intRow][intColumn][intBoard] == chrTurn)
                    {
                        Board[intRow][intColumn][intBoard] = ' '; //erase the marker
                        intCount = intCount + 1; //increase the amount of markers removed by 1
                        intSpacesUsed = intSpacesUsed -1; //decrease the amount of spaces taken
                    }
                       
                    intColumn = intColumn + 1; //Looping variable   
                }
                   
                intRow = intRow + 1; //Looping variable
            }
               
            intBoard = intBoard + 1; //Looping variable
        }
    }
   
   //Switch the turns 
   if (chrTurn == 'X')
            chrTurn = 'O';
        else
            chrTurn = 'X';
            
   cout << endl << endl;
}   

int CheckWin(apvector< apmatrix<char> > Board, int intBoardSize, char chrWinCharacter, int intSpacesUsed)
{ 
    //After every turn, the board is checked for a win to determine if the game will continue 
 
 //At the end of each player turn, the character used to indicate whose turn it is is switched
 //This is undone temporarily because if a win is found, it will belong to the previous player
 if (chrWinCharacter=='X')
  chrWinCharacter='O';
    else
  chrWinCharacter='X';
 
    int intCheckWin=0;
 //Horizontal/Vertical win check. There are three planes on each board: x/y, y/z, and x/z. 
 //Each plane has it's own horizontal/vertical win criteria. The basic structure for a 
 //horizontal/vertical win check is three nested counting variables in while loops.
 //Within the third counting loop, each counting variable is used as a coordinate in
 //the matrix Board. The arrangement of each counting variable as x/y/z coordinates
 //depends on the plane and type of win which is being checked. This is determined
 //by intWinCheck. The list of win types and intCheckWin values can be found below. 
 //If the contents at that specific coordinate match the win character, then the interior 
 //counting variable is increased by 1. Another check is done etc. This loop is broken 
 //when either the third looping variable reaches the board size, or a non-matching
 //character is found along the way. After the loop is broken, the third looping
 //variable is compared to intBoardSize. If they are equal, then a win has been 
 //found. If not, then the third counting variable is reset to 0 and the second counting
 //variable is incremented by 1 and the process repeats. When the second counting 
 //variable reaches the board size, the first counting variable is incremented by 1
 //and the second counting variable is reset to 0 and the entire process repeats. 
 //When the first counting variable reaches the board size, then no wins have been 
 //found of that specific type. intCheckWin is then increased by 1 and the first counting
 //variable is reset to 0. This is done 6 times, for each of the 6 types of horizontal/vertical
 //wins
    //intWinCheck=0 Horizontal x/y
    //intWinCheck=1 Vertical x/y
    //intWinCheck=2 Horizontal y/z
    //intWinCheck=3 Vertical y/z
    //intWinCheck=4 Horizontal x/z
    //intWinCheck=5 Vertical x/z
    int intCount=0, intCount2=0, intCount3=0;
     
    while (intCheckWin<6)
    {
  intCount3=0;
  while (intCount3<intBoardSize)
  {
   intCount2=0;
   while (intCount2<intBoardSize)
   {
    intCount=0;
  
    
    while (intCount<intBoardSize and (
     (intCheckWin==0 and Board[intCount][intCount2][intCount3]==chrWinCharacter) or
     (intCheckWin==1 and Board[intCount2][intCount][intCount3]==chrWinCharacter) or
     (intCheckWin==2 and Board[intCount3][intCount][intCount2]==chrWinCharacter) or
     (intCheckWin==3 and Board[intCount3][intCount2][intCount]==chrWinCharacter) or
     (intCheckWin==4 and Board[intCount][intCount3][intCount2]==chrWinCharacter) or
     (intCheckWin==5 and Board[intCount2][intCount3][intCount]==chrWinCharacter)))
    {
     intCount++;
         
     if (intCount==intBoardSize)
     {
      return 1;
     }
    }
        
    intCount2++;
   }
   
   intCount3++;
  }
     
  intCheckWin++;
    }
 
    intCheckWin=0;
    intCount=0;
    intCount2=0;
 
 //2D negative diagonal win check. The same general process from above takes place here, except
 //only two counting variables are used. This is because negative diagonal wins will always have
 //two coordinates which are equal. There is only 1 negative win possibility per plane, so 
 //intCheckWin only has 3 possible values (found below). 
    //0=negative diagonal x/y
    //1=negative diagonal y/z
    //2=negative diagonal x/z
     
    while (intCheckWin<3)
    {
  intCount2=0;
  while (intCount2<intBoardSize)
  {
   intCount=0;
   while (intCount<intBoardSize and (
    (intCheckWin==0 and Board[intCount][intCount][intCount2]==chrWinCharacter) or
    (intCheckWin==1 and Board[intCount2][intCount][intCount]==chrWinCharacter) or
    (intCheckWin==2 and Board[intCount][intCount2][intCount]==chrWinCharacter)))
   {
    intCount++;
       
    if (intCount==intBoardSize)
     return 1;
   }
     
   intCount2++;
  }
     
  intCheckWin++;
    }
     
 intCheckWin=0;
    intCount=0;
    intCount2=0;
    intCount3=0;
 //Positive diagonal win check. Same general process above, except the second counting variable is
 //used. This checks the reverse of the diagonal above by having one of the counting variables
 //start at the intBoardSize-1 (since a board size of 3 will have a matrix range of 0-2) and then 
 //be diminished by 1 every cycle. 
    //0=positive diagonal x/y
    //1=positive diagonal y/z
    //2=positive diagonal x/z
     
    while (intCheckWin<3)
    {
  intCount3=0;
  while (intCount3<intBoardSize)
  {
   intCount2=intBoardSize-1;
   intCount=0;
   while (intCount<intBoardSize and (
    (intCheckWin==0 and Board[intCount2][intCount][intCount3]==chrWinCharacter) or
    (intCheckWin==1 and Board[intCount3][intCount2][intCount]==chrWinCharacter) or
    (intCheckWin==2 and Board[intCount2][intCount3][intCount]==chrWinCharacter)))
   {
    intCount2--;
    intCount++;
     
    if (intCount==intBoardSize)
    return 1;
   } 
   
   intCount3++;
  }
      
  intCheckWin++;
    }
    
    intCheckWin=0;
 intCount=0;
    intCount2=0;
    intCount3=0;
    
 //This function checks the 4 possible 3D diagonal wins using an increasing and a decreasing 
 //counting variable. 
 
 //intCheckWin=0, Back-Bottom-Left-Corner to Front-Top-Right-Corner: All x/y/z values of the 
 //coordinates from (0,0,0) to (boardSize, boardSize, boardSize) are equivalent, so only 1 looping 
 //variable has to be increased and used in each coordinate
 
 //intCheckWin=1, Front-Bottom-Left-Corner to Back-Top-Right-Corner: x coordinate starts at board 
 //size -1, y and z start at 0. x is decreased while y and z are increased until they reach board 
 //size.
 
 //intCheckWin=2, Back-Bottom-Left-Corner to Front-Top-Right-Corner: y coordinate starts at board 
 //size -1, x and z start at 0. y is decreased while y and z are increased until they reach board 
 //size. 
 
 //intCheckWin=3, Front-Bottom-Right-Corner to Back-Top-Left-Corner: Both x and y start at board 
 //size -1, z starts at 0. x and y are decreased while z is increased until it reaches board size. 
 
 while (intCheckWin<4)
 {
  intCount=0;
  intCount2=intBoardSize-1;
  
  while (intCount<intBoardSize and (
   (intCheckWin==0 and Board[intCount][intCount][intCount]==chrWinCharacter) or
   (intCheckWin==1 and Board[intCount2][intCount][intCount]==chrWinCharacter) or
   (intCheckWin==2 and Board[intCount][intCount2][intCount]==chrWinCharacter) or 
   (intCheckWin==3 and Board[intCount2][intCount2][intCount]==chrWinCharacter)))
  {
   intCount++;
   intCount2--;
     
   if (intCount==intBoardSize)
    return 1;
  }
  
  intCheckWin++;
 }
    
 //Tie check: intSpacesUsed keeps track of the number of spaces which are taken up on the board. 
 //When this value reaches the board size cubed, then all spaces have been taken up and the game 
 //ends. To differentiate from a win, CheckWin() returns a 2 instead of a 1 (which would indicate
 //a win). Otherwise, a 0 is returned and the game continues. 
    if (intSpacesUsed==intBoardSize*intBoardSize*intBoardSize)
  return 2;
    else
  return 0;
}

int main()
{ 
     
    //Declarations 
    
     char chrBoard;
     int intBoardSize;
     int intSpacesUsed=0;
     char chrTurn='X';
     int intContinue=0;
     apstring strPlayer1;
     apstring strPlayer2;
     bool TimeOut = false; 
     bool blnContinueGame = true; 
     //This ensures that all randomly generated spots (Mainly for Chain Reactions) will be different
     // every time the program compiles
     srand(time(0)); 
    
    StartScreen(); //This function displays the game's title
     
     //Prompt the users to enter their names 
     //This is so we can use the player's names throughout the game 
     
     cout << "\n\nPlayer 1, what is your name?: ";
     cin >> strPlayer1; //Assign the value entered to a variable 
     cin.clear();  //Clear current value  
     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore current value 
     
     cout << "Player 2, what is your name?: ";
     cin >> strPlayer2; //Assign the value entered to a variable
     cin.clear();  //Clear current value  
     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore current value 
        
     Instructions(); //Call on the Instructions function to display the game's intro and instructions 
     
     //Call on the CollectBoardSize function to collect the board's size from the user
     intBoardSize=CollectBoardSize(); 
     //Collect the character for the board construction
     chrBoard=CollectBoardCharacter(); 
    
    //Setting up some components 
    
    //Setting up the vector of matrices to store the board's information

     apmatrix<char> BoardVector(intBoardSize, intBoardSize, ' ');
     apvector< apmatrix<char> > Board(intBoardSize, BoardVector);
     
    //Setting up the game timer 
    
    //Depending on the board size generate the total game time.
     unsigned long GameTime=intBoardSize*intBoardSize*60; 
     
      //Setting the end time as the current time + the Game Time 
     time_t EndTime = clock() + GameTime*CLOCKS_PER_SEC; 
     //time_t currentTime = clock();
     //time_t deadline = clock()+10*CLOCKS_PER_SEC; //Testing Time 
     //time_t deadline = clock()+(intBoardSize*60)*CLOCKS_PER_SEC; //Actual Game Time
     
     //Generating our Chain Reaction Spot Locations 
    ChainReactionCreation(Board, intBoardSize);
     
     cout << "\n\n\n"; 
     
     //Draw the Board
     BoardConstruction(chrBoard, intBoardSize, Board);
     
     //Game Loop 
     
     //The game will run while intContinue == 0 (there is no win) and time still remains 
     while (intContinue==0 && clock() < EndTime)
     {
         cout << "\n"; 
        
        //Display the time remaining in the game
          cout << (EndTime -clock())/1000 << " seconds until nuclear meltdown.\n";
        
        //Call on the player turn function
        PlayerTurn(Board, intSpacesUsed, chrTurn, intBoardSize, strPlayer1, strPlayer2, EndTime, 
           TimeOut);
        if (TimeOut == true) //If the TimeOut has occured during the player turn break out of the loop
            break; 
        
        //If the spaces used is enough (2* boardsize)-1 Check for a win
        if (intSpacesUsed>=((2*intBoardSize)-1))
            intContinue=CheckWin(Board, intBoardSize, chrTurn, intSpacesUsed);
        
        //Draw the board
        cout << endl;
        BoardConstruction(chrBoard, intBoardSize, Board);
        
        //We check to see if the game time has run out. 
        if (clock() >= EndTime)
             TimeOut = true; //Set the value of Timeout to true
     }
        
    //This happens after the player has finished the game

     if (intContinue==1) //If there is a win
     { 
      cout << "Looks like "; 
      if (chrTurn == 'X') 
       cout << strPlayer2; 
      else 
       cout << strPlayer1;
      cout << " has gone nuclear!"; 
        cout << "\n\nCongratulations! ";
        if (chrTurn=='X')
            cout << strPlayer2;
        
        else 
            cout << strPlayer1;
        cout << " you have won!";
     }
   
    else if (TimeOut == true && intContinue == 0) //If the game has timed out 
        cout << "Look like your fishing trip has turned into a fission trip."
         << "You were unable to complete the circuit in time. Nuclear Meltdown occurs."; 
     
    else //If there is a tie
     cout << "\nLooks like this game was a dud."
          << "\nYou've tied. :("; 
    
    return 0;
}
