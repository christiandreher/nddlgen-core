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

#include <nddlgen/utilities/WorkflowControllerConfig.h>

nddlgen::utilities::WorkflowControllerConfig::WorkflowControllerConfig()
{
	this->_adapter = "an custom, unnamed adapter";

	this->_sdfInputFile = "";
	this->_isdInputFile = "";
	this->_outputFilesPath = "";

	this->_readOnly = false;
}

nddlgen::utilities::WorkflowControllerConfig::~WorkflowControllerConfig()
{

}


void nddlgen::utilities::WorkflowControllerConfig::setAdapter(std::string adapter)
{
	this->trySet();

	this->_adapter = adapter;
}

void nddlgen::utilities::WorkflowControllerConfig::setSdfInputFile(std::string sdfInputFile)
{
	this->trySet();

	if (sdfInputFile != "")
	{
		this->_sdfInputFile = this->normalizePath(sdfInputFile);
	}
}

void nddlgen::utilities::WorkflowControllerConfig::setIsdInputFile(std::string isdInputFile)
{
	this->trySet();

	if (isdInputFile != "")
	{
		this->_isdInputFile = this->normalizePath(isdInputFile);
	}
}

void nddlgen::utilities::WorkflowControllerConfig::setOutputFilesPath(std::string outputFilesPath)
{
	this->trySet();

	if (outputFilesPath != "")
	{
		this->_outputFilesPath = this->normalizePath(outputFilesPath);
	}
}

void nddlgen::utilities::WorkflowControllerConfig::setModelFactory(
		nddlgen::controllers::NddlGeneratableFactoryPtr modelFactory)
{
	this->trySet();

	this->_modelFactory = modelFactory;
	this->_modelFactory->registerNddlGeneratables();
}

void nddlgen::utilities::WorkflowControllerConfig::setReadOnly()
{
	this->_readOnly = true;
}


std::string nddlgen::utilities::WorkflowControllerConfig::getAdapter()
{
	return this->_adapter;
}

std::string nddlgen::utilities::WorkflowControllerConfig::getSdfInputFile()
{
	return this->_sdfInputFile;
}

std::string nddlgen::utilities::WorkflowControllerConfig::getSdfInputFileExt()
{
	return boost::filesystem::path(this->_sdfInputFile).extension().string();
}

std::string nddlgen::utilities::WorkflowControllerConfig::getSdfInputFileName()
{
	std::string fileName = boost::filesystem::path(this->_sdfInputFile).filename().string();
	return fileName;
}

std::string nddlgen::utilities::WorkflowControllerConfig::getSdfInputFilePath()
{
	std::string filePath = boost::filesystem::path(this->_sdfInputFile).parent_path().string();
	return filePath;
}

std::string nddlgen::utilities::WorkflowControllerConfig::getIsdInputFile()
{
	return this->_isdInputFile;
}

std::string nddlgen::utilities::WorkflowControllerConfig::getIsdInputFileExt()
{
	return boost::filesystem::path(this->_isdInputFile).extension().string();
}

std::string nddlgen::utilities::WorkflowControllerConfig::getIsdInputFileName()
{
	std::string fileName = boost::filesystem::path(this->_isdInputFile).filename().string();
	return fileName;
}

std::string nddlgen::utilities::WorkflowControllerConfig::getIsdInputFilePath()
{
	std::string filePath = boost::filesystem::path(this->_isdInputFile).parent_path().string();
	return filePath;
}

std::string nddlgen::utilities::WorkflowControllerConfig::getOutputFilesPath()
{
	// Standard output path is the path of the input file
	std::string outputFilesPath = this->getSdfInputFilePath();

	// If a custom output path was set, override local variable
	if (this->_outputFilesPath != "")
	{
		outputFilesPath = this->_outputFilesPath;
	}

	return outputFilesPath;
}

std::string nddlgen::utilities::WorkflowControllerConfig::getOutputModelFile()
{
	return this->getOutputFilesPath() + "/" + this->getOutputModelFileName();
}

std::string nddlgen::utilities::WorkflowControllerConfig::getOutputModelFileName()
{
	std::string fileStem = boost::filesystem::path(this->_sdfInputFile).stem().string();
	fileStem += "-model";

	return fileStem + ".nddl";
}

std::string nddlgen::utilities::WorkflowControllerConfig::getOutputInitialStateFile()
{
	return this->getOutputFilesPath() + "/" + this->getOutputInitialStateFileName();
}

std::string nddlgen::utilities::WorkflowControllerConfig::getOutputInitialStateFileName()
{
	std::string fileStem = boost::filesystem::path(this->_isdInputFile).stem().string();
	fileStem += "-initial-state";

	return fileStem + ".nddl";
}


bool nddlgen::utilities::WorkflowControllerConfig::isReadOnly()
{
	return this->_readOnly;
}


void nddlgen::utilities::WorkflowControllerConfig::trySet()
{
	if (this->_readOnly)
	{
		throw nddlgen::exceptions::ControllerConfigIsReadOnlyException();
	}
}

std::string nddlgen::utilities::WorkflowControllerConfig::normalizePath(const boost::filesystem::path &path)
{
	// Implementation of this function by jarzec (stackoverflow community member)

	boost::filesystem::path absPath = boost::filesystem::absolute(path);
	boost::filesystem::path::iterator it = absPath.begin();
	boost::filesystem::path result = *it++;

	// Get canonical version of the existing part
	for (; boost::filesystem::exists(result / *it)
			&& it != absPath.end(); ++it)
	{
		result /= *it;
	}

	result = boost::filesystem::canonical(result);

	// For the rest remove ".." and "." in a path with no symlinks
	for (; it != absPath.end(); ++it)
	{
		// Just move back on ../
		if (*it == "..")
		{
			result = result.parent_path();
		}
		// Ignore "."
		else if (*it != ".")
		{
			// Just cat other path entries
			result /= *it;
		}
	}

	return result.string();
}

nddlgen::controllers::NddlGeneratableFactoryPtr nddlgen::utilities::WorkflowControllerConfig::getModelFactory()
{
	return this->_modelFactory;
}
