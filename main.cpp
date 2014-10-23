#include <iostream>
#include <cmath>
#include <fstream>

#include <solarsystem.h>
#include <rk4.h>
//#include <armadillo>
#include <valarray>
using namespace std;
//using namespace arma;

int main()
{
    ofstream myfile;
    myfile.open("data.txt");
    //define step variable h and run length. years are the units
    int N = 1000000; //number of steps over 10,000 years
    double h = .001; //step length
    double initial = 0; //years
    double final_time = 10000; //years
    double G = 1; //value of G.

    //earth velocity given by initial condition x = 1AU, vy_e = 2*pi*1AU, mass_e/mass_sun = 3e-6
    SolarSystem mySolarSystem;
    CelestialBody sun(vec3(0,0,0), vec3(0,0,0), 1.0);
    CelestialBody earth(vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6);
    //CelestialBody jupiter(vec3(1,0,0), vec3(0,2*M_PI, 0), 1e-3);

    mySolarSystem.addCelestialBody(sun);
    mySolarSystem.addCelestialBody(earth);
   // mySolarSystem.addCelestialBody(jupiter);

    mySolarSystem.makeX();
    for(int i = 0; i < final_time; i++){

        //perform RK4 for the timescale of observation
        RK4::integrate(mySolarSystem.X,h,mySolarSystem);

        //write to file
        myfile  << mySolarSystem.X[4] << " " << mySolarSystem.X[5] << endl;
    }
    myfile.close();
    for(int i = 0; i < mySolarSystem.bodies.size(); i++) {
        CelestialBody &thisBody = mySolarSystem.bodies[i];
        cout << "The position of this object is " << thisBody.position << " with velocity " << thisBody.velocity << endl;
    }

    cout << "I just created my first solar system that has " << mySolarSystem.bodies.size() << " objects." << endl;
    return 0;
}

