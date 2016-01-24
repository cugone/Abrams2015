#include "IRenderable.h"

void a2de::IRenderable::Render(ALLEGRO_BITMAP* /*dest*/) {
    /* DO NOTHING */
}

void a2de::IRenderable::SetZIndex(unsigned long z_index) {
    _z_index = z_index;
}

unsigned long a2de::IRenderable::GetZOrder() const {
    return _z_index;
}

unsigned long a2de::IRenderable::GetZOrder() {
    return static_cast<const IRenderable&>(*this).GetZOrder();
}
