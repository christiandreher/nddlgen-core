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

#include <nddlgen/math/CuboidOperations.h>

nddlgen::math::CuboidOperations::CuboidOperations()
{

}

nddlgen::math::CuboidOperations::~CuboidOperations()
{

}

void nddlgen::math::CuboidOperations::roll(std::vector<nddlgen::math::VectorPtr> vertices, double angle)
{
	angle *= - 1; // Invert angle since roll/pitch/yaw are considered to be counter-clockwise, while angles are clockwise

	double sinAngle = std::sin(angle);
	double cosAngle = std::cos(angle);

	for (int i = 0; i < 8 /* amount of vertices of a cuboid */; i++)
	{
		VectorPtr vector = vertices[i];

		double y = vector->getY();
		double z = vector->getZ();

		double rotatedY = y * cosAngle - z * sinAngle;
		double rotatedZ = z * cosAngle + y * sinAngle;

		vector->setY(rotatedY);
		vector->setZ(rotatedZ);
	}
}

void nddlgen::math::CuboidOperations::pitch(std::vector<nddlgen::math::VectorPtr> vertices, double angle)
{
	angle *= - 1; // Invert angle since roll/pitch/yaw are considered to be counter-clockwise, while angles are clockwise

	double sinAngle = std::sin(angle);
	double cosAngle = std::cos(angle);

	for (int i = 0; i < 8 /* amount of vertices of a cuboid */; i++)
	{
		VectorPtr vector = vertices[i];

		double x = vector->getX();
		double z = vector->getZ();

		double rotatedX = x * cosAngle - z * sinAngle;
		double rotatedZ = z * cosAngle + x * sinAngle;

		vector->setX(rotatedX);
		vector->setZ(rotatedZ);
	}
}

void nddlgen::math::CuboidOperations::yaw(std::vector<nddlgen::math::VectorPtr> vertices, double angle)
{
	angle *= - 1; // Invert angle since roll/pitch/yaw are considered to be counter-clockwise, while angles are clockwise

	double sinAngle = std::sin(angle);
	double cosAngle = std::cos(angle);

	for (int i = 0; i < 8 /* amount of vertices of a cuboid */; i++)
	{
		VectorPtr vector = vertices[i];

		double x = vector->getX();
		double y = vector->getY();

		double rotatedX = x * cosAngle - y * sinAngle;
		double rotatedY = y * cosAngle + x * sinAngle;

		vector->setX(rotatedX);
		vector->setY(rotatedY);
	}
}
