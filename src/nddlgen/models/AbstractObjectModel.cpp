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

#include <nddlgen/models/AbstractObjectModel.h>

nddlgen::models::AbstractObjectModel::AbstractObjectModel()
{

}

nddlgen::models::AbstractObjectModel::~AbstractObjectModel()
{

}

void nddlgen::models::AbstractObjectModel::initPredicates()
{
	// Dummy. Do nothing
}

void nddlgen::models::AbstractObjectModel::initSubObjects()
{
	// Dummy. Do nothing
}

void nddlgen::models::AbstractObjectModel::initActions()
{
	// Dummy. Do nothing
}

void nddlgen::models::AbstractObjectModel::generateForwardDeclaration(std::ofstream& ofStream)
{
	wrln(0, "class " + this->getClassName() + ";", 1);
}

void nddlgen::models::AbstractObjectModel::generateInstantiation(std::ofstream& ofStream)
{
	std::string className = this->getClassName();
	std::string instanceName = this->getName();

	std::string constructorParameters = "";

	if (this->hasSubObjects())
	{
		nddlgen::types::ObjectModelList subObjects = this->getSubObjects();

		foreach (nddlgen::models::AbstractObjectModelPtr subObject, subObjects)
		{
			std::string subObjectClassName = subObject->getClassName();
			std::string subObjectInstanceName = subObject->getName();

			subObject->generateInstantiation(ofStream);

			constructorParameters += subObjectInstanceName + ", ";
		}

		constructorParameters = constructorParameters.substr(0, constructorParameters.size() - 2);
	}

	wrln(0, className + " " + instanceName + " = new " + className + "(" + constructorParameters + ");", 1);
}

void nddlgen::models::AbstractObjectModel::generateModel(std::ofstream& ofStream)
{
	std::string extendsTimeline = "";

	// Timeline needs to be extended so that no actions are performed at once
	// and no predicates overlap
	if (this->hasPredicates())
	{
		extendsTimeline = " extends Timeline";
	}

	wrln(0, "class " + this->_className + extendsTimeline, 1);
	wrln(0, "{", 1);

	// Print predicates if present
	this->generateModelPredicates(ofStream);

	// Print sub objects as member if present
	this->generateModelSubObjects(ofStream);

	// Print constructor if sub objects are set
	this->generateModelConstructor(ofStream);

	wrln(0, "}", 2);
}

void nddlgen::models::AbstractObjectModel::generateModelPredicates(std::ofstream& ofStream)
{
	// Print predicates if present
	if (this->hasPredicates())
	{
		foreach (std::string predicate, this->_predicates)
		{
			wrln(1, "predicate " + predicate + " {}", 1);
		}

		if (this->hasSubObjects())
		{
			wrel(1);
		}
	}
}

void nddlgen::models::AbstractObjectModel::generateModelSubObjects(std::ofstream& ofStream)
{
	// Only print members if the model has any sub objects
	if (this->hasSubObjects())
	{
		// For each sub object, print member
		foreach (nddlgen::models::AbstractObjectModelPtr generatableModel, this->_subObjects)
		{
			std::string className = generatableModel->getClassName();
			std::string instanceName = generatableModel->getNamePref();

			wrln(1, className + " " + instanceName + ";", 1);
		}

		wrel(1);
	}
}

void nddlgen::models::AbstractObjectModel::generateModelConstructor(std::ofstream& ofStream)
{
	// Only print constructor if the model has any sub objects
	if (this->hasSubObjects())
	{
		// Print constructor
		std::string constructorHeader = this->getClassName() + "(";

		foreach (nddlgen::models::AbstractObjectModelPtr generatableModel, this->_subObjects)
		{
			std::string parameter = generatableModel->getClassName() + " " + generatableModel->getNamePrefSuff() + ", ";
			constructorHeader += parameter;
		}

		constructorHeader = constructorHeader.substr(0, constructorHeader.length() - 2);

		constructorHeader += ")";

		wrln(1, constructorHeader, 1);
		wrln(1, "{", 1);

		foreach (nddlgen::models::AbstractObjectModelPtr generatableModel, this->_subObjects)
		{
			std::string assignment = generatableModel->getNamePref() + " = " + generatableModel->getNamePrefSuff() + ";";

			wrln(2, assignment, 1);
		}

		wrln(1, "}", 1);
	}
}

void nddlgen::models::AbstractObjectModel::setName(std::string name)
{
	this->_name = name;
}

std::string nddlgen::models::AbstractObjectModel::getName()
{
	return this->_name;
}

std::string nddlgen::models::AbstractObjectModel::getNamePref()
{
	return "_" + this->getName();
}

std::string nddlgen::models::AbstractObjectModel::getNamePrefSuff()
{
	return this->getNamePref() + "_param";
}

std::string nddlgen::models::AbstractObjectModel::getAccessor()
{
	std::string accessor = this->getNamePref();

	if (this->hasSuperObject())
	{
		nddlgen::models::AbstractObjectModelPtr superObject = this->_superObject.lock();

		accessor = superObject->getAccessor() + "." + accessor;
	}

	return accessor;
}

void nddlgen::models::AbstractObjectModel::setClassName(std::string className)
{
	this->_className = className;
}

std::string nddlgen::models::AbstractObjectModel::getClassName()
{
	return this->_className;
}

void nddlgen::models::AbstractObjectModel::addBlockingObject(nddlgen::models::AbstractObjectModelPtr blockingObject)
{
	this->_blockingObjects.push_back(blockingObject);
}

bool nddlgen::models::AbstractObjectModel::hasBlockingObjects()
{
	return (this->_blockingObjects.size() != 0);
}

void nddlgen::models::AbstractObjectModel::addPredicate(std::string predicate)
{
	this->_predicates.push_back(predicate);
}

bool nddlgen::models::AbstractObjectModel::hasPredicates()
{
	return (this->_predicates.size() != 0);
}

void nddlgen::models::AbstractObjectModel::setInitialPredicate(std::string initialPredicate)
{
	this->_initialPredicate = initialPredicate;
}

std::string nddlgen::models::AbstractObjectModel::getInitialPredicate()
{
	return this->_initialPredicate;
}

nddlgen::models::InitialStateFactModelPtr nddlgen::models::AbstractObjectModel::getInitialState()
{
	if (this->_initialPredicate == "")
	{
		// TODO: throw proper exception
		throw "No initial predicate was set for " + this->_name;
	}

	nddlgen::models::InitialStateFactModelPtr fact(new nddlgen::models::InitialStateFactModel());

	fact->setFactName(this->getName() + "_" + this->getInitialPredicate());
	fact->setObjectName(this->getName());
	fact->setPredicate(this->getInitialPredicate());

	return fact;
}

void nddlgen::models::AbstractObjectModel::addAction(nddlgen::models::ActionModelPtr action)
{
	this->_actions.push_back(action);
}

bool nddlgen::models::AbstractObjectModel::hasActions()
{
	return (this->_actions.size() != 0);
}

nddlgen::types::ActionList nddlgen::models::AbstractObjectModel::getActions()
{
	return this->_actions;
}

nddlgen::math::CuboidPtr nddlgen::models::AbstractObjectModel::getObjectBoundingBox()
{
	return this->_objectBoundingBox;
}

void nddlgen::models::AbstractObjectModel::setObjectBoundingBox(nddlgen::math::CuboidPtr objectBoundingBox)
{
	this->_objectBoundingBox = objectBoundingBox;
}

bool nddlgen::models::AbstractObjectModel::hasObjectBoundingBox()
{
	return (bool) this->_objectBoundingBox;
}

nddlgen::math::CuboidPtr nddlgen::models::AbstractObjectModel::getAccessibilityBoundingBox()
{
	return this->_accessibilityBoundingBox;
}

void nddlgen::models::AbstractObjectModel::setAccessibilityBoundingBox(nddlgen::math::CuboidPtr accessibilityBoundingBox)
{
	this->_accessibilityBoundingBox = accessibilityBoundingBox;
}

bool nddlgen::models::AbstractObjectModel::hasAccessibilityBoundingBox()
{
	return (bool) this->_accessibilityBoundingBox;
}

bool nddlgen::models::AbstractObjectModel::hasSubObjects()
{
	return (this->_subObjects.size() != 0);
}

void nddlgen::models::AbstractObjectModel::addSubObject(nddlgen::models::AbstractObjectModelPtr subObject)
{
	subObject->setSuperObject(this->shared_from_this());
	this->_subObjects.push_back(subObject);
}

nddlgen::types::ObjectModelList nddlgen::models::AbstractObjectModel::getSubObjects()
{
	return this->_subObjects;
}

nddlgen::models::AbstractObjectModelPtr nddlgen::models::AbstractObjectModel::getSubObjectByName(
		std::string name,
		bool findInTree)
{
	nddlgen::models::AbstractObjectModelPtr output(0);

	foreach (nddlgen::models::AbstractObjectModelPtr generatableModel, this->_subObjects)
	{
		if (generatableModel->getName() == name)
		{
			output = generatableModel;
		}

		if (!output && findInTree)
		{
			output = generatableModel->getSubObjectByName(name, findInTree);
		}

		if (output)
		{
			return output;
		}
	}

	return output;
}

void nddlgen::models::AbstractObjectModel::setInstanceNameFor(int index, std::string instanceName)
{
	this->_subObjects.at(index)->setName(instanceName);
}

bool nddlgen::models::AbstractObjectModel::hasSuperObject()
{
	nddlgen::models::AbstractObjectModelPtr superObject = this->_superObject.lock();
	return (bool) superObject;
}

void nddlgen::models::AbstractObjectModel::setSuperObject(nddlgen::models::AbstractObjectModelPtr superObject)
{
	this->_superObject = superObject;
}
