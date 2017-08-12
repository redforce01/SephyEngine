#include "stdafx.h"
#include "entity.h"

//=============================================================================
// constructor
//=============================================================================
Entity::Entity() : Image()
{
    oldX = getX();
    oldY = getY();
    radius = 10.0;
    edge.left = -1;
    edge.top = -1;
    edge.right = 1;
    edge.bottom = 1;
    mass = 1.0;
    bounciness = 1.0;               // max bounce
    velocity.x = 0.0;
    velocity.y = 0.0;
    deltaV.x = 0.0;
    deltaV.y = 0.0;
    active = true;                  // the entity is active
    rotatedBoxReady = false;
    intersecting = false;
    embedded = false;
    collisionType = entityNS::CIRCLE;
    health = 100;
    gravity = entityNS::GRAVITY;
    pixelsColliding = 0;
    rotationRate = 0;
    noBounce = false;
}

//=============================================================================
// Initialize the Entity.
// Pre: *gamePtr = pointer to Game object
//      width = width of Image in pixels  (0 = use full texture width)
//      height = height of Image in pixels (0 = use full texture height)
//      ncols = number of columns in texture (1 to n) (0 same as 1)
//      *textureM = pointer to TextureManager object
// Post: returns true if successful, false if failed
//=============================================================================
bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM)
{
    input = gamePtr->getInput();                // the input system
    //audio = gamePtr->getAudio();                // the audio system
    return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

//=============================================================================
// activate the entity
//=============================================================================
void Entity::activate()
{
    active = true;
}

//=============================================================================
// Angle to target
// Pre:  x,y = Target center
// Returns: Angle to target in radians. + target is clockwise, - target is counterclockwise
//=============================================================================
float Entity::angleToTarget(float x, float y)
{
    float distX = x - getCenterX();     // Target X - entity X
    float distY = y - getCenterY();     // Target Y - entity Y
    float angle = atan2(distY, distX);  // Angle to target
    float angleDifference = angle - getRadians();   // Angle difference

    // normalize angleDifference to [-PI,PI] range so we turn shortest direction toward target
    if (angleDifference >= PI)
        angleDifference -= 2 * (float)PI;
    else if (angleDifference < -PI)
        angleDifference += 2 * (float)PI;

    return angleDifference;         // Angle to target in radians
}

//=============================================================================
// Aim at target
// Pre: frameTime = Elapsed time of the prevous frame in seconds.
//      rotationRate = radians/second
//      x,y = Target center
// Post: Current rotation rate is unchanged
// Returns: Angle to target in radians. + target is clockwise, - target is counterclockwise
//=============================================================================
float Entity::aimAtTarget(float frameTime, float rotationRate, float x, float y)
{
    float angleDifference = angleToTarget(x, y); // Angle to target
    rotationRate = abs(rotationRate);           // Absolute value

    if (angleDifference > 0)                    // If aimed right of target
        rotate(frameTime, -rotationRate);       //     Turn left
    else if (angleDifference < 0)               // If aimed left of target
        rotate(frameTime, rotationRate);        //     Turn right
    return angleDifference;                     // Angle to target in radians
}

//=============================================================================
// update
// Typically called once per frame.
// Pre: frameTime = Elapsed time of the prevous frame in seconds.
//                  It is used to regulate the speed of movement and animation.
//=============================================================================
void Entity::update(float frameTime)
{
    oldX = getX();
    oldY = getY();
    velocity += deltaV;
    deltaV.x = 0;
    deltaV.y = 0;
    Image::update(frameTime);
    rotatedBoxReady = false;    // for rotatedBox collision detection
    intersecting = false;
    embedded = false;
}

//=============================================================================
// ai (artificial intelligence)
// Typically called once per frame.
// Performs AI calculations.
// Pre: frameTime = Elapsed time of the prevous frame in seconds.
//      ent = The other Entity. 
//      Interaction with multiple entities should be handled with multiple calls to this function.
//=============================================================================
void Entity::ai(float frameTime, Entity &ent)
{}

//=============================================================================
// Does this entity intersect with ent?
// Each entity must use a single collision type. Complex shapes that require
// multiple collision types may be done by treating each part as a separate
// entity or by using PIXEL_PERFECT collision. PIXEL_PERFECT collision detection
// is slower and returns a less accurate collision vector so it is not good for
// realistic physics.
// Pre:  &ent = The other Entity.
//       &collisionVector = Set by this function.
// Post: Returns true if the entities are intersecting.
//       Sets the collision vector if intersecting.
//       Sets intersecting true if this entity is intersecting another entity.
//   The collisionVector points in the direction of force that would be applied
//   to this entity as a result of the collision. (e.g. If this entity is a ball
//   that is dropped onto a box, the collision vector would point up (-Y).

bool Entity::intersects(Entity &ent, VECTOR2 &collisionVector)
{
    intersecting = false;

    // if either entity is not active then no collision may occcur
    if (!active || !ent.getActive())    
        return false;

    // If both entities are using CIRCLE collision
    if (collisionType == entityNS::CIRCLE && ent.getCollisionType() == entityNS::CIRCLE)
        intersecting = collideCircle(ent, collisionVector);

    // If both entities are using BOX collision
    else if (collisionType == entityNS::BOX && ent.getCollisionType() == entityNS::BOX)
        intersecting = collideBox(ent, collisionVector);

    // If either entity is using PIXEL_PERFECT collision
    else if (collisionType == entityNS::PIXEL_PERFECT || ent.getCollisionType() == entityNS::PIXEL_PERFECT)
        intersecting = collidePixelPerfect(ent, collisionVector);

    // All other combinations use separating axis test.
    else
    {
        // If neither entity uses CIRCLE collision.
        if (collisionType != entityNS::CIRCLE && ent.getCollisionType() != entityNS::CIRCLE)
            intersecting = collideRotatedBox(ent, collisionVector);
        else    // one of the entities is a circle
        if (collisionType == entityNS::CIRCLE)  // if this entity uses CIRCLE collision
        {
            // Check for collision from other box with our circle
            intersecting = ent.collideRotatedBoxCircle(*this, collisionVector);
            collisionVector *= -1;  // put collisionVector in proper direction
        }
        else    // the other entity uses CIRCLE collision
            intersecting = collideRotatedBoxCircle(ent, collisionVector);
    }

    return intersecting;
}

//=============================================================================
// Perform collision detection between this entity and the other Entity.
// Calls intersects function.
// Each entity must use a single collision type. Complex shapes that require
// multiple collision types may be done by treating each part as a separate
// entity or by using PIXEL_PERFECT collision.  PIXEL_PERFECT collision detection
// is slower and returns a less accurate collision vector so it is not good for
// realistic physics. 
// Typically called once per frame.
// The collision types: CIRCLE, BOX, ROTATED_BOX or PIXEL_PERFECT.
// Pre:  &ent = The other Entity.
//       &collisionVector = Set by this function.
// Post: Returns true if collision, false otherwise. A collision is occurring if
//       the entities are intersecting and moving toward each other. If the
//       entities are intersecting and moving apart it is assumed they are
//       intersecting as the result of a previous collision; false is returned.
//       Sets intersecting true if collision.
//       Sets collisionVector if collision. The collisionVector points in the
//         direction of force that would be applied to this entity as a result
//         of the collision. (e.g. If this entity is a ball that is dropped
//         onto a box, the collision vector would point up (-Y).
//=============================================================================
bool Entity::collidesWith(Entity &ent, VECTOR2 &collisionVector)
{ 
    // if either entity is not active then no collision may occcur
    if (!active || !ent.getActive())    
        return false;

    VECTOR2 cv;
    // Are the entities intersecting? Sets intersecting bool.
    bool collide = intersects(ent, cv);
    if(collide == false)
        return false;               // not colliding

    VECTOR2 Vdiff = velocity - ent.getVelocity();   // velocity difference
    VECTOR2 cUV = cv;               // collision unit vector
    Graphics::Vector2Normalize(&cUV);
    float cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);
    // If cUVdotVdiff > 0 it indicates the entities are moving apart. This may indicate
    // that the entities are still intersecting from an earlier collision.
    if(cUVdotVdiff > 0)             // Entities are moving apart.
        return false;               // Not a new collision.
    collisionVector = cv;           // Set collisionVector.
    return true;                    // Entites are colliding.
}

