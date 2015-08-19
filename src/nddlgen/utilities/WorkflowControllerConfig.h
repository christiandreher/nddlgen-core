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

#ifndef NDDLGEN_UTILITIES_WORKFLOWCONTROLLERCONFIG_H_
#define NDDLGEN_UTILITIES_WORKFLOWCONTROLLERCONFIG_H_

#include <boost/filesystem.hpp>

#include <nddlgen/exceptions/ControllerConfigIsReadOnlyException.hpp>

namespace nddlgen { namespace utilities { class WorkflowControllerConfig; }}

class nddlgen::utilities::WorkflowControllerConfig
{

	private:

		std::string _adapter;
		std::string _sdfInputFile;
		std::string _isdInputFile;
		std::string _outputFilesPath;
		bool _readOnly;

		void trySet();

		/**
		 * Normalizes existing and non-existing paths. From: http://stackoverflow.com/a/12797413/2938082
		 * Courtesy of jarzec (stackoverflow community member)
		 *
		 * @param path Path to be normalized
		 *
		 * @return Normalized path as string
		 */
		std::string normalizePath(const boost::filesystem::path &path);

	public:

		WorkflowControllerConfig();
		virtual ~WorkflowControllerConfig();

		void setAdapter(std::string adapter);
		void setSdfInputFile(std::string sdfInputFile);
		void setIsdInputFile(std::string isdInputFile);
		void setOutputFilesPath(std::string outputFilesPath);
		void setReadOnly();

		std::string getAdapter();
		std::string getSdfInputFile();
		std::string getSdfInputFileExt();
		std::string getSdfInputFileName();
		std::string getSdfInputFilePath();
		std::string getIsdInputFile();
		std::string getIsdInputFileExt();
		std::string getIsdInputFileName();
		std::string getIsdInputFilePath();
		std::string getOutputFilesPath();
		std::string getOutputModelFile();
		std::string getOutputModelFileName();
		std::string getOutputInitialStateFile();
		std::string getOutputInitialStateFileName();

		bool isReadOnly();
};

#endif
