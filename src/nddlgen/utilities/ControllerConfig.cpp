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

#include <nddlgen/utilities/ControllerConfig.h>

namespace nddlgen { namespace utilities
{

	ControllerConfig::ControllerConfig()
	{
		this->_adapter = "a custom adapter";

		this->_inputSdfFile = "";
		this->_inputIsdFile = "";
		this->_outputFilesPath = "";

		this->_readOnly = false;
	}

	ControllerConfig::~ControllerConfig()
	{

	}


	void ControllerConfig::setAdapter(std::string adapter)
	{
		this->trySet();

		this->_adapter = adapter;
	}

	void ControllerConfig::setInputSdfFile(std::string inputSdfFile)
	{
		this->trySet();

		if (inputSdfFile != "")
		{
			this->_inputSdfFile = this->normalizePath(inputSdfFile);
		}
	}

	void ControllerConfig::setInputIsdFile(std::string inputIsdFile)
	{
		this->trySet();

		if (inputIsdFile != "")
		{
			this->_inputIsdFile = this->normalizePath(inputIsdFile);
		}
	}

	void ControllerConfig::setOutputFilesPath(std::string outputFilesPath)
	{
		this->trySet();

		if (outputFilesPath != "")
		{
			this->_outputFilesPath = this->normalizePath(outputFilesPath);
		}
	}

	void ControllerConfig::setReadOnly()
	{
		this->_readOnly = true;
	}


	std::string ControllerConfig::getAdapter()
	{
		return this->_adapter;
	}

	std::string ControllerConfig::getInputSdfFile()
	{
		return this->_inputSdfFile;
	}

	std::string ControllerConfig::getInputSdfFileExt()
	{
		return boost::filesystem::path(this->_inputSdfFile).extension().string();
	}

	std::string ControllerConfig::getInputSdfFileName()
	{
		std::string fileName = boost::filesystem::path(this->_inputSdfFile).filename().string();
		return fileName;
	}

	std::string ControllerConfig::getInputSdfFilePath()
	{
		std::string filePath = boost::filesystem::path(this->_inputSdfFile).parent_path().string();
		return filePath;
	}

	std::string ControllerConfig::getInputIsdFile()
	{
		return this->_inputIsdFile;
	}

	std::string ControllerConfig::getInputIsdFileExt()
	{
		return boost::filesystem::path(this->_inputIsdFile).extension().string();
	}

	std::string ControllerConfig::getInputIsdFileName()
	{
		std::string fileName = boost::filesystem::path(this->_inputIsdFile).filename().string();
		return fileName;
	}

	std::string ControllerConfig::getInputIsdFilePath()
	{
		std::string filePath = boost::filesystem::path(this->_inputIsdFile).parent_path().string();
		return filePath;
	}

	std::string ControllerConfig::getOutputFilesPath()
	{
		// Standard output path is the path of the input file
		std::string outputFilesPath = this->getInputSdfFilePath();

		// If a custom output path was set, override local variable
		if (this->_outputFilesPath != "")
		{
			outputFilesPath = this->_outputFilesPath;
		}

		return outputFilesPath;
	}

	std::string ControllerConfig::getOutputModelFile()
	{
		return this->getOutputFilesPath() + "/" + this->getOutputModelFileName();
	}

	std::string ControllerConfig::getOutputModelFileName()
	{
		std::string fileStem = boost::filesystem::path(this->_inputSdfFile).stem().string();
		fileStem += "-model";

		return fileStem + ".nddl";
	}

	std::string ControllerConfig::getOutputInitialStateFile()
	{
		return this->getOutputFilesPath() + "/" + this->getOutputInitialStateFileName();
	}

	std::string ControllerConfig::getOutputInitialStateFileName()
	{
		std::string fileStem = boost::filesystem::path(this->_inputIsdFile).stem().string();
		fileStem += "-initial-state";

		return fileStem + ".nddl";
	}


	bool ControllerConfig::isReadOnly()
	{
		return this->_readOnly;
	}


	void ControllerConfig::trySet()
	{
		if (this->_readOnly)
		{
			throw nddlgen::exceptions::ControllerConfigIsReadOnlyException();
		}
	}

	std::string ControllerConfig::normalizePath(const boost::filesystem::path &path)
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

}}
