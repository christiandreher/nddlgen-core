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

#ifndef NDDLGEN_MODELS_WORKSPACE_H_
#define NDDLGEN_MODELS_WORKSPACE_H_

#include <iostream>
#include <fstream>

#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/Box.h>
#include <nddlgen/models/LidBox.h>
#include <nddlgen/models/ObjectSlide.h>
#include <nddlgen/models/ObjectSlideContainer.h>
#include <nddlgen/types/Types.hpp>
#include <nddlgen/utilities/Foreach.hpp>

namespace nddlgen { namespace models
{

	class Workspace : public nddlgen::models::NddlGeneratable
	{

		private:

			nddlgen::types::NddlGeneratableList _modelClasses;
			nddlgen::types::NddlGeneratableList _models;

			void generateWorkspaceMembers(std::ofstream& ofStream);
			void generateWorkspaceConstructor(std::ofstream& ofStream);

		public:

			Workspace();
			virtual ~Workspace();

			virtual void generateModel(std::ofstream& ofStream);
			virtual void generateInitialState(std::ofstream& ofStream);

			void addModelToWorkspace(nddlgen::models::NddlGeneratable* model);
			nddlgen::models::NddlGeneratable* getModelByName(std::string name);

	};

}}

#endif
