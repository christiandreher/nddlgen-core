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

#include <nddlgen/utilities/ModelAction.h>

nddlgen::utilities::ModelAction::ModelAction()
{

}

nddlgen::utilities::ModelAction::~ModelAction()
{

}

void nddlgen::utilities::ModelAction::setName(std::string name)
{
	this->_name = name;
}

void nddlgen::utilities::ModelAction::setDuration(std::string duration)
{
	this->_duration = duration;
}

void nddlgen::utilities::ModelAction::setMetByCondition(std::string modelName, std::string predicate)
{
	this->_metByCondition = modelName + "." + predicate;
}

void nddlgen::utilities::ModelAction::setContainedByCondition(std::string modelName, std::string predicate)
{
	this->_containedByCondition = modelName + "." + predicate;
}

void nddlgen::utilities::ModelAction::setMeetsEffect(std::string modelName, std::string predicate)
{
	this->_meetsEffect = modelName + "." + predicate;
}

std::string nddlgen::utilities::ModelAction::getName()
{
	return this->_name;
}

std::string nddlgen::utilities::ModelAction::getDuration()
{
	return this->_duration;
}

std::string nddlgen::utilities::ModelAction::getMetByCondition(std::string workspaceNamePref)
{
	return "met_by(condition object." + workspaceNamePref + "." + this->_metByCondition + ");";
}

std::string nddlgen::utilities::ModelAction::getContainedByCondition(std::string workspaceNamePref)
{
	return "contained_by(condition object." + workspaceNamePref + "." + this->_containedByCondition + ");";
}

std::string nddlgen::utilities::ModelAction::getMeetsEffect(std::string workspaceNamePref)
{
	return "meets(effect object." + workspaceNamePref + "." + this->_meetsEffect + ");";
}

std::string nddlgen::utilities::ModelAction::getActionDefinition()
{
	return "action " + this->getName() + " { duration=" + this->getDuration() + "; }";
}

std::list<std::string> nddlgen::utilities::ModelAction::getActionSteps(std::string workspaceNamePref)
{
	std::list<std::string> actionSteps;

	if (this->_metByCondition != "")
	{
		actionSteps.push_back(this->getMetByCondition(workspaceNamePref));
	}

	if (this->_containedByCondition != "")
	{
		actionSteps.push_back(this->getContainedByCondition(workspaceNamePref));
	}

	if (this->_meetsEffect != "")
	{
		actionSteps.push_back(this->getMeetsEffect(workspaceNamePref));
	}

	return actionSteps;
}
