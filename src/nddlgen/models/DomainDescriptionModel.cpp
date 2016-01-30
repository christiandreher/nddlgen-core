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

void nddlgen::models::DomainDescriptionModel::registerActions(nddlgen::types::ActionList actions)
{
	this->_actions.insert(this->_actions.end(), actions.begin(), actions.end());
}

nddlgen::types::ActionList nddlgen::models::DomainDescriptionModel::getActions()
{
	return this->_actions;
}

void nddlgen::models::DomainDescriptionModel::registerUsedClass(nddlgen::models::NddlGeneratablePtr object)
{
	this->_usedClasses.insert(std::pair<std::string, nddlgen::models::NddlGeneratablePtr>(object->getClassName(),
			object));
}

void nddlgen::models::DomainDescriptionModel::generateForwardDeclarations(std::ofstream& ofStream)
{
	for (std::map<std::string, nddlgen::models::NddlGeneratablePtr>::iterator it = this->_usedClasses.begin();
			it != this->_usedClasses.end(); it++)
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

void nddlgen::models::DomainDescriptionModel::generateModels(std::ofstream& ofStream)
{
	for (std::map<std::string, nddlgen::models::NddlGeneratablePtr>::iterator it = this->_usedClasses.begin();
			it != this->_usedClasses.end(); it++)
	{
		it->second->generateModel(ofStream);
	}
}

void nddlgen::models::DomainDescriptionModel::generateActions(std::ofstream& ofStream)
{
	std::string armClass = this->getArm()->getClassName();

	// Iterate through all actions and print it
	foreach (nddlgen::utilities::ModelActionPtr action, this->_actions)
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
	foreach (nddlgen::utilities::InitialStateFactPtr fact, facts)
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
	foreach (nddlgen::utilities::InitialStateGoalPtr goal, goals)
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
