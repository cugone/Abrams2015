#ifndef A2DE_CVERTEX_H
#define A2DE_CVERTEX_H

#include "../a2de_vals.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

#include "CVector3D.h"
#include "CVector2D.h"

A2DE_BEGIN

class Vertex {
public:
    Vertex(const Vertex& other) = default;
    Vertex(Vertex&& rrhs) = default;
    Vertex& operator=(const Vertex& rhs) = default;
    Vertex& operator=(Vertex&& rhs) = default;
    Vertex(Vector3D position = Vector3D(), Vector2D uv = Vector2D(), const ALLEGRO_COLOR& color = { 0.0, 0.0, 0.0, 1.0 });
    ~Vertex() = default;

    const Vector3D& GetPosition() const;
    Vector3D& GetPosition();

    const Vector2D& GetUV() const;
    Vector2D& GetUV();

    const ALLEGRO_COLOR& GetColor() const;
    ALLEGRO_COLOR& GetColor();

protected:
private:

    Vector3D _position;
    Vector2D _uv;
    ALLEGRO_COLOR _color;
};

A2DE_END

#endif // A2DE_CVERTEX_H
