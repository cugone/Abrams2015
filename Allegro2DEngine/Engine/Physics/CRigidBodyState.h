/**************************************************************************************************
// file:	Engine\Physics\CRigidBodyState.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the rigid body state class
 **************************************************************************************************/
#ifndef A2DE_CRIGIDBODYSTATE_H
#define A2DE_CRIGIDBODYSTATE_H

#include "../a2de_vals.h"
#include "../Math/CVector2D.h"
#include "IUpdatable.h"
#include <list>
#include "../Math/CRectangle.h"

A2DE_BEGIN

class Shape;
class IBoundingBox;
class AABB;
class OBB;

class PhysicsMaterial {
public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="restitution">The restitution.</param>
     * <param name="friction">   The friction.</param>
     **************************************************************************************************/
    PhysicsMaterial(double restitution, double static_friction, double kinetic_friction);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="other">The other.</param>
     **************************************************************************************************/
    PhysicsMaterial(const PhysicsMaterial& other);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    PhysicsMaterial& operator=(const PhysicsMaterial& rhs);

    /**************************************************************************************************
     * <summary>Gets the restitution.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The restitution.</returns>
     **************************************************************************************************/
    double GetRestitution() const;

    /**************************************************************************************************
     * <summary>Gets the restitution.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The restitution.</returns>
     **************************************************************************************************/
    double GetRestitution();

    /**************************************************************************************************
     * <summary>Sets a restitution.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="restitution">The restitution.</param>
     **************************************************************************************************/
    void SetRestitution(double restitution);

    /**************************************************************************************************
     * <summary>Gets the Kinetic friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The friction.</returns>
     **************************************************************************************************/
    double GetKineticFriction() const;

    /**************************************************************************************************
     * <summary>Gets the Kinetic friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The friction.</returns>
     **************************************************************************************************/
    double GetKineticFriction();

    /**************************************************************************************************
     * <summary>Sets the Kinetic friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="friction">The friction.</param>
     **************************************************************************************************/
    void SetKineticFriction(double friction);

    /**************************************************************************************************
     * <summary>Gets the Static friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The friction.</returns>
     **************************************************************************************************/
    double GetStaticFriction() const;

    /**************************************************************************************************
     * <summary>Gets the Static friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The friction.</returns>
     **************************************************************************************************/
    double GetStaticFriction();

    /**************************************************************************************************
     * <summary>Sets the Static friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="friction">The friction.</param>
     **************************************************************************************************/
    void SetStaticFriction(double friction);

protected:
private:
    /// <summary> The restitution coefficient</summary>
    double _restitution;
    /// <summary> The static friction coefficient.</summary>
    double _static_friction;
    /// <summary> The kinetic friction coefficient.</summary>
    double _kinetic_friction;

};

class State : public IUpdatable {
    
    typedef std::list<std::pair<Vector2D, double> > ForceContainer;
    typedef std::list<Vector2D> ImpulseContainer;

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 6/15/2015.</remarks>
     * <param name="mass">               The mass.</param>
     * <param name="gravMod">            The grav modifier.</param>
     * <param name="position">           The position.</param>
     * <param name="velocity">           The velocity.</param>
     * <param name="material_properties">The material properties.</param>
     **************************************************************************************************/
    State(double mass, const Vector2D& gravMod, const Vector2D& position, const Vector2D& velocity, const PhysicsMaterial& material_properties);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="other">The other.</param>
     **************************************************************************************************/
    State(const State& other);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 4/25/2013.</remarks>
     **************************************************************************************************/
    ~State();

    /**************************************************************************************************
     * <summary>Gets the mass.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The mass.</returns>
     **************************************************************************************************/
    double GetMass() const;

    /**************************************************************************************************
     * <summary>Gets the mass.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The mass.</returns>
     **************************************************************************************************/
    double GetMass();

    /**************************************************************************************************
     * <summary>Sets the mass.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="mass">The mass.</param>
     **************************************************************************************************/
    void SetMass(double mass);

    /**************************************************************************************************
     * <summary>Gets the gravity modifier.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The gravity modifier.</returns>
     **************************************************************************************************/
    Vector2D& GetGravityModifier();

