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

#ifndef CORE_NDDLGENERATOR_H_
#define CORE_NDDLGENERATOR_H_

#include <iostream>
#include <fstream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <nddlgen/models/Arm.h>
#include <nddlgen/utilities/ControllerConfig.h>
#include <nddlgen/utilities/Meta.h>

namespace nddlgen { namespace core
{

	class NddlGenerator
	{

		private:

			nddlgen::utilities::ControllerConfig* _controllerConfig;

			nddlgen::models::Arm* _armModel;

			std::string getPrettifiedDate();

		public:

			NddlGenerator(nddlgen::models::Arm* armModel, nddlgen::utilities::ControllerConfig* controllerConfig);
			virtual ~NddlGenerator();

			bool generateModels(std::string fileName);
			bool generateInitialState(std::string fileName);

	};

}}

#endif
