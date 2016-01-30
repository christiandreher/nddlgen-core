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

#include <nddlgen/controllers/DomainDescriptionFactory.h>

nddlgen::controllers::DomainDescriptionFactory::DomainDescriptionFactory()
{

}

nddlgen::controllers::DomainDescriptionFactory::~DomainDescriptionFactory()
{

}

nddlgen::models::DomainDescriptionModelPtr nddlgen::controllers::DomainDescriptionFactory::build(
		nddlgen::types::SdfRoot sdfRoot,
		nddlgen::types::IsdRoot isdRoot)
{
	// Assert that a model factory was set
	if (!this->_modelFactory)
	{
		throw nddlgen::exceptions::ModelFactoryNotSetException();
	}

	// Instantiate basic models
	nddlgen::models::DomainDescriptionModelPtr domainDescription(new nddlgen::models::DomainDescriptionModel());
	nddlgen::models::ArmModelPtr arm = boost::dynamic_pointer_cast<nddlgen::models::ArmModel>(this->_modelFactory->fromString("arm"));
	nddlgen::models::WorkspaceModelPtr workspace = boost::dynamic_pointer_cast<nddlgen::models::WorkspaceModel>(this->_modelFactory->fromString("workspace"));
	nddlgen::models::InitialStateModelPtr initialState(new nddlgen::models::InitialStateModel());

	// Set names for arm and workspace manually
	arm->setName("arm");
	workspace->setName("workspace");

	// Add workspace to arm hierarchy, and arm and initial state to domain description
	arm->addSubObject(workspace);
	domainDescription->setArm(arm);
	domainDescription->setInitialState(initialState);

	// Populate domain description with the information given by the SDF and ISD input files
	this->populateModelsFromSdf(domainDescription, sdfRoot);
	this->populateGoalsFromIsd(domainDescription, isdRoot);

	// Initialize model sub objects by calling initSubObjects() for all models
	domainDescription->initSubObjects();

	// Initialize predicates by calling initPredicates() for all models
	domainDescription->initPredicates();

	// Initialize facts
	domainDescription->gatherFacts();

	// Call configurateDomain(...) to allow user to modify domain further
	this->_modelFactory->configurateDomain(domainDescription);

	// Detect blocking objects
	domainDescription->detectBlockingObjects();

	// Initialize actions by calling initActions() for all models
	domainDescription->initActions();

	// Gather used classes
	domainDescription->gatherUsedClasses();

	// Gather all actions
	domainDescription->gatherActions();

	// Return the fully qualified domain description model
	return domainDescription;
}

void nddlgen::controllers::DomainDescriptionFactory::setModelFactory(
		nddlgen::controllers::NddlGeneratableFactoryPtr modelFactory)
{
	this->_modelFactory = modelFactory;
}

void nddlgen::controllers::DomainDescriptionFactory::populateModelsFromSdf(
		nddlgen::models::DomainDescriptionModelPtr domainDescription,
		nddlgen::types::SdfRoot sdfRoot)
{
	// Initialize needed variables
	nddlgen::models::WorkspaceModelPtr workspace = domainDescription->getArm()->getWorkspace();
	sdf::ElementPtr currentModelElement = sdfRoot->root->GetElement("world")->GetElement("model");

	// Iterate through elements in SDF model node
	while (currentModelElement)
	{
		nddlgen::models::NddlGeneratablePtr generatableModel = this->modelFactory(currentModelElement);

		// If generatableModel is null, it is not supported by the given model factory
		// and will therefore be ignored and not added to the workspace
		if (generatableModel)
		{
			// First add generatableModel to workspace to make sure that it is initialized properly
			workspace->addModelToWorkspace(generatableModel);
		}

		// Iterate
		currentModelElement = currentModelElement->GetNextElement("model");
	}
}