//=============================================================================
// Circular collision detection method.
// Called by collision(), default collision detection method.
// Pre:  &ent = The other Entity.
//       &collisionVector = Set by this function.
// Post: Returns true if collision, false otherwise.
//       Sets collisionVector if collision. The collisionVector points in the
//         direction of force that would be applied to this entity as a result
//         of the collision. The magnitude of the collision vector is the
//         distance the entities are overlapping.
//=============================================================================
bool Entity::collideCircle(Entity &ent, VECTOR2 &collisionVector)
{
    // difference between centers
    distSquared = *getCenter() - *ent.getCenter();
    distSquared.x = distSquared.x * distSquared.x;      // difference squared
    distSquared.y = distSquared.y * distSquared.y;

    // Calculate the sum of the radii (adjusted for scale)
    sumRadiiSquared = (radius*getScale()) + (ent.radius*ent.getScale());
    sumRadiiSquared *= sumRadiiSquared;                 // square it

    // if entities are colliding
    if((distSquared.x + distSquared.y) < sumRadiiSquared)
    {
        // Set collision vector between centers
        collisionVector = *getCenter() - *ent.getCenter();
        Graphics::Vector2Normalize(&collisionVector);   // set vector length to 1
        // Calculate overlap
        float overlap = sqrt(sumRadiiSquared - (distSquared.x + distSquared.y));
        collisionVector *= overlap;     // Include overlap distance
        return true;
    }
    return false;   // not colliding
}

