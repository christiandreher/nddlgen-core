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

#include <sys/stat.h>
#include <boost/filesystem.hpp>

#include "Controller.h"

using namespace std;
using namespace sdf;

namespace base
{

	const string Controller::ERR_FILE_ID_ALREADY_SET =
			"A file identifier has already been set. Create a new instance if necessary.";
	const string Controller::ERR_FILE_ALREADY_CHECKED =
			"The file has already been checked.";
	const string Controller::ERR_FILE_ALREADY_PARSED =
			"The file has already been parsed.";
	const string Controller::ERR_NDDL_ALREADY_GENERATED =
			"The NDDL-file has already been generated.";
	const string Controller::ERR_SET_FILE_ID_FIRST =
			"No file identifier has been set. Set one by calling Controller::setFileIdentifier(fileIdentifier).";
	const string Controller::ERR_CHECK_FILE_FIRST =
			"The file was not checked. Check it by calling Controller::checkFile().";
	const string Controller::ERR_PARSE_FILE_FIRST =
			"The file was not parsed. Parse it by calling Controller::parseFile().";
	const string Controller::ERR_FILE_MUST_BE_SDF =
			"File must be an .sdf file.";
	const string Controller::ERR_FILE_NOT_EXISTING =
			"File does not exist.";
	const string Controller::ERR_INITIALIZING_SDF =
			"Unable to initialize .sdf file.";
	const string Controller::ERR_READING_SDF_FILE =
			"Unable to read .sdf file.";


	Controller::Controller(string* errorText)
	{
		this->cerrStdRdBuf = cerr.rdbuf();

		this->errorText = errorText;

		this->isFileIdentifierSet = false;
		this->isFileChecked = false;
		this->isFileParsed = false;
		this->isNddlGenerated = false;
	}

	Controller::Controller(string fileIdentifier, string* errorText)
	{
		this->cerrStdRdBuf = cerr.rdbuf();

		this->fileIdentifier = fileIdentifier;

		this->errorText = errorText;

		this->isFileIdentifierSet = true;
		this->isFileChecked = false;
		this->isFileParsed = false;
		this->isNddlGenerated = false;
	}

	Controller::~Controller()
	{

	}


	bool Controller::setFileIdentifier(string fileIdentifier)
	{
		// Check if file identifier has already been set
		if (this->isFileIdentifierSet)
		{
			*this->errorText = Controller::ERR_FILE_ID_ALREADY_SET;
			return false;
		}

		this->fileIdentifier = fileIdentifier;
		this->isFileIdentifierSet = true;

		return true;
	}

	string Controller::getOutputFileName()
	{
		string fileStem = boost::filesystem::path(this->fileIdentifier).stem().string();
		return fileStem + ".nddl";
	}

	bool Controller::checkFile()
	{
		SDFPtr sdf(new SDF);

		// Check if file has already been checked
		if (this->isFileChecked)
		{
			*this->errorText = Controller::ERR_FILE_ALREADY_CHECKED;
			return false;
		}

		// Check if file is checkable
		if (!this->isCheckable())
		{
			return false;
		}

		// Check if file is a .sdf file
		if (boost::filesystem::path(this->fileIdentifier).extension().string() != ".sdf")
		{
			*this->errorText = Controller::ERR_FILE_MUST_BE_SDF;
			return false;
		}

		// Check if file exists
		if (!boost::filesystem::exists(this->fileIdentifier))
		{
			*this->errorText = Controller::ERR_FILE_NOT_EXISTING;
			return false;
		}

		this->disableCerr();

		// Init .sdf based on installed sdf_format.xml file
		if (!sdf::init(sdf))
		{
			this->enableCerr();
			*this->errorText = Controller::ERR_INITIALIZING_SDF + "\n" + this->getBufferedCerrOutput();
			return false;
		}

		// Try to read the file
		if (!sdf::readFile(this->fileIdentifier, sdf))
		{
			this->enableCerr();
			*this->errorText = Controller::ERR_READING_SDF_FILE + "\n" + this->getBufferedCerrOutput();
			return false;
		}

		this->sdfRoot = sdf->root;

		this->enableCerr();

		this->isFileChecked = true;
		return true;
	}

	bool Controller::parseSdf()
	{
		// Check if file has already been parsed
		if (this->isFileParsed)
		{
			*this->errorText = Controller::ERR_FILE_ALREADY_PARSED;
			return false;
		}

		// Check if file is parsable
		if (!this->isParsable())
		{
			return false;
		}

		this->isFileParsed = true;
		return true;
	}

	bool Controller::generateNddl()
	{
		// Check if nddl has already been generated
		if (this->isNddlGenerated)
		{
			*this->errorText = Controller::ERR_NDDL_ALREADY_GENERATED;
			return false;
		}

		// Check if files are generatable
		if (!this->isGeneratable())
		{
			return false;
		}

		this->isNddlGenerated = true;
		return true;
	}


	bool Controller::isCheckable()
	{
		// Check if file identifier was set
		if (!this->isFileIdentifierSet)
		{
			*this->errorText = Controller::ERR_SET_FILE_ID_FIRST;
			return false;
		}

		return true;
	}

	bool Controller::isParsable()
	{
		// Check if file is checkable
		if (!this->isCheckable())
		{
			return false;
		}

		// Check if file was checked
		if (!this->isFileChecked)
		{
			*this->errorText = Controller::ERR_CHECK_FILE_FIRST;
			return false;
		}

		return true;
	}

	bool Controller::isGeneratable()
	{
		// Check if file is parsable
		if (!this->isParsable())
		{
			return false;
		}

		// Check if file was parsed
		if (!this->isFileParsed)
		{
			*this->errorText = Controller::ERR_PARSE_FILE_FIRST;
			return false;
		}

		return true;
	}


	void Controller::disableCerr()
	{
		std::cerr.rdbuf(this->cerrOvRdBuf.rdbuf());
	}

	void Controller::enableCerr()
	{
		std::cerr.rdbuf(this->cerrStdRdBuf);
	}

	string Controller::getBufferedCerrOutput()
	{
		return this->cerrOvRdBuf.str();
	}

}
