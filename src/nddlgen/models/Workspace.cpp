/**
 * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)
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

#include <nddlgen/models/Workspace.h>

namespace nddlgen { namespace models
{

	Workspace::Workspace()
	{
		this->_modelClasses.push_back(new nddlgen::models::Box());
		this->_modelClasses.push_back(new nddlgen::models::LidBox());
		this->_modelClasses.push_back(new nddlgen::models::ObjectSlide());
		this->_modelClasses.push_back(new nddlgen::models::ObjectSlideContainer());
	}

	Workspace::~Workspace()
	{
		// @todo watch out to delete objects properly in future
	}


	void Workspace::generateModelAsString(std::ofstream& ofStream)
	{
		foreach (nddlgen::models::NddlGeneratable& generatableModelObject, this->_modelClasses)
		{
			nddlgen::models::NddlGeneratable* generatableModel = &generatableModelObject;

			generatableModel->generateModelAsString(ofStream);

			ofStream << std::endl;
		}

		ofStream << "class Workspace" << std::endl;
		ofStream << "{" << std::endl;

		ofStream << "}" << std::endl;
	}

	void Workspace::generateInitialStateAsString(std::ofstream& ofStream)
	{

	}


	void Workspace::addModelToWorkspace(nddlgen::models::NddlGeneratable* model)
	{
		this->_models.push_back(model);
	}

	nddlgen::models::NddlGeneratable* Workspace::getModelByName(std::string name)
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

}}
