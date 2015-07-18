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

#include <nddlgen/models/Arm.h>

namespace nddlgen { namespace models
{

	Arm::Arm()
	{
		this->_workspace = nullptr;
	}

	Arm::~Arm()
	{
		delete this->_workspace;
	}


	void Arm::generateModelAsString(std::ofstream& ofStream)
	{
		this->_workspace->generateModelAsString(ofStream);

		ofStream << std::endl;

		ofStream << "class Arm" << std::endl;
		ofStream << "{" << std::endl;

		ofStream << "}" << std::endl;
	}

	void Arm::generateInitialStateAsString(std::ofstream& ofStream)
	{
		//ofStream << this->_workspace->generateInitialStateAsString(ofStream);
	}


	void Arm::setWorkspace(nddlgen::models::Workspace* workspace)
	{
		this->_workspace = workspace;
	}

	nddlgen::models::Workspace* Arm::getWorkspace()
	{
		return this->_workspace;
	}

}}