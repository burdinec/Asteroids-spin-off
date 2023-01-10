//
//  game.cpp
//  spaceObject
//
//  Created by Chris Burdine on 1/30/21.
//

#include <SFML/Graphics.hpp>
#include "spaceObject.h"
#include <cmath>

Point getRandomLocation();
double getRandomAngle(int x);
Point getRandomVelocity();
double getRandomRadius();
Point getRandomLocationAsteroid();
Point getRandomVelocityAsteroid();
double getRandomRadiusAsteroid();
//bool objectIntersect(SpaceObject* obj1, SpaceObject* obj2);
//============================================================================
int main()
{
    //create graphics window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Asteroids!",sf::Style::Default | sf::Style::Close);
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(false);
    
    //create SpaceObjects
    SpaceObject* ship = NULL;
    SpaceObject* star[numOfStars] = {0};
    SpaceObject* asteroid[MAX_ASTEROIDS] = {0};
    //                     Type, Radius,       Location,           Velocity,  Angle
    ship = new SpaceObject(SHIP, 100, {((SCREEN_WIDTH/2)-50), 1250}, {0,0},     0);
   
    //creates non null entries of stars array
    for (int x = 0; x < numOfStars; x++) {
        star[x] = new SpaceObject(STAR, getRandomRadius(), getRandomLocation(), getRandomVelocity(), 0);
    }
    
    // creates non null entries of the asteroid array
    for (int x = 0; x < MAX_ASTEROIDS; x++) {
        asteroid[x] = new SpaceObject(ASTEROID, getRandomRadiusAsteroid(), getRandomLocationAsteroid(), {0, 35}, getRandomAngle(x));
    }
    //srand(10);
    //SpaceObject* bullet = {NULL};
    //game loop
    //bool shootBullet = false;
    while (window.isOpen())
    {
        //handle user input (events and keyboard keys being pressed) ----
        sf::Event event;
        while (window.pollEvent(event))    {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            ship->thrustLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            ship->thrustRight();
        }
        else {
            ship->applyBrakes();
        }
        /**if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            shootBullet = true;
            bullet = new SpaceObject(BULLET, 10, {(ship->getLocation().x)-7, (ship->getLocation().y+110)}, {0,-bulletVelocity}, 125.5);
            
        }
        **/
        // update game objects & draw new frame
        
        for (int x = 0; x < numOfStars; x++) {
            star[x]->draw(window);
        }
        for (int x = 0; x < numOfStars; x++) {
            star[x]->updatePosition();
        }
        /**
        if (shootBullet) {
            if (bullet->getLocation().y > 50) {
                bullet->updatePosition();
                bullet->draw(window);
            }
        }
        **/
            for (int x = 0; x < MAX_ASTEROIDS; x++) {
                asteroid[x]->draw(window);
                asteroid[x]->updatePosition();
        }
        ship->updatePosition();
        ship->draw(window);
        
        window.display();
        
    }
    //delete bullet;
    delete ship;
    for (int x = 0; x < numOfStars; x++){
        delete star[x];
    }
    return 0;
}

/*
 Generates a random location
 */
Point getRandomLocation()
{
    Point temp;
    temp.x = rand() % SCREEN_WIDTH;
    temp.y = rand() % SCREEN_HEIGHT;
    return temp;
}

/*
 Generates a random velocity within a certain range
 */
Point getRandomVelocity()
{
    Point temp;
    temp.x = 0;
    temp.y = (rand() % 50) +5;
    return temp;
}

/*
 Generates a random radius within certain range to draw asteroids
 */
double getRandomRadius()
{
    double radius;
    radius = (rand() % 3);
    return radius;
}

double getRandomRadiusAsteroid(){
    double radius;
    radius = (rand() % 200) +100;
    return radius;
}

Point getRandomLocationAsteroid()
{
    Point temp;
    temp.x = rand() % SCREEN_WIDTH + 30;
    temp.y = 0;
    return temp;
}

Point getRandomVelocityAsteroid(){
    Point temp;
    temp.x = (rand() % 10);
    temp.y = (rand() % 20) +5;
    return temp;
}

double getRandomAngle(int x){
    srand(x);
    double temp;
    temp = (rand() % 360);
    return temp;
}
/*
 Determines whether the ship and an asteroid have collided each frame
 */
//Program wont compile with this implemented, Get an error on my getLocation() function------------------------------
/**
bool objectIntersect(SpaceObject* obj1, SpaceObject* obj2)
{
    Point obj1Location = obj1->getLocation();

    Point obj2Location = obj2->getLocation();
    
    int obj1Radius = obj1->getRadius();
    std::cout << obj1Radius << '\n';

    int obj2Radius = obj2->getRadius();
    std::cout << obj2Radius << '\n';
    double distance = sqrt((pow((obj1Location.x - obj2Location.x), 2) + ((pow(obj1Location.y - obj2Location.y, 2)))));
    double radii = obj1Radius + obj2Radius;
    if (distance < radii)
    {
        return true;
    }
    
    return false;
}
**/


