//
// camera.h
//
// Created by Rachel Mailach 2015
// Copyright (c) 2015 Rachel Mailach. All rights reserved.
//

#pragma once

#define _USE_MATH_DEFINES

#include "freeglut.h"
#include <glm/glm.hpp>
#include <math.h>
#include "math3D.h"

namespace mathFuncs3D {

	class Camera
	{
	public:
		double camera_centre[3];	//where camera is looking
		double camera_radius;
		double camera_rotation[2];
		double camera_position[3]; //where physical camera is located
		float movementAmount = 0.05;

		point3D* origin = new point3D(0, 0, 0);

		vec3D* movementVector;



		float r;
		float angleY;
		float angleZ;

		int cameraID;

		Camera();

		void LookAt() const;

		void moveForward();
		void moveBackward();
		void strafeLeft();
		void strafeRight();
		void moveUp();
		void moveDown();

		void updateFPSPos(float x, float y, float z);

		void firstPerson(float x, float y, float z);
		void thirdPerson();
		void topDown();
		void isometric();
		void freeRoaming();
	};
}