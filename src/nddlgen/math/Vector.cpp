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

#include <nddlgen/math/Vector.h>

nddlgen::math::Vector::Vector(double x, double y, double z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

nddlgen::math::Vector::~Vector()
{

}

double nddlgen::math::Vector::getX()
{
	return this->_x;
}

double nddlgen::math::Vector::getY()
{
	return this->_y;
}

double nddlgen::math::Vector::getZ()
{
	return this->_z;
}

bool nddlgen::math::Vector::isNull()
{
	return (this->_x == 0 && this->_y == 0 && this->_z == 0);
}
