/*
  Copyright (c) 2010 Marcos Slomp, Toru Tamaki

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation
  files (the "Software"), to deal in the Software without
  restriction, including without limitation the rights to use,
  copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following
  conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.
*/

#include <cstdio>
#include <algorithm>

#include "engine.h"
#include "freeglut.h"
#include "orbcam.h"

#define MAX_POINT_CLOUDS 3

int g_idWin (0);
orbcamera_t g_poCam (NULL);

bool winFlag (true);
bool g_KeyPressed (false);
bool updateFlag (false);

bool g_boMouseButtonLeft   (false);
bool g_boMouseButtonMiddle (false);
bool g_boMouseButtonRight  (false);
int g_nMouseLastX (0);
int g_nMouseLastY (0);

bool displayTexture=true;
bool displayMesh = true;

float *mRGB;
int **engineMesh;
float *mXYZ;
float *mNormals;
int nbEngineMesh=0;

float theta_x(0.0f), theta_y(0.0f), theta_z(0.0f), t_x(0.0f), t_y(0.0f), t_z(0.0f);


struct SPointCloud
{
  const float* points;
  int count;
  float color [3];
  float pointsize;
  bool visible;
};

SPointCloud g_vstPointClouds [MAX_POINT_CLOUDS] = { { NULL, 0, { 1.0f, 1.0f, 1.0f }, 1.0f, true } };

void OnClose()
{
  g_idWin = 0;
}

void initEngineRGB() {
	mRGB = new float[MAX_IMG_INDEX_3];
}
void setEngineRGB(float RGB, int i) {	
	mRGB[i] = RGB;
}
void freeEngineRGB() {
	delete[] mRGB;
}

void initEngineXYZ() {
	mXYZ = new float[MAX_IMG_INDEX_3];
}
void setEngineXYZ(float XYZ, int i) {	
	mXYZ[i] = XYZ;
}
void freeEngineXYZ() {
	delete[] mXYZ;
}

void initEngineNormals() {
	mNormals = new float[MAX_IMG_INDEX_3];
}
void setEngineNormals(float N, int i) {	
	mNormals[i] = N;
}
void freeEngineNormals() {
	delete[] mNormals;
}


void initEngineMesh(int nb_mesh) {
	engineMesh = new int *[3];
	for (int k=0; k<3; k++) 
		engineMesh[k] = new int[nb_mesh];
}
void setEngineMesh(int v1, int v2, int v3, int i) {	
	engineMesh[0][i] = v1;
	engineMesh[1][i] = v2;
	engineMesh[2][i] = v3;
}
void freeEngineMesh() {
	for (int k=0; k<3;k++)
		delete[] engineMesh[k];
	delete[] engineMesh;
}

void setNbEngineMesh(int nb) {
	nbEngineMesh = nb;
}




