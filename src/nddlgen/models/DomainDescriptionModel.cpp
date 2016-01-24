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

void nddlgen::models::DomainDescriptionModel::initSubObjects()
{
	// Map containing all sub object classes and an incrementing index to keep
	// track of numbers to avoid instances with the same name
	std::map<std::string, int> indices;

	this->initSubObjects(this->_arm, indices);
}

void nddlgen::models::DomainDescriptionModel::initPredicates()
{
	this->initPredicates(this->_arm);
}

void nddlgen::models::DomainDescriptionModel::detectBlockingObjects()
{
	// Get all models on workspace
	nddlgen::types::NddlGeneratableList models = this->getArm()->getWorkspace()->getModels();

	// Use this...
	foreach (nddlgen::models::NddlGeneratablePtr model1, models)
	{
		// ...and this foreach loop to form all permutations (naive, may be improved)
		foreach (nddlgen::models::NddlGeneratablePtr model2, models)
		{
			// Only run collision detection if model1 and model2 are not the same object
			if (model1 != model2)
			{
				// Accessibility bounding box of model1 and object bounding box of model2 need to be set
				if (model1->hasAccessibilityBoundingBox() && model2->hasObjectBoundingBox())
				{
					// Run collision detection and save result
					bool doBoundingBoxesIntersect = nddlgen::controllers::CollisionDetectionController::doesIntersect(
							model1->getAccessibilityBoundingBox(),
							model2->getObjectBoundingBox()
					);

					// If the bounding boxes intersect, instruct model1 that it is blocked by model2
					if (doBoundingBoxesIntersect)
					{
						model1->addBlockingObject(model2);
					}
				}
			}
		}
	}
}

void nddlgen::models::DomainDescriptionModel::initActions()
{
	this->initActions(this->_arm);
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

void nddlgen::models::DomainDescriptionModel::gatherActions()
{
	std::list<nddlgen::models::NddlGeneratablePtr> allObjects = this->gatherUsedObjects(this->_arm);

	foreach (nddlgen::models::NddlGeneratablePtr object, allObjects)
	{
		nddlgen::types::ActionList actions = object->getActions();
		this->_actions.insert(this->_actions.end(), actions.begin(), actions.end());
	}
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

		foreach (std::string actionStep, actionSteps)
		{
			wrln(1, actionStep, 1);
		}

		wrln(0, "}", 2);
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

void nddlgen::models::DomainDescriptionModel::initSubObjects(nddlgen::models::NddlGeneratablePtr model,
		std::map<std::string, int> indices)
{
	// In any case, call function of model
	model->initSubObjects();

	// If model has sub objects, initialize recursive call
	if (model->hasSubObjects())
	{
		// Index to be able to address sub objects
		int index = 0;

		// Get sub objects
		std::vector<nddlgen::models::NddlGeneratablePtr> subObjects = model->getSubObjects();

		// Loop through sub objects and use it as parameter for the recursive call
		foreach (nddlgen::models::NddlGeneratablePtr subObject, subObjects)
		{
			this->initSubObjects(subObject, indices);

			std::string subObjectClass = subObject->getClassName();
			std::string instanceName = subObject->getName();
			std::map<std::string, int>::iterator it = indices.find(subObjectClass);

			if (instanceName == "")
			{
				instanceName = boost::to_lower_copy(subObject->getClassName())  + "_";

				// Check if subObjectClass exists in indices
				if (it != indices.end())
				{
					instanceName = instanceName + boost::lexical_cast<std::string>(it->second);
					model->setInstanceNameFor(index, instanceName);

					it->second++;
				}
				else
				{
					instanceName = instanceName + boost::lexical_cast<std::string>(1);
					model->setInstanceNameFor(index, instanceName);

					indices.insert(std::pair<std::string, int>(subObjectClass, 2));
				}
			}

			index++;
		}
	}
}

void nddlgen::models::DomainDescriptionModel::initPredicates(nddlgen::models::NddlGeneratablePtr model)
{
	// If model has sub objects, initialize recursive call
	if (model->hasSubObjects())
	{
		// Get sub objects
		std::vector<nddlgen::models::NddlGeneratablePtr> subObjects = model->getSubObjects();

		// Loop through sub objects and use it as parameter for the recursive call
		foreach (nddlgen::models::NddlGeneratablePtr subObject, subObjects)
		{
			this->initPredicates(subObject);
		}
	}

	// In any case, call function of model
	model->initPredicates();
}

void nddlgen::models::DomainDescriptionModel::initActions(nddlgen::models::NddlGeneratablePtr model)
{
	// If model has sub objects, initialize recursive call
	if (model->hasSubObjects())
	{
		// Get sub objects
		std::vector<nddlgen::models::NddlGeneratablePtr> subObjects = model->getSubObjects();

		// Loop through sub objects and use it as parameter for the recursive call
		foreach (nddlgen::models::NddlGeneratablePtr subObject, subObjects)
		{
			this->initActions(subObject);
		}
	}

	// In any case, call function of model
	model->initActions();
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