void nddlgen::controllers::DomainDescriptionFactory::populateGoalsFromIsd(
		nddlgen::models::DomainDescriptionModelPtr domainDescription,
		nddlgen::types::IsdRoot isdRoot)
{
	nddlgen::models::InitialStateModelPtr initialState = domainDescription->getInitialState();

	TiXmlHandle isdRootHandle(isdRoot->RootElement());
	TiXmlElement* goals = isdRootHandle.FirstChild("goals").FirstChild("goal").ToElement();

	// Iterate through goals and add them to initial state model
	for (; goals; goals = goals->NextSiblingElement())
	{
		nddlgen::utilities::InitialStateGoalPtr goal(new nddlgen::utilities::InitialStateGoal());

		goal->setGoalName(goals->Attribute("name"));
		goal->setModelName(goals->Attribute("for"));
		goal->setPredicate(goals->Attribute("predicate"));
		goal->setStartsAfter(goals->Attribute("starts-after"));
		goal->setEndsBefore(goals->Attribute("ends-before"));

		initialState->addGoal(goal);
	}
}

nddlgen::models::NddlGeneratablePtr nddlgen::controllers::DomainDescriptionFactory::modelFactory(
		sdf::ElementPtr element)
{
	std::string elementName = element->GetAttribute("name")->GetAsString();
	nddlgen::models::NddlGeneratablePtr instance = this->_modelFactory->fromString(elementName);

	// If instance is set
	if (instance)
	{
		// Set name
		instance->setName(elementName);

		std::string basePoseRaw = element->GetElement("pose")->GetValue()->GetAsString();

		sdf::ElementPtr boundingBox = element->GetElement("link");

		while (boundingBox)
		{
			std::string linkName = boundingBox->GetAttribute("name")->GetAsString();

			if (linkName.find("bounding_box") != std::string::npos)
			{
				std::string poseRaw = boundingBox->GetElement("visual")->GetElement("pose")
						->GetValue()->GetAsString();
				std::string sizeRaw = boundingBox->GetElement("visual")->GetElement("geometry")->GetElement("box")
						->GetElement("size")->GetValue()->GetAsString();

				nddlgen::math::CuboidPtr boundingBox = nddlgen::controllers::DomainDescriptionFactory::
						boundingBoxFactory(basePoseRaw, poseRaw, sizeRaw);

				if (linkName.find("object") != std::string::npos)
				{
					instance->setObjectBoundingBox(boundingBox);
				}
				else if (linkName.find("accessibility") != std::string::npos)
				{
					instance->setAccessibilityBoundingBox(boundingBox);
				}
			}

			// Iterate
			boundingBox = boundingBox->GetNextElement("link");
		}
	}

	return instance;
}

