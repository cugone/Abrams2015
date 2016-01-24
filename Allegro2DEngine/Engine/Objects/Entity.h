#ifndef A2DE_ENTITY_H
#define A2DE_ENTITY_H

#include "../a2de_vals.h"

A2DE_BEGIN

class Entity {
public:
    Entity();
    virtual ~Entity();
protected:
private:
    unsigned int _id;
};

A2DE_END

#endif // A2DE_ENTITY_H
