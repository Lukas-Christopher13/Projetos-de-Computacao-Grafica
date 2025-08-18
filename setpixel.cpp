#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

using namespace std;

#define X_MIN -1000.f
#define X_MAX  1000.f
#define Y_MIN -1000.f
#define Y_MAX  1000.f


float worldToNdcX(float x);
float worldToNdcY(float y);
int ndcToDiviceX(float ndcx, int width);
int ndcToDiviceY(float ndcy, int height);

unsigned int createVBO(float vertices[], int verticeSize);
unsigned int createVAO();
unsigned int compileShaders(const char *shaderStr, int shaderType);
unsigned int createShaderProgram();

int window(int width, int height, float vertices[], int verticeSize);
void setPixl(unsigned int shaderProgram, unsigned int VAO);


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
    int dcx, dcy;

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

    cout << "Coordenadas do Mndo: (" << x << ", " << y << ")" << endl;
    
    ndcx = worldToNdcX(x);
    ndcy = worldToNdcY(y);

    cout << "Coordenadas NDC: (" << ndcx << ", " << ndcy << ")" << endl;
    
    dcx = ndcToDiviceX(ndcx, width);
    dcy = ndcToDiviceY(ndcy, height);

    cout << "Coordenadas do Dispositivo: (" << dcx << ", " << dcy << ")" << endl;

    float vertices[] = {ndcx, ndcy, 0.0f};
    window(width, height, vertices, sizeof(vertices));

    return 0;
}

int window(int width, int height, float vertices[], int verticeSize) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "SetPixel", NULL, NULL);
    if (window == NULL) {
        cout << "Falha ao criar a janela" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Falha ao inicializar o GLAD" << endl;
        return -1;
    }

    unsigned int sharedProgram = createShaderProgram();
    unsigned int VBO = createVBO(vertices, verticeSize);
    unsigned int VAO = createVAO();


    while (!glfwWindowShouldClose(window)) {
        setPixl(sharedProgram, VAO);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void setPixl(unsigned int shaderProgram, unsigned int VAO) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
}

//Criar o buffer e manda pra GPU
unsigned int createVBO(float vertices[], int verticeSize) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticeSize , vertices, GL_STATIC_DRAW);

    return VBO;
}

//Diz como interpretar o array
unsigned int createVAO() {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    return VAO;
}

unsigned int createShaderProgram() {
    unsigned int vertexShader = compileShaders(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShaders(fragmentShaderSource, GL_FRAGMENT_SHADER);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
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
    return 2.0 * (x - X_MIN) / (X_MAX - X_MIN) - 1.0;
}

float worldToNdcY(float y) {
    return 2.0 * (y - X_MIN) / (X_MAX - X_MIN) - 1.0;
}

int ndcToDiviceX(float ndcx, int width) {
    return (int)round((ndcx + 1.0) / 2.0 * (width - 1));
}

int ndcToDiviceY(float ndcy, int height) {
    return (int)round((ndcy + 1.0) / 2.0 * (height - 1));
}