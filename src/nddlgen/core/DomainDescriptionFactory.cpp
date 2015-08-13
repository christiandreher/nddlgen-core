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

#include <nddlgen/core/DomainDescriptionFactory.h>

namespace nddlgen { namespace core
{

	DomainDescriptionFactory::DomainDescriptionFactory()
	{

	}

	DomainDescriptionFactory::~DomainDescriptionFactory()
	{

	}


	nddlgen::models::DomainDescription* DomainDescriptionFactory::getDomainDescription(sdf::ElementPtr sdfRoot)
	{
		nddlgen::models::DomainDescription* ddm = new nddlgen::models::DomainDescription();
		nddlgen::models::Arm* arm = new nddlgen::models::Arm();
		nddlgen::types::ModelList models;

		arm->setName("arm");
		ddm->setArm(arm);

		DomainDescriptionFactory::instantiateWorkspace(ddm);
		DomainDescriptionFactory::populateModelListFromSdf(sdfRoot->GetElement("world")->GetElement("model"), &models);
		DomainDescriptionFactory::addRelevantModelsToWorkspace(ddm, models);
		DomainDescriptionFactory::calculateDependencies(ddm, models);

		return ddm;
	}


	void DomainDescriptionFactory::instantiateWorkspace(nddlgen::models::DomainDescription* ddm)
	{
		nddlgen::models::Workspace* workspace = new nddlgen::models::Workspace();
		workspace->setName("workspace");

		ddm->getArm()->setWorkspace(workspace);
	}

	void DomainDescriptionFactory::populateModelListFromSdf(sdf::ElementPtr modelElements, nddlgen::types::ModelList* models)
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
	}

	void DomainDescriptionFactory::addRelevantModelsToWorkspace(nddlgen::models::DomainDescription* ddm, nddlgen::types::ModelList models)
	{
		nddlgen::models::Workspace* workspace = ddm->getArm()->getWorkspace();

		foreach (sdf::ElementPtr model, models)
		{
			nddlgen::models::NddlGeneratable* generatableModel = DomainDescriptionFactory::instanceFactory(model);

			if (generatableModel != nullptr)
			{
				workspace->addModelToWorkspace(generatableModel);
			}
		}
	}

	void DomainDescriptionFactory::calculateDependencies(nddlgen::models::DomainDescription* ddm, nddlgen::types::ModelList models)
	{
		ddm->getArm()->getWorkspace()->postInitProcessing();
	}


	nddlgen::models::NddlGeneratable* DomainDescriptionFactory::instanceFactory(sdf::ElementPtr element)
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
