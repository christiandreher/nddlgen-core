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

#include <nddlgen/models/ArmModel.h>

nddlgen::models::ArmModel::ArmModel()
{
	this->setClassName("Arm");
}

nddlgen::models::ArmModel::~ArmModel()
{

}

void nddlgen::models::ArmModel::initSubObjects()
{
	nddlgen::models::ProcessModelPtr armProcess(new nddlgen::models::ProcessModel());
	armProcess->setName("armprocess");

	this->addSubObject(armProcess);
}

void nddlgen::models::ArmModel::generateModel(std::ofstream& ofStream)
{
	// Arm needs Timeline, since actions should be executed one by one
	wrln(0, "class " + this->_className + " extends Timeline", 1);
	wrln(0, "{", 1);

	// Print predicates if present
	this->generateModelPredicates(ofStream);

	// Print sub objects as member if present
	this->generateModelSubObjects(ofStream);

	// Print constructor if sub objects are set
	this->generateModelConstructor(ofStream);

	// Additional line to devide constructor and actions
	wrel(1);

	// Print action prototypes
	foreach (std::string actionPrototype, this->_actionPrototypes)
	{
		wrln(1, actionPrototype, 1);
	}

	wrln(0, "}", 2);
}

nddlgen::models::WorkspaceModelPtr nddlgen::models::ArmModel::getWorkspace()
{
	nddlgen::models::NddlGeneratablePtr workspaceUncasted = this->getSubObjectByName("workspace");
	nddlgen::models::WorkspaceModelPtr workspace = boost::dynamic_pointer_cast<nddlgen::models::WorkspaceModel>(workspaceUncasted);
	return workspace;
}

std::string nddlgen::models::ArmModel::getAccessor()
{
	return "object";
}

void nddlgen::models::ArmModel::setActionPrototypes(std::list<std::string> actionPrototypes)
{
	this->_actionPrototypes = actionPrototypes;
}
