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

nddlgen::controllers::DomainDescriptionFactory::DomainDescriptionFactory()
{
	this->_modelFactory = nullptr;
}

nddlgen::controllers::DomainDescriptionFactory::~DomainDescriptionFactory()
{

}


nddlgen::models::DomainDescriptionModel* nddlgen::controllers::DomainDescriptionFactory::build(
		nddlgen::types::SdfRoot sdfRoot,
		nddlgen::types::IsdRoot isdRoot)
{
	if (this->_modelFactory == nullptr)
	{
		throw nddlgen::exceptions::ModelFactoryNotSetException();
	}

	nddlgen::models::DomainDescriptionModel* domainDescription = new nddlgen::models::DomainDescriptionModel();
	nddlgen::models::ArmModel* arm = new nddlgen::models::ArmModel();
	nddlgen::types::ModelList models;

	arm->setName("arm");
	domainDescription->setArm(arm);

	this->instantiateWorkspace(domainDescription);
	this->populateModelListFromSdf(sdfRoot->GetElement("world")->GetElement("model"), &models);
	this->addRelevantModelsToWorkspace(domainDescription, models);
	this->calculateDependencies(domainDescription, models);

	this->populateInitialStateFromIsd(domainDescription, isdRoot);

	return domainDescription;
}


void nddlgen::controllers::DomainDescriptionFactory::setModelFactory(
		nddlgen::controllers::NddlGeneratableFactory* modelFactory)
{
	this->_modelFactory = modelFactory;
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
		nddlgen::models::NddlGeneratable* generatableModel = this->instanceFactory(model);

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

void nddlgen::controllers::DomainDescriptionFactory::populateInitialStateFromIsd(
		nddlgen::models::DomainDescriptionModel* domainDescription,
		nddlgen::types::IsdRoot isdRoot)
{
	nddlgen::models::InitialStateModel* initialState = new nddlgen::models::InitialStateModel();
}


nddlgen::models::NddlGeneratable* nddlgen::controllers::DomainDescriptionFactory::instanceFactory(
		sdf::ElementPtr element)
{
	std::string elementName = element->GetAttribute("name")->GetAsString();
	nddlgen::models::NddlGeneratable* instance = this->_modelFactory->fromString(elementName);

	if (instance != nullptr)
	{
		instance->setName(elementName);
	}

	return instance;
}
