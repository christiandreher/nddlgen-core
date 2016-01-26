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
#include <nddlgen/models/ArmModel.h>
#include <nddlgen/models/WorkspaceModel.h>
#include <nddlgen/models/DomainDescriptionModel.h>

namespace nddlgen
{
	namespace controllers
	{
		class NddlGeneratableFactory;
		typedef boost::shared_ptr<nddlgen::controllers::NddlGeneratableFactory> NddlGeneratableFactoryPtr;
	}
}

/**
 * Typedefs for function pointer and function pointer map
 */
typedef nddlgen::models::NddlGeneratablePtr (*CreateNddlGeneratable)(void);
typedef std::map<std::string, CreateNddlGeneratable> NddlGeneratableMap;

/**
 * Abstract factory class to instantiate NddlGeneratables. This enables programs which
 * use the nddlgen framework to register their own models according to their field of application.
 *
 * @author Christian Dreher
 */
class nddlgen::controllers::NddlGeneratableFactory
{

	protected:

		/**
		 * Map containing all registered NddlGeneratables.
		 */
		NddlGeneratableMap _registeredNddlGeneratables;

		/**
		 * Helper function to register a new NddlGeneratable.
		 *
		 * @param modelName Name of the Model (CLass name)
		 * @param createFunction Create function
		 */
		void registerNddlGeneratable(std::string modelName, CreateNddlGeneratable createFunction);

	public:

		/**
		 * Constructs a new NddlGeneratableFactory.
		 */
		NddlGeneratableFactory();

		/**
		 * Destructor to free memory.
		 */
		virtual ~NddlGeneratableFactory();

		/**
		 * Just after the Domain tree was built, but before all methods and classes are gathered,
		 * this function will be called. This enables framework users to configurate the domain
		 * if the other functionality is not enough.
		 *
		 * @param domain (Not fully qualified) domain description model
		 */
		virtual void configurateDomain(nddlgen::models::DomainDescriptionModelPtr domain);

		/**
		 * Generate an NddlGeneratable from modelName. This method will match all registered
		 * classes to the given modelName parameter. If either the lower case modelName is equal
		 * to the lower case class name or the lower case modelName is contained in the lower
		 * case class name, an instance of this class will be returned.
		 *
		 * @param modelName Name of the model
		 *
		 * @return NddlGeneratable object
		 */
		nddlgen::models::NddlGeneratablePtr fromString(std::string modelName);

		/**
		 * Pure virtual function which has to be overridden. Inside this function, all possible
		 * objects (NddlGeneratables) should be registered (using registerNddlGeneratable(...)).
		 * This function is the initialization of the factory. The factory instance is later used
		 * by the framework so that it can instantiate objects, which it is not fully aware of.
		 */
		virtual void registerNddlGeneratables() = 0;

		/**
		 * Creates the default Arm NddlGeneratable model
		 *
		 * @return ArmModel instance
		 */
		static nddlgen::models::NddlGeneratablePtr createArm();

		/**
		 * Creates the default Workspace NddlGeneratable model
		 *
		 * @return WorkspaceModel instance
		 */
		static nddlgen::models::NddlGeneratablePtr createWorkspace();

};

#endif
