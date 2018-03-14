#pragma once

#include <vector>
#include <cmath>

using namespace std;

class Stroke
{
public:
	Stroke() {}
	Stroke(float w, vector<float> v, vector<float> n) :width(w), verts(v), normals(n) {}

	void constructStroke(){
		vector<float> armVerts; // fron 1 to size/3-1;

		for (int i = 1; i < verts.size() / 3 - 1; ++i){
			float x, y, z;
			arm(i, x, y, z);
			
			armVerts.push_back(verts[3 * i] + x);
			armVerts.push_back(verts[3 * i + 1] + y);
			armVerts.push_back(verts[3 * i + 2] + z);

			armVerts.push_back(verts[3 * i] - x);
			armVerts.push_back(verts[3 * i + 1] - y);
			armVerts.push_back(verts[3 * i + 2] - z);
		}

		m_strokeVerts.insert(m_strokeVerts.end(), verts.begin(), verts.end());
		m_strokeVerts.insert(m_strokeVerts.end(), armVerts.begin(), armVerts.end());

		for (int i = 0; i < verts.size()/3 - 1; ++i) {
			if (i == 0){
				m_strokeFaces.push_back(0);
				m_strokeFaces.push_back(1);
				m_strokeFaces.push_back(verts.size() / 3 + 1);

				m_strokeFaces.push_back(1);
				m_strokeFaces.push_back(0);
				m_strokeFaces.push_back(verts.size() / 3);
			}
			else if (i == verts.size() / 3 - 2) {
				m_strokeFaces.push_back(verts.size() / 3 - 1);
				m_strokeFaces.push_back(verts.size() / 3 - 2);
				m_strokeFaces.push_back(verts.size() / 3 + 2 * (verts.size() / 3 - 2) - 2);

				m_strokeFaces.push_back(verts.size() / 3 - 2);
				m_strokeFaces.push_back(verts.size() / 3 - 1);
				m_strokeFaces.push_back(verts.size() / 3 + 2 * (verts.size() / 3 - 2) - 1);
			}
			else {
				m_strokeFaces.push_back(i);
				m_strokeFaces.push_back(i+1);
				m_strokeFaces.push_back(verts.size() / 3 + 2 * i - 1);

				m_strokeFaces.push_back(i + 1);
				m_strokeFaces.push_back(verts.size() / 3 + 2 * i + 1);
				m_strokeFaces.push_back(verts.size() / 3 + 2 * i - 1);

				m_strokeFaces.push_back(i + 1);
				m_strokeFaces.push_back(i);
				m_strokeFaces.push_back(verts.size() / 3 + 2 * i - 2);

				m_strokeFaces.push_back(i + 1);
				m_strokeFaces.push_back(verts.size() / 3 + 2 * i - 2);
				m_strokeFaces.push_back(verts.size() / 3 + 2 * i);
			}
		}
	}

	vector<float>& strokeVerts() { return m_strokeVerts; }
	vector<size_t>& strokeFaces() { return m_strokeFaces; }

private:
	float length(){
		double l = 0;
		for (int i = 0; i < verts.size() / 3 - 1; ++i) {
			l += length(i);
		}
		return l;
	}

	float length(size_t i) {
		return sqrt((verts[3 * i + 3] - verts[3 * i])*(verts[3 * i + 3] - verts[3 * i])
			+ (verts[3 * i + 4] - verts[3 * i + 1])*(verts[3 * i + 4] - verts[3 * i + 1])
			+ (verts[3 * i + 5] - verts[3 * i + 2])*(verts[3 * i + 5] - verts[3 * i + 2]));
	}

	void arm(size_t i, float& x, float& y, float& z) {
		float dx, dy, dz, nx, ny, nz;
		dx = verts[3 * i + 3] - verts[3 * i];
		dy = verts[3 * i + 4] - verts[3 * i + 1];
		dz = verts[3 * i + 5] - verts[3 * i + 2];
		nx = normals[3 * i];
		ny = normals[3 * i + 1];
		nz = normals[3 * i + 2];
		
		float ax, ay, az;
		ax = dy*nz - dz*ny;
		ay = dz*nx - dx*nz;
		az = dx*ny - dy*nx;
		
		float al = sqrt(ax*ax + ay*ay + az*az);
		
		x = (ax / al)*(width / 2);
		y = (ay / al)*(width / 2);
		z = (az / al)*(width / 2);
	}
		

private:
	float width;
	vector<float> verts; // tripple, a list of vertices representing the line segments.
	vector<float> normals; // tripple, corresponding normals.
	
	vector<float> m_strokeVerts; 
	vector<size_t> m_strokeFaces;
};

