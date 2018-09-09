// Miguel A. Ruelasjacobo
// COP1334 Prof. Lawrence Eric Meyer
// EXTRA CREDIT:
// Place "houses" or other objects as obstacles in the grid :
// Delayed //cout for dramatic effect and readability
// Intro function that gives premise to the game and shows available commands

//Student Comments: I apologize in advance for all the commented out //cout 's. I wrote
//them in to be able to debug the game. I also put the function description in a cout
//at the very beginning of every function. I meant to go back and add the description outside
//the function. I did not use structures or pointers in order to keep the programming as simple
//as possible. The following are changes that I would have liked to make but it was not practical to make the changes
//this far into the project:

//I realized that declaring the variables globally meant that the functions had access
// to it and I did not need to actually put in the parameters. I would have liked to use structures and made
//my functions more flexible to accept all commands from smart, stupid, and user instead of creating functions
//for each.

//I learned a lot, and still have much more to learn.  This was a fun project and I am inspired to learn more about c++
//and work on becoming a programming. Thank you for the class!!!


#include <iostream>
#include <cstdlib> // For rand and srand
#include <ctime> // For the time function
#include <iomanip> // For setw
#include <time.h>  //for delaying cout
#include <windows.h>

using namespace std;

    const int maxlongt = 19 ;      // Array subscript north/south in grid
    const int maxlat = 19;         // Array subscript east/west in grid

    const int maxmenu = 12;        // Array subscript # of menu items

    char grid [maxlongt][maxlat];  // Array to hold characters to be displayed on screen
    int occp [maxlongt][maxlat];  // Array to hold show if grid is occupied
    const char menu [maxmenu]= {'0','1','2','3','4','5','6','7','8','9','.','q'}; //Array to hold valid menu options
    int curlat = 10;              // variable to hold east/west location of character
    int curlongt = 1;            // variable to hold north/south location of character
    int maxhealth = 5;            // variable to hold maximum health of character
    int curhealth = 5;            // variable to hold current health of character
    bool glasses = 0;             // variable to show if character is wearing glasses
    bool earmuff = 0;             // variable to show if character is wearing
    int moves = 0;                // variable to hold how many turns the user has used
    int turn = 0;                 // variable to hold how many turns have passed
    int stpkatz[5][2];            // Multidimensional array to hold location of stupid katz, [5] is the Katz and [5][0] longt, [5][1] lat
    int stpkatattck[5][1];        //Multidimensional array to hold if a stupid kat can attack // value of [5][0] = 0 no // 1 yes
    int stpkatateye[5][1];        //Multidimensional array to hold if a stupid kat can attack // value of [5][0] = 0 no // 1 yes
    int stpkatzmv[5][2];          // Multidimensional array to hold a random move to be made by stupid katz
    bool menupass =0;             //Used to test if a user action counts as a move
    bool stunned =0;              //used to skip turn if stunned is not 0
    bool dead =0;                 //used to end game if curheal is 0 or below
    int capture =-1;              //used to transfer what kat can be captured to katcapture function
    int stpkatdead[5][1];         //Array to hold value of stupid katz that are dead
    int won = 0;                  //tally that counts how many katz have been captured, when total is 5 all katz captured and game ends
    int smartkatz[5][2];          // Multidimensional array to hold location of smart katz, [5] is the Katz and [5][0] longt, [5][1] lat
    int smartkatdead[5][1];       ////Array to hold value of smart katz that are dead
    int smartkatateye [5][1];     //Multidimensional array to hold if a smart kat can attack // value of [5][0] = 0 no // 1 yes
    int smartkatzmv[5][2];        // Multidimensional array to hold a move to be made by smart katz
    bool smart= 1;                   //Flag to show if katz seem smart or dumb

void initgrid (char [maxlongt][maxlat]);                                                    //function that builds the grid array
void display(char [maxlongt][maxlat]);                                                      //function that displays the grid
void currentloc(char [maxlongt][maxlat],int [maxlongt][maxlat],int curlongt, int curlat);   //function that updates the current character location on the grid
void priorloc(char [maxlongt][maxlat],int [maxlongt][maxlat],int curlongt, int curlat);     //function that clears the prior location of the character
void occupiedloc(int [maxlongt][maxlat],int curlongt, int curlat,int katnum);                          //function updates the grid to show where the Katz are '1'
//void freeloc(int [maxlongt][maxlat],int curlongt, int curlat);                             // currently not used
int validmenu(const char menu[maxmenu],char);                                                //function searches through array for user input returns member location if found to value of menunum
bool menuexec(int);                                                                          //Function initiates menu testing to see if it can be executed returns false if user selection cannot execute
char inptcommand();                                                                          //Function gets character from user
bool charmovetest(int dir);                                                                  //function used to test if user is attempting to move out of bounds
void charmov(int dir);                                                                       //funtion updates curlongt and curlat of character if able to move to new location
void huddisplay();                                                                           //function displays character health, glasses and earmuffs status.
void randkatloc(int);                                                                        //function randomly generates location of stupid katz to stpkatz array [][0] is longt and [][1] is lat
void populatekatz();                                                                         //function uses stplatz array locations to update the grid array with locations of stupid katz
bool occptest(int dir);                                                                       //function tests to see if the space the user wants to move to is occupied
void cankatattckpur();                                                                        //function to test the distance of kat from user sets value in stpkatattck array to 1 if kat can use purr attack;
void katattckpur();                                                                           //function executes a purr attack sets stunned variable to true if successful
void randkatmov();                                                                            //function that generates random moves for katz
bool stpkatzmvexec(int ,int katnum);                                                          //function that initiates tests for random move that was generated for the kat
void stpktmov(int, int);                                                                       //function that executes a move for katz if the space is empty
bool katmovetest(int dir,int katnum);                                                          //Function tests to see if kat is moving out of bounds
bool occptestkatz (int dir, int katnum);                                                       //Function tests to see if there is something in a grid for katz only
bool purrtest();                                                                               //function tests if kat is close enough to use a purr attack
void katattckeye();                                                                            //function executes attacks from cats who can eye attack
bool eyetest();                                                                                //function tests if a kat is close enough to do an eye attack
void katcapture(int);                                                                          //function executes capture command from user if there katz nearby
int cankatcapture();                                                                           //function tests if katz are close enough to capture
void foundtuna();                                                                              //function tests if tuna is found after kat is captured
bool smartkatzmvexec(int comd,int katnum);
bool smartoccptestkatz (int dir, int katnum);
bool smartkatmovetest(int dir,int katnum);
void smartktmov(int dir,int katnum);
void intro();


int main()
{
    char usrinp;                                                   //holds user choice
    int menunum;                                                   // Used to test if user input was valid
    int stpdkatz =5;                                               //Number of stupid katz
    //cout << "**Calling Function: " << intro << endl;
    intro();
    //cout << "**Calling Function: " << "initgrid" << " Line 59 " << endl;
    initgrid(grid);                                                //Call function to build grid

    //cout << "**Calling Function: " << "randkatloc" << " Line 62 " << endl;
    randkatloc(stpdkatz);                                           //Call function to populate stpdkatz array with grid locations

    //cout << "**Calling Function: " << "populatekatz" << " Line 64 " << endl;
    populatekatz();

    //cout << "**Calling Function: " << "currentloc" << " Line 68 " << endl;
    currentloc(grid,occp,curlongt,curlat);

    //cout << "**Calling Function: " << "display" << " Line 71 " << endl;
    display(grid);

    //cout << "**Calling Function: " << "huddisplay" << " Line 73 " << endl;
    huddisplay();
    //cout << "Longt: " << curlongt <<" lat: " << curlat <<  endl;
    cout << "Move " << moves << "/2" << endl ;
    cout << "Turn 0" << endl;
    Sleep(200);
    cout << "Command:";


    do
        {
            if (!(stunned))
            {

                do
                {

                //cout << "**Calling Function: " << "inptcommand" << " Line 83 " << endl;
                usrinp= inptcommand();
                //cout << "**Function: " << "inptcommand returned: " << usrinp << " Line 83 " << endl;

                //cout << "**Calling Function: " << "validmenu" << " Line 87 " << endl;
                menunum=validmenu(menu,usrinp);
                //cout << "**Function: " << "validmenu returned: " << menunum << " Line 87 " << endl;

                if (menunum == -1)
                    {
                        cout << "Invalid command, please try again.." << endl;
                        Sleep(200);                // seconds

                    }


            } while (menunum==-1);

            //cout << "**Calling Function: " << "menuexec" << " Line 98 " << endl;
            menupass = menuexec(menunum);
            //cout << "**Function: " << "menuexec returned: " << menupass << " Line 98 " << endl;

            //cout << "**Calling Function: " << "populatekatz" << " Line 120 " << endl;
            populatekatz();

            //cout << "**Calling Function: " << "currentloc" << " Line 103 " << endl;
            currentloc(grid,occp,curlongt,curlat);




            //cout << "**Calling Function: " << "display" << " Line 106 " << endl;
            display(grid);

            //cout << "**Calling Function: " << "huddisplay" << " Line 109 " << endl;
            huddisplay();


            //cout << "Longt: " << curlongt <<" lat: " << curlat <<  endl;
            //cout << "**If menupass is true add 1 to " << "moves" << " Line 113 " << endl;
            if (menupass)
                {
                    //cout << "**menupass is true add 1 to " << "moves" << " Line 116 " << endl;
                    moves++;

                    //cout << "**If moves is 2 reset to 0 " << " Line 119 " << endl;
                    if (moves==2)
                    {
                       // cout << "**moves is 2 add 1 to \"turn\" and run functions for Katz" << " Line 131 " << endl;
                    turn++;
                         //cout << "**moves is 2 reset to 0 " << " Line 119 " << endl;
                         moves =0;
                    }
                }
            cout << "Move " << moves << "/2" << endl ;
            Sleep(200);
            }
            else
                {
                    cout << "You are unable to move this turn!";
                    Sleep(200);
                    stunned=0;

                }
            //cout << "**If moves is 0 then add 1 to \"turn\" and run functions for Katz " << " Line 128 " << endl;
             if (menupass) {if ((moves % 2 == 0)&&(turn!=0))
                {

                    cout << setw(30)<< right << "End of Turn" << endl;
                    Sleep(500);
                    cout << setw(30)<< right << "Cats TURN!!!" << endl;
                    Sleep(500);

                    //cout << "**Calling Function: " << "cankatattckpur" << " Line 136 " << endl;
                    cankatattckpur();

                    //cout << "**Calling Function: " << "katattckpur" << " Line 136 " << endl;
                    //katattckpur();

                    //cout << "**Calling Function: " << "randkatmov" << " Line 139 " << endl;
                    randkatmov();

                    //cout << "**Calling Function: " << "populatekatz" << " Line 139 " << endl;
                    populatekatz();

                    //cout << "**Calling Function: " << "currentloc" << " Line 103 " << endl;
                    currentloc(grid,occp,curlongt,curlat);

                    //cout << "**Calling Function: " << "cankatattckpur" << " Line 139 " << endl;
                    //cankatattckpur();

                    //cout << "**Calling Function: " << "display" << " Line 139 " << endl;
                    display(grid);

                    //cout << "**Calling Function: " << "huddisplay" << " Line 139 " << endl;
                    huddisplay();
                    cout << "Move " << moves << "/2" << endl ;

                    ;}
                }
            cout << "Turn "<< turn << endl;
            cout << "Command:";

            if (curhealth<=0)
                dead=1;
        } while (dead != 1);
        cout << "The Katz have taken all the Tuna!!!!!" << endl;
        Sleep(1500);
        cout << "You must now go to the store and get more Tuna!!!!!" << endl;
        Sleep(1500);
        cout << "Once you return you find your house is no longer your own..." << endl;
        Sleep(1500);
        cout << "You know the katz must go but are unable to break out of their spell" << endl;
        Sleep(1500);
        cout << "It has now been 10 years since the kat takeover, you have no money, and no life" << endl;
        Sleep(1500);
        cout << "GAME OVER!" << endl;
        Sleep(1500);

    return 0;
}

