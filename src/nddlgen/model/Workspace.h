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

#ifndef NDDLGEN_MODEL_WORKSPACE_H_
#define NDDLGEN_MODEL_WORKSPACE_H_

#include <boost/ptr_container/ptr_list.hpp>

#include "nddlgen/model/NddlGeneratable.h"

namespace nddlgen { namespace model
{

	class Workspace : public nddlgen::model::NddlGeneratable
	{

		private:

			boost::ptr_list<NddlGeneratable> _objects;

		public:

			Workspace();
			virtual ~Workspace();

			virtual std::string generateDomainAsString();
			virtual std::string generateInitialStateAsString();

			void addToWorkspace(NddlGeneratable* object);

	};

}}

#endif