//=============================================================================
// Axis aligned bounding box collision detection method
// Called by collision()
// Pre:  &ent = The other Entity.
//       &collisionVector = Set by this function.
// Post: Returns true if collision, false otherwise.
//       Sets collisionVector if collision. The collisionVector points in the
//         direction of force that would be applied to this entity as a result
//         of the collision. The magnitude of the collision vector is the
//         distance the entities are overlapping.
//=============================================================================
bool Entity::collideBox(Entity &ent, VECTOR2 &collisionVector)
{
    // if either entity is not active then no collision may occcur
    if (!active || !ent.getActive())
        return false;
    
    // Check for collision using Axis Aligned Bounding Box
    if( (this->getCenterX() + edge.right*getScale() >= ent.getCenterX() + ent.getEdge().left*ent.getScale()) && 
        (this->getCenterX() + edge.left*getScale() <= ent.getCenterX() + ent.getEdge().right*ent.getScale()) &&
        (this->getCenterY() + edge.bottom*getScale() >= ent.getCenterY() + ent.getEdge().top*ent.getScale()) &&
        (this->getCenterY() + edge.top*getScale() <= ent.getCenterY() + ent.getEdge().bottom*ent.getScale()))
    {
        // If we get to here the entities are colliding. The edge with the smallest
        // overlapping section is the edge where the collision is occurring.
        // The collision vector is created perpendicular to the collision edge.

        // Calculate amount of overlap between entities on each edge of box
        float overlapX, overlapY;
        if (this->getCenterX() < ent.getCenterX())      // if this entity left of other entity
        {
            overlapX = (this->getCenterX() + edge.right*getScale()) - (ent.getCenterX() + ent.getEdge().left*ent.getScale());
            collisionVector = VECTOR2(-overlapX, 0);    // collison vector points left
        }
        else    // this entity right of other entity
        {
            overlapX = (ent.getCenterX() + ent.getEdge().right*ent.getScale()) - (this->getCenterX() + edge.left*getScale());
            collisionVector = VECTOR2(overlapX, 0);     // collison vector points right
        }
        if (this->getCenterY() < ent.getCenterY())      // if this entity above other entity
        {
            overlapY = (this->getCenterY() + edge.bottom*getScale()) - (ent.getCenterY() + ent.getEdge().top*ent.getScale());
            if (overlapY < overlapX)                    // if Y overlap is smaller
                collisionVector = VECTOR2(0, -overlapY); // collison vector points up
        }
        else    // this entity below other entity
        {
            overlapY = (ent.getCenterY() + ent.getEdge().bottom*ent.getScale()) - (this->getCenterY() + edge.top*getScale());
            if (overlapY < overlapX)                    // if Y overlap is smaller
                collisionVector = VECTOR2(0, overlapY); // collison vector points down
        }

        return true;    // entities are colliding
    }
    return false;       // entities are not colliding
}

