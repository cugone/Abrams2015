#include "CRenderManager.h"

#include <vector>

#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/bitmap_lock.h>
#include <allegro5/color.h>
#include <allegro5/drawing.h>

#include "../Math/CShape.h"
#include "../Math/CArc.h"
#include "../Math/CCircle.h"
#include "../Math/CEllipse.h"
#include "../Math/CLine.h"
#include "../Math/CPoint.h"
#include "../Math/CPolygon.h"
#include "../Math/CRectangle.h"
#include "../Math/CSector.h"
#include "../Math/CSpline.h"
#include "../Math/CTriangle.h"
#include "../Math/CVertex.h"

#include "IRenderable.h"
#include "CSprite.h"
#include "../Objects/Entity.h"

//TODO: Uncomment RenderManager functions after testing window.
A2DE_BEGIN

RenderManager::RenderManager(ALLEGRO_DISPLAY& display) : _display_context(&display) { /* DO NOTHING */ }

RenderManager::~RenderManager() {
    _display_context = nullptr;
}

//void RenderManager::RenderObject(Entity* object) {
//    if(object == nullptr) return;
//    object->Render(al_get_backbuffer(_display_context));
//}
//
void RenderManager::RenderObject(const Sprite& sprite) {
    sprite.Draw(al_get_backbuffer(_display_context));
}

void RenderManager::RenderObject(const Shape& shape, bool filled, ALLEGRO_BITMAP* texture) {
    //shape->Render(al_get_backbuffer(_display_context));
    auto& verts = shape.GetVerticies();
    std::vector<ALLEGRO_VERTEX> allegro_verts;
	allegro_verts.reserve(verts.size());
    for(const auto& v : verts) {
        auto p = a2de::Math::ToScreenScale(v.GetPosition());
        auto uv = v.GetUV();
        auto c = v.GetColor();
        allegro_verts.push_back(
                        std::move(ALLEGRO_VERTEX{
                            static_cast<float>(p.GetX()),
                            static_cast<float>(p.GetY()),
                            static_cast<float>(p.GetZ()),
                            static_cast<float>(uv.GetX()),
                            static_cast<float>(uv.GetY()),
                            c
                        }));
    }
    switch(shape.GetShapeType()) {
        case Shape::ShapeType::Point: {
            al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_POINT_LIST);
            break;
        } case Shape::ShapeType::Line: {
            al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_LINE_LIST);
            break;
        } case Shape::ShapeType::Rectangle: {
            filled ?
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_TRIANGLE_LIST)
                :
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_LINE_LOOP);
            break;
        } case Shape::ShapeType::Circle: {
            filled ?
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_TRIANGLE_FAN)
                :
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_POINT_LIST);
            break;
        } case Shape::ShapeType::Ellipse: {
            filled ?
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_TRIANGLE_FAN)
                :
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_POINT_LIST);
            break;
        } case Shape::ShapeType::Triangle: {
            filled ?
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_TRIANGLE_LIST)
                :
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_LINE_LOOP);
            break;
        } case Shape::ShapeType::Arc: {
            al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_LINE_STRIP);
            break;
        } case Shape::ShapeType::Polygon: {
            filled ?
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_TRIANGLE_FAN)
                :
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_LINE_LOOP);
            break;
        } case Shape::ShapeType::Spline: {
            al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_LINE_STRIP);
            break;
        } case Shape::ShapeType::Sector: {
            filled ?
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_TRIANGLE_FAN)
                :
                al_draw_prim(allegro_verts.data(), nullptr, texture, 0, allegro_verts.size(), ALLEGRO_PRIM_LINE_LOOP);
            break;
        } default: {
            /* DO NOTHING: All cases handled */;
        }
    }
}

void RenderManager::RenderObject(IRenderable& renderable) {
    renderable.Render(al_get_backbuffer(_display_context));
}

//void RenderManager::RenderObjectAt(Entity* object, const a2de::Vector2D& screen_position) {
//    if(object == nullptr) return;
//    a2de::Vector2D old_pos(object->GetBody()->GetPosition());
//    object->GetBody()->SetPosition(screen_position);
//    object->Render(al_get_backbuffer(_display_context));
//    object->GetBody()->SetPosition(old_pos);
//}
//
void RenderManager::RenderObjectAt(Sprite& sprite, const a2de::Vector2D& screen_position) {
    a2de::Vector2D old_pos(sprite.GetPosition());
    sprite.SetPosition(screen_position);
    sprite.Draw(al_get_backbuffer(_display_context));
    sprite.SetPosition(old_pos);
}

void RenderManager::RenderObjectAt(Shape& shape, const a2de::Vector2D& screen_position, bool filled) {
    a2de::Vector2D old_pos(shape.GetPosition());
    shape.SetPosition(screen_position);
    RenderObject(shape, filled);
    shape.SetPosition(old_pos);
}


A2DE_END
