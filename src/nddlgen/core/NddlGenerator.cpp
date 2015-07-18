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

#include "nddlgen/core/NddlGenerator.h"

namespace nddlgen { namespace core
{

	NddlGenerator::NddlGenerator(nddlgen::models::Arm* armModel)
	{
		this->_armModel = armModel;
	}

	NddlGenerator::~NddlGenerator()
	{
		// TODO Auto-generated destructor stub
	}


	bool NddlGenerator::generateModels(std::string fileName)
	{
		std::ofstream ofStream(fileName);

		this->_armModel->generateModelAsString(ofStream);

		ofStream.close();

		return true;
	}

	bool NddlGenerator::generateInitialState(std::string fileName)
	{
		//this->_initialState = this->_armModel->generateInitialStateAsString();

		return true;
	}

}}
