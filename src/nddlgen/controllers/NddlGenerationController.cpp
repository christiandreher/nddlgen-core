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

#include <nddlgen/controllers/NddlGenerationController.h>

nddlgen::controllers::NddlGenerationController::NddlGenerationController()
{

}

nddlgen::controllers::NddlGenerationController::~NddlGenerationController()
{

}

void nddlgen::controllers::NddlGenerationController::writeModelFile(
		nddlgen::models::DomainDescriptionModelPtr domainDescription,
		nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig,
		bool forceOverwrite)
{
	// Assert that the file does not exist yet, unless an overwrite is forced
	if (!forceOverwrite && boost::filesystem::exists(controllerConfig->getOutputModelFile()))
	{
		throw nddlgen::exceptions::FileAlreadyExistsException(controllerConfig->getOutputModelFile());
	}

	// Open output file stream
	std::ofstream ofStream(controllerConfig->getOutputModelFile());

	// Print boilerplate
	nddlgen::controllers::NddlGenerationController::generateModelBoilerplate(ofStream, controllerConfig);

	// Print forward declarations
	domainDescription->generateForwardDeclarations(ofStream);

	// Print model for each used class
	domainDescription->generateNddlClasses(ofStream);

	// Print arm actions
	domainDescription->generateActions(ofStream);

	// Model file generated, close stream
	ofStream.close();
}

void nddlgen::controllers::NddlGenerationController::writeInitialStateFile(
		nddlgen::models::DomainDescriptionModelPtr domainDescription,
		nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig,
		bool forceOverwrite)
{
	// Assert that the file does not exist yet, unless an overwrite is forced
	if (!forceOverwrite && boost::filesystem::exists(controllerConfig->getOutputInitialStateFile()))
	{
		throw nddlgen::exceptions::FileAlreadyExistsException(controllerConfig->getOutputInitialStateFile());
	}

	// Open output file stream
	std::ofstream ofStream(controllerConfig->getOutputInitialStateFile());

	// Print boilerplate
	nddlgen::controllers::NddlGenerationController::generateInitialStateBoilerplate(ofStream, controllerConfig);

	// Print include directive for the NDDL model file
	wrln(0, "#include \"" + controllerConfig->getOutputModelFileName() + "\"", 2);

	// Print instantiation of all needed objects
	domainDescription->generateInstantiations(ofStream);

	// Print PLASMA function call to close model instantiation
	wrln(0, "close();", 2);

	// Print facts
	domainDescription->generateFacts(ofStream);

	// Print goals
	domainDescription->generateGoals(ofStream);

	// Initial state file generated, close stream
	ofStream.close();
}

void nddlgen::controllers::NddlGenerationController::generateModelBoilerplate(std::ofstream& ofStream,
		nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig)
{
	nddlgen::controllers::NddlGenerationController::generateBoilerplate(ofStream, controllerConfig, "model");
}

void nddlgen::controllers::NddlGenerationController::generateInitialStateBoilerplate(std::ofstream& ofStream,
		nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig)
{
	nddlgen::controllers::NddlGenerationController::generateBoilerplate(ofStream, controllerConfig, "initial state");
}

void nddlgen::controllers::NddlGenerationController::generateBoilerplate(std::ofstream& ofStream,
		nddlgen::utilities::WorkflowControllerConfigPtr controllerConfig,
		std::string modelOrInitialState)
{
	// Initialize meta information short hands
	std::string nddlgenVersion = nddlgen::utilities::Meta::NDDLGEN_VERSION;
	std::string nddlgenProjectHomepage = nddlgen::utilities::Meta::NDDLGEN_PROJECT_HOMEPAGE;
	std::string nddlgenSupportEmail = nddlgen::utilities::Meta::NDDLGEN_SUPPORT_EMAIL;
	std::string authorChrDreherEmail = nddlgen::utilities::Meta::AUTHOR_CHR_DREHER_EMAIL;

	// Initialize adapter name short hand
	std::string adapter = controllerConfig->getAdapter();

	// Initialize file name short hands
	std::string outputFile = "";
	std::string sdfInputFile = controllerConfig->getSdfInputFileName();
	std::string isdInputFile = controllerConfig->getIsdInputFileName();
	std::string sdfInputFilePath = controllerConfig->getSdfInputFilePath();
	std::string isdInputFilePath = controllerConfig->getIsdInputFilePath();

	// Initialize timestamp and file type
	std::string now = nddlgen::controllers::NddlGenerationController::getPrettifiedDate();

	// Assign values according to the type of the file (model or initial state)
	if (modelOrInitialState == "model")
	{
		outputFile = controllerConfig->getOutputModelFileName();
	}
	else if (modelOrInitialState == "initial state")
	{
		outputFile = controllerConfig->getOutputInitialStateFileName();
	}

	// Print boilerplate
	wrln(0, "// Generated by nddlgen \t\t <" + nddlgenProjectHomepage + ">", 1);
	wrln(0, "// Author: Christian Dreher \t <" + authorChrDreherEmail + ">", 1);
	wrln(0, "// Support: \t\t\t\t\t <" + nddlgenSupportEmail + ">", 2);

	wrln(0, "// This NDDL " + modelOrInitialState + " file (" + outputFile + ") was generated from ", 1);
	wrln(0, "// \"" + sdfInputFile + "\" originally located in \"" + sdfInputFilePath + "\" ", 0);

	if (modelOrInitialState == "model")
	{
		wrln(0, "by", 1);
	}
	else if (modelOrInitialState == "initial state")
	{
		wrln(0, "and", 1);
		wrln(0, "// \"" + isdInputFile + "\" originally located in \"" + isdInputFilePath + "\" by", 1);
	}

	wrln(0, "// nddlgen-core v" + nddlgenVersion + " using " + adapter + "", 1);
	wrln(0, "// Creation date: " + now, 2);
}

std::string nddlgen::controllers::NddlGenerationController::getPrettifiedDate()
{
	// Get POSIX time
	std::string date = boost::posix_time::to_iso_extended_string(boost::posix_time::second_clock::local_time());

	// Replace T with space: "yyyy-mm-ddThh:MM:ss" => "yyyy-mm-dd hh:MM:ss"
	boost::replace_all(date, "T", " ");

	// Return prettified date
	return date;
}
