#ifndef A2DE_DIMENSIONSCOMPONENT_H
#define A2DE_DIMENSIONSCOMPONENT_H


#include "../a2de_vals.h"
#include "IComponent.h"

#include "../Math/CVector2D.h"

A2DE_BEGIN

class DimensionsComponent : a2de::IComponent {
public:
	DimensionsComponent() = default;
	virtual ~DimensionsComponent() = default;

	virtual void Update(double deltaTime) override;

	a2de::Vector2D dimensions;

protected:
private:

};

A2DE_END


#endif