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

#include <nddlgen/models/ProcessModel.h>

nddlgen::models::ProcessModel::ProcessModel()
{
	this->setClassName("Process");

	this->_pendingPredicate = "pending";
	this->_processingPredicate = "processing";
	this->_donePredicate = "done";
}

nddlgen::models::ProcessModel::~ProcessModel()
{

}

void nddlgen::models::ProcessModel::initPredicates()
{
	this->addPredicate(this->_pendingPredicate);
	this->addPredicate(this->_processingPredicate);
	this->addPredicate(this->_donePredicate);

	this->setInitialPredicate(this->_pendingPredicate);
}

std::string nddlgen::models::ProcessModel::getPendingPredicate()
{
	return this->_pendingPredicate;
}

std::string nddlgen::models::ProcessModel::getProcessingPredicate()
{
	return this->_processingPredicate;
}

std::string nddlgen::models::ProcessModel::getDonePredicate()
{
	return this->_donePredicate;
}
