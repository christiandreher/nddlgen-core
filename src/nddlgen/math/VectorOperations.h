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

#ifndef NDDLGEN_MATH_VECTOROPERATIONS_H_
#define NDDLGEN_MATH_VECTOROPERATIONS_H_

#include <boost/shared_ptr.hpp>

#include <nddlgen/math/Vector.h>

namespace nddlgen
{
	namespace math
	{
		class VectorOperations;
	}
}

class nddlgen::math::VectorOperations
{

	private:

		VectorOperations();
		virtual ~VectorOperations();

	public:

		static nddlgen::math::VectorPtr plus(nddlgen::math::VectorPtr summand1, nddlgen::math::VectorPtr summand2);
		static nddlgen::math::VectorPtr minus(nddlgen::math::VectorPtr minuend, nddlgen::math::VectorPtr subtrahend);
		static double dotProduct(nddlgen::math::VectorPtr a, nddlgen::math::VectorPtr b);
		static nddlgen::math::VectorPtr crossProduct(nddlgen::math::VectorPtr a, nddlgen::math::VectorPtr b);

};

#endif
