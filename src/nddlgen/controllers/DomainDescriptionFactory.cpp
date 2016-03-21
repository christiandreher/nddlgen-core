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
	nddlgen::models::DefaultArmModelPtr arm = boost::dynamic_pointer_cast<nddlgen::models::DefaultArmModel>(this->_modelFactory->fromString("arm"));
	nddlgen::models::DefaultWorkspaceModelPtr workspace = boost::dynamic_pointer_cast<nddlgen::models::DefaultWorkspaceModel>(this->_modelFactory->fromString("workspace"));
	nddlgen::models::InitialStateModelPtr initialState(new nddlgen::models::InitialStateModel());

	// Set names for arm and workspace manually
	arm->setName("arm");
	workspace->setName("workspace");

	// Add workspace to arm hierarchy, and arm and initial state to domain description
	arm->addSubObject(workspace);
	domainDescription->setArm(arm);
	domainDescription->setInitialState(initialState);

	// Populate DDM with the models defined in the SDF
	this->populateWithModelsFromSdf(domainDescription, sdfRoot);

	// Populate DDM with the goals defined in the ISD
	this->populateWithGoalsFromIsd(domainDescription, isdRoot);

	// Populate DDM with the sub objects as defined in each NddlGeneratable
	this->populateWithSubObjects(domainDescription);

	// Populate DDM with the actions and action prototypes as defined in each NddlGeneratable
	this->populateWithPredicates(domainDescription);

	// Populate DDM with the facts as defined in each NddlGeneratable
	this->populateWithFacts(domainDescription);

	// Populate DDM models that are blocked with the blocking objects
	this->populateWithBlockedObjects(domainDescription);

	// Populate DDM with actions as defined in each NddlGeneratable
	this->populateWithActions(domainDescription);

	// Populate DDM with used classes by traversing tree
	this->populateWithUsedClasses(domainDescription);

	// Return the fully qualified domain description model
	return domainDescription;
}

void nddlgen::controllers::DomainDescriptionFactory::setModelFactory(
		nddlgen::controllers::AbstractObjectFactoryPtr modelFactory)
{
	this->_modelFactory = modelFactory;
}

