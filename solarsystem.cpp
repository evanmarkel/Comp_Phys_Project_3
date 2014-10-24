    #include "solarsystem.h"

    SolarSystem::SolarSystem()
    {
    }

    void SolarSystem::addCelestialBody(CelestialBody newBody) {
        bodies.push_back(newBody);
    }

        void SolarSystem::makeX(){

            X.resize(4*this->numberOfBodies());
             forces.resize(2*this->numberOfBodies());
             k.resize(4*this->numberOfBodies());
          for(int i =0; i<this->numberOfBodies(); i++){
              this->X[4*i + 0] = this->bodies[i].position[0];
              this->X[4*i + 1] = this->bodies[i].position[1];
              this->X[4*i + 2] = this->bodies[i].velocity[0];
              this->X[4*i + 3] = this->bodies[i].velocity[1];
          }
        }

      std::valarray<double> SolarSystem::calculateForcesAndEnergy(std::valarray<double> X)
        {
            forces = 0;
            kineticEnergy = 0;
            potentialEnergy = 0;
            angularMomentum.setToZero();
            a.setToZero();
            double G = 4*M_PI*M_PI;

                    for(int i=0; i<numberOfBodies(); i++) {
                        CelestialBody &body1 = bodies[i];
                        for(int j=i+1; j<numberOfBodies(); j++) {
                            CelestialBody &body2 = bodies[j];
                                vec3 deltaRVector =  body1.position - body2.position;
                                double dr = deltaRVector.length();
                                double dx = X[4*i + 0] - X[4*j + 0];
                                double dy = X[4*i + 1] - X[4*j + 1];

                            //f is the force acting between body 1 and body 2
                            double f = -(G * body1.mass * body2.mass)/(dr*dr*dr);

                        //a is the force multiplied by the relative position of the two bodies. the movement is added to previous position
                        double axtemp = dx*(f);
                        double aytemp = dy*(f);

                    //forces vector values for body 1
                    forces[2*i + 0] += axtemp;
                    forces[2*i + 1] += aytemp;

                    //forces vector values for body 2
                    forces[2*j + 0] -= axtemp;
                    forces[2*j + 1] -= aytemp;

                    potentialEnergy -= (body1.mass*body2.mass)/dr;
                    }

            kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();

            //angular momentum L = r x v
            double dangularMomentum = body1.position.length() * body1.velocity.length();
           // std::cout << potentialEnergy << " and KE " << kineticEnergy << "and L" << dangularMomentum<< std::endl;
        }
            //calculate Vx Vy.assign to X. also assign forces.
            for (int i =0; i <numberOfBodies(); i++){
                double m = bodies[i].mass;
                k[4*i + 0] = X[4*i +2]; //vx
                k[4*i + 1] = X[4*i +3]; //vy
                k[4*i + 2] = forces[2*i + 0] / m; //Fx/m
                k[4*i + 3] = forces[2*i + 1] / m; //Fy/m
            }
            return k;
    }

    int SolarSystem::numberOfBodies()
    {
        return bodies.size();
    }

    double SolarSystem::totalEnergy()
    {
        return this->kineticEnergy + this->potentialEnergy;
    }
