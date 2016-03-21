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
#include <nddlgen/models/AbstractObjectModel.h>

#include <nddlgen/models/DefaultArmModel.h>
#include <nddlgen/models/DefaultWorkspaceModel.h>

namespace nddlgen
{
	namespace controllers
	{
		class AbstractObjectFactory;
		typedef boost::shared_ptr<nddlgen::controllers::AbstractObjectFactory> AbstractObjectFactoryPtr;
	}
}

/**
 * Typedefs for function pointer and function pointer map
 */
typedef nddlgen::models::AbstractObjectModelPtr (*CreateObject)(void);
typedef std::map<std::string, CreateObject> ObjectModelMap;

/**
 * Abstract factory class to instantiate NddlGeneratables. This enables programs which
 * use the nddlgen framework to register their own models according to their field of application.
 *
 * @author Christian Dreher
 */
class nddlgen::controllers::AbstractObjectFactory
{

	protected:

		/**
		 * Map containing all registered NddlGeneratables.
		 */
		ObjectModelMap _registeredObjectModels;

		/**
		 * Helper function to register a new NddlGeneratable.
		 *
		 * @param modelName Name of the Model (CLass name)
		 * @param createFunction Create function
		 */
		void registerObjectModel(std::string modelName, CreateObject createFunction);

	public:

		/**
		 * Constructs a new NddlGeneratableFactory.
		 */
		AbstractObjectFactory();

		/**
		 * Destructor to free memory.
		 */
		virtual ~AbstractObjectFactory();

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
		nddlgen::models::AbstractObjectModelPtr fromString(std::string modelName);

		/**
		 * Pure virtual function which has to be overridden. Inside this function, all possible
		 * objects (NddlGeneratables) should be registered (using registerNddlGeneratable(...)).
		 * This function is the initialization of the factory. The factory instance is later used
		 * by the framework so that it can instantiate objects, which it is not fully aware of.
		 */
		virtual void registerObjectModels() = 0;

		/**
		 * Creates the default Arm NddlGeneratable model
		 *
		 * @return ArmModel instance
		 */
		static nddlgen::models::AbstractObjectModelPtr createDefaultArm();

		/**
		 * Creates the default Workspace NddlGeneratable model
		 *
		 * @return WorkspaceModel instance
		 */
		static nddlgen::models::AbstractObjectModelPtr createDefaultWorkspace();

};

#endif
