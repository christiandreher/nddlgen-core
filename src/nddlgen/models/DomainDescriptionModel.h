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

#ifndef NDDLGEN_MODELS_DOMAINDESCRIPTIONMODEL_H_
#define NDDLGEN_MODELS_DOMAINDESCRIPTIONMODEL_H_

#include <cstddef>

#include <boost/shared_ptr.hpp>

#include <nddlgen/models/ArmModel.h>
#include <nddlgen/models/InitialStateModel.h>

namespace nddlgen
{
	namespace models
	{
		class DomainDescriptionModel;
		typedef boost::shared_ptr<nddlgen::models::DomainDescriptionModel> DomainDescriptionModelPtr;
	}
}

class nddlgen::models::DomainDescriptionModel
{

	private:

		nddlgen::models::ArmModelPtr _arm;
		nddlgen::models::InitialStateModelPtr _initialState;

	public:

		DomainDescriptionModel();
		virtual ~DomainDescriptionModel();

		void setArm(nddlgen::models::ArmModelPtr arm);
		nddlgen::models::ArmModelPtr getArm();

		void setInitialState(nddlgen::models::InitialStateModelPtr initialState);
		nddlgen::models::InitialStateModelPtr getInitialState();

};

#endif
