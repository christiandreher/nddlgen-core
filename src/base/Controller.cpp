/*
 * Controller.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: chris
 */

#include <string>
#include <sys/stat.h>
#include "Controller.h"
#include <boost/filesystem.hpp>

using namespace std;

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

	Controller::Controller(string* errorText)
	{
		this->errorText = errorText;
		this->isFileIdentifierSet = false;
		this->isFileChecked = false;
		this->isFileParsed = false;
		this->isNddlGenerated = false;
	}

	Controller::~Controller()
	{
		// TODO Auto-generated destructor stub
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
		// Check if file has already been checked
		if (this->isFileChecked)
		{
			*this->errorText = Controller::ERR_FILE_ALREADY_CHECKED;
			return false;
		}

		// Check if file identifier was set
		if (!this->isFileIdentifierSet)
		{
			*this->errorText = Controller::ERR_SET_FILE_ID_FIRST;
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

		this->isFileChecked = true;
		return true;
	}

	bool Controller::parseFile()
	{
		// Check if file has already been parsed
		if (this->isFileParsed)
		{
			*this->errorText = Controller::ERR_FILE_ALREADY_PARSED;
			return false;
		}

		// Check if file identifier was set
		if (!this->isFileIdentifierSet)
		{
			*this->errorText = Controller::ERR_SET_FILE_ID_FIRST;
			return false;
		}

		// Check if file was checked
		if (!this->isFileChecked)
		{
			*this->errorText = Controller::ERR_CHECK_FILE_FIRST;
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

		// Check if file identifier was set
		if (!this->isFileIdentifierSet)
		{
			*this->errorText = Controller::ERR_SET_FILE_ID_FIRST;
			return false;
		}

		// Check if file was checked
		if (!this->isFileChecked)
		{
			*this->errorText = Controller::ERR_CHECK_FILE_FIRST;
			return false;
		}

		// Check if file was parsed
		if (!this->isFileParsed)
		{
			*this->errorText = Controller::ERR_PARSE_FILE_FIRST;
			return false;
		}

		this->isNddlGenerated = true;
		return true;
	}

}