void nddlgen::controllers::DomainDescriptionFactory::populateWithModelsFromSdf(
		nddlgen::models::DomainDescriptionModelPtr domainDescription,
		nddlgen::types::SdfRoot sdfRoot)
{
	// Initialize needed variables
	nddlgen::models::DefaultWorkspaceModelPtr workspace = domainDescription->getArm()->getWorkspace();
	sdf::ElementPtr currentModelElement = sdfRoot->root->GetElement("world")->GetElement("model");

	// Iterate through elements in SDF model node
	while (currentModelElement)
	{
		nddlgen::models::AbstractObjectModelPtr generatableModel = this->modelFactory(currentModelElement);

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

void nddlgen::controllers::DomainDescriptionFactory::populateWithGoalsFromIsd(
		nddlgen::models::DomainDescriptionModelPtr domainDescription,
		nddlgen::types::IsdRoot isdRoot)
{
	nddlgen::models::InitialStateModelPtr initialState = domainDescription->getInitialState();

	TiXmlHandle isdRootHandle(isdRoot->RootElement());
	TiXmlElement* goals = isdRootHandle.FirstChild("goals").FirstChild("goal").ToElement();

	// Iterate through goals and add them to initial state model
	for (; goals; goals = goals->NextSiblingElement())
	{
		nddlgen::models::InitialStateGoalModelPtr goal(new nddlgen::models::InitialStateGoalModel());

		goal->setGoalName(goals->Attribute("name"));
		goal->setObjectName(goals->Attribute("for"));
		goal->setPredicate(goals->Attribute("predicate"));
		goal->setStartsAfter(goals->Attribute("starts-after"));
		goal->setEndsBefore(goals->Attribute("ends-before"));

		initialState->addGoal(goal);
	}
}

void nddlgen::controllers::DomainDescriptionFactory::populateWithSubObjects(
		nddlgen::models::DomainDescriptionModelPtr domainDescription)
{
	// Map containing all sub object classes and an incrementing index to keep
	// track of numbers to avoid instances with the same name
	std::map<std::string, int> indices;

	this->subObjectPopulationHelper(domainDescription->getArm(), indices);
}

void nddlgen::controllers::DomainDescriptionFactory::populateWithPredicates(
		nddlgen::models::DomainDescriptionModelPtr domainDescription)
{
	this->predicatesPopulationHelper(domainDescription->getArm());
}

void nddlgen::controllers::DomainDescriptionFactory::populateWithFacts(
		nddlgen::models::DomainDescriptionModelPtr domainDescription)
{
	// Get all objects
	nddlgen::types::ObjectModelList allObjects = this->getSubObjectsFrom(domainDescription);

	// Iterate through objects
	foreach (nddlgen::models::AbstractObjectModelPtr object, allObjects)
	{
		// If the object has predicates, get initial state predicate as fact and add
		// it to the initial state model
		if (object->hasPredicates())
		{
			domainDescription->getInitialState()->addFact(object->getInitialState());
		}
	}
}

void nddlgen::controllers::DomainDescriptionFactory::populateWithBlockedObjects(
		nddlgen::models::DomainDescriptionModelPtr domainDescription)
{
	// Get all models on workspace
	nddlgen::types::ObjectModelList models = domainDescription->getArm()->getWorkspace()->getModels();

	// Use this...
	foreach (nddlgen::models::AbstractObjectModelPtr model1, models)
	{
		// ...and this foreach loop to form all permutations (naive, may be improved)
		foreach (nddlgen::models::AbstractObjectModelPtr model2, models)
		{
			// Only run collision detection if model1 and model2 are not the same object
			if (model1 != model2)
			{
				// Accessibility bounding box of model1 and object bounding box of model2 need to be set
				if (model1->hasAccessibilityBoundingBox() && model2->hasObjectBoundingBox())
				{
					// Run collision detection and save result
					bool doBoundingBoxesIntersect = nddlgen::controllers::CollisionDetectionController::doesIntersect(
							model1->getAccessibilityBoundingBox(),
							model2->getObjectBoundingBox()
					);

					// If the bounding boxes intersect, instruct model1 that it is blocked by model2
					if (doBoundingBoxesIntersect)
					{
						model1->addBlockingObject(model2);
					}
				}
			}
		}
	}
}

void nddlgen::controllers::DomainDescriptionFactory::populateWithActions(
		nddlgen::models::DomainDescriptionModelPtr domainDescription)
{
	// Populate actions by calling initActions() for each NddlGeneratable
	this->actionsPopulationHelper(domainDescription->getArm());

	// List of all action prototypes. This will be passed to the Arm model later
	std::list<std::string> actionPrototypes;

	// Get all objects
	nddlgen::types::ObjectModelList allObjects = this->getSubObjectsFrom(domainDescription->getArm());

	// Iterate through all objects and register actions in DDM
	foreach (nddlgen::models::AbstractObjectModelPtr object, allObjects)
	{
		nddlgen::types::ActionList actions = object->getActions();
		domainDescription->registerActions(actions);
	}

	// Get all actions
	nddlgen::types::ActionList actions = domainDescription->getActions();

	// Loop through actions and generate prototypes
	foreach (nddlgen::models::ActionModelPtr action, actions)
	{
		std::string actionPrototype = "action " + action->getName() + " " + "{ duration=" + action->getDuration() + "; }";
		actionPrototypes.push_back(actionPrototype);
	}

	// Register action prototypes for the arm
	domainDescription->getArm()->setActionPrototypes(actionPrototypes);
}

void nddlgen::controllers::DomainDescriptionFactory::populateWithUsedClasses(
		nddlgen::models::DomainDescriptionModelPtr domainDescription)
{
	// Get all objects
	nddlgen::types::ObjectModelList allObjects = this->getSubObjectsFrom(domainDescription);

	// Insert class name into map. As the class name is used as the map key, there won't be duplicates
	foreach (nddlgen::models::AbstractObjectModelPtr object, allObjects)
	{
		domainDescription->addUsedClass(object);
	}
}

void nddlgen::controllers::DomainDescriptionFactory::subObjectPopulationHelper(
		nddlgen::models::AbstractObjectModelPtr model,
				std::map<std::string, int> indices)
{
	// Call initSubObjects() first, so that sub objects get instantiated
	model->initSubObjects();

	// If model has sub objects, initialize recursive call
	if (model->hasSubObjects())
	{
		// Index to be able to address sub objects
		int index = 0;

		// Get sub objects
		nddlgen::types::ObjectModelList subObjects = model->getSubObjects();

		// Loop through sub objects and use it as parameter for the recursive call
		foreach (nddlgen::models::AbstractObjectModelPtr subObject, subObjects)
		{
			this->subObjectPopulationHelper(subObject, indices);

			std::string subObjectClass = subObject->getClassName();
			std::string instanceName = subObject->getName();
			std::map<std::string, int>::iterator it = indices.find(subObjectClass);

			// If instanceName was not set, action is needed. Otherwise the program relies
			// on the uniqueness of instance names as the SDF species names to be unique
			if (instanceName == "")
			{
				instanceName = boost::to_lower_copy(subObject->getClassName())  + "_";

				// Check if subObjectClass exists in indices
				if (it != indices.end())
				{
					instanceName = instanceName + boost::lexical_cast<std::string>(it->second);
					model->setInstanceNameFor(index, instanceName);

					it->second++;
				}
				else
				{
					instanceName = instanceName + boost::lexical_cast<std::string>(1);
					model->setInstanceNameFor(index, instanceName);

					indices.insert(std::pair<std::string, int>(subObjectClass, 2));
				}
			}

			index++;
		}
	}
}

void nddlgen::controllers::DomainDescriptionFactory::predicatesPopulationHelper(
		nddlgen::models::AbstractObjectModelPtr model)
{
	// If model has sub objects, initialize recursive call
	if (model->hasSubObjects())
	{
		// Get sub objects
		nddlgen::types::ObjectModelList subObjects = model->getSubObjects();

		// Loop through sub objects and use it as parameter for the recursive call
		foreach (nddlgen::models::AbstractObjectModelPtr subObject, subObjects)
		{
			this->predicatesPopulationHelper(subObject);
		}
	}

	// In any case, call function of model
	model->initPredicates();
}

void nddlgen::controllers::DomainDescriptionFactory::actionsPopulationHelper(
		nddlgen::models::AbstractObjectModelPtr model)
{
	// If model has sub objects, initialize recursive call
	if (model->hasSubObjects())
	{
		// Get sub objects
		nddlgen::types::ObjectModelList subObjects = model->getSubObjects();

		// Loop through sub objects and use it as parameter for the recursive call
		foreach (nddlgen::models::AbstractObjectModelPtr subObject, subObjects)
		{
			this->actionsPopulationHelper(subObject);
		}
	}

	// In any case, call function of model
	model->initActions();
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::DomainDescriptionFactory::modelFactory(
		sdf::ElementPtr element)
{
	std::string elementName = element->GetAttribute("name")->GetAsString();
	nddlgen::models::AbstractObjectModelPtr instance = this->_modelFactory->fromString(elementName);

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

nddlgen::types::ObjectModelList nddlgen::controllers::DomainDescriptionFactory::getSubObjectsFrom(
		nddlgen::models::DomainDescriptionModelPtr domainDescription)
{
	// If list is empty, get all sub objects and save them to member
	if (this->_objects.size() == 0)
	{
		this->_objects = this->getSubObjectsFrom(domainDescription->getArm());
	}

	// Return list of all objects
	return this->_objects;
}

nddlgen::types::ObjectModelList nddlgen::controllers::DomainDescriptionFactory::getSubObjectsFrom(
		nddlgen::models::AbstractObjectModelPtr model)
{
	nddlgen::types::ObjectModelList output;

	// If model has sub objects, initialize recursive call
	if (model->hasSubObjects())
	{
		// Get sub objects
		nddlgen::types::ObjectModelList subObjects = model->getSubObjects();

		// Loop through sub objects and use it as parameter for the recursive call
		foreach (nddlgen::models::AbstractObjectModelPtr subObject, subObjects)
		{
			nddlgen::types::ObjectModelList recursiveOutput = this->getSubObjectsFrom(subObject);

			// Merge lists of sub objects into output list
			output.insert(output.end(), recursiveOutput.begin(), recursiveOutput.end());
		}
	}

	// Add parent model to the list, too
	output.push_back(model);

	return output;
}
