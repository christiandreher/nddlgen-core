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

#ifndef NDDLGEN_MATH_ORIENTEDBOUNDINGBOX_H_
#define NDDLGEN_MATH_ORIENTEDBOUNDINGBOX_H_

#include <vector>

#include <boost/shared_ptr.hpp>

#include <nddlgen/math/Vector.h>

namespace nddlgen
{
	namespace math
	{
		class Cuboid;
		typedef boost::shared_ptr<nddlgen::math::Cuboid> CuboidPtr;
	}
}

class nddlgen::math::Cuboid
{

	private:

		std::vector<nddlgen::math::VectorPtr> _vertices;
		nddlgen::math::VectorPtr _normalXAxis;
		nddlgen::math::VectorPtr _normalYAxis;
		nddlgen::math::VectorPtr _normalZAxis;

	public:

		Cuboid(std::vector<nddlgen::math::VectorPtr> vertices,
				nddlgen::math::VectorPtr normalXAxis,
				nddlgen::math::VectorPtr normalYAxis,
				nddlgen::math::VectorPtr normalZAxis);
		virtual ~Cuboid();

		nddlgen::math::VectorPtr getVertex(int index);
		nddlgen::math::VectorPtr getNormalXAxis();
		nddlgen::math::VectorPtr getNormalYAxis();
		nddlgen::math::VectorPtr getNormalZAxis();

};

#endif