void OnRender()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//glEnable(GL_TEXTURE_2D);
	//GLuint  texture1;
	//glGenTextures(1, &texture1);
	//glBindTexture(GL_TEXTURE_2D, texture1);
	//glTexImage2D(GL_TEXTURE_2D, 0, texture1, XN_VGA_X_RES, XN_VGA_Y_RES, 0, GL_FLOAT, GL_FLOAT, mRGB);




  orbLoadOpenGLViewTransform(g_poCam);

	float color[3];
	float *curr=NULL;

	int icurr=0;
	int i2=0, i3=0, i4=0;
	int ic1=0, ic2=0, ic3=0, ic4=0;
	int i_first = THETA_MAX+1;
	int i_last = (THETA_MAX-2/*-CHIN_CUT*/)*Y_MAX-2;

	float R=0.0f, G=0.0f, B=0.0f;

  glEnableClientState(GL_VERTEX_ARRAY);
  for (int i=0; i<MAX_POINT_CLOUDS; i++)
  {
    SPointCloud& stPointCloud (g_vstPointClouds[i]);
    if (NULL != stPointCloud.points && false != stPointCloud.visible)
    {
      //glPointSize(stPointCloud.pointsize);
      //glColor3fv(stPointCloud.color);
	  //color[0]=1.0f; color[1]=color[2]=0.5f; 
	  //glColor3fv(color);
	  //glVertexPointer(3, GL_FLOAT, 0, stPointCloud.points);
      //glDrawArrays(GL_POINTS, 0, stPointCloud.count);

	  int k3=0;
	  //for (int k=0; k<MAX_IMG_INDEX_3; k+=3) {
	//for (int m=0; m<nbEngineMesh; m++) {

	  for (int i1=i_first; i1<i_last; i1++) {

		i2 = i1+1;				// x+1, y
		i3 = i1+THETA_MAX;		// x, y+1
		i4 = i3+1;				// x+1, y+1

		ic1 = 3*i1;
		ic2 = 3*i2;
		ic3 = 3*i3;
		ic4 = 3*i4;

		//glColor3f(1.0f, 0.0f, 0.0f);
		////glVertex3f(stPointCloud.points[k],stPointCloud.points[k+1],stPointCloud.points[k+2]);
		//color[0]=mRGB[k]; 
		//color[1]=mRGB[k+1]; 
		//color[2]=mRGB[k+2]; 
		//glColor3fv(color);
		//glVertexPointer(3, GL_FLOAT, 0, &stPointCloud.points[k]);
		//glDrawArrays(GL_POINTS, 0, 1);

		//glBegin(GL_TRIANGLES);
		//	glVertex3f(0.5f,-0.25f,0.0f);//triangle two first vertex
		//	glVertex3f(1.0f,-0.25f,0.0f);//triangle two second vertex
		//	glVertex3f(0.75f,0.25f,0.0f);//triangle two third vertex
		//glEnd();

	
		if (displayMesh) {
			if (displayTexture) {
				R = (mRGB[ic1]+mRGB[ic2]+mRGB[ic4])/3.0f;
				G = (mRGB[ic1+1]+mRGB[ic2+1]+mRGB[ic4+1])/3.0f;
				B = (mRGB[ic1+2]+mRGB[ic2+2]+mRGB[ic4+2])/3.0f;
			} else {
				R = G = B = 0.2f;
			}
			color[0]=R; 
			color[1]=G; 
			color[2]=B;
			//glColor3fv(color);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

			  if (	(mXYZ[i1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_2]!=0.0f)
			&&	(mXYZ[i2]!=0.0f || mXYZ[i2+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i2+MAX_IMG_INDEX_2]!=0.0f)
			&&	(mXYZ[i4]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_2]!=0.0f) ) {
				glBegin(GL_TRIANGLES);
					icurr = i1;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i2;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i4;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					//glVertex3f(1.0f,-0.25f,-1.0f);//triangle two second vertex
					//glVertex3f(0.75f,0.25f,-1.0f);//triangle two third vertex
				glEnd();

			}
			if (displayTexture) {
				R = (mRGB[ic1]+mRGB[ic2]+mRGB[ic4])/3.0f;
				G = (mRGB[ic1+1]+mRGB[ic2+1]+mRGB[ic4+1])/3.0f;
				B = (mRGB[ic1+2]+mRGB[ic2+2]+mRGB[ic4+2])/3.0f;
			} else {
				R = G = B = 0.2f;
			}
			color[0]=R; 
			color[1]=G; 
			color[2]=B; 
			//glColor3fv(color);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

			if (	(mXYZ[i1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_2]!=0.0f)
				&&	(mXYZ[i3]!=0.0f || mXYZ[i3+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i3+MAX_IMG_INDEX_2]!=0.0f)
				&&	(mXYZ[i4]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_2]!=0.0f) ) {
				glBegin(GL_TRIANGLES);
					icurr = i1;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i4;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i3;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					//glVertex3f(1.0f,-0.25f,-1.0f);//triangle two second vertex
					//glVertex3f(0.75f,0.25f,-1.0f);//triangle two third vertex
				glEnd();
			}
		}






		else {
			glLineWidth(1.0f); 
			if (displayTexture) {
				R = (mRGB[ic1]+mRGB[ic2]+mRGB[ic4])/3.0f;
				G = (mRGB[ic1+1]+mRGB[ic2+1]+mRGB[ic4+1])/3.0f;
				B = (mRGB[ic1+2]+mRGB[ic2+2]+mRGB[ic4+2])/3.0f;
			} else {
				R = G = B = 0.2f;
			}
			color[0]=R; 
			color[1]=G; 
			color[2]=B; 
			//glColor3fv(color);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

			if (	(mXYZ[i1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_2]!=0.0f)
				&&	(mXYZ[i2]!=0.0f || mXYZ[i2+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i2+MAX_IMG_INDEX_2]!=0.0f) ) {
				glBegin(GL_LINES); 
					icurr = i1;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i2;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);
				glEnd(); 
			}
			if (	(mXYZ[i4]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_2]!=0.0f)
				&&	(mXYZ[i2]!=0.0f || mXYZ[i2+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i2+MAX_IMG_INDEX_2]!=0.0f) ) {
				glBegin(GL_LINES); 
					icurr = i4;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i2;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);
				glEnd(); 
			}
			if (	(mXYZ[i4]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_2]!=0.0f)
				&&	(mXYZ[i1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_2]!=0.0f) ) {
				glBegin(GL_LINES); 
					icurr = i1;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i4;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);
				glEnd(); 
			}

			if (	(mXYZ[i3]!=0.0f || mXYZ[i3+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i3+MAX_IMG_INDEX_2]!=0.0f)
				&&	(mXYZ[i1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i1+MAX_IMG_INDEX_2]!=0.0f) ) {
				glBegin(GL_LINES); 
					icurr = i1;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i3;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);
				glEnd(); 
			}
			if (	(mXYZ[i4]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i4+MAX_IMG_INDEX_2]!=0.0f)
				&&	(mXYZ[i3]!=0.0f || mXYZ[i3+MAX_IMG_INDEX_1]!=0.0f || mXYZ[i3+MAX_IMG_INDEX_2]!=0.0f) ) {
				glBegin(GL_LINES); 
					icurr = i3;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);//triangle two first vertex
					
					icurr = i4;
					glNormal3f(mNormals[icurr],mNormals[icurr+MAX_IMG_INDEX_1],mNormals[icurr+MAX_IMG_INDEX_2]);
					glVertex3f(mXYZ[icurr],mXYZ[icurr+MAX_IMG_INDEX_1],mXYZ[icurr+MAX_IMG_INDEX_2]);
				glEnd(); 
			}
		
		}


	  }


		//= loadTexture("model\\imFront.jpg");
    }
  }
  glDisableClientState(GL_VERTEX_ARRAY);

  glutSwapBuffers();
}

