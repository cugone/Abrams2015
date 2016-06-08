#include "a2de_base.h"

#include "GFX/CBitmapCache.h"

A2DE_BEGIN

bool a2de_init() {
    std::cout << "Calling a2de_init...";
    std::cout.flush();

    bool system_init_result = al_install_system(ALLEGRO_VERSION_INT, std::atexit);
    bool system_installed = al_is_system_installed();
    bool image_init_result = system_installed && al_init_image_addon();
    bool primitives_init_result = system_installed && al_init_primitives_addon();
    bool font_init_result = system_installed && al_init_font_addon();
    bool ttf_init_result = system_installed && al_init_ttf_addon();
    bool install_audio_result = system_installed && al_install_audio();
    bool acodec_init_result = system_installed && al_init_acodec_addon();
    bool native_dialog_init_result = system_installed && al_init_native_dialog_addon();
    bool install_keyboard_result = system_installed && al_install_keyboard();
    bool install_mouse_result = system_installed && al_install_mouse();
    bool install_joystick_result = system_installed && al_install_joystick();
    bool result = system_init_result || image_init_result ||
        primitives_init_result || font_init_result || ttf_init_result ||
        install_audio_result || acodec_init_result ||
        native_dialog_init_result || install_keyboard_result ||
        install_mouse_result || install_joystick_result;

    std::atexit(a2de::a2de_deinit);

    std::cout << "done" << std::endl;
    return result;
}

void a2de_deinit() {
    std::cout << "Calling a2de_deinit...";
    std::cout.flush();

    a2de::BitmapCache::_cache.clear();

    al_uninstall_joystick();
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_shutdown_native_dialog_addon();
    al_uninstall_audio();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_uninstall_system();
    
    std::cout << "done" << std::endl;
}

A2DE_END