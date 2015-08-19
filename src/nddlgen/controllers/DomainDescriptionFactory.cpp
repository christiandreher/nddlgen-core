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

#include <nddlgen/controllers/DomainDescriptionFactory.h>

nddlgen::models::DomainDescriptionModel* nddlgen::controllers::DomainDescriptionFactory::build(
		nddlgen::types::SdfRoot sdfRoot,
		nddlgen::types::IsdRoot isdRoot)
{
	nddlgen::models::DomainDescriptionModel* domainDescription = new nddlgen::models::DomainDescriptionModel();
	nddlgen::models::ArmModel* arm = new nddlgen::models::ArmModel();
	nddlgen::types::ModelList models;

	arm->setName("arm");
	domainDescription->setArm(arm);

	DomainDescriptionFactory::instantiateWorkspace(domainDescription);
	DomainDescriptionFactory::populateModelListFromSdf(sdfRoot->GetElement("world")->GetElement("model"), &models);
	DomainDescriptionFactory::addRelevantModelsToWorkspace(domainDescription, models);
	DomainDescriptionFactory::calculateDependencies(domainDescription, models);

	return domainDescription;
}


nddlgen::controllers::DomainDescriptionFactory::DomainDescriptionFactory()
{

}

nddlgen::controllers::DomainDescriptionFactory::~DomainDescriptionFactory()
{

}


void nddlgen::controllers::DomainDescriptionFactory::instantiateWorkspace(
		nddlgen::models::DomainDescriptionModel* domainDescription)
{
	nddlgen::models::WorkspaceModel* workspace = new nddlgen::models::WorkspaceModel();
	workspace->setName("workspace");

	domainDescription->getArm()->setWorkspace(workspace);
}

void nddlgen::controllers::DomainDescriptionFactory::populateModelListFromSdf(
		sdf::ElementPtr modelElements,
		nddlgen::types::ModelList* models)
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

void nddlgen::controllers::DomainDescriptionFactory::addRelevantModelsToWorkspace(
		nddlgen::models::DomainDescriptionModel* domainDescription,
		nddlgen::types::ModelList models)
{
	nddlgen::models::WorkspaceModel* workspace = domainDescription->getArm()->getWorkspace();

	foreach (sdf::ElementPtr model, models)
	{
		nddlgen::models::NddlGeneratable* generatableModel = DomainDescriptionFactory::instanceFactory(model);

		if (generatableModel != nullptr)
		{
			workspace->addModelToWorkspace(generatableModel);
		}
	}
}

void nddlgen::controllers::DomainDescriptionFactory::calculateDependencies(
		nddlgen::models::DomainDescriptionModel* domainDescription,
		nddlgen::types::ModelList models)
{
	domainDescription->getArm()->getWorkspace()->postInitProcessing();
}


nddlgen::models::NddlGeneratable* nddlgen::controllers::DomainDescriptionFactory::instanceFactory(
		sdf::ElementPtr element)
{
	std::string elementName = element->GetAttribute("name")->GetAsString();

	return nddlgen::controllers::NddlGeneratableFactory::fromString(elementName);
}
