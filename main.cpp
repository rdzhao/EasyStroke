#include "stroke.h"
#include <fstream>

int main()
{
	vector<float> v, n;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
		v.push_back(0);
		v.push_back(0);

		n.push_back(0);
		n.push_back(0);
		n.push_back(1);
	}

	Stroke s(1, v, n);
	s.constructStroke();

	vector<float> sv;
	vector<size_t> sf;
	sv = s.strokeVerts();
	sf = s.strokeFaces();

	ofstream out("ribbon.obj");
	
	for (int i = 0; i < sv.size() / 3; ++i) {
		out << "v "
			<< sv[3 * i] << " "
			<< sv[3 * i + 1] << " "
			<< sv[3 * i + 2] << endl;
	}

	for (int i = 0; i < sf.size() / 3; ++i) {
		out << "f "
			<< sf[3 * i] + 1 << " "
			<< sf[3 * i + 1] + 1 << " "
			<< sf[3 * i + 2] + 1 << endl;
	}
}