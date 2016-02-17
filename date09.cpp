/*******************************************************
*
*      program name:       Date09
*      Author:             Grant Fisher
*      date due:           4/28/14
*      remarks:            A basic program with a class
*                          that details specific date
*                          inputs. Validates the date input.
********************************************************/

/******************************************
*     library includes
******************************************/
#include <iostream>                // needed for I/O
#include <cstdlib>
#include <string.h>
/******************************************
*     pre-processor
******************************************/
using namespace std;

/****************************************
*         Class definitions
****************************************/
class Date
{
    private:
        int* month;              // holds month
        int* day;                // holds day
        int* year;               // holds year
    public:
        //Constructors
        Date();
        Date(int doy, int year);
        Date(int, int, int);

        //Copy Constructor
        Date(Date &obj);

        //Destructor
        ~Date();

        // setters
        void setMonth(int x)    {*month = x;}
        void setDay(int x)      {*day = x;}
        void setYear(int x)     {*year = x;}

        // getters
        int getMonth()          {return *month;}
        int getDay()            {return *day;}
        int getYear()           {return *year;}

        // member functions
        bool calcLeapYear();    // determines leap year
        int calcDayOfYear();    // determines the julian day
        char* getDayOfWeek();   // determines the day of week
        string getMonthName();  // determines the month name
        void display();         // displays information
        int eternalJulian();
        void operator=(Date &obj);
        void operator>(Date &obj);
        void operator<(Date &obj);
        bool validateDate();
};
/****************************************
*         member functions
****************************************/

/*** constructors *****/
Date::Date()
{
    month = new int;
    day = new int;
    year = new int;
}//end default constructor

Date::Date(int doy, int y)
{
    int julianMonth[13] =
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int x;

    month   = new int;
    day     = new int;
    year    = new int;

    setYear(y);

    for(x=1; x<13; x++)
    {
        // increment by 1 if a leap year and Feb ~ Dec
        if(calcLeapYear() && x>1)
        {
            julianMonth[x]++;
        }

        if(doy <= julianMonth[x])
        {
            setMonth(x);
            setDay(doy - julianMonth[x-1]);
            break;
        }
    }
}//end of constructor

Date::Date(int x, int y, int z)
{
   month = new int(x);
   day = new int(y);
   year = new int(z);
}

//Copy Constructor
Date::Date( Date &obj)
{
    month = new int;
    setMonth(obj.getMonth());
    day = new int;
    setDay(obj.getMonth());
    year = new int;
    setYear(obj.getYear());
}//end of copy constructor

// Determines if the year is a leap year
bool Date :: calcLeapYear()
{
    int isLeapYear;

    if((getYear()%400) == 0)
    {
        isLeapYear = 1;
    }
    else if((getYear()%100) == 0)
    {
        isLeapYear = 0;
    }
    else if((getYear()%4) == 0)
    {
        isLeapYear = 1;
    }
    else
    {
        isLeapYear = 0;
    }

    return isLeapYear;
};

//Uses the month, day, and year to calculate the julian day
int Date :: calcDayOfYear()
{
    int doy;   // Variable for Julian Date
    int numDays[14] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    doy = numDays[getMonth()] + getDay();

    if(calcLeapYear() && getMonth()>2)
    {
        doy++;
    }

    else
    {
    }

    return doy;
}

