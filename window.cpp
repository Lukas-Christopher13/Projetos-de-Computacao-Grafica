#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//nosso imput
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.0f,  0.5f, 0.0f
};

const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n {"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    
const char *fragmentShaderSource = "version 460 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

//Compila o shader que eu criei!
unsigned int createVertexShader() {
    int success;
    char infoLog[512];
    unsigned int vertexShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }
    return vertexShader;
}

//Compilação do fragment shader!
unsigned int createFragmentShader() {
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    return fragmentShader;
}

unsigned int createShaderProgam() {
    unsigned int vertexShader = createVertexShader();
    unsigned int fragmentShader = createFragmentShader();
    
    unsigned int shaderProgam;
    shaderProgam = glCreateProgram();

    //logar dps
    glAttachShader(shaderProgam, vertexShader);
    glAttachShader(shaderProgam, fragmentShader);
    glLinkProgram(shaderProgam);

    glUseProgram(shaderProgam);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgam;
}


//VBO para mandar tudo de uma vez pra GPU
unsigned int drowTriagle() {
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    return VAO;
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LeranOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Falha ao criar a janela" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Falha ao inicializar o GLAD" << std::endl;
        return -1;
    }

    unsigned int shaderProgram = createFragmentShader();
    unsigned int VBO = drowTriagle();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        //triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VBO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
            
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