void initgrid (char grd [maxlongt][maxlat])
{
    //cout << "**Function: " << "initgrid" << " Line 139 " << endl;
    int row = 0;
    int col = 0;

    for (row = 0; row <= maxlongt; row++)
    {
        //cout << "**Function: " << "initgrid" << "For loop row: " << row << " Line 139 " << endl;
        for (col = 0; col <= maxlat; col++)
        {
            //cout << "**Function: " << "initgrid" << "For loop col: " << col << " Line 139 " << endl;

            grid[row][col] = '-';
        }
    }

    //***Extra credit: build homes
    grid[3][2] = 201;
    grid[3][3] = 187;
    grid[2][2] = 200;
    grid[2][3] = 188;

    grid[3][16] = 201;
    grid[3][17] = 187;
    grid[2][16] = 200;
    grid[2][17] = 188;

    grid[17][16] = 201;
    grid[17][17] = 187;
    grid[16][16] = 200;
    grid[16][17] = 188;

    grid[17][2] = 201;
    grid[17][3] = 187;
    grid[16][2] = 200;
    grid[16][3] = 188;
}

void currentloc(char grd [maxlongt][maxlat],int ocp [maxlongt][maxlat],int curlongt, int curlat)
{
    //cout << "**Function: " << " currentloc " << "updating grid to " << "long:"<< curlongt << " lat:" << curlat << " Line 139 " << endl;
    grid[curlongt][curlat] = '@';
    ocp[curlongt][curlat] = '1';
}

void priorloc(char grd [maxlongt][maxlat],int nonocp [maxlongt][maxlat],int curlongt, int curlat)
{
    //cout << "**Function: " << " priorloc " << "remove current position from grid " << "long:"<< curlongt << " lat:" << curlat << " Line 139 " << endl;
    grid[curlongt][curlat] = '-';
    nonocp[curlongt][curlat] = '-';
}

void occupiedloc (char grid [maxlongt][maxlat],int curl, int curla, int katnum)
{
    char kat = '0';
    //cout << "**Function: " << " occupiedloc " << "updates grid with kat position " << "long:"<< curl << " lat:" << curla << " Line 139 " << endl;
    //Code below is for debug only
    //if (katnum == 0)
    //    kat='0';
    //else if (katnum == 1)
    //    kat='1';
    //else if (katnum == 2)
    //    kat='2';
    //else if (katnum == 3)
    //    kat='3';
    //else if (katnum == 4)
    //    kat='4';
    //else if (katnum == 5)
    //    kat='5';
    //else if (katnum == 6)
    //    kat='6';
    //else if (katnum == 7)
    //    kat='7';
    //else if (katnum == 8)
    //    kat='8';
    //else if (katnum == 9)
    //    kat='9';


        kat = 2;

    grid[curl][curla] = kat;

     if (smart==1 && katnum > 4)
    {
        kat= 1;
        grid[curl][curla] = kat;
    }


}

//void freeloc (char ocp [maxlongt][maxlat],int curlongt, int curlat)
//{
//   grid[curlongt][curlat] = '-';


//}

void display (char grd [maxlongt][maxlat])
{
    //cout << "**Function: " << " display " << "shows grid on screen using for loop " << " Line 139 " << endl;

    int row = 0;
    int col = 0;

    for (row = maxlongt-1; row > 0; row--)
    {
        //cout << row;
        for (col = 1; col < maxlat; col++)
        {

            cout << grid[row][col] << " " ;

        }
         cout << endl;
         Sleep(5);
         }
}

int validmenu(const char menu[maxmenu],char usrinp)
{
    //cout << "**Function: " << " validmenu " << "uses linear search on menu array for user input " << " Line 139 " << endl;

    char test = tolower(usrinp);

    int index = 0; // Used as a subscript to search array
    int position = -1; // To record position of search value
    bool found = false; // Flag to indicate if the value was found
    while (index < maxmenu && !found)
    {
        if (menu[index] == test) // If the value is found
        {
            found = true; // Set the flag
            //cout << "found" << endl;
            position = index; // Record the value's subscript
        }
        index++;
    }
    return position; // Return the position, or −1
}

bool menuexec(int comd)
{
    //cout << "**Function: " << " menuexec " << "uses a switch to execute user command " << " Line 139 " << endl;
    switch (comd)
    {
        case 0 : {//cout << "**Function: " << " menuexec " << "executing 0" << endl;
                    if (glasses == 0)
                    {
                        //cout << "**Function: " << " menuexec " << "executing 0 " << "glasses are off putting them on " << endl;
                        glasses = 1;
                        cout << "You put on your highly Reflective Glasses!!" << endl;
                        Sleep(500);
                    }
                    else
                        {
                            //cout << "**Function: " << " menuexec " << "executing 0 " << "glasses are on taking them off " << endl;
                            glasses = 0;
                        cout << "You start to think your glasses are attracting katz and take them off " << endl;
                        Sleep(500);
                        }
                     return true;
                     break;
                 }

        case 1 : {//cout << "**Function: " << " menuexec " << "executing 1 " << endl;
                    //cout << "**Function: " << " menuexec " << "executing 1 " << "calling function: " << "charmovetest" << endl;
                    if (charmovetest(1))
                        {
                            //cout << "**Function: " << " menuexec " << "executing 1 "<< "function " << "charmovetest " <<  "passed " << "calling function: " << "occptest" << endl;
                            if (occptest(1))
                            {
                                //cout << "**Function: " << " menuexec " << "executing 1 "<< "function " << "occptest " <<  "passed " << "calling function: " << "charmov" << endl;
                                charmov(1);
                            }
                        }
                    else
                        {
                            cout << "Cannot move in that direction" << endl;
                            Sleep(500);
                            return false;
                        }
                            break;
                 }

        case 2 : {//cout << "**Function: " << " menuexec " << "executing 2" << endl;
                    //cout << "**Function: " << " menuexec " << "executing 2 " << "calling function: " << "charmovetest" << endl;
                    if (charmovetest(2))
                        {
                             //cout << "**Function: " << " menuexec " << "executing 2 "<< "function " << "charmovetest " <<  "passed " << "calling function: " << "occptest" << endl;
                            if (occptest(2))
                                {
                                    //cout << "**Function: " << " menuexec " << "executing 2 "<< "function " << "occptest " <<  "passed " << "calling function: " << "charmov" << endl;
                                charmov(2);
                                }
                        }
                    else {cout << "Cannot move in that direction" << endl;
                    Sleep(500);
                        return false;}
                    break;
                  }



        case 3 : {//cout << "**Function: " << " menuexec " << "executing 3" << endl;
                    //cout << "**Function: " << " menuexec " << "executing 3 " << "calling function: " << "charmovetest" << endl;
                     if (charmovetest(3))
                        {
                             //cout << "**Function: " << " menuexec " << "executing 3 "<< "function " << "charmovetest " <<  "passed " << "calling function: " << "occptest" << endl;
                            if (occptest(3))
                                {
                                    //cout << "**Function: " << " menuexec " << "executing 3 "<< "function " << "occptest " <<  "passed " << "calling function: " << "charmov" << endl;
                                charmov(3);
                                }
                            }
                    else {cout << "Cannot move in that direction" << endl;
                    Sleep(500);
                            return false;
                        }
                        break;}

        case 4 : {//cout << "**Function: " << " menuexec " << "executing 4" << endl;
                    //cout << "**Function: " << " menuexec " << "executing 4 " << "calling function: " << "charmovetest" << endl;
                     if (charmovetest(4))
                        {
                             //cout << "**Function: " << " menuexec " << "executing 4 "<< "function " << "charmovetest " <<  "passed " << "calling function: " << "occptest" << endl;
                            if (occptest(4))
                                {
                                    //cout << "**Function: " << " menuexec " << "executing 4 "<< "function " << "occptest " <<  "passed " << "calling function: " << "charmov" << endl;
                                charmov(4);
                                }
                            }
                    else {cout << "Cannot move in that direction" << endl;
                    Sleep(500);
                            return false;
                        }
                        break;}
        case 5 : {//cout << "**Function: " << " menuexec " << "executing 5" << endl;
                    capture = cankatcapture();
                    if ((!(capture ==-1)))
                         {
                             katcapture(capture);
                         }
                     else {cout << "There are no Katz nearby" << endl;
                        Sleep(500);
                            return false;
                    }
                break;}

        case 6 : {//cout << "**Function: " << " menuexec " << "executing 6" << endl;
                    //cout << "**Function: " << " menuexec " << "executing 6 " << "calling function: " << "charmovetest" << endl;
                     if (charmovetest(6))
                        {
                             //cout << "**Function: " << " menuexec " << "executing 6 "<< "function " << "charmovetest " <<  "passed " << "calling function: " << "occptest" << endl;
                            if (occptest(6))
                                {
                                    //cout << "**Function: " << " menuexec " << "executing 6 "<< "function " << "occptest " <<  "passed " << "calling function: " << "charmov" << endl;
                                charmov(6);
                                }
                            }
                    else {cout << "Cannot move in that direction" << endl;
                    Sleep(500);
                            return false;
                        }
                        break;}
        case 7 : {//cout << "**Function: " << " menuexec " << "executing 7" << endl;
                    //cout << "**Function: " << " menuexec " << "executing 7 " << "calling function: " << "charmovetest" << endl;
                     if (charmovetest(7))
                        {
                             //cout << "**Function: " << " menuexec " << "executing 7 "<< "function " << "charmovetest " <<  "passed " << "calling function: " << "occptest" << endl;
                            if (occptest(7))
                                {
                                    //cout << "**Function: " << " menuexec " << "executing 7 "<< "function " << "occptest " <<  "passed " << "calling function: " << "charmov" << endl;
                                charmov(7);
                                }
                            }
                    else {cout << "Cannot move in that direction" << endl;
                    Sleep(500);
                            return false;
                        }
                        break;}
        case 8 : {//cout << "**Function: " << " menuexec " << "executing 8" << endl;
                    //cout << "**Function: " << " menuexec " << "executing 8 " << "calling function: " << "charmovetest" << endl;
                     if (charmovetest(8))
                        {
                             //cout << "**Function: " << " menuexec " << "executing 8 "<< "function " << "charmovetest " <<  "passed " << "calling function: " << "occptest" << endl;
                            if (occptest(8))
                                {
                                    //cout << "**Function: " << " menuexec " << "executing 8 "<< "function " << "occptest " <<  "passed " << "calling function: " << "charmov" << endl;
                                charmov(8);
                                }
                            }
                    else {cout << "Cannot move in that direction" << endl;
                    Sleep(500);
                            return false;
                        }
                        break;}
        case 9 : {//cout << "**Function: " << " menuexec " << "executing 9" << endl;
                    //cout << "**Function: " << " menuexec " << "executing 9 " << "calling function: " << "charmovetest" << endl;
                     if (charmovetest(9))
                        {
                             //cout << "**Function: " << " menuexec " << "executing 9 "<< "function " << "charmovetest " <<  "passed " << "calling function: " << "occptest" << endl;
                            if (occptest(9))
                                {
                                    //cout << "**Function: " << " menuexec " << "executing 9 "<< "function " << "occptest " <<  "passed " << "calling function: " << "charmov" << endl;
                                charmov(9);
                                }
                            }
                    else {cout << "Cannot move in that direction" << endl;
                    Sleep(500);
                            return false;
                        }
                        break;}
        case 10 : {//cout << "**Function: " << " menuexec " << "executing 10"<< endl;
             if (earmuff == 0) {
                    earmuff = 1;
                    cout << "These katz are creeping you out.." << endl;
                     Sleep(1000);
                    cout << "You put on your Earmuff's of Happiness and everything seems much better" << endl;
                     Sleep(1500);
                    }
                    else earmuff = 0; return true;
                    break;}

        case 11 : {cout << "Thanks for playing!!!"<< endl;
                    Sleep(500);
                    exit(0); break;}

        case 12 : cout << "executing 12"; break;

        case 13 : cout << "executing 13"; break;
    }


}

