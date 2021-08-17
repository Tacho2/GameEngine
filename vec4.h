#pragma once


class vec4 {

private:
	float x;
	float y;
	float z;
	float w;
public:
	vec4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {}
	~vec4();

};
