#include <glm/gtx/transform.hpp>
#include "../Globals.h"
#include "Light.h"

#define VERTEX_NUMBER 1

const GLfloat Light::vertices[] =
{
	//Position			Colour
	0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f
};

Light::Light(const glm::vec3 position) : Object(), position(position) { }

Light::~Light()
{
	if (set)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}

void Light::setup()
{
	if (!set)
	{
		//Generate containers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		//Bind VAO
		glBindVertexArray(VAO);

		//Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Setup the position vertex attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		glEnableVertexAttribArray(0);

		//Setup the texture vertex attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		set = true;
	}
}

void Light::render() const
{
	//Bind VAO
	simpleShader->use();
	glBindVertexArray(VAO);

	//Set line width
	simpleShader->setMat4("MVP", translate(vpMatrix, position));
	glDrawArrays(GL_POINTS, 0, VERTEX_NUMBER);

	//Unbind VAO
	glBindVertexArray(0);
}