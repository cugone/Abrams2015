#ifndef A2DE_TRANSFORMCOMPONENT_H
#define A2DE_TRANSFORMCOMPONENT_H

#include "../a2de_vals.h"
#include "IComponent.h"

#include "../Math/CTransform2D.h"

A2DE_BEGIN

class TransformComponent : a2de::IComponent {
public:
    TransformComponent();
    virtual ~TransformComponent();

    virtual void Update(double deltaTime) override;

protected:
private:
    a2de::Transform2D _transform;
};

A2DE_END

#endif // A2DE_TRANSFORMCOMPONENT_H
