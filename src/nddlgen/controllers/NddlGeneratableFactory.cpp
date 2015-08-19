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

#include <nddlgen/controllers/NddlGeneratableFactory.h>

nddlgen::controllers::NddlGeneratableFactory::NddlGeneratableFactory()
{

}

nddlgen::controllers::NddlGeneratableFactory::~NddlGeneratableFactory()
{

}

nddlgen::models::NddlGeneratable* nddlgen::controllers::NddlGeneratableFactory::fromString(std::string modelName)
{
	std::string modelNameLc = boost::algorithm::to_lower_copy(modelName);
	NddlGeneratableMap::reverse_iterator i;

	// Using reverse iterator, so that non-prefix-free keys are not matched wrong.
	for (i = this->_registeredNddlGeneratables.rbegin(); i != this->_registeredNddlGeneratables.rend(); i++)
	{
		if (boost::algorithm::contains(modelName, i->first))
		{
			return i->second();
		}
	}

	return nullptr;
}

void nddlgen::controllers::NddlGeneratableFactory::registerNddlGeneratable(
		std::string modelName,
		CreateNddlGeneratable createFunction)
{
	std::string modelNameLc = boost::algorithm::to_lower_copy(modelName);

	this->_registeredNddlGeneratables[modelNameLc] = createFunction;
}
