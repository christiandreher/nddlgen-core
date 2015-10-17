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
	nddlgen::models::WorkspaceModel* workspace = new nddlgen::models::WorkspaceModel();
	nddlgen::types::ModelList models;

	// Set names for arm and workspace
	arm->setName("arm");
	workspace->setName("workspace");

	// Add both of them into the hierarchy
	arm->setWorkspace(workspace);
	domainDescription->setArm(arm);

	// Populate the model with given sdf and isd roots
	this->populateModelsFromSdf(domainDescription, sdfRoot);
	this->populateInitialStateFromIsd(domainDescription, isdRoot);

	// Return the fully qualified domain description model
	return domainDescription;
}


void nddlgen::controllers::DomainDescriptionFactory::setModelFactory(
		nddlgen::controllers::NddlGeneratableFactory* modelFactory)
{
	this->_modelFactory = modelFactory;
}


void nddlgen::controllers::DomainDescriptionFactory::populateModelsFromSdf(
		nddlgen::models::DomainDescriptionModel* domainDescription,
		nddlgen::types::SdfRoot sdfRoot)
{
	nddlgen::models::WorkspaceModel* workspace = domainDescription->getArm()->getWorkspace();
	sdf::ElementPtr currentModelElement = sdfRoot->GetElement("world")->GetElement("model");

	// Iterate through elements in sdf model node
	while (currentModelElement != nullptr)
	{
		nddlgen::models::NddlGeneratable* generatableModel = this->modelFactory(currentModelElement);

		// If generatableModel is a nullptr, it is not supported by the given model factory
		// and will not be added to the workspace
		if (generatableModel != nullptr)
		{
			workspace->addModelToWorkspace(generatableModel);
		}

		// Iterate
		currentModelElement = currentModelElement->GetNextElement("model");
	}

	// Run post-init processing
	workspace->postInitProcessing();
}

void nddlgen::controllers::DomainDescriptionFactory::populateInitialStateFromIsd(
		nddlgen::models::DomainDescriptionModel* domainDescription,
		nddlgen::types::IsdRoot isdRoot)
{
	nddlgen::models::InitialStateModel* initialState = new nddlgen::models::InitialStateModel();

	TiXmlElement* facts = isdRoot->FirstChildElement("facts")->FirstChildElement("fact");
	TiXmlElement* goals = isdRoot->FirstChildElement("goals")->FirstChildElement("goal");

	for (; facts; facts = facts->NextSiblingElement())
	{
		nddlgen::utilities::InitialStateFact* fact = this->factFactory(facts);
		initialState->addFact(fact);
	}

	for (; goals; goals = goals->NextSiblingElement())
	{
		nddlgen::utilities::InitialStateGoal* goal = this->goalFactory(goals);
		initialState->addGoal(goal);
	}

	domainDescription->setInitialState(initialState);
}


nddlgen::models::NddlGeneratable* nddlgen::controllers::DomainDescriptionFactory::modelFactory(sdf::ElementPtr element)
{
	std::string elementName = element->GetAttribute("name")->GetAsString();
	nddlgen::models::NddlGeneratable* instance = this->_modelFactory->fromString(elementName);

	if (instance != nullptr)
	{
		instance->setName(elementName);
	}

	return instance;
}

nddlgen::utilities::InitialStateFact* nddlgen::controllers::DomainDescriptionFactory::factFactory(TiXmlElement* factElement)
{
	nddlgen::utilities::InitialStateFact* fact = new nddlgen::utilities::InitialStateFact();

	fact->setModelName(factElement->Value());
	fact->setPredicate(factElement->Attribute("for"));

	return fact;
}

nddlgen::utilities::InitialStateGoal* nddlgen::controllers::DomainDescriptionFactory::goalFactory(TiXmlElement* goalElement)
{
	nddlgen::utilities::InitialStateGoal* goal = new nddlgen::utilities::InitialStateGoal();

	goal->setModelName(goalElement->Value());
	goal->setPredicate(goalElement->Attribute("for"));
	goal->setMaxTicks(goalElement->Attribute("max-ticks"));

	return goal;
}
