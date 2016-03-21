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

#include <nddlgen/controllers/AbstractObjectFactory.h>

nddlgen::controllers::AbstractObjectFactory::AbstractObjectFactory()
{

}

nddlgen::controllers::AbstractObjectFactory::~AbstractObjectFactory()
{

}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::AbstractObjectFactory::fromString(std::string modelName)
{
	std::string modelNameLc = boost::algorithm::to_lower_copy(modelName);

	// Using reverse iterator, so that non-prefix-free keys are not matched wrong.
	for (NddlGeneratableMap::reverse_iterator i = this->_registeredNddlGeneratables.rbegin();
			i != this->_registeredNddlGeneratables.rend(); i++)
	{
		std::string classNameLc = boost::algorithm::to_lower_copy(i->first);

		if (modelNameLc == classNameLc || boost::algorithm::contains(modelNameLc, classNameLc))
		{
			return i->second();
		}
	}

	nddlgen::models::AbstractObjectModelPtr null(0);
	return null;
}

void nddlgen::controllers::AbstractObjectFactory::registerNddlGeneratable(
		std::string modelName,
		CreateNddlGeneratable createFunction)
{
	std::string modelNameLc = boost::algorithm::to_lower_copy(modelName);

	this->_registeredNddlGeneratables[modelNameLc] = createFunction;
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::AbstractObjectFactory::createDefaultArm()
{
	nddlgen::models::DefaultArmModelPtr model(new nddlgen::models::DefaultArmModel());
	return model;
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::AbstractObjectFactory::createDefaultWorkspace()
{
	nddlgen::models::DefaultWorkspaceModelPtr model(new nddlgen::models::DefaultWorkspaceModel());
	return model;
}
