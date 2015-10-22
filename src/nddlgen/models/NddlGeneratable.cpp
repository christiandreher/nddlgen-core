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

nddlgen::models::NddlGeneratable::NddlGeneratable()
{

}

nddlgen::models::NddlGeneratable::~NddlGeneratable()
{

}


void nddlgen::models::NddlGeneratable::postInitProcessing()
{

}


void nddlgen::models::NddlGeneratable::generateModel(std::ofstream& ofStream)
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

void nddlgen::models::NddlGeneratable::setName(std::string name)
{
	this->_name = name;
}

std::string nddlgen::models::NddlGeneratable::getName()
{
	return this->_name;
}

std::string nddlgen::models::NddlGeneratable::getNamePref()
{
	return "_" + this->getName();
}

std::string nddlgen::models::NddlGeneratable::getNamePrefSuff()
{
	return this->getNamePref() + "_param";
}


void nddlgen::models::NddlGeneratable::setClassName(std::string className)
{
	this->_className = className;
}

std::string nddlgen::models::NddlGeneratable::getClassName()
{
	return this->_className;
}


void nddlgen::models::NddlGeneratable::addBlockingObject(nddlgen::models::NddlGeneratablePtr blockingObject)
{
	this->_blockedBy.push_back(blockingObject);
}

bool nddlgen::models::NddlGeneratable::isBlocked()
{
	return (this->_blockedBy.size() != 0);
}


void nddlgen::models::NddlGeneratable::addPredicate(std::string predicate)
{
	this->_predicates.push_back(predicate);
}

bool nddlgen::models::NddlGeneratable::hasPredicates()
{
	return (this->_predicates.size() != 0);
}


void nddlgen::models::NddlGeneratable::addAction(nddlgen::utilities::ModelActionPtr action)
{
	this->_actions.push_back(action);
}

bool nddlgen::models::NddlGeneratable::hasActions()
{
	return (this->_actions.size() != 0);
}

nddlgen::types::ActionList nddlgen::models::NddlGeneratable::getActions()
{
	return this->_actions;
}
