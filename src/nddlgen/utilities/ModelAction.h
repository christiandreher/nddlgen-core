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

#ifndef NDDLGEN_UTILITIES_MODELACTION_H_
#define NDDLGEN_UTILITIES_MODELACTION_H_

#include <list>
#include <string>

#include <boost/shared_ptr.hpp>

namespace nddlgen
{
	namespace utilities
	{
		class ModelAction;
		typedef boost::shared_ptr<nddlgen::utilities::ModelAction> ModelActionPtr;
	}
}

class nddlgen::utilities::ModelAction
{

	private:

		std::string _name;
		std::string _duration;
		std::string _metByCondition;
		std::string _containedByCondition;
		std::string _meetsEffect;

	public:

		ModelAction();
		~ModelAction();

		void setName(std::string name);
		void setDuration(std::string duration);
		void setMetByCondition(std::string modelName, std::string predicate);
		void setContainedByCondition(std::string modelName, std::string predicate);
		void setMeetsEffect(std::string modelName, std::string predicate);

		std::string getName();
		std::string getDuration();
		std::string getMetByCondition(std::string workspaceNamePref);
		std::string getContainedByCondition(std::string workspaceNamePref);
		std::string getMeetsEffect(std::string workspaceNamePref);
		std::string getActionDefinition();
		std::list<std::string> getActionSteps(std::string workspaceNamePref);

};

#endif
