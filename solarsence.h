#ifndef SOLARSENCE_H
#define SOLARSENCE_H

#include <QObject>
#include <QList>
#include "planetentity.h"

class SolarSence : public QObject
{
    Q_OBJECT
public:
    explicit SolarSence(QObject *parent = nullptr);

signals:

public slots:

private:
    // 所有星星
    QList<PlanetEntity*> planetEntities;
};

#endif // SOLARSENCE_H
