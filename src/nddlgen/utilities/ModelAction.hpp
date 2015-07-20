/**
 * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)
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

#ifndef NDDLGEN_UTILITIES_MODELACTION_HPP_
#define NDDLGEN_UTILITIES_MODELACTION_HPP_

#include <list>

namespace nddlgen { namespace utilities
{

	class ModelAction
	{

		private:

			std::string _name;
			std::string _duration;
			std::string _metByCondition;
			std::string _containedByCondition;
			std::string _meetsEffect;

		public:

			ModelAction()
			{

			}

			~ModelAction()
			{

			}

			void setName(std::string name)
			{
				this->_name = name;
			}

			std::string getName()
			{
				return this->_name;
			}

			void setDuration(std::string duration)
			{
				this->_duration = duration;
			}

			std::string getDuration()
			{
				return this->_duration;
			}

			void setMetByCondition(std::string modelName, std::string predicate)
			{
				this->_metByCondition = modelName + "." + predicate;
			}

			std::string getMetByCondition(std::string workspaceNamePref)
			{
				return "met_by(condition object." + workspaceNamePref + "." + this->_metByCondition + ");";
			}

			void setContainedByCondition(std::string modelName, std::string predicate)
			{
				this->_containedByCondition = modelName + "." + predicate;
			}

			std::string getContainedByCondition(std::string workspaceNamePref)
			{
				return "contained_by(condition object." + workspaceNamePref + "." + this->_containedByCondition + ");";
			}

			void setMeetsEffect(std::string modelName, std::string predicate)
			{
				this->_meetsEffect = modelName + "." + predicate;
			}

			std::string getMeetsEffect(std::string workspaceNamePref)
			{
				return "meets(effect object." + workspaceNamePref + "." + this->_meetsEffect + ");";
			}

			std::string getActionDefinition()
			{
				return "action " + this->getName() + " { duration=" + this->getDuration() + "; }";
			}

			std::list<std::string> getActionSteps(std::string workspaceNamePref)
			{
				std::list<std::string> actionSteps;

				if (this->_metByCondition != "")
				{
					actionSteps.push_back(this->getMetByCondition(workspaceNamePref));
				}

				if (this->_containedByCondition != "")
				{
					actionSteps.push_back(this->getContainedByCondition(workspaceNamePref));
				}

				if (this->_meetsEffect != "")
				{
					actionSteps.push_back(this->getMeetsEffect(workspaceNamePref));
				}

				return actionSteps;
			}

	};

}}

#endif
