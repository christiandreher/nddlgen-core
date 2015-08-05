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

	}


	void LidBox::postInitProcessing()
	{
		std::string openedPredicate = "opened";
		std::string closedPredicate = "closed";

		nddlgen::utilities::ModelAction* openAction = new nddlgen::utilities::ModelAction();
		nddlgen::utilities::ModelAction* closeAction = new nddlgen::utilities::ModelAction();

		this->setClassName("LidBox");

		openAction->setName("open" + this->getNamePref());
		openAction->setDuration("1");
		openAction->setMetByCondition(this->getNamePref(), closedPredicate);

		if (this->isBlocked())
		{
			foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_blockedBy)
			{
				nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;

				openAction->setContainedByCondition(generatableModel->getNamePref(), closedPredicate);
			}
		}

		openAction->setMeetsEffect(this->getNamePref(), openedPredicate);

		closeAction->setName("close" + this->getNamePref());
		closeAction->setDuration("1");
		closeAction->setMetByCondition(this->getNamePref(), openedPredicate);
		closeAction->setMeetsEffect(this->getNamePref(), closedPredicate);

		this->addPredicate(openedPredicate);
		this->addPredicate(closedPredicate);

		this->addAction(openAction);
		this->addAction(closeAction);
	}


	void LidBox::generateInitialState(std::ofstream& ofStream)
	{

	}


	bool LidBox::isOpened()
	{
		return this->_isOpened;
	}

}}
