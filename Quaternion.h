#pragma once

class Quaternion {
private:
	float x;
	float y;
	float z;
	float w;

public:
	Quaternion(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {};
	~Quaternion();
};