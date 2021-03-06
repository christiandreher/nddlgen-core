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

#ifndef NDDLGEN_MODELS_DEFAULTWORKSPACEMODEL_H_
#define NDDLGEN_MODELS_DEFAULTWORKSPACEMODEL_H_

#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>
#include <nddlgen/models/AbstractObjectModel.h>

#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/Foreach.hpp>

namespace nddlgen
{
	namespace models
	{
		class DefaultWorkspaceModel;
		typedef boost::shared_ptr<nddlgen::models::DefaultWorkspaceModel> DefaultWorkspaceModelPtr;
	}
}

class nddlgen::models::DefaultWorkspaceModel : public nddlgen::models::AbstractObjectModel
{

	private:

		void generateWorkspaceMembers(std::ofstream& ofStream);
		void generateWorkspaceConstructor(std::ofstream& ofStream);

	public:

		DefaultWorkspaceModel();
		virtual ~DefaultWorkspaceModel();

		void addObjectToWorkspace(nddlgen::models::AbstractObjectModelPtr model);
		nddlgen::models::AbstractObjectModelPtr getObjectByName(std::string name);

		nddlgen::types::ObjectModelList getObjects();

};

#endif
