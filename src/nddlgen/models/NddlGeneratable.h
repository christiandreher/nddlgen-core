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
#include <list>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <nddlgen/math/Cuboid.h>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/WriteStream.hpp>
#include <nddlgen/utilities/Foreach.hpp>
#include <nddlgen/utilities/ModelAction.h>
#include <nddlgen/utilities/InitialStateFact.h>

namespace nddlgen
{
	namespace models
	{
		class NddlGeneratable;
		typedef boost::shared_ptr<nddlgen::models::NddlGeneratable> NddlGeneratablePtr;
	}
}

class nddlgen::models::NddlGeneratable : public boost::enable_shared_from_this<nddlgen::models::NddlGeneratable>
{

	protected:

		std::string _name;

		std::string _className;

		nddlgen::types::NddlGeneratableList _blockedBy;

		std::list<std::string> _predicates;

		std::string _initialPredicate;

		nddlgen::types::ActionList _actions;

		nddlgen::math::CuboidPtr _objectBoundingBox;

		nddlgen::math::CuboidPtr _accessibilityBoundingBox;

		nddlgen::types::NddlGeneratableList _subObjects;

		boost::weak_ptr<nddlgen::models::NddlGeneratable> _superObject;

		void generateModelPredicates(
				std::ofstream& ofStream
		);

		void generateModelSubObjects(
				std::ofstream& ofStream
		);

		void generateModelConstructor(
				std::ofstream& ofStream
		);

	public:

		NddlGeneratable();

		virtual ~NddlGeneratable();

		virtual void initPredicates();

		virtual void initSubObjects();

		virtual void initActions();

		virtual void generateForwardDeclaration(
				std::ofstream& ofStream
		);

		virtual void generateModel(
				std::ofstream& ofStream
		);

		virtual void generateInstantiation(
				std::ofstream& ofStream
		);

		void setName(
				std::string name
		);

		std::string getName();

		std::string getNamePref();

		std::string getNamePrefSuff();

		virtual std::string getAccessor();

		void setClassName(
				std::string className
		);

		std::string getClassName();

		void addBlockingObject(
				nddlgen::models::NddlGeneratablePtr blockingObject
		);

		bool isBlocked();

		void addPredicate(
				std::string predicate
		);

		bool hasPredicates();

		void setInitialPredicate(
				std::string initialPredicate
		);

		std::string getInitialPredicate();

		nddlgen::utilities::InitialStateFactPtr getInitialState();

		void addAction(
				nddlgen::utilities::ModelActionPtr action
		);

		bool hasActions();

		nddlgen::types::ActionList getActions();

		nddlgen::math::CuboidPtr getObjectBoundingBox();

		void setObjectBoundingBox(
				nddlgen::math::CuboidPtr objectBoundingBox
		);

		bool hasObjectBoundingBox();

		nddlgen::math::CuboidPtr getAccessibilityBoundingBox();

		void setAccessibilityBoundingBox(
				nddlgen::math::CuboidPtr accessibilityBoundingBox
		);

		bool hasAccessibilityBoundingBox();

		bool hasSubObjects();

		void addSubObject(
				nddlgen::models::NddlGeneratablePtr subObject
		);

		nddlgen::types::NddlGeneratableList getSubObjects();

		nddlgen::models::NddlGeneratablePtr getSubObjectByName(
				std::string name,
				bool findInTree = false
		);

		void setInstanceNameFor(
				int index,
				std::string instanceName
		);

		bool hasSuperObject();

		void setSuperObject(
				nddlgen::models::NddlGeneratablePtr superObject
		);

};

#endif
