#include "OpenGLSB.h"

typedef struct ImageLoad
{
	GLbyte *image;
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
}ImageLoad;

//���ο� ����� �Լ�
void ChangeSize(GLsizei w, GLsizei h); // âũ�Ⱑ ����Ǹ� ȣ��Ǵ� �Լ�

GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat); 
//TGA������ �ε��ϴ� �Լ�
void TimerFunction(int value); // Ÿ�̸�

//startscene�� ����� �Լ�
void displayStartScene(); //ù��° ȭ�鿡 ������ �̹����� ����ϴ� �Լ�
int startscene_menuidentify(); // ù ȭ�鿡�� �޴� Ŭ���� �����ϴ� �Լ�
void Display1(); // ù ȭ�� �Լ�
void mouseclick1(int button, int state, int x, int y); // ù��° â���� ���콺 Ŭ�� ó��
void Initdisplay1();; // ù��° ȭ�� �ʱ�ȭ

//gamescene�� ����� �Լ�
void Display2(); // ����ȭ���� ����ϴ� �Լ�
void mouseclick2(int button, int state, int x, int y); // 
void KeyBoard(unsigned char key, int x, int y);
void initscene2(int stage);
void sonarfunc();
void shurakenmake();
void shurakenfunc();
//targa.cpp ����� �Լ�
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

typedef struct VertexList
{
	int n;
	float xpos[12];
	float ypos[12];
}VertexList;

typedef struct Unit { // ������ ��ü �ѹ� ��� ���Ŀ� �ȿ�����
	float xpos, ypos; // x,y ��ǥ
	float xs,ys; // ũ�� 
	float rotation; // ȸ��
	VertexList origin; // �� ��ü�� ����
	VertexList transform; // ���ο� ��ü�� ����
}Unit; 

typedef struct ActingUnit{ // ������ ��ü �������� ��� �ʿ� (���ΰ�, ��, ������)
	float vx,vy,vrot;
	Unit unit;
}ActingUnit;

//unit�� ����� �Լ�
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

// SelectScene�� ����
void initscene3();
void mouseclick3(int button, int state, int x, int y);
void KeyBoard2(unsigned char key, int x, int y);
void Display3();
bool Icon(float x,float y,float rasterx,float rastery,float width,float height);

void Display4();
void mouseclick4(int button, int state, int x, int y);
void initscene4();
