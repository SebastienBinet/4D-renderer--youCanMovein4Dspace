/*
*		This Code Was Based on a tutorial of Jeff Molofee 2000
*		If This Code is Useful, he would be interested to be informed (nehe.gamedev.net)
*/


#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include <math.h>

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
float DeltaX=0.0f;
float DeltaY=0.0f;
float DeltaZ=0.0f;
float DeltaT=0.0f;
float g4DTransformMatrix[5][5]=
{
  {1,0,0,0,0},
  {0,1,0,0,0},
  {0,0,1,0,0},
  {0,0,0,1,0},
  {0,0,0,0,1}
};



int SebasShift=false;

#define COS_1_DEG   (float)0.99984769515639123915701155881391
#define SIN_1_DEG   (float)0.017452406437283512819418978516316
#define COS_2_DEG   (float)0.99939082701909573000624344004393
#define SIN_2_DEG   (float)0.034899496702500971645995181625333
//#define COS_2_DEG   (float)0.70710678118654752440084436210485
//#define SIN_2_DEG   (float)0.70710678118654752440084436210485
#define COS_5_DEG   (float)0.99619469809174553229501040247389
#define SIN_5_DEG   (float)0.087155742747658173558064270837474
const float c4DRotateXZ_2Deg[5][5]=
{
  {  COS_2_DEG,          0,  SIN_2_DEG,          0,          0 },
  {          0,          1,          0,          0,          0 },
  { -SIN_2_DEG,          0,  COS_2_DEG,          0,          0 },
  {          0,          0,          0,          1,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateZX_2Deg[5][5]=
{
  {  COS_2_DEG,          0, -SIN_2_DEG,          0,          0 },
  {          0,          1,          0,          0,          0 },
  {  SIN_2_DEG,          0,  COS_2_DEG,          0,          0 },
  {          0,          0,          0,          1,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateYZ_2Deg[5][5]=
{
  {          1,          0,          0,          0,          0 },
  {          0,  COS_2_DEG, -SIN_2_DEG,          0,          0 },
  {          0,  SIN_2_DEG,  COS_2_DEG,          0,          0 },
  {          0,          0,          0,          1,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateZY_2Deg[5][5]=
{
  {          1,          0,          0,          0,          0 },
  {          0,  COS_2_DEG,  SIN_2_DEG,          0,          0 },
  {          0, -SIN_2_DEG,  COS_2_DEG,          0,          0 },
  {          0,          0,          0,          1,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateXY_2Deg[5][5]=
{
  {  COS_2_DEG, -SIN_2_DEG,          0,          0,          0 },
  {  SIN_2_DEG,  COS_2_DEG,          0,          0,          0 },
  {          0,          0,          1,          0,          0 },
  {          0,          0,          0,          1,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateYX_2Deg[5][5]=
{
  {  COS_2_DEG,  SIN_2_DEG,          0,          0,          0 },
  { -SIN_2_DEG,  COS_2_DEG,          0,          0,          0 },
  {          0,          0,          1,          0,          0 },
  {          0,          0,          0,          1,          0 },
  {          0,          0,          0,          0,          1 }
};




const float c4DRotateXT_2Deg[5][5]=
{
  {  COS_2_DEG,          0,          0, -SIN_2_DEG,          0 },
  {          0,          1,          0,          0,          0 },
  {          0,          0,          1,          0,          0 },
  {  SIN_2_DEG,          0,          0,  COS_2_DEG,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateTX_2Deg[5][5]=
{
  {  COS_2_DEG,          0,          0,  SIN_2_DEG,          0 },
  {          0,          1,          0,          0,          0 },
  {          0,          0,          1,          0,          0 },
  { -SIN_2_DEG,          0,          0,  COS_2_DEG,          0 },
  {          0,          0,          0,          0,          1 }
};

const float c4DRotateYT_2Deg[5][5]=
{
  {          1,          0,          0,          0,          0 },
  {          0,  COS_2_DEG,          0, -SIN_2_DEG,          0 },
  {          0,          0,          1,          0,          0 },
  {          0,  SIN_2_DEG,          0,  COS_2_DEG,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateTY_2Deg[5][5]=
{
  {          1,          0,          0,          0,          0 },
  {          0,  COS_2_DEG,          0,  SIN_2_DEG,          0 },
  {          0,          0,          1,          0,          0 },
  {          0, -SIN_2_DEG,          0,  COS_2_DEG,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateZT_2Deg[5][5]=
{
  {          1,          0,          0,          0,          0 },
  {          0,          1,          0,          0,          0 },
  {          0,          0,  COS_2_DEG, -SIN_2_DEG,          0 },
  {          0,          0,  SIN_2_DEG,  COS_2_DEG,          0 },
  {          0,          0,          0,          0,          1 }
};
const float c4DRotateTZ_2Deg[5][5]=
{
  {          1,          0,          0,          0,          0 },
  {          0,          1,          0,          0,          0 },
  {          0,          0,  COS_2_DEG,  SIN_2_DEG,          0 },
  {          0,          0, -SIN_2_DEG,  COS_2_DEG,          0 },
  {          0,          0,          0,          0,          1 }
};


void Seb4DRotate(const float i4DTrMatr[5][5])
{
  float mTemp4DMatrix[5][5];

  // Create temp matrix
  for(int i=0; i<5; i++)
  {
    for(int j=0; j<5; j++)
    {
      mTemp4DMatrix[j][i] = 
        g4DTransformMatrix[j][0]*i4DTrMatr[0][i] +
        g4DTransformMatrix[j][1]*i4DTrMatr[1][i] +
        g4DTransformMatrix[j][2]*i4DTrMatr[2][i] +
        g4DTransformMatrix[j][3]*i4DTrMatr[3][i] +
        g4DTransformMatrix[j][4]*i4DTrMatr[4][i] ;
    }
  }

  // Copy back to global transfor matrix
  for(int i=0; i<5; i++)
  {
    for(int j=0; j<5; j++)
    {
      g4DTransformMatrix[j][i]=mTemp4DMatrix[j][i];
    }
  }
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///////// Sebas

#define MAX_TR_PRE (5000)
#define MAX (2)
#define MAX2 ((MAX-1)*14)
#define MAX3 (MAX2*2)

bool ThereWasAProblem =false;
float variableT=0.0;

class SebVertex4D
{
public:
	GLfloat x,y,z,t;
	float r,g,b; // 0.0 to 1.0
	SebVertex4D::SebVertex4D(void):x(0.0f),y(0.0f),z(0.0f),t(0.0f),r(0.0),g(0.0),b(0.0){}
	SebVertex4D::SebVertex4D(GLfloat _x,GLfloat _y,GLfloat _z,GLfloat _t,float _r,float _g,float _b):x(_x), y(_y), z(_z), t(_t), r(_r), g(_g), b(_b) {}
  void SebVertex4DTransform(float i4DTrMatr[][5])
  {
	  GLfloat xTemp,yTemp,zTemp,tTemp;
    /*
    x = x* i4DTrMatr[0][0] + y* i4DTrMatr[1][0] + z* i4DTrMatr[2][0] + t* i4DTrMatr[3][0] + 1* i4DTrMatr[4][0];
    y = x* i4DTrMatr[0][1] + y* i4DTrMatr[1][1] + z* i4DTrMatr[2][1] + t* i4DTrMatr[3][1] + 1* i4DTrMatr[4][1];
    z = x* i4DTrMatr[0][2] + y* i4DTrMatr[1][2] + z* i4DTrMatr[2][2] + t* i4DTrMatr[3][2] + 1* i4DTrMatr[4][2];
    t = x* i4DTrMatr[0][3] + y* i4DTrMatr[1][3] + z* i4DTrMatr[2][3] + t* i4DTrMatr[3][3] + 1* i4DTrMatr[4][3];
    */
    xTemp = x* i4DTrMatr[0][0] + y* i4DTrMatr[0][1] + z* i4DTrMatr[0][2] + t* i4DTrMatr[0][3] + 1* i4DTrMatr[0][4];
    yTemp = x* i4DTrMatr[1][0] + y* i4DTrMatr[1][1] + z* i4DTrMatr[1][2] + t* i4DTrMatr[1][3] + 1* i4DTrMatr[1][4];
    zTemp = x* i4DTrMatr[2][0] + y* i4DTrMatr[2][1] + z* i4DTrMatr[2][2] + t* i4DTrMatr[2][3] + 1* i4DTrMatr[2][4];
    tTemp = x* i4DTrMatr[3][0] + y* i4DTrMatr[3][1] + z* i4DTrMatr[3][2] + t* i4DTrMatr[3][3] + 1* i4DTrMatr[3][4];

    x=xTemp;
    y=yTemp;
    z=zTemp;
    t=tTemp;
  };

};

class SebVertex3D
{
public:
	GLfloat x,y,z;
	float r,g,b; // 0.0 to 1.0
	SebVertex3D::SebVertex3D(void):x(0.0f),y(0.0f),z(0.0f),r(0.0),g(0.0),b(0.0){}
	SebVertex3D::SebVertex3D(GLfloat _x,GLfloat _y,GLfloat _z,float _r,float _g,float _b):x(_x), y(_y), z(_z), r(_r), g(_g), b(_b) {}
};

class SebTriangle4D
{
public:
	SebVertex4D v4d[3];
	SebTriangle4D::SebTriangle4D(void){SebVertex4D vv; v4d[0]=vv; v4d[1]=vv; v4d[2]=vv;}
	SebTriangle4D::SebTriangle4D(SebVertex4D a, SebVertex4D b, SebVertex4D c){v4d[0]=a;v4d[1]=b;v4d[2]=c;}
};

class SebTriangle3D
{
public:
	SebVertex3D v3d[3];
	float r,g,b; // 0 to 1
	SebTriangle3D::SebTriangle3D(void):r(0.0),g(0.0),b(0.0){SebVertex3D vv; v3d[0]=vv; v3d[1]=vv; v3d[2]=vv;}
	SebTriangle3D::SebTriangle3D(SebVertex3D a, SebVertex3D b, SebVertex3D c): r((a.r+b.r+c.r)/float(3.0)), g((a.g+b.g+c.g)/float(3.0)), b((a.b+b.b+c.b)/float(3.0)) {v3d[0]=a;v3d[1]=b;v3d[2]=c;}
};

class SebTrianglePyramid4D
{
public:
	SebVertex4D v4d[4];
	float r,g,b; // 0 to 1
	SebTrianglePyramid4D::SebTrianglePyramid4D(void){SebVertex4D xx;v4d[0]=xx;v4d[1]=xx;v4d[2]=xx;v4d[4]=xx;}
	SebTrianglePyramid4D::SebTrianglePyramid4D(SebVertex4D a, SebVertex4D b, SebVertex4D c, SebVertex4D d) {v4d[0]=a;v4d[1]=b;v4d[2]=c;v4d[3]=d;}
};

class SebTrianglePresence
{
public:
	int tr4dQty;
	SebTriangle4D tr4D[MAX];
	int trPy4dQty;
	SebTrianglePyramid4D trPy4D[MAX2];
	int tr3dQty;
	SebTriangle3D tr3D[MAX3];
	SebTrianglePresence::SebTrianglePresence(void):tr4dQty(0),trPy4dQty(0){}
	void createTrianglePyramid4D(void)
	{
		if(tr4dQty>=2)
		{
			for(int tr4Di=0;tr4Di<tr4dQty-1;tr4Di++)
			{
				int tr1Index=tr4Di;
				int tr2Index=tr1Index+1;
				SebVertex4D vertexCenter01(
					((tr4D[tr1Index].v4d[0].x+tr4D[tr1Index].v4d[1].x+tr4D[tr2Index].v4d[0].x+tr4D[tr2Index].v4d[1].x)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[0].y+tr4D[tr1Index].v4d[1].y+tr4D[tr2Index].v4d[0].y+tr4D[tr2Index].v4d[1].y)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[0].z+tr4D[tr1Index].v4d[1].z+tr4D[tr2Index].v4d[0].z+tr4D[tr2Index].v4d[1].z)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[0].t+tr4D[tr1Index].v4d[1].t+tr4D[tr2Index].v4d[0].t+tr4D[tr2Index].v4d[1].t)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[0].r+tr4D[tr1Index].v4d[1].r+tr4D[tr2Index].v4d[0].r+tr4D[tr2Index].v4d[1].r)/float(4.0)),
					((tr4D[tr1Index].v4d[0].g+tr4D[tr1Index].v4d[1].g+tr4D[tr2Index].v4d[0].g+tr4D[tr2Index].v4d[1].g)/float(4.0)),
					((tr4D[tr1Index].v4d[0].b+tr4D[tr1Index].v4d[1].b+tr4D[tr2Index].v4d[0].b+tr4D[tr2Index].v4d[1].b)/float(4.0))
					);
				SebVertex4D vertexCenter12(
					((tr4D[tr1Index].v4d[1].x+tr4D[tr1Index].v4d[2].x+tr4D[tr2Index].v4d[1].x+tr4D[tr2Index].v4d[2].x)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[1].y+tr4D[tr1Index].v4d[2].y+tr4D[tr2Index].v4d[1].y+tr4D[tr2Index].v4d[2].y)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[1].z+tr4D[tr1Index].v4d[2].z+tr4D[tr2Index].v4d[1].z+tr4D[tr2Index].v4d[2].z)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[1].t+tr4D[tr1Index].v4d[2].t+tr4D[tr2Index].v4d[1].t+tr4D[tr2Index].v4d[2].t)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[1].r+tr4D[tr1Index].v4d[2].r+tr4D[tr2Index].v4d[1].r+tr4D[tr2Index].v4d[2].r)/float(4.0)),
					((tr4D[tr1Index].v4d[1].g+tr4D[tr1Index].v4d[2].g+tr4D[tr2Index].v4d[1].g+tr4D[tr2Index].v4d[2].g)/float(4.0)),
					((tr4D[tr1Index].v4d[1].b+tr4D[tr1Index].v4d[2].b+tr4D[tr2Index].v4d[1].b+tr4D[tr2Index].v4d[2].b)/float(4.0))
					);
				SebVertex4D vertexCenter20(
					((tr4D[tr1Index].v4d[2].x+tr4D[tr1Index].v4d[0].x+tr4D[tr2Index].v4d[2].x+tr4D[tr2Index].v4d[0].x)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[2].y+tr4D[tr1Index].v4d[0].y+tr4D[tr2Index].v4d[2].y+tr4D[tr2Index].v4d[0].y)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[2].z+tr4D[tr1Index].v4d[0].z+tr4D[tr2Index].v4d[2].z+tr4D[tr2Index].v4d[0].z)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[2].t+tr4D[tr1Index].v4d[0].t+tr4D[tr2Index].v4d[2].t+tr4D[tr2Index].v4d[0].t)/GLfloat(4.0)),
					((tr4D[tr1Index].v4d[2].r+tr4D[tr1Index].v4d[0].r+tr4D[tr2Index].v4d[2].r+tr4D[tr2Index].v4d[0].r)/float(4.0)),
					((tr4D[tr1Index].v4d[2].g+tr4D[tr1Index].v4d[0].g+tr4D[tr2Index].v4d[2].g+tr4D[tr2Index].v4d[0].g)/float(4.0)),
					((tr4D[tr1Index].v4d[2].b+tr4D[tr1Index].v4d[0].b+tr4D[tr2Index].v4d[2].b+tr4D[tr2Index].v4d[0].b)/float(4.0))
					);

				SebVertex4D vertexCenter012(
					((vertexCenter01.x+vertexCenter12.x+vertexCenter20.x)/GLfloat(3.0)),
					((vertexCenter01.y+vertexCenter12.y+vertexCenter20.y)/GLfloat(3.0)),
					((vertexCenter01.z+vertexCenter12.z+vertexCenter20.z)/GLfloat(3.0)),
					((vertexCenter01.t+vertexCenter12.t+vertexCenter20.t)/GLfloat(3.0)),
					((vertexCenter01.r+vertexCenter12.r+vertexCenter20.r)/GLfloat(3.0)),
					((vertexCenter01.g+vertexCenter12.g+vertexCenter20.g)/GLfloat(3.0)),
					((vertexCenter01.b+vertexCenter12.b+vertexCenter20.b)/GLfloat(3.0))
					);

				// tr1
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr1Index].v4d[0],tr4D[tr1Index].v4d[1],tr4D[tr1Index].v4d[2],vertexCenter012);
				// tr2
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr2Index].v4d[0],tr4D[tr2Index].v4d[1],tr4D[tr2Index].v4d[2],vertexCenter012);

				// vertices 0 and 1
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr1Index].v4d[0],tr4D[tr2Index].v4d[0],vertexCenter01,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr2Index].v4d[0],tr4D[tr2Index].v4d[1],vertexCenter01,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr2Index].v4d[1],tr4D[tr1Index].v4d[1],vertexCenter01,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr1Index].v4d[1],tr4D[tr1Index].v4d[0],vertexCenter01,vertexCenter012);
				// vertices 1 and 2
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr1Index].v4d[1],tr4D[tr2Index].v4d[1],vertexCenter12,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr2Index].v4d[1],tr4D[tr2Index].v4d[2],vertexCenter12,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr2Index].v4d[2],tr4D[tr1Index].v4d[2],vertexCenter12,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr1Index].v4d[2],tr4D[tr1Index].v4d[1],vertexCenter12,vertexCenter012);
				// vertices 2 and 0
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr1Index].v4d[2],tr4D[tr2Index].v4d[2],vertexCenter20,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr2Index].v4d[2],tr4D[tr2Index].v4d[0],vertexCenter20,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr2Index].v4d[0],tr4D[tr1Index].v4d[0],vertexCenter20,vertexCenter012);
				trPy4D[trPy4dQty++]=SebTrianglePyramid4D(tr4D[tr1Index].v4d[0],tr4D[tr1Index].v4d[2],vertexCenter20,vertexCenter012);

			}

		}

	};
	void operations4D()
	{
		for (int i=0;i<trPy4dQty;i++)
		{
			for (int j=0;j<4;j++)
			{
		    	trPy4D[i].v4d[j].SebVertex4DTransform(g4DTransformMatrix);
	    		/*
				trPy4D[i].v4d[j].x+=DeltaX;
				trPy4D[i].v4d[j].y+=DeltaY;
				trPy4D[i].v4d[j].z+=DeltaZ;
				trPy4D[i].v4d[j].t+=DeltaT;
    			*/
			}
		}

	}
	void createTriangle3d(GLfloat t)
	{
		tr3dQty=0;
		for (int i=0;i<trPy4dQty;i++)
		{
			int j=0;
			SebVertex3D v3D[6]; // 4 max
			float fraction;
			float numerator;
			// for each segment, look if the plan intersect between the two vertices 4D
			// compute the fraction of the plan to vertice 0 / vertice 1 to vertice 0
			numerator=(t-trPy4D[i].v4d[0].t);
			fraction=numerator/(trPy4D[i].v4d[1].t-trPy4D[i].v4d[0].t);
			if((fraction>=0)&&(fraction<=1)||(numerator==0))
			{ // There is an intersection
				v3D[j].x=trPy4D[i].v4d[0].x+fraction*(trPy4D[i].v4d[1].x-trPy4D[i].v4d[0].x);
				v3D[j].y=trPy4D[i].v4d[0].y+fraction*(trPy4D[i].v4d[1].y-trPy4D[i].v4d[0].y);
				v3D[j].z=trPy4D[i].v4d[0].z+fraction*(trPy4D[i].v4d[1].z-trPy4D[i].v4d[0].z);
				v3D[j].r=trPy4D[i].v4d[0].r+fraction*(trPy4D[i].v4d[1].r-trPy4D[i].v4d[0].r);
				v3D[j].g=trPy4D[i].v4d[0].g+fraction*(trPy4D[i].v4d[1].g-trPy4D[i].v4d[0].g);
				v3D[j].b=trPy4D[i].v4d[0].b+fraction*(trPy4D[i].v4d[1].b-trPy4D[i].v4d[0].b);
				j++;
			}
			// compute the fraction of the plan to vertice 0 / vertice 2 to vertice 0
			fraction=(t-trPy4D[i].v4d[0].t)/(trPy4D[i].v4d[2].t-trPy4D[i].v4d[0].t);
			if((fraction>=0)&&(fraction<=1))
			{ // There is an intersection
				v3D[j].x=trPy4D[i].v4d[0].x+fraction*(trPy4D[i].v4d[2].x-trPy4D[i].v4d[0].x);
				v3D[j].y=trPy4D[i].v4d[0].y+fraction*(trPy4D[i].v4d[2].y-trPy4D[i].v4d[0].y);
				v3D[j].z=trPy4D[i].v4d[0].z+fraction*(trPy4D[i].v4d[2].z-trPy4D[i].v4d[0].z);
				v3D[j].r=trPy4D[i].v4d[0].r+fraction*(trPy4D[i].v4d[2].r-trPy4D[i].v4d[0].r);
				v3D[j].g=trPy4D[i].v4d[0].g+fraction*(trPy4D[i].v4d[2].g-trPy4D[i].v4d[0].g);
				v3D[j].b=trPy4D[i].v4d[0].b+fraction*(trPy4D[i].v4d[2].b-trPy4D[i].v4d[0].b);
				j++;
			}
			// compute the fraction of the plan to vertice 0 / vertice 3 to vertice 0
			fraction=(t-trPy4D[i].v4d[0].t)/(trPy4D[i].v4d[3].t-trPy4D[i].v4d[0].t);
			if((fraction>=0)&&(fraction<=1))
			{ // There is an intersection
				v3D[j].x=trPy4D[i].v4d[0].x+fraction*(trPy4D[i].v4d[3].x-trPy4D[i].v4d[0].x);
				v3D[j].y=trPy4D[i].v4d[0].y+fraction*(trPy4D[i].v4d[3].y-trPy4D[i].v4d[0].y);
				v3D[j].z=trPy4D[i].v4d[0].z+fraction*(trPy4D[i].v4d[3].z-trPy4D[i].v4d[0].z);
				v3D[j].r=trPy4D[i].v4d[0].r+fraction*(trPy4D[i].v4d[3].r-trPy4D[i].v4d[0].r);
				v3D[j].g=trPy4D[i].v4d[0].g+fraction*(trPy4D[i].v4d[3].g-trPy4D[i].v4d[0].g);
				v3D[j].b=trPy4D[i].v4d[0].b+fraction*(trPy4D[i].v4d[3].b-trPy4D[i].v4d[0].b);
				j++;
			}
			// compute the fraction of the plan to vertice 1 / vertice 2 to vertice 1
			fraction=(t-trPy4D[i].v4d[1].t)/(trPy4D[i].v4d[2].t-trPy4D[i].v4d[1].t);
			if((fraction>=0)&&(fraction<=1))
			{ // There is an intersection
				v3D[j].x=trPy4D[i].v4d[1].x+fraction*(trPy4D[i].v4d[2].x-trPy4D[i].v4d[1].x);
				v3D[j].y=trPy4D[i].v4d[1].y+fraction*(trPy4D[i].v4d[2].y-trPy4D[i].v4d[1].y);
				v3D[j].z=trPy4D[i].v4d[1].z+fraction*(trPy4D[i].v4d[2].z-trPy4D[i].v4d[1].z);
				v3D[j].r=trPy4D[i].v4d[1].r+fraction*(trPy4D[i].v4d[2].r-trPy4D[i].v4d[1].r);
				v3D[j].g=trPy4D[i].v4d[1].g+fraction*(trPy4D[i].v4d[2].g-trPy4D[i].v4d[1].g);
				v3D[j].b=trPy4D[i].v4d[1].b+fraction*(trPy4D[i].v4d[2].b-trPy4D[i].v4d[1].b);
				j++;
			}
			// compute the fraction of the plan to vertice 1 / vertice 3 to vertice 1
			fraction=(t-trPy4D[i].v4d[1].t)/(trPy4D[i].v4d[3].t-trPy4D[i].v4d[1].t);
			if((fraction>=0)&&(fraction<=1))
			{ // There is an intersection
				v3D[j].x=trPy4D[i].v4d[1].x+fraction*(trPy4D[i].v4d[3].x-trPy4D[i].v4d[1].x);
				v3D[j].y=trPy4D[i].v4d[1].y+fraction*(trPy4D[i].v4d[3].y-trPy4D[i].v4d[1].y);
				v3D[j].z=trPy4D[i].v4d[1].z+fraction*(trPy4D[i].v4d[3].z-trPy4D[i].v4d[1].z);
				v3D[j].r=trPy4D[i].v4d[1].r+fraction*(trPy4D[i].v4d[3].r-trPy4D[i].v4d[1].r);
				v3D[j].g=trPy4D[i].v4d[1].g+fraction*(trPy4D[i].v4d[3].g-trPy4D[i].v4d[1].g);
				v3D[j].b=trPy4D[i].v4d[1].b+fraction*(trPy4D[i].v4d[3].b-trPy4D[i].v4d[1].b);
				j++;
			}
			// compute the fraction of the plan to vertice 2 / vertice 3 to vertice 2
			fraction=(t-trPy4D[i].v4d[2].t)/(trPy4D[i].v4d[3].t-trPy4D[i].v4d[2].t);
			if((fraction>=0)&&(fraction<=1))
			{ // There is an intersection
				v3D[j].x=trPy4D[i].v4d[2].x+fraction*(trPy4D[i].v4d[3].x-trPy4D[i].v4d[2].x);
				v3D[j].y=trPy4D[i].v4d[2].y+fraction*(trPy4D[i].v4d[3].y-trPy4D[i].v4d[2].y);
				v3D[j].z=trPy4D[i].v4d[2].z+fraction*(trPy4D[i].v4d[3].z-trPy4D[i].v4d[2].z);
				v3D[j].r=trPy4D[i].v4d[2].r+fraction*(trPy4D[i].v4d[3].r-trPy4D[i].v4d[2].r);
				v3D[j].g=trPy4D[i].v4d[2].g+fraction*(trPy4D[i].v4d[3].g-trPy4D[i].v4d[2].g);
				v3D[j].b=trPy4D[i].v4d[2].b+fraction*(trPy4D[i].v4d[3].b-trPy4D[i].v4d[2].b);
				j++;
			}
			if(j==3)
			{
				tr3D[tr3dQty].v3d[0]=v3D[0];
				tr3D[tr3dQty].v3d[1]=v3D[1];
				tr3D[tr3dQty].v3d[2]=v3D[2];
				tr3D[tr3dQty].r=((v3D[0].r+v3D[1].r+v3D[2].r)/float(3.0));
				tr3D[tr3dQty].g=((v3D[0].g+v3D[1].g+v3D[2].g)/float(3.0));
				tr3D[tr3dQty].b=((v3D[0].b+v3D[1].b+v3D[2].b)/float(3.0));
				tr3dQty++;
			}
			if(j==4)
			{
				tr3D[tr3dQty].v3d[0]=v3D[0];
				tr3D[tr3dQty].v3d[1]=v3D[1];
				tr3D[tr3dQty].v3d[2]=v3D[2];
				tr3D[tr3dQty].r=((v3D[0].r+v3D[1].r+v3D[2].r)/float(3.0));
				tr3D[tr3dQty].g=((v3D[0].g+v3D[1].g+v3D[2].g)/float(3.0));
				tr3D[tr3dQty].b=((v3D[0].b+v3D[1].b+v3D[2].b)/float(3.0));
				tr3dQty++;
				tr3D[tr3dQty].v3d[0]=v3D[1];
				tr3D[tr3dQty].v3d[1]=v3D[2];
				tr3D[tr3dQty].v3d[2]=v3D[3];
				tr3D[tr3dQty].r=((v3D[1].r+v3D[2].r+v3D[3].r)/float(3.0));
				tr3D[tr3dQty].g=((v3D[1].g+v3D[2].g+v3D[3].g)/float(3.0));
				tr3D[tr3dQty].b=((v3D[1].b+v3D[2].b+v3D[3].b)/float(3.0));
				tr3dQty++;
			}
			if(j==1 || j==2 || j>4)
			{
				ThereWasAProblem=true;
			}

		}
	}
};

