/**
 * Copyright 2015 Christian Dreher (dreher@charlydelta.org)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NDDLGEN_CONTROLLERS_COLLISIONDETECTIONCONTROLLER_H_
#define NDDLGEN_CONTROLLERS_COLLISIONDETECTIONCONTROLLER_H_

#include <nddlgen/math/Cuboid.h>
#include <nddlgen/math/SeparatingAxisTheoremTest.h>

namespace nddlgen
{
	namespace controllers
	{
		class CollisionDetectionController;
	}
}

/**
 * Controller to test for collisions between to objects.
 *
 * @author Christian Dreher
 */
class nddlgen::controllers::CollisionDetectionController
{

	private:

		/**
		 * Private constructor to prevent instantiation.
		 */
		CollisionDetectionController();

		/**
		 * Destructor to free memory.
		 */
		virtual ~CollisionDetectionController();

	public:

		/**
		 * Test for intersection between to objects. Eventually, this should be changed to
		 * also allow cylindric shaped bounding boxes
		 *
		 * @param box1 First box
		 * @param box2 Second box
		 *
		 * @return True, if box1 and box2 intersect, false if not
		 */
		static bool doesIntersect(nddlgen::math::CuboidPtr box1, nddlgen::math::CuboidPtr box2);

};

#endif
