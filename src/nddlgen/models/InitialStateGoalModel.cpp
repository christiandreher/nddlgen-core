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

#include <nddlgen/utilities/InitialStateGoal.h>

nddlgen::utilities::InitialStateGoal::InitialStateGoal()
{
	this->_goalName = "";
	this->_modelName = "";
	this->_predicate = "";
	this->_startsAfter = "";
	this->_endsBefore = "";
	this->_index = "";
}

nddlgen::utilities::InitialStateGoal::~InitialStateGoal()
{

}

void nddlgen::utilities::InitialStateGoal::setGoalName(std::string goalName)
{
	this->_goalName = goalName;
}

void nddlgen::utilities::InitialStateGoal::setModelName(std::string modelName)
{
	this->_modelName = modelName;
}

void nddlgen::utilities::InitialStateGoal::setPredicate(std::string predicate)
{
	this->_predicate = predicate;
}

void nddlgen::utilities::InitialStateGoal::setStartsAfter(std::string startsAfter)
{
	this->_startsAfter = startsAfter;
}

void nddlgen::utilities::InitialStateGoal::setEndsBefore(std::string endsBefore)
{
	this->_endsBefore = endsBefore;
}

void nddlgen::utilities::InitialStateGoal::setIndex(int index)
{
	this->_index = boost::lexical_cast<std::string>(index);
}

std::list<std::string> nddlgen::utilities::InitialStateGoal::getGoal()
{
	if (this->_index == "")
	{
		throw nddlgen::exceptions::NoIndexSetException();
	}

	std::list<std::string> goal;
	std::string goalName;

	if (this->_goalName != "")
	{
		goalName = this->_goalName;
	}
	else
	{
		goalName = "goal" + this->_index;
	}

	goal.push_back("goal(" + this->_modelName + "." + this->_predicate + " " + goalName + ");");

	if (this->_startsAfter != "")
	{
		goal.push_back(this->_startsAfter + " <= " + goalName + ".start" + ";");
	}

	if (this->_endsBefore != "")
	{
		goal.push_back(goalName + ".end" + " <= " + this->_endsBefore + ";");
	}

	return goal;
}