char inptcommand()
{
    //cout << "**Function: " << " inptcommand " << "gets a char from the user " << " Line 139 " << endl;

    char inpt;
    cin >> inpt;
    return inpt;

}

bool charmovetest(int dir)
{
    //cout << "**Function: " << " charmovetest " << "tests if the character can move in a specified direction using a switch" << " Line 139 " << endl;

    int top = 18;
    int bottom = 1;
    switch (dir)
    {
        case 0 : {//cout << "**Function: " << " charmovetest " << "executing 0" << endl;
                    break;}
        case 1 : {//cout << "**Function: " << " charmovetest " << "testing 1" << " sw " << endl;
                    if (curlat == bottom || curlongt == bottom)
                        return false;
                    break;}
        case 2 : {//cout << "**Function: " << " charmovetest " << "testing 2" << " s " << endl;
                    if (curlongt ==bottom  )
                        return false;
                        break;}
        case 3 : {//cout << "**Function: " << " charmovetest " << "testing 3" << " se " << endl;
                    if (curlat == top || curlongt == bottom )
                        return false;
                        break;}
        case 4 : {//cout << "**Function: " << " charmovetest " << "testing 4" << " w " << endl;
                    if (curlat == bottom)
                        return false;
                        break;}
        case 5 : {//cout << "**Function: " << " charmovetest " << "executing 5";
                    break;}
        case 6 : {//cout << "**Function: " << " charmovetest " << "testing 6" << " e " << endl;
                    if (curlat == top)
                        return false;
                        break;}
        case 7 : {//cout << "**Function: " << " charmovetest " << "testing 7" << " nw " << endl;
                    if (curlat == bottom || curlongt == top )
                        return false;
                        break;}
        case 8 : {//cout << "**Function: " << " charmovetest " << "testing 8" << " n " << endl;
                    if (curlongt == top )
                        return false;
                        break;}
        case 9 : {//cout << "**Function: " << " charmovetest " << "testing 9" << " ne " <<endl;
                    if (curlat == top || curlongt == top)
                        { return false;}
                    else {return true;}
                        break;}
        case 10 : cout << "executing 10"; break;
        case 11 : cout << "executing 11"; break;
        case 12 : cout << "executing 12"; break;
        case 13 : cout << "executing 13"; break;
    }



}

void charmov(int dir)
{
    //cout << "**Function: " << " charmov " << "calls function priorloc then updates curlongt and curlat to new location" << " Line 139 " << endl;

    //cout << "**Function: " << " charmov " << "calling function priorloc" << endl;
    priorloc(grid,occp,curlongt,curlat);

    //cout << "**Function: " << " charmov " << "updating char location using switch" << endl;
    switch (dir)
    {
        case 0 : {//cout << "**Function: " << " charmov "  << "executing 0";
                    break;}
        case 1 : {//cout << "**Function: " << " charmov "  << "moving 1" << " sw" << endl;
                    curlat-=1;curlongt-=1;
                    break;}
        case 2 : {//cout << "**Function: " << " charmov "  << "moving 2" << " s" << endl;
                    curlongt-=1;
                    break;}
        case 3 : {//cout << "**Function: " << " charmov "  << "moving 3" << " se" << endl;
                    curlat+=1;curlongt-=1;
                    break;}
        case 4 : {//cout << "**Function: " << " charmov "  << "moving 4" << " w" << endl;
                    curlat-=1;
                    break;}
        case 5 : {//cout << "**Function: " << " charmov "  << "executing 5";
                    break;}
        case 6 : {//cout << "**Function: " << " charmov "  << "moving 6" << " e" << endl;
                    curlat+=1;
                    break;}
        case 7 : {//cout << "**Function: " << " charmov "  << "moving 7" << " nw" << endl;
                    curlat-=1;curlongt+=1;
                    break;}
        case 8 : {//cout << "**Function: " << " charmov "  << "moving 8" << " n" << endl;
                    curlongt+=1;
                    break;}
        case 9 : {//cout << "**Function: " << " charmov "  << "moving 9" << " ne" << endl;
                    curlat+=1;curlongt+=1;
                    break;}
        case 10 : cout << "executing 10"; break;
        case 11 : cout << "executing 11"; break;
        case 12 : cout << "executing 12"; break;
        case 13 : cout << "executing 13"; break;
    }



}

void huddisplay()
{
    //cout << "**Function: " << " huddisplay " << "displays user status" << " Line 139 " << endl;

    cout << "Tuna Health: " << curhealth << "/" << maxhealth << " Cans " << endl ;
    cout << "RF Glasses: ";
    if (glasses == 0)
        cout << "off ";
        else
        cout << "ON ";
    cout << endl;
    cout << "Earmuffs of Happiness: ";
    if (earmuff == 0)
        cout << "off ";
        else
        cout << "ON ";
    cout << endl;
    //cout << "Longt: " << curlongt <<" lat: " << curlat <<  endl;

}

