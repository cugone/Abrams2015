/**************************************************************************************************
// file:	Engine\GFX\ADTAnimationHandler.h
//
// summary:	Declares the adt animation handler class
 **************************************************************************************************/
#ifndef A2DE_IANIMATIONHANDLER_H
#define A2DE_IANIMATIONHANDLER_H


#include <map>
#include <utility>
#include <string>
#include <vector>

#include "../a2de_vals.h"
#include "CAnimationFrame.h"
#include "CAnimationFrameSet.h"

A2DE_BEGIN

class Sprite;
class AnimatedSprite;

class ADTAnimationHandler {
public:

    /**************************************************************************************************
     * <summary>Values that represent animation directions.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     **************************************************************************************************/
    enum class Direction {
         /** <summary>An enum constant representing the forward nonlooping option.</summary> */
        Forward_Nonlooping,
         /** <summary>An enum constant representing the forward looping option.</summary> */
        Forward_Looping,
         /** <summary>An enum constant representing the reverse nonlooping option.</summary> */
        Reverse_Nonlooping,
         /** <summary>An enum constant representing the reverse looping option.</summary> */
        Reverse_Looping,
     /** <summary>.</summary> */
    };

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="sprite">[in,out] The sprite.</param>
     **************************************************************************************************/
    explicit ADTAnimationHandler(Sprite& sprite);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="other">The other.</param>
     **************************************************************************************************/
    ADTAnimationHandler(const ADTAnimationHandler& other) = default;

    /**************************************************************************************************
     * <summary>Move constructor.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="r_other">[in,out] The other.</param>
     **************************************************************************************************/
    ADTAnimationHandler(ADTAnimationHandler&& r_other) = default;

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this ADTAnimationHandler.</returns>
     **************************************************************************************************/
    ADTAnimationHandler& operator=(const ADTAnimationHandler& rhs) = default;

    /**************************************************************************************************
     * <summary>Move assignment operator.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="rrhs">[in,out] The rrhs.</param>
     * <returns>A shallow copy of this ADTAnimationHandler.</returns>
     **************************************************************************************************/
    ADTAnimationHandler& operator=(ADTAnimationHandler&& rrhs) = default;

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     **************************************************************************************************/
    virtual ~ADTAnimationHandler() = 0;

    /**************************************************************************************************
     * <summary>Adds an animation by name.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">The name of the new empty animation.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool AddAnimation(const std::string& name);

    /**************************************************************************************************
     * <summary>Adds an animation to 'frames'.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">  The name of the animation to add.</param>
     * <param name="frames">The specific frames to add.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool AddAnimation(const std::string& name, const AnimationFrameSet& frames);

    /**************************************************************************************************
     * <summary>Removes an animation by name.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">The name of the animation to remove.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool RemoveAnimation(const std::string& name);

    /**************************************************************************************************
     * <summary>Gets the iterator pointing to the first animation.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <returns>An iterator.</returns>
     **************************************************************************************************/
    std::map<std::string, AnimationFrameSet>::const_iterator begin() const;

    /**************************************************************************************************
     * <summary>Gets the iterator pointing to the first animation.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <returns>An iterator.</returns>
     **************************************************************************************************/
    std::map<std::string, AnimationFrameSet>::iterator begin();

    /**************************************************************************************************
     * <summary>Gets the iterator pointing to .</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <returns>An iterator.</returns>
     **************************************************************************************************/
    std::map<std::string, AnimationFrameSet>::const_iterator end() const;

    /**************************************************************************************************
     * <summary>Gets the end.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <returns>An auto.</returns>
     **************************************************************************************************/
    std::map<std::string, AnimationFrameSet>::iterator end();

    /**************************************************************************************************
     * <summary>Empties this ADTAnimationHandler.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool empty() const;

    /**************************************************************************************************
     * <summary>Empties this ADTAnimationHandler.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool empty();

    /**************************************************************************************************
     * <summary>Gets the size.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <returns>A std::size_t.</returns>
     **************************************************************************************************/
    std::size_t size() const;

    /**************************************************************************************************
     * <summary>Gets the size.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <returns>A std::size_t.</returns>
     **************************************************************************************************/
    std::size_t size();

    /**************************************************************************************************
     * <summary>Sizes the given name.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">The name.</param>
     * <returns>A std::size_t.</returns>
     **************************************************************************************************/
    std::size_t size(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Sizes the given name.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">The name.</param>
     * <returns>A std::size_t.</returns>
     **************************************************************************************************/
    std::size_t size(const std::string& name);

    /**************************************************************************************************
     * <summary>Searches for the first match for the given constant standard string&amp;
     * </summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">The name.</param>
     * <returns>A std::map&lt;std::string,AnimationFrameSet&gt;::const_iterator.</returns>
     **************************************************************************************************/
    std::map<std::string, AnimationFrameSet>::const_iterator find(const std::string& name) const;

    /**************************************************************************************************
     * <summary>Searches for the first match for the given constant standard string&amp;
     * </summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">The name.</param>
     * <returns>A std::map&lt;std::string,AnimationFrameSet&gt;::iterator.</returns>
     **************************************************************************************************/
    std::map<std::string, AnimationFrameSet>::iterator find(const std::string& name);

    /**************************************************************************************************
     * <summary>Plays.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">              The name.</param>
     * <param name="rewindOnCompletion">true to rewind on completion.</param>
     **************************************************************************************************/
    void Play(const std::string& name, bool rewindOnCompletion);

    /**************************************************************************************************
     * <summary>Reverses.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">              The name.</param>
     * <param name="rewindOnCompletion">true to rewind on completion.</param>
     **************************************************************************************************/
    void Reverse(const std::string& name, bool rewindOnCompletion);

protected:

    /**************************************************************************************************
     * <summary>Animates.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="name">The name.</param>
     * <param name="dir"> The dir.</param>
     **************************************************************************************************/
    void Animate(const std::string& name, ADTAnimationHandler::Direction dir);

    /**************************************************************************************************
     * <summary>Copies the current frame to image frame described by iter.</summary>
     * <remarks>Casey Ugone, 1/11/2016.</remarks>
     * <param name="iter">The iterator.</param>
     **************************************************************************************************/
    void CopyCurrentFrameToImageFrame(AnimationFrameSet::const_iterator iter);

private:

    /** <summary><summary>The animations.</summary></summary> */
    std::map<std::string, AnimationFrameSet> _animations;
    /** <summary><summary>The current set.</summary></summary> */
    std::map<std::string, AnimationFrameSet>::const_iterator _curSet;
    /** <summary><summary>The current frame.</summary></summary> */
    AnimationFrameSet::const_iterator _curFrame;
    /** <summary><summary>The observed.</summary></summary> */
    Sprite& _observed;
    /** <summary><summary>The current name.</summary></summary> */
    std::string _curName;

 /** <summary>.</summary> */
};

A2DE_END

#endif // A2DE_IANIMATIONHANDLER_H