    /**************************************************************************************************
     * <summary>Gets the gravity modifier.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The gravity modifier.</returns>
     **************************************************************************************************/
    const Vector2D& GetGravityModifier() const;
    
    /**************************************************************************************************
     * <summary>Sets a gravity modifier.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="gravity_modifier">The gravity modifier.</param>
     **************************************************************************************************/
    void SetGravityModifier(const Vector2D& gravity_modifier);
    
    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    Vector2D& GetPosition();

    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    const Vector2D& GetPosition() const;

    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    void SetPosition(const Vector2D& position);

    /**************************************************************************************************
     * <summary>Gets the velocity.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The velocity.</returns>
     **************************************************************************************************/
    Vector2D GetVelocity();

    /**************************************************************************************************
     * <summary>Gets the velocity.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The velocity.</returns>
     **************************************************************************************************/
    Vector2D GetVelocity() const;

    /**************************************************************************************************
     * <summary>Sets a velocity.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="velocity">The velocity.</param>
     **************************************************************************************************/
    void SetVelocity(const Vector2D& velocity);

    /**************************************************************************************************
     * <summary>Gets the acceleration.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The acceleration.</returns>
     **************************************************************************************************/
    Vector2D GetAcceleration() const;

    /**************************************************************************************************
     * <summary>Gets the acceleration.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The acceleration.</returns>
     **************************************************************************************************/
    Vector2D GetAcceleration();

    /**************************************************************************************************
     * <summary>Sets an acceleration.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="acceleration">The acceleration.</param>
     **************************************************************************************************/
    void SetAcceleration(const Vector2D& acceleration);

    /**************************************************************************************************
     * <summary>Clears the forces.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void ClearForces();

    /**************************************************************************************************
     * <summary>Clears the impulses.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void ClearImpulses();

    /**************************************************************************************************
     * <summary>Applies the force.</summary>
     * <remarks>Casey Ugone, 6/15/2015.</remarks>
     * <param name="force">   The force in Newtons.</param>
     * <param name="duration">The duration in seconds.</param>
     **************************************************************************************************/
    void ApplyForce(const Vector2D& force, double duration);

    /**************************************************************************************************
     * <summary>Applies the impulse described by impulse.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="impulse">The impulse in Newtons.</param>
     **************************************************************************************************/
    void ApplyImpulse(const Vector2D& impulse);

    /**************************************************************************************************
     * <summary>Sleeps this object.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void Sleep();

    /**************************************************************************************************
     * <summary>Wakes this object.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void Wake();

    /**************************************************************************************************
     * <summary>Query if this object is active.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if active, false if not.</returns>
     **************************************************************************************************/
    bool IsActive() const;

    /**************************************************************************************************
     * <summary>Query if this object is active.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if active, false if not.</returns>
     **************************************************************************************************/
    bool IsActive();

    /**************************************************************************************************
     * <summary>Sets an active.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="active">true to active.</param>
     **************************************************************************************************/
    void SetActive(bool active);

    /**************************************************************************************************
     * <summary>Updates the given deltaTime.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="deltaTime">Time since the last frame.</param>
     **************************************************************************************************/
    void Update(double deltaTime);

    /**************************************************************************************************
     * <summary>Sets a material.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="material">The material.</param>
     **************************************************************************************************/
    void SetMaterial(const PhysicsMaterial& material);

    /**************************************************************************************************
     * <summary>Gets the restitution.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The restitution.</returns>
     **************************************************************************************************/
    double GetRestitution() const;

    /**************************************************************************************************
     * <summary>Gets the restitution.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The restitution.</returns>
     **************************************************************************************************/
    double GetRestitution();

    /**************************************************************************************************
     * <summary>Sets a restitution.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="restitution">The restitution.</param>
     **************************************************************************************************/
    void SetRestitution(double restitution);

    /**************************************************************************************************
     * <summary>Gets the friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The friction.</returns>
     **************************************************************************************************/
    double GetStaticFriction() const;

    /**************************************************************************************************
     * <summary>Gets the friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The friction.</returns>
     **************************************************************************************************/
    double GetStaticFriction();

