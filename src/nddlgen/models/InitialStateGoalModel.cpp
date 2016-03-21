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

#include <nddlgen/models/InitialStateGoalModel.h>

nddlgen::models::InitialStateGoalModel::InitialStateGoalModel()
{
	this->_goalName = "";
	this->_objectName = "";
	this->_predicate = "";
	this->_startsAfter = "";
	this->_endsBefore = "";
	this->_index = "";
}

nddlgen::models::InitialStateGoalModel::~InitialStateGoalModel()
{

}

void nddlgen::models::InitialStateGoalModel::setGoalName(std::string goalName)
{
	this->_goalName = goalName;
}

void nddlgen::models::InitialStateGoalModel::setObjectName(std::string objectName)
{
	this->_objectName = objectName;
}

void nddlgen::models::InitialStateGoalModel::setPredicate(std::string predicate)
{
	this->_predicate = predicate;
}

void nddlgen::models::InitialStateGoalModel::setStartsAfter(std::string startsAfter)
{
	this->_startsAfter = startsAfter;
}

void nddlgen::models::InitialStateGoalModel::setEndsBefore(std::string endsBefore)
{
	this->_endsBefore = endsBefore;
}

void nddlgen::models::InitialStateGoalModel::setIndex(int index)
{
	this->_index = boost::lexical_cast<std::string>(index);
}

std::list<std::string> nddlgen::models::InitialStateGoalModel::getGoal()
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

	goal.push_back("goal(" + this->_objectName + "." + this->_predicate + " " + goalName + ");");

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
