#define _USE_MATH_DEFINES
#include "Lesson102.h"
#include "Timing.h"
#include <cmath>                                  
#include "ctime"
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <string>
#include "../..\\Programs\\Shared_Projects\\tinyxml\\include\\tinyxml.h"

#define PI 3.14159265 
using namespace std;

// Physics SDK globals
NxPhysicsSDK*     gPhysicsSDK = NULL;
NxScene*          gScene = NULL;
NxVec3            gDefaultGravity(0, -100.0, 0);
UserAllocator*	  gAllocator;

// User report globals
DebugRenderer     gDebugRenderer;

// HUD globals
HUD hud;

// Display globals
int gMainHandle;
int mx = 0;
int my = 0;
float outerCylinderD;
float cylinderH;
float cylindersDelta;
float innerCylinderD;
float sphereDiameter;
float sphereDiameterTolerance;
float particlesH;
int count_of_sphere = 0;

float** spheres_pos;
NxActor** sphere;
NxActor* InCylinder;
NxActor* OutCylinder;
// Camera globals
float	gCameraAspectRatio = 1;
NxVec3	gCameraPos(0, 5, -15);
NxVec3	gCameraForward(0, 0, 1);
NxVec3	gCameraRight(-1, 0, 0);
const NxReal gCameraSpeed = 10;

// Force globals
NxVec3 gForceVec(0, 0, 0);
NxReal gForceStrength = 20000;
bool bForceMode = true;

// Keyboard globals
#define MAX_KEYS 256
bool gKeys[MAX_KEYS];

// Simulation globals
NxReal gDeltaTime = 1.0 / 60.0;
bool bHardwareScene = false;
bool bPause = false;
bool bShadows = true;
bool bDebugWireframeMode = false;
bool bDeleteActors = false;

// Actor globals
NxActor* groundPlane = NULL;
NxConvexMeshDesc* convexDesc = NULL;
NxTriangleMeshDesc* triangleMeshDesc = NULL;
NxTriangleMeshDesc* concaveDesc = NULL;

// Focus actor
NxActor* gSelectedActor = NULL;

bool was_frozen = false;

bool IsSelectable(NxActor* actor)
{
	NxShape*const* shapes = gSelectedActor->getShapes();
	NxU32 nShapes = gSelectedActor->getNbShapes();
	while (nShapes--)
	{
		if (shapes[nShapes]->getFlag(NX_TRIGGER_ENABLE))
		{
			return false;
		}
	}

	if (!actor->isDynamic())
		return false;

	if (actor == groundPlane)
		return false;

	return true;
}


void SelectNextActor()
{
	NxU32 nbActors = gScene->getNbActors();
	NxActor** actors = gScene->getActors();
	for (NxU32 i = 0; i < nbActors; i++)
	{
		if (actors[i] == gSelectedActor)
		{
			NxU32 j = 1;
			gSelectedActor = actors[(i + j) % nbActors];
			while (!IsSelectable(gSelectedActor))
			{
				j++;
				gSelectedActor = actors[(i + j) % nbActors];
			}
			break;
		}
	}
}

void PrintControls()
{
	printf("\n Flight Controls:\n ----------------\n w = forward, s = back\n a = strafe left, d = strafe right\n q = up, z = down\n");
	printf("\n Press 'n' to freeze spheres and delete cylindres");
	printf("\n Miscellaneous:\n --------------\n p   = Pause\n b   = Toggle Debug Wireframe Mode\n x   = Toggle Shadows\n r   = Select Actor\n F10 = Reset Scene\n");
}

NxVec3 ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength)
{
	NxVec3 forceVec = forceStrength * forceDir*gDeltaTime;
	actor->addForce(forceVec);
	return forceVec;
}

