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

#ifndef NDDLGEN_MATH_VECTOR_H_
#define NDDLGEN_MATH_VECTOR_H_

#include <boost/shared_ptr.hpp>

namespace nddlgen
{
	namespace math
	{
		class Vector;
		typedef boost::shared_ptr<nddlgen::math::Vector> VectorPtr;
	}
}

class nddlgen::math::Vector
{

	private:

		double _x;
		double _y;
		double _z;

	public:

		Vector(double x, double y, double z);
		virtual ~Vector();

		double getX();
		double getY();
		double getZ();

		bool isNull();

};

#endif
