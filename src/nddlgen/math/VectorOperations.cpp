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

#include <nddlgen/math/VectorOperations.h>

nddlgen::math::VectorOperations::VectorOperations()
{

}

nddlgen::math::VectorOperations::~VectorOperations()
{

}

nddlgen::math::VectorPtr nddlgen::math::VectorOperations::plus(nddlgen::math::VectorPtr summand1, nddlgen::math::VectorPtr summand2)
{
	double x = summand1->getX() + summand2->getX();
	double y = summand1->getY() + summand2->getY();
	double z = summand1->getZ() + summand2->getZ();

	nddlgen::math::VectorPtr sum(new Vector(x, y, z));

	return sum;
}

nddlgen::math::VectorPtr nddlgen::math::VectorOperations::minus(nddlgen::math::VectorPtr minuend, nddlgen::math::VectorPtr subtrahend)
{
	double x = minuend->getX() - subtrahend->getX();
	double y = minuend->getY() - subtrahend->getY();
	double z = minuend->getZ() - subtrahend->getZ();

	nddlgen::math::VectorPtr difference(new Vector(x, y, z));

	return difference;
}

double nddlgen::math::VectorOperations::dotProduct(nddlgen::math::VectorPtr a, nddlgen::math::VectorPtr b)
{
	double dot = 0;

	dot += a->getX() * b->getX();
	dot += a->getY() * b->getY();
	dot += a->getZ() * b->getZ();

	return dot;
}

nddlgen::math::VectorPtr nddlgen::math::VectorOperations::crossProduct(nddlgen::math::VectorPtr a, nddlgen::math::VectorPtr b)
{
	double x = (a->getY() * b->getZ()) - (a->getZ() * b->getY());
	double y = (a->getZ() * b->getX()) - (a->getX() * b->getZ());
	double z = (a->getX() * b->getY()) - (a->getY() * b->getX());

	nddlgen::math::VectorPtr cross(new Vector(x, y, z));

	return cross;
}
