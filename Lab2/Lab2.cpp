#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); //очистка цвета
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //вызов цвета

    glutMainLoop(); //ждет события и передает их через функ обратного вызова
}
