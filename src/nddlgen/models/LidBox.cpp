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

#include <nddlgen/models/LidBox.h>

namespace nddlgen { namespace models
{

	LidBox::LidBox()
	{
		this->setClassName("LidBox");

		this->_isOpened = false;
	}

	LidBox::LidBox(bool isOpened)
	{
		this->setClassName("LidBox");

		this->_isOpened = isOpened;
	}

	LidBox::~LidBox()
	{
		// TODO Auto-generated destructor stub
	}


	void LidBox::generateInitialState(std::ofstream& ofStream)
	{

	}


	bool LidBox::isOpened()
	{
		return this->_isOpened;
	}

	void LidBox::init()
	{
		std::string openedPredicate = "opened";
		std::string closedPredicate = "closed";

		nddlgen::utilities::ModelAction* openAction = new nddlgen::utilities::ModelAction();
		nddlgen::utilities::ModelAction* closeAction = new nddlgen::utilities::ModelAction();

		this->setClassName("LidBox");

		this->addPredicate(openedPredicate);
		this->addPredicate(closedPredicate);

		openAction->setName("open" + this->getNamePref());
		openAction->setDuration("1");
	}
}}
