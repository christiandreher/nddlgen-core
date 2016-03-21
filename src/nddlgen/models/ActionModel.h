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
		std::list<std::string> _actionSteps;

		void addGenericConditionOrEffect(std::string relationName, std::string conditionOrEffect, std::string modelName, std::string predicate, std::string tokenName);

	public:

		ModelAction();
		~ModelAction();

		void setName(std::string name);
		void setDuration(std::string duration);

		void addBeforeCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addAfterCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addMeetsCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addMetByCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEqualCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEqualsCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addContainsCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addContainedByCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addParalleledByCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addParallelsCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsAfterCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsBeforeCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsAfterStartCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsBeforeEndCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsDuringCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addContainsStartCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsDuringCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addContainsEndCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsAfterCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsBeforeCondition(std::string modelName, std::string predicate, std::string tokenName = "");
		void addAnyCondition(std::string modelName, std::string predicate, std::string tokenName = "");

		void addBeforeEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addAfterEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addMeetsEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addMetByEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEqualEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEqualsEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addContainsEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addContainedByEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addParalleledByEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addParallelsEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsAfterEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsBeforeEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsAfterStartEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsBeforeEndEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsDuringEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addContainsStartEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addEndsDuringEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addContainsEndEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsAfterEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addStartsBeforeEffect(std::string modelName, std::string predicate, std::string tokenName = "");
		void addAnyEffect(std::string modelName, std::string predicate, std::string tokenName = "");

		void addCustomLineToActionSteps(std::string line);

		std::string getName();
		std::string getDuration();
		std::string getActionDefinition();
		std::list<std::string> getActionSteps();

};

#endif
