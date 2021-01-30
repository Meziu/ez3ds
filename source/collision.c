#include "little3ds/collision.h"

CollisionBox newCollisionBox(Vector2D p_pos, Vector2D p_bounds)
{
    CollisionBox res;

    res.position = p_pos;
    res.boundaries = p_bounds;

    return res;
}

bool checkCollision(CollisionBox* box1, CollisionBox* box2)
{
    if (box1->position.x - (box1->boundaries.x/2) < box2->position.x + (box2->boundaries.x/2) && // left1 will detect right2
		box1->position.x + (box1->boundaries.x/2) > box2->position.x - (box2->boundaries.x/2) && // right1 will detect left2
		box1->position.y - (box1->boundaries.y/2) < box2->position.y + (box2->boundaries.y/2) && // top1 will detect bottom2
		box1->position.y + (box1->boundaries.y/2) > box2->position.y - (box2->boundaries.y/2))   // bottom1 will detect top2
    { 
    	return true;
	}
	return false;
}