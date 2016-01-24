#ifndef A2DE_IDRAWABLE_H
#define A2DE_IDRAWABLE_H

#include "../a2de_vals.h"
#include <allegro5/bitmap.h>


A2DE_BEGIN

class IRenderable {
public:

    /**************************************************************************************************
     * <summary>Draws the object given the destination ALLEGRO_BITMAP.</summary>
     * <remarks>Casey Ugone, 5/27/2014.</remarks>
     * <param name="dest">Destination to draw to. Does nothing if dest is null.</param>
     **************************************************************************************************/
    virtual void Render(ALLEGRO_BITMAP* dest) = 0;
    virtual ~IRenderable(){ /* DO NOTHING */ }

    void SetZIndex(unsigned long z_index);
    unsigned long GetZOrder() const;
    unsigned long GetZOrder();

private:
    unsigned long _z_index;
};

A2DE_END

#endif