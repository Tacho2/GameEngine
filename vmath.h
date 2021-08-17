#pragma once
#include <glad/glad.h>
#include "Matrix.h"
#include "vec4.h"
#include "Quaternion.h"
#include <iostream>


class vmath 
{
	private:
		float projectionMatrix[16] = {};
		//get all the matrixes into the system
		//	-projection matrix
		//	-
		//need to make getters for each projection matrix
		
		//for now we will have hardcoded projection matricies with no camera class, thats a feature for another day i think
		// but we need inputs for transformations, rotations and scaling, but i think we should do those with quaternions
			//either way those values need to be inputable

		//we need input for the tranformation of the gl_position to world space as input
		//we will hardcode the projection values, camera class is next step i think
		float completedTransformMatrix; 
		

	public:
		vmath();
		~vmath();
		//Matrix multiplyMatricies(Matrix a, Matrix b);	
		void log();
		int* buildTransformationMatrix(float sx, float sy, float sz, float rx, float ry, float rz, float tx, float ty, float tz);
		int* buildViewMatrix();
		int* buildProjectionMatrix();
};

