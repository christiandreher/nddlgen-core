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

#include <nddlgen/math/Cuboid.h>

nddlgen::math::Cuboid::Cuboid(std::vector<nddlgen::math::VectorPtr> vertices,
		nddlgen::math::VectorPtr normalXAxis,
		nddlgen::math::VectorPtr normalYAxis,
		nddlgen::math::VectorPtr normalZAxis)
{
	if (vertices.size() != 8)
	{
		// todo: throw proper exception
		throw "A bounding box must be defined by exactly 8 vertices.";
	}

	this->_vertices = vertices;
	this->_normalXAxis = normalXAxis;
	this->_normalYAxis = normalYAxis;
	this->_normalZAxis = normalZAxis;
}

nddlgen::math::Cuboid::~Cuboid()
{

}

nddlgen::math::VectorPtr nddlgen::math::Cuboid::getVertex(int index)
{
	return this->_vertices.at(index);
}

nddlgen::math::VectorPtr nddlgen::math::Cuboid::getNormalXAxis()
{
	return this->_normalXAxis;
}

nddlgen::math::VectorPtr nddlgen::math::Cuboid::getNormalYAxis()
{
	return this->_normalYAxis;
}

nddlgen::math::VectorPtr nddlgen::math::Cuboid::getNormalZAxis()
{
	return this->_normalZAxis;
}