void OnKeyPressed(unsigned char key, int,int)
{
  switch(key)
  {
    case 27 : // ESC
	case 'q':
	case 'Q':
      glutDestroyWindow(g_idWin);
      break;
	  //case 'q' :
	    //winFlag = false;
	    //break;
    case 'r' :
    case 'R' :
      orbSetOrbitalDistance(g_poCam, 2.0f);
      break;
	case 'm' :
    case 'M' :
		displayMesh = !displayMesh;
		break;

	case 't' :
    case 'T' :
		displayTexture = !displayTexture;
		break;

    case '1' :
    case '2' :
    case '3' :
      {
	unsigned int index = key - '1';
	if (index >= MAX_POINT_CLOUDS) break;
	SPointCloud& stPointCloud (g_vstPointClouds[index]);
	stPointCloud.visible = !stPointCloud.visible;
	break;
      }
    default:
      break;
  }

  g_KeyPressed = true;
}

void OnKeyReleased(unsigned char key, int,int)
{
  g_KeyPressed = false;
}

void OnMouseButtonPressed(int button)
{
  switch(button)
  {
    case GLUT_LEFT_BUTTON :
      g_boMouseButtonLeft = true;
      break;
    case GLUT_MIDDLE_BUTTON :
      g_boMouseButtonMiddle = true;
      break;
    case GLUT_RIGHT_BUTTON :
      g_boMouseButtonRight = true;
      break;
    default :
      break;
  };
}

