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

#ifndef NDDLGEN_CONTROLLER_DOMAINDESCRIPTIONFACTORY_H_
#define NDDLGEN_CONTROLLER_DOMAINDESCRIPTIONFACTORY_H_

#include <cstddef>

#include <sdf/sdf.hh>
#include <tinyxml.h>

#include <nddlgen/controllers/NddlGeneratableFactory.h>
#include <nddlgen/exceptions/ModelFactoryNotSetException.hpp>
#include <nddlgen/models/ArmModel.h>
#include <nddlgen/models/DomainDescriptionModel.h>
#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/WorkspaceModel.h>
#include <nddlgen/utilities/InitialStateFact.h>
#include <nddlgen/utilities/InitialStateGoal.h>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/Foreach.hpp>

namespace nddlgen { namespace controllers { class DomainDescriptionFactory; }}

class nddlgen::controllers::DomainDescriptionFactory
{

	private:

		nddlgen::controllers::NddlGeneratableFactory* _modelFactory;

		void populateModelsFromSdf(nddlgen::models::DomainDescriptionModel* domainDescription,
				nddlgen::types::SdfRoot sdfRoot);

		void populateInitialStateFromIsd(nddlgen::models::DomainDescriptionModel* domainDescription,
				nddlgen::types::IsdRoot isdRoot);

		nddlgen::models::NddlGeneratable* modelFactory(sdf::ElementPtr element);

		nddlgen::utilities::InitialStateFact* factFactory(TiXmlElement* factElement);

		nddlgen::utilities::InitialStateGoal* goalFactory(TiXmlElement* goalElement);

	public:

		DomainDescriptionFactory();
		virtual ~DomainDescriptionFactory();

		nddlgen::models::DomainDescriptionModel* build(nddlgen::types::SdfRoot sdfRoot,
				nddlgen::types::IsdRoot isdRoot);

		void setModelFactory(nddlgen::controllers::NddlGeneratableFactory* modelFactory);

};

#endif
