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

#include <nddlgen/models/InitialStateFactModel.h>

nddlgen::models::InitialStateFactModel::InitialStateFactModel()
{
	this->_factName = "";
	this->_objectName = "";
	this->_predicate = "";
	this->_index = "";
}

nddlgen::models::InitialStateFactModel::~InitialStateFactModel()
{

}

void nddlgen::models::InitialStateFactModel::setFactName(std::string factName)
{
	this->_factName = factName;
}

void nddlgen::models::InitialStateFactModel::setObjectName(std::string objectName)
{
	this->_objectName = objectName;
}

void nddlgen::models::InitialStateFactModel::setPredicate(std::string predicate)
{
	this->_predicate = predicate;
}

void nddlgen::models::InitialStateFactModel::setIndex(int index)
{
	this->_index = boost::lexical_cast<std::string>(index);
}

std::list<std::string> nddlgen::models::InitialStateFactModel::getFact()
{
	if (this->_index == "")
	{
		throw nddlgen::exceptions::NoIndexSetException();
	}

	std::list<std::string> fact;
	std::string factName;

	if (this->_factName != "")
	{
		factName = this->_factName;
	}
	else
	{
		factName = "initialCondition" + this->_index;
	}

	fact.push_back("fact(" + this->_objectName + "." + this->_predicate + " " + factName + ");");
	fact.push_back("eq(" + factName + ".start, 0);");

	return fact;
}