nddlgen::math::CuboidPtr nddlgen::controllers::DomainDescriptionFactory::boundingBoxFactory(
		std::string basePose,
		std::string pose,
		std::string size)
{
	// For all values: (x,y,z) element of double^3 (no unit defined by gazebo)
	//				   (roll,pitch,yaw) element of double^3 (in radians)

	// Vectors holding exploded strings
	std::vector<std::string> basePoseSplit;
	std::vector<std::string> poseSplit;
	std::vector<std::string> sizeSplit;

	// Explode strings and save to vectors defined above
	boost::algorithm::split(basePoseSplit, basePose, boost::is_any_of(" "));
	boost::algorithm::split(poseSplit, pose, boost::is_any_of(" "));
	boost::algorithm::split(sizeSplit, size, boost::is_any_of(" "));

	// Extract pose of base object
	double xBase = atof(basePoseSplit[0].c_str());
	double yBase = atof(basePoseSplit[1].c_str());
	double zBase = atof(basePoseSplit[2].c_str());
	double rollBase = atof(basePoseSplit[3].c_str());
	double pitchBase = atof(basePoseSplit[4].c_str());
	double yawBase = atof(basePoseSplit[5].c_str());

	// Extract pose of bounding box and add base pose
	double x = atof(poseSplit[0].c_str()) + xBase;
	double y = atof(poseSplit[1].c_str()) + yBase;
	double z = atof(poseSplit[2].c_str()) + zBase;
	double roll = atof(poseSplit[3].c_str());
	double pitch = atof(poseSplit[4].c_str());
	double yaw = atof(poseSplit[5].c_str());

	// Extract extend of bounding box (an extend is the abs value of half the size)
	double xExtend = atof(sizeSplit[0].c_str()) / 2.f;
	double yExtend = atof(sizeSplit[1].c_str()) / 2.f;
	double zExtend = atof(sizeSplit[2].c_str()) / 2.f;

	// Construct vectors defining every single vertex of the cuboid by extends with the
	// origin in the middle of the cuboid. This eases rotations
	nddlgen::math::VectorPtr vertex1(new nddlgen::math::Vector(  xExtend,   yExtend,   zExtend));
	nddlgen::math::VectorPtr vertex2(new nddlgen::math::Vector(  xExtend, - yExtend,   zExtend));
	nddlgen::math::VectorPtr vertex3(new nddlgen::math::Vector(- xExtend,   yExtend,   zExtend));
	nddlgen::math::VectorPtr vertex4(new nddlgen::math::Vector(- xExtend, - yExtend,   zExtend));
	nddlgen::math::VectorPtr vertex5(new nddlgen::math::Vector(  xExtend,   yExtend, - zExtend));
	nddlgen::math::VectorPtr vertex6(new nddlgen::math::Vector(  xExtend, - yExtend, - zExtend));
	nddlgen::math::VectorPtr vertex7(new nddlgen::math::Vector(- xExtend,   yExtend, - zExtend));
	nddlgen::math::VectorPtr vertex8(new nddlgen::math::Vector(- xExtend, - yExtend, - zExtend));

	// Define and construct vector of all vertices
	std::vector<nddlgen::math::VectorPtr> vertices;
	vertices.push_back(vertex1);
	vertices.push_back(vertex2);
	vertices.push_back(vertex3);
	vertices.push_back(vertex4);
	vertices.push_back(vertex5);
	vertices.push_back(vertex6);
	vertices.push_back(vertex7);
	vertices.push_back(vertex8);

	// Roll cuboid
	nddlgen::math::CuboidOperations::roll(vertices, rollBase);
	nddlgen::math::CuboidOperations::roll(vertices, roll);

	// Pitch cuboid
	nddlgen::math::CuboidOperations::pitch(vertices, pitchBase);
	nddlgen::math::CuboidOperations::pitch(vertices, pitch);

	// Yaw cuboid
	nddlgen::math::CuboidOperations::yaw(vertices, yawBase);
	nddlgen::math::CuboidOperations::yaw(vertices, yaw);

	// Define absolute position of cuboid in space
	for (int i = 0; i < 8 /* amount of vertices of a cuboid */; i++)
	{
		nddlgen::math::VectorPtr vertex = vertices[i];

		vertex->addX(x);
		vertex->addY(y);
		vertex->addZ(z);
	}

	// Calculate normals for each axis
	nddlgen::math::VectorPtr xAxisNormal = nddlgen::math::VectorOperations::crossProduct(
			nddlgen::math::VectorOperations::minus(vertex1, vertex5),
			nddlgen::math::VectorOperations::minus(vertex6, vertex5)
	);
	nddlgen::math::VectorPtr yAxisNormal = nddlgen::math::VectorOperations::crossProduct(
			nddlgen::math::VectorOperations::minus(vertex1, vertex5),
			nddlgen::math::VectorOperations::minus(vertex7, vertex5)
	);
	nddlgen::math::VectorPtr zAxisNormal = nddlgen::math::VectorOperations::crossProduct(
			nddlgen::math::VectorOperations::minus(vertex7, vertex5),
			nddlgen::math::VectorOperations::minus(vertex6, vertex5)
	);

	// Construct cuboid defining the bounding box
	nddlgen::math::CuboidPtr boundingBox(new nddlgen::math::Cuboid(vertices, xAxisNormal, yAxisNormal, zAxisNormal));

	return boundingBox;
}
