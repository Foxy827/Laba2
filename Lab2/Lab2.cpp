#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>

GLuint VBO; //глобальная переменная для хранени указателя на буфер вершин
float Scale = 0.0f;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); //очистка цвета

    glm::vec3 Vertices[3]; //создается массив из 2 экземпляра

    Vertices[0] = glm::vec3(1.0f, 1.0f, 0.0f);
    Vertices[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, -1.0f, 0.0f);

    Scale += 0.001f;
    glm::mat4x4 World;

    World[0][0] = sinf(Scale); World[0][1] = 0.0f;         World[0][2] = 0.0f;        World[0][3] = 0.0f;
    World[1][0] = 0.0f;        World[1][1] = cosf(Scale);  World[1][2] = 0.0f;        World[1][3] = 0.0f;
    World[2][0] = 0.0f;        World[2][1] = 0.0f;         World[2][2] = sinf(Scale); World[2][3] = 0.0f;
    World[3][0] = 0.0f;        World[3][1] = 0.0f;         World[3][2] = 0.0f;        World[3][3] = 1.0f;

    Vertices[0] = World * glm::vec4(Vertices[0], 1.0f);
    Vertices[1] = World * glm::vec4(Vertices[1], 1.0f);
    Vertices[2] = World * glm::vec4(Vertices[2], 1.0f);

    
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
