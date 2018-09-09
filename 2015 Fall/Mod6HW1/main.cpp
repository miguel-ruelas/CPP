#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct temps
{
    string month;
    float rainfall;
    float hightemp;
    float lowtemp;
    float avgtemp;
};
struct yeardata
{
    short int year;
    float totalrain;
    float avgrain;
    float yrhigh;
    string highmnth;
    float yrlow;
    string lowmonth;
    float yravgtemp;
};

void getdata(temps yr[], int);
void calcdat(temps yr[], int,yeardata yrs[], int);
void showdata(yeardata yrs[], int);

int main()
{

    int size = 12;
    temps year1[size];
    int decade = 10;
    yeardata years[decade];

    getdata(year1, size);
    calcdat(year1, size, years, decade);
    showdata(years, decade);


    return 0;
}

void getdata(temps yr[], int sze)
{
    ifstream inputFile;

// Open the file.
inputFile.open("input.txt");
// If the file successfully opened, process it.
if (inputFile)
{
    float lowstemp =  -100;
    float maxtemp = 140;

    for (int row = 0; row < sze; row++)
        {
            inputFile >> yr[row].month;
          //test  cout << yr[row].month << endl;
            inputFile >> yr[row].rainfall;
            if (yr[row].rainfall < 0)
            {
                cout << "Invalid amount entered, rainfall cannot be less than 0";
            }
            //test cout << yr[row].rainfall << endl;
            inputFile >> yr[row].hightemp;
            if (yr[row].hightemp < lowstemp || yr[row].hightemp> maxtemp )
            {
                cout << "Invalid amount detected :" << yr[row].hightemp << endl ;
            }

           //test  cout << yr[row].hightemp << endl;
            inputFile >> yr[row].lowtemp;
             if (yr[row].lowtemp < lowstemp || yr[row].lowtemp > maxtemp )
            {
                cout << "Invalid amount detected :" << yr[row].lowtemp << endl ;
            }

          //test   cout << yr1[row].lowtemp << endl;
            inputFile >> yr[row].avgtemp;
            if (yr[row].avgtemp < lowstemp || yr[row].avgtemp > maxtemp )
            {
                cout << "Invalid amount detected :" << yr[row].avgtemp << endl ;
            }
          //test   cout << yr[row].avgtemp << endl;

        }
 // Read the numbers from the file and
 // display them.

// Close the file.
 inputFile.close();
 }
 else
 {
 // Display an error message.
 cout << "Error opening the file.\n";
 }
}

void calcdat(temps yr[], int sze ,yeardata yrs[], int dec)
{
    float totalrain = 0; // Initialize accumulator
    float totaltemp = 0; // Initialize accumulator
    float hightemp = 0;
    string highmonth = "";
    float lowtemp = 0;
    string lowmonth ="";

    for (int row = 0; row < sze; row++)
    {
        totalrain += yr[row].rainfall;
        totaltemp += yr[row].avgtemp;
        if (yr[row].hightemp > hightemp)
        {
            hightemp = yr[row].hightemp;
            highmonth= yr[row].month;
        }
        if (yr[row].lowtemp < lowtemp)
        {
            lowtemp = yr[row].lowtemp;
            lowmonth = yr[row].month;
        }

    }

    yrs[0].year = 2015;
    yrs[0].totalrain = totalrain;
    yrs[0].avgrain = (totalrain/12);
    yrs[0].yrhigh = hightemp;
    yrs[0].highmnth = highmonth;
    yrs[0].yrlow =lowtemp;
    yrs[0].lowmonth = lowmonth;
    yrs[0].yravgtemp = (totaltemp/12);

}

void showdata(yeardata yrs[], int dec)
{
    cout << setprecision(2) << fixed << showpoint;
    cout << "Annual Rain Analysis" << endl;
    cout << "Total Rain: " << setw (24) << yrs[0].totalrain << endl;
    cout << "Average Rain: " << setw (22) << yrs[0].avgrain << endl;
    cout << "Average of average rain: " << setw (11) << yrs[0].yravgtemp << endl;
    cout << "The highest temp is: " << yrs[0].yrhigh << " in " << yrs[0].highmnth  << endl;
    cout << "The Lowest temp is: " << yrs[0].yrlow <<" in " << yrs[0].lowmonth  << endl;

}
