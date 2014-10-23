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
    myfile.open("datasolarsystem5.txt");
    //define step variable h and run length. years are the units
    double h = .1; //step length
    double final_time = 7000; //years
    double G = 4*M_PI*M_PI; //value of Gravitational constant.
    double earthvel = 2*M_PI;

    //earth velocity given by initial condition x = 1AU, vy_e = 2*pi*1AU, mass_e/mass_sun = 3e-6
    SolarSystem mySolarSystem;
    CelestialBody sun(vec3(0,0,0), vec3(0,-.00890885,0), 0.99865924);
    CelestialBody mercury(vec3(-.39,0,0), vec3(0,-1.67*earthvel,0), 1.65e-7);
    CelestialBody venus(vec3(0,.72,0), vec3(1.174*earthvel,0,0), 2.44e-6);
    CelestialBody earth(vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6);
    CelestialBody mars(vec3(0,1.52,0), vec3(.802*earthvel,0, 0), 0.0000003209425513);
    CelestialBody jupiter(vec3(5.2, 0, 0), vec3(0, .434*earthvel, 0), 3e-3);  //Jupiter's orbital velocity is 43% of earth's 1/r^2. or 5.20/12year orbit.
    CelestialBody saturn(vec3(0,-9.54,0), vec3(-.323*earthvel,0, 0), 2.85e-5);
    CelestialBody uranus(vec3(19.19,0,0), vec3(0,.228*earthvel, 0), 4.3e-5);
    CelestialBody neptune(vec3(30.06,0,0), vec3(0,.182*earthvel, 0), 5.516e-5);
    CelestialBody pluto(vec3(0,39.53,0), vec3(.159*earthvel,0, 0), 7.79e-9);


    mySolarSystem.addCelestialBody(sun);
    mySolarSystem.addCelestialBody(mercury);
    mySolarSystem.addCelestialBody(venus);
    mySolarSystem.addCelestialBody(earth);
    mySolarSystem.addCelestialBody(mars);
    mySolarSystem.addCelestialBody(jupiter);
    mySolarSystem.addCelestialBody(saturn);
    mySolarSystem.addCelestialBody(uranus);
    mySolarSystem.addCelestialBody(neptune);
    mySolarSystem.addCelestialBody(pluto);

    mySolarSystem.makeX();
    for(int i = 0; i < final_time/h; i++){

        //perform RK4 for the timescale of observation
        RK4::integrate(mySolarSystem.X,h,mySolarSystem);

        //calculate energies and angular momentum

        //write to file
        myfile  << mySolarSystem.X[0] << " " << mySolarSystem.X[1]<< " " << mySolarSystem.X[4] << " " << mySolarSystem.X[5] << " " << mySolarSystem.X[8] << " "
        << mySolarSystem.X[9] << " " << mySolarSystem.X[12]<< " " << mySolarSystem.X[13] << " " << mySolarSystem.X[16] << " "
        << mySolarSystem.X[17] <<" " << mySolarSystem.X[20] << " " << mySolarSystem.X[21]<< " " << mySolarSystem.X[24] << " " << mySolarSystem.X[25] << " "<< mySolarSystem.X[28] << " "
        << mySolarSystem.X[29] <<" " << mySolarSystem.X[32] << " " << mySolarSystem.X[33]<< " " << mySolarSystem.X[36] << " " << mySolarSystem.X[37] << endl;
    }
    myfile.close();
    for(int i = 0; i < mySolarSystem.bodies.size(); i++) {
        CelestialBody &thisBody = mySolarSystem.bodies[i];
        //cout << "The position of this object is " << thisBody.position << " with velocity " << thisBody.velocity << endl;
    }

    cout << "I just created my first solar system that has " << mySolarSystem.bodies.size() << " objects." << endl;
    return 0;
}

