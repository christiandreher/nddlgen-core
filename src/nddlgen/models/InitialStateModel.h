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

#ifndef NDDLGEN_MODELS_INITIALSTATEMODEL_H_
#define NDDLGEN_MODELS_INITIALSTATEMODEL_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include <nddlgen/utilities/InitialStateFact.h>
#include <nddlgen/utilities/InitialStateGoal.h>
#include <nddlgen/utilities/Types.hpp>

namespace nddlgen
{
	namespace models
	{
		class InitialStateModel;
		typedef boost::shared_ptr<nddlgen::models::InitialStateModel> InitialStateModelPtr;
	}
}

class nddlgen::models::InitialStateModel
{

	private:

		nddlgen::types::FactList _facts;
		nddlgen::types::GoalList _goals;

	public:

		InitialStateModel();
		virtual ~InitialStateModel();

		void addFact(nddlgen::utilities::InitialStateFactPtr fact);
		nddlgen::types::FactList getFacts();

		void addGoal(nddlgen::utilities::InitialStateGoalPtr goal);
		nddlgen::types::GoalList getGoals();

};

#endif
