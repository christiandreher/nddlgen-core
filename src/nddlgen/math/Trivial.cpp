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

#include <nddlgen/math/Trivial.h>

nddlgen::math::Trivial::Trivial()
{

}

nddlgen::math::Trivial::~Trivial()
{

}

int nddlgen::math::Trivial::min(int a, int b)
{
	if (a <= b)
	{
		return a;
	}

	return b;
}

float nddlgen::math::Trivial::min(float a, float b)
{
	if (a <= b)
	{
		return a;
	}

	return b;
}

double nddlgen::math::Trivial::min(double a, double b)
{
	if (a <= b)
	{
		return a;
	}

	return b;
}

int nddlgen::math::Trivial::max(int a, int b)
{
	if (a >= b)
	{
		return a;
	}

	return b;
}

float nddlgen::math::Trivial::max(float a, float b)
{
	if (a >= b)
	{
		return a;
	}

	return b;
}

double nddlgen::math::Trivial::max(double a, double b)
{
	if (a >= b)
	{
		return a;
	}

	return b;
}
