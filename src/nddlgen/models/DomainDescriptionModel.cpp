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

void nddlgen::models::DomainDescriptionModel::setArm(nddlgen::models::ArmModelPtr arm)
{
	this->_arm = arm;
}

nddlgen::models::ArmModelPtr nddlgen::models::DomainDescriptionModel::getArm()
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

void nddlgen::models::DomainDescriptionModel::postInitProcessing()
{
	// Calculate dependencies between models. Runs collision detection
	this->calculateDependencies();

	// Run post-init processing for each sub object
	this->recursivePostInitProcessing(this->_arm);

	// Gather used classes to be able to perform class-based generation processes
	this->gatherUsedClasses();

	// Gather actions to be able to print them
	this->gatherActions();
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

void nddlgen::models::DomainDescriptionModel::generateFacts(std::ofstream& ofStream)
{
	nddlgen::types::FactList facts = this->getInitialState()->getFacts();

	foreach (nddlgen::utilities::InitialStateFactPtr fact, facts)
	{
		std::list<std::string> factLines = fact->getFact();

		foreach (std::string factLine, factLines)
		{
			wrln(0, factLine, 1);
		}

		wrel(1);
	}
}

void nddlgen::models::DomainDescriptionModel::generateGoals(std::ofstream& ofStream)
{
	nddlgen::types::GoalList goals = this->getInitialState()->getGoals();

	foreach (nddlgen::utilities::InitialStateGoalPtr goal, goals)
	{
		std::list<std::string> goalLines = goal->getGoal();

		foreach (std::string goalLine, goalLines)
		{
			wrln(0, goalLine, 1);
		}

		wrel(1);
	}
}

void nddlgen::models::DomainDescriptionModel::calculateDependencies()
{
	nddlgen::types::NddlGeneratableList models = this->getArm()->getWorkspace()->getModels();

	// Detect all blocking objects and populate models accordingly
	foreach (nddlgen::models::NddlGeneratablePtr model1, models)
	{
		foreach (nddlgen::models::NddlGeneratablePtr model2, models)
		{
			if (model1 != model2)
			{
				if (model1->hasAccessibilityBoundingBox() && model2->hasObjectBoundingBox())
				{
					bool doBoundingBoxesIntersect = nddlgen::controllers::CollisionDetectionController::doesIntersect(
							model1->getAccessibilityBoundingBox(),
							model2->getObjectBoundingBox()
					);

					if (doBoundingBoxesIntersect)
					{
						model1->addBlockingObject(model2);
					}
				}
			}
		}
	}
}

void nddlgen::models::DomainDescriptionModel::recursivePostInitProcessing(nddlgen::models::NddlGeneratablePtr model)
{
	if (model->hasSubObjects())
	{
		std::vector<nddlgen::models::NddlGeneratablePtr> subObjects = model->getSubObjects();

		foreach (nddlgen::models::NddlGeneratablePtr subObject, subObjects)
		{
			this->recursivePostInitProcessing(subObject);
		}
	}

	model->postInitProcessing();
}

void nddlgen::models::DomainDescriptionModel::gatherUsedClasses()
{
	std::list<nddlgen::models::NddlGeneratablePtr> allObjects = this->gatherUsedObjects(this->_arm);

	foreach (nddlgen::models::NddlGeneratablePtr object, allObjects)
	{
		this->_usedClasses.insert(std::pair<std::string, nddlgen::models::NddlGeneratablePtr>(object->getClassName(),
				object));
	}
}

std::list<nddlgen::models::NddlGeneratablePtr> nddlgen::models::DomainDescriptionModel::gatherUsedObjects(
		nddlgen::models::NddlGeneratablePtr model)
{
	std::list<nddlgen::models::NddlGeneratablePtr> output;

	if (model->hasSubObjects())
	{
		std::vector<nddlgen::models::NddlGeneratablePtr> subObjects = model->getSubObjects();

		foreach (nddlgen::models::NddlGeneratablePtr subObject, subObjects)
		{
			std::list<nddlgen::models::NddlGeneratablePtr> recursiveOutput = this->gatherUsedObjects(subObject);
			output.insert(output.end(), recursiveOutput.begin(), recursiveOutput.end());
		}
	}

	output.push_back(model);

	return output;
}

void nddlgen::models::DomainDescriptionModel::gatherActions()
{
	// TODO: implement
}
