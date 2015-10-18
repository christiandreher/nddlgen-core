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

#ifndef NDDLGEN_TYPES_TYPES_HPP_
#define NDDLGEN_TYPES_TYPES_HPP_

#include <boost/ptr_container/ptr_list.hpp>
#include <sdf/sdf.hh>
#include <tinyxml.h>

// Forward declaration
namespace nddlgen
{
	namespace models
	{
		class NddlGeneratable;
	}

	namespace utilities
	{
		class ModelAction;
		class InitialStateFact;
		class InitialStateGoal;
	}
}

namespace nddlgen { namespace types
{

	typedef boost::ptr_list<nddlgen::models::NddlGeneratable> NddlGeneratableList;

	typedef boost::ptr_list<nddlgen::utilities::ModelAction> ActionList;

	typedef boost::ptr_list<nddlgen::utilities::InitialStateFact> FactList;

	typedef boost::ptr_list<nddlgen::utilities::InitialStateGoal> GoalList;

	typedef sdf::ElementPtr SdfRoot;

	typedef std::string IsdRoot;

}}

#endif
