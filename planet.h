#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <QList>
#include <QPixmap>

enum class PlanetType{
    FIXED,PLANET,MOON
};

class Planet
{
public:
    Planet(float revolutionR, float revolutionCycle,float obliquity, QString imagePath, float rotationCycle, QString planetName, PlanetType plantType, float planetR);
    float getRealRevolutionR();
    int getRealRevolutionCycle();
    int getRealRotationCycle();
    float calOwnRevolutionAngle();
    float calRevolutionAngle();

    // geter/setter方法   
    void changeRScale();
    QString getPlantName();
    PlanetType getPlanetType();
    QString getImagePath();
    void setSubPlanets(QList<Planet*> subPlanets);
    QList<Planet*> getSubPlanets();
    QPixmap* getImage();
    long getRealPlanetR();
    float getRevolutionAngle();
    void setRevolutionAngle(float angle);
    float getOwnRevolutionAngle();
    void setOwnRevolutionAngle(float angle);
    float getObliquity();
private:
    // 公转半径(km)
    float revolutionR;
    // 公转周期(h)
    float revolutionCycle;
    // 黄赤交角
    float obliquity;
    // 图片
    QString imagePath;
    // 自转周期(h)
    float rotationCycle;
    // 子星球
    QList<Planet*> subPlanets;
    // 星球名称
    QString planetName;
    // 星球类型
    PlanetType planetType;
    // 星球本身半径
    float planetR;
    // 图片指针
    QPixmap* pixmap;
    // 公转偏移角度
    float revolutionAngle;
    // 自转偏转角度
    float ownRevolutionAngle;


};

#endif // PLANET_H
