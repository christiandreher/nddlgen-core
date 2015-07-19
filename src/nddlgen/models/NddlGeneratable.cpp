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

#include <nddlgen/models/NddlGeneratable.h>

namespace nddlgen { namespace models
{

	NddlGeneratable::NddlGeneratable()
	{

	}

	NddlGeneratable::~NddlGeneratable()
	{

	}

	void NddlGeneratable::setName(std::string name)
	{
		this->_name = name;
	}

	std::string NddlGeneratable::getName()
	{
		return this->_name;
	}

	std::string NddlGeneratable::getNamePref()
	{
		return "_" + this->getName();
	}

	std::string NddlGeneratable::getNamePrefSuff()
	{
		return this->getNamePref() + "_param";
	}

	void NddlGeneratable::setClassName(std::string className)
	{
		this->_className = className;
	}

	std::string NddlGeneratable::getClassName()
	{
		return this->_className;
	}

}}


