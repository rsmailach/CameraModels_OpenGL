//
// camera.cpp
//
// Created by Rachel Mailach 2015
// Copyright (c) 2015 Rachel Mailach. All rights reserved.
//
#include <iostream>
#include "camera.h"

using namespace mathFuncs3D;
using namespace std;

mathFunctions mathFuncs;

Camera::Camera() 
{

}

void Camera::LookAt() const
{
	gluLookAt(
		camera_position[0], camera_position[1], camera_position[2],
		camera_centre[0], camera_centre[1], camera_centre[2],
		0, 1, 0
		);
}

void Camera::moveForward()
{	
	point3D* cameraPos = new point3D(camera_position[0], camera_position[1], camera_position[2]);

	//Create movement Vector between camera and origin
	movementVector = mathFuncs.createVector(cameraPos, origin);

	//Normailize the vector
	movementVector = mathFuncs.normalize(movementVector);
	switch (cameraID)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			camera_position[0] += movementAmount;
			camera_position[2] += movementAmount;
			break;
		case 4:
			camera_position[0] += (movementVector->x * movementAmount);
			camera_position[1] += (movementVector->y * movementAmount);
			camera_position[2] += (movementVector->z * movementAmount);
			if (camera_position[0] <= 0.85)
				camera_position[0] = 0.85;
			if (camera_position[1] <= 0.85)
				camera_position[1] = 0.85;
			if (camera_position[2] <= 0.85)
				camera_position[2] = 0.85;

			//cout << camera_position[0] << ", " << camera_position[1] << ", " << camera_position[2] << endl;
			break;
		case 5:
			break;
	}
}
void Camera::moveBackward()
{
	switch (cameraID)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		camera_position[0] -= movementAmount;
		camera_position[2] -= movementAmount;
		break;
	case 4:
		//BREAKS SOMETIMES...?
		camera_position[0] -= (movementVector->x * movementAmount);
		camera_position[1] -= (movementVector->y * movementAmount);
		camera_position[2] -= (movementVector->z * movementAmount);
		break;
	case 5:
		break;
	}
}
void Camera::strafeRight()
{
	switch (cameraID)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		camera_position[0] += movementAmount;
		camera_position[2] += movementAmount;
		break;
	case 4://///////////DOESNT USE UPDATED POSITION
		angleY += movementAmount;
		camera_position[0] = camera_radius*sin(angleY);
		camera_position[2] = camera_radius*cos(angleY);
		//cout << camera_position[0] << ", " << camera_position[1] << ", " << camera_position[2] << endl;
		break;
	case 5:
		break;
	}
}
void Camera::strafeLeft()
{
	switch (cameraID)
	{
	case 1:
		camera_centre[0] += movementAmount;
		camera_centre[2] += movementAmount;
		break;
	case 2:
		break;
	case 3:
		camera_position[0] -= movementAmount;
		camera_position[2] -= movementAmount;
		break;
	case 4:
		angleY -= movementAmount;
		camera_position[0] = camera_radius*sin(angleY);
		camera_position[2] = camera_radius*cos(angleY);
		break;
	case 5:
		break;
	}
}
void Camera::moveUp()
{
	switch (cameraID)
	{
	case 1:
		camera_centre[1] += movementAmount;
		break;
	case 2:
		break;
	case 3:
		camera_position[1] += movementAmount;
		break;
	case 4:
		angleZ -= movementAmount;
		//camera_position[0] = camera_radius*sin(angleY);
		camera_position[1] = camera_radius*cos(angleZ);
		camera_position[2] = camera_radius*cos(angleY);
		break;
	case 5:
		break;
	}
}
void Camera::moveDown()
{
	switch (cameraID)
	{
	case 1:
		angleZ += movementAmount;
		//camera_centre[0] = camera_radius*sin(angleY);
		camera_centre[1] = camera_radius*cos(angleZ);
		//camera_centre[2] = camera_radius*cos(angleY);
		break;
	case 2:
		break;
	case 3:
		camera_position[1] -= movementAmount;
		if (camera_position[1] == 0.5f)
			camera_position[1] = 0.5f;
		break;
	case 4:
		angleZ += movementAmount;
		//camera_position[0] = camera_radius*sin(angleY);
		camera_position[1] = camera_radius*cos(angleZ);
		camera_position[2] = camera_radius*cos(angleY);
		break;
	case 5:
		break;
	}
}

void Camera::updateFPSPos(float x, float y, float z)
{
	if (cameraID == 1)
	{
		camera_position[0] = x;
		camera_position[1] = y;
		camera_position[2] = z;
	}
}

void Camera::firstPerson(float x, float y, float z)
{
	cameraID = 1;
	angleY = M_PI/4;
	angleZ = M_PI/4;

	camera_radius = 4.0;

	camera_rotation[0] = 0.0f;
	camera_rotation[1] = 0.0f;

	camera_position[0] = x;
	camera_position[1] = y;
	camera_position[2] = z;

	camera_centre[0] = camera_radius*sin(angleY);
	camera_centre[1] = camera_radius*cos(angleZ);
	camera_centre[2] = camera_radius*cos(angleY);
}
void Camera::thirdPerson()
{
	cameraID = 2;
}
void Camera::topDown()
{
	cameraID = 3;

	camera_radius = 10.0f;
	//angleY =   M_PI / 2.0f;
	//angleZ = M_PI / 2;

	camera_centre[0] = 0.0f;
	camera_centre[1] = 0.0f;
	camera_centre[2] = 0.0f;
	
	camera_position[0] = camera_radius * sin(M_PI / 2.0f);
	camera_position[1] = camera_radius;
	camera_position[2] = camera_radius *cos(M_PI / 2.0f);
}
void Camera::isometric()
{
	cameraID = 4;
	//r = 10 * sqrt(2.0);
	angleY = M_PI / 4;
	angleZ = M_PI / 4;

	camera_centre[0] = 0.0f;
	camera_centre[1] = 0.0f;
	camera_centre[2] = 0.0f;

	camera_radius = 10 * sqrt(2.0);

	camera_rotation[0] = 0.0f;
	camera_rotation[1] = 0.0f;

	camera_position[0] = camera_radius*sin(angleY);
	camera_position[1] = camera_radius*cos(angleZ);
	camera_position[2] = camera_radius*cos(angleY);
}
void Camera::freeRoaming()
{
	cameraID = 5;
}