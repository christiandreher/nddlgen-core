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

#include <nddlgen/models/NddlGeneratable.h>

namespace nddlgen { namespace models
{

	NddlGeneratable::NddlGeneratable()
	{

	}

	NddlGeneratable::~NddlGeneratable()
	{

	}


	void NddlGeneratable::postInitProcessing()
	{

	}


	void NddlGeneratable::generateModel(std::ofstream& ofStream)
	{
		wrln(0, "class " + this->_className,	1);
		wrln(0, "{",							1);

		if (this->hasPredicates())
		{
			foreach (std::string predicate, this->_predicates)
			{
				wrln(1, "predicate " + predicate + " {}", 1);
			}
		}

		wrln(0, "}",							2);
	}

	void NddlGeneratable::setName(std::string name)
	{
		this->_name = name;
	}

	std::string NddlGeneratable::getName()
	{
		return this->_name;
	}

	std::string NddlGeneratable::getNamePref()
	{
		return "_" + this->getName();
	}

	std::string NddlGeneratable::getNamePrefSuff()
	{
		return this->getNamePref() + "_param";
	}


	void NddlGeneratable::setClassName(std::string className)
	{
		this->_className = className;
	}

	std::string NddlGeneratable::getClassName()
	{
		return this->_className;
	}


	void NddlGeneratable::addBlockingObject(nddlgen::models::NddlGeneratable* blockingObject)
	{
		this->_blockedBy.push_back(blockingObject);
	}

	bool NddlGeneratable::isBlocked()
	{
		return (this->_blockedBy.size() != 0);
	}


	void NddlGeneratable::addPredicate(std::string predicate)
	{
		this->_predicates.push_back(predicate);
	}

	bool NddlGeneratable::hasPredicates()
	{
		return (this->_predicates.size() != 0);
	}


	void NddlGeneratable::addAction(nddlgen::utilities::ModelAction* action)
	{
		this->_actions.push_back(action);
	}

	bool NddlGeneratable::hasActions()
	{
		return (this->_actions.size() != 0);
	}

	nddlgen::types::ActionList NddlGeneratable::getActions()
	{
		return this->_actions;
	}

}}