void randkatloc(int num)
{
//    cout << "**Function: " << " randkatloc " << "users srand to generate random locations for katz" << " Line 139 " << endl;

    int count1 = 0;
    const int MIN_VALUE = 4;
    const int MAX_VALUE = 15;
    static int seeded =0;
    int sd = (seeded * 30);

    // Seed the random number generator by passing
    // the return value of time(0) to srand.
    unsigned seed = (time(0));
    srand(seed);

    // Populate the array with random numbers.
    for (int count = 0; count < 5; count++)
       {
           for (count1 = 0; count1 < 2; count1++)
           {
               stpkatz[count][count1] = ((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);
               //cout << "**Function: " << " randkatloc " << " Stupid Kat: " << count  << "longt/lat: " << count1 << " location: " <<  stpkatz[count][count1] << endl;
           }
       }
    for (int count = 0; count < 5; count++)
       {
           for (count1 = 0; count1 < 2; count1++)
           {

               smartkatz[count][count1] = ((rand() % (MAX_VALUE - MIN_VALUE + 0)) + MIN_VALUE);
               //cout << "**Function: " << " randkatloc " << "Smart Kat: " << count  << "longt/lat: " << count1 << " location: " <<  smartkatz[count][count1] << endl;
           }
       }
 seeded++;
}

void populatekatz()
{
    //cout << "**Function: " << " populatekatz " << "updates location of katz on grid array" << " Line 139 " << endl;

     for (int count = 0; count < 5; count++)
     {
         if (stpkatdead[count][0]==0)
            {
         occupiedloc(grid,stpkatz[count][0], stpkatz[count][1],count);

            }
            else
                {
                    //cout << "Stupid Kat: " << count << " is captured" << endl;
                        int lat = stpkatz[count][1];
                        int longt = stpkatz[count][0];

                        priorloc(grid,occp,longt,lat);
                }
     }
     for (int count = 0; count < 5; count++)
     {
         if (smartkatdead[count][0]==0)
            {
         occupiedloc(grid,smartkatz[count][0], smartkatz[count][1],(count+5));

            }
            else
                {
                    //cout << "Smart Kat: " << count << " is captured" << endl;
                        int lat = smartkatz[count][1];
                        int longt = smartkatz[count][0];

                        priorloc(grid,occp,longt,lat);
                }
     }

}

bool occptest(int dir)
{
    //cout << "**Function: " << " occptest " << "tests to see if there is something in a grid for user only" << " Line 139 " << endl;

    int lat = 0;
    int longt = 0;
    char test = '0';
    char test1='-';
    switch (dir)
    {
        case 0 : {//cout << "**Function: " << " occptest "  << "executing 0";
                    break;}
        case 1 : {//cout << "**Function: " << " occptest " << "ocptesting 1" << " sw" << endl;
                    lat=curlat-1;longt=curlongt-1;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1)
                        {cout << "Cannot move in that direction, " << "something is there. " << endl;
                        Sleep( 500 );
                        return false;}
                    break;}
        case 2 : {//cout << "**Function: " << " occptest " << "ocptesting 2" << " s" << endl;
                    lat=curlat;longt= curlongt-1;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1)
                        {cout << "Cannot move in that direction, " << "something is there. " << endl;
                        Sleep( 500 );
                        return false;}
                    break;}
        case 3 : {//cout << "**Function: " << " occptest " << "ocptesting 3" << " se" << endl;
                    lat=curlat+1;longt=curlongt-1;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1)
                        {cout << "Cannot move in that direction, " << "something is there. " << endl;
                        Sleep( 500 );
                        return false;}
                    break;}
        case 4 : {//cout << "**Function: " << " occptest " << "ocptesting 4" << " w" << endl;
                    lat=curlat-1;longt=curlongt;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1)
                        {cout << "Cannot move in that direction, " << "something is there. " << endl;
                        Sleep( 500 );
                        return false;}
                    break;}
        case 5 : {//cout << "**Function: " << " occptest " << "executing 5";
                    break;}
        case 6 : {//cout << "**Function: " << " occptest " << "ocptesting 6" << " e" << endl;
                    lat=curlat+1;longt=curlongt;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1)
                        {cout << "Cannot move in that direction, " << "something is there. " << endl;
                        Sleep( 500 );
                        return false;}
                    break;}
        case 7 : {//cout << "**Function: " << " occptest " << "ocptesting 7" << " nw" << endl;
                    lat=curlat-1;longt=curlongt+1;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1)
                        {cout << "Cannot move in that direction, " << "something is there. " << endl;
                        Sleep( 500 );
                        return false;}
                    break;}
        case 8 : {//cout << "**Function: " << " occptest " << "ocptesting 8" << " n" << endl;
                    lat=curlat;longt=curlongt+1;test=grid[longt][lat];
                    //cout << test << " " << longt << " " << lat  << endl;
                    if (test!=test1)
                        {cout << "Cannot move in that direction, " << "something is there. " << endl;
                        Sleep( 500 );
                        return false;}
                    break;}
        case 9 : {//cout << "**Function: " << " occptest " << "ocptesting 9" << " ne" << endl;
                    lat=curlat+1;longt=curlongt+1;test=grid[longt][lat];
                    //cout << test << " " << longt << " " << lat << endl;
                    if (test!=test1)
                        {cout << "Cannot move in that direction, " << "something is there. " << endl;
                        Sleep( 500 );
                        return false;}
                    break;}
        case 10 : {cout << "executing 10";
                    break;}
        case 11 : {cout << "executing 11";
                    break;}
        case 12 : {cout << "executing 12";
                    break;}
        case 13 : {cout << "executing 13";
                    break;}
    }
}

void cankatattckpur()
{
    //cout << "**Function: " << " cankatattckpur " << "tests to see if a stupid kat is close enough to do a purr attack" << " Line 139 " << endl;

    int difrnlong =0;
    int difrnlat = 0;
    int absltdifflong =0;
    int absltdifflat =0;

    for (int count = 0; count < 5; count++)
       {
           difrnlong =stpkatz[count][0] - curlongt;
           difrnlat= stpkatz[count][1] - curlat;
           //cout << "**Function: " << " cankatattckpur "  << "kat: " << count << " longt:" << stpkatz[count][0] << " lat:" << stpkatz [count][1] << endl;
           absltdifflong=abs(difrnlong);
           absltdifflat=abs(difrnlat);
           if (absltdifflong== 2)
                {

                    //cout << "**Function: " << " cankatattckpur "  << "if absltdifflong ==2 " << absltdifflong << endl;
                    stpkatattck[count][0]=0;
                    //cout << "**Function: " << " cankatattckpur "  << " if (absltdifflong== 2) kat " << count << " attack set to " << stpkatattck[count][0] << endl;
                    if (absltdifflat== 2)
                        {
                        stpkatattck[count][0]=1;
                        //cout << "**Function: " << " cankatattckpur "  << " if (absltdifflat== 2) kat " << count << " attack set to " << stpkatattck[count][0] << endl;
                        }
                    else if (absltdifflat== 0)
                        {
                            //cout << "**Function: " << " cankatattckpur "  << "else if (absltdifflat== 0) absltdifflat " << absltdifflat << endl;
                            stpkatattck[count][0]=1;
                           // cout << "**Function: " << " cankatattckpur "  << "else if (absltdifflat== 0) Kat " << count << " attack set to " << stpkatattck[count][0] << endl;
                           }
                        }
            else if (absltdifflong== 0)
                {
                    //cout << "**Function: " << " cankatattckpur "  << "if (absltdifflong== 0) Kat " << count << endl;
                    stpkatattck[count][0]=0;
                    //cout << "**Function: " << " cankatattckpur "  << "if (absltdifflong== 0) Kat " << count << " attack set to " << stpkatattck[count][0] << endl;

                    if (absltdifflat== 2)
                        {stpkatattck[count][0]=1;
                        //cout << "**Function: " << " cankatattckpur "  << "if (absltdifflat== 2) Kat " << count << " attack set to " << stpkatattck[count][0] << endl;
                        }
                }
            else
                {
                //cout << "**Function: " << " cankatattckpur "  << "kat:" << count << "{stpkatattck[count][0]=0;" << endl;
                stpkatattck[count][0]=0;
                //cout << "**Function: " << " cankatattckpur "  << "longt distance" << absltdifflong << endl;
                //cout << "**Function: " << " cankatattckpur "  << "lat distance" << absltdifflat << endl;
                stpkatattck[count][0]=0;
                }

       }
       //check to see if kat can attack using eye of submission
       for (int count = 0; count < 5; count++)
       {
           difrnlong =stpkatz[count][0] - curlongt;
           difrnlat= stpkatz[count][1] - curlat;
           //cout << "**Function: " << " cankatattckpur " << " eye "  << "kat: " << count << " longt:" << stpkatz[count][0] << " lat:" << stpkatz [count][1] << endl;
           absltdifflong=abs(difrnlong);
           absltdifflat=abs(difrnlat);
           if (absltdifflong== 1)
                {

                    //cout << "**Function: " << " cankatattckpur " << " eye "  << "if absltdifflong ==1 " << absltdifflong << endl;
                    stpkatateye[count][0]=0;
                    //cout << "**Function: " << " cankatattckpur " << " eye "  << " if (absltdifflong== 1) kat " << count << " attack set to " << stpkatateye[count][0] << endl;
                    if (absltdifflat== 1)
                        {stpkatateye[count][0]=1;
                        //cout << "**Function: " << " cankatattckpur " << " eye "  << " if (absltdifflat== 1) kat " << count << " attack set to " << stpkatateye[count][0] << endl;
                        }
                    else if (absltdifflat== 0)
                        {
                            //cout << "**Function: " << " cankatattckpur " << " eye "  << "else if (absltdifflat== 0) absltdifflat " << absltdifflat << endl;
                            stpkatateye[count][0]=1;
                           // cout << "**Function: " << " cankatattckpur " << " eye "  << "else if (absltdifflat== 0) Kat " << count << " attack set to " << stpkatateye[count][0] << endl;
                           }
                }
            else if (absltdifflong== 0)
                {
                   // cout << "**Function: " << " cankatattckpur " << " eye "  << "if (absltdifflong== 0) Kat " << count << endl;
                    stpkatateye[count][0]=0;
                    //cout << "**Function: " << " cankatattckpur "  << " eye " << "if (absltdifflong== 0) Kat " << count << " attack set to " << stpkatateye[count][0] << endl;

                    if (absltdifflat== 1)
                        {stpkatateye[count][0]=1;
                        //cout << "**Function: " << " cankatattckpur " << " eye "  << "if (absltdifflat== 1) Kat " << count << " attack set to " << stpkatateye[count][0] << endl;
                        }
                }
            else
                {
                //cout << "**Function: " << " cankatattckpur " << " eye "   << "kat:" << count << "{stpkatateye[count][0]=0;" << endl;
                stpkatateye[count][0]=0;
                //cout << "**Function: " << " cankatattckpur " << " eye "   << "longt distance" << absltdifflong << endl;
                //cout << "**Function: " << " cankatattckpur " << " eye "  << "lat distance" << absltdifflat << endl;
                stpkatateye[count][0]=0;
                }

       }
       for (int count = 0; count < 5; count++)
       {
           difrnlong =smartkatz[count][0] - curlongt;
           difrnlat= smartkatz[count][1] - curlat;
           //cout << "**Function: " << " cankatattckpur " << " eye "  << "Smart kat: " << count << " longt:" << smartkatz[count][0] << " lat:" << smartkatz [count][1] << endl;
           absltdifflong=abs(difrnlong);
           absltdifflat=abs(difrnlat);
           if (absltdifflong== 1)
                {

                    //cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count   << "if absltdifflong ==1 " << absltdifflong << endl;
                    smartkatateye[count][0]=0;
                   // cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count     << " if (absltdifflong== 1) kat " << count << " attack set to " << smartkatateye[count][0] << endl;
                    if (absltdifflat== 1)
                        {smartkatateye[count][0]=1;
                        //cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count     << " if (absltdifflat== 1) kat " << count << " attack set to " << smartkatateye[count][0] << endl;
                        }
                    else if (absltdifflat== 0)
                        {
                            //cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count     << "else if (absltdifflat== 0) absltdifflat " << absltdifflat << endl;
                            smartkatateye[count][0]=1;
                            //cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count     << "else if (absltdifflat== 0) Kat " << count << " attack set to " << smartkatateye[count][0] << endl;
                           }
                }
            else if (absltdifflong== 0)
                {
                   //cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count     << "if (absltdifflong== 0) Kat " << count << endl;
                    smartkatateye[count][0]=0;
                    //cout << "**Function: " << " cankatattckpur "  << " eye " << "Smart kat: " << count    << "if (absltdifflong== 0) Kat " << count << " attack set to " << smartkatateye[count][0] << endl;

                    if (absltdifflat== 1)
                        {smartkatateye[count][0]=1;
                        //cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count     << "if (absltdifflat== 1) Kat " << count << " attack set to " << smartkatateye[count][0] << endl;
                        }
                }
            else
                {
                //cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count   << "{smartkatateye[count][0]=0;" << endl;
                smartkatateye[count][0]=0;
               // cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count      << "longt distance" << absltdifflong << endl;
               // cout << "**Function: " << " cankatattckpur " << " eye " << "Smart kat: " << count     << "lat distance" << absltdifflat << endl;
                smartkatateye[count][0]=0;
                }

       }
}

