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

#ifndef NDDLGEN_MATH_CUBOIDOPERATIONS_H_
#define NDDLGEN_MATH_CUBOIDOPERATIONS_H_

#include <cmath>
#include <vector>

#include <nddlgen/math/Vector.h>

namespace nddlgen
{
	namespace math
	{
		class CuboidOperations;
	}
}

class nddlgen::math::CuboidOperations
{

	private:

		CuboidOperations();
		virtual ~CuboidOperations();

	public:

		static void roll(std::vector<nddlgen::math::VectorPtr> vertices, double angle);
		static void pitch(std::vector<nddlgen::math::VectorPtr> vertices, double angle);
		static void yaw(std::vector<nddlgen::math::VectorPtr> vertices, double angle);

};

#endif
