#ifndef PLANETENTITY_H
#define PLANETENTITY_H

#include <Qt3DCore/qentity.h>
#include "planet.h"

class PlanetEntity : public QObject
{
    Q_OBJECT
public:
    explicit PlanetEntity(Qt3DCore::QEntity *rootEntity);
    ~PlanetEntity();
private:
    Qt3DCore::QEntity *rootEntity;
    // 星球的信息实体
    Planet* plant;



signals:

public slots:
};

#endif // PLANETENTITY_H