char* Date :: getDayOfWeek()
{
    //  Finds the total number of days after 1/1/1900
    int totDays = 0;
    for (int x = 1900; x < getYear(); x++)
    {
        totDays += 365;
        if(calcLeapYear())
        {
            totDays ++;
        }
    }
    totDays = totDays + calcDayOfYear();

    //  Takes that number and uses it to calculate the day
    char dayOfWeek[7][10] = {"Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int dayCalc;

    dayCalc = totDays % 7;
    //cout << "dayCalc = " << dayCalc;

    char* ptrDayOfWeek;
    ptrDayOfWeek = dayOfWeek[dayCalc];
    return dayOfWeek[dayCalc];
}
// calculates the name of the month number entered
string Date :: getMonthName()
{
    string month1 [13][10] = {
                             {"YaGoofed"},
                             {"January"},
                             {"February"},
                             {"March"},
                             {"April"},
                             {"May"},
                             {"June"},
                             {"July"},
                             {"August"},
                             {"September"},
                             {"October"},
                             {"Novermer"},
                             {"December"}
                            };
    return month1[getMonth()][0];

}


void Date::display()
{
    ///Displays the date and wether or not
    ///The date is a leap year
    ///As well as the julian Date
    char dayName[11];
    strcpy(dayName, getDayOfWeek());

    cout << "\n\n";
    cout << "Month is       " << getMonth() << "\n";
    cout << "Day is         " << getDay() << "\n";
    cout << "Year is        " << getYear() << "\n";
    cout << "Day of year is " << calcDayOfYear() << "\n";

    if(calcLeapYear())
    {
        cout << getYear() << " is a leap year\n";
    }

    else
    {
        cout << getYear() << " is not a leap year\n";
    }
    cout << "Month          " << getMonthName() << "\n";
    cout << "Day-of-week is " << dayName << "\n";
}

int Date::eternalJulian()
{
    int etJulian;
    etJulian = ((calcDayOfYear()) + (getYear() * 365));
    return etJulian;
}
Date::~Date()
{
    delete month;
    delete day;
    delete year;
}

void Date :: operator=( Date &obj)
{
     setMonth(obj.getMonth());
     setDay(obj.getDay());
     setYear(obj.getYear());
}

//Overloads the ">" operator to compare if
//the initial object is "Greater than" the
//other object
void Date :: operator>(Date &obj)
{
    if ((eternalJulian()) > (obj.eternalJulian()))
    {
        cout << getMonth() << "-" << getDay() << "-" << getYear();
        cout << "  is greater than  " << obj.getMonth() << "-" << obj.getDay();
        cout << "-" << obj.getYear();
    }

    else
    {
        cout << getMonth() << "-" << getDay() << "-" << getYear();
        cout << "  is not greater than  " << obj.getMonth() << "-" << obj.getDay();
        cout << "-" << obj.getYear();
    }
}

void Date :: operator<(Date &obj)
{
    if ((eternalJulian()) < (obj.eternalJulian()))
    {
        cout << getMonth() << "-" << getDay() << "-" << getYear();
        cout << "  is lesser than  " << obj.getMonth() << "-" << obj.getDay();
        cout << "-" << obj.getYear();
    }

    else
    {
        cout << getMonth() << "-" << getDay() << "-" << getYear();
        cout << "  is not lesser than  " << obj.getMonth() << "-" << obj.getDay();
        cout << "-" << obj.getYear();
    }
}

bool Date :: validateDate()
{
    try
    {
        ///Checks for valid month input
        if (getMonth() < 1 || getMonth() > 12)
        {
            throw getMonth();
        }
        
        ///Checks the year input
        if (getYear() < 1)
        {
            throw getYear();
        }

        switch(getMonth()) 
        {
            ///Checks Odd months
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (getDay() > 31 || getDay() < 1)
                {
                    throw getDay();
                }
                break;

            ///Checks even Months
            case 4:
            case 6:
            case 9:
            case 11:
                if (getDay() > 30 || getDay() < 1)
                {
                    throw getDay();
                }
                break;

            ///Checks leapyear Days
            case 2:
                if (getDay() < 1 || getDay() > 29)
                {
                    throw getDay();
                }
                else if (calcLeapYear() == 0 && getDay() > 28)
                {
                    throw getDay();
                }
        }

    ///Outputs the valid date if no exception is found.
    cout << getMonth() << "-" << getDay() << "-" << getYear();
    cout << " is a valid date.\n";

    }
    catch(int x)
    {
        cout << x << " is not a valid entry.\n";
    }
        
}


/****************************************
*          function prototypes
****************************************/
void testDate01();
void testDate02();
void testDate03();
void testDate05();
void testDate06();
void testDate07();
void testDate08();
void testDate09();
/*****************************************
*   main() - the function that executes
*****************************************/
int main()
{
    /*******************************
    *     local variables
    ******************************/
    //testDate01();
    //testDate02();
    //testDate03();
    //testDate05();
    //testDate06();
    //testDate07();
    testDate09();
    //system("PAUSE");// causes the program to pause
	return 0;
}  // end main

/*******    PREVIOUS TESTS FUNCTIONS UNRELATED TO DATE07    *******
********                PLEASE IGNORE MR. GRAF              *******


void testDate01()
{
    Date today;     // Define an instance of the 'Date' class

    int loMonth;    // Local variable for month
    int loDay;      // Local variable for day
    int loYear;     // Local variable for year

    //Take in values for the local variables
    cout << "Please enter the month: ";
    cin >> loMonth;
    cout << "Please enter the day: ";
    cin >> loDay;
    cout << "Please enter the year: ";
    cin >> loYear;

    //store the date in the 'today' object
    today.setMonth(loMonth);
    today.setDay(loDay);
    today.setYear(loYear);

    today.display(); //output

    /*** Test the getters *****
    cout << "\n\nThe following lines are the test for the getters:\n";
    cout << today.getMonth() << "\n";
    cout << today.getDay()   << "\n";
    cout << today.getYear()  << "\n\n\n";
    ***************************/

    /***Tests the calcLeapYear member function
    cout << "The following blocks are tests for the calcLeapYear member function:";
    today.setYear(1900);
    today.display();
    today.setYear(2000);
    today.display();
    today.setYear(1999);
    today.display();
    today.setYear(1996);
    today.display();
}

/*** Constructor [off] ******
/// tests the constructors
void testDate02()
{
     Date d1;
     d1.display();
     Date d2(5, 15, 1992);
     d2.display();
}

///Tests the default constructor
void testDate03()
{
    cout << "The following outputs are tests for the constructor";
    Date d3;

    //Tests the calcDayOfYear() function
    d3.setMonth(1);
    d3.setDay(1);
    d3.setYear(1999);
    d3.display();
    d3.setYear(2000);
    d3.display();
    d3.setMonth(12);
    d3.setDay(31);
    d3.display();
    d3.setYear(1999);
    d3.display();
    d3.setMonth(2);
    d3.setDay(28);
    d3.display();
    //d3.setYear(2000);
    //d3.display();
    //d3.setDay(29);
    //d3.display();
    //d3.setMonth(3);
    //d3.setDay(1);
    //d3.display();
    //d3.setYear(1999);
    //d3.display();
}

void testDate05()
{
    Date d01(1, 2000);
    d01.display();
    Date d02(1, 2001);
    d02.display();
    Date d03(59, 2000);
    d03.display();
    Date d04(59, 2001);
    d04.display();
    Date d05(60, 2000);
    d05.display();
    Date d06(60, 2001);
    d06.display();
    Date d07(61, 2000);
    d07.display();
    Date d08(61, 2001);
    d08.display();
    Date d09(366, 2000);
    d09.display();
    Date d10(365, 2001);
    d10.display();
}
***
///Tests the Copy Constructor
void testDate06()
{
    Date d6;
    d6.setMonth(1);
    d6.setDay(1);
    d6.setYear(2000);
    d6.display();


    ///IF THE COPY CONSTRUCTOR WAS NOT IN PLACE THE FOLLOWING LINES
    ///WOULD CAUSE A MEMORY ERROR. THIS WAS THE ONLY WAY I COULD
    ///THINK OF TO TEST THE COPY CONSTRUCTORS
    Date d7;
    d7 = d6;
    d7.display();
}//end of test function

void testDate07()
{
     Date d1(5, 3, 1999); //Error
     cout << "This is Object d1:";
     d1.display();
     cout << "\n\nThis is Object d2:";
     Date d2(4, 6, 2000);
     d2.display();
     cout << "\n\n****  The Following tests the overloaded  ****\n";
     cout <<     "****  '>' and '<' operators               ****\n";
     d1 > d2;
     cout << "\n";
     d1 < d2;
     cout << "\n";
     d2 < d1;
     cout << "\n";
     d2 > d1;

     //Demonstrates the overloaded =operator
     cout << "\n\n\n****  The Following tests the overloaded  ****\n";
     cout <<    "****  '=' operator (d1 = d2)                 ****\n";
     d1 = d2;
     d1.display();

}****/

void testDate09()
{
    Date test(2, 29, 2012);
    test.validateDate();
    Date test2(2, 30, 2012);
    test2.validateDate();
    Date test3(0, 0, 0);
    test3.validateDate();
    Date test4(4, 31, 1999);
    test4.validateDate();
}
