#ifndef A2DE_ICOMPONENT_H
#define A2DE_ICOMPONENT_H

#include "../a2de_vals.h"

A2DE_BEGIN

class IComponent {
public:
    virtual void Update(double deltaTime) = 0;
    virtual ~IComponent() { /* DO NOTHING */ };
protected:
private:
    
};

A2DE_END

#endif // A2DE_ICOMPONENT_H
