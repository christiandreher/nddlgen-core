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

#include <nddlgen/models/InitialStateModel.h>

nddlgen::models::InitialStateModel::InitialStateModel()
{

}

nddlgen::models::InitialStateModel::~InitialStateModel()
{

}

void nddlgen::models::InitialStateModel::addFact(nddlgen::utilities::InitialStateFact* fact)
{
	int index = this->_facts.size() + 1;
	fact->setIndex(index);

	this->_facts.push_back(fact);
}

boost::ptr_list<nddlgen::utilities::InitialStateFact> nddlgen::models::InitialStateModel::getFacts()
{
	return this->_facts;
}

void nddlgen::models::InitialStateModel::addGoal(nddlgen::utilities::InitialStateGoal* goal)
{
	int index = this->_goals.size() + 1;
	goal->setIndex(index);

	this->_goals.push_back(goal);
}

boost::ptr_list<nddlgen::utilities::InitialStateGoal> nddlgen::models::InitialStateModel::getGoals()
{
	return this->_goals;
}
