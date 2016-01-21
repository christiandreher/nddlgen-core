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

#include <nddlgen/utilities/ModelAction.h>

nddlgen::utilities::ModelAction::ModelAction()
{

}

nddlgen::utilities::ModelAction::~ModelAction()
{

}

void nddlgen::utilities::ModelAction::setName(std::string name)
{
	this->_name = name;
}

void nddlgen::utilities::ModelAction::setDuration(std::string duration)
{
	this->_duration = duration;
}

std::string nddlgen::utilities::ModelAction::getName()
{
	return this->_name;
}

std::string nddlgen::utilities::ModelAction::getDuration()
{
	return this->_duration;
}

std::string nddlgen::utilities::ModelAction::getActionDefinition()
{
	return "action " + this->getName() + " { duration=" + this->getDuration() + "; }";
}

std::list<std::string> nddlgen::utilities::ModelAction::getActionSteps(std::string workspaceNamePref)
{
	return this->_actionSteps;
}

void nddlgen::utilities::ModelAction::addGenericConditionOrEffect(std::string relationName, std::string conditionOrEffect,
		std::string modelName, std::string predicate, std::string tokenName)
{
	if (tokenName != "")
	{
		tokenName = " " + tokenName;
	}

	std::string line = relationName + " (" + conditionOrEffect + " " + modelName + "." + predicate + tokenName + ");";

	this->_actionSteps.push_back(line);
}

void nddlgen::utilities::ModelAction::addBeforeCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("before", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addAfterCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("after", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addMeetsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("meets", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addMetByCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("met_by", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEqualCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("equal", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEqualsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("equals", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addContainsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addContainedByCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contained_by", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addParalleledByCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("paralleled_by", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addParallelsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("parallels", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsAfterCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_after", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsBeforeCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_before", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsAfterStartCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_after_start", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsBeforeEndCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_before_end", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsDuringCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_during", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addContainsStartCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains_start", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsDuringCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_during", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addContainsEndCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains_end", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsAfterCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_after", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsBeforeCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_before", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addAnyCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("any", "condition", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addBeforeEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("before", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addAfterEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("after", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addMeetsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("meets", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addMetByEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("met_by", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEqualEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("equal", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEqualsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("equals", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addContainsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addContainedByEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contained_by", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addParalleledByEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("paralleled_by", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addParallelsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("parallels", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsAfterEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_after", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsBeforeEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_before", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsAfterStartEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_after_start", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsBeforeEndEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_before_end", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsDuringEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_during", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addContainsStartEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains_start", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addEndsDuringEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_during", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addContainsEndEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains_end", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsAfterEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_after", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addStartsBeforeEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_before", "effect", modelName, predicate, tokenName);
}

void nddlgen::utilities::ModelAction::addAnyEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("any", "effect", modelName, predicate, tokenName);
}
