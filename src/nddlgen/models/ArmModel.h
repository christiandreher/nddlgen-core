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

#ifndef NDDLGEN_MODELS_ARMMODEL_H_
#define NDDLGEN_MODELS_ARMMODEL_H_

#include <string>
#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/WorkspaceModel.h>

namespace nddlgen
{
	namespace models
	{
		class ArmModel;
		typedef boost::shared_ptr<ArmModel> ArmModelPtr;
	}
}

class nddlgen::models::ArmModel : public nddlgen::models::NddlGeneratable
{

	private:

		nddlgen::models::WorkspaceModelPtr _workspace;

	public:

		ArmModel();
		virtual ~ArmModel();

		virtual void generateModel(std::ofstream& ofStream);

		void setWorkspace(nddlgen::models::WorkspaceModelPtr workspace);
		nddlgen::models::WorkspaceModelPtr getWorkspace();

};

#endif
