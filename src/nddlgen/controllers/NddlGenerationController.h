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

#ifndef NDDLGEN_CONTROLLER_NDDLGENERATIONCONTROLLER_H_
#define NDDLGEN_CONTROLLER_NDDLGENERATIONCONTROLLER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>

#include <nddlgen/exceptions/FileAlreadyExistsException.hpp>
#include <nddlgen/models/DomainDescriptionModel.h>
#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/ProcessModel.h>
#include <nddlgen/utilities/Foreach.hpp>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/Meta.h>
#include <nddlgen/utilities/WorkflowControllerConfig.h>

namespace nddlgen
{
	namespace controllers
	{
		class NddlGenerationController;
		typedef boost::shared_ptr<nddlgen::controllers::NddlGenerationController> NddlGenerationControllerPtr;
	}
}

class nddlgen::controllers::NddlGenerationController
{

	private:

		NddlGenerationController();
		virtual ~NddlGenerationController();

		static void generateModelBoilerplate(std::ofstream& ofStream, nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig);
		static void generateInitialStateBoilerplate(std::ofstream& ofStream, nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig);
		static void generateBoilerplate(std::ofstream& ofStream, nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig, std::string modelOrInitialState);

		static std::string getPrettifiedDate();

	public:

		static void writeModelFile(nddlgen::models::DomainDescriptionModelPtr domainDescription,
				nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig,
				bool forceOverwrite);
		static void writeInitialStateFile(nddlgen::models::DomainDescriptionModelPtr domainDescription,
				nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig,
				bool forceOverwrite);

};

#endif
