#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;


float worldToNdc(float value);
int ndcToDivice(float value);

int main() {
    int width, height;
    float x, y;

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
    
    

    return 0;
}