//=============================================================================
// Rotated Box collision detection method
// Called by collision()
// Uses Separating Axis Test to detect collision. 
// The separating axis test:
//   Two boxes are not colliding if their projections onto a line do not overlap.
// The current entity is A the other entity is B
// Post: returns true if collision, false otherwise
//       Sets collisionVector if collision. The collisionVector points in the
//         direction of force that would be applied to this entity as a result
//         of the collision. The magnitude of the collision vector is the
//         distance the entities are overlapping.
//=============================================================================
bool Entity::collideRotatedBox(Entity &entB, VECTOR2 &collisionVector)
{
    VECTOR2 collisionVect1, collisionVect2; // temp collision vectors
    computeRotatedBox();                    // prepare rotated box
    entB.computeRotatedBox();               // prepare rotated box
    if (projectionsOverlap(entB, collisionVect1) && entB.projectionsOverlap(*this, collisionVect2))
    {
        // If we get here the entities are colliding. The edge with the
        // smallest overlapping section is the edge where the collision is
        // occurring. The collision vector is created perpendicular to the
        // collision edge. 

        if (minOverlap < entB.getMinOverlap())  // if this entity has the smallest overlap
        {
            collisionVector = collisionVect1;               // use collisionVect1
            Graphics::Vector2Normalize(&collisionVector);   // normalize the collision vector
            collisionVector *= minOverlap;                  // collision vector contains the overlap distance
        }
        else
        {
            // Use inverted collisionVect2 so the direction is correct for *this entity.
            collisionVector = -collisionVect2;
            Graphics::Vector2Normalize(&collisionVector);   // normalize the collision vector
            collisionVector *= entB.getMinOverlap();        // collision vector contains the overlap distance
        }

        return true;
    }
    return false;
}

//=============================================================================
// This function projects the other entity onto this entity's edges 01 and 03.
// The projection edges 01 and 03 are created for each entity A and B.
// In this diagram the A and B entities are both aligned with the 01
// and 03 axes but that may not be the case with actual entities.
//
// Projections as they appear from this entity
//
//                    entA01min
//                   /     entB01min
//                  /     / entA01max 
//                 /     / /  entB01max
//                /     / /  /
//            0--------------------1
// entB03min..|          ____  
// entA03min..|    _____|_ B |   A = this entity
//            |   | A   | |  |   B = entB entity
// entA03max..|   |_____|_|  |
// entB03max..|         |____|
//            | 
//            |   
//            3
//            
// Pre: The current entity's projections have been calculated in the computeRotatedBox function.
// Post: returns true if projections overlap, false otherwise
//       if projections overlap
//           minOverlap contains minimum overlap distance
//           collisionVector is set
//=============================================================================
bool Entity::projectionsOverlap(Entity &entB, VECTOR2 &collisionVector)
{
    float projection;

    // project other box onto edge01
    projection = graphics->Vector2Dot(&edge01, entB.getCorner(0)); // project corner 0
    entB01min = projection;
    entB01max = projection;
    // for each remaining corner
    for(int c=1; c<4; c++)
    {
        // project corner onto edge01
        projection = graphics->Vector2Dot(&edge01, entB.getCorner(c));
        if (projection < entB01min)
            entB01min = projection;
        else if (projection > entB01max)
            entB01max = projection;
    }
    // if projections do not overlap
    if (entB01min > entA01max || entB01max < entA01min)
        return false;                       // no collision is possible
    // project other box onto edge03
    projection = graphics->Vector2Dot(&edge03, entB.getCorner(0)); // project corner 0
    entB03min = projection;
    entB03max = projection;
    // for each remaining corner
    for(int c=1; c<4; c++)
    {
        // project corner onto edge03
        projection = graphics->Vector2Dot(&edge03, entB.getCorner(c));
        if (projection < entB03min)
            entB03min = projection;
        else if (projection > entB03max)
            entB03max = projection;
    }
    if (entB03min > entA03max || entB03max < entA03min) // if projections do not overlap
        return false;                       // no collision is possible

    // The projections overlap. 
    // Calculate the amount of overlap along edge01 and edge03.
    // Sets a possible collision vector.
    if (entA01min < entB01min)   // if A left of B
    {
        overlap01 = entA01max - entB01min;
        collisionVector = corners[0] - corners[1];
    }
    else    // else, A right of B
    {
        overlap01 = entB01max - entA01min;
        collisionVector = corners[1] - corners[0];
    }
    minOverlap = overlap01;     // set minimum overlap

    if (entA03min < entB03min)  // if A above B
    {
        overlap03 = entA03max - entB03min;
        if (overlap03 < overlap01)
        {
            collisionVector = corners[0] - corners[3];
            minOverlap = overlap03; // minimum overlap
        }
    }
    else    // else, A below B
    {
        overlap03 = entB03max - entA03min;
        if (overlap03 < overlap01)
        {
            collisionVector = corners[3] - corners[0];
            minOverlap = overlap03; // minimum overlap
        }
    }

    return true;                            // projections overlap
}

