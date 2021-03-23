#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

static constexpr int const SUCCESS = 0;
static constexpr int const ERROR = -1;
static constexpr double long const ALPHA = 0.012299;
static constexpr double long const BETA = 1 - ALPHA;
static constexpr char const First = 'x';
static constexpr char const Second = 'y';

using namespace std;

bool Position(long double &x, long double &y)
{

    cout << "Enter initial pos " << First << ":\n" << flush;


    try
    {
        if (!(cin >> x))
        {
            throw (First);
        }
        cout << "Enter initial pos " << Second << ":\n" << flush;

        if (!(cin >> y))
        {
            throw (Second);
        }

        return true;
    }
    catch (char Letter)
    {
        exit(ERROR);
    }

}

bool Velocity(long double &x, long double &y)
{

    cout << "Enter initial vel " << First << ":\n" << flush;


    try
    {
        if (!(cin >> x))
        {
            throw (First);
        }
        cout << "Enter initial vel " << Second << ":\n" << flush;

        if (!(cin >> y))
        {
            throw (Second);
        }
        return true;

    }
    catch (char Letter)
    {
        exit(ERROR);
    }

}

bool TimeCheck(long double &T)
{
    cout << "Enter total time T:\n" << flush;

    if (cin >> T && T > 0)
    {
        return true;
    }
    else
    {
        exit(ERROR);
    }
}

bool Steps(long double &x, long double &y)
{

    cout << "Enter num of steps:\n" << flush;

    try
    {
        if (!(cin >> x))
        {
            throw (First);
        }

        cout << "Enter num of steps to save:\n" << flush;

        if (!(cin >> y))
        {
            throw (Second);
        }
        return true;
    }
    catch (char Letter)
    {
        exit(ERROR);
    }

}

bool CheckAllInputs(double long &PositionX, double long &PositionY, double long &VelocityX, double long &VelocityY,
                    double long &T, double long &nStep, double long &mSteps)
{

    if (Position(PositionX, PositionY) && Velocity(VelocityX, VelocityY) && Steps(nStep, mSteps) && TimeCheck(T))
    {


        return true;

    }
}

void CalculateOstroff(double long &PositionX, double long &PositionY, double long &VelocityX, double long &VelocityY,
                      double long &T, double long &nStep, double long &mStepsForPrint, double long &Distance1,
                      long double &Distance2, long double &AccelerationX, long double &AccelerationY)
{
    long double DT = T / nStep;
    for (int i = 0; i < nStep; i++)//divide nicely
    {
        Distance1 = pow((pow(PositionX + ALPHA, 2)) + (PositionY * PositionY), (1.5));
        Distance2 = pow((pow(PositionX - BETA, 2)) + (PositionY * PositionY), (1.5));

        AccelerationX = PositionX + 2 * VelocityY - BETA * (PositionX + ALPHA) / Distance1 -
                        ALPHA * (PositionX - BETA) / Distance2;
        AccelerationY = PositionY - 2 * VelocityX - BETA * PositionY / Distance1 - ALPHA * PositionY / Distance2;


        PositionX += DT * VelocityX;
        PositionY += DT * VelocityY;

        VelocityX += DT * AccelerationX;
        VelocityY += DT * AccelerationY;


        if (fmod(nStep, mStepsForPrint) == 0)
        {
            cout << "x new position is " << PositionX << "\ny new position is  "
                 << PositionY << endl;
        }
    }
}

int main()
{
    double long Distance1, Distance2, AccelerationX, AccelerationY = 0;///Parameters that are unnecessarily repeated not needed to be in main but funk
    cout << "\n\tPlease follow the steps ahead carefully\n\t" << endl;
    double long PositionX, PositionY, T, VelocityX, VelocityY, nStep, mSteps = 0;//if positive to unsigned
    int UserChoice = 0;
    cout << "\n\tWould you like to: "
            "\n\t1.give in the details one by one"
            "\n\t2.via uploaded file\n" << flush;
    cin >> UserChoice;

    switch (UserChoice)
    {
        case 1:


            if (CheckAllInputs(PositionX, PositionY, VelocityX, VelocityY, T, nStep, mSteps))
            {
                CalculateOstroff(PositionX, PositionY, VelocityX, VelocityY, T, nStep, mSteps, Distance1, Distance2,
                                 AccelerationX, AccelerationY);
            }
            break;

        case 2:
            string FileLocation;
            cout << "\n\tWhere is the file please?\n" << flush;
            if (cin >> FileLocation)
            {

                fstream my_file;
                my_file.open(FileLocation, ios::in);
                long double ReadFile;
                string Line = "";
                char Stop = ',';

                do
                {
                    std::istringstream Read(Line);
                    Read >> Line;
                    Read >> Stop;

                    if (Read >> Stop)
                    {
                        PositionX = stold(Line);
                    }
                    if (Read >> Stop)
                    {
                        PositionY = stold(Line);
                    }
                    if (Read >> Stop)
                    {
                        PositionX = stold(Line);
                    }
                    if (Read >> Stop)
                    {
                        VelocityX = stold(Line);
                    }
                    if (Read >> Stop)
                    {
                        VelocityY = stold(Line);
                    }
                    if (Read >> Stop)
                    {
                        T = stold(Line);
                    }
                    if (Read >> Stop)
                    {
                        nStep = stold(Line);
                    }
                    if (Read >> Stop)
                    {
                        mSteps = stold(Line);
                    }

                    if (my_file.eof())
                    {
                        break;
                    }

                    cout << ReadFile;
                } while (true);

                my_file.close();

                if (CheckAllInputs(PositionX, PositionY, VelocityX, VelocityY, T, nStep, mSteps))
                {
                    CalculateOstroff(PositionX, PositionY, VelocityX, VelocityY, T, nStep, mSteps, Distance1,
                                     Distance2, AccelerationX, AccelerationY);
                }
                break;
            }
            else
            {
                exit(ERROR);
            }
    }
    return SUCCESS;
}
/**************************
 TODO create read file function as stated in the exercise
TODO check all functions and calculations

 check conventions

 x%y
 */