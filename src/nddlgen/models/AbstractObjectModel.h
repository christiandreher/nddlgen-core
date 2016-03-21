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

#ifndef NDDLGEN_MODELS_ABSTRACTOBJECTMODEL_H_
#define NDDLGEN_MODELS_ABSTRACTOBJECTMODEL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <nddlgen/math/Cuboid.h>
#include <nddlgen/models/ActionModel.h>
#include <nddlgen/models/InitialStateFactModel.h>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/WriteStream.hpp>
#include <nddlgen/utilities/Foreach.hpp>

namespace nddlgen
{
	namespace models
	{
		class AbstractObjectModel;
		typedef boost::shared_ptr<nddlgen::models::AbstractObjectModel> AbstractObjectModelPtr;
	}
}

class nddlgen::models::AbstractObjectModel : public boost::enable_shared_from_this<nddlgen::models::AbstractObjectModel>
{

	protected:

		std::string _name;

		std::string _className;

		nddlgen::types::ObjectModelList _blockingObjects;

		std::list<std::string> _predicates;

		std::string _initialPredicate;

		nddlgen::types::ActionList _actions;

		nddlgen::math::CuboidPtr _objectBoundingBox;

		nddlgen::math::CuboidPtr _accessibilityBoundingBox;

		nddlgen::types::ObjectModelList _subObjects;

		boost::weak_ptr<nddlgen::models::AbstractObjectModel> _superObject;

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

		AbstractObjectModel();

		virtual ~AbstractObjectModel();

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
				nddlgen::models::AbstractObjectModelPtr blockingObject
		);

		bool hasBlockingObjects();

		void addPredicate(
				std::string predicate
		);

		bool hasPredicates();

		void setInitialPredicate(
				std::string initialPredicate
		);

		std::string getInitialPredicate();

		nddlgen::models::InitialStateFactModelPtr getInitialState();

		void addAction(
				nddlgen::models::ActionModelPtr action
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
				nddlgen::models::AbstractObjectModelPtr subObject
		);

		nddlgen::types::ObjectModelList getSubObjects();

		nddlgen::models::AbstractObjectModelPtr getSubObjectByName(
				std::string name,
				bool findInTree = false
		);

		void setInstanceNameFor(
				int index,
				std::string instanceName
		);

		bool hasSuperObject();

		void setSuperObject(
				nddlgen::models::AbstractObjectModelPtr superObject
		);

};

#endif
