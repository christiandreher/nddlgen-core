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

#include <nddlgen/utilities/InitialStateFact.h>

nddlgen::utilities::InitialStateFact::InitialStateFact()
{
	this->_modelName = "";
	this->_predicate = "";
	this->_index = "";
}

nddlgen::utilities::InitialStateFact::~InitialStateFact()
{

}

void nddlgen::utilities::InitialStateFact::setModelName(std::string modelName)
{
	this->_modelName = modelName;
}

void nddlgen::utilities::InitialStateFact::setPredicate(std::string predicate)
{
	this->_predicate = predicate;
}

void nddlgen::utilities::InitialStateFact::setIndex(int index)
{
	this->_index = boost::lexical_cast<std::string>(index);
}

std::list<std::string> nddlgen::utilities::InitialStateFact::getFact()
{
	if (this->_index == "")
	{
		throw nddlgen::exceptions::NoIndexSetException();
	}

	std::list<std::string> fact;

	std::string conditionName = "initialCondition" + this->_index;

	fact.push_back("fact(" + this->_modelName + "." + this->_predicate + " " + conditionName + ");");
	fact.push_back("eq(" + conditionName + ".start, 0);");

	return fact;
}
