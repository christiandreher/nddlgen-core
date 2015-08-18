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

#include <sdf/sdf.hh>

#include <nddlgen/controller/NddlGeneratableFactory.h>
#include <nddlgen/models/ArmModel.h>
#include <nddlgen/models/DomainDescriptionModel.h>
#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/WorkspaceModel.h>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/Foreach.hpp>

namespace nddlgen { namespace controller
{

	class DomainDescriptionFactory
	{

		private:

			DomainDescriptionFactory();
			virtual ~DomainDescriptionFactory();

			static void instantiateWorkspace(nddlgen::models::DomainDescriptionModel* domainDescription);
			static void populateModelListFromSdf(sdf::ElementPtr modelElements, nddlgen::types::ModelList* models);
			static void addRelevantModelsToWorkspace(nddlgen::models::DomainDescriptionModel* domainDescription,
					nddlgen::types::ModelList models);
			static void calculateDependencies(nddlgen::models::DomainDescriptionModel* domainDescription,
					nddlgen::types::ModelList models);

			static nddlgen::models::NddlGeneratable* instanceFactory(sdf::ElementPtr element);

		public:

			static nddlgen::models::DomainDescriptionModel* build(nddlgen::types::SdfRoot sdfRoot,
					nddlgen::types::IsdRoot isdRoot);

	};

}}

#endif
