#pragma once

#include <GL/glew.h>

#include <vector>

#include <SDL.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Utils/CameraAndLight.h"
#include "../UI/request.h"
#include "../UI/userinterface.hpp"

class Visualization
{
public:
	Visualization(void);
	~Visualization(void);

	bool Init();
	void Clean();

	void Update();
	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);

	void Resize(int, int);

protected:
	
	//Camera
	Camera c;

	//------------------------------------------
	//Events
	Request request;
	UserInterface ui;

	//------------------------------------------
	// DRAWING
	
	int MOREUNIT = 1;

	void GetsegmentPoints(const  glm::vec2&, const  glm::vec2&);
	void DrawSegment();
	void CreateXAndY();
	void DrawXAndY();
	void CreateXAndYPoints();
	void DrawXAndYPoints();

	int PointCount;
	float width = 4.0f;
	//--------------------------------------------
	// IDs
	GLuint programID;

	GLuint vaoID, vboID;
	GLuint LineVaoID, LineVboID;
	GLuint LinePointsVaoID, LinePointsVboID;

	// IDs of shader variables
	GLuint m_loc_mvp;
	GLuint LineColor;
	//----------------------------------------------

	//transformation matrix
	glm::mat4 m_matView;
	glm::mat4 m_matProj;

	//----------------------------------------------
	// Structure
	void AddShaders();

};
