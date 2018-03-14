#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "glm/glm.hpp"

using namespace std;
using namespace glm;

class Stroke
{
public:
	Stroke() {}
	Stroke(vector<vec3> v, vector<vec3> n, float hw, float r = 0.3)
		: m_verts(v), m_normals(n), m_halfwidth(hw), m_ratio(r) {}

	void buildStroke(){
		checkValidation();

		vector<vec3> armVerts;
		for (int i = 1; i < m_verts.size() - 1; ++i) {
			armVerts.push_back(m_verts[i] + m_halfwidth*arm(i));
			armVerts.push_back(m_verts[i] - m_halfwidth*arm(i));
		}

		m_strokeVerts.insert(m_strokeVerts.end(), m_verts.begin(), m_verts.end());
		m_strokeVerts.insert(m_strokeVerts.end(), armVerts.begin(), armVerts.end());

		for (int i = 0; i < m_verts.size() - 1; ++i) {
			if (i == 0) {
				m_strokeFaces.push_back(ivec3(i + 1, i, m_verts.size() + 2 * i));
				m_strokeFaces.push_back(ivec3(i, i + 1, m_verts.size() + 2 * i + 1));
			}
			else if (i == m_verts.size() - 2) {
				m_strokeFaces.push_back(ivec3(i + 1, i, m_verts.size() + 2 * (i - 1)));
				m_strokeFaces.push_back(ivec3(i, i + 1, m_verts.size() + 2 * (i - 1) + 1));
			}
			else {
				m_strokeFaces.push_back(ivec3(i + 1, i, m_verts.size() + 2 * i));
				m_strokeFaces.push_back(ivec3(i, i + 1, m_verts.size() + 2 * i + 1));

				m_strokeFaces.push_back(ivec3(i, m_verts.size() + 2 * (i - 1), m_verts.size() + 2 * i));
				m_strokeFaces.push_back(ivec3(i, m_verts.size() + 2 * i + 1, m_verts.size() + 2 * (i - 1) + 1));
			}
		}
	}

	vector<vec3>& strokeVerts() { return m_strokeVerts; }
	vector<ivec3>& strokeFaces() { return m_strokeFaces; }

private:
	void checkValidation() {
		if (m_verts.size() < 3)
			cerr << "Error: vertices size < 3" << endl;
	}

	vec3 arm(int i) {
		vec3 df = m_verts[i + 1] - m_verts[i];
		vec3 db = m_verts[i - 1] - m_verts[i];
		//cout << i<<" "<<df.x << " " << df.y << " " << df.z << endl;
		vec3 uf = normalize(cross(df, m_normals[i]));
		vec3 ub = normalize(cross(m_normals[i], db));
		cout << i << " " << uf.x << " " << uf.y << " " << uf.z << endl;
		cout << i << " " << ub.x << " " << ub.y << " " << ub.z << endl;
		return normalize(uf + ub);
	}

private:
	float m_halfwidth;
	float m_ratio;
	vector<vec3> m_verts;
	vector<vec3> m_normals;

	vector<vec3> m_strokeVerts;
	vector<ivec3> m_strokeFaces;
};

