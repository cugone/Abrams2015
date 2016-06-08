/**************************************************************************************************
// file:	Engine\Input\CMouse.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the mouse class
 **************************************************************************************************/
#ifndef A2DE_CMOUSE_H
#define A2DE_CMOUSE_H

#include <bitset>
#include <memory>
#include <tuple>
#include <utility>

#include <allegro5/mouse.h>
#include <allegro5/mouse_cursor.h>

#include "../a2de_vals.h"

#include "../Math/CVector2D.h"
#include "../Math/CVector3D.h"
#include "../Math/CVector4D.h"

struct ALLEGRO_MOUSE_CURSOR;
struct ALLEGRO_DISPLAY;

A2DE_BEGIN

class Sprite;
class GameWindow;

/**************************************************************************************************
 * <summary>Mouse.</summary>
 * <remarks>Casey Ugone, 7/28/2011.</remarks>
 **************************************************************************************************/
class Mouse {

public:

    /**************************************************************************************************
    * <summary>Initializes a new instance of the Mouse class.</summary>
    * <remarks>Casey Ugone, 7/28/2011.</remarks>
    **************************************************************************************************/
    explicit Mouse(ALLEGRO_DISPLAY& parent_display);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
    ~Mouse();

    /**************************************************************************************************
     * <summary>Gets the sprite of the mouse image.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>null if it fails, else the sprite.</returns>
     **************************************************************************************************/
    std::weak_ptr<Sprite> GetSprite() const;
    std::weak_ptr<Sprite> GetSprite();

    /**************************************************************************************************
     * <summary>Gets position as a 4D Vector.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    const Vector4D& GetPosition() const;

    /**************************************************************************************************
     * <summary>Gets position as a 4D Vector.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    Vector4D& GetPosition();

    /**************************************************************************************************
     * <summary>Gets mickeys as a 4D Vector.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The mickeys.</returns>
     **************************************************************************************************/
    const Vector4D& GetMickeys() const;

    /**************************************************************************************************
     * <summary>Gets mickeys as a 4D Vector.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The mickeys.</returns>
     **************************************************************************************************/
    Vector4D& GetMickeys();
	
    /**************************************************************************************************
     * <summary>Gets the focus as a Vector2D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The focus.</returns>
     **************************************************************************************************/
    const Vector2D& GetFocus() const;

    /**************************************************************************************************
     * <summary>Gets the focus as a Vector2D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The focus.</returns>
     **************************************************************************************************/
    Vector2D& GetFocus();
	
    /**************************************************************************************************
     * <summary>Gets the number of buttons.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The number of buttons.</returns>
     **************************************************************************************************/
	int GetNumButtons() const;

    /**************************************************************************************************
     * <summary>Gets the number of buttons.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The number of buttons.</returns>
     **************************************************************************************************/
    int GetNumButtons();

    /**************************************************************************************************
     * <summary>Sets the position.</summary>
     * <remarks>Casey Ugone, 10/11/2014.</remarks>
     * <param name="pos">The position as a Vector4D object.</param>
     **************************************************************************************************/
    void SetPosition(const a2de::Vector4D& pos);

	/**************************************************************************************************
	 * <summary>Sets the focus.</summary>
	 * <remarks>Casey Ugone, 6/4/2016.</remarks>
	 * <param name="pos">The focus point as a Vector2D object.</param>
	 **************************************************************************************************/
	void SetFocus(const a2de::Vector2D& pos);

    /**************************************************************************************************
     * <summary>Updates the mouse parameters.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
    void Update();
    
    /**************************************************************************************************
     * <summary>Sets the image.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="image"> [in] If non-null, the image, else clears the image.</param>
     * <param name="focusX">The focus x coordinate.</param>
     * <param name="focusY">The focus y coordinate.</param>
     **************************************************************************************************/
	void SetImage(std::shared_ptr<a2de::Sprite> image, int focusX, int focusY);

    /**************************************************************************************************
     * <summary>Query if this object is visible.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>true if visible, false if not.</returns>
     **************************************************************************************************/
	bool IsVisible();

