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

#ifndef NDDLGEN_CONTROLLER_DOMAINDESCRIPTIONFACTORY_H_
#define NDDLGEN_CONTROLLER_DOMAINDESCRIPTIONFACTORY_H_

#include <cstddef>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

#include <boost/shared_ptr.hpp>
#include <sdf/sdf.hh>
#include <tinyxml.h>

#include <nddlgen/controllers/NddlGeneratableFactory.h>
#include <nddlgen/exceptions/ModelFactoryNotSetException.hpp>
#include <nddlgen/math/Cuboid.h>
#include <nddlgen/math/CuboidOperations.h>
#include <nddlgen/math/Vector.h>
#include <nddlgen/math/VectorOperations.h>
#include <nddlgen/models/ArmModel.h>
#include <nddlgen/models/DomainDescriptionModel.h>
#include <nddlgen/models/NddlGeneratable.h>
#include <nddlgen/models/WorkspaceModel.h>
#include <nddlgen/utilities/InitialStateFact.h>
#include <nddlgen/utilities/InitialStateGoal.h>
#include <nddlgen/utilities/Types.hpp>
#include <nddlgen/utilities/Foreach.hpp>

namespace nddlgen
{
	namespace controllers
	{
		class DomainDescriptionFactory;
		typedef boost::shared_ptr<nddlgen::controllers::DomainDescriptionFactory> DomainDescriptionFactoryPtr;
	}
}

/**
 * Factory to properly build a domain description model.
 *
 * @author Christian Dreher
 */
class nddlgen::controllers::DomainDescriptionFactory
{

	private:

		/**
		 * Model factory instance.
		 */
		nddlgen::controllers::NddlGeneratableFactoryPtr _modelFactory;

		/**
		 * Populates workspace with the models that are found in the SDF.
		 *
		 * @param domainDescription Domain description model
		 * @param sdfRoot SDF document root
		 */
		void populateModelsFromSdf(nddlgen::models::DomainDescriptionModelPtr domainDescription,
				nddlgen::types::SdfRoot sdfRoot);

		/**
		 * Populates initial state model with the data in the ISD.
		 *
		 * @param domainDescription Domain description model
		 * @param isdRoot ISD document root
		 */
		void populateInitialStateFromIsd(nddlgen::models::DomainDescriptionModelPtr domainDescription,
				nddlgen::types::IsdRoot isdRoot);

		/**
		 * Factory function to instantiate NddGeneratables.
		 *
		 * @param element SDF element node
		 *
		 * @return Instantiated NddlGeneratable, or null pointer if this->_modelFactory was
		 * not able to instantiate one from the SDF data.
		 */
		nddlgen::models::NddlGeneratablePtr modelFactory(sdf::ElementPtr element);

		/**
		 * Factory function to instantiate a bounding box.
		 *
		 * @param basePose Base pose as defined in SDF
		 * @param pose Pose as defined in SDF
		 * @param size Size as defined in SDF
		 *
		 * @return Cuboid object representing bounding box.
		 */
		nddlgen::math::CuboidPtr boundingBoxFactory(std::string basePose,
				std::string pose,
				std::string size);

		/**
		 * Factory function to instantiate facts.
		 *
		 * @param factElement Fact as defined in ISD
		 *
		 * @return Fact object representing a fact in NDDL.
		 */
		nddlgen::utilities::InitialStateFactPtr factFactory(TiXmlElement* factElement);

		/**
		 * Factory function to instantiate goals.
		 *
		 * @param goalElement Goal as defined in ISD
		 *
		 * @return Goal object representing a goal in NDDL.
		 */
		nddlgen::utilities::InitialStateGoalPtr goalFactory(TiXmlElement* goalElement);

	public:

		/**
		 * Constructor initializing a new object.
		 */
		DomainDescriptionFactory();

		/**
		 * Destructor to free memory.
		 */
		virtual ~DomainDescriptionFactory();

		/**
		 * Builds a domain description out of SDF and ISD document roots.
		 *
		 * @param sdfRoot SDF document root
		 * @param isdRoot ISD document root
		 *
		 * @return Fully qualified domain description model.
		 */
		nddlgen::models::DomainDescriptionModelPtr build(nddlgen::types::SdfRoot sdfRoot,
				nddlgen::types::IsdRoot isdRoot);

		/**
		 * Set model factory needed by domain description factory.
		 *
		 * @param modelFactory Model factory
		 */
		void setModelFactory(nddlgen::controllers::NddlGeneratableFactoryPtr modelFactory);

};

#endif