void ProcessCameraKeys()
{
	NxReal deltaTime;

	if (bPause) deltaTime = 0.0005; else deltaTime = gDeltaTime;

	// Process camera keys
	for (int i = 0; i < MAX_KEYS; i++)
	{
		if (!gKeys[i]) { continue; }

		switch (i)
		{
		// Camera controls
		case 'w': { gCameraPos += gCameraForward * gCameraSpeed*deltaTime; break; }
		case 's': { gCameraPos -= gCameraForward * gCameraSpeed*deltaTime; break; }
		case 'a': { gCameraPos -= gCameraRight * gCameraSpeed*deltaTime; break; }
		case 'd': { gCameraPos += gCameraRight * gCameraSpeed*deltaTime; break; }
		case 'z': { gCameraPos -= NxVec3(0, 1, 0)*gCameraSpeed*deltaTime; break; }
		case 'q': { gCameraPos += NxVec3(0, 1, 0)*gCameraSpeed*deltaTime; break; }
		}
	}
}

void SetupCamera()
{
	gCameraAspectRatio = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);

	// Setup camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, gCameraAspectRatio, 1.0f, 10000.0f);
	gluLookAt(gCameraPos.x, gCameraPos.y, gCameraPos.z, gCameraPos.x + gCameraForward.x, gCameraPos.y + gCameraForward.y, gCameraPos.z + gCameraForward.z, 0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderActors(bool shadows)
{
	// Render all the actors in the scene
	NxU32 nbActors = gScene->getNbActors();
	NxActor** actors = gScene->getActors();
	while (nbActors--)
	{
		NxActor* actor = *actors++;
		DrawActor(actor, gSelectedActor, false);

		// Handle shadows
		if (shadows)
		{
			DrawActorShadow(actor, false);
		}
	}
}

void DrawForce(NxActor* actor, NxVec3& forceVec, const NxVec3& color)
{
	// Draw only if the force is large enough
	NxReal force = forceVec.magnitude();
	if (force < 0.1)  return;

	forceVec = 3 * forceVec / force;

	NxVec3 pos = actor->getCMassGlobalPosition();
	DrawArrow(pos, pos + forceVec, color);
}

void freeze_objects()
{
	if (was_frozen) {
		return;
	}

	/*Delete outer spheres*/
	float PosX, PosY, PosZ;
	for (int i = 0; i < count_of_sphere; i++)
	{
		PosX = sphere[i]->getGlobalPosition()[0];
		PosY = sphere[i]->getGlobalPosition()[1];
		PosZ = sphere[i]->getGlobalPosition()[2];
		if (sqrt(PosX*PosX + PosZ * PosZ) > outerCylinderD / 2 || PosY > cylinderH)
		{
			gScene->releaseActor(*sphere[i]);
			sphere[i] = NULL;
			continue;
		}
		sphere[i]->raiseBodyFlag(NX_BF_FROZEN_ROT);
		sphere[i]->raiseBodyFlag(NX_BF_FROZEN_POS);
	}

	/*Delete cylinders*/
	gScene->releaseActor(*OutCylinder);
	OutCylinder = NULL;
	gScene->releaseActor(*InCylinder);
	InCylinder = NULL;

	was_frozen = true;
}

void ProcessInputs()
{
	//	ProcessForceKeys();
	if (bDeleteActors)
		if (gScene)
		{
			freeze_objects();
			bDeleteActors = false;
		}

	// Show debug wireframes
	if (bDebugWireframeMode)
	{
		if (gScene)  gDebugRenderer.renderData(*gScene->getDebugRenderable());
	}
}

void RenderCallback()
{
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ProcessCameraKeys();
	SetupCamera();
	if (gScene && !bPause)
	{
		GetPhysicsResults();
		ProcessInputs();
		StartPhysics();
	}


	// Display scene
	RenderActors(bShadows);
	DrawForce(gSelectedActor, gForceVec, NxVec3(1, 1, 0));
	gForceVec = NxVec3(0, 0, 0);

	// Render the HUD
	hud.Render();

	glFlush();
	glutSwapBuffers();
}

void ReshapeCallback(int width, int height)
{
	glViewport(0, 0, width, height);
	gCameraAspectRatio = float(width) / float(height);
}

void IdleCallback()
{
	glutPostRedisplay();
}

void KeyboardCallback(unsigned char key, int x, int y)
{
	gKeys[key] = true;

	switch (key)
	{
	case 'r': { SelectNextActor(); break; }
	default: { break; }
	}
}

void KeyboardUpCallback(unsigned char key, int x, int y)
{
	gKeys[key] = false;

	switch (key)
	{
	case 'p': { bPause = !bPause;
		if (bPause)
			hud.SetDisplayString(0, "Paused - Hit \"p\" to Unpause", 0.3f, 0.55f);
		else
			hud.SetDisplayString(0, "", 0.0f, 0.0f);
		getElapsedTime();
		break; }
	case 'x': { bShadows = !bShadows; break; }
	case 'b': { bDebugWireframeMode = !bDebugWireframeMode; break; }
	case ' ': { bDeleteActors = true; break; }
	case 27: { exit(0); break; }
	default: { break; }
	}
}

void SpecialCallback(int key, int x, int y)
{
	switch (key)
	{
	// Reset PhysX
	case GLUT_KEY_F10: ResetNx(); return;
	}
}

void MouseCallback(int button, int state, int x, int y)
{
	mx = x;
	my = y;
}

void MotionCallback(int x, int y)
{
	int dx = mx - x;
	int dy = my - y;

	gCameraForward.normalize();
	gCameraRight.cross(gCameraForward, NxVec3(0, 1, 0));

	NxQuat qx(NxPiF32 * dx * 20 / 180.0f, NxVec3(0, 1, 0));
	qx.rotate(gCameraForward);
	NxQuat qy(NxPiF32 * dy * 20 / 180.0f, gCameraRight);
	qy.rotate(gCameraForward);

	mx = x;
	my = y;
}

void ExitCallback()
{
	ReleaseNx();
}

void InitGlut(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	gMainHandle = glutCreateWindow("Laboratory work ¹2. Filter");
	glutSetWindow(gMainHandle);
	glutDisplayFunc(RenderCallback);
	glutReshapeFunc(ReshapeCallback);
	glutIdleFunc(IdleCallback);
	glutKeyboardFunc(KeyboardCallback);
	glutKeyboardUpFunc(KeyboardUpCallback);
	glutSpecialFunc(SpecialCallback);
	glutMouseFunc(MouseCallback);
	glutMotionFunc(MotionCallback);
	MotionCallback(0, 0);
	atexit(ExitCallback);

	// Setup default render states
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);

	// Setup lighting
	glEnable(GL_LIGHTING);
	float AmbientColor[] = { 0.0f, 0.1f, 0.2f, 0.0f };         glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientColor);
	float DiffuseColor[] = { 0.2f, 0.2f, 0.2f, 0.0f };         glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseColor);
	float SpecularColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };         glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularColor);
	float Position[] = { 100.0f, 100.0f, -400.0f, 1.0f };  glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glEnable(GL_LIGHT0);
}