class SebObject
{
public:
	int trPrQty;
	SebTrianglePresence trPr[MAX_TR_PRE];
	void createTrianglePyramid4D(void)
	{
		for(int i=0;i<trPrQty;i++)
		{
			trPr[i].createTrianglePyramid4D();
		}
	};
	void operations4D(void)
	{
		for(int i=0;i<trPrQty;i++)
		{
			trPr[i].operations4D();
		}
	};
	void produceListTriangle3d(void)
	{
		for(int i=0;i<trPrQty;i++)
		{
			trPr[i].createTriangle3d(GLfloat(.05*sin(variableT)));
		}
		variableT=variableT+(float)0.1;
//		if(variableT>2.1){variableT=-2.1;}
	}
};

SebObject sebObj;




//////////////////////////////////////////////////////////////
//////// Sebas begin file access
//////// 
//////// +---------------------------------------------------------------------+
//////// |                                                                     |
//////// | 3. POV-Ray RAW Triangle, Fractint Color                             |
//////// |                                                                     |
//////// +---------------------------------------------------------------------+
//////// 
//////// If the RAW2POV application is fed the -fc option then it will use the
//////// following twelve numbers per triangle format that includes color. The
//////// numbers can be separated with single spaces or tabs. The R G B values
//////// are between 0 and 1.
//////// //////// 
//////// R   G   B   Ax   Ay   Az   Bx   By   Bz   Cx   Cy   Cz
//////// 
//////// Example with two triangles:
//////// //////// 
//////// <-------start of file-------->
//////// 0.4 0.3 0.2 5.0 -5.3 -2.1 3.4 1.2 4.2 3.3 -2.1 3.0
//////// 0.4 0.3 0.2 4.0 -2.3 -1.1 2.4 2.2 5.2 4.3 -3.1 1.0
//////// <-------start of file-------->


