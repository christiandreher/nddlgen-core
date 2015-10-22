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

#include <list>

#include <boost/shared_ptr.hpp>
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

	typedef std::list<boost::shared_ptr<nddlgen::models::NddlGeneratable>> NddlGeneratableList;

	typedef std::list<boost::shared_ptr<nddlgen::utilities::ModelAction>> ActionList;

	typedef std::list<boost::shared_ptr<nddlgen::utilities::InitialStateFact>> FactList;

	typedef std::list<boost::shared_ptr<nddlgen::utilities::InitialStateGoal>> GoalList;

	typedef boost::shared_ptr<sdf::SDF> SdfRoot;

	typedef boost::shared_ptr<TiXmlDocument> IsdRoot;

}}

#endif
