#pragma once

#include <GL/glew.h>

#include "common.h"
#include "component.h"

Component* CreateQuadMeshComponent();
GLfloat* GetVertices(Component* meshComponent);
int GetVertexCount(Component* meshComponent);
GLint* GetIndices(Component* meshComponent);
int GetIndexCount(Component* meshComponent);


//Mesh* generatePlaneMesh(int width, int length);
//Mesh* updateNormals(Mesh* mesh);
//Mesh* applyHeightMap(Mesh* mesh, float* heightMap);