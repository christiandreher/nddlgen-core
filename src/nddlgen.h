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

#ifndef NDDLGEN_H_
#define NDDLGEN_H_

#include <nddlgen/controllers/WorkflowController.h>
#include <nddlgen/utilities/WorkflowControllerConfig.h>
#include <nddlgen/utilities/Meta.h>

/**
 * Root namespace of nddlgen. Also a convenient-namespace with short-hand typedefs to use the
 * rudimentary functionality of this library as known from other libraries. Internally, the
 * library is structured using nested namespaces which can also be used explicitly if needed.
 *
 * @author Christian Dreher
 */
namespace nddlgen
{

	/**
	 * Groups all controller, factories and parsers
	 */
	namespace controllers
	{

	}

	/**
	 * Groups all exceptions that may be thrown using nddlgen
	 */
	namespace exceptions
	{

	}

	/**
	 * Groups all models used by nddlgen
	 */
	namespace models
	{

	}

	/**
	 * Groups utilities like meta information, include-all-headers, macros and types
	 */
	namespace utilities
	{

	}

	/**
	 * @see nddlgen::utilities::Meta::NDDLGEN_VERSION
	 */
	static const std::string VERSION = nddlgen::utilities::Meta::NDDLGEN_VERSION;

	/**
	 * @see nddlgen::controller::WorkflowController
	 */
	typedef nddlgen::controllers::WorkflowController Controller;

	/**
	 * @see nddlgen::controller::WorkflowControllerPtr
	 */
	typedef nddlgen::controllers::WorkflowControllerPtr ControllerPtr;

	/**
	 * @see nddlgen::controller::WorkflowControllerConfig
	 */
	typedef nddlgen::utilities::WorkflowControllerConfig ControllerConfig;

	/**
	 * @see nddlgen::controller::WorkflowControllerConfigPtr
	 */
	typedef nddlgen::utilities::WorkflowControllerConfigPtr ControllerConfigPtr;

}

#endif
