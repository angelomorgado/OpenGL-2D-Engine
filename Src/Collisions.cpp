#include <Collisions.hpp>

#include <glm/glm.hpp>

namespace Collisions {
    /* 
        Check if the two objects are colliding with each other (AABB)
        Returns true if the objects are colliding, false otherwise
    */
    bool checkAABBCollision(Object& obj1, Object& obj2) {
        glm::vec2 obj1Position = obj1.getPosition();
        glm::vec2 obj1Size = obj1.getSize();
        glm::vec2 obj2Position = obj2.getPosition();
        glm::vec2 obj2Size = obj2.getSize();

        // collision x-axis?
        bool collisionX = obj1Position.x + obj1Size.x / 2 >= obj2Position.x - obj2Size.x / 2 &&
            obj2Position.x + obj2Size.x / 2 >= obj1Position.x - obj1Size.x / 2;
        // collision y-axis?
        bool collisionY = obj1Position.y + obj1Size.y / 2 >= obj2Position.y  - obj2Size.y / 2 &&
            obj2Position.y + obj2Size.y / 2 >= obj1Position.y  - obj1Size.y / 2;
        // collision only if on both axes
        return collisionX && collisionY;
    }

    /* 
        Check if the two objects are colliding with each other (AABB)
        Returns:
            - 0: No collision
            - 1: Collision on the Y axis
            - 2: Collision on the X axis
            - 3: Collision on the corner
    */
    unsigned int checkAABBCollisionComplex(Object& obj1, Object& obj2) {
        glm::vec2 obj1Position = obj1.getPosition();
        glm::vec2 obj1Size = obj1.getSize();
        glm::vec2 obj2Position = obj2.getPosition();
        glm::vec2 obj2Size = obj2.getSize();

        // Calculate the edges of both objects
        float obj1Left = obj1Position.x - obj1Size.x / 2;
        float obj1Right = obj1Position.x + obj1Size.x / 2;
        float obj1Top = obj1Position.y + obj1Size.y / 2;
        float obj1Bottom = obj1Position.y - obj1Size.y / 2;

        float obj2Left = obj2Position.x - obj2Size.x / 2;
        float obj2Right = obj2Position.x + obj2Size.x / 2;
        float obj2Top = obj2Position.y + obj2Size.y / 2;
        float obj2Bottom = obj2Position.y - obj2Size.y / 2;

        // Check for collision
        bool collisionX = obj1Right >= obj2Left && obj2Right >= obj1Left;
        bool collisionY = obj1Top >= obj2Bottom && obj2Top >= obj1Bottom;

        // Determine collision type
        if (collisionX && collisionY) {
            // Calculate overlap on each axis
            float overlapX = std::min(obj1Right, obj2Right) - std::max(obj1Left, obj2Left);
            float overlapY = std::min(obj1Top, obj2Top) - std::max(obj1Bottom, obj2Bottom);

            if (overlapX < overlapY) {
                return 2; // Collision primarily on X axis
            } else if (overlapY < overlapX) {
                return 1; // Collision primarily on Y axis
            } else {
                return 3; // Collision on the corner (equal overlap)
            }
        }

        return 0; // No collision
    }


    /* 
        Check if a circle is colliding with an object (AABB)
        Returns true if the circle is colliding with the object, false otherwise
    */
    bool checkCircleCollision(Object& circle, Object& obj) { 
        // Get center point of circle
        glm::vec2 circle_center = circle.getPosition();

        // Calculate AABB info (center, half-extents)
        glm::vec2 aabb_half_extents = obj.getSize() / 2.0f;
        glm::vec2 aabb_center = obj.getPosition();

        // Get difference vector between both centers
        glm::vec2 difference = circle_center - aabb_center;
        glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

        // Add clamped value to AABB_center and we get the value of box closest to circle
        glm::vec2 closest = aabb_center + clamped;

        // Retrieve vector between center circle and closest point AABB and check if length <= radius
        difference = closest - circle_center;

        return glm::length(difference) < circle.getSize().x / 2.0f;
    }

