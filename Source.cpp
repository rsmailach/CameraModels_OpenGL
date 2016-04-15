//
// Sourece.cpp
// Camera modeling program
//
// Created by Rachel Mailach 2015
// Copyright (c) 2015 Rachel Mailach. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "freeglut.h"
#include <iostream>
#include "camera.h"

#define WIDTH 800
#define HEIGHT 800

using namespace mathFuncs3D;
using namespace std;

//mathFunctions mathFuncs;
Camera camera;
//bool keys[256];
float angle = 0.0f;				//Teapot angle for rotation
float size = 0.5f;
bool pauseAnimation = true;
bool toggle = true;
float cubeTranslateX = 0.0f;
float cubeTranslateY = 0.0f + (size/2.0f);
float cubeTranslateZ = 0.0f;
float animationShift = 0.0f;
float bodySize = 0.5f;
float armSize = bodySize / 4.0f;

///TEXTURE MAPPING
//an array for iamge data
GLubyte* snail_tex;
GLubyte* marble_tex;
int width, height, maxValue;
GLuint textures[2];

void coolGuy()
{
	glPushMatrix();
		glTranslatef(-2.0f, 0.0f, 0.0f);
		glPushMatrix();
			glTranslatef(0.0f, bodySize / 2.0f, 0.0f);
			glutSolidCube(bodySize);
		glPopMatrix();

		//right arm
		glPushMatrix();
			glTranslatef(bodySize / 2.0f, 2.0f*bodySize / 3.0f, 0.0f);
			glPushMatrix();
				//joint 1
				glTranslatef(0, 0, 0);
				glutSolidSphere(armSize, 5.0f, 5.0f);

				glPushMatrix();
				glTranslatef(armSize / 2.0f, 0.0f, 0.0f);
					//joint 2
					glTranslatef(0.0f, armSize*(2.0f), 0.05f + animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);

					//joint 3
					glTranslatef(0.0f, armSize*(2.0f), 0.05f + animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);

					//joint 4
					glTranslatef(0.0f, armSize*(2.0f), 0.05f + animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);

					//joint 5
					glTranslatef(0.0f, armSize*(2.0f), 0.05f + animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);

					//joint 6
					glTranslatef(0.0f, armSize*(2.0f), 0.05f + animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		//left arm
		glPushMatrix();
			glTranslatef(-bodySize / 2.0f, (2.0f)*bodySize / 3.0f, 0.0f);
			glPushMatrix();
				//joint 7
				glTranslatef(0, 0, 0);
				glutSolidSphere(armSize, 5.0f, 5.0f);

				glPushMatrix();
					glTranslatef(-armSize / 2.0f, 0.0f, 0.0f);
					//joint 8
					glTranslatef(0.0f, armSize*(2.0f), -0.05f - animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);

					//joint 9
					glTranslatef(0.0f, armSize*(2.0f), -0.05f - animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);

					//joint 10
					glTranslatef(0.0f, armSize*(2.0f), -0.05f - animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);

					//joint 11
					glTranslatef(0.0f, armSize*(2.0f), -0.05f - animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);

					//joint 12
					glTranslatef(0.0f, armSize*(2.0f), -0.05f - animationShift);
					glutSolidSphere(armSize, 5.0f, 5.0f);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();


}

void display()
{
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera.LookAt();

	//Draw plane
	glBegin(GL_QUADS);
		glVertex3f(-4, 0, -4);
		glVertex3f(-4, 0, 4);
		glVertex3f(4, 0, 4);
		glVertex3f(4, 0, -4);
	glEnd();

	//Draw the objects in the scene
	glPushMatrix();
		glRotatef(angle, 0, 1, 0);
		glTranslatef(2, size/2, 0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glutSolidTeapot(size);
	glPopMatrix();
	
	//Draw cube used for first and third person cameras
	glPushMatrix();
		glTranslatef(cubeTranslateX, cubeTranslateY, cubeTranslateZ);
		glutSolidCube(size + 0.5f);
	glPopMatrix();

	coolGuy();

	//Angle increment for animation
	if (pauseAnimation == false) {
		angle += 0.05;

		//cout << "ani: " << animationShift << endl;
		if (animationShift <= -(0.25f) || animationShift >= (0.25f))
			toggle = !toggle;
		if (toggle) {
			animationShift += 0.001f;
			//cout << "true" << endl;
		}
		if (!toggle) {
			animationShift -= 0.001f;
			//cout << "false" << endl;
		}
	}
	glutSwapBuffers();
}




void initLighting()
{
	GLfloat specular[]  = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess[] = { 50.0, 50.0, 50.0, 50.0 };
	GLfloat position[]  = { 1.0, 1.0, 1.0, 0.0 };
	
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void reshape(int width, int height)
{
	float ratio;
	//To avoid divide by zero error
	if (height == 0)
	{
		height = 1;
	}

	ratio = (float)width / (float)height;
	
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, ratio, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	//If the esc key is pressed, quit the program
	if (key == 27)
	{
		exit(0);
	}
	//If the spacebar is pressed, start animation
	if (key == 32)
	{
		pauseAnimation = !pauseAnimation;
	}
	switch (key)
	{
	//First-Person 
	case '1':
		std::cout << "First - Person Camera enabled" << std::endl;
		camera.firstPerson(cubeTranslateX + (size / 2.0f), cubeTranslateY, cubeTranslateZ + (size / 2.0f));
		break;

	//Third-Person
	case '2':
		std::cout << "Third - Person Camera enabled" << std::endl;
		camera.thirdPerson();
		break;

	//Top-Down
	case '3':
		std::cout << "Top - Down Camera enabled" << std::endl;
		camera.topDown();
		break;

	//Isometric
	case '4':
		std::cout << "Isometric Camera enabled" << std::endl;
		camera.isometric();
		break;

	//Free roaming
	case '5':
		std::cout << "Free Roaming Camera enabled" << std::endl;
		camera.freeRoaming();
		break;

	default:
		//std::cout << "Isometric Camera enabled" << std::endl;
		//camera.isometric();
		break;
	}
	if (key == 'w' || key == 'W')
		camera.moveForward();
	if (key == 'a' || key == 'A')
		camera.strafeLeft();
	if (key == 's' || key == 'S')
		camera.moveBackward();
	if (key == 'd' || key == 'D')
		camera.strafeRight();
	if (key == 'r' || key == 'R')
		camera.moveUp();
	if (key == 'f' || key == 'F')
		camera.moveDown();

	glutPostRedisplay();
}
/*
point3D *GetCubePosition()
{
	point3D * cubePos = new point3D(cubeTranslateX + (size / 2.0f), cubeTranslateY, cubeTranslateZ + (size / 2.0f));
	return cubePos;
}*/

void spckey(int key, int x, int y){
	//Arrow keys move camera
	if (key == GLUT_KEY_UP) {
		cubeTranslateZ -= 0.05f;
		camera.updateFPSPos(cubeTranslateX + (size / 2.0f), cubeTranslateY, cubeTranslateZ + (size / 2.0f));
	}
	if (key == GLUT_KEY_DOWN) {
		cubeTranslateZ += 0.05f;
		camera.updateFPSPos(cubeTranslateX + (size / 2.0f), cubeTranslateY, cubeTranslateZ + (size / 2.0f));
	}
	if (key == GLUT_KEY_RIGHT) {
		cubeTranslateX += 0.05f;
		camera.updateFPSPos(cubeTranslateX + (size / 2.0f), cubeTranslateY, cubeTranslateZ + (size / 2.0f));
	}
	if (key == GLUT_KEY_LEFT) {
		cubeTranslateX -= 0.05f;
		camera.updateFPSPos(cubeTranslateX + (size / 2.0f), cubeTranslateY, cubeTranslateZ + (size / 2.0f));
	}
}

void idle(void){
	glutPostRedisplay();
}

/* LoadPPM -- loads the specified ppm file, and returns the image data as a GLubyte
*  (unsigned byte) array. Also returns the width and height of the image, and the
*  maximum colour value by way of arguments
*/
GLubyte* LoadPPM(char* file, int* width, int* height, int* maxValue) {
	GLubyte* img;
	FILE *fd;
	int n, m;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;

	fd = fopen(file, "r");
	fscanf(fd, "%[^\n] ", b);
	if (b[0] != 'P' || b[1] != '3')     {
		printf("%s is not a PPM file!\n", file);
		exit(0);
	}

	fscanf(fd, "%c", &c);
	while (c == '#') {
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n", b);
		fscanf(fd, "%c", &c);
	}
	ungetc(c, fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);

	nm = n*m;

	//img = malloc(3*sizeof(GLuint)*nm);
	img = (GLubyte *)malloc(3 * sizeof(GLuint)*nm);

	s = 255.0 / k;

	for (i = 0; i<nm; i++) {
		fscanf(fd, "%d %d %d", &red, &green, &blue);
		img[3 * nm - 3 * i - 3] = red*s;
		img[3 * nm - 3 * i - 2] = green*s;
		img[3 * nm - 3 * i - 1] = blue*s;
	}

	*width = n;
	*height = m;
	*maxValue = k;

	return img;
}


void init(int w, int h)
{
	//enable texturing
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	//generate 2 texture IDs, store them in array "textures"
	glGenTextures(2, textures);

	
	//load the texture (snail)
	snail_tex = LoadPPM("snail_a.ppm", &width, &height, &maxValue);

	//setup first texture (using snail image)
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//create a texture using the "snail_tex" array data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, snail_tex);

	//load the texture (marble)
	marble_tex = LoadPPM("marble.ppm", &width, &height, &maxValue);

	//setup second texture (using marble image)
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	//set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//create a texture using the "tex" array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, marble_tex);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("SE 4GC3 Assignment 2");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 300);
	glFrustum(-200, 200, -200, 200, -200, 200);

	glEnable(GL_DEPTH_TEST);
	initLighting();

	cout << "CAMERA MODELS - 4GC3" << endl;
	cout << "Press spacebar to toggle animations" << endl;
	cout << "Press 3 or 4 to view top-down and isometric cameras" << endl;
	cout << "Press the WASD keys to move the camera" << endl;
	cout << "Press the arrow keys to move the cube" << endl;
	cout << "Press Esc to quit the application" << endl;
	cout << endl;

	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(spckey);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init(100, 100);
	camera.isometric(); //SET INITIAL CAM

	glutMainLoop();

	return 0;
}

/*
 *	TODO
 *	-ADD RESET BUTTON
 */

/* 
 * RESOURCES
 *	1. Lighting & window resizing
 *	http://www.glprogramming.com/red/chapter05.html
 *
 *	2. Camera
 *	http://stackoverflow.com/questions/10609743/how-do-i-implement-basic-camera-operations-in-opengl
 *	https://www.youtube.com/watch?v=HhXzKOMkA1k
 *
 *	4. Textures & PPM Loader
 *  Old project code from Dr. Teather's class
 * 
 *
 */