#include "stroke.h"
#include <fstream>

#define PI 3.14159265358979323

int main()
{
	vector<vec3> v, n;
	//for (int i = 0; i < 3; ++i) {
	//	v.push_back(vec3(i, 0, 0));
	//	n.push_back(vec3(0, 0, 1));
	//}


	for (int i = 0; i < 100; ++i) {
		v.push_back(vec3(2 * cos(i * 2 * PI / 20), 2 * sin(i * 2 * PI / 20), i / 10.0));
		n.push_back(vec3(cos(i * 2 * PI / 20), sin(i * 2 * PI / 20), 0));
	}

	Stroke s(v, n, 0.3);
	s.buildStroke();

	vector<vec3> sv;
	vector<ivec3> sf;
	sv = s.strokeVerts();
	sf = s.strokeFaces();

	ofstream out("ribbon.obj");
	
	for (int i = 0; i < sv.size(); ++i) {
		out << "v "
			<< sv[i].x << " "
			<< sv[i].y << " "
			<< sv[i].z << endl;
	}

	for (int i = 0; i < sf.size(); ++i) {
		out << "f "
			<< sf[i].x + 1 << " "
			<< sf[i].y + 1 << " "
			<< sf[i].z + 1 << endl;
	}
}