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

#ifndef NDDLGEN_MODELS_WORKSPACEMODEL_H_
#define NDDLGEN_MODELS_WORKSPACEMODEL_H_

#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/Foreach.hpp>

namespace nddlgen
{
	namespace models
	{
		class WorkspaceModel;
		typedef boost::shared_ptr<nddlgen::models::WorkspaceModel> WorkspaceModelPtr;
	}
}

class nddlgen::models::WorkspaceModel : public nddlgen::models::NddlGeneratable
{

	private:

		void generateWorkspaceMembers(std::ofstream& ofStream);
		void generateWorkspaceConstructor(std::ofstream& ofStream);

	public:

		WorkspaceModel();
		virtual ~WorkspaceModel();

		void addModelToWorkspace(nddlgen::models::NddlGeneratablePtr model);
		nddlgen::models::NddlGeneratablePtr getModelByName(std::string name);

		nddlgen::types::NddlGeneratableList getModels();

};

#endif
