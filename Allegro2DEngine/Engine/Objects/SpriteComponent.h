#ifndef A2DE_SPRITECOMPONENT_H
#define A2DE_SPRITECOMPONENT_H

#include <memory>

#include "../a2de_vals.h"
#include "IComponent.h"

#include "../GFX/CSprite.h"

A2DE_BEGIN

class SpriteComponent : public a2de::IComponent {
public:
	SpriteComponent() = default;
	virtual ~SpriteComponent() = default;
	virtual void Update(double deltaTime) override;

	std::unique_ptr<a2de::Sprite> _sprite;

protected:
private:

};

A2DE_END

#endif