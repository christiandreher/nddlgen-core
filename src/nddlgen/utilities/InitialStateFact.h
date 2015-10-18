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

#ifndef NDDLGEN_UTILITIES_INITIALSTATEFACT_H_
#define NDDLGEN_UTILITIES_INITIALSTATEFACT_H_

#include <string>
#include <list>

namespace nddlgen { namespace utilities { class InitialStateFact; }}

class nddlgen::utilities::InitialStateFact
{

	private:

		std::string _modelName;
		std::string _predicate;
		int _index;

	public:

		InitialStateFact();
		virtual ~InitialStateFact();

		void setModelName(std::string modelName);
		void setPredicate(std::string predicate);
		void setIndex(int index);

		std::list<std::string> getFact();

};

#endif