void katattckpur()
{
    //cout << "**Function: " << " katattckpur " << "executes attacks from cats who can attack" << " Line 139 " << endl;

    for (int count = 0; count < 5; count++)
    {
        if (stpkatdead[count][0]==0)
        {
        //cout << "**Function: " << " katattckpur " << "For loop count:" << count << endl;
        //cout << "**Function: " << " katattckpur flag is:"  << stpkatattck[count][0] <<  endl;
        if (stpkatattck[count][0]==1)
        {
            purrtest();
            purrtest();

            //cout << "**Function: " << " katattckpur "  << count << " " << "can attack!" << endl;
            stpkatzmv[count][0] = 10;
            stpkatzmv[count][1] = 10;
        }
        }
        else
            {
                //cout << "Kat: " << count << "is captured" << endl;

           }

    }
}

void randkatmov()
{
    //cout << "**Function: " << " randkatmov " << "uses srand to generate moves for katz" << " Line 139 " << endl;

    int count1 = 0;
    const int MIN_VALUE = 1;
    const int MAX_VALUE = 9;
    static int seededmov =0;
    int sd = (seededmov * 30);
    static int playstupid = 0;


    // Seed the random number generator by passing
    // the return value of time(0) to srand.
    unsigned seed = time(0)*sd;
    srand(seed);



    //cout << "**Function: " << " randkatmov " << "Populate the array stpkatzmv with random commands." << " Line 139 " << endl;
    for (int count = 0; count < 5; count++)
       {
           if (stpkatdead[count][0]==0)
           {
           for (count1 = 0; count1 < 2; count1++)
           {

               stpkatzmv[count][0] = ((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);
               seededmov++;

               if (stpkatzmv[count][0] == 5)
               stpkatzmv[count][0] = ((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);seededmov++;

               stpkatzmv[count][1] = ((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);seededmov++;
               if (stpkatzmv[count][1] == 5)
               stpkatzmv[count][1] = ((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);seededmov++;
            }
           }
           else
            {
                //cout << "Kat: " << count << "is captured" << endl;

           }
       }
//  cout << "**Function: " << " randkatmov " << "Populate the array smartkatzmv with  commands." << " Line 139 " << endl;
    playstupid= ((rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE);
    if (playstupid % 3 != 0)
    {
    cout << "Some of the Katz seem to be plotting something..." << endl ;
    Sleep(1000);
    cout << "It seems like some of these katz might be smarter than the others ..." << endl;
    Sleep(2500);
    cout << "They want your TUNA!!!" << endl;
    Sleep(1500);
    smart=1;

    for (int count = 0; count < 5; count++)
       {
           if (smartkatdead[count][0]==0 && smart==1)
           {
           for (count1 = 0; count1 < 2; count1++)
           {
               if ((smartkatz[count][0] > curlongt)&& ((smartkatz[count][1]>curlat)))
               {
                   smartkatzmv[count][count1]=1;
                   //cout << "**Function: " << " randkatmov " << "smartkatzmv[count][0]= " <<smartkatzmv[count][count1] << " Smart Kat: " << count << " Move: " << count1 << " Line 139 " << endl;

               }
               else if ((smartkatz[count][0] < curlongt)&& ((smartkatz[count][1]<curlat)))
                        {

                   smartkatzmv[count][count1]=9;
                    //cout << "**Function: " << " randkatmov " << "smartkatzmv[count][0]= " <<smartkatzmv[count][count1] << " Smart Kat: " << count << " Move: " << count1 << " Line 139 " << endl;

                        }
                else if ((smartkatz[count][0] > curlongt)&& ((smartkatz[count][1]<curlat)))
                        {

                   smartkatzmv[count][count1]=3;
                   // cout << "**Function: " << " randkatmov " << "smartkatzmv[count][0]= " <<smartkatzmv[count][count1] << " Smart Kat: " << count << " Move: " << count1 << " Line 139 " << endl;

                        }
                else if ((smartkatz[count][0] < curlongt)&& ((smartkatz[count][1]>curlat)))
                        {

                   smartkatzmv[count][count1]=7;
                   // cout << "**Function: " << " randkatmov " << "smartkatzmv[count][0]= " <<smartkatzmv[count][count1] << " Smart Kat: " << count << " Move: " << count1 << " Line 139 " << endl;

                        }
                else if ((smartkatz[count][0] < curlongt)&& ((smartkatz[count][1]==curlat)))
                        {

                   smartkatzmv[count][count1]=8;
                    //cout << "**Function: " << " randkatmov " << "smartkatzmv[count][0]= " <<smartkatzmv[count][count1] << " Smart Kat: " << count << " Move: " << count1 << " Line 139 " << endl;

                        }
                else if ((smartkatz[count][0] > curlongt)&& ((smartkatz[count][1]==curlat)))
                        {

                   smartkatzmv[count][count1]=2;
                   // cout << "**Function: " << " randkatmov " << "smartkatzmv[count][0]= " <<smartkatzmv[count][count1] << " Smart Kat: " << count << " Move: " << count1 << " Line 139 " << endl;

                        }
                else if ((smartkatz[count][0] == curlongt)&& ((smartkatz[count][1]<curlat)))
                        {

                   smartkatzmv[count][count1]=6;
                   // cout << "**Function: " << " randkatmov " << "smartkatzmv[count][0]= " <<smartkatzmv[count][count1] << " Smart Kat: " << count << " Move: " << count1 << " Line 139 " << endl;

                        }
                else if ((smartkatz[count][0] == curlongt)&& ((smartkatz[count][1]>curlat)))
                        {

                   smartkatzmv[count][count1]=4;
                  // cout << "**Function: " << " randkatmov " << "smartkatzmv[count][0]= " <<smartkatzmv[count][count1] << " Smart Kat: " << count << " Move: " << count1 << " Line 139 " << endl;


                        }
           }
           }
           else
            {
                //cout << "Kat: " << count << "is captured" << endl;

           }
       }
    }
    else
    {
        cout << "You suddenly can't tell one kat from another.." << endl;
        Sleep(1000);
        cout << "The Katz seem to be missing a few marbles" << endl;
        Sleep(1000);
        cout << "They all look as dumb as a rock!! " << endl;
        Sleep(2000);
        smart=0;

    }

    //cout << "**Function: " << " randkatmov " << " calls function katattackpur ,Katz attack if they can" << " Line 653 " << endl;
    katattckpur();

    //cout << "**Function: " << " randkatmov " << " calls function katattackeye ,Katz attack if they can" << " Line 653 " << endl;
    katattckeye();


    for (int count = 0; count < 5; count++)
        {
            if (stpkatdead[count][0]==0)
            {
                    stpkatzmvexec(stpkatzmv[count][0],count);
                    stpkatzmvexec(stpkatzmv[count][1],count);
            }
            else
                {
                 //cout << "Kat: " << count << "is captured" << endl;

            }
        }

    for (int count = 0; count < 5; count++)
        {
            if (smartkatdead[count][0]==0)
            {
                    smartkatzmvexec(smartkatzmv[count][0],count);
                    smartkatzmvexec(smartkatzmv[count][1],count);
            }
            else
                {
                 //cout << "Kat: " << count << "is captured" << endl;

            }
        }


}

bool stpkatzmvexec(int comd,int katnum)
{
    //cout << "**Function: " << " stpkatzmvexec " << "receives command and kat number then executes the command" << " Line 139 " << endl;

    switch (comd)
    {
        case 0 : {//cout << "**Function: " << " stpkatzmvexec "  << "Kat " << katnum << " executing 0" << endl;
                    if (glasses == 0)
                    {
                          glasses = 1;
                    }
                    else
                    {
                        glasses = 0;
                    }
                    }
                     break;

        case 1 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 1" << endl;
                    if (katmovetest(1,katnum))
                        {
                            if (occptestkatz(1,katnum))
                                stpktmov(1,katnum);
                        }
                    else
                        {
                            //cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                     return false;
                    }
                      break;
                }
        case 2 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 2" << endl;
                    if (katmovetest(2,katnum))if (occptestkatz(2,katnum))stpktmov(2,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                        return false;}
                        break;}
        case 3 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 3" << endl;
                    if (katmovetest(3,katnum))if (occptestkatz(3,katnum))stpktmov(3,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                        return false;}
                        break;}
        case 4 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 4" << endl;
                    if (katmovetest(4,katnum))if (occptestkatz(4,katnum))stpktmov(4,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                        return false;}
                        break;}
        case 5 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 5" << endl;
                    if (earmuff == 0) earmuff = 1; else earmuff = 0;
                    break;}
        case 6 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 6" << endl;
                    if (katmovetest(6,katnum))if (occptestkatz(6,katnum))stpktmov(6,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                    return false;}
                     break;}
        case 7 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 7" << endl;
                    if (katmovetest(7,katnum))if (occptestkatz(7,katnum))stpktmov(7,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                    return false;}
                    break;}
        case 8 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 8" << endl;
                    if (katmovetest(8,katnum))if (occptestkatz(8,katnum))stpktmov(8,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                    return false;}
                    break;}
        case 9 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 9" << endl;
                    if (katmovetest(9,katnum))if (occptestkatz(9,katnum))stpktmov(9,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                    return false;}
                    break;}
        case 10 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 10"<< endl;
                    if (earmuff == 0) earmuff = 1; else earmuff = 0; break;}
        case 11 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 11";
                    break;}
        case 12 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 12";
                    break;}
        case 13 : {//cout << "**Function: " << " stpkatzmvexec " << "Kat " << katnum << " executing 13";
                    break;}
        }

}

