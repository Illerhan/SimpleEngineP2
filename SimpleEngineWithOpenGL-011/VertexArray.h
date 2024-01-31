#pragma once

constexpr float spriteVertices[] = {
	-0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, // top left
	 0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, // top right
	 0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, // bottom right
	-0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f  // bottom left
};

constexpr unsigned int indices[] = {
	0,1,2,
	2,3,0
};

class VertexArray
{
public:
	VertexArray(const float* verticesP, unsigned int nbVeticesP, const unsigned int* indicesP, unsigned int nbIndicesP);
	~VertexArray();

	void setActive();

	unsigned int getNbVetices() const { return nbVertices; }
	unsigned int getNbIndices() const { return nbIndices; }
private:
	unsigned int nbVertices;
	unsigned int nbIndices;

	// OpenGL ID of the vertex array object
	unsigned int vertexArray;
	// OpenGL ID of the vertex buffer
	unsigned int vertexBuffer;
	// OpenGl ID of the index buffer
	unsigned int indexBuffer;
};

