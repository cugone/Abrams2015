/**************************************************************************************************
// file:	Engine\GFX\CAnimationFrameSet.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the animation frame set class
 **************************************************************************************************/
#ifndef A2DE_CANIMATIONFRAMESET_H
#define A2DE_CANIMATIONFRAMESET_H

#include "../a2de_vals.h"
#include <utility>
#include <string>
#include <vector>

#include "CAnimationFrame.h"

A2DE_BEGIN

class Sprite;

/**************************************************************************************************
 * <summary>Animation frame set. </summary>
 * <remarks>Casey Ugone, 6/29/2012.</remarks>
 **************************************************************************************************/
class AnimationFrameSet {
public:

    typedef std::vector<AnimationFrame>::iterator iterator;
    typedef std::vector<AnimationFrame>::const_iterator const_iterator;
    typedef std::vector<AnimationFrame>::reverse_iterator reverse_iterator;
    typedef std::vector<AnimationFrame>::const_reverse_iterator const_reverse_iterator;
    

    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     **************************************************************************************************/
    AnimationFrameSet() = default;

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="other">The other FrameSet.</param>
     **************************************************************************************************/
    AnimationFrameSet(const AnimationFrameSet& other) = default;
    AnimationFrameSet(AnimationFrameSet&& other) = default;

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     **************************************************************************************************/
    ~AnimationFrameSet() = default;

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A deep copy of this object.</returns>
     **************************************************************************************************/
    AnimationFrameSet& operator=(const AnimationFrameSet& rhs) = default;

    AnimationFrameSet& operator=(AnimationFrameSet&& rhs) = default;

    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const AnimationFrameSet& rhs);

    /**************************************************************************************************
     * <summary>InEquality operator.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are not considered equivalent.</returns>
     **************************************************************************************************/
    bool operator!=(const AnimationFrameSet& rhs);

    /**************************************************************************************************
     * <summary>Adds a frame by copying an existing frame's location and size.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="frame">The frame to copy.</param>
     **************************************************************************************************/
    void AddFrame(const AnimationFrame& frame);
    
    /**************************************************************************************************
     * <summary>Gets the size of the FrameSet.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The size of the FrameSet</returns>
     **************************************************************************************************/
    std::size_t size() const;

    /**************************************************************************************************
     * <summary>Gets the size of the FrameSet.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The size of the FrameSet</returns>
     **************************************************************************************************/
    std::size_t size();

    /**************************************************************************************************
     * <summary>Gets the beginning iterator.</summary>
     * <remarks>Casey Ugone, 10/23/2015.</remarks>
     * <returns>A beginning iterator.</returns>
     **************************************************************************************************/
    const_iterator begin() const;
    const_iterator cbegin() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    iterator begin();
    const_iterator cbegin();
    reverse_iterator rbegin();
    const_reverse_iterator crbegin();

    /**************************************************************************************************
     * <summary>Gets the end iterator.</summary>
     * <remarks>Casey Ugone, 10/23/2015.</remarks>
     * <returns>An end iterator.</returns>
     **************************************************************************************************/
    const_iterator end() const;
    const_iterator cend() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;
    iterator end();
    const_iterator cend();
    reverse_iterator rend();
    const_reverse_iterator crend();

    /**************************************************************************************************
     * <summary>Query if the position is at the first frame.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if at last, false if not.</returns>
     **************************************************************************************************/
    bool IsAtFirst() const;

    /**************************************************************************************************
     * <summary>Query if the position is at the first frame.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if at last, false if not.</returns>
     **************************************************************************************************/
    bool IsAtFirst();

    /**************************************************************************************************
     * <summary>Query if the position is at the last frame.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if at last, false if not.</returns>
     **************************************************************************************************/
    bool IsAtLast() const;

    /**************************************************************************************************
     * <summary>Query if the position is at the last frame.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if at last, false if not.</returns>
     **************************************************************************************************/
    bool IsAtLast();

    /**************************************************************************************************
     * <summary>Query if the current position is at a specific frame.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="position">The position.</param>
     * <returns>true if at, false if not.</returns>
     **************************************************************************************************/
    bool IsAt(const std::vector<AnimationFrame>::const_iterator& position) const;

    /**************************************************************************************************
     * <summary>Query if the current position is at a specific frame.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="position">The position.</param>
     * <returns>true if at, false if not.</returns>
     **************************************************************************************************/
    bool IsAt(const std::vector<AnimationFrame>::const_iterator& position);

    /**************************************************************************************************
     * <summary>Query if the position is at the end.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if complete, false if not.</returns>
     **************************************************************************************************/
    bool IsComplete() const;

    /**************************************************************************************************
     * <summary>Query if the position is at the end.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if complete, false if not.</returns>
     **************************************************************************************************/
    bool IsComplete();

    /**************************************************************************************************
     * <summary>Query if the position is at front of the FrameSet.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if at front, false if not.</returns>
     **************************************************************************************************/
    bool IsAtFront() const;

    /**************************************************************************************************
     * <summary>Query if the position is at front of the FrameSet.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if at front, false if not.</returns>
     **************************************************************************************************/
    bool IsAtFront();

    /**************************************************************************************************
     * <summary>Query if the position is at end of the FrameSet.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if at end, false if not.</returns>
     **************************************************************************************************/
    bool IsAtEnd() const;

    /**************************************************************************************************
     * <summary>Query if the position is at end of the FrameSet.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>true if at end, false if not.</returns>
     **************************************************************************************************/
    bool IsAtEnd();

    /**************************************************************************************************
     * <summary>Gets the current frame.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The current frame.</returns>
     **************************************************************************************************/
    const AnimationFrame& GetCurFrame() const;

    /**************************************************************************************************
     * <summary>Gets the current frame.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The current frame.</returns>
     **************************************************************************************************/
    AnimationFrame& GetCurFrame();

    /**************************************************************************************************
     * <summary>Gets a frame at the specified position.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="position">The position to get the frame from.</param>
     * <returns>The frame at the specified position.</returns>
     **************************************************************************************************/
    const AnimationFrame& at(std::size_t position) const;

    /**************************************************************************************************
     * <summary>Gets a frame at the specified position.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="position">The position to get the frame from.</param>
     * <returns>The frame at the specified position.</returns>
     **************************************************************************************************/
    AnimationFrame& at(std::size_t position);

protected:
private:

    /// <summary> The frame strip </summary>
    std::vector<AnimationFrame> _frameStrip;
    /// <summary> The current position index of the FrameSet. </summary>
    std::vector<AnimationFrame>::const_iterator _curFrame;

};

A2DE_END

#endif
