#include "a2de_base.h"

#include "GFX/CBitmapCache.h"

A2DE_BEGIN

bool a2de_init() {
    std::cout << "Calling a2de_init" << std::endl;
    bool system_init_result = al_install_system(ALLEGRO_VERSION_INT, std::atexit);
    bool image_init_result = al_init_image_addon();
    bool primitives_init_result = al_init_primitives_addon();
    al_init_font_addon();
    bool ttf_init_result = al_init_ttf_addon();
    bool install_audio_result = al_install_audio();
    bool acodec_init_result = al_init_acodec_addon();
    bool native_dialog_init_result = al_init_native_dialog_addon();
    bool keyboard_result = al_install_keyboard();
    bool mouse_result = al_install_mouse();
    bool joystick_result = al_install_joystick();
    bool result = system_init_result || image_init_result ||
        primitives_init_result || ttf_init_result ||
        install_audio_result || acodec_init_result ||
        native_dialog_init_result || keyboard_result ||
        mouse_result || joystick_result;

    std::atexit(a2de::a2de_deinit);

    return result;
}

void a2de_deinit() {
    std::cout << "Calling a2de_deinit" << std::endl;
    a2de::BitmapCache::_cache.clear();
}

A2DE_END