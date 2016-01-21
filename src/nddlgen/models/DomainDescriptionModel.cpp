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

void nddlgen::models::DomainDescriptionModel::summarizeNeededClasses()
{
	std::list<nddlgen::models::NddlGeneratablePtr> allObjects = this->wrapSubObjects(this->_arm);

	foreach (nddlgen::models::NddlGeneratablePtr object, allObjects)
	{
		this->_usedClasses.insert(std::pair<std::string, nddlgen::models::NddlGeneratablePtr>(object->getClassName(),
				object));
	}
}

void nddlgen::models::DomainDescriptionModel::generateForwardDeclarations(std::ofstream& ofStream)
{
	for (std::map<std::string, nddlgen::models::NddlGeneratablePtr>::iterator it = this->_usedClasses.begin();
			it != this->_usedClasses.end(); it++)
	{
		it->second->generateForwardDeclaration(ofStream);
	}
}

void nddlgen::models::DomainDescriptionModel::generateInstantiations(std::ofstream& ofStream)
{
	this->_arm->generateInstantiation(ofStream);
}

void nddlgen::models::DomainDescriptionModel::generateModels(std::ofstream& ofStream)
{
	for (std::map<std::string, nddlgen::models::NddlGeneratablePtr>::iterator it = this->_usedClasses.begin();
			it != this->_usedClasses.end(); it++)
	{
		it->second->generateModel(ofStream);
	}
}

std::list<nddlgen::models::NddlGeneratablePtr> nddlgen::models::DomainDescriptionModel::wrapSubObjects(nddlgen::models::NddlGeneratablePtr model)
{
	std::list<nddlgen::models::NddlGeneratablePtr> output;

	if (model->hasSubObjects())
	{
		std::vector<nddlgen::models::NddlGeneratablePtr> subObjects = model->getSubObjects();

		foreach (nddlgen::models::NddlGeneratablePtr subObject, subObjects)
		{
			std::list<nddlgen::models::NddlGeneratablePtr> recursiveOutput = this->wrapSubObjects(subObject);
			output.insert(output.end(), recursiveOutput.begin(), recursiveOutput.end());
		}
	}

	output.push_back(model);

	return output;
}
