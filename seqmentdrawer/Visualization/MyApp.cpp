#include "MyApp.h"
#include "../Utils/GLUtils.hpp"

#include <GL/GLU.h>

Visualization::Visualization(void)
{
	vaoID = 0;
	vboID = 0;
	
	LineVaoID = 0;
	LineVboID = 0;

	LinePointsVaoID = 0;
	LinePointsVboID = 0;

	programID = 0;

}

Visualization::~Visualization(void)
{
	Clean();
}

bool Visualization::Init()
{

	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);

	AddShaders();
	GetsegmentPoints(glm::vec2(-10,-5),glm::vec2(3,-2));
	CreateXAndY();
	CreateXAndYPoints();

	return true;
}

void Visualization::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--------------------------------------------------------

	glUseProgram(programID);

	switch (request._event)
	{
	case NEWSEGMENT:
		GetsegmentPoints(request.first, request.second);
		break;
	case NEWWIDTHORUNIT:
		width = request.width;
		if (MOREUNIT != request.units)
		{
			MOREUNIT = request.units;
			GetsegmentPoints(request.first, request.second);
		}
	}


	DrawXAndY();
	DrawXAndYPoints();
	DrawSegment();

	glUseProgram(0);

}

void Visualization::GetsegmentPoints(const glm::vec2& first, const glm::vec2& second)
{
	int db;
	float MX, MY, M = 1;
	
	float difX = second.x - first.x;
	float difY = second.y - first.y;

	db = (int)(std::abs(difX) * MOREUNIT);
	
	if (db < difY)
	{
		db = (int)(std::abs(difY) * MOREUNIT);
	}

	if (db == 0) return;

	MX = difX / (float)db ;
	MY = difY / (float)db ;

	std::vector<glm::vec2> vertexes;
	float X = first.x, Y = first.y;
	
	for (int i = 0; i <= db;++i)
	{
		vertexes.push_back( glm::vec2(X , Y ) );
		X += MX;
		Y += MY;
	}
	PointCount = (int)vertexes.size();

	//************************************//

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(glm::vec2), &vertexes[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);	//pos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

	glBindVertexArray(0);	//vao leszedése
	glBindBuffer(GL_ARRAY_BUFFER, 0);	//vbo leszedése
}

void Visualization::DrawSegment()
{
	glBindVertexArray(vaoID);

	glm::mat4 mvp = m_matProj * m_matView;

	glUniformMatrix4fv(m_loc_mvp, 1, GL_FALSE, &(mvp[0][0]));
	glUniform3f(LineColor, 0, 1, 0);
	glPointSize(width);

	glDrawArrays(GL_POINTS, 0, PointCount);
}

void Visualization::CreateXAndY()
{
	std::vector<glm::vec2> vertexes;

	vertexes.push_back(glm::vec2(-100, 0));
	vertexes.push_back(glm::vec2(0, 0));
	vertexes.push_back(glm::vec2(100, 0));
	vertexes.push_back(glm::vec2(0, 0));
	vertexes.push_back(glm::vec2(0, 100));
	vertexes.push_back(glm::vec2(0, 0));
	vertexes.push_back(glm::vec2(0, -100));

	glGenVertexArrays(1, &LineVaoID);
	glGenBuffers(1, &LineVboID);

	glBindVertexArray(LineVaoID);
	glBindBuffer(GL_ARRAY_BUFFER, LineVboID);

	glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(glm::vec2), &vertexes[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);	//pos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

	glBindVertexArray(0);	//vao leszedése

	glBindBuffer(GL_ARRAY_BUFFER, 0);	//vbo leszedése
}

void Visualization::CreateXAndYPoints()
{
	std::vector<glm::vec2> vertexes;

	for (int i = 0; i < 200;++i)
	{
		vertexes.push_back(glm::vec2(i - 100, 0));
		vertexes.push_back(glm::vec2(0, i - 100));
	}

	glGenVertexArrays(1, &LinePointsVaoID);
	glGenBuffers(1, &LinePointsVboID);

	glBindVertexArray(LinePointsVaoID);
	glBindBuffer(GL_ARRAY_BUFFER, LinePointsVboID);

	glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(glm::vec2), &vertexes[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);	//pos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

	glBindVertexArray(0);	//vao leszedése

	glBindBuffer(GL_ARRAY_BUFFER, 0);	//vbo leszedése
}

void Visualization::DrawXAndY()
{
	glBindVertexArray(LineVaoID);

	glm::mat4 mvp = m_matProj * m_matView;

	glUniformMatrix4fv(m_loc_mvp, 1, GL_FALSE, &(mvp[0][0]));
	glLineWidth(0.5f);
	glUniform3f(LineColor, 1, 0, 0);

	glDrawArrays(GL_LINE_STRIP, 0, 7);

}

void Visualization::DrawXAndYPoints()
{
	glBindVertexArray(LinePointsVaoID);

	glm::mat4 mvp = m_matProj * m_matView;

	glUniformMatrix4fv(m_loc_mvp, 1, GL_FALSE, &(mvp[0][0]));

	glPointSize(2.0f);
	glUniform3f(LineColor, 1, 1, 0);

	glDrawArrays(GL_POINTS, 0, 400);

}


void Visualization::AddShaders()
{
	GLuint vs_ID = loadShader(GL_VERTEX_SHADER, "Shaders/vert_2d.vert");
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER, "Shaders/frag_2d.frag");

	programID = glCreateProgram();

	glAttachShader(programID, vs_ID);
	glAttachShader(programID, fs_ID);

	glBindAttribLocation(programID, 0, "vs_in_pos");
	
	glLinkProgram(programID);

	glDeleteShader(vs_ID);
	glDeleteShader(fs_ID);

	m_matProj = glm::perspective(45.0f, 800 / 600.0f, 0.01f, 1000.0f);

	m_loc_mvp = glGetUniformLocation(programID, "MVP");
	LineColor = glGetUniformLocation(programID, "COLOR");

}

void Visualization::Update()
{
	m_matView = glm::lookAt(c.GetEye(), c.GetAt(), c.GetUp());

	request = ui.GetRequest();
}

void Visualization::KeyboardDown(SDL_KeyboardEvent& key)
{
	switch (key.keysym.sym){
	case SDLK_w:	//camera
		c.Add(c.GetVertUnit());
		break;
	case SDLK_s:
		c.Sub(c.GetVertUnit());
		break;
	case SDLK_a:
		c.Add(c.GetCameraUnit());
		break;
	case SDLK_d:
		c.Sub(c.GetCameraUnit());
		break;
	}
}

void Visualization::MouseWheel(SDL_MouseWheelEvent& wheel)
{
	wheel.y > 0 ? (c.Add(c.GetZoomUnit())) : (c.Sub(c.GetZoomUnit()));
}

void Visualization::Clean()
{
	glDeleteBuffers(1, &vaoID);
	glDeleteBuffers(1, &vboID);

	glDeleteBuffers(1, &LineVaoID);
	glDeleteBuffers(1, &LineVboID);

	glDeleteBuffers(1, &LinePointsVaoID);
	glDeleteBuffers(1, &LinePointsVboID);

	glDeleteProgram(programID);
}
void Visualization::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);

	m_matProj = glm::perspective(45.0f, _w / (float)_h, 0.01f, 1000.0f);
}