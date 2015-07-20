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

#ifndef NDDLGEN_MODELS_ARM_H_
#define NDDLGEN_MODELS_ARM_H_

#include <string>
#include <iostream>
#include <fstream>

#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/Workspace.h>
#include <nddlgen/utilities/ControllerMeta.hpp>

namespace nddlgen { namespace models
{

	class Arm : public nddlgen::models::NddlGeneratable
	{

		private:

			nddlgen::models::Workspace* _workspace;

			nddlgen::utilities::ControllerMeta* _controllerMeta;

		public:

			Arm();
			virtual ~Arm();

			virtual void generateModel(std::ofstream& ofStream);
			virtual void generateInitialState(std::ofstream& ofStream);

			void setWorkspace(nddlgen::models::Workspace* workspace);
			nddlgen::models::Workspace* getWorkspace();

			void setControllerMeta(nddlgen::utilities::ControllerMeta* controllerMeta);

	};

}}

#endif