static int line = 0;
static char buff[255];

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void POV_ray_RAW_triangle_Fractin_Color_load(char *fname0, GLfloat t0, char *fname1, GLfloat t1, float r0, float g0, float b0, float r1, float g1, float b1)
{
	FILE *f0, *f1;
	fopen_s(&f0, fname0, "r");
	fopen_s(&f1, fname1, "r");
	if (f0 != NULL && f1 != NULL)
	{
		int feof0=feof(f0);
		int feof1=feof(f1);
		while (!feof0 && !feof1)
		{

			float r,g,b;
			float Ax,Ay,Az;
			float Bx,By,Bz;
			float Cx,Cy,Cz;
			fscanf(f0, "%f %f %f %f %f %f %f %f %f %f %f %f \n", &r, &g, &b,  &Ax, &Ay, &Az, &Bx, &By, &Bz, &Cx, &Cy, &Cz);
      r=r+r0; 
      if(r>1.0){r=1.0;}
      if(r<0.0){r=0;}
      g=g+g0;
      if(g>1.0){g=1.0;}
      if(g<0.0){g=0;}
      b=b+b0;
      if(b>1.0){b=1.0;}
      if(b<0.0){b=0;}
//			SebTriangle4D tr4d_0(SebVertex4D(GLfloat(Ax),GLfloat(Ay),GLfloat(Az),t0;r+r0,g+g0,b+b0),SebVertex4D(GLfloat(Bx),GLfloat(By),GLfloat(Bz),t0,r+r0,g+g0,b+b0),SebVertex4D(GLfloat(Cx),GLfloat(Cy),GLfloat(Cz),t0,r+r0,g+g0,b+b0));
			SebTriangle4D tr4d_0(SebVertex4D(GLfloat(Ax),GLfloat(Ay),GLfloat(Az),t0,r,g,b),SebVertex4D(GLfloat(Bx),GLfloat(By),GLfloat(Bz),t0,r,g,b),SebVertex4D(GLfloat(Cx),GLfloat(Cy),GLfloat(Cz),t0,r,g,b));
			sebObj.trPr[sebObj.trPrQty].tr4D[sebObj.trPr[sebObj.trPrQty].tr4dQty++]=tr4d_0;


			fscanf(f1, "%f %f %f %f %f %f %f %f %f %f %f %f \n", &r, &g, &b,  &Ax, &Ay, &Az, &Bx, &By, &Bz, &Cx, &Cy, &Cz);
      r=r+r1; if(r>1.0){r=1.0;} if(r<0.0){r=0;}
      g=g+g1; if(g>1.0){g=1.0;} if(g<0.0){g=0;}
      b=b+b1; if(b>1.0){b=1.0;} if(b<0.0){b=0;}
//			SebTriangle4D tr4d_1(SebVertex4D(GLfloat(Ax),GLfloat(Ay),GLfloat(Az), t1,r+r1,g+g1,b+b1),SebVertex4D(GLfloat(Bx),GLfloat(By),GLfloat(Bz), t1,r+r1,g+g1,b+b1),SebVertex4D(GLfloat(Cx),GLfloat(Cy),GLfloat(Cz), t1,r+r1,g+g1,b+b1));
			SebTriangle4D tr4d_1(SebVertex4D(GLfloat(Ax),GLfloat(Ay),GLfloat(Az), t1,r,g,b),SebVertex4D(GLfloat(Bx),GLfloat(By),GLfloat(Bz), t1,r,g,b),SebVertex4D(GLfloat(Cx),GLfloat(Cy),GLfloat(Cz), t1,r,g,b));
			sebObj.trPr[sebObj.trPrQty].tr4D[sebObj.trPr[sebObj.trPrQty].tr4dQty++]=tr4d_1;

			//  sebObj.trPr[sebObj.trPrQty].tr4dQty++;
			sebObj.trPrQty ++;
			feof0=feof(f0);
			feof1=feof(f1);

		}
	}
	else
	{
		printf("can't open the file(s):");
		if (f0 == NULL)
		{
			printf("%s ", fname0);
		}
		if (f1 == NULL)
		{
			printf("%s ", fname1);
		}
		printf("\n", fname0);
		return;
	}

	fclose(f0);
	fclose(f1);
}




