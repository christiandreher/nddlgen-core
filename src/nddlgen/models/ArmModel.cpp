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

void nddlgen::models::ArmModel::generateModel(std::ofstream& ofStream)
{
	std::string armClass = this->getClassName();
	std::string workspaceClass = this->getWorkspace()->getClassName();
	std::string workspacePref = this->_workspace->getNamePref();
	std::string workspacePrefSuff = this->_workspace->getNamePrefSuff();
	nddlgen::types::ActionList actions = this->_workspace->getActions();

	// Arm class
	this->_workspace->generateModel(ofStream);

	// #\t  text																	#endl
	wrln(0, "class " + armClass,													1);
	wrln(0, "{", 																	1);
	wrln(1, 	workspaceClass + " " + workspacePref + ";",							2);

	wrln(1, 	armClass + "(" + workspaceClass + " " + workspacePrefSuff + ")",	1);
	wrln(1, 	"{",																1);
	wrln(2,			workspacePref + " = " + workspacePrefSuff + ";",				1);
	wrln(1, 	"}",																2);

	foreach (nddlgen::utilities::ModelActionPtr action, actions)
	{
		wrln(1, action->getActionDefinition(), 										1);
	}

	wrln(0, "}",																	2);
	// End Arm class

	// Arm member functions
	foreach (nddlgen::utilities::ModelActionPtr action, actions)
	{
		std::string actionName = action->getName();
		std::list<std::string> actionSteps = action->getActionSteps(workspacePref);

		// Arm member function
		wrln(0, armClass + "::" + actionName,										1);
		wrln(0, "{",																1);

		foreach (std::string actionStep, actionSteps)
		{
			wrln(1, actionStep, 													1);
		}

		wrln(0, "}",																2);
		// End Arm member function
	}
	// End Arm member functions
}

void nddlgen::models::ArmModel::generateInitialState(std::ofstream& ofStream)
{
	//ofStream << this->_workspace->generateInitialStateAsString(ofStream);
}

void nddlgen::models::ArmModel::setWorkspace(nddlgen::models::WorkspaceModelPtr workspace)
{
	this->_workspace = workspace;
}

nddlgen::models::WorkspaceModelPtr nddlgen::models::ArmModel::getWorkspace()
{
	return this->_workspace;
}
