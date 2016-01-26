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

#ifndef NDDLGEN_MATH_SEPARATINGAXISTHEOREMTEST_H_
#define NDDLGEN_MATH_SEPARATINGAXISTHEOREMTEST_H_

#include <limits>

#include <nddlgen/math/Vector.h>
#include <nddlgen/math/Cuboid.h>
#include <nddlgen/math/Trivial.h>
#include <nddlgen/math/VectorOperations.h>

namespace nddlgen
{
	namespace math
	{
		class SeparatingAxisTheoremTest;
	}
}

/**
 * Implementation of the separating axis theorem (SAT) test.
 * Can be used to check for collisions between cuboids.
 *
 * @author Christian Dreher
 */
class nddlgen::math::SeparatingAxisTheoremTest
{

	private:

		/**
		 * Private constructor to prevent instantiation.
		 */
		SeparatingAxisTheoremTest();

		/**
		 * Destructor to free memory.
		 */
		virtual ~SeparatingAxisTheoremTest();

	public:

		/**
		 * Checks if two objects (box1 and box2) do intersect by using the seperating axis theorem.
		 *
		 * @param box1 First box
		 * @param box2 Second box
		 *
		 * @return True, if boxes intersect according to SAT, false if not
		 */
		static bool doesIntersect(nddlgen::math::CuboidPtr box1, nddlgen::math::CuboidPtr box2);

		/**
		 * Checks if the projection of two objects (box1 and box2) do intersect, when projected
		 * to axis. From: http://gamedev.stackexchange.com/a/92055/74703
		 * Translated from a C#/Unity code example
		 * Courtesy of Acegikmo (stackoverflow community member)
		 *
		 * @param box1 First box to be projected
		 * @param box2 Second box to be projected
		 * @param axis Axis where the objects should be projected to
		 *
		 * @return True, if the projections of the objects do intersect when projected to axis, false if not.
		 */
		static bool doesProjectionIntersect(nddlgen::math::CuboidPtr box1,
				nddlgen::math::CuboidPtr box2,
				nddlgen::math::VectorPtr axis);

};

#endif