NxActor* CreateSphere(NxVec3 s)
{
	// Set the sphere starting height to 3.5m so box starts off falling onto the ground
	NxReal sphereStartHeight = 0;
	NxReal start_box_posX = s[0];
	NxReal start_box_posY = s[1];
	NxReal start_box_posZ = s[2];

	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;

	// The actor has one shape, a sphere, 1m on radius
	NxSphereShapeDesc sphereDesc;
	sphereDesc.radius = sphereDiameter / 2 + (float(rand() % int(sphereDiameterTolerance * 100))) / 100 - (float(rand() % int(sphereDiameterTolerance * 100))) / 100;
	sphereDesc.localPose.t = NxVec3(0, 0, 0);

	actorDesc.shapes.pushBack(&sphereDesc);
	actorDesc.body = &bodyDesc;
	actorDesc.density = 1.0f;
	actorDesc.globalPose.t = NxVec3(start_box_posX, start_box_posY, start_box_posZ);
	return gScene->createActor(actorDesc);
}

void CreateCloudSphere()
{
	int count_x_sphere = outerCylinderD / (sphereDiameter);
	int count_y_sphere = particlesH;
	int count_z_sphere = count_x_sphere;
	int startX = -count_x_sphere * sphereDiameter / 2;
	int startY = 3 * cylinderH;
	int startZ = startX;
	int count = 0;

	count_of_sphere = (count_y_sphere)*(count_z_sphere)*(count_x_sphere);
	spheres_pos = new float*[count_of_sphere];
	sphere = new NxActor*[count_of_sphere];

	for (int i = 0; i < count_of_sphere; i++)
		spheres_pos[i] = new float[3];
	srand(time(NULL));

	for (int i = 0; i < count_x_sphere; i++)
		for (int j = 0; j < count_y_sphere; j++)
			for (int k = 0; k < count_z_sphere; k++)
			{
				spheres_pos[count][0] = startX + k * (sphereDiameter + sphereDiameterTolerance);
				spheres_pos[count][1] = startY + j * (sphereDiameter + sphereDiameterTolerance);
				spheres_pos[count][2] = startZ + i * (sphereDiameter + sphereDiameterTolerance);
				count++;
			}

	for (int i = 0; i < count_of_sphere; i++)
		sphere[i] = CreateSphere(NxVec3(spheres_pos[i][0], spheres_pos[i][1], spheres_pos[i][2]));
}

