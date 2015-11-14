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

#include <nddlgen/math/SeparatingAxisTheoremTest.h>

nddlgen::math::SeparatingAxisTheoremTest::SeparatingAxisTheoremTest()
{

}

nddlgen::math::SeparatingAxisTheoremTest::~SeparatingAxisTheoremTest()
{

}

bool nddlgen::math::SeparatingAxisTheoremTest::doesIntersect(nddlgen::math::CuboidPtr box1,
		nddlgen::math::CuboidPtr box2)
{
	if (!SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2, box1->getNormalXAxis())
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2, box1->getNormalYAxis())
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2, box1->getNormalZAxis())
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2, box2->getNormalXAxis())
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2, box2->getNormalYAxis())
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2, box2->getNormalZAxis())
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalXAxis(), box2->getNormalXAxis()))
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalXAxis(), box2->getNormalYAxis()))
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalXAxis(), box2->getNormalZAxis()))
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalYAxis(), box2->getNormalXAxis()))
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalYAxis(), box2->getNormalYAxis()))
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalYAxis(), box2->getNormalZAxis()))
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalZAxis(), box2->getNormalXAxis()))
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalZAxis(), box2->getNormalYAxis()))
		|| !SeparatingAxisTheoremTest::doesProjectionIntersect(box1, box2,
				VectorOperations::crossProduct(box1->getNormalZAxis(), box2->getNormalZAxis())))
	{
		return false;
	}

	return true;
}

bool nddlgen::math::SeparatingAxisTheoremTest::doesProjectionIntersect(nddlgen::math::CuboidPtr box1,
		nddlgen::math::CuboidPtr box2,
		nddlgen::math::VectorPtr axis)
{
	if (axis->isNull())
	{
		return true;
	}

	double aMin = std::numeric_limits<double>::max();
	double aMax = std::numeric_limits<double>::min();
	double bMin = std::numeric_limits<double>::max();
	double bMax = std::numeric_limits<double>::min();

	for (int i = 0; i < 8; i++)
	{
		double aDist = VectorOperations::dotProduct(box1->getVertex(i), axis);
		aMin = Trivial::min(aDist, aMin);
		aMax = Trivial::max(aDist, aMax);

		double bDist = VectorOperations::dotProduct(box2->getVertex(i), axis);
		bMin = Trivial::min(bDist, bMin);
		bMax = Trivial::max(bDist, bMax);
	}

	double longSpan = Trivial::max(aMax, bMax) - Trivial::min(aMin, bMin);
	double sumSpan = aMax - aMin + bMax - bMin;

	return longSpan <= sumSpan;
}
