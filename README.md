Projeto em **C++/OpenGL** para demonstrar transformação de coordenadas do mundo → NDC (Normalized Device Coordinates) → dispositivo (pixels).  
O programa abre uma janela e desenha um **ponto vermelho** na posição calculada.

## 📂 Estrutura do Projeto

## ⚙️ Dependências
### 🔹 Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install cmake g++ libglfw3-dev libx11-dev libxcursor-dev libxrandr-dev libxi-dev

🚀 Como rodar
🔹 1. Clonar o repositório
git clone https://github.com/seu-usuario/SetPixelProject.git
cd SetPixelProject

🔹 2. Compilar
Linux
mkdir build && cd build
cmake ..
make

Windows (MinGW)
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .

