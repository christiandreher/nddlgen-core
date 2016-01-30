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

#include <nddlgen/models/NddlGeneratable.h>

nddlgen::models::NddlGeneratable::NddlGeneratable()
{

}

nddlgen::models::NddlGeneratable::~NddlGeneratable()
{

}

void nddlgen::models::NddlGeneratable::initPredicates()
{
	// Dummy. Do nothing
}

void nddlgen::models::NddlGeneratable::initSubObjects()
{
	// Dummy. Do nothing
}

void nddlgen::models::NddlGeneratable::initActions()
{
	// Dummy. Do nothing
}

void nddlgen::models::NddlGeneratable::generateForwardDeclaration(std::ofstream& ofStream)
{
	wrln(0, "class " + this->getClassName() + ";", 1);
}

void nddlgen::models::NddlGeneratable::generateInstantiation(std::ofstream& ofStream)
{
	std::string className = this->getClassName();
	std::string instanceName = this->getName();

	std::string constructorParameters = "";

	if (this->hasSubObjects())
	{
		std::vector<nddlgen::models::NddlGeneratablePtr> subObjects = this->getSubObjects();

		foreach (nddlgen::models::NddlGeneratablePtr subObject, subObjects)
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

void nddlgen::models::NddlGeneratable::generateModel(std::ofstream& ofStream)
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

void nddlgen::models::NddlGeneratable::generateModelPredicates(std::ofstream& ofStream)
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

void nddlgen::models::NddlGeneratable::generateModelSubObjects(std::ofstream& ofStream)
{
	// Only print members if the model has any sub objects
	if (this->hasSubObjects())
	{
		// For each sub object, print member
		foreach (nddlgen::models::NddlGeneratablePtr generatableModel, this->_subObjects)
		{
			std::string className = generatableModel->getClassName();
			std::string instanceName = generatableModel->getNamePref();

			wrln(1, className + " " + instanceName + ";", 1);
		}

		wrel(1);
	}
}

void nddlgen::models::NddlGeneratable::generateModelConstructor(std::ofstream& ofStream)
{
	// Only print constructor if the model has any sub objects
	if (this->hasSubObjects())
	{
		// Print constructor
		std::string constructorHeader = this->getClassName() + "(";

		foreach (nddlgen::models::NddlGeneratablePtr generatableModel, this->_subObjects)
		{
			std::string parameter = generatableModel->getClassName() + " " + generatableModel->getNamePrefSuff() + ", ";
			constructorHeader += parameter;
		}

		constructorHeader = constructorHeader.substr(0, constructorHeader.length() - 2);

		constructorHeader += ")";

		wrln(1, constructorHeader, 1);
		wrln(1, "{", 1);

		foreach (nddlgen::models::NddlGeneratablePtr generatableModel, this->_subObjects)
		{
			std::string assignment = generatableModel->getNamePref() + " = " + generatableModel->getNamePrefSuff() + ";";

			wrln(2, assignment, 1);
		}

		wrln(1, "}", 1);
	}
}

void nddlgen::models::NddlGeneratable::setName(std::string name)
{
	this->_name = name;
}

std::string nddlgen::models::NddlGeneratable::getName()
{
	return this->_name;
}

std::string nddlgen::models::NddlGeneratable::getNamePref()
{
	return "_" + this->getName();
}

std::string nddlgen::models::NddlGeneratable::getNamePrefSuff()
{
	return this->getNamePref() + "_param";
}

std::string nddlgen::models::NddlGeneratable::getAccessor()
{
	std::string accessor = this->getNamePref();

	if (this->hasSuperObject())
	{
		nddlgen::models::NddlGeneratablePtr superObject = this->_superObject.lock();

		accessor = superObject->getAccessor() + "." + accessor;
	}

	return accessor;
}

void nddlgen::models::NddlGeneratable::setClassName(std::string className)
{
	this->_className = className;
}

std::string nddlgen::models::NddlGeneratable::getClassName()
{
	return this->_className;
}

void nddlgen::models::NddlGeneratable::addBlockingObject(nddlgen::models::NddlGeneratablePtr blockingObject)
{
	this->_blockedBy.push_back(blockingObject);
}

bool nddlgen::models::NddlGeneratable::isBlocked()
{
	return (this->_blockedBy.size() != 0);
}

void nddlgen::models::NddlGeneratable::addPredicate(std::string predicate)
{
	this->_predicates.push_back(predicate);
}

bool nddlgen::models::NddlGeneratable::hasPredicates()
{
	return (this->_predicates.size() != 0);
}

void nddlgen::models::NddlGeneratable::setInitialPredicate(std::string initialPredicate)
{
	this->_initialPredicate = initialPredicate;
}

std::string nddlgen::models::NddlGeneratable::getInitialPredicate()
{
	return this->_initialPredicate;
}

nddlgen::utilities::InitialStateFactPtr nddlgen::models::NddlGeneratable::getInitialState()
{
	if (this->_initialPredicate == "")
	{
		// TODO: throw proper exception
		throw "No initial predicate was set for " + this->_name;
	}

	nddlgen::utilities::InitialStateFactPtr fact(new nddlgen::utilities::InitialStateFact());

	fact->setFactName(this->getName() + "_" + this->getInitialPredicate());
	fact->setModelName(this->getName());
	fact->setPredicate(this->getInitialPredicate());

	return fact;
}

void nddlgen::models::NddlGeneratable::addAction(nddlgen::utilities::ModelActionPtr action)
{
	this->_actions.push_back(action);
}

bool nddlgen::models::NddlGeneratable::hasActions()
{
	return (this->_actions.size() != 0);
}

nddlgen::types::ActionList nddlgen::models::NddlGeneratable::getActions()
{
	return this->_actions;
}

nddlgen::math::CuboidPtr nddlgen::models::NddlGeneratable::getObjectBoundingBox()
{
	return this->_objectBoundingBox;
}

void nddlgen::models::NddlGeneratable::setObjectBoundingBox(nddlgen::math::CuboidPtr objectBoundingBox)
{
	this->_objectBoundingBox = objectBoundingBox;
}

bool nddlgen::models::NddlGeneratable::hasObjectBoundingBox()
{
	return (bool) this->_objectBoundingBox;
}

nddlgen::math::CuboidPtr nddlgen::models::NddlGeneratable::getAccessibilityBoundingBox()
{
	return this->_accessibilityBoundingBox;
}

void nddlgen::models::NddlGeneratable::setAccessibilityBoundingBox(nddlgen::math::CuboidPtr accessibilityBoundingBox)
{
	this->_accessibilityBoundingBox = accessibilityBoundingBox;
}

bool nddlgen::models::NddlGeneratable::hasAccessibilityBoundingBox()
{
	return (bool) this->_accessibilityBoundingBox;
}

bool nddlgen::models::NddlGeneratable::hasSubObjects()
{
	return (this->_subObjects.size() != 0);
}

void nddlgen::models::NddlGeneratable::addSubObject(nddlgen::models::NddlGeneratablePtr subObject)
{
	subObject->setSuperObject(this->shared_from_this());
	this->_subObjects.push_back(subObject);
}

std::vector<nddlgen::models::NddlGeneratablePtr> nddlgen::models::NddlGeneratable::getSubObjects()
{
	return this->_subObjects;
}

nddlgen::models::NddlGeneratablePtr nddlgen::models::NddlGeneratable::getSubObjectByName(std::string name)
{
	foreach (nddlgen::models::NddlGeneratablePtr generatableModel, this->_subObjects)
	{
		if (generatableModel->getName() == name)
		{
			return generatableModel;
		}
	}

	nddlgen::models::NddlGeneratablePtr null(0);
	return null;
}

void nddlgen::models::NddlGeneratable::setInstanceNameFor(int index, std::string instanceName)
{
	this->_subObjects.at(index)->setName(instanceName);
}

bool nddlgen::models::NddlGeneratable::hasSuperObject()
{
	nddlgen::models::NddlGeneratablePtr superObject = this->_superObject.lock();
	return (bool) superObject;
}

void nddlgen::models::NddlGeneratable::setSuperObject(nddlgen::models::NddlGeneratablePtr superObject)
{
	this->_superObject = superObject;
}
