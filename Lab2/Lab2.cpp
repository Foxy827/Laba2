#define _USE_MATH_DEFINES 
#include <cmath>
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

GLuint gWorldLocation;
GLuint VBO; //глобальная переменная для хранени указателя на буфер вершин
float Scale = 0.0f;
const int width = 300;
const int height = 150;

glm::mat4 Conversion(glm::mat4& m) {
    m[0][0] = sinf(Scale); m[0][1] = 0.0f;        m[0][2] = 0.0f;        m[0][3] = 0.0f;
    m[1][0] = 0.0f;        m[1][1] = cosf(Scale); m[1][2] = 0.0f;        m[1][3] = 0.0f;
    m[2][0] = 0.0f;        m[2][1] = 0.0f;        m[2][2] = sinf(Scale); m[2][3] = 0.0f;
    m[3][0] = 0.0f;        m[3][1] = 0.0f;        m[3][2] = 0.0f;        m[3][3] = 1.0f;
    return m;
}

glm::mat4 Rotation(glm::mat4& m) {
    m[0][0] = cosf(Scale); m[0][1] = -sinf(Scale); m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = sinf(Scale); m[1][1] = cosf(Scale);  m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f;        m[2][1] = 0.0f;         m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f;        m[3][1] = 0.0f;         m[3][2] = 0.0f; m[3][3] = 1.0f;
    return m;
}

glm::mat4 Moving(glm::mat4& m) {
    m[0][0] = 1.0f;  m[0][1] = 0.0f;  m[0][2] = 0.0f; m[0][3] = sinf(Scale);
    m[1][0] = 0.0f;  m[1][1] = 1.0f;  m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f;  m[2][1] = 0.0f;  m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f; m[3][3] = 1.0f;
    return m;
}

glm::mat4 InitPerspectiveProj(float fovy, float aspect, float znear, float zfar) {
    glm::mat4 m;
    const float zRange = znear - zfar;
    const float tanHalfFOV = tanf(fovy / 2.0 * M_PI / 180);

    m[0][0] = 1.0f / (tanHalfFOV * aspect);
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = 1.0f / tanHalfFOV;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = (-znear - zfar) / zRange;
    m[2][3] = 2.0f * zfar * znear / zRange;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 1.0f;
    m[3][3] = 0.0f;

    return m;
}

glm::vec3 Cross(const glm::vec3 v1, const glm::vec3 v2) {
    const float _x = v1.y * v2.z - v1.z * v2.y;
    const float _y = v1.z * v2.x - v1.x * v2.z;
    const float _z = v1.x * v2.y - v1.y * v2.x;

    return glm::vec3(_x, _y, _z);
}

glm::vec3 Normalize(glm::vec3 v)
{
    const float Length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

    v.x /= Length;
    v.y /= Length;
    v.z /= Length;

    return glm::vec3(v.x, v.y, v.z);
}

glm::mat4 InitCameraTransform(const glm::vec3& Target, const glm::vec3& Up)
{
    glm::mat4 m;

    glm::vec3 N = Target;
    N = Normalize(N);
    glm::vec3 U = Up;
    U = Normalize(U);
    U = Cross(U, Target);
    glm::vec3 V = Cross(N, U);

    m[0][0] = U.x; m[0][1] = U.y; m[0][2] = U.z; m[0][3] = 0.0f;
    m[1][0] = V.x; m[1][1] = V.y; m[1][2] = V.z; m[1][3] = 0.0f;
    m[2][0] = N.x; m[2][1] = N.y; m[2][2] = N.z; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

    return m;
}

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); //очистка цвета

    glm::vec3 Vertices[3]; //создается массив из 2 экземпляра

    Vertices[0] = glm::vec3(1.0f, 1.0f, 0.0f);
    Vertices[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, -1.0f, 0.0f);

    Scale += 0.001f;

    glm::mat4 mtconv = Conversion(mtconv); //создание матрицы
    glm::mat4 mtrotation = Rotation(mtrotation);
    glm::mat4 mtmove = Moving(mtmove);
    glm::mat4 proj = InitPerspectiveProj(120.0f, (float)width / (float)height, 1.0f, 2000.0f);

    glm::vec3 CameraPos = glm::vec3(1.0f, 1.0f, -3.0f);
    glm::vec3 CameraTarget = glm::vec3(0.45f, 0.0f, 1.0f);
    glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    CameraPos = Cross(CameraPos, CameraUp);
    CameraUp = Normalize(CameraUp);
    glm::mat4 mtcam = InitCameraTransform(CameraTarget, CameraUp);

    Vertices[0] = glm::vec4(Vertices[0], 1.0f) * proj * mtcam * mtmove * mtrotation * mtconv;
    Vertices[1] = glm::vec4(Vertices[1], 1.0f) * proj * mtcam * mtmove * mtrotation * mtconv;
    Vertices[2] = glm::vec4(Vertices[2], 1.0f) * proj * mtcam * mtmove * mtrotation * mtconv;

    
    glGenBuffers(1, &VBO); //генерация объектов перемен. типов(Кол-во объектов и сслыка на массив)
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязка указателя к названию цели 
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //наполнение данными(название цели, размер данных в байтах, адрес массива вершин, флаг(исп. паттернов))

    glEnableVertexAttribArray(0); //координаты вершин, используемые в буфере, рассматриваются как атрибут вершины с индексом 0
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0); //отключение атрибута вершины

    glutSwapBuffers(); //фоновый буфер меняется с буфером кадра
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //инициализация GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //настройка опций (двойная буферизация и буфер цвета)
    glutInitWindowSize(1024, 768);  //создание и изменения окна
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 1");
    glutDisplayFunc(RenderSceneCB); //взаимодействие с оконной системой
    glutIdleFunc(RenderSceneCB);

    GLenum res = glewInit(); //инициализация GLEW и проверка на ошибки
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //вызов цвета
    glutMainLoop(); //ждет события и передает их через функ обратного вызова
}