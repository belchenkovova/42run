#include "mesh.h"

#include "engine/model/material.h"

using namespace		engine;

					model::mesh::mesh(
					vector<vertex> &vertices,
					vector<unsigned> &indices,
					unique_ptr<engine::model::material> &material)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vertex), this->vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, UV));

	for (int i = 0; i < number_of_bones; i++)
	{
		glVertexAttribPointer(3 + i, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(offsetof(vertex, bones) + offsetof(bone, id) + sizeof(float) * i));
		glEnableVertexAttribArray(3 + i);
	}

	for (int i = 0; i < number_of_bones; i++)
	{
		glVertexAttribPointer(3 + number_of_bones + i, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(offsetof(vertex, bones) + offsetof(bone, weight) + sizeof(float) * i));
		glEnableVertexAttribArray(3 + number_of_bones + i);
	}

	glBindVertexArray(0);
}