void OnMouseButtonReleased(int button)
{
  switch(button)
  {
    case GLUT_LEFT_BUTTON :
      g_boMouseButtonLeft = false;
      break;
    case GLUT_MIDDLE_BUTTON :
      g_boMouseButtonMiddle = false;
      break;
    case GLUT_RIGHT_BUTTON :
      g_boMouseButtonRight = false;
      break;
    default :
      break;
  };
}

void OnMouseButton(int button, int state, int,int)
{
  switch(state)
  {
    case GLUT_DOWN :
      OnMouseButtonPressed(button);
      break;
    case GLUT_UP :
      OnMouseButtonReleased(button);
      break;
    default :
      // should never happen!
      break;
  }
}

void OnMouseMove(int x, int y)
{
  int dx = x-g_nMouseLastX;
  int dy = y-g_nMouseLastY;
  float theta;
  float stepsize;

  if (!g_KeyPressed) {

  if (g_boMouseButtonLeft)
  {
    if (dx != 0)
    {
      theta = ((const float)dx)*0.01f;
      orbOrbitHorizontally(g_poCam, theta);
    }

    if (dy != 0)
    {
      theta = ((const float)dy)*0.01f;
      orbOrbitVertically(g_poCam, theta);
    }
  }

  if (g_boMouseButtonRight)
  {
    if (dx != 0)
    {
      theta = ((const float)dx)*0.01f;
      orbRoll(g_poCam, theta);
    }
  }

  if (g_boMouseButtonMiddle)
  {
    if (dy != 0)
    {
      stepsize = ((const float)dy)*0.01f;
      orbZoom(g_poCam, stepsize);
    }
  }

  } else{

  if (g_boMouseButtonLeft)
  {
    if (dx != 0)
    {
      theta_x = ((const float)dx)*0.01f;
    }

    if (dy != 0)
    {
      theta_y = ((const float)dy)*0.01f;
    }
  }

  if (g_boMouseButtonRight)
  {
    if (dx != 0)
    {
      t_x = ((const float)dx)*0.001f;
    }

    if (dy != 0)
    {
      t_y = ((const float)dy)*0.001f;
    }
  }



  }

  g_nMouseLastX = x;
  g_nMouseLastY = y;
}

void OnMouseWheel(int, int direction, int,int)
{
  orbZoom(g_poCam, direction*0.05f);
}

void OnResize(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  const float fAspect ((const float)width / (const float) height);
  gluPerspective(60.0f, fAspect, 0.1f, 1000.0f);
}

void InitWindow()
{
	// The standard glut does not initialization, but freeglut breaks this rule.
	// Calling any freeglut function without prior initializing it causes a run-time error.
	// The following code performs a "dummy" initialization.
	int zero (0);
	glutInit(&zero, NULL);

	// Now everything proceeds like the old glut...
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	//glutInitWindowSize(512,512);
	glutInitWindowSize(900,900);
	g_idWin = glutCreateWindow("Model Viewer");
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);
	glutKeyboardFunc(OnKeyPressed);
	glutKeyboardUpFunc(OnKeyReleased);
	glutMouseFunc(OnMouseButton);
	glutMotionFunc(OnMouseMove);
	glutPassiveMotionFunc(OnMouseMove);
	// the following are freeglut-only!
	glutMouseWheelFunc(OnMouseWheel);
	glutCloseFunc(OnClose);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_AUTO_NORMAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	// Create light components
	float ambientLight0[] = { 0.125f, 0.125f, 0.125f, 0.2f };
	float diffuseLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specularLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float position0[] = { 0.0f, 0.0f, 2.0f, 1.0f };
	float lookat0[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	float position1[] = { 0.0f, 0.0f, -2.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lookat0);

	//glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight0);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight0);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight0);
	//glLightfv(GL_LIGHT1, GL_POSITION, position1);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lookat0);
	
	glEnable (GL_LINE_SMOOTH);
	glHint (GL_LINE_SMOOTH_HINT, GL_FASTEST );

	// COLOR OF THE BACKGROUND
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);

	// Very simple (but complete and effective) orbital camera "class".
	g_poCam = orbCreateCamera();
	orbSetOrbitalDistance(g_poCam, 2.0f);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 1);

	glShadeModel(GL_SMOOTH);
}

