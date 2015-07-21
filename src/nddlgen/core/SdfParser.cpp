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

#include "nddlgen/core/SdfParser.h"

namespace nddlgen { namespace core
{

	SdfParser::SdfParser(nddlgen::models::Arm* armModel)
	{
		this->_armModel = armModel;
		this->_armModel->setName("arm");
	}

	SdfParser::~SdfParser()
	{
		// TODO Auto-generated destructor stub
	}


	bool SdfParser::parseDataStructure(sdf::ElementPtr sdfRoot)
	{
		nddlgen::types::ModelList models;

		// Try instantiating Workspace model
		if (!this->instantiateWorkspace())
		{
			return false;
		}

		// Convert sdformat's data structure into one that can be better processed
		if (!this->convertModelDataStructure(sdfRoot->GetElement("world")->GetElement("model"), &models))
		{
			return false;
		}

		// Try instantiating Models (Boxes, ...)
		if (!this->instantiateModels(models))
		{
			return false;
		}

		// Try calculating dependencies (Does the lid of a box block another, ...)
		if (!this->calculateDependencies(models))
		{
			return false;
		}

		return true;
	}


	bool SdfParser::instantiateWorkspace()
	{
		nddlgen::models::Workspace* workspace = new nddlgen::models::Workspace();
		workspace->setName("workspace");

		this->_armModel->setWorkspace(workspace);

		return true;
	}

	bool SdfParser::convertModelDataStructure(sdf::ElementPtr modelElements, nddlgen::types::ModelList* models)
	{
		sdf::ElementPtr currentModelElement = modelElements;

		// The sdf lib only offers a useless data structure for the models, so it is
		// converted into a ModelList here
		while (currentModelElement != nullptr)
		{
			models->push_back(currentModelElement);

			// Iterate
			currentModelElement = currentModelElement->GetNextElement("model");
		}

		return true;
	}

	bool SdfParser::instantiateModels(nddlgen::types::ModelList models)
	{
		nddlgen::models::Workspace* workspace = this->_armModel->getWorkspace();

		foreach (sdf::ElementPtr model, models)
		{
			nddlgen::models::NddlGeneratable* generatableModel = this->instanceFactory(model);

			if (generatableModel != nullptr)
			{
				workspace->addModelToWorkspace(generatableModel);
			}
		}

		return true;
	}

	bool SdfParser::calculateDependencies(nddlgen::types::ModelList models)
	{
		this->_armModel->getWorkspace()->postInitProcessing();

		return true;
	}


	nddlgen::models::NddlGeneratable* SdfParser::instanceFactory(sdf::ElementPtr element)
	{
		std::string elementName = element->GetAttribute("name")->GetAsString();
		std::string elementNameLc = boost::algorithm::to_lower_copy(elementName);
		nddlgen::models::NddlGeneratable* instance;

		if (boost::algorithm::contains(elementNameLc, "lidbox"))
		{
			instance = new nddlgen::models::LidBox();
		}
		else if (boost::algorithm::contains(elementNameLc, "box"))
		{
			instance = new nddlgen::models::Box();
		}
		else if (boost::algorithm::contains(elementNameLc, "objectslidecontainer"))
		{
			instance = new nddlgen::models::ObjectSlideContainer();
		}
		else if (boost::algorithm::contains(elementNameLc, "objectslide"))
		{
			instance = new nddlgen::models::ObjectSlide();
		}
		else
		{
			instance = nullptr;
		}

		if (instance != nullptr)
		{
			instance->setName(elementName);
		}

		return instance;
	}

}}
