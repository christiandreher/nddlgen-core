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

#ifndef NDDLGEN_CONTROLLER_NDDLGENERATABLEFACTORY_H_
#define NDDLGEN_CONTROLLER_NDDLGENERATABLEFACTORY_H_

#include <map>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>

#include <nddlgen/models/NddlGeneratable.h>

namespace nddlgen
{
	namespace controllers
	{
		class NddlGeneratableFactory;
		typedef boost::shared_ptr<nddlgen::controllers::NddlGeneratableFactory> NddlGeneratableFactoryPtr;
	}
}

typedef nddlgen::models::NddlGeneratablePtr (*CreateNddlGeneratable)(void);
typedef std::map<std::string, CreateNddlGeneratable> NddlGeneratableMap;

class nddlgen::controllers::NddlGeneratableFactory
{

	protected:

		NddlGeneratableMap _registeredNddlGeneratables;
		void registerNddlGeneratable(std::string modelName, CreateNddlGeneratable createFunction);

	public:

		NddlGeneratableFactory();
		virtual ~NddlGeneratableFactory();

		nddlgen::models::NddlGeneratablePtr fromString(std::string modelName);
		virtual void registerNddlGeneratables() = 0;

};

#endif