bool EngineInit()
{
  if (0 == g_idWin)
    InitWindow();
  return(true);
}

bool EngineShutDown()
{
  if (0 != g_idWin)
    glutDestroyWindow(g_idWin);
  g_idWin = 0;
  return(true);
}

void setWinFlag()
{
  winFlag = true;
}

bool isWinFlag()
{
  return winFlag;
}

bool isUpdated()
{
  return updateFlag;
}

bool EngineIteration()
{
  if (0 == g_idWin || !winFlag)
    return(false);

  glutPostRedisplay();
  glutMainLoopEvent();
  return(true);
}

#include <nvVector.h>
#include <nvMatrix.h>
#include <cmath>

bool EngineIteration(int Ysize, float* points2,
                     float* h_Y, const float* h_R, const float* h_t)
{


  float* h_Yx = &h_Y[0];
  float* h_Yy = &h_Y[Ysize];
  float* h_Yz = &h_Y[Ysize*2];


  // start add

  nv::matrix4<float>
    Rx(cos(theta_x), sin(theta_x), 0, 0,
       -sin(theta_x), cos(theta_x), 0, 0,
       0, 0, 1, 0,
       0, 0, 0, 0),
    Ry(cos(theta_y), 0, sin(theta_y), 0,
       0, 1, 0, 0,
       -sin(theta_y), 0, cos(theta_y), 0,
       0, 0, 0, 0),
    Rxy;
    Rxy = Rx * Ry;
  const float* R = Rxy.get_value();
  

  for (int i=0; i<Ysize; i++)
    {
      float point[3];
      point[0] = (R[0]*h_Yx[i] + R[1]*h_Yy[i] + R[ 2]*h_Yz[i]) + t_x;
      point[1] = (R[4]*h_Yx[i] + R[5]*h_Yy[i] + R[ 6]*h_Yz[i]) + t_y;
      point[2] = (R[8]*h_Yx[i] + R[9]*h_Yy[i] + R[10]*h_Yz[i]) + t_z;
      h_Yx[i] = point[0];
      h_Yy[i] = point[1];
      h_Yz[i] = point[2];
  }
  theta_x = theta_y = theta_x = t_x = t_y = t_z = 0.0f;



  // end add



  // Another point cloud:
  for (int i=0; i<Ysize; i++)
    {
      float* point = &points2[i*3];
      point[0] = (h_R[0]*h_Yx[i] + h_R[1]*h_Yy[i] + h_R[2]*h_Yz[i]) + h_t[0];
      point[1] = (h_R[3]*h_Yx[i] + h_R[4]*h_Yy[i] + h_R[5]*h_Yz[i]) + h_t[1];
      point[2] = (h_R[6]*h_Yx[i] + h_R[7]*h_Yy[i] + h_R[8]*h_Yz[i]) + h_t[2];
    }
  // The second point cloud has "index" 1.
  EnginePointCloudData(1, points2, Ysize);
  //EnginePointCloudDecoration(1, 0.0f, 1.0f, 1.0f, 2.0f);


  return EngineIteration();

}

bool EnginePointCloudData(const unsigned int index, const float* points, const int count)
{
  if (index >= MAX_POINT_CLOUDS)
    return(false);

  SPointCloud& stPointCloud (g_vstPointClouds[index]);
  stPointCloud.points = points;
  stPointCloud.count = count;
  return(true);
}

bool EnginePointCloudDecoration(const unsigned int index, const float red, const float green, const float blue, const float pointsize)
{
  if (index >= MAX_POINT_CLOUDS)
    return(false);

  SPointCloud& stPointCloud (g_vstPointClouds[index]);
  stPointCloud.color[0] = red;
  stPointCloud.color[1] = green;
  stPointCloud.color[2] = blue;
  stPointCloud.pointsize = pointsize;
  stPointCloud.visible = true;
  return(true);
}

bool EngineCameraSetup(const float distance)
{
  orbSetOrbitalDistance(g_poCam, distance);
  return(true);
}