    /**************************************************************************************************
     * <summary>Sets the mouse's visible state.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="visible">true to show, false to hide.</param>
     **************************************************************************************************/
	void SetVisible(bool visible);

    /**************************************************************************************************
     * <summary>Shows the mouse on the specified BITMAP.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <remarks>Synonoumus with Show(dest, 0, 0, dest->w, dest->h)</remarks>
     * <param name="dest">[in] If non-null, destination for the Bitmap, else hides the mouse pointer.</param>
     **************************************************************************************************/
    void Show();
    
    /**************************************************************************************************
     * <summary>Hides the mouse pointer.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
	void Hide();

    /**************************************************************************************************
     * <summary>Sets image to a system default.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="cursor">The cursor to set to.</param>
     **************************************************************************************************/
    void SetImageToDefault(ALLEGRO_SYSTEM_MOUSE_CURSOR cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    /**************************************************************************************************
     * <summary>Determines if the display lost focus of the mouse.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>true if it did, false if it did not.</returns>
     **************************************************************************************************/
    bool MouseLostFocus() const;

    /**************************************************************************************************
     * <summary>Determines if the display lost focus of the mouse.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>true if it did, false if it did not.</returns>
     **************************************************************************************************/
    bool MouseLostFocus();

private:

    /// <summary> The position </summary>
    Vector4D _position;
    /// <summary> The mickeys </summary>
    Vector4D _mickeys;

    /// <summary>The focus location.</summary>
    Vector2D _focus;

    /// <summary> The image </summary>
    std::weak_ptr<a2de::Sprite> _image;
    
    /// <summary> true to show, false to hide the image</summary>
    bool _isVisible;

    /// <summary> Number of buttons </summary>
    unsigned int _numButtons;

    /**************************************************************************************************
     * <summary>the previous state.</summary>
     **************************************************************************************************/
    ALLEGRO_MOUSE_STATE _prevState;

    /**************************************************************************************************
     * <summary>The current state.</summary>
     **************************************************************************************************/
    ALLEGRO_MOUSE_STATE _curState;

    /**************************************************************************************************
     * <summary>The cursor currently in use.</summary>
     **************************************************************************************************/
    std::unique_ptr<ALLEGRO_MOUSE_CURSOR, decltype(&al_destroy_mouse_cursor)> _cursor;

    /**************************************************************************************************
     * <summary>The parent display.</summary>
     **************************************************************************************************/
    ALLEGRO_DISPLAY& _parent_display;

    /**************************************************************************************************
     * <summary>Identifier for the cursor.</summary>
     **************************************************************************************************/
    ALLEGRO_SYSTEM_MOUSE_CURSOR _cursor_id;

    /// <summary> The instance </summary>
    static bool _is_instanced;
	
    /**************************************************************************************************
     * <summary>Initializes this object.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     **************************************************************************************************/
    void Init();

	/**************************************************************************************************
	 * <summary>Initialises this Mouse.</summary>
	 * <remarks>Casey Ugone, 6/4/2016.</remarks>
	 * <param name="parent_display">[in] If non-null, the parent display.</param>
	 * <param name="image">			The image.</param>
	 * <param name="focus">			The focus.</param>
	 * <param name="cursor_id">		Identifier for the cursor.</param>
	 **************************************************************************************************/
	void Init(const ALLEGRO_DISPLAY& parent_display, const std::string& file, const a2de::Vector2D& focus, ALLEGRO_SYSTEM_MOUSE_CURSOR cursor_id);

    /**************************************************************************************************
     * <summary>Deinitializes this object.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     **************************************************************************************************/
    void Deinit();

    //TODO: Uncomment Mouse functions after testing window.
    /**************************************************************************************************
     * <summary>Initializes a new instance of the Mouse class.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="image"> [in] If non-null, the image.</param>
     * <param name="focusX">The focus x coordinate.</param>
     * <param name="focusY">The focus y coordinate.</param>
     **************************************************************************************************/
    //Mouse(ALLEGRO_DISPLAY* parent_display, Sprite* image, int focusX, int focusY);
    
    friend class MouseInputHandler;
};

A2DE_END

#endif