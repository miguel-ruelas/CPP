#include <iostream>
#include <cstdlib> // For rand and srand
#include <ctime> // For the time function

using namespace std;

    const int maxlat = 19;
    const int maxlongt = 19 ;
    const int maxmenu = 20;

    char grid [maxlongt][maxlat];
    int occp [maxlongt][maxlat];
    const char menu [maxmenu]= {'0','1','2','3','4','5','6','7','8','9','.','q'};
    int curlat = 10;
    int curlongt = 10;
    int maxhealth = 5;
    int curhealth = 5;
    bool glasses = 0;
    bool earmuff = 0;
    int moves = 0;
    int turn = 0;
    int *stpkatz = NULL; // To point to the baddies

void initgrid (char [maxlongt][maxlat]);
void display(char [maxlongt][maxlat]);
void currentloc(char [maxlongt][maxlat],int [maxlongt][maxlat],int curlongt, int curlat);
void priorloc(char [maxlongt][maxlat],int [maxlongt][maxlat],int curlongt, int curlat);
void occupiedloc(int [maxlongt][maxlat],int curlongt, int curlat);
void freeloc(int [maxlongt][maxlat],int curlongt, int curlat);
int validmenu(const char menu[maxmenu],char);
void menuexec(int);
char inptcommand();
bool charmovetest(int dir);
void charmov(int dir);
void huddisplay();
int *randkatloc(int);

int main()
{
    char usrinp;
    int menunum;
    // Get an array of five random numbers.
    stpkatz = randkatloc(5);
    initgrid(grid);

    currentloc(grid,occp,curlongt,curlat);

    display(grid);
    huddisplay();

    do
        {
    do
    {
        usrinp= inptcommand();

        menunum=validmenu(menu,usrinp);

        if (menunum == -1)
        {
            cout << "Invalid command, please try again.." << endl;
        }


    } while (menunum==-1);

    menuexec(menunum);

    currentloc(grid,occp,curlongt,curlat);
    display(grid);
    huddisplay();
    cout <<"lat: " << curlat << " Longt: " << curlongt << endl;
    moves++;
    cout << "Move " << moves << "/2" << endl ;
    if (moves % 2 == 0)
    {
            turn++;
            cout << "Cats TURN!!!" << endl;
    }
    cout << "Turn "<< turn << endl;

        } while (curhealth != 0);










    return 0;
}

void initgrid (char grd [maxlongt][maxlat])
{
    int row = 0;
    int col = 0;

    for (row = 0; row <= maxlongt; row++)
    {
        for (col = 0; col <= maxlat; col++)
        {
            grid[row][col] = '-';


        }
    }

}


void currentloc(char grd [maxlongt][maxlat],int ocp [maxlongt][maxlat],int curlongt, int curlat)
{
    grid[curlongt][curlat] = '@';
    ocp[curlongt][curlat] = '1';



}
void priorloc(char grd [maxlongt][maxlat],int nonocp [maxlongt][maxlat],int curlongt, int curlat)
{
    grid[curlongt][curlat] = '-';
    nonocp[curlongt][curlat] = '0';



}

void occupiedloc (int ocp [maxlongt][maxlat],int curlongt, int curlat)
{
    ocp[curlongt][curlat] = '1';


}

void freeloc (int ocp [maxlongt][maxlat],int curlongt, int curlat)
{
    ocp[curlongt][curlat] = '0';


}

