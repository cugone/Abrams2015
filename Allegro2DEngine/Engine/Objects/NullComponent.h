#ifndef A2DE_NULLCOMPONENT_H
#define A2DE_NULLCOMPONENT_H

#include "../a2de_vals.h"
#include "IComponent.h"

A2DE_BEGIN

class NullComponent : a2de::IComponent {
public:
    NullComponent();
    virtual ~NullComponent();

    virtual void Update(double deltaTime) override;

protected:
private:
    
};

A2DE_END

#endif // A2DE_NULLCOMPONENT_H
