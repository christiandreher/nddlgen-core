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

#include <nddlgen/models/ActionModel.h>

nddlgen::models::ActionModel::ActionModel()
{

}

nddlgen::models::ActionModel::~ActionModel()
{

}

void nddlgen::models::ActionModel::setName(std::string name)
{
	this->_name = name;
}

void nddlgen::models::ActionModel::setDuration(std::string duration)
{
	this->_duration = duration;
}

std::string nddlgen::models::ActionModel::getName()
{
	return this->_name;
}

std::string nddlgen::models::ActionModel::getDuration()
{
	return this->_duration;
}

std::string nddlgen::models::ActionModel::getActionDefinition()
{
	return "action " + this->getName() + " { duration=" + this->getDuration() + "; }";
}

std::list<std::string> nddlgen::models::ActionModel::getActionSteps()
{
	return this->_actionSteps;
}

void nddlgen::models::ActionModel::addGenericConditionOrEffect(std::string relationName, std::string conditionOrEffect,
		std::string modelName, std::string predicate, std::string tokenName)
{
	if (tokenName != "")
	{
		tokenName = " " + tokenName;
	}

	std::string line = relationName + " (" + conditionOrEffect + " " + modelName + "." + predicate + tokenName + ");";

	this->_actionSteps.push_back(line);
}

void nddlgen::models::ActionModel::addBeforeCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("before", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addAfterCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("after", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addMeetsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("meets", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addMetByCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("met_by", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEqualCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("equal", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEqualsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("equals", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addContainsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addContainedByCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contained_by", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addParalleledByCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("paralleled_by", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addParallelsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("parallels", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsAfterCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_after", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsBeforeCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_before", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsAfterStartCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_after_start", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsBeforeEndCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_before_end", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsDuringCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_during", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addContainsStartCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains_start", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsDuringCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_during", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addContainsEndCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains_end", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsAfterCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_after", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsBeforeCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_before", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addAnyCondition(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("any", "condition", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addBeforeEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("before", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addAfterEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("after", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addMeetsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("meets", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addMetByEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("met_by", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEqualEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("equal", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEqualsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("equals", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addContainsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addContainedByEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contained_by", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addParalleledByEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("paralleled_by", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addParallelsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("parallels", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsAfterEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_after", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsBeforeEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_before", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsAfterStartEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_after_start", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsBeforeEndEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_before_end", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsDuringEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_during", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addContainsStartEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains_start", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addEndsDuringEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("ends_during", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addContainsEndEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("contains_end", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsAfterEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_after", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addStartsBeforeEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("starts_before", "effect", modelName, predicate, tokenName);
}

void nddlgen::models::ActionModel::addAnyEffect(std::string modelName, std::string predicate, std::string tokenName)
{
	this->addGenericConditionOrEffect("any", "effect", modelName, predicate, tokenName);
}
