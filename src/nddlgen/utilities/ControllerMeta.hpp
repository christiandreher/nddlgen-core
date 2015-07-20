/*
 * ControllerMeta.hpp
 *
 *  Created on: Jul 19, 2015
 *      Author: chris
 */

#ifndef NDDLGEN_UTILITIES_CONTROLLERMETA_HPP_
#define NDDLGEN_UTILITIES_CONTROLLERMETA_HPP_

namespace nddlgen { namespace utilities {

	class ControllerMeta
	{
		public:
			std::string nddlgenVersion;
			std::string inputFile;
			std::string outputFilePath;
			std::string outputFileModels;
			std::string outputFileInitialState;

			ControllerMeta()
			{

			}

			~ControllerMeta()
			{

			}
	};

}}

#endif