//=============================================================================
// Rotated Box and Circle collision detection method
// Called by collision()
// Uses separating axis test on edges of box and radius of circle.
// If the circle center is outside the lines extended from the collision box
// edges (also known as the Voronoi region) then the nearest box corner is checked
// for collision using a distance check.
// The nearest corner is determined from the overlap tests.
//
//   Voronoi0 |   | Voronoi1
//         ---0---1---
//            |   |
//         ---3---2---
//   Voronoi3 |   | Voronoi2
//
// Pre: This entity (entA) must be rotated box and other entity (entB) must be circle.
// Post: Returns true if collision, false otherwise.
//       Sets collisionVector if collision. The collisionVector points in the
//         direction of force that would be applied to this entity as a result
//         of the collision. The magnitude of the collision vector is the
//         distance the entities are overlapping.
//=============================================================================
bool Entity::collideRotatedBoxCircle(Entity &entB, VECTOR2 &collisionVector)
{
    float center01, center03, overlap01, overlap03;

    computeRotatedBox();                    // prepare rotated box

    // project circle center onto edge01
    center01 = graphics->Vector2Dot(&edge01, entB.getCenter());
    entB01min = center01 - entB.getRadius()*entB.getScale(); // min and max are Radius from center
    entB01max = center01 + entB.getRadius()*entB.getScale();
    if (entB01min > entA01max || entB01max < entA01min) // if projections do not overlap
        return false;                       // no collision is possible
        
    // project circle center onto edge03
    center03 = graphics->Vector2Dot(&edge03, entB.getCenter());
    entB03min = center03 - entB.getRadius()*entB.getScale(); // min and max are Radius from center
    entB03max = center03 + entB.getRadius()*entB.getScale();
    if (entB03min > entA03max || entB03max < entA03min) // if projections do not overlap
        return false;                       // no collision is possible

    // circle projection overlaps box projection
    // check to see if circle is in voronoi region of collision box
    if(center01 < entA01min && center03 < entA03min)    // if circle in Voronoi0
        return collideCornerCircle(corners[0], entB, collisionVector);
    if(center01 > entA01max && center03 < entA03min)    // if circle in Voronoi1
        return collideCornerCircle(corners[1], entB, collisionVector);
    if(center01 > entA01max && center03 > entA03max)    // if circle in Voronoi2
        return collideCornerCircle(corners[2], entB, collisionVector);
    if(center01 < entA01min && center03 > entA03max)    // if circle in Voronoi3
        return collideCornerCircle(corners[3], entB, collisionVector);

    // If we reach this point the circle and the rotated box are colliding

    // Special case 1, the circle is inside the box (this is called tunneling). 
    // High closing velocities, an unusually long frameTime or very small entities may all contribute to this.
    // This creates two problems:
    //    1. How to determine the collision vector.
    //    2. How to make sure the entities are no longer colliding after bounce function is called.
    //       The bounce function uses the embedded flag.
    //
    // A is this entity (rotated box), B is other entity (circle).
    // A' and B' are entites at previous frame's X,Y
    //                    entA01min
    //                   /   entB01min
    //                  /   /    entB01max 
    //                 /   /    /  entA01max 
    //                /   /    /  /         
    //            0--------------------1    
    //            |                   ___        ___________ 
    //            |                  / B'\      | A'        |
    //            |                  \___/      |           |
    //            |                             |           |
    // entA03min..|    ___________              |___________|
    // entB03min..|   | A  ___    |    
    //            |   |   / B \   |    
    // entB03max..|   |   \___/   |    
    // entA03max..|   |___________|    
    //            3
    //                 case 1    
    //
    // Special case 2, the box is inside the circle (this is called tunneling).
    // A is this entity (rotated box), B is other entity (circle).
    // A' and B' are entites at previous frame's X,Y
    //                   ___
    //                  | A'|
    //                  |___|
    //       ______              ______
    //      /B ___ \            /B'    \
    //     /  | A | \          /        \
    //     \  |___| /          \        /
    //      \______/            \______/
    //                 case 2
    // if box A is inside circle B

    // if circle B is inside box A OR if box A is inside circle B
    if ( (entB01min > entA01min && entB01max < entA01max && entB03min > entA03min && entB03max < entA03max) ||
        (entA01min > entB01min && entA01max < entB01max && entA03min > entB03min && entA03max < entB03max))
    {
        // Treat B as stationary and calculate the velocity of A relative to B.
        VECTOR2 Vdiff = this->getVelocity() - entB.getVelocity();   // velocity difference
        // Use the largest component (X or Y) of Vdiff to determine which edge of box A the collision occurred on.
        // This is a bit of a hack because it is not 100% accurate but that is OK. It's quick and we don't need to
        // be perfect.
        if (abs(Vdiff.x) > abs(Vdiff.y))    // if X velocity > Y velocity
        {
            if (Vdiff.x > 0)                // if A moving right relative to B
            {
                overlap01 = entA01max - entB01min;  // embedded distance
                collisionVector = corners[0] - corners[1];
            }
            else                            // else, A moving left relative to B
            {
                overlap01 = entB01max - entA01min;  // embedded distance
                collisionVector = corners[1] - corners[0];
            }
            Graphics::Vector2Normalize(&collisionVector);   // normalize the collision vector
            collisionVector *= overlap01;   // collision vector contains the embedded distance
        }
        else    // Y velocity >= X velocity
        {
            if (Vdiff.y > 0)                // if A moving down relative to B
            {
                overlap03 = entA03max - entB03min;  // embedded distance
                collisionVector = corners[0] - corners[3];
            }
            else                            // else, B moving up relative to A
            {
                overlap03 = entB03max - entA03min;  // embedded distance
                collisionVector = corners[3] - corners[0];
            }
            Graphics::Vector2Normalize(&collisionVector);   // normalize the collision vector
            collisionVector *= overlap03;   // collision vector contains the embedded distance
        }
        entB.setEmbedded(true);     // entity B is completely contained within the collision area of A

        return true;
    }
    else
        entB.setEmbedded(false);


    // Normal case
    // Circle not in voronoi region so it is colliding with edge of box.
    // The edge with the smallest overlapping section is the edge where the
    // collision is occurring. The collision vector is created perpendicular
    // to the collision edge. The projection edges are 01 and 03.
    // A is this entity (rotated box), B is other entity (circle).
    //                    entA01min
    //                   /   entB01min
    //                  /   /    entB01max 
    //                 /   /    /  entA01max 
    //                /   /    /  /         
    //            0--------------------1    
    // entB03min..|        ___              
    // entA03min..|    ___/ B \__           
    // entB03max..|   |   \___/  |          
    //            |   |          |          
    // entA03max..|   |  A(this) |          
    //            |   |__________|          
    //            |             
    //            |    normal case  
    //            3
    //            
    if (entA01min < entB01min)   // if A left of B
    {
        overlap01 = entA01max - entB01min;          // Overlap along 0..1 axis
        collisionVector = corners[0] - corners[1];
    }
    else    // else, A right of B
    {
        overlap01 = entB01max - entA01min;          // Overlap along 0..1 axis
        collisionVector = corners[1] - corners[0];
    }
    if (entA03min < entB03min)   // if A above B
    {
        overlap03 = entA03max - entB03min;          // Overlap along 0..3 axis
        if (overlap03 < overlap01)
            collisionVector = corners[0] - corners[3];
    }
    else    // else, A below B
    {
        overlap03 = entB03max - entA03min;          // Overlap along 0..3 axis
        if (overlap03 < overlap01)
            collisionVector = corners[3] - corners[0];
    }
    Graphics::Vector2Normalize(&collisionVector);   // normalize the collision vector
    if (overlap03 < overlap01)
        collisionVector *= overlap03;
    else
        collisionVector *= overlap01;   // collision vector contains the overlap distance

    return true;
}

