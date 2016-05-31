#ifndef A2DE_PHYSICSCOMPONENT_H
#define A2DE_PHYSICSCOMPONENT_H

#include <utility>
#include <vector>

#include "../a2de_vals.h"
#include "IComponent.h"
#include "../Math/CVector2D.h"
#include "../Physics/CRigidBody.h"

A2DE_BEGIN

class PhysicsComponent : IComponent {
public:
    PhysicsComponent() = default;
    virtual ~PhysicsComponent() = default;

    virtual void Update(double deltaTime) override;

    a2de::RigidBody body;

protected:
private:
    
};

A2DE_END

#endif