    /* 
        Check if a circle is colliding with an object (AABB)
        Returns:
            - 0: No collision
            - 1: Collision on the Y axis
            - 2: Collision on the X axis
            - 3: Collision on the corner

    */
    unsigned int checkCircleCollisionComplex(Object& circle, Object& obj) { 
        // Get center point of circle
        glm::vec2 circle_center = circle.getPosition();

        // Calculate AABB info (center, half-extents)
        glm::vec2 aabb_half_extents = obj.getSize() / 2.0f;
        glm::vec2 aabb_center = obj.getPosition();

        // Get difference vector between both centers
        glm::vec2 difference = circle_center - aabb_center;
        glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

        // Add clamped value to AABB_center and we get the value of box closest to circle
        glm::vec2 closest = aabb_center + clamped;

        // Retrieve vector between center circle and closest point AABB and check if length <= radius
        difference = closest - circle_center;

        if(glm::length(difference) < circle.getSize().x / 2.0f) {
            float offset = 0.01;

            bool collisionY = circle.getPosition().x > (obj.getPosition().x - obj.getSize().x / 2 - offset) && circle.getPosition().x < (obj.getPosition().x + obj.getSize().x / 2 + offset);

            bool collisionX = circle.getPosition().y > (obj.getPosition().y - obj.getSize().y / 2 - offset) && circle.getPosition().y < (obj.getPosition().y + obj.getSize().y / 2 + offset);

            if (collisionY) {
                return 1; // Collision on the Y axis
            } else if (collisionX) {
                return 2; // Collision on the X axis
            } else {
                return 3; // Collision on the corner
            }
        } else {
            return 0; // No collision
        }
    }

    /**
     * Check if the object is colliding with the borders of the window.
     *      
     * @param obj The object being checked.
     * 
     * @return A code representing the boundary where `obj1` is exceeding `obj2`:
     *         - 0: if the object is not colliding with the window
     *         - 2: if the object is colliding with the top border
     *         - 3: if the object is colliding with the bottom border
     *         - 4: if the object is colliding with the left border
     *         - 5: if the object is colliding with the right border
     *         - 6+ : if the object is colliding with multiple borders
     */
    unsigned int  checkWindowCollision(Object& obj) {
        glm::vec2 objSize     = obj.getSize();
        glm::vec2 objPosition = obj.getPosition();

        unsigned int collisionX = 0;
        unsigned int collisionY = 0;  

        // Y axis
        // Top
        if(objPosition.y + objSize.y/2.0f >= 1.0f) {
            collisionY = 2;
        // Bottom
        } else if(objPosition.y - objSize.y/2.0f <= -1.0f) {
            collisionY = 3;
        }

        // X axis
        // Left
        if(objPosition.x - objSize.x/2.0f <= -1.0f) {
            collisionX = 4;
        // Right
        } else if(objPosition.x + objSize.x/2.0f >= 1.0f) {
            collisionX = 5;
        }

        // No collision
        return collisionX + collisionY;
    }

    /**
     * Detects if obj1 overlaps the boundaries of obj2.
     * 
     * This function checks whether any part of `obj1` exceeds the boundaries of `obj2` on both the X and Y axes. So the object needs to be placed inside the container object.
     * 
     * @param obj1 The object whose boundaries are being checked.
     * @param obj2 The container object whose boundaries define the limits.
     * 
     * @return A code representing the boundary where `obj1` is exceeding `obj2`:
     *         - 2: Exceeded the top boundary
     *         - 3: Exceeded the bottom boundary
     *         - 4: Exceeded the right boundary
     *         - 5: Exceeded the left boundary
     *         - 6+ : If multiple boundaries are exceeded, the return value will be a combination of these codes.
     */
    unsigned int detectBoundaryOverlap(Object& obj1, Object& obj2) {
        glm::vec2 obj1Size     = obj1.getSize();
        glm::vec2 obj1Position = obj1.getPosition();
        
        glm::vec2 obj2Size     = obj2.getSize();
        glm::vec2 obj2Position = obj2.getPosition();

        glm::vec2 obj1HalfSize = obj1Size / 2.0f;
        glm::vec2 obj2HalfSize = obj2Size / 2.0f;

        unsigned int collisionX = 0;
        unsigned int collisionY = 0;        

        // Y-axis boundary checks
        if (obj1Position.y + obj1HalfSize.y > obj2Position.y + obj2HalfSize.y) {
            collisionY = 2;  // Top boundary exceeded
        }
        else if (obj1Position.y - obj1HalfSize.y < obj2Position.y - obj2HalfSize.y) {
            collisionY = 3;  // Bottom boundary exceeded
        }

        // X-axis boundary checks
        if (obj1Position.x + obj1HalfSize.x > obj2Position.x + obj2HalfSize.x) {
            collisionX = 4;  // Right boundary exceeded
        }
        else if (obj1Position.x - obj1HalfSize.x < obj2Position.x - obj2HalfSize.x) {
            collisionX = 5;  // Left boundary exceeded
        }

        return collisionX + collisionY;
    }
}