//////// Sebas end file access

void SebInitSebOb(void)
{
	sebObj.trPrQty=0;
	for(int i=0;i<MAX_TR_PRE;i++)
	{
		sebObj.trPr[i].tr4dQty=0;
		sebObj.trPr[i].trPy4dQty=0;
	}
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.50), "cubeColor00.pov", GLfloat(-0.275), -0.5,  +0.5,  +0.0,  -0.2,  +0.2,  +0.0);
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.225), "cubeColor00.pov", GLfloat(-0.025), -0.2,  +0.2,  +0.0,  +0.0,  +0.0,  +0.0);
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat( 0.025), "cubeColor00.pov", GLfloat( 0.225), +0.0,  +0.0,  +0.0,  +0.2,  -0.2,  +0.0);
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat( 0.275), "cubeColor01.pov", GLfloat( 0.50), +0.2,  -0.2,  +0.0,  +0.5,  -0.5,  +0.0);
/*
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-4.5), "cubeColor00.pov", GLfloat(-4.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-4.0), "cubeColor00.pov", GLfloat(-3.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-3.5), "cubeColor00.pov", GLfloat(-3.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-3.0), "cubeColor00.pov", GLfloat(-2.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-2.5), "cubeColor00.pov", GLfloat(-2.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-2.0), "cubeColor00.pov", GLfloat(-1.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-1.5), "cubeColor00.pov", GLfloat(-1.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-1.0), "cubeColor00.pov", GLfloat(-0.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.5), "cubeColor00.pov", GLfloat( 0.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat( 0.0), "cubeColor00.pov", GLfloat( 0.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat( 0.5), "cubeColor00.pov", GLfloat( 1.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat( 1.0), "cubeColor00.pov", GLfloat( 1.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat( 1.5), "cubeColor00.pov", GLfloat( 2.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.0), "cubeColor00.pov", GLfloat( 2.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.5), "cubeColor00.pov", GLfloat( 3.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.0), "cubeColor00.pov", GLfloat( 3.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.5), "cubeColor00.pov", GLfloat( 4.0));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.0), "cubeColor00.pov", GLfloat( 4.5));
POV_ray_RAW_triangle_Fractin_Color_load("cubeColor00.pov", GLfloat(-0.5), "cubeColor00.pov", GLfloat( 5.0));
*/
/*
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre00.pov", GLfloat(-10.0), "PrismeBaseCarre01.pov", GLfloat(-9.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre01.pov", GLfloat(-9.0), "PrismeBaseCarre02.pov", GLfloat(-8.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre02.pov", GLfloat(-8.0), "PrismeBaseCarre03.pov", GLfloat(-7.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre03.pov", GLfloat(-7.0), "PrismeBaseCarre04.pov", GLfloat(-6.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre04.pov", GLfloat(-6.0), "PrismeBaseCarre05.pov", GLfloat(-5.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre05.pov", GLfloat(-5.0), "PrismeBaseCarre06.pov", GLfloat(-4.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre06.pov", GLfloat(-4.0), "PrismeBaseCarre07.pov", GLfloat(-3.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre07.pov", GLfloat(-3.0), "PrismeBaseCarre08.pov", GLfloat(-2.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre08.pov", GLfloat(-2.0), "PrismeBaseCarre09.pov", GLfloat(-1.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre09.pov", GLfloat(-1.0), "PrismeBaseCarre10.pov", GLfloat( 0.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre10.pov", GLfloat( 0.0), "PrismeBaseCarre11.pov", GLfloat( 1.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre11.pov", GLfloat( 1.0), "PrismeBaseCarre12.pov", GLfloat( 2.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre12.pov", GLfloat( 2.0), "PrismeBaseCarre13.pov", GLfloat( 3.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre13.pov", GLfloat( 3.0), "PrismeBaseCarre14.pov", GLfloat( 4.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre14.pov", GLfloat( 4.0), "PrismeBaseCarre15.pov", GLfloat( 5.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre15.pov", GLfloat( 5.0), "PrismeBaseCarre16.pov", GLfloat( 6.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre16.pov", GLfloat( 6.0), "PrismeBaseCarre17.pov", GLfloat( 7.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre17.pov", GLfloat( 7.0), "PrismeBaseCarre18.pov", GLfloat( 8.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre18.pov", GLfloat( 8.0), "PrismeBaseCarre19.pov", GLfloat( 9.0));
POV_ray_RAW_triangle_Fractin_Color_load("PrismeBaseCarre19.pov", GLfloat( 9.0), "PrismeBaseCarre20.pov", GLfloat(10.0));
*/

