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

}

nddlgen::controllers::DomainDescriptionFactory::~DomainDescriptionFactory()
{

}

nddlgen::models::DomainDescriptionModelPtr nddlgen::controllers::DomainDescriptionFactory::build(
		nddlgen::types::SdfRoot sdfRoot,
		nddlgen::types::IsdRoot isdRoot)
{
	if (!this->_modelFactory)
	{
		throw nddlgen::exceptions::ModelFactoryNotSetException();
	}

	nddlgen::models::DomainDescriptionModelPtr domainDescription(new nddlgen::models::DomainDescriptionModel());
	nddlgen::models::ArmModelPtr arm(new nddlgen::models::ArmModel());
	nddlgen::models::WorkspaceModelPtr workspace(new nddlgen::models::WorkspaceModel());

	// Set names for arm and workspace
	arm->setName("arm");
	workspace->setName("workspace");

	// Add both of them into the hierarchy
	arm->setWorkspace(workspace);
	domainDescription->setArm(arm);

	// Populate the model with given SDF and ISD roots
	this->populateModelsFromSdf(domainDescription, sdfRoot);
	this->populateInitialStateFromIsd(domainDescription, isdRoot);

	// Return the fully qualified domain description model
	return domainDescription;
}

void nddlgen::controllers::DomainDescriptionFactory::setModelFactory(
		nddlgen::controllers::NddlGeneratableFactoryPtr modelFactory)
{
	this->_modelFactory = modelFactory;
}

void nddlgen::controllers::DomainDescriptionFactory::populateModelsFromSdf(
		nddlgen::models::DomainDescriptionModelPtr domainDescription,
		nddlgen::types::SdfRoot sdfRoot)
{
	nddlgen::models::WorkspaceModelPtr workspace = domainDescription->getArm()->getWorkspace();
	sdf::ElementPtr currentModelElement = sdfRoot->root->GetElement("world")->GetElement("model");

	// Iterate through elements in SDF model node
	while (currentModelElement)
	{
		nddlgen::models::NddlGeneratablePtr generatableModel = this->modelFactory(currentModelElement);

		// If generatableModel is null, it is not supported by the given model factory
		// and will not be added to the workspace
		if (generatableModel)
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
		nddlgen::models::DomainDescriptionModelPtr domainDescription,
		nddlgen::types::IsdRoot isdRoot)
{
	nddlgen::models::InitialStateModelPtr initialState(new nddlgen::models::InitialStateModel());
//
//	TiXmlHandle isdRootHandle(isdRoot.RootElement());
//
//	std::cout << isdRootHandle.ToElement()->Attribute("version") << std::endl;
//
//
//	TiXmlElement* facts = isdRootHandle.FirstChild("facts").FirstChild("fact").ToElement();
//	TiXmlElement* goals = isdRootHandle.FirstChild("goals").FirstChild("goal").ToElement();
//
//	for (; facts; facts = facts->NextSiblingElement())
//	{
//		nddlgen::utilities::InitialStateFact* fact = this->factFactory(facts);
//		std::cout << "fact " << std::endl;
//		initialState->addFact(fact);
//	}
//
//	for (; goals; goals = goals->NextSiblingElement())
//	{
//		nddlgen::utilities::InitialStateGoal* goal = this->goalFactory(goals);
//		std::cout << "goal " << std::endl;
//		initialState->addGoal(goal);
//	}
//
	domainDescription->setInitialState(initialState);
}

nddlgen::models::NddlGeneratablePtr nddlgen::controllers::DomainDescriptionFactory::modelFactory(sdf::ElementPtr element)
{
	std::string elementName = element->GetAttribute("name")->GetAsString();
	nddlgen::models::NddlGeneratablePtr instance = this->_modelFactory->fromString(elementName);

	if (instance)
	{
		instance->setName(elementName);
	}

	return instance;
}

nddlgen::utilities::InitialStateFactPtr nddlgen::controllers::DomainDescriptionFactory::factFactory(TiXmlElement* factElement)
{
	nddlgen::utilities::InitialStateFactPtr fact(new nddlgen::utilities::InitialStateFact());

	fact->setModelName(factElement->Attribute("for"));
	fact->setPredicate(factElement->Attribute("predicate"));

	return fact;
}

nddlgen::utilities::InitialStateGoalPtr nddlgen::controllers::DomainDescriptionFactory::goalFactory(TiXmlElement* goalElement)
{
	nddlgen::utilities::InitialStateGoalPtr goal(new nddlgen::utilities::InitialStateGoal());

	goal->setModelName(goalElement->Attribute("for"));
	goal->setPredicate(goalElement->Attribute("predicate"));
	goal->setMaxTicks(goalElement->Attribute("max-ticks"));

	return goal;
}
