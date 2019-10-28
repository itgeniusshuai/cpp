#include "planetentity.h"

PlanetEntity::PlanetEntity(Qt3DCore::QEntity *rootEntity) : rootEntity(rootEntity)
{

}

PlanetEntity::~PlanetEntity(){
    if( plant != nullptr){
            delete plant;
    }
}
