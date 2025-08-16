#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

#define X_MIN -1000.f
#define X_MAX  1000.f
#define Y_MIN -1000.f
#define Y_MAX  1000.f


float worldToNdcX(float x);
float worldToNdcY(float y);
int ndcToDivice(float value);

unsigned int createVBO(float vetices[]);
unsigned int createVAB();
unsigned int compileShaders();


const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   gl_PointSize = 1.0;\n"
    "}\0";

const char *fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n\0";

int main() {
    int width, height;
    float x, y;
    float ndcx, ndcy;

    cout << "Insira o tamanho da janela" << endl;
    cout << "Width: ";
    cin >> width;
    cout << "Height: ";
    cin >> height;

    cout << "Insira as coordenadas do mundo" << endl;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;

    cout << "Coordenadas do mundo (" << x << ", " << y << ")" << endl;
    
    ndcx = worldToNdcX(x);
    ndcy = worldToNdcY(y);

    cout << "Coordenadas NDC (" << ndcx << ", " << ndcy << ")" << endl;

    float vertices[] = {ndcx, ndcy, 0.0f};

    return 0;
}

//Criar o buffer e manda pra GPU
unsigned int createVBO(float vertices[]) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    return VBO;
}

//Diz como interpretar o array
unsigned int createVAB() {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    return VAO;
}

unsigned int compileShaders(const char *shaderStr, int shaderType) {
    int success;
    char infoLog[512];

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderStr, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "Erro na compilação do Shader\n" << infoLog << endl;
    }
    
    return shader;
}

float worldToNdcX(float x) {
    return (x - X_MIN)/(X_MAX - X_MIN);
}

float worldToNdcY(float y) {
    return (y - Y_MIN)/(Y_MAX - Y_MIN);
}


