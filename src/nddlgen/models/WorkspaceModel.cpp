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

#include <nddlgen/models/WorkspaceModel.h>

namespace nddlgen { namespace models
{

	WorkspaceModel::WorkspaceModel()
	{
		this->setClassName("Workspace");
	}

	WorkspaceModel::~WorkspaceModel()
	{

	}


	void WorkspaceModel::postInitProcessing()
	{
		foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_models)
		{
			nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;

			generatableModel->postInitProcessing();
		}
	}


	void WorkspaceModel::generateModel(std::ofstream& ofStream)
	{
		std::list<std::string> alreadyDefinedClasses;

		foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_models)
		{
			nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;

			if (std::find(alreadyDefinedClasses.begin(), alreadyDefinedClasses.end(), generatableModel->getClassName())
				== alreadyDefinedClasses.end())
			{
				generatableModel->generateModel(ofStream);
				alreadyDefinedClasses.push_back(generatableModel->getClassName());
			}

		}

		wrln(0, "class " + this->getClassName(),	1);
		wrln(0, "{",								1);

		this->generateWorkspaceMembers(ofStream);

		this->generateWorkspaceConstructor(ofStream);

		wrln(0, "}",								2);
	}

	void WorkspaceModel::generateInitialState(std::ofstream& ofStream)
	{

	}


	void WorkspaceModel::addModelToWorkspace(nddlgen::models::NddlGeneratable* model)
	{
		this->_models.push_back(model);
	}

	nddlgen::models::NddlGeneratable* WorkspaceModel::getModelByName(std::string name)
	{
		foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_models)
		{
			nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;

			if (generatableModel->getName() == name)
			{
				return generatableModel;
			}
		}

		return nullptr;
	}

	nddlgen::types::ActionList WorkspaceModel::getActions()
	{
		nddlgen::types::ActionList actionList;

		foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_models)
		{
			nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;
			nddlgen::types::ActionList actions = generatableModel->getActions();


			actionList.insert(actionList.end(), actions.begin(), actions.end());
		}

		return actionList;
	}

	void WorkspaceModel::generateWorkspaceMembers(std::ofstream& ofStream)
	{
		foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_models)
		{
			nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;

			std::string className = generatableModel->getClassName();
			std::string instanceName = generatableModel->getNamePref();

			wrln(1, className + " " + instanceName + ";", 		1);
		}

		wrel(1);
	}

	void WorkspaceModel::generateWorkspaceConstructor(std::ofstream& ofStream)
	{
		std::string constructorHeader = this->getClassName() + "(";

		if (this->_models.size() > 0)
		{
			foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_models)
			{
				nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;
				std::string parameter = generatableModel->getClassName() + " " + generatableModel->getNamePrefSuff() + ", ";
				constructorHeader += parameter;
			}

			constructorHeader = constructorHeader.substr(0, constructorHeader.length() - 2);
		}

		constructorHeader += ")";

		wrln(1, constructorHeader,								1);
		wrln(1, "{",											1);

		foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_models)
		{
			nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;
			std::string assignment = generatableModel->getNamePref() + " = " + generatableModel->getNamePrefSuff() + ";";

			wrln(2, assignment, 1);
		}

		wrln(1, "}",											1);
	}

}}
