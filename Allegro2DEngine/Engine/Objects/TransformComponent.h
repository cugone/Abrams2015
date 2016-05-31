#ifndef A2DE_TRANSFORMCOMPONENT_H
#define A2DE_TRANSFORMCOMPONENT_H

#include "../a2de_vals.h"
#include "IComponent.h"

#include "../Math/CTransform2D.h"

A2DE_BEGIN

class TransformComponent : a2de::IComponent {
public:
    TransformComponent() = default;
    virtual ~TransformComponent() = default;

    virtual void Update(double deltaTime) override;

    a2de::Transform2D transform;
protected:
private:
    
};

A2DE_END

#endif // A2DE_TRANSFORMCOMPONENT_H