/*
// TrPr[0]
SebTriangle4D tr1(SebVertex4D( 1.0,-0.5, 0.5,-1.0),SebVertex4D( 0.0, 1.0, 0.5,-1.0),SebVertex4D(-1.0,-0.5, 0.5,-2.0));
	//	SebTriangle4D tr1bis(SebVertex4D( 4.0,-0.5, 0.5,0.0),SebVertex4D( 0.0, 1.0, 0.5,0.0),SebVertex4D(-1.0,-0.7, 0.5,0.0));
	SebTriangle4D tr2(SebVertex4D( 1.0,-0.5, 0.5, 1.0),SebVertex4D( 0.0, 1.0, 0.5, 2.0),SebVertex4D(-1.0,-0.5, 0.5, 1.0));
	sebObj.trPr[sebObj.trPrQty].tr4D[sebObj.trPr[sebObj.trPrQty].tr4dQty++]=tr1;
	//	sebObj.trPr[sebObj.trPrQty].tr4D[sebObj.trPr[sebObj.trPrQty].tr4dQty++]=tr1bis;
	sebObj.trPr[sebObj.trPrQty].tr4D[sebObj.trPr[sebObj.trPrQty].tr4dQty++]=tr2;
	sebObj.trPrQty++;


	// TrPr[1]
	SebTriangle4D tr3(SebVertex4D( 1.0,-0.5, 0.5,-1.0),SebVertex4D( 0.0, 1.0, 0.5,-1.0),SebVertex4D(1.0,1.5, 0.0,-2.0));
	//	SebTriangle4D tr1bis(SebVertex4D( 4.0,-0.5, 0.5,0.0),SebVertex4D( 0.0, 1.0, 0.5,0.0),SebVertex4D(-1.0,-0.7, 0.5,0.0));
	SebTriangle4D tr4(SebVertex4D( 1.0,-0.5, 0.5, 1.0),SebVertex4D( 0.0, 1.0, 0.5, 2.0),SebVertex4D(1.0,1.5, 0.0, 1.0));
	sebObj.trPr[sebObj.trPrQty].tr4D[sebObj.trPr[sebObj.trPrQty].tr4dQty++]=tr3;
	//	sebObj.trPr[sebObj.trPrQty].tr4D[sebObj.trPr[sebObj.trPrQty].tr4dQty++]=tr1bis;
	sebObj.trPr[sebObj.trPrQty].tr4D[sebObj.trPr[sebObj.trPrQty].tr4dQty++]=tr4;
	sebObj.trPrQty++;
*/

	sebObj.createTrianglePyramid4D();
	sebObj.operations4D();
	sebObj.produceListTriangle3d();
}


