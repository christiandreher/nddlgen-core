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

#ifndef NDDLGEN_MODELS_NDDLGENERATABLE_H_
#define NDDLGEN_MODELS_NDDLGENERATABLE_H_

#include <iostream>
#include <fstream>
#include <string>

#include <boost/shared_ptr.hpp>

#include <nddlgen/math/Cuboid.h>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/WriteStream.hpp>
#include <nddlgen/utilities/Foreach.hpp>
#include <nddlgen/utilities/ModelAction.h>

namespace nddlgen
{
	namespace models
	{
		class NddlGeneratable;
		typedef boost::shared_ptr<nddlgen::models::NddlGeneratable> NddlGeneratablePtr;
	}
}

class nddlgen::models::NddlGeneratable
{

	protected:

		std::string _name;
		std::string _className;
		nddlgen::types::NddlGeneratableList _blockedBy;
		std::list<std::string> _predicates;
		nddlgen::types::ActionList _actions;
		nddlgen::math::CuboidPtr _objectBoundingBox;
		nddlgen::math::CuboidPtr _accessibilityBoundingBox;

	public:

		NddlGeneratable();
		virtual ~NddlGeneratable();

		virtual void postInitProcessing();

		virtual void generateModel(std::ofstream& ofStream);

		void setName(std::string name);
		std::string getName();
		std::string getNamePref();
		std::string getNamePrefSuff();

		void setClassName(std::string className);
		std::string getClassName();

		void addBlockingObject(nddlgen::models::NddlGeneratablePtr blockingObject);
		bool isBlocked();

		void addPredicate(std::string predicate);
		bool hasPredicates();

		void addAction(nddlgen::utilities::ModelActionPtr action);
		bool hasActions();
		virtual nddlgen::types::ActionList getActions();

		nddlgen::math::CuboidPtr getObjectBoundingBox();
		void setObjectBoundingBox(nddlgen::math::CuboidPtr objectBoundingBox);
		bool hasObjectBoundingBox();

		nddlgen::math::CuboidPtr getAccessibilityBoundingBox();
		void setAccessibilityBoundingBox(nddlgen::math::CuboidPtr accessibilityBoundingBox);
		bool hasAccessibilityBoundingBox();

};

#endif