//=============================================================================
// The box corner is checked for collision with circle using a distance check.
// Called by collideRotatedBoxCircle(). This entity is rotated box. The other
// entity is the circle.
// Post: returns true if collision, false otherwise
//       Sets collisionVector if collision. The collisionVector points in the
//         direction of force that would be applied to this entity as a result
//         of the collision. The magnitude of the collision vector is the
//         distance the entities are overlapping.
//=============================================================================
bool Entity::collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector)
{
    distSquared = corner - *ent.getCenter();            // corner - circle
    distSquared.x = distSquared.x * distSquared.x;      // difference squared
    distSquared.y = distSquared.y * distSquared.y;

    // Calculate the sum of the radii, then square it
    sumRadiiSquared = ent.getRadius()*ent.getScale();   // (0 + circleR)
    sumRadiiSquared *= sumRadiiSquared;                 // square it

    // if corner and circle are colliding
    if(distSquared.x + distSquared.y <= sumRadiiSquared)
    {
        // Set collision vector between corner and center
        collisionVector = corner - *ent.getCenter();
        Graphics::Vector2Normalize(&collisionVector);   // set vector length to 1
        // Calculate overlap
        float overlap = sqrt(sumRadiiSquared - (distSquared.x + distSquared.y));
        collisionVector *= overlap;     // Include overlap distance
        return true;
    }
    return false;
}

