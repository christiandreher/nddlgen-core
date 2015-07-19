/**
 * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)
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

#include <nddlgen/models/ObjectSlideContainer.h>

namespace nddlgen { namespace models
{

	ObjectSlideContainer::ObjectSlideContainer()
	{
		this->setClassName("ObjectSlideContainer");

		this->_capacity = 36;
	}

	ObjectSlideContainer::ObjectSlideContainer(int capacity)
	{
		this->setClassName("ObjectSlideContainer");

		this->_capacity = capacity;
	}

	ObjectSlideContainer::~ObjectSlideContainer()
	{
		// TODO Auto-generated destructor stub
	}


	void ObjectSlideContainer::generateModelAsString(std::ofstream& ofStream)
	{
		wrln(0, "class ObjectSlideContainer", 	1);
		wrln(0, "{",							1);
		wrln(0, "}",							2);
	}

	void ObjectSlideContainer::generateInitialStateAsString(std::ofstream& ofStream)
	{

	}

}}
