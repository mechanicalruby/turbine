#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cstdint>

#if PSP
#include <pspge.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#else
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

union Color {
	struct {
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char alpha;
	};
	unsigned int rgb_value;
};

struct Vertex {
	float u, v;
	unsigned int color;
	float x, y, z;
};

struct Rectangle {
	float x;
	float y;
	float width;
	float height;
};

template <class T> class Mesh {
public:
	Mesh() {
		clearData();
	}

	void clearData() {
		vertices.clear();
		indices.clear();
		vertices.shrink_to_fit();
		indices.shrink_to_fit();
	};

	// TODO: Take arguments ... please ... the psp needs its lines
	void draw() {
#if __linux__ || WIN32 || VITA
		glDrawArrays(GL_TRIANGLES, 0, 6);
#elif PSP
		sceGumDrawArray(GU_TRIANGLES, GU_INDEX_16BIT | GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, indices.size(), indices.data(), vertices.data());
#endif
	}

	std::vector<T> vertices;
	std::vector<uint16_t> indices;
};

template <class T, size_t V, size_t I> class FixedMesh {
public:
	FixedMesh() {
		for (int i = 0; i < V; i++)
			vertices[i] = { 0 };

		for (int i = 0; i < I; i++)
			indices[i] = 0;
	}

	void draw() {
#if __linux__ || WIN32 || VITA
		glDrawArrays(GL_TRIANGLES, 0, 6);
#elif PSP
		sceGumDrawArray(GU_TRIANGLES, GU_INDEX_16BIT | GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, indices.size(), indices.data(), vertices.data());
#endif
	}

	std::array<T, V> vertices;
	std::array<uint16_t, I> indices;
};
