#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


#define NDH 800
#define NDV 600

#define X_MIN 10.5
#define X_MAX 100.3
#define Y_MIN 10.5
#define Y_MAX 100.3

// ============ Transformações NDC [0,1] =================
void user_to_ndc(double x, double y, double *ndcx, double *ndcy) {
    *ndcx = (x - X_MIN) / (X_MAX - X_MIN);
    *ndcy = (y - Y_MIN) / (Y_MAX - Y_MIN);
}

void ndc_to_dc(double ndcx, double ndcy, int *dcx, int *dcy) {
    *dcx = (int)round(ndcx * (NDH - 1));
    *dcy = (int)round(ndcy * (NDV - 1));
}

int pixel_x = 0;
int pixel_y = 0;

// ==== Função de Desenho ====
void setPixel() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f); // define cor (vermelho)
    glBegin(GL_POINTS);
        glVertex2i(pixel_x, pixel_y); // posição do pixel calculada
    glEnd();

    glFlush();
}

// =============== Programa Principal =====================
int main(int argc, char** argv) {
    double x, y, ndcx, ndcy;
    int dcx, dcy;

    printf("Digite coordenadas do mundo (x y): ");
    scanf("%lf %lf", &x, &y);

    //Conversão: coordenadas do mundo para coordenadas normalizadas do dispositivo
    user_to_ndc(x, y, &ndcx, &ndcy);
    printf("NDC [0,1]: (%f, %f)\n", ndcx, ndcy);

    //Conversão: coordenadas normalizadas do dispositivo para coordenadas do dispositivo (pixel)
    ndc_to_dc(ndcx, ndcy, &dcx, &dcy);
    printf("Pixel final OpenGL: (%d, %d)\n", dcx, dcy);

    pixel_x = dcx;
    pixel_y = dcy;

    //Configuração do OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(NDH, NDV); // tamanho da janela
    glutInitWindowPosition(100, 100); // posição onde a janela vai abrir
    glutCreateWindow("Pixel OpenGL - NDC [0,1]");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, NDH, 0, NDV);

    glutDisplayFunc(setPixel);
    glutMainLoop();

    return 0;
}