bool smartkatzmvexec(int comd,int katnum)
{
   // cout << "**Function: " << " smartkatzmvexec " << "receives command and kat number then executes the command" << " Line 139 " << endl;

    switch (comd)
    {
        case 0 : {//cout << "**Function: " << " smartkatzmvexec "  << "Kat " << katnum << " executing 0" << endl;
                    if (glasses == 0)
                    {
                        glasses = 1;
                    }
                    else
                    {
                        glasses = 0;
                    }
                    }
                     break;

        case 1 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 1" << endl;
                    if (smartkatmovetest(1,katnum))
                        {
                            if (smartoccptestkatz(1,katnum))
                                smartktmov(1,katnum);
                        }
                    else
                        {
                            //cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                     return false;
                    }
                      break;
                }
        case 2 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 2" << endl;
                    if (smartkatmovetest(2,katnum))if (smartoccptestkatz(2,katnum))smartktmov(2,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                            return false;} break;}
        case 3 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 3" << endl;
                    if (smartkatmovetest(3,katnum))if (smartoccptestkatz(3,katnum))smartktmov(3,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                            return false;} break;}
        case 4 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 4" << endl;
                    if (smartkatmovetest(4,katnum))if (smartoccptestkatz(4,katnum))smartktmov(4,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                            return false;} break;}
        case 5 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 5" << endl;
                    if (earmuff == 0) earmuff = 1; else earmuff = 0; break;}
        case 6 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 6" << endl;
                    if (smartkatmovetest(6,katnum))if (smartoccptestkatz(6,katnum))smartktmov(6,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                            return false;} break;}
        case 7 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 7" << endl;
                    if (smartkatmovetest(7,katnum))if (smartoccptestkatz(7,katnum))smartktmov(7,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                            return false;} break;}
        case 8 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 8" << endl;
                    if (smartkatmovetest(8,katnum))if (smartoccptestkatz(8,katnum))smartktmov(8,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                            return false;} break;}
        case 9 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 9" << endl;
                    if (smartkatmovetest(9,katnum))if (smartoccptestkatz(9,katnum))smartktmov(9,katnum); else {//cout << "Kat: "<< katnum << " Cannot move in that direction" << endl;
                            return false;} break;}
        case 10 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 10"<< endl;
                    if (earmuff == 0) earmuff = 1; else earmuff = 0; break;}
        case 11 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 11";
                    break;}
        case 12 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 12";
                    break;}
        case 13 : {//cout << "**Function: " << " smartkatzmvexec " << "Kat " << katnum << " executing 13";
                    break;}
        }

}
bool katmovetest(int dir,int katnum)
{
    //cout << "**Function: " << " katmovetest " << "receives command and kat number then tests to see if kat can move in that direction" << " Line 139 " << endl;

    int lat = stpkatz[katnum][1];
    int longt = stpkatz[katnum][0];
    int top = 18;
    int bottom = 1;
    switch (dir)
    {
        case 0 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " executing 0";
                    break;}
        case 1 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " testing 1" << endl;
                    if (lat == bottom || longt == bottom) return false;  break;}
        case 2 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " testing 2" << endl;
                    if (longt ==bottom  ) return false; break;}
        case 3 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " testing 3" << endl;
                    if (lat == top || longt == bottom ) return false; break;}
        case 4 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " testing 4" << endl;
                    if (lat == bottom) return false; break;}
        case 5 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " executing 5";
                    break;}
        case 6 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " testing 6" << endl;
                    if (lat == top) return false; break;}
        case 7 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " testing 7" << endl;
                    if (lat == bottom || longt == top ) return false; break;}
        case 8 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " testing 8" << endl;
                    if (longt == top ) return false; break;}
        case 9 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " testing 9" << endl;
                    if (lat == top || longt == top){ return false;} else {return true;}  break;}
        case 10 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " executing 10";
                    break;}
        case 11 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " executing 11";
                    break;}
        case 12 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " executing 12";
                    break;}
        case 13 : {//cout << "**Function: " << " katmovetest " << "Kat " << katnum << " executing 13";
                    break;}
    }



}

bool smartkatmovetest(int dir,int katnum)
{
    //cout << "**Function: " << " smartkatmovetest " << "receives command and kat number then tests to see if kat can move in that direction" << " Line 139 " << endl;

    int lat = smartkatz[katnum][1];
    int longt = smartkatz[katnum][0];
    int top = 18;
    int bottom = 1;
    switch (dir)
    {
        case 0 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " executing 0";
                    break;}
        case 1 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " testing 1" << endl;
                    if (lat == bottom || longt == bottom) return false;  break;}
        case 2 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " testing 2" << endl;
                    if (longt ==bottom  ) return false; break;}
        case 3 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " testing 3" << endl;
                    if (lat == top || longt == bottom ) return false; break;}
        case 4 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " testing 4" << endl;
                    if (lat == bottom) return false; break;}
        case 5 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " executing 5";
                    break;}
        case 6 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " testing 6" << endl;
                    if (lat == top) return false; break;}
        case 7 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " testing 7" << endl;
                    if (lat == bottom || longt == top ) return false; break;}
        case 8 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " testing 8" << endl;
                    if (longt == top ) return false; break;}
        case 9 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " testing 9" << endl;
                    if (lat == top || longt == top){ return false;} else {return true;}  break;}
        case 10 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " executing 10";
                    break;}
        case 11 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " executing 11";
                    break;}
        case 12 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " executing 12";
                    break;}
        case 13 : {//cout << "**Function: " << " smartkatmovetest " << "Kat " << katnum << " executing 13";
                    break;}
    }



}
bool occptestkatz (int dir, int katnum)
{
    //cout << "**Function: " << " occptestkatz " << "tests to see if there is something in a grid for katz only" << " Line 139 " << endl;
    int katlongt =stpkatz[katnum][0];
    int katlat = stpkatz[katnum][1];
    int lat = 0;
    int longt = 0;
    char test = '0';
    char test1='-';
    switch (dir)
    {
        case 0 : {//cout << "**Function: " << " occptestkatz "  << "Kat " << katnum << " executing 0";
                    break;}
        case 1 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " ocptesting 1" << " sw" << endl;
                    lat=katlat-1;longt=katlongt-1;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                return false;}
                break;}
        case 2 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " ocptesting 2" << " s" << endl;
                    lat=katlat;longt= katlongt-1;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. "<< endl;
                    return false;}
                    break;}
        case 3 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " ocptesting 3" << " se" << endl;
                    lat=katlat+1;longt=katlongt-1;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. "<< endl;
                    return false;}
                    break;}
        case 4 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " ocptesting 4" << " w" << endl;
                    lat=katlat-1;longt=katlongt;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. "<< endl;
                    return false;}
                    break;}
        case 5 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " executing 5";
                    break;}
        case 6 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " ocptesting 6" << " e" << endl;
                    lat=katlat+1;longt=katlongt;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. "<< endl;
                    return false;}
                    break;}
        case 7 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " ocptesting 7" << " nw" << endl;
                    lat=katlat-1;longt=katlongt+1;test=grid[longt][lat];
                    //cout << test<< " " << longt << " " << lat  << endl;
                if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. "<< endl;
                    return false;}
                    break;}
        case 8 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " ocptesting 8" << " n" << endl;
                    lat=katlat;longt=katlongt+1;test=grid[longt][lat];
                    //cout << test << " " << longt << " " << lat  << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. "<< endl;
                    return false;}
                    break;}
        case 9 : {//cout << "**Function: " << " occptestkatz " << "Kat " << katnum << " ocptesting 9" << " ne" << endl;
                    lat=katlat+1;longt=katlongt+1;test=grid[longt][lat];
                    //cout << test << " " << longt << " " << lat << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. "<< endl;
                    return false;}
                    break;}
        case 10 : {cout << "executing 10";
                    break;}
        case 11 : {cout << "executing 11";
                    break;}
        case 12 : {cout << "executing 12";
                    break;}
        case 13 : {cout << "executing 13";
                    break;}
    }
}

bool smartoccptestkatz (int dir, int katnum)
{
    //cout << "**Function: " << " smartoccptestkatz " << "tests to see if there is something in a grid for katz only" << " Line 139 " << endl;
    int katlongt =smartkatz[katnum][0];
    int katlat = smartkatz[katnum][1];
    int lat = 0;
    int longt = 0;
    char test = '0';
    char test1='-';

    populatekatz();

    switch (dir)
    {
        case 0 : {//cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " executing 0";
                    break;}
        case 1 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " ocptesting 1" << " sw" << endl;
                    lat=katlat-1;longt=katlongt-1;test=grid[longt][lat];
                    //cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " loc: " << test<< " " << longt << " " << lat << " from: " << katlongt << " " << katlat << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                return false;}
                break;}
        case 2 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " ocptesting 2" << " s" << endl;
                    lat=katlat;longt= katlongt-1;test=grid[longt][lat];
                    //cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " loc: " << test<< " " << longt << " " << lat  << " from: " << katlongt << " " << katlat << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                    return false;}
                    break;}
        case 3 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " ocptesting 3" << " se" << endl;
                    lat=katlat+1;longt=katlongt-1;test=grid[longt][lat];
                    //cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " loc: " << test<< " " << longt << " " << lat  << " from: " << katlongt << " " << katlat << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                    return false;}
                    break;}
        case 4 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " ocptesting 4" << " w" << endl;
                    lat=katlat-1;longt=katlongt;test=grid[longt][lat];
                    //cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " loc: " << test<< " " << longt << " " << lat  << " from: " << katlongt << " " << katlat << endl;
                if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                    return false;}
                    break;}
        case 5 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " executing 5";
                    break;}
        case 6 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " ocptesting 6" << " e" << endl;
                    lat=katlat+1;longt=katlongt;test=grid[longt][lat];
                  //cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " loc: " << test<< " " << longt << " " << lat  << " from: " << katlongt << " " << katlat << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                    return false;}
                    break;}
        case 7 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " ocptesting 7" << " nw" << endl;
                    lat=katlat-1;longt=katlongt+1;test=grid[longt][lat];
                 //cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " loc: " << test<< " " << longt << " " << lat  << " from: " << katlongt << " " << katlat << endl;
                if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                    return false;}
                    break;}
        case 8 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " ocptesting 8" << " n" << endl;
                    lat=katlat;longt=katlongt+1;test=grid[longt][lat];
                    //cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " loc: " << test << " " << longt << " " << lat  << " from: " << katlongt << " " << katlat << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                    return false;}
                    break;}
        case 9 : {//cout << "**Function: " << " smartoccptestkatz " << "Kat " << katnum << " ocptesting 9" << " ne" << endl;
                    lat=katlat+1;longt=katlongt+1;test=grid[longt][lat];
                    //cout << "**Function: " << " smartoccptestkatz "  << "Kat " << katnum << " loc: " << test << " " << longt << " " << lat << " from: " << katlongt << " " << katlat << endl;
                    if (test!=test1){//cout <<"Kat: "<< katnum << " cannot move in that direction, " << "something is there. " << endl;
                    return false;}
                    break;}
        case 10 : {cout << "executing 10";
                    break;}
        case 11 : {cout << "executing 11";
                    break;}
        case 12 : {cout << "executing 12";
                    break;}
        case 13 : {cout << "executing 13";
                    break;}
    }
}

