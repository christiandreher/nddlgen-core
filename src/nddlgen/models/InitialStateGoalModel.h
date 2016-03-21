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

#ifndef NDDLGEN_MODELS_INITIALSTATEGOALMODEL_H_
#define NDDLGEN_MODELS_INITIALSTATEGOALMODEL_H_

#include <string>
#include <list>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <nddlgen/exceptions/NoIndexSetException.hpp>

namespace nddlgen
{
	namespace models
	{
		class InitialStateGoalModel;
		typedef boost::shared_ptr<nddlgen::models::InitialStateGoalModel> InitialStateGoalModelPtr;
	}
}

class nddlgen::models::InitialStateGoalModel
{

	private:

		std::string _goalName;
		std::string _objectName;
		std::string _predicate;
		std::string _startsAfter;
		std::string _endsBefore;
		std::string _index;

	public:

		InitialStateGoalModel();
		virtual ~InitialStateGoalModel();

		void setGoalName(std::string goalName);
		void setObjectName(std::string objectName);
		void setPredicate(std::string predicate);
		void setStartsAfter(std::string startsAfter);
		void setEndsBefore(std::string endsBefore);
		void setIndex(int index);

		std::list<std::string> getGoal();

};

#endif