    /**************************************************************************************************
     * <summary>Sets a friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="friction">The friction.</param>
     **************************************************************************************************/
    void SetStaticFriction(double friction);

    /**************************************************************************************************
     * <summary>Gets the friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The friction.</returns>
     **************************************************************************************************/
    double GetKineticFriction() const;

    /**************************************************************************************************
     * <summary>Gets the friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The friction.</returns>
     **************************************************************************************************/
    double GetKineticFriction();

    /**************************************************************************************************
     * <summary>Sets a friction.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="friction">The friction.</param>
     **************************************************************************************************/
    void SetKineticFriction(double friction);

    /**************************************************************************************************
     * <summary>Sets a collision shape.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="shape">[in,out] If non-null, the shape.</param>
     **************************************************************************************************/
    void SetCollisionShape(Shape* shape);

    /**************************************************************************************************
     * <summary>Gets the collision shape.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>null if it fails, else the collision shape.</returns>
     **************************************************************************************************/
    const Shape* GetCollisionShape() const;

    /**************************************************************************************************
     * <summary>Gets the collision shape.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>null if it fails, else the collision shape.</returns>
     **************************************************************************************************/
    Shape* GetCollisionShape();

    /**************************************************************************************************
     * <summary>Sets the local damper value.</summary>
     * <remarks>Casey Ugone, 4/25/2013.</remarks>
     * <param name="value">The new damper value.</param>
     **************************************************************************************************/
    void SetDamper(double value);

    /**************************************************************************************************
     * <summary>Gets the velocity damper value.</summary>
     * <remarks>Casey Ugone, 4/25/2013.</remarks>
     * <returns>The damper value.</returns>
     **************************************************************************************************/
    double GetDamper() const;

    /**************************************************************************************************
     * <summary>Gets the velocity damper value.</summary>
     * <remarks>Casey Ugone, 4/25/2013.</remarks>
     * <returns>The damper value.</returns>
     **************************************************************************************************/
    double GetDamper();

    /**************************************************************************************************
     * <summary>Sets the density.</summary>
     * <remarks>Casey Ugone, 6/15/2015.</remarks>
     * <param name="density">The density.</param>
     **************************************************************************************************/
    void SetDensity(double density);

    /**************************************************************************************************
     * <summary>Gets the density.</summary>
     * <remarks>Casey Ugone, 5/3/2013.</remarks>
     * <returns>The density.</returns>
     **************************************************************************************************/
    double GetDensity() const;

    /**************************************************************************************************
     * <summary>Gets the density.</summary>
     * <remarks>Casey Ugone, 5/3/2013.</remarks>
     * <returns>The density.</returns>
     **************************************************************************************************/
    double GetDensity();

    /**************************************************************************************************
     * <summary>Calculates the density based on area and mass values.</summary>
     * <remarks>Casey Ugone, 5/3/2013.</remarks>
     * <returns>The calculated density.</returns>
     **************************************************************************************************/
    double CalculateDensity();

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    State& operator=(const State& rhs);

    /// <summary>A body's Mass.</summary>
    double _mass;
    /// <summary>A body's gravity modifier in the X-Y direction a body.</summary>
    Vector2D _gravMod;
    /// <summary>A body's current position.</summary>
    Vector2D _position;
    /// <summary>A body's current velocity.</summary>
    Vector2D _velocity;
    /// <summary> A body's current acceleration.</summary>
    Vector2D _acceleration;
    /// <summary> The forces applied to a body.</summary>
    ForceContainer _forces;
    /// <summary> The impulses applied to a body.</summary>
    ImpulseContainer _impulses;

    /// <summary> The body is not asleep and can accept forces and collisions. </summary>
    bool _active;

    /// <summary> The physics material </summary>
    PhysicsMaterial _mat;

    /// <summary> The collision shape </summary>
    Shape* _collision_shape;

    /// <summary> The default velocity damper </summary>
    static const double DEFAULT_DAMPER_VALUE;

    /// <summary> The density </summary>
    double _density;

    /// <summary> The local velocity damper </summary>
    double _damper;

    /// <summary> The rigid body </summary>
    friend class RigidBody;

};


A2DE_END

#endif