void stpktmov(int dir,int katnum)
{
    //cout << "**Function: " << " stpktmov " << "moves kat to new location and calls priorloc function to remove old location" << " Line 139 " << endl;

    int lat = stpkatz[katnum][1];
    int longt = stpkatz[katnum][0];

    priorloc(grid,occp,longt,lat);
    switch (dir)
    {
        case 0 : {//cout << "Kat " << katnum << " executing 0";
                    break;}
        case 1 : {//cout << "Kat " << katnum << " moving 1" << endl;
                    stpkatz[katnum][1]-=1;stpkatz[katnum][0]-=1;
                    break;}
        case 2 : {//cout << "Kat " << katnum << " moving 2" << endl;
                    stpkatz[katnum][0]-=1;
                    break;}
        case 3 : {//cout << "Kat " << katnum << " moving 3" << endl;
                    stpkatz[katnum][1]+=1;stpkatz[katnum][0]-=1;
                    break;}
        case 4 : {//cout << "Kat " << katnum << " moving 4" << endl;
                    stpkatz[katnum][1]-=1;
                    break;}
        case 5 : {//cout << "Kat " << katnum << " executing 5";
                    break;}
        case 6 : {//cout << "Kat " << katnum << " moving 6" << endl;
                    stpkatz[katnum][1]+=1;
                    break;}
        case 7 : {//cout << "Kat " << katnum << " moving 7" << endl;
                    stpkatz[katnum][1]-=1;stpkatz[katnum][0]+=1;
                    break;}
        case 8 : {//cout << "Kat " << katnum << " moving 8" << endl;
                    stpkatz[katnum][0]+=1;
                    break;}
        case 9 : {//cout << "Kat " << katnum << " moving 9" << endl;
                    stpkatz[katnum][1]+=1;stpkatz[katnum][0]+=1;
                    break;}
        case 10 : {//cout << "executing 10";
                    break;}
        case 11 : {//cout << "executing 11";
                    break;}
        case 12 : {//cout << "executing 12";
                    break;}
        case 13 : {//cout << "executing 13";
                    break;}
    }

}
void smartktmov(int dir,int katnum)
{
    //cout << "**Function: " << " smartktmov " << "moves kat to new location and calls priorloc function to remove old location" << " Line 139 " << endl;

    int lat = smartkatz[katnum][1];
    int longt = smartkatz[katnum][0];

    priorloc(grid,occp,longt,lat);
    switch (dir)
    {
        case 0 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " executing 0";
                    break;}
        case 1 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " moving 1" << endl;
                    smartkatz[katnum][1]-=1;smartkatz[katnum][0]-=1;
                    break;}
        case 2 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " moving 2" << endl;
                    smartkatz[katnum][0]-=1;
                    break;}
        case 3 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " moving 3" << endl;
                    smartkatz[katnum][1]+=1;smartkatz[katnum][0]-=1;
                    break;}
        case 4 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " moving 4" << endl;
                    smartkatz[katnum][1]-=1;
                    break;}
        case 5 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " executing 5";
                    break;}
        case 6 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " moving 6" << endl;
                    smartkatz[katnum][1]+=1;
                    break;}
        case 7 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " moving 7" << endl;
                    smartkatz[katnum][1]-=1;smartkatz[katnum][0]+=1;
                    break;}
        case 8 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " moving 8" << endl;
                    smartkatz[katnum][0]+=1;
                    break;}
        case 9 : {//cout << "**Function: " << " smartktmov " << "Kat " << katnum << " moving 9" << endl;
                    smartkatz[katnum][1]+=1;smartkatz[katnum][0]+=1;
                    break;}
        case 10 : {//cout << "**Function: " << " smartktmov " << "executing 10";
                    break;}
        case 11 : {//cout << "**Function: " << " smartktmov " << "executing 11";
                    break;}
        case 12 : {//cout << "**Function: " << " smartktmov " << "executing 12";
                    break;}
        case 13 : {//cout << "executing 13";
                    break;}
    }

}


bool purrtest()
{
    //cout << "**Function: " << " purrtest " << "generates random number to see if attack is successfull" << " Line 139 " << endl;
    int minn = 0;
    int maxhit = 100;
    int minhit = 20;
    int hit = 0;
    static int seededmov =0;
    int sd = (seededmov * 30);

    unsigned seed = time(0)*sd;
    srand(seed);

    hit = ((rand() % (maxhit - minn + 1)) + minn);
    //cout << "**Function: " << " purrtest " << "hit: " << hit << endl;

    if (glasses)
    {
        minhit = 40;

    }
    //cout << "**Function: " << " purrtest " << "minhit: " << minhit << endl;

    if (hit >=minhit)
    {
        //cout << "**Function: " << " purrtest " << "Success" <<  endl;
        stunned=1;
        cout << "You have been stunned!!!" <<  endl;
        Sleep(1000);
    }
    seededmov++;
}

void katattckeye()
{
   // cout << "**Function: " << " katattckeye " << "executes attacks from cats who can eye attack" << " Line 139 " << endl;

    for (int count = 0; count < 5; count++)
    {
        if (stpkatdead[count][0]==0)
        {


       // cout << "**Function: " << " katattckeye " << "For loop count:" << count << endl;
        //cout << "**Function: " << " katattckeye flag is:"  << stpkatateye[count][0] <<  endl;
        if (stpkatateye[count][0]==1)
        {
            eyetest();
            eyetest();

          //  cout << "**Function: " << " katattckeye "  << count << " " << "can attack!" << endl;
            stpkatzmv[count][0] = 10;
            stpkatzmv[count][1] = 10;
        }
        }
        else
        {

        //cout << "Kat: " << count << " is captured" << endl;

        }

    }
    for (int count = 0; count < 5; count++)
    {
        if (smartkatdead[count][0]==0)
        {


       //cout << "**Function: " << " katattckeye " << "For loop, Smart Kat:" << count << endl;
        //cout << "**Function: " << " katattckeye flag is:"  << smartkatateye[count][0] <<  endl;
        if (smartkatateye[count][0]==1)
        {
           // cout << "**Function: " << " katattckeye " << "executing eyetest:" << count << endl;
            eyetest();
            eyetest();

          //  cout << "**Function: " << " katattckeye "  << count << " " << "can attack!" << endl;
            smartkatzmv[count][0] = 10;
            smartkatzmv[count][1] = 10;
        }
        }
        else
        {

        //cout << "Smart Kat: " << count << " is captured" << endl;

        }

    }
}

bool eyetest()
{

    //cout << "**Function: " << " eyetest " << "generates random number to see if eye attack is successfull" << " Line 139 " << endl;
    int minn = 1;
    int maxhit = 100;
    int minhit = 40;
    int hit = 0;
    static int seededmov =0;
    int sd = (seededmov * 30);


    unsigned seed = time(0)*sd;
    srand(seed);

    hit = (rand() % (maxhit - minn + 1)) + minn;
    //cout << "**Function: " << " eyetest " << "hit: " << hit << endl;

    cout << "Wow, one of the katz has some really adorable eyes .." <<  endl;
    Sleep(500);
    cout << endl;
    cout << "It seems to be getting closer and closer ..." <<  endl;
    Sleep(500);
    cout << endl;
    cout << "The kat attempts to look deep into your eyes!" <<  endl;
    Sleep(2500);
    cout << endl;
    cout << endl;

    if (glasses)
    {
    cout << "Good thing you are wearing your glasses!!!" <<  endl;
    Sleep(500);
    cout << endl;
    cout << endl;

        minhit = 70;

    }
    //cout << "**Function: " << " eyetest " << "minhit: " << minhit << endl;

    if (hit >=minhit)
    {
    cout << "The kat locks eyes with you!!" <<  endl;
    Sleep(500);
    cout << "You can't help but wonder how bad a life these katz must have!" <<  endl;
    Sleep(500);
    cout << "You decide you will give the Kat one of your tuna cans!" <<  endl;
    Sleep(500);
    cout << "But as you reach for a can you discover that ..." <<  endl;
    Sleep(2500);
    cout << endl;
    cout << endl;
        //cout << "**Function: " << " eyetest " << "Success" <<  endl;
        curhealth-=1;
        cout << "One of your tuna cans is missing!!!" <<  endl;
        Sleep(1000);
        cout << endl;
        cout << endl;
    }
    seededmov++;
}

