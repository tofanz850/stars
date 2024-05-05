#include <GL/glut.h>
#include <windows.h>
#include <stdlib.h>
#include <cmath>


struct Star {
    float x;
    float y;
    float scale;
};

Star stars[] = {
    {-300, 300, 1.0f},
    { 300, 300, 1.0f},
    {-300,-300, 1.0f},
    { 300,-300, 1.0f}
};

void drawStar(float x, float y, float scale) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 360; i += 36) {
        float angle_rad = i * 3.14159 / 180.0;
        float sx = scale * cos(angle_rad);
        float sy = scale * sin(angle_rad);
        if (i % 72 == 0) {
            sx *= 0.4;
            sy *= 0.4;
        }
        glVertex2f(x + sx, y + sy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    for (const auto& star : stars) {
        drawStar(star.x, star.y, star.scale);
    }
    glFlush();
}

void update(int value) {
    for (auto& star : stars) {
        star.scale += 0.1f;
        if (star.scale > 15.0f) {
            star.scale = 2.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(20, update, 0); 
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(-400.0, 400.0, -400.0, 400.0, -400.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1080, 1920);
    glutCreateWindow("Scaling Star");
    init();
    glutDisplayFunc(display);

    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return 0;
}