//////////////////////////////////////////////////////////////

GLfloat	rtri;				// Angle For The Triangle ( NEW )
GLfloat	rquad;				// Angle For The Quad ( NEW )
GLfloat	SebTime;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}

int SebasTest1=0;
int SebasTest2=0;
int SebasTest3=0;
bool SebasFlags[26];

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	GLfloat sebas1=0.2f;
	GLfloat sebas2=0.2f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	///////////////////////
	SebInitSebOb();
	glTranslatef(0.0f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(rtri,0.1f,1.0f,0.0f);						// Rotate The Triangle On The Y axis ( NEW )

	float r=0.0f;
	float g=0.0f;
	float b=0.0f;

	float r_offset=0.02f;
	float g_offset=0.05f;
	float b_offset=0.07f;


	{
		for(int tr4Di=0;tr4Di<sebObj.trPrQty;tr4Di++)
		{
			for(int i=0;i<sebObj.trPr[tr4Di].tr3dQty;i++)
			{
				GLfloat x0=sebObj.trPr[tr4Di].tr3D[i].v3d[0].x;
				GLfloat y0=sebObj.trPr[tr4Di].tr3D[i].v3d[0].y;
				GLfloat z0=sebObj.trPr[tr4Di].tr3D[i].v3d[0].z;

				GLfloat x1=sebObj.trPr[tr4Di].tr3D[i].v3d[1].x;
				GLfloat y1=sebObj.trPr[tr4Di].tr3D[i].v3d[1].y;
				GLfloat z1=sebObj.trPr[tr4Di].tr3D[i].v3d[1].z;

				GLfloat x2=sebObj.trPr[tr4Di].tr3D[i].v3d[2].x;
				GLfloat y2=sebObj.trPr[tr4Di].tr3D[i].v3d[2].y;
				GLfloat z2=sebObj.trPr[tr4Di].tr3D[i].v3d[2].z;



				r=sebObj.trPr[tr4Di].tr3D[i].r;
				g=sebObj.trPr[tr4Di].tr3D[i].g;
				b=sebObj.trPr[tr4Di].tr3D[i].b;

				r_offset=r_offset+0.031f; if(r_offset>0.10f) r_offset-=0.08f;
				g_offset=g_offset+0.053f; if(g_offset>0.10f) g_offset-=0.08f;
				b_offset=b_offset+0.071f; if(b_offset>0.10f) b_offset-=0.08f;

				//r=r+r_offset;
				//g=g+g_offset;
				//b=b+b_offset;

				if(!SebasFlags[i])
				{
					glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
					glColor3f(r,g,b);						// Red
					glVertex3f(x0,y0,z0);					
					glVertex3f(x1,y1,z1);					
					glVertex3f(x2,y2,z2);					
					glEnd();											// Done Drawing The Pyramid
				}
			}
		}
	}
	///////////////////////

	//rtri+=0.2f;											// Increase The Rotation Variable For The Triangle ( NEW )
	//rquad-=0.15f;										// Decrease The Rotation Variable For The Quad ( NEW )
	return TRUE;										// Keep Going
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right-WindowRect.left,	// Calculate Window Width
		WindowRect.bottom-WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
						 UINT	uMsg,			// Message For This Window
						 WPARAM	wParam,			// Additional Message Information
						 LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			// LoWord Can Be WA_INACTIVE, WA_ACTIVE, WA_CLICKACTIVE,
			// The High-Order Word Specifies The Minimized State Of The Window Being Activated Or Deactivated.
			// A NonZero Value Indicates The Window Is Minimized.
			if ((LOWORD(wParam) != WA_INACTIVE) && !((BOOL)HIWORD(wParam)))
				active=TRUE;						// Program Is Active
			else
				active=FALSE;						// Program Is No Longer Active

			return 0;								// Return To The Message Loop
		}

	case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
			case SC_SCREENSAVE:					// Screensaver Trying To Start?
			case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

	case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

	case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

	case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
				   HINSTANCE	hPrevInstance,		// Previous Instance
				   LPSTR		lpCmdLine,			// Command Line Parameters
				   int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's Solid Object Tutorial",640,480,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's Solid Object Tutorial",640,480,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
			if (keys[' '])						// Is F1 Being Pressed?
			{
				keys[' ']=FALSE;					// If So Make Key FALSE
				SebasTest1=!SebasTest1;

			}
			if (keys[VK_SHIFT])						// Is SHIFT Being Pressed?
			{
				SebasShift=1;
				//keys[VK_SHIFT]=FALSE;					// If So Make Key FALSE
			}
			if (keys[VK_NUMPAD0])						// Is F1 Being Pressed?
			{
				keys[VK_NUMPAD0]=FALSE;					// If So Make Key FALSE
				if(SebasShift==1)
				{
					SebasShift=0;
					DeltaX=DeltaX-0.1;
				}
				else
				{
					DeltaX=DeltaX+0.1;
				}
			}
			if (keys[VK_NUMPAD1])						// Is F1 Being Pressed?
			{
				keys[VK_NUMPAD1]=FALSE;					// If So Make Key FALSE
				if(SebasShift==1)
				{
					SebasShift=0;
					DeltaY=DeltaY-0.1;
				}
				else
				{
					DeltaY=DeltaY+0.1;
				}
			}
			if (keys[VK_NUMPAD4])						// Is F1 Being Pressed?
			{
				keys[VK_NUMPAD4]=FALSE;					// If So Make Key FALSE
				if(SebasShift==1)
				{
					SebasShift=0;
					DeltaZ=DeltaZ-0.1;
				}
				else
				{
					DeltaZ=DeltaZ+0.1;
				}
			}
			if (keys[VK_NUMPAD7])						// Is F1 Being Pressed?
			{
				keys[VK_NUMPAD7]=FALSE;					// If So Make Key FALSE
				if(SebasShift==1)
				{
					SebasShift=0;
					DeltaT=DeltaT-0.1;
				}
				else
				{
					DeltaT=DeltaT+0.1;
				}
			}

      // Y-X plane
      
      if (keys['S'])
			{
               // DeltaY=DeltaY+0.1;
				g4DTransformMatrix[1][4]+=0.01;
			}
			if (keys['X'])
			{
               // DeltaY=DeltaY-0.1;
				g4DTransformMatrix[1][4]-=0.01;
			}
			if (keys['Z'])
			{
               // DeltaX=DeltaX-0.1;
				g4DTransformMatrix[0][4]-=0.01;
			}
			if (keys['C'])
			{
               // DeltaX=DeltaX+0.1;
				g4DTransformMatrix[0][4]+=0.01;
			}
			if (keys['A'])
			{
                // Rotation
				Seb4DRotate(c4DRotateXY_2Deg);
			}
			if (keys['D'])
			{
                // Rotation
				Seb4DRotate(c4DRotateYX_2Deg);
			}

			
      // Z-X plane
      

			if (keys['G'])
			{
               // DeltaZ=DeltaZ-0.1;
				g4DTransformMatrix[2][4]-=0.01;
			}
			if (keys['B'])
			{
               // DeltaZ=DeltaZ+0.1;
				g4DTransformMatrix[2][4]+=0.01;
			}
			if (keys['V'])
			{
               // DeltaX=DeltaX-0.1;
				g4DTransformMatrix[0][4]-=0.01;
			}
			if (keys['N'])
			{
               // DeltaX=DeltaX+0.1;
				g4DTransformMatrix[0][4]+=0.01;
			}
			if (keys['F'])
			{
                // Rotation
				Seb4DRotate(c4DRotateXZ_2Deg);
			}
			if (keys['H'])
			{
                // Rotation
				Seb4DRotate(c4DRotateZX_2Deg);
			}


      // Y-Z plane

			if (keys['J'])
			{
                // Rotation
				Seb4DRotate(c4DRotateZY_2Deg);
			}
			if (keys['M'])
			{
                // Rotation
				Seb4DRotate(c4DRotateYZ_2Deg);
			}


      // T-X plane

			if (keys['2'])
			{
               // DeltaT=DeltaT-0.1;
				g4DTransformMatrix[3][4]-=0.01;
			}
			if (keys['W'])
			{
               // DeltaT=DeltaT+0.1;
				g4DTransformMatrix[3][4]+=0.01;
			}
			if (keys['Q'])
			{
               // DeltaX=DeltaX-0.1;
				g4DTransformMatrix[0][4]-=0.01;
			}
			if (keys['E'])
			{
               // DeltaX=DeltaX+0.1;
				g4DTransformMatrix[0][4]+=0.01;
			}
			if (keys['1'])
			{
                // Rotation
				Seb4DRotate(c4DRotateXT_2Deg);
			}
			if (keys['3'])
			{
                // Rotation
				Seb4DRotate(c4DRotateTX_2Deg);
			}

			
      // T-Y plane

			if (keys['4'])
			{
                // Rotation
				Seb4DRotate(c4DRotateYT_2Deg);
			}
			if (keys['R'])
			{
                // Rotation
				Seb4DRotate(c4DRotateTY_2Deg);
			}


      // T-Z plane

			if (keys['5'])
			{
                // Rotation
				Seb4DRotate(c4DRotateZT_2Deg);
			}
			if (keys['T'])
			{
                // Rotation
				Seb4DRotate(c4DRotateTZ_2Deg);
			}



/*
			for (int ggg=0;ggg<26;ggg++)
			{
				if (keys['A'+ggg])						// Is F1 Being Pressed?
				{
					keys['A'+ggg]=FALSE;					// If So Make Key FALSE
					SebasFlags[ggg]=!SebasFlags[ggg];
				}
			}
*/
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