//=============================================================================
// Compute corners of rotated box, projection edges and min and max projections
// 0---1  corner numbers
// |   |
// 3---2
// See chapter 6 page 153
//=============================================================================
void Entity::computeRotatedBox()
{
    if(rotatedBoxReady)
        return;
    float projection;

    VECTOR2 rotatedX(cos(spriteData.angle), sin(spriteData.angle));
    VECTOR2 rotatedY(-sin(spriteData.angle), cos(spriteData.angle));

    const VECTOR2 *center = getCenter();
    corners[0] = *center + rotatedX * ((float)edge.left*getScale())  +
                           rotatedY * ((float)edge.top*getScale());
    corners[1] = *center + rotatedX * ((float)edge.right*getScale()) + 
                           rotatedY * ((float)edge.top*getScale());
    corners[2] = *center + rotatedX * ((float)edge.right*getScale()) + 
                           rotatedY * ((float)edge.bottom*getScale());
    corners[3] = *center + rotatedX * ((float)edge.left*getScale())  +
                           rotatedY * ((float)edge.bottom*getScale());

    // corners[0] is used as origin
    // The two edges connected to corners[0] are used as the projection lines
    edge01 = VECTOR2(corners[1].x - corners[0].x, corners[1].y - corners[0].y);
    graphics->Vector2Normalize(&edge01);
    edge03 = VECTOR2(corners[3].x - corners[0].x, corners[3].y - corners[0].y);
    graphics->Vector2Normalize(&edge03);

    // this entities min and max projection onto edges
    projection = graphics->Vector2Dot(&edge01, &corners[0]);
    entA01min = projection;
    entA01max = projection;
    // project onto edge01
    projection = graphics->Vector2Dot(&edge01, &corners[1]);
    if (projection < entA01min)
        entA01min = projection;
    else if (projection > entA01max)
        entA01max = projection;
    // project onto edge03
    projection = graphics->Vector2Dot(&edge03, &corners[0]);
    entA03min = projection;
    entA03max = projection;
    projection = graphics->Vector2Dot(&edge03, &corners[3]);
    if (projection < entA03min)
        entA03min = projection;
    else if (projection > entA03max)
        entA03max = projection;

    rotatedBoxReady = true;
}

