/**************************************************************************************************
// file:	Engine\GFX\CBitmapCache.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the bitmap cache class
 **************************************************************************************************/
#ifndef A2DE_CBITMAPCACHE_H
#define A2DE_CBITMAPCACHE_H

#include "../a2de_vals.h"
#include "../a2de_base.h"

#include <memory>
#include <map>
#include <utility>
#include <string>

struct ALLEGRO_BITMAP;

A2DE_BEGIN

/**************************************************************************************************
 * <summary>Bitmap pool.</summary>
 * <remarks>Casey Ugone, 8/2/2011.</remarks>
 **************************************************************************************************/
class BitmapCache {

    BitmapCache() = default;
    ~BitmapCache() = default;
    BitmapCache(const BitmapCache& other) = delete;
    BitmapCache(BitmapCache&& rother) = delete;
    BitmapCache& operator=(const BitmapCache& rhs) = delete;
    BitmapCache& operator=(BitmapCache&& rrhs) = delete;

    /**************************************************************************************************
     * <summary>Pulls the requested bitmap from the cache if it has already been loaded, else it loads and stores it first.</summary>
     * <remarks>Casey Ugone, 8/2/2011.</remarks>
     * <remarks>The caller is responsible for destroying the ALLEGRO_BITMAP.</remarks>
     * <param name="filename">Path and Filename of the file.</param>
     * <returns>null if it fails, else the ALLEGRO_BITMAP.</returns>
     **************************************************************************************************/
    static std::weak_ptr<ALLEGRO_BITMAP> GetBitmap(const std::string& filename) noexcept ;

    /// <summary> The BITMAP cache:
    ///           std::string: The name or filepath of the ALLEGRO_BITMAP.
    ///           long: The total number of references of the name.
    ///           ALLEGRO_BITMAP*: The stored pixel data.</summary>
    static std::map<std::string, std::shared_ptr<ALLEGRO_BITMAP>> _cache;

    friend class Sprite;
    friend class TileSet;
    friend void a2de_deinit();

private:
    
};

A2DE_END

#endif