void InitializeHUD()
{
	bHardwareScene = (gScene->getSimType() == NX_SIMULATION_HW);

	hud.Clear();

	// Add pause to HUD
	if (bPause)
		hud.AddDisplayString("Paused - Hit \"p\" to Unpause", 0.3f, 0.55f);
	else
		hud.AddDisplayString("", 0.0f, 0.0f);
}

NxActor* CreateGroundPlane()
{
	// Create a plane with default descriptor
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	return gScene->createActor(actorDesc);
}

NxActor* CreateInnerCylinder()
{
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;
	bodyDesc.flags |= NX_BF_KINEMATIC;

	// Pyramid
	NxVec3 verts[48];

	for (int i = 0, j = 0; i < 24; i++, j = j + 15)
	{
		verts[i] = NxVec3(innerCylinderD / 2 * cos(j * PI / 180), cylindersDelta, innerCylinderD / 2 * sin(j * PI / 180));
		verts[i + 24] = NxVec3(innerCylinderD / 2 * cos(j * PI / 180), cylinderH, innerCylinderD / 2 * sin(j * PI / 180));
	}


	// Create descriptor for convex mesh
	if (!convexDesc)
	{
		convexDesc = new NxConvexMeshDesc();
		assert(convexDesc);
	}
	convexDesc->numVertices = 48;
	convexDesc->pointStrideBytes = sizeof(NxVec3);
	convexDesc->points = verts;
	convexDesc->flags = NX_CF_COMPUTE_CONVEX;

	NxConvexShapeDesc convexShapeDesc;
	convexShapeDesc.localPose.t = NxVec3(0, 0, 0);
	convexShapeDesc.userData = convexDesc;

	// Two ways on cooking mesh: 1. Saved in memory, 2. Saved in file	
	NxInitCooking();

	// Cooking from memory
	MemoryWriteBuffer buf;
	bool status = NxCookConvexMesh(*convexDesc, buf);
	
	NxConvexMesh *pMesh = gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data));
	assert(pMesh);
	convexShapeDesc.meshData = pMesh;
	NxCloseCooking();

	if (pMesh)
	{
		// Save mesh in userData for drawing.
		pMesh->saveToDesc(*convexDesc);
		NxActorDesc actorDesc;
		assert(convexShapeDesc.isValid());
		actorDesc.shapes.pushBack(&convexShapeDesc);
		actorDesc.body = &bodyDesc;
		actorDesc.density = 1.0f;

		actorDesc.globalPose.t = NxVec3(0.0f, 0.0f, 0.0f);
		assert(actorDesc.isValid());
		NxActor* actor = gScene->createActor(actorDesc);
		assert(actor);
		return actor;
	}

	return NULL;
}

NxActor* CreateOuterCylinder()
{
	// Supply hull
	NxVec3 verts[48];
	for (int i = 0, j = 0; i < 24; i++, j = j + 15)
	{
		verts[i] = NxVec3(outerCylinderD / 2 * cos(j * PI / 180), 0, outerCylinderD / 2 * sin(j * PI / 180));
		verts[i + 24] = NxVec3(outerCylinderD / 2 * cos(j * PI / 180), cylinderH, outerCylinderD / 2 * sin(j * PI / 180));
	}

	// Triangles is 12*3
	NxU32 indices[48 * 3] =
	{ 1, 24, 0,
		1, 25, 24,
		2, 25, 1,
		2, 26, 25,
		3, 26, 2,
		3, 27, 26,
		4, 27, 3,
		4, 28, 27,
		5, 28, 4,
		5, 29, 28,
		6, 29, 5,
		6, 30, 29,
		7, 30, 6,
		7, 31, 30,
		8, 31, 7,
		8, 32, 31,
		9, 32, 8,
		9, 33, 32,
		10, 33, 9,
		10, 34, 33,
		11, 34, 10,
		11, 35, 34,
		12, 35, 11,
		12, 36, 35,
		13, 36, 12,
		13, 37, 36,
		14, 37, 13,
		14, 38, 37,
		15, 38, 14,
		15, 39, 38,
		16, 39, 15,
		16, 40, 39,
		17, 40, 16,
		17, 41, 40,
		18, 41, 17,
		18, 42, 41,
		19, 42, 18,
		19, 43, 42,
		20, 43, 19,
		20, 44, 43,
		21, 44, 20,
		21, 45, 44,
		22, 45, 21,
		22, 46, 45,
		23, 46, 22,
		23, 47, 46,
		0, 47, 23,
		0, 24, 47,
	};
	if (!triangleMeshDesc)
	{
		triangleMeshDesc = new NxTriangleMeshDesc();
		assert(triangleMeshDesc);
	}
	triangleMeshDesc->numVertices = 48;
	triangleMeshDesc->pointStrideBytes = sizeof(NxVec3);
	triangleMeshDesc->points = verts;
	triangleMeshDesc->numTriangles = 48;
	triangleMeshDesc->flags = 0;
	triangleMeshDesc->triangles = indices;
	triangleMeshDesc->triangleStrideBytes = 3 * sizeof(NxU32);


	// The actor has one shape, a triangle mesh
	NxInitCooking();
	MemoryWriteBuffer buf;

	bool status = NxCookTriangleMesh(*triangleMeshDesc, buf);
	NxTriangleMesh* pMesh;
	if (status)
	{
		pMesh = gPhysicsSDK->createTriangleMesh(MemoryReadBuffer(buf.data));
	}
	else
	{
		assert(false);
		pMesh = NULL;
	}
	NxCloseCooking();
	// Create TriangleMesh above code segment.

	NxTriangleMeshShapeDesc tmsd;
	tmsd.meshData = pMesh;
	tmsd.userData = triangleMeshDesc;
	tmsd.localPose.t = NxVec3(0, 0, 0);
	tmsd.meshPagingMode = NX_MESH_PAGING_AUTO;

	NxActorDesc actorDesc;
	NxBodyDesc  bodyDesc;
	assert(tmsd.isValid());
	actorDesc.shapes.pushBack(&tmsd);
	//Dynamic triangle mesh don't be supported anymore. So body = NULL
	actorDesc.body = NULL;
	//actorDesc.density = 10.0f;
	actorDesc.globalPose.t = NxVec3(0.0f, 0.0f, 0.0f);

	if (pMesh)
	{
		// Save mesh in userData for drawing
		pMesh->saveToDesc(*triangleMeshDesc);
		//
		assert(actorDesc.isValid());
		NxActor* pActor = gScene->createActor(actorDesc);
		assert(pActor);

		return pActor;
	}

	return NULL;
}

