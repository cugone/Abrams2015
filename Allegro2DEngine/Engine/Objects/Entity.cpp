#include "Entity.h"

A2DE_BEGIN

void Entity::Update(double deltaTime) {
	for(auto& elem : _components) {
		elem->Update(deltaTime);
	}
}

A2DE_END