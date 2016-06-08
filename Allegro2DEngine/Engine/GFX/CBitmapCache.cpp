/**************************************************************************************************
// file:	Engine\GFX\CBitmapCache.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the bitmap cache class
 **************************************************************************************************/
#include "CBitmapCache.h"

#include <iostream>
#include <algorithm>
#include <experimental/filesystem>
#include <map>

#include <allegro5/bitmap.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/allegro_image.h>
#include <allegro5/fshook.h>

A2DE_BEGIN

std::map<std::string, std::shared_ptr<ALLEGRO_BITMAP>> BitmapCache::_cache;

std::weak_ptr<ALLEGRO_BITMAP> BitmapCache::GetBitmap(const std::string& filename) noexcept {
    //Return NULL if a bad filename was passed.
    if(filename.empty()) return std::weak_ptr<ALLEGRO_BITMAP>();
    if(std::experimental::filesystem::exists(std::experimental::filesystem::v1::path(filename)) == false) return std::weak_ptr<ALLEGRO_BITMAP>();

    //Search for requested BITMAP.
    auto _iter = _cache.lower_bound(filename);

    //If found, return it.
    if(_iter != _cache.end()) {
        return _iter->second;
    }

    auto temp_bitmap = al_load_bitmap(filename.c_str());
    if(temp_bitmap == nullptr) return std::weak_ptr<ALLEGRO_BITMAP>(); //Allocation failed.

    //Otherwise, create it, store it, then return it.
    return _cache.insert(_iter, std::move(std::make_pair(filename, std::move(std::shared_ptr<ALLEGRO_BITMAP>(temp_bitmap, al_destroy_bitmap)))))->second;
}


A2DE_END