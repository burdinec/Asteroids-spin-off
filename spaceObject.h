//
//  spaceObject.h
//
//  Created by Chris Burdine on 1/21/21.
//

#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
#include <iostream>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH =3024;
const int SCREEN_HEIGHT = 1964;
const double PI = 3.14159;
const unsigned int MAX_ASTEROIDS = 1;
const int numOfStars = 150;
const int ammo = 5;
const double brakingPower = 2.5;
const double thrust =5;
const double maxVelocity = 40;
const double bulletVelocity = 120;
//int score = 0;


struct Point {
    double x;
    double y;
};

enum SpaceObjType { SHIP, ASTEROID, PHOTON_TORPEDO, STAR };


class SpaceObject {
    
public:
    //default constructor
    SpaceObject();
    //initializes member variables to appropriate values
    SpaceObject(SpaceObjType type, double radius, Point location, Point velocity, double angle);
    
    //==================================================================
    /** --------------------------------------------------------------------------
     *   Draws the spaceobject on the given window
     *
     *     @param win - the window on which we’ll draw the ship
     ---------------------------------------------------------------------------- */
    void draw(sf::RenderWindow& win);
    
    
    
    //mutators
    
    /*------------------------------------------------------------------
     checks to make sure radius is within bounds and adjusts it if needed
     
     @param radius - radius to use in class
     
     @return true
     ------------------------------------------------------------------*/
    bool setRadius(int radius);
    
    /*------------------------------------------------------------------
     Checks to make sure the location is within bounds of the screen and adjusts it if needed
     
     @param x, y - location(x,y) to use in class
     
     @return true
     ------------------------------------------------------------------*/
    bool setLocation(double x, double y);
    
    /*------------------------------------------------------------------
     Checks to make sure the velocity is valid, adjusts it if needed
     
     @param velocityX, velocityY - distance traveled(x) per frame(y)
     
     @return true
     ------------------------------------------------------------------*/
    bool setVelocity(double velocityX, double velocityY);
    
    /*------------------------------------------------------------------
     checks to make sure the angle is between 0 and 360
     
     @param angDeg - angle to be used in class
     
     @return true
     ------------------------------------------------------------------*/
    bool setAngle(double angDeg);
    
    
    //============================================
    //accessors
    
    double getRadius() const;//returns radius variable stored within class
    Point getLocation() const;//returns location struct stored within class
    Point getVelocity() const;//returns velocity struct stored within class
    double getAngle() const;//returns angleDeg variable stored within class
    int getShipPosition() const;
    
    //============================================
    //others
    void updatePosition();//updates position of the given object every frame
    void applyThrust();//applies thrust to given object(ship)
    void applyBrakes();// slow down the object(ship)
    void applyThrustReverse();//applies thrust to given object(ship) in reverse
    void thrustLeft();
    void thrustRight();
    //void shootBullet();
    
    

private:
    SpaceObjType type;      //type of object
    Point location;      //current location (x,y)
    Point velocity;      //current velocity (in pixels/frame)
    double angleDeg;      //angle object is facing (in degrees)
    double radius;        //gross radius of object (for collision detection)
    void drawAsteroid(sf::RenderWindow& win);  //draws SpaceObject: asteroid
    void drawShip(sf::RenderWindow& win);   //draws SpaceObject: ship
    void drawShipThruster(sf::RenderWindow& win);   //draws thruster trailing ship when applied
    void drawStar(sf::RenderWindow& win);
    //void drawBullet(sf::RenderWindow& win);
};




#endif /* spaceObject_h */