int cankatcapture()
{
    //cout << "**Function: " << " cankatcapture " << "returns kat that can be captured" << " Line 139 " << endl;

    int difrnlong =0;
    int difrnlat = 0;
    int absltdifflong =0;
    int absltdifflat =0;

    for (int count = 0; count < 5; count++)
       {
           if (stpkatdead[count][0]==0)
           {


           difrnlong =stpkatz[count][0] - curlongt;
           difrnlat= stpkatz[count][1] - curlat;
          // cout << "**Function: " << " cankatcapture " << " eye "  << "kat: " << count << " longt:" << stpkatz[count][0] << " lat:" << stpkatz [count][1] << endl;

           absltdifflong=abs(difrnlong);
           absltdifflat=abs(difrnlat);
          // cout << "**Function: " << " cankatcapture " << " eye "  << "kat: " << count << " abslongt:" << absltdifflong << " abslat:" << absltdifflat << endl;

           if (absltdifflong== 1)
                {

                    //cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count  << "if absltdifflong ==1 " << absltdifflong << endl;
                    stpkatateye[count][0]=0;
                  //  cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count  << " if (absltdifflong== 1) kat " << count << " attack set to " << stpkatateye[count][0] << endl;
                    if (absltdifflat== 1)
                        {
                       // cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count   << " if (absltdifflat== 1) kat " << count << " can be captured" << endl;
                        return count;}
                    else if (absltdifflat== 0)
                        {
                           // cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count  << " else if (absltdifflat== 0) absltdifflat " << absltdifflat << endl;
                            stpkatateye[count][0]=1;

                           // cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count  << " else if (absltdifflat== 0) Kat " << count << " can be captured" << endl;
                            return count;}
                }
            else if (absltdifflong== 0)
                {
                  //  cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count   << " if (absltdifflong== 0) Kat " << count << endl;
                    stpkatateye[count][0]=0;
                   // cout << "**Function: " << " cankatcapture "  << " eye " << "kat: "  << count  << " if (absltdifflong== 0) Kat " << count << " attack set to " << stpkatateye[count][0] << endl;

                    if (absltdifflat== 1)
                        {stpkatateye[count][0]=1;
                        {
                      //  cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count   << " if (absltdifflat== 1) Kat " << count << " can be captured" <<  endl;
                        return count;}
                        }
                }
            else
                {
             //   cout << "**Function: " << " cankatcapture " << " eye "   << "kat:" << count << "{stpkatateye[count][0]=0;" << endl;
                stpkatateye[count][0]=0;
               // cout << "**Function: " << " cankatcapture " << " eye "   << "kat: "  << count << " longt distance  " << absltdifflong << endl;
               // cout << "**Function: " << " cankatcapture " << " eye "  << "kat: "  << count << " lat distance " << absltdifflat << endl;
                stpkatateye[count][0]=0;
                ;
                }

            }
            else
                {
                    //cout << "Kat: " << count << " is captured " << endl;

            }
       }
       for (int count = 0; count < 5; count++)
       {
           if (smartkatdead[count][0]==0)
           {


           difrnlong =smartkatz[count][0] - curlongt;
           difrnlat= smartkatz[count][1] - curlat;
          // cout << "**Function: " << " cankatcapture " << " eye "  << "kat: " << count << " longt:" << smartkatz[count][0] << " lat:" << smartkatz [count][1] << endl;

           absltdifflong=abs(difrnlong);
           absltdifflat=abs(difrnlat);
          // cout << "**Function: " << " cankatcapture " << " eye "  << "kat: " << count << " abslongt:" << absltdifflong << " abslat:" << absltdifflat << endl;

           if (absltdifflong== 1)
                {

                    //cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count  << "if absltdifflong ==1 " << absltdifflong << endl;
                    smartkatateye[count][0]=0;
                  //  cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count  << " if (absltdifflong== 1) kat " << count << " attack set to " << smartkatateye[count][0] << endl;
                    if (absltdifflat== 1)
                        {
                       // cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count   << " if (absltdifflat== 1) kat " << count << " can be captured" << endl;
                        return count+5;}
                    else if (absltdifflat== 0)
                        {
                           // cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count  << " else if (absltdifflat== 0) absltdifflat " << absltdifflat << endl;
                            smartkatateye[count][0]=1;

                           // cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count  << " else if (absltdifflat== 0) Kat " << count << " can be captured" << endl;
                            return count+5;}
                }
            else if (absltdifflong== 0)
                {
                  //  cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count   << " if (absltdifflong== 0) Kat " << count << endl;
                    smartkatateye[count][0]=0;
                   // cout << "**Function: " << " cankatcapture "  << " eye " << "kat: "  << count  << " if (absltdifflong== 0) Kat " << count << " attack set to " << smartkatateye[count][0] << endl;

                    if (absltdifflat== 1)
                        {smartkatateye[count][0]=1;
                        {
                      //  cout << "**Function: " << " cankatcapture " << " eye " << "kat: "  << count   << " if (absltdifflat== 1) Kat " << count << " can be captured" <<  endl;
                        return count+5;}
                        }
                }
            else
                {
             //   cout << "**Function: " << " cankatcapture " << " eye "   << "kat:" << count << "{smartkatateye[count][0]=0;" << endl;
                smartkatateye[count][0]=0;
               // cout << "**Function: " << " cankatcapture " << " eye "   << "kat: "  << count << " longt distance  " << absltdifflong << endl;
               // cout << "**Function: " << " cankatcapture " << " eye "  << "kat: "  << count << " lat distance " << absltdifflat << endl;
                smartkatateye[count][0]=0;
                ;
                }

            }
            else
                {
                    //cout << "Kat: " << count << " is captured " << endl;

            }
       }
       return -1;



}

void katcapture(int kat)
{

    //cout << "**Function: " << " katcapture " << "generates random number to see if capture is successfull" << " Line 139 " << endl;
    int minn = 1;
    int maxhit = 100;
    int minhit = 25;
    int hit = 0;
    static int seededmov =0;
    int sd = (seededmov * 30);

    unsigned seed = time(0)*sd;
    srand(seed);

    hit = (rand() % (maxhit - minn + 1)) + minn;
   // cout << "**Function: " << " katcapture " << "hit: " << hit << endl;

    //cout << "**Function: " << " katcapture " << "minhit: " << minhit << endl;

    if (hit ==minhit)
    {
       // cout << "**Function: " << " katcapture " << "Trapped self" <<  endl;
        stunned=1;
        cout << "You carefully lay down your trap... " <<  endl;
        Sleep(1000);
        cout << "You hear a strange noise and fall into your own trap!!!" << endl;
         Sleep(1000);
         cout << endl;
         cout << endl;
        cout << "You have trapped for one turn!!" <<  endl;
         Sleep(1000);
    }
    else if (hit >=minhit)
        {
            if (kat < 5)
            {
                 cout << "You carefully lay down your trap... " <<  endl;
                 Sleep(1000);
                 cout << "You bait the trap with a can of Tuna and wait for a Kat" << endl;
                 Sleep(1000);
                 cout << "You see a Kat sniffing around your trap... could this be it?!!!" << endl;
                Sleep(1500);

       // cout << "**Function: " << " katcapture " << "success" <<  endl;
         stpkatdead[kat][0]=1;
         foundtuna();
        cout << "You have trapped kat " << kat << " !!!" <<  endl;
        won++;
        if (won==10)
        {
            cout << "You have captured all the katz!!! Congratulations!!!" << endl;
            exit(0);
        }
            }
            else
            {

                 cout << "You carefully lay down your trap... " <<  endl;
                 Sleep(1000);
                 cout << "You bait the trap with a can of Tuna and wait for a Kat" << endl;
                 Sleep(1000);
                 cout << "You see a Kat sniffing around your trap... could this be it?!!!" << endl;
                Sleep(1500);
                kat-=5;


       // cout << "**Function: " << " katcapture " << "success" <<  endl;
         smartkatdead[kat][0]=1;
         foundtuna();
        cout << "You have trapped smart kat " << kat << "!!!" <<  endl;
         Sleep(1500);
        won++;
        if (won==10)
        {
            cout << "You have captured all the katz!!! Congratulations!!!" << endl;
            exit(0);
        }

            }

    }
    srand(seed);srand(seed);srand(seed);

}
void foundtuna()
{
    //cout << "**Function: " << " foundtuna " << "generates random number to see if a tuna is found" << " Line 139 " << endl;

    if (!(curhealth == 5))
    {
    int minn = 1;
    int maxhit = 100;
    int minhit = 90;
    int hit = 0;

    unsigned seed = time(0);
    srand(seed);

    hit = (rand() % (maxhit - minn + 1)) + minn;
    //cout << "**Function: " << " foundtuna " <<"hit:  " << hit <<  endl;
    if (hit >=minhit)
        {
       // cout << "**Function: " << " foundtuna " << "success you have found tuna" <<  endl;
        curhealth+=1;
        cout << "You have found a tuna from a kat " <<  endl;
        }

    }
}
void intro()
{
    // cout << "**Function: " << " intro " << "shows description of the game and commands" <<  endl;

    char buildings = 200;
    char smartkat = 1 ;
    char stupidkat = 2;
    char user ='@';
    char emptyspace= '-';

    //Intro to the game
    cout << setw(40)<< right << "KRAZY KATZ" << endl<<endl;
    cout << "You are a well renown Krazy Kat hunter sent into a town crawling" <<endl;
    cout << "with Krazy Kats!! These Kats wander through town attacking their"<< endl;
    cout << "victims with Eyes of Submission & Purrs of Doom. Once a human has"<< endl;
    cout << "been subdued they steal their Tuna Of Health!!" << endl << endl;

    cout << "You the hunter can put on Reflective Glasses or Earmuffs of Happiness"<< endl;
    cout << "to stop the Kats attacks. You also have the Kat Kapture system that "<< endl;
    cout << "safely bags and muffles the Kats."<<endl<<endl<<endl;


    cout << "Press \"Enter\" to continue..."<<endl;
    cin.get();
    system("cls");

    //How to play the game
    cout << setw(40)<< right << "HOW TO PLAY" << endl<<endl;
    cout << "You use the number pad to enter commands. Alternatively you can issue commands" << endl;
    cout << "by entering the appropriate number or character."<< endl<< endl;
    cout << "The Hunter gets two moves and then its the Katz turn!!! " << endl<< endl;

    cout << "Press \"Enter\" to continue..."<<endl;
    cin.get();
    system("cls");

    cout << "Movement Commands:" << endl << endl;
    cout << setw(23) << right << "8" << endl<< endl;
    cout << setw(25) << right << "North" << endl<< endl;
    cout << setw(4) << right << "7" << setw(15) << right  << "Northwest" << setw(15) << "Northeast" << setw(4)<< 9<< endl <<endl;
    cout << setw(4) << right << "4" << setw(15) << right  << "West" << setw(15) << "East" << setw(4)<< 6<< endl<< endl;
    cout << setw(4) << right << "1" << setw(15) << right  << "Southwest" << setw(15) << "Southeast" << setw(4)<< 3<< endl<< endl;
    cout << setw(25) << right << "South" << endl<< endl;
    cout << setw(23) << right << "2" << endl<< endl;

    cout << "Action Commands:" << endl << endl;
    cout << setw(4) << right << "5" << setw(15) << right << "Kat Kapture" << setw(35) << "Equip Reflective Glasses" << setw (4) << 0 << endl << endl;
    cout << setw(10) << right << ". " << setw(32) << right << "Equip Earmuff's of Happiness" <<endl << endl;

    cout << "Press \"Enter\" to continue..."<<endl;
    cin.get();
    system("cls");

    cout << setw(40)<< right << "THE TOWN" << endl<<endl;
    cout << "Icons:" << endl << endl;

    cout << setw(4) << right << "-" << setw(15) << right << "Empty room" << setw(15) << "Building" << setw (4) << buildings  << endl << endl;
    cout << setw(4) << right << smartkat << setw(15) << right << "Smart Katz" << setw(15) << "Stupid Katz" << setw (4) << stupidkat  << endl << endl;
    cout << setw(27) << right << "The Hunter" << endl<< endl;
    cout << setw(23) << right << "@" << endl<< endl;

    cout << "Press \"Enter\" to continue..."<<endl;
    cin.get();
    system("cls");

}




