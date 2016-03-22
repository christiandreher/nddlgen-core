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

#include <nddlgen/models/DomainDescriptionModel.h>

nddlgen::models::DomainDescriptionModel::DomainDescriptionModel()
{

}

nddlgen::models::DomainDescriptionModel::~DomainDescriptionModel()
{

}

void nddlgen::models::DomainDescriptionModel::setArm(nddlgen::models::DefaultArmModelPtr arm)
{
	this->_arm = arm;
}

nddlgen::models::DefaultArmModelPtr nddlgen::models::DomainDescriptionModel::getArm()
{
	return this->_arm;
}

void nddlgen::models::DomainDescriptionModel::setInitialState(nddlgen::models::InitialStateModelPtr initialState)
{
	this->_initialState = initialState;
}

nddlgen::models::InitialStateModelPtr nddlgen::models::DomainDescriptionModel::getInitialState()
{
	return this->_initialState;
}

void nddlgen::models::DomainDescriptionModel::addActions(nddlgen::types::ActionList actions)
{
	this->_actions.insert(this->_actions.end(), actions.begin(), actions.end());
}

nddlgen::types::ActionList nddlgen::models::DomainDescriptionModel::getActions()
{
	return this->_actions;
}

void nddlgen::models::DomainDescriptionModel::addUsedNddlClass(nddlgen::models::AbstractObjectModelPtr object)
{
	this->_usedNddlClasses.insert(std::pair<std::string, nddlgen::models::AbstractObjectModelPtr>(object->getClassName(),
			object));
}

void nddlgen::models::DomainDescriptionModel::generateForwardDeclarations(std::ofstream& ofStream)
{
	for (std::map<std::string, nddlgen::models::AbstractObjectModelPtr>::iterator it = this->_usedNddlClasses.begin();
			it != this->_usedNddlClasses.end(); it++)
	{
		it->second->generateForwardDeclaration(ofStream);
	}

	wrel(1);
}

void nddlgen::models::DomainDescriptionModel::generateInstantiations(std::ofstream& ofStream)
{
	this->_arm->generateInstantiation(ofStream);

	wrel(1);
}

void nddlgen::models::DomainDescriptionModel::generateNddlClasses(std::ofstream& ofStream)
{
	for (std::map<std::string, nddlgen::models::AbstractObjectModelPtr>::iterator it = this->_usedNddlClasses.begin();
			it != this->_usedNddlClasses.end(); it++)
	{
		it->second->generateNddlClass(ofStream);
	}
}

void nddlgen::models::DomainDescriptionModel::generateActions(std::ofstream& ofStream)
{
	std::string armClass = this->getArm()->getClassName();

	// Iterate through all actions and print it
	foreach (nddlgen::models::ActionModelPtr action, this->_actions)
	{
		std::string actionName = action->getName();
		std::list<std::string> actionSteps = action->getActionSteps();

		// Arm member function
		wrln(0, armClass + "::" + actionName, 1);
		wrln(0, "{", 1);

		// Print each line
		foreach (std::string actionStep, actionSteps)
		{
			wrln(1, actionStep, 1);
		}

		wrln(0, "}", 2);
	}
}

void nddlgen::models::DomainDescriptionModel::generateFacts(std::ofstream& ofStream)
{
	// Get facts
	nddlgen::types::FactList facts = this->getInitialState()->getFacts();

	// Iterate through facts
	foreach (nddlgen::models::InitialStateFactModelPtr fact, facts)
	{
		// Get fact
		std::list<std::string> factLines = fact->getFact();

		// Print each line
		foreach (std::string factLine, factLines)
		{
			wrln(0, factLine, 1);
		}

		wrel(1);
	}
}

void nddlgen::models::DomainDescriptionModel::generateGoals(std::ofstream& ofStream)
{
	// Get goals
	nddlgen::types::GoalList goals = this->getInitialState()->getGoals();

	// Iterate through goals
	foreach (nddlgen::models::InitialStateGoalModelPtr goal, goals)
	{
		// Get goal
		std::list<std::string> goalLines = goal->getGoal();

		// Print each line
		foreach (std::string goalLine, goalLines)
		{
			wrln(0, goalLine, 1);
		}

		wrel(1);
	}
}
