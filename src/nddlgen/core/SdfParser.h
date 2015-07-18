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

#ifndef CORE_SDFPARSER_H_
#define CORE_SDFPARSER_H_

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <nddlgen/models/Arm.h>
#include <nddlgen/models/Box.h>
#include <nddlgen/models/LidBox.h>
#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/ObjectSlide.h>
#include <nddlgen/models/ObjectSlideContainer.h>

#include <sdf/sdf.hh>

#include "nddlgen/types/Types.h"


namespace nddlgen { namespace core
{

	class SdfParser
	{

		private:

			nddlgen::models::Arm* _armModel;

			bool instantiateWorkspace();
			bool convertModelDataStructure(sdf::ElementPtr modelElements, nddlgen::types::ModelList* models);
			bool instantiateModels(nddlgen::types::ModelList models);
			bool calculateDependencies(nddlgen::types::ModelList models);

			nddlgen::models::NddlGeneratable* instanceFactory(sdf::ElementPtr element);

		public:

			SdfParser(nddlgen::models::Arm* armModel);
			virtual ~SdfParser();

			bool parseDataStructure(sdf::ElementPtr sdfRoot);

	};

}}

#endif
