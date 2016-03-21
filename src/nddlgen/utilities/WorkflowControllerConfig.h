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

#include <cstddef>

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <nddlgen/controllers/AbstractObjectFactory.h>
#include <nddlgen/exceptions/ControllerConfigIsReadOnlyException.hpp>

namespace nddlgen
{
	namespace utilities
	{
		class WorkflowControllerConfig;
		typedef boost::shared_ptr<nddlgen::utilities::WorkflowControllerConfig> WorkflowControllerConfigPtr;
	}
}

/**
 * An object of this class is required to be passed to the WorkflowController
 * as configuration.
 *
 * @author Christian Dreher
 */
class nddlgen::utilities::WorkflowControllerConfig
{

	private:

		/**
		 * Name of the adapter which uses the framework.
		 * Will be printed into generated NDDL files to be able to backtrace generation.
		 */
		std::string _adapter;

		/**
		 * Path and name of SDF file. Relative or absolute. (E.g. ~/models/test.sdf).
		 */
		std::string _sdfInputFile;

		/**
		 * Path and name of ISD file. Relative or absolute. (E.g. ~/models/test.isd).
		 */
		std::string _isdInputFile;

		/**
		 * Output folder where NDDL files should be written to.
		 */
		std::string _outputFilesPath;

		/**
		 * Flag to mark this workflow controller object as read only. Disables all setters.
		 */
		bool _readOnly;

		/**
		 * Instance of the model factory which should be used.
		 */
		nddlgen::controllers::AbstractObjectFactoryPtr _modelFactory;

		/**
		 * Helper for setter functions. Tries to use the setter. May throw, if _readOnly
		 * was set to true before using a setter.
		 */
		void trySet();

		/**
		 * Normalizes existing and non-existing paths. From: http://stackoverflow.com/a/12797413/2938082
		 * Courtesy of jarzec (stackoverflow community member)
		 *
		 * @param path Path to be normalized
		 *
		 * @return Normalized path as string.
		 */
		std::string normalizePath(const boost::filesystem::path &path);

	public:

		/**
		 * Constructs a new worklfow controller configuration instance.
		 */
		WorkflowControllerConfig();

		/**
		 * Destructor to free memory.
		 */
		virtual ~WorkflowControllerConfig();

		/**
		 * Sets the adapter name.
		 *
		 * @param adapter Adapter name
		 */
		void setAdapter(std::string adapter);

		/**
		 * Sets SDF input file path and name.
		 *
		 * @param sdfInputFile SDF input file path and name (E.g. ~/models/test.sdf)
		 */
		void setSdfInputFile(std::string sdfInputFile);

		/**
		 * Sets ISD input file path and name.
		 *
		 * @param isdInputFile ISD input file path and name (E.g. ~/models/test.isd)
		 */
		void setIsdInputFile(std::string isdInputFile);

		/**
		 * Sets output folder path where NDDL files should be written to.
		 *
		 * @param outputFilesPath Path to output folder
		 */
		void setOutputFilesPath(std::string outputFilesPath);

		/**
		 * Sets this instance as read only. Calling setter after this function was
		 * invoked will result in thrown exceptions. Setting an instance as read only
		 * can not be reverted.
		 */
		void setReadOnly();

		/**
		 * Sets the model factory to be used.
		 *
		 * @param modelFactory Model factory
		 */
		void setModelFactory(nddlgen::controllers::AbstractObjectFactoryPtr modelFactory);

		/**
		 * Gets the adapter name.
		 *
		 * @return Adapter name.
		 */
		std::string getAdapter();

		/**
		 * Gets the SDF input file path and name.
		 *
		 * @return SDF input file path and name.
		 */
		std::string getSdfInputFile();

		/**
		 * Gets the file extension of the SDF input file.
		 *
		 * @return SDF input file extension.
		 */
		std::string getSdfInputFileExt();

		/**
		 * Gets the name of the SDF input file.
		 *
		 * @return SDF input file name.
		 */
		std::string getSdfInputFileName();

		/**
		 * Gets the path to the SDF input file.
		 *
		 * @return Path to SDF input file.
		 */
		std::string getSdfInputFilePath();

		/**
		 * Gets the ISD input file path and name.
		 *
		 * @return ISD input file path and name.
		 */
		std::string getIsdInputFile();

		/**
		 * Gets the file extension of the ISD input file.
		 *
		 * @return ISD input file extension.
		 */
		std::string getIsdInputFileExt();

		/**
		 * Gets the name of the ISD input file.
		 *
		 * @return ISD input file name.
		 */
		std::string getIsdInputFileName();

		/**
		 * Gets the path to the ISD input file.
		 *
		 * @return Path to ISD input file.
		 */
		std::string getIsdInputFilePath();

		/**
		 * Gets output file path.
		 *
		 * @return Ouput file path.
		 */
		std::string getOutputFilesPath();

		/**
		 * Get the name and path of the NDDL model file.
		 *
		 * @return NDDL model file name and path.
		 */
		std::string getOutputModelFile();

		/**
		 * Get the name of the NDDL model file.
		 *
		 * @return NDDL model name.
		 */
		std::string getOutputModelFileName();

		/**
		 * Get the name and path of the NDDL initial state file.
		 *
		 * @return NDDL initial state file name and path.
		 */
		std::string getOutputInitialStateFile();

		/**
		 * Get the name of the NDDL initial state file.
		 *
		 * @return NDDL initial state name.
		 */
		std::string getOutputInitialStateFileName();

		/**
		 * Gets the model factory.
		 *
		 * @return Model factory.
		 */
		nddlgen::controllers::AbstractObjectFactoryPtr getModelFactory();

		/**
		 * Tests if this instance has been marked as read only.
		 *
		 * @return True, if it is set as read only, false if not.
		 */
		bool isReadOnly();

};

#endif
