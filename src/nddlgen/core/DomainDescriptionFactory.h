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

#ifndef CORE_SDFPARSER_H_
#define CORE_SDFPARSER_H_

#include <sdf/sdf.hh>

#include <boost/algorithm/string.hpp>

#include <nddlgen/models/Arm.h>
#include <nddlgen/models/Box.h>
#include <nddlgen/models/DomainDescription.h>
#include <nddlgen/models/LidBox.h>
#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/ObjectSlide.h>
#include <nddlgen/models/ObjectSlideContainer.h>
#include <nddlgen/types/Types.hpp>
#include <nddlgen/utilities/Foreach.hpp>

namespace nddlgen { namespace core
{

	class DomainDescriptionFactory
	{

		private:

			static void instantiateWorkspace(nddlgen::models::DomainDescription* ddm);
			static void populateModelListFromSdf(sdf::ElementPtr modelElements, nddlgen::types::ModelList* models);
			static void addRelevantModelsToWorkspace(nddlgen::models::DomainDescription* ddm, nddlgen::types::ModelList models);
			static void calculateDependencies(nddlgen::models::DomainDescription* ddm, nddlgen::types::ModelList models);

			static nddlgen::models::NddlGeneratable* instanceFactory(sdf::ElementPtr element);

			DomainDescriptionFactory();
			virtual ~DomainDescriptionFactory();

		public:

			static nddlgen::models::DomainDescription* getDomainDescription(sdf::ElementPtr sdfRoot);

	};

}}

#endif
