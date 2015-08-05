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

#include <nddlgen/models/Arm.h>

namespace nddlgen { namespace models
{

	Arm::Arm()
	{
		this->setClassName("Arm");

		this->_workspace = nullptr;
	}

	Arm::~Arm()
	{
		boost::checked_delete(this->_workspace);
	}


	void Arm::generateModel(std::ofstream& ofStream)
	{
		std::string armClass = this->getClassName();
		std::string workspaceClass = this->getWorkspace()->getClassName();
		std::string workspacePref = this->_workspace->getNamePref();
		std::string workspacePrefSuff = this->_workspace->getNamePrefSuff();
		nddlgen::types::ActionList actions = this->_workspace->getActions();

		// Workspace class
		this->_workspace->generateModel(ofStream);

		// #\t  text																	#endl
		wrln(0, "class " + armClass,													1);
		wrln(0, "{", 																	1);
		wrln(1, 	workspaceClass + " " + workspacePref + ";",							2);

		wrln(1, 	armClass + "(" + workspaceClass + " " + workspacePrefSuff + ")",	1);
		wrln(1, 	"{",																1);
		wrln(2,			workspacePref + " = " + workspacePrefSuff + ";",				1);
		wrln(1, 	"}",																2);

		foreach (nddlgen::utilities::ModelAction& actionObject, actions)
		{
			nddlgen::utilities::ModelAction* action = &actionObject;

			wrln(1, action->getActionDefinition(), 										1);
		}

		wrln(0, "}",																	2);
		// End Workspace class

		// Arm member functions
		foreach (nddlgen::utilities::ModelAction& actionObject, actions)
		{
			nddlgen::utilities::ModelAction* action = &actionObject;

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

	void Arm::generateInitialState(std::ofstream& ofStream)
	{
		//ofStream << this->_workspace->generateInitialStateAsString(ofStream);
	}


	void Arm::setWorkspace(nddlgen::models::Workspace* workspace)
	{
		this->_workspace = workspace;
	}

	nddlgen::models::Workspace* Arm::getWorkspace()
	{
		return this->_workspace;
	}

}}