void display (char grd [maxlongt][maxlat])
{
    int row = 0;
    int col = 0;

    for (row = maxlongt-1; row > 0; row--)
    {
        //cout << row;
        for (col = 1; col < maxlat; col++)
        {

            cout << grid[row][col] << " " ;

        }
         //cout << col << endl;
         cout << endl;


    }

}
int validmenu(const char menu[maxmenu],char usrinp)
{
    char test = tolower(usrinp);

    int index = 0; // Used as a subscript to search array
    int position = -1; // To record position of search value
    bool found = false; // Flag to indicate if the value was found
    while (index < maxmenu && !found)
    {
        if (menu[index] == test) // If the value is found
        {
            found = true; // Set the flag
            cout << "found" << endl;
            position = index; // Record the value's subscript
        }
        index++;
    }
    return position; // Return the position, or −1

}
void menuexec(int comd)
{
    switch (comd)
    {
        case 0 : cout << "executing 0" << endl; if (glasses == 0) glasses = 1; else glasses = 0; break;
        case 1 : cout << "executing 1" << endl; if (charmovetest(1))charmov(1); else cout << "Cannot move in that direction" << endl; break;
        case 2 : cout << "executing 2" << endl; if (charmovetest(2))charmov(2); else cout << "Cannot move in that direction" << endl; break;
        case 3 : cout << "executing 3" << endl; if (charmovetest(3))charmov(3); else cout << "Cannot move in that direction" << endl; break;
        case 4 : cout << "executing 4" << endl; if (charmovetest(4))charmov(4); else cout << "Cannot move in that direction" << endl; break;
        case 5 : cout << "executing 5" << endl; if (earmuff == 0) earmuff = 1; else earmuff = 0; break;
        case 6 : cout << "executing 6" << endl; if (charmovetest(6))charmov(6); else cout << "Cannot move in that direction" << endl; break;
        case 7 : cout << "executing 7" << endl; if (charmovetest(7))charmov(7); else cout << "Cannot move in that direction" << endl; break;
        case 8 : cout << "executing 8" << endl; if (charmovetest(8))charmov(8); else cout << "Cannot move in that direction" << endl; break;
        case 9 : cout << "executing 9" << endl; if (charmovetest(9))charmov(9); else cout << "Cannot move in that direction" << endl; break;
        case 10 : cout << "executing 10"<< endl; if (earmuff == 0) earmuff = 1; else earmuff = 0; break;
        case 11 : cout << "executing 11"; break;
        case 12 : cout << "executing 12"; break;
        case 13 : cout << "executing 13"; break;
    }

}
char inptcommand()
{
    char inpt;
    cin >> inpt;
    return inpt;

}

bool charmovetest(int dir)
{
    int top = 18;
    int bottom = 1;
    switch (dir)
    {
        case 0 : cout << "executing 0"; break;
        case 1 : cout << "testing 1" << endl; if (curlat == bottom || curlongt == bottom) return false;  break;
        case 2 : cout << "testing 2" << endl; if (curlongt ==bottom  ) return false; break;
        case 3 : cout << "testing 3" << endl; if (curlat == top || curlongt == bottom ) return false; break;
        case 4 : cout << "testing 4" << endl; if (curlat == bottom) return false; break;
        case 5 : cout << "executing 5"; break;
        case 6 : cout << "testing 6" << endl; if (curlat == top) return false; break;
        case 7 : cout << "testing 7" << endl; if (curlat == bottom || curlongt == top ) return false; break;
        case 8 : cout << "testing 8" << endl; if (curlongt == top ) return false; break;
        case 9 : cout << "testing 9" << endl; if (curlat == top || curlongt == top){ return false;} else {return true;}  break;
        case 10 : cout << "executing 10"; break;
        case 11 : cout << "executing 11"; break;
        case 12 : cout << "executing 12"; break;
        case 13 : cout << "executing 13"; break;
    }



}
void charmov(int dir)
{
    priorloc(grid,occp,curlongt,curlat);
    switch (dir)
    {
        case 0 : cout << "executing 0"; break;
        case 1 : cout << "moving 1" << endl; curlat-=1;curlongt-=1;  break;
        case 2 : cout << "moving 2" << endl; curlongt-=1; break;
        case 3 : cout << "moving 3" << endl; curlat+=1;curlongt-=1; break;
        case 4 : cout << "moving 4" << endl; curlat-=1;; break;
        case 5 : cout << "executing 5"; break;
        case 6 : cout << "moving 6" << endl; curlat+=1;; break;
        case 7 : cout << "moving 7" << endl; curlat-=1;curlongt+=1; break;
        case 8 : cout << "moving 8" << endl; curlongt+=1; break;
        case 9 : cout << "moving 9" << endl; curlat+=1;curlongt+=1;  break;
        case 10 : cout << "executing 10"; break;
        case 11 : cout << "executing 11"; break;
        case 12 : cout << "executing 12"; break;
        case 13 : cout << "executing 13"; break;
    }



}
void huddisplay()
{
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

}
int *randkatloc( int num)
{
    int *arr = NULL; // Array to hold the numbers

    // Dynamically allocate the array.

    arr = new int[5][5];
    // Seed the random number generator by passing
    // the return value of time(0) to srand.
    srand( time(0) );

    // Populate the array with random numbers.
    for (int count = 0; count < num; count++)
       {
           for (count1 = 0; col < num; count1++)
           arr[count][count] = rand();
       }

}