void InitNx()
{
	NxVec3 temp;
	// Initialize Camera Parameters
	gCameraAspectRatio = 1.0f;
	gCameraPos = NxVec3(0, 20, -70);
	gCameraForward = NxVec3(0, 0, 1);
	gCameraRight = NxVec3(-1, 0, 0);

	// Create a memory allocator
	if (!gAllocator)
	{
		gAllocator = new UserAllocator;
		assert(gAllocator);
	}

	// Create the physics SDK
	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, gAllocator);
	if (!gPhysicsSDK)  return;

	// Set the physics parameters
	gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.01);

	// Set the debug visualization parameters
	gPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_FNORMALS, 1);

	// Create the scene
	NxSceneDesc sceneDesc;
	sceneDesc.simType = NX_SIMULATION_SW;
	sceneDesc.gravity = gDefaultGravity;
	gScene = gPhysicsSDK->createScene(sceneDesc);
	if (!gScene)
	{
		sceneDesc.simType = NX_SIMULATION_SW;
		gScene = gPhysicsSDK->createScene(sceneDesc);
		if (!gScene) return;
	}

	// Create the default material
	NxMaterial* defaultMaterial = gScene->getMaterialFromIndex(0);
	defaultMaterial->setRestitution(0.75);
	defaultMaterial->setStaticFriction(0.5);
	defaultMaterial->setDynamicFriction(0.5);
	// Create the objects in the scene
	groundPlane = CreateGroundPlane();
	CreateCloudSphere();
	OutCylinder = CreateOuterCylinder();
	InCylinder = CreateInnerCylinder();
	InitializeHUD();
	// Get the current time
	getElapsedTime();

	// Start the first frame of the simulation
	if (gScene)  StartPhysics();
}


void ReleaseNx()
{
	GetPhysicsResults();  // Make sure to fetchResults() before shutting down  

	if (convexDesc)
	{
		delete convexDesc;
		convexDesc = NULL;
	}

	if (triangleMeshDesc)
	{
		delete triangleMeshDesc;
		triangleMeshDesc = NULL;
	}

	if (concaveDesc)
	{
		delete concaveDesc;
		concaveDesc = NULL;
	}

	if (gScene)
	{
		gPhysicsSDK->releaseScene(*gScene);
	}
	if (gPhysicsSDK)  gPhysicsSDK->release();
}

void ResetNx()
{
	ReleaseNx();
	InitNx();
	was_frozen = false;
}

void StartPhysics()
{
	// Update the time step
	gDeltaTime = getElapsedTime();

	// Start collision and dynamics for delta time since the last frame
	gScene->simulate(gDeltaTime);
	gScene->flushStream();
}

void GetPhysicsResults()
{
	// Get results from gScene->simulate(gDeltaTime)
	while (!gScene->fetchResults(NX_RIGID_BODY_FINISHED, false));
}

void print_config()
{
	printf("CONFIG:\n");
	printf("-----------------------------------\n");
	printf("sphereDiameter: %f\n", sphereDiameter);
	printf("sphereDiameterTolerance: %f\n", sphereDiameterTolerance);
	printf("innerCylinderD: %f\n", innerCylinderD);
	printf("outerCylinderD: %f\n", outerCylinderD);
	printf("cylinderH: %f\n", cylinderH);
	printf("cylindersDelta: %f\n", cylindersDelta);
	printf("particlesH: %f\n", particlesH);
	printf("-----------------------------------\n");
}

void get_config()
{
	TiXmlDocument doc("config.xml");
	TiXmlElement* xml_root = 0;
	TiXmlElement* xml_curr = 0;

	if (!doc.LoadFile())
	{
		printf("%s\n", doc.ErrorDesc());
		return;
	}

	TiXmlHandle docHandle(&doc);
	xml_root = docHandle.FirstChildElement("root").ToElement();

	xml_curr = xml_root->FirstChildElement("sphereDiameter");
	sphereDiameter = atof(xml_curr->GetText());

	xml_curr = xml_root->FirstChildElement("sphereDiameterTolerance");
	sphereDiameterTolerance = atof(xml_curr->GetText());

	xml_curr = xml_root->FirstChildElement("innerCylinderD");
	innerCylinderD = atof(xml_curr->GetText());

	xml_curr = xml_root->FirstChildElement("outerCylinderD");
	outerCylinderD = atof(xml_curr->GetText());

	xml_curr = xml_root->FirstChildElement("cylinderH");
	cylinderH = atof(xml_curr->GetText());

	xml_curr = xml_root->FirstChildElement("cylindersDelta");
	cylindersDelta = atof(xml_curr->GetText());

	xml_curr = xml_root->FirstChildElement("particlesH");
	particlesH = atof(xml_curr->GetText());
}

int main(int argc, char** argv)
{
	get_config();
	print_config();
	PrintControls();
	InitGlut(argc, argv);
	InitNx();
	glutMainLoop();
	ReleaseNx();
	return 0;
}