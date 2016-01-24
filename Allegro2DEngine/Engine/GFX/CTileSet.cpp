/**************************************************************************************************
// file:	Engine\GFX\CTileSet.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the tile set class
 **************************************************************************************************/
#include "CTileSet.h"

#include <cassert>
#include <experimental/filesystem>

#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/display.h>

#include "../a2de_exceptions.h"
#include "CBitmapCache.h"


A2DE_BEGIN


TileSet::TileSet(const std::string& file, int tileWidth, int tileHeight) : _file(file), _tileWidth(tileWidth), _tileHeight(tileHeight), _sheetWidth(0), _sheetHeight(0), _max_rows(0), _max_columns(0), _max_tiles(0), _tileSheet() {

    if(std::experimental::filesystem::exists(std::experimental::filesystem::v1::path(_file)) == false) {
        throw a2de::FileNotFoundException(_file);
    }

    if(tileWidth < 1) throw a2de::InvalidArgumentException("Tile Width cannot be less than one.");
    if(tileHeight < 1) throw a2de::InvalidArgumentException("Tile Height cannot be less than one.");

    _tileSheet = BitmapCache::GetBitmap(_file);
    if(_tileSheet.expired()) {
        throw a2de::BitmapLoadFailureException(file);
    }

    auto s_tileSheet = _tileSheet.lock();

    _sheetWidth = al_get_bitmap_width(s_tileSheet.get());
    _sheetHeight = al_get_bitmap_height(s_tileSheet.get());

    _max_columns = _sheetWidth / _tileWidth;
    _max_rows = _sheetHeight / _tileHeight;
    _max_tiles = _max_columns * _max_rows;

}

void TileSet::DrawTile(ALLEGRO_BITMAP* dest, unsigned int column, unsigned int row, int dest_x, int dest_y) {
    if(dest == nullptr) return;
    if(column >= _max_columns || row >= _max_rows) return;

    ALLEGRO_BITMAP* old_target_bmp = al_get_target_bitmap();
    al_set_target_bitmap(dest);

    al_draw_bitmap_region(_tileSheet.lock().get(), column * _tileWidth, row * _tileHeight, _tileWidth, _tileHeight, dest_x, dest_y, 0);

    al_set_target_bitmap(old_target_bmp);    
}

void TileSet::DrawTile(ALLEGRO_BITMAP* dest, unsigned int index, int dest_x, int dest_y) {
    if(dest == nullptr) return;
    if(index >= _max_tiles) return;

    unsigned int row = index / _max_columns;
    unsigned int column = index % _max_columns;

    DrawTile(dest, column, row, dest_x, dest_y);
}

unsigned int TileSet::GetTileWidth() const {
    return _tileWidth;
}

unsigned int TileSet::GetTileWidth() {
    return static_cast<const TileSet&>(*this).GetTileWidth();
}

unsigned int TileSet::GetTileHeight() const {
    return _tileHeight;
}

unsigned int TileSet::GetTileHeight() {
    return static_cast<const TileSet&>(*this).GetTileHeight();
}

unsigned int TileSet::GetSheetWidth() const {
    return _sheetWidth;
}

unsigned int TileSet::GetSheetWidth() {
    return static_cast<const TileSet&>(*this).GetSheetWidth();
}

unsigned int TileSet::GetSheetHeight() const {
    return _sheetHeight;
}

unsigned int TileSet::GetSheetHeight() {
    return static_cast<const TileSet&>(*this).GetSheetHeight();
}


A2DE_END