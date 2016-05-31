#ifndef A2DE_ENTITY_H
#define A2DE_ENTITY_H

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "../a2de_vals.h"
#include "IComponent.h"
#include "NullComponent.h"

A2DE_BEGIN

class Entity {
public:
    Entity() = default;
	Entity(const Entity& other) = default;
	Entity& operator=(const Entity& rhs) = default;
	Entity(Entity&& r_rhs) = default;
	Entity& operator=(Entity&& r_rhs) = default;
    ~Entity() = default;

    template<typename C, typename... Args>
    void AddComponent(Args&&... args);

    template<typename C>
    const C& GetComponent() const;
    
    template<typename C>
    C& GetComponent();

	void Update(double deltaTime);

protected:
private:

    template<typename C, typename... Args>
    void AddComponent_helper(Args&&... args, std::false_type);

    template<typename C, typename... Args>
    void AddComponent_helper(Args&&... args, std::true_type);
    
    unsigned int _id;
    std::vector<std::unique_ptr<IComponent>> _components;
    a2de::NullComponent _null_component;
};

template<typename C, typename... Args>
void Entity::AddComponent(Args&&... args) {
    return AddComponent_helper(args, typename std::is_base_of<a2de::IComponent, C>::type);
}

template<typename C, typename... Args>
void Entity::AddComponent_helper(Args&&... args, std::false_type) {
    return;
}

template<typename C, typename... Args>
void Entity::AddComponent_helper(Args&&... args, std::true_type) {
    _components.push_back(std::make_unique<C>(std::forward<Args>(args)...));
}

template<typename C>
const C& Entity::GetComponent() const {
    for(auto& uc : _components) {
        auto* c = dynamic_cast<C*>(uc.get());
        if(c && std::is_base_of<a2de::IComponent&, C&>().value && std::is_same<decltype(c), C&>().value) {
            return *c;
        }
    }
    throw _null_component;
}

template<typename C>
C& Entity::GetComponent() {
    return const_cast<C&>(static_cast<const Entity&>(*this).GetComponent<C>());
}

A2DE_END

#endif // A2DE_ENTITY_H
