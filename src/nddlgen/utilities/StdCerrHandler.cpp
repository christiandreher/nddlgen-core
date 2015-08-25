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

#include <nddlgen/utilities/StdCerrHandler.h>

std::stringstream nddlgen::utilities::StdCerrHandler::_cerrOvRdBuf;

std::streambuf* nddlgen::utilities::StdCerrHandler::_cerrStdRdBuf = std::cerr.rdbuf();

nddlgen::utilities::StdCerrHandler::StdCerrHandler()
{

}

nddlgen::utilities::StdCerrHandler::~StdCerrHandler()
{

}

void nddlgen::utilities::StdCerrHandler::disableCerr()
{

	// Disable std::cerr by setting custom read buffer
	std::cerr.rdbuf(nddlgen::utilities::StdCerrHandler::_cerrOvRdBuf.rdbuf());
}

void nddlgen::utilities::StdCerrHandler::enableCerr()
{
	// Re-enabling std::cerr by restoring initial value
	std::cerr.rdbuf(nddlgen::utilities::StdCerrHandler::_cerrStdRdBuf);
}

std::string nddlgen::utilities::StdCerrHandler::getBufferedCerrOutput()
{
	// Return contents of custom read buffer
	return nddlgen::utilities::StdCerrHandler::_cerrOvRdBuf.str();
}
