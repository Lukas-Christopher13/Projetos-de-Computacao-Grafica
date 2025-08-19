#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define NDH 800
#define NDV 600

#define X_MIN 10.5
#define X_MAX 100.3
#define Y_MIN 10.5
#define Y_MAX 100.3

// ============ Transformações NDC [-1,1] =================
void user_to_ndc_centralizado(double x, double y, double *ndcx, double *ndcy) {
    *ndcx = 2.0 * (x - X_MIN) / (X_MAX - X_MIN) - 1.0;
    *ndcy = 2.0 * (y - Y_MIN) / (Y_MAX - Y_MIN) - 1.0;
}

void ndc_to_dc_centralizado(double ndcx, double ndcy, int *dcx, int *dcy) {
    *dcx = (int)round((ndcx + 1.0) / 2.0 * (NDH - 1));
    *dcy = (int)round((ndcy + 1.0) / 2.0 * (NDV - 1));
}

int pixel_x = 0;
int pixel_y = 0;

// ==== Função de Desenho ====
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
        glVertex2i(pixel_x, pixel_y);
    glEnd();

    glFlush();
}

// ==== Programa Principal ====
int main(int argc, char** argv) {
    double x, y, ndcx, ndcy;
    int dcx, dcy;

    printf("Digite coordenadas do mundo (x y): ");
    scanf("%lf %lf", &x, &y);

    // Conversão: coordenadas do mundo para coordenadas normalizadas do dispositivo
    user_to_ndc_centralizado(x, y, &ndcx, &ndcy);
    printf("NDC [-1,1]: (%f, %f)\n", ndcx, ndcy);

    // Conversão: coordenadas normalizadas do dispositivo para coordenadas do dispositivo (pixel)
    ndc_to_dc_centralizado(ndcx, ndcy, &dcx, &dcy);
    printf("Pixel final OpenGL: (%d, %d)\n", dcx, dcy);

    pixel_x = dcx;
    pixel_y = dcy;

    // Inicializa OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(NDH, NDV);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pixel OpenGL - NDC [-1,1]");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, NDH, 0, NDV);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
