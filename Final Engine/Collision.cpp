#include "Collision.h"

namespace Collision

	/*struct BB {
	  glm::vec3 pos;
	  glm::vec3 box_dims;
    };*/
{
	bool detected = false;

	bool collisionDetection(Entity* ent1, Entity* ent2)
	{


		//	change this to be placed into each entity
		//	allows for flexibilty with collision boxes
		glm::vec3 box1{ 1,1,1 };
		glm::vec3 box2{ 1,1,1 };

		bool p1collision_z = (ent1->getPosition().z - box1.z) > (ent2->getPosition().z - box2.z) &&
							 (ent1->getPosition().z - box1.z) < (ent2->getPosition().z + box2.z);
		
		bool p2collision_z = (ent1->getPosition().z + box1.z) > (ent2->getPosition().z - box2.z) &&
							 (ent1->getPosition().z + box1.z) < (ent2->getPosition().z + box2.z);
		
		bool p1collision_y = (ent1->getPosition().y - box1.y) > (ent2->getPosition().y - box2.y) &&
							 (ent1->getPosition().y - box1.y) < (ent2->getPosition().y + box2.y);
		
		bool p2collision_y = (ent1->getPosition().y + box1.y) > (ent2->getPosition().y - box2.y) &&
							 (ent1->getPosition().y + box1.y) < (ent2->getPosition().y + box2.y);
		
		if ((p1collision_y || p2collision_y) && (p1collision_z || p2collision_z))
		{
			detected = true;
		}
		else detected = false;

		return detected;
	}
	
	//doesn't work
	bool returnDetected()
	{
		return detected;
	}
}
