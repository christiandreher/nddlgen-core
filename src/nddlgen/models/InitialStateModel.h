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

#include <boost/ptr_container/ptr_list.hpp>

namespace nddlgen { namespace models { class InitialStateModel; }}

class nddlgen::models::InitialStateModel
{

	private:

		boost::ptr_list<nddlgen::utilities::InitialStateFact> _facts;
		boost::ptr_list<nddlgen::utilities::InitialStateGoal> _goals;

	public:

		InitialStateModel();
		virtual ~InitialStateModel();

		void addFact(nddlgen::utilities::InitialStateFact* fact);
		boost::ptr_list<nddlgen::utilities::InitialStateFact> getFacts();

		void addGoal(nddlgen::utilities::InitialStateGoal* goal);
		boost::ptr_list<nddlgen::utilities::InitialStateGoal> getGoals();

};

#endif
