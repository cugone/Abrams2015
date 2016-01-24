#include "CVertex.h"

A2DE_BEGIN

Vertex::Vertex(Vector3D position, Vector2D uv, const ALLEGRO_COLOR& color ) :
    _position(position),
    _uv(uv),
    _color(color) { }

const Vector3D& a2de::Vertex::GetPosition() const {
    return _position;
}

Vector3D& a2de::Vertex::GetPosition() {
    return const_cast<Vector3D&>(static_cast<const Vertex&>(*this).GetPosition());
}

const Vector2D& a2de::Vertex::GetUV() const {
    return _uv;
}

Vector2D& a2de::Vertex::GetUV() {
    return const_cast<Vector2D&>(static_cast<const Vertex&>(*this).GetUV());
}

const ALLEGRO_COLOR& a2de::Vertex::GetColor() const {
    return _color;
}

ALLEGRO_COLOR& a2de::Vertex::GetColor() {
    return const_cast<ALLEGRO_COLOR&>(static_cast<const Vertex&>(*this).GetColor());
}

A2DE_END