//=============================================================================
// Pixel Perfect collision detection method
// Called by collision()
// If the graphics card does not support a stencil buffer then CIRCLE
// collision is used.
// This function waits for the graphics card to render the last frame and return
// the collision query pixel count. To avoid slowing down your game, use a
// simple collison test first to eliminate entities that are not colliding.
// Post: Returns true if collision, false otherwise.
//       Uses collideCircle to set the collision vector.  Be sure to set the
//       collision radius of each entity.
//=============================================================================
bool Entity::collidePixelPerfect(Entity &ent, VECTOR2 &collisionVector)
{
    if(graphics->getStencilSupport() == false)  // if stencil not supported
        return (collideCircle(ent, collisionVector));   // use CIRCLE collision

    // get fresh texture because they may have been released
    ent.spriteData.texture = ent.textureManager->getTexture();
    spriteData.texture = textureManager->getTexture();

    // if pixels are colliding
    pixelsColliding = graphics->pixelCollision(ent.getSpriteData(), this->getSpriteData());
    if(pixelsColliding > 0)
    {
        collideCircle(ent, collisionVector);    // set collisionVector
        return true;
    }
    return false;
}

//=============================================================================
// Is this Entity outside the specified rectangle
// Post: returns true if outside rect, false otherwise
//=============================================================================
bool Entity::outsideRect(RECT rect)
{
    if( spriteData.x + spriteData.width*getScale() < rect.left || 
        spriteData.x > rect.right ||
        spriteData.y + spriteData.height*getScale() < rect.top || 
        spriteData.y > rect.bottom)
        return true;
    return false;
}

//=============================================================================
// damage
// This entity has been damaged by a weapon.
// Override this function in the inheriting class.
//=============================================================================
void Entity::damage(int weapon)
{}

//=============================================================================
// Entity bounces after collision with another entity
// Pre: ent is the other entity.
//      The collisionVector has been set with direction of force that should be
//      applied to this entity. The magnitude of collisionVector is the
//      distance the two entities are overlapping.
// Post: The deltaV of the current entity is set. The deltaV will be applied
//      to this entity in the update function.
//      This entity is moved in the direction of the collison vector by a
//      distance proportinal to the mass ratio with the other entity.
//=============================================================================
void Entity::bounce(VECTOR2 &collisionVector, Entity &ent)
{
    float cUVdotVdiff;
    VECTOR2 Vdiff = ent.getVelocity() - velocity;
    VECTOR2 cUV = collisionVector;              // collision unit vector
    Graphics::Vector2Normalize(&cUV);
    cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);   // use velocity difference
    float massRatio = 2.0f;
    if (getMass() != 0)
        massRatio *= (ent.getMass() / (getMass() + ent.getMass()));
    if(massRatio < 0.1f)
        massRatio = 0.1f;

    // bounce
    deltaV += ((massRatio * cUVdotVdiff) * cUV);
    deltaV *= bounciness;   // how bouncy is this entity

    // if this entity is embedded inside the other entity or the other entity does not react to collision
    if (embedded || ent.getNoBounce())
    {
        // Move this entity out of collision along the collision vector.
        // The collision vector contains the embedded or overlap distance
        this->setX(getX() + collisionVector.x);
        this->setY(getY() + collisionVector.y);
    }
    else    // the other entity does bounce
    {
        // Move this entity along collision vector using massRatio
        // The collision vector contains the embedded distance.
        this->setX(getX() + collisionVector.x * massRatio);
        this->setY(getY() + collisionVector.y * massRatio);
    }
}

//=============================================================================
// Force of gravity on this entity from other entity
// Adds the gravitational force to the velocity vector of this entity
// force = GRAVITY * m1 * m2 / r*r
//                    2              2
//  r*r  =   (Ax - Bx)   +  (Ay - By)
//=============================================================================
void Entity::gravityForce(Entity *ent, float frameTime)
{
    // if either entity is not active then no gravity effect
    if (!active || !ent->getActive())
        return ;

    rr = pow((ent->getCenterX() - getCenterX()),2) + 
            pow((ent->getCenterY() - getCenterY()),2);
    force = gravity * ent->getMass() * mass/rr;

    // --- Using vector math to create gravity vector ---
    // Create vector between entities
    VECTOR2 gravityV(ent->getCenterX() - getCenterX(),
                        ent->getCenterY() - getCenterY());
    // Normalize the vector
    Graphics::Vector2Normalize(&gravityV);
    // Multipy by force of gravity to create gravity vector
    gravityV *= force * frameTime;
    // Add gravity vector to moving velocity vector to change direction
    velocity += gravityV;
}
