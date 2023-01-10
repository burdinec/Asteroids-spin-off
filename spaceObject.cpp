//
//  spaceObject.cpp
//  
//  Created by Chris Burdine on 1/21/21.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "spaceObject.h"

SpaceObject::SpaceObject(SpaceObjType type, double radius, Point location, Point velocity, double angle){
    this->type = type;
    this->radius = radius;
    this->location = location;
    this->velocity = velocity;
    this->angleDeg = angle;
};

double SpaceObject::getRadius() const{
    return radius;
}

Point SpaceObject::getLocation() const{
    return location;
}

Point SpaceObject::getVelocity() const{
    return velocity;
}

double SpaceObject::getAngle() const{
    return angleDeg;
}



void SpaceObject::updatePosition(){
    location.x = location.x + velocity.x;
    location.y = location.y + velocity.y;
    
    setLocation(location.x, location.y);
}

bool SpaceObject::setRadius(int radius){
    this->radius = radius;
    if (radius < 1 || radius > SCREEN_HEIGHT/2) {
        return false;
    }
    else
        return true;
}

bool SpaceObject::setLocation(double x, double y){
    while (x < 0)
        x += SCREEN_WIDTH;
    while (x > SCREEN_WIDTH)
        x -= SCREEN_WIDTH;
    this->location.x = x;
    while (y < 0)
        y += SCREEN_HEIGHT;
    while (y > SCREEN_HEIGHT){
        y -= SCREEN_HEIGHT;
        if (this->type == ASTEROID) {
            location.x += rand() % SCREEN_WIDTH;
            y -= SCREEN_HEIGHT-160;
        }
    }
    this->location.y = y;
        
    return true;
}

bool SpaceObject::setVelocity(double velocityX, double velocityY){
    this->velocity.x = velocity.x;
    this->velocity.y = velocity.y;
    return true;
}

bool SpaceObject::setAngle(double angle){
    if (angle > 360) {
        angle--;
    }
    if (angle < 360) {
        angle++;
    }
    angleDeg = angle;
    
    
    return true;
}

void SpaceObject::draw(sf::RenderWindow& win) {
    if (type==SHIP)
        drawShip(win);
    else if (type==ASTEROID)
        drawAsteroid(win);
    else if (type==STAR)
        drawStar(win);
    //else if (type==BULLET)
      //  drawBullet(win);
}

void SpaceObject::drawStar(sf::RenderWindow &win){
    int points = 8;
    int radius = this->radius;
    sf::CircleShape photon(radius, points);
    sf::Vector2f midpoint(radius, radius);
    photon.setOrigin(midpoint);
    photon.setFillColor(sf::Color(255, 255, 255));
    photon.setOutlineThickness(1);
    photon.setOutlineColor(sf::Color(255, 255, 255));
    photon.setPosition(location.x, location.y);
    win.draw(photon);
}
/**
void SpaceObject::drawBullet(sf::RenderWindow &win){
    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("/Users/chris/Library/Developer/Xcode/DerivedData/spaceObject-grodossjmpkpascdhmcmorwqdvky/Build/Products/Debug/bullet.png")) {
        return;
    }
    sf::Image pixels;
    bulletTexture.update(pixels);
    sf::Sprite bullet;
    bullet.setTexture(bulletTexture);
    bullet.scale(.09, .08);
    bullet.setPosition(location.x, location.y);
    bullet.setRotation(angleDeg);
    win.draw(bullet);
}
**/
void SpaceObject::drawAsteroid(sf::RenderWindow& win) {
    sf::Texture asteroidTexture;
    if (!asteroidTexture.loadFromFile("/Users/chris/Library/Developer/Xcode/DerivedData/spaceObject-grodossjmpkpascdhmcmorwqdvky/Build/Products/Debug/asteroid1.png")) {
        return;
    }
    sf::Image pixels;
    asteroidTexture.update(pixels);
    sf::Sprite asteroid;
    asteroid.scale(.5, .5);
    asteroid.setTexture(asteroidTexture);
    asteroid.setPosition(location.x-400, location.y-400);
    asteroid.setRotation(angleDeg);
    win.draw(asteroid);
    
}

void SpaceObject::drawShip(sf::RenderWindow& win) {
    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("/Users/chris/Library/Developer/Xcode/DerivedData/spaceObject-grodossjmpkpascdhmcmorwqdvky/Build/Products/Debug/pngkey.com-spaceship-png-130236.png")) {
        return;
    }
    sf::Image pixels;
    shipTexture.update(pixels);
    sf::Sprite ship;
    ship.setTexture(shipTexture);
    ship.scale(.25, .25);
    ship.setPosition(location.x-140, location.y+50);
    ship.rotate(angleDeg);
    win.draw(ship);
}

void SpaceObject::thrustLeft(){
    if(velocity.x > -maxVelocity){
        velocity.x = velocity.x - thrust;
        angleDeg = -5;
    }
}

void SpaceObject::thrustRight(){
    if (velocity.x < maxVelocity){
        velocity.x = velocity.x + thrust;
        angleDeg = 5;
    }
}

void SpaceObject::applyBrakes(){    
    if  (velocity.x >= 0) {
        velocity.x -= brakingPower;
    }
    if (velocity.x <= 0) {
        velocity.x += brakingPower;
    }
    
    this->angleDeg = 0;
}

/**void SpaceObject::applyThrust(){
    double engineThrust = .3;
    double forcex= cos((angleDeg-90)*PI/180) * engineThrust;
    double forcey= sin((angleDeg-90)*PI/180) * engineThrust;
    velocity.x = velocity.x + forcex;
    velocity.y = velocity.y + forcey;
}
**/
