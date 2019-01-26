#include "OpenGLSB.h"

typedef struct ImageLoad
{
	GLbyte *image;
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
}ImageLoad;

//메인에 선언된 함수
void ChangeSize(GLsizei w, GLsizei h); // 창크기가 변경되면 호출되는 함수

GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat); 
//TGA파일을 로드하는 함수
void TimerFunction(int value); // 타이머

//startscene에 선언된 함수
void displayStartScene(); //첫번째 화면에 나오는 이미지를 출력하는 함수
int startscene_menuidentify(); // 첫 화면에서 메뉴 클릭을 감지하는 함수
void Display1(); // 첫 화면 함수
void mouseclick1(int button, int state, int x, int y); // 첫번째 창에서 마우스 클릭 처리
void Initdisplay1();; // 첫번째 화면 초기화

//gamescene에 선언된 함수
void Display2(); // 게임화면을 출력하는 함수
void mouseclick2(int button, int state, int x, int y); // 
void KeyBoard(unsigned char key, int x, int y);
void initscene2(int stage);
void sonarfunc();
void shurakenmake();
void shurakenfunc();
//targa.cpp 선언된 함수
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

typedef struct VertexList
{
	int n;
	float xpos[12];
	float ypos[12];
}VertexList;

typedef struct Unit { // 정적인 물체 한번 계산 이후에 안움직임
	float xpos, ypos; // x,y 좌표
	float xs,ys; // 크기 
	float rotation; // 회전
	VertexList origin; // 원 물체의 형태
	VertexList transform; // 새로운 물체의 형태
}Unit; 

typedef struct ActingUnit{ // 동적인 물체 지속적인 계산 필요 (주인공, 적, 수리검)
	float vx,vy,vrot;
	Unit unit;
}ActingUnit;

//unit에 선언된 함수
void DrawVertex(VertexList list);
void DrawUnit(Unit unit);
void DrawUnit(ActingUnit acunit);
void DrawEnemy(ActingUnit acunit);
//void DrawUnit(ActingUnit *acunit);
float InerAngle(float* p1,float* p2,float* p3);
bool MinMaxTest(Unit unit1,Unit unit2);
bool ContainTest(Unit unit1,Unit unit2);
bool CollisionTest(Unit unit1,Unit unit2);
bool ShurakenCollision(ActingUnit act,ActingUnit* ary,int num);

void TransformVertex(Unit *unit);
void TransformVertex(ActingUnit *actunit);
void AIcompute(ActingUnit *actunit);

bool UnitCollision(ActingUnit act,Unit* ary,int num);
bool UnitCollision(ActingUnit act,ActingUnit* ary,int num);
bool Sight(float* p1,float* p2,float* p3,float* p4);
bool Sight2(float* p1,float* p2,Unit unit);

//save load Manager
void Save(int number);
int Load(int number);
void LoadBefore();

// SelectScene에 사용됨
void initscene3();
void mouseclick3(int button, int state, int x, int y);
void KeyBoard2(unsigned char key, int x, int y);
void Display3();
bool Icon(float x,float y,float rasterx,float rastery,float width,float height);

void Display4();
void mouseclick4(int button, int state, int x, int y);
void initscene4();
