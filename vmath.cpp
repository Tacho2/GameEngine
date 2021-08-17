#include "vmath.h"

vmath::vmath()
{
	//completedTransformMatrix = 0;// multiply all given matrixes
};
vmath::~vmath() {};

void vmath::log() {
	std::cout << "hello world" << std::endl;
}

int* vmath::buildTransformationMatrix(float sx, float sy, float sz, float rx, float ry, float rz, float rangle, float tx, float ty, float tz) {
	// scaling diag with 1 in 4,4
	// rotaions
		// convert form euler angles to quaternions or just use quaternions? maybe both methods? idk
	// translations
}

int* vmath::buildViewMatrix() {

}

int* vmath::buildProjectionMatrix() {

}