#include "planet.h"

Planet::Planet(float revolutionR, float revolutionCycle,float obliquity, QString imagePath, float rotationCycle, QString planetName, PlanetType planetType, float planetR):revolutionR(revolutionR),revolutionCycle(revolutionCycle),obliquity(obliquity), imagePath(imagePath), rotationCycle(rotationCycle),planetName(planetName), planetType(planetType), planetR(planetR){
    pixmap = new QPixmap(this->getImagePath());
    this->revolutionAngle = 0;
    this->ownRevolutionAngle = 0;
}

Planet::~Planet(){
    if(pixmap != nullptr){
        delete pixmap;
    }
}

float Planet::getRealRevolutionR(){
    if(PlanetType::MOON ==  planetType){
        return 0.5f;
    }
    return this->revolutionR*1.0f;
}

float Planet::getObliquity(){
    return this->obliquity;
}


QString Planet::getPlantName(){
    return this->planetName;
}

PlanetType Planet::getPlanetType(){
    return this->planetType;
}

QString Planet::getImagePath(){
    return this->imagePath;
}

void Planet::changeRScale(){

}

void Planet::setSubPlanets(QList<Planet*> subPlanets){
    this->subPlanets = subPlanets;
}

QList<Planet*>  Planet::getSubPlanets(){
    return this->subPlanets;
}

QPixmap* Planet::getImage(){
    return this->pixmap;
}

long Planet::getRealPlanetR(){
    return this->planetR;
}

void Planet::setRevolutionAngle(float angle){
    this->revolutionAngle = angle;
}

void Planet::setOwnRevolutionAngle(float angle){
    this->ownRevolutionAngle = angle;
}

float Planet::getRevolutionAngle(){
    return this->revolutionAngle;
}

float Planet::getOwnRevolutionAngle(){
    return this->ownRevolutionAngle;
}

float Planet::calRevolutionAngle(){
    // 按照10ms为1h算
    return 360.0f/this->revolutionCycle*10;
}

float Planet::calOwnRevolutionAngle(){
    return 360.0f/this->rotationCycle;
}
