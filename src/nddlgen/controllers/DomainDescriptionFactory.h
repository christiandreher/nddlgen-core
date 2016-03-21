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
#include <nddlgen/controllers/AbstractObjectFactory.h>
#include <nddlgen/exceptions/ObjectFactoryNotSetException.hpp>
#include <sdf/sdf.hh>
#include <tinyxml.h>

#include <nddlgen/math/Cuboid.h>
#include <nddlgen/math/CuboidOperations.h>
#include <nddlgen/math/Vector.h>
#include <nddlgen/math/VectorOperations.h>
#include <nddlgen/models/AbstractObjectModel.h>
#include <nddlgen/models/DefaultArmModel.h>
#include <nddlgen/models/DefaultWorkspaceModel.h>
#include <nddlgen/models/DomainDescriptionModel.h>
#include <nddlgen/models/InitialStateFactModel.h>
#include <nddlgen/models/InitialStateGoalModel.h>
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
		nddlgen::controllers::AbstractObjectFactoryPtr _objectFactory;

		/**
		 * Collection of all NddlGeneratable objects within the hierarchy.
		 * Access this only with the getObjects() function, since this value
		 * will be evaluated lazily.
		 */
		nddlgen::types::ObjectModelList _objects;

		/**
		 * Populates domain description model with the models that are found in the SDF.
		 *
		 * @param domainDescription Domain description model
		 * @param sdfRoot SDF document root
		 */
		void populateWithObjectsFromSdf(
				nddlgen::models::DomainDescriptionModelPtr domainDescription,
				nddlgen::types::SdfRoot sdfRoot
		);

		/**
		 * Populates domain description model with the goals from the ISD.
		 *
		 * @param domainDescription Domain description model
		 * @param isdRoot ISD document root
		 */
		void populateWithGoalsFromIsd(
				nddlgen::models::DomainDescriptionModelPtr domainDescription,
				nddlgen::types::IsdRoot isdRoot
		);

		/**
		 * Populates domain description model with model sub objects as defined
		 * in the NddlGeneratable::initSubObject() function.
		 *
		 * @param domainDescription Domain description model
		 */
		void populateWithSubObjects(
				nddlgen::models::DomainDescriptionModelPtr domainDescription
		);

		/**
		 * Populates domain description model with predicates as defined in
		 * the NddlGeneratable::initPredicates() function.
		 *
		 * @param domainDescription Domain description model
		 */
		void populateWithPredicates(
				nddlgen::models::DomainDescriptionModelPtr domainDescription
		);

		/**
		 * Populates domain description model with facts as defined by the
		 * NddlGeneratable::_initialPredicate member.
		 *
		 * @param domainDescription Domain description model
		 */
		void populateWithFacts(
				nddlgen::models::DomainDescriptionModelPtr domainDescription
		);

		/**
		 * Populates the models within the domain description model which are
		 * blocked by other objects according to a collision detection algorithm.
		 *
		 * @param domainDescription Domain description model
		 */
		void populateWithBlockedObjects(
				nddlgen::models::DomainDescriptionModelPtr domainDescription
		);

		/**
		 * Populates domain description model with actions as defined in the
		 * NddlGenertable::initActions() function.
		 *
		 * @param domainDescription Domain description model
		 */
		void populateWithActions(
				nddlgen::models::DomainDescriptionModelPtr domainDescription
		);

		/**
		 * Populates domain description model with all classes that are used.
		 *
		 * @param domainDescription Domain description model
		 */
		void populateWithUsedClasses(
				nddlgen::models::DomainDescriptionModelPtr domainDescription
		);

		/**
		 * Helper to populate models with sub objects as defined in the initSubObjects()
		 * function.
		 *
		 * @param model Current model in tree
		 * @param indices Map to keep track of all indices. Should be empty initially
		 */
		void subObjectPopulationHelper(
				nddlgen::models::AbstractObjectModelPtr model,
				std::map<std::string, int> indices
		);

		/**
		 * Helper to populate models with predicates as defined in the initPredicates()
		 * function.
		 *
		 * @param model Current model in tree
		 */
		void predicatesPopulationHelper(
				nddlgen::models::AbstractObjectModelPtr object
		);

		/**
		 * Helper to populate models with actions as defined in the initActions()
		 * function. Also add all actions to the domain description model directly.
		 *
		 * @param model Current model in tree
		 */
		void actionsPopulationHelper(
				nddlgen::models::AbstractObjectModelPtr model
		);

		/**
		 * Factory function to instantiate NddGeneratables.
		 *
		 * @param element SDF element node
		 *
		 * @return Instantiated NddlGeneratable, or null pointer if this->_modelFactory was
		 * not able to instantiate one from the SDF data.
		 */
		nddlgen::models::AbstractObjectModelPtr objectFactory(
				sdf::ElementPtr element
		);

		/**
		 * Factory function to instantiate a bounding box.
		 *
		 * @param basePose Base pose as defined in SDF
		 * @param pose Pose as defined in SDF
		 * @param size Size as defined in SDF
		 *
		 * @return Cuboid object representing bounding box.
		 */
		nddlgen::math::CuboidPtr boundingBoxFactory(
				std::string basePose,
				std::string pose,
				std::string size
		);

		/**
		 * Gets all used objects. Use this instead of directly accessing
		 * _objects, since this field is lazily evaluated.
		 *
		 * @param domainDescription Domain description model
		 *
		 * @return List of all used objects
		 */
		nddlgen::types::ObjectModelList getSubObjectsFrom(
				nddlgen::models::DomainDescriptionModelPtr domainDescription
		);

		/**
		 * Gets all sub objects of given model.
		 *
		 * @param model Model from where to start traversing tree
		 *
		 * @return List of all sub objects.
		 */
		nddlgen::types::ObjectModelList getSubObjectsFrom(
				nddlgen::models::AbstractObjectModelPtr model
		);

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
		nddlgen::models::DomainDescriptionModelPtr build(
				nddlgen::types::SdfRoot sdfRoot,
				nddlgen::types::IsdRoot isdRoot
		);

		/**
		 * Set model factory needed by domain description factory.
		 *
		 * @param modelFactory Model factory
		 */
		void setObjectFactory(
				nddlgen::controllers::AbstractObjectFactoryPtr modelFactory
		);

};

#endif
