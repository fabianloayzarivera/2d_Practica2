#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <litegfx.h>
#include "stb_image.h"
#include <glfw3.h>
#include <Vec2.h>
//#include <textures.h>
using namespace std;

ltex_t* createMyTexture(const char *filename, int *width, int *height) {

	unsigned char* buffer = stbi_load(filename, width, height, nullptr, 4);

	ltex_t* tex = ltex_alloc(*width, *height, 0);
	ltex_setpixels(tex, buffer);

	stbi_image_free(buffer);

	return tex;
	//ltex_free(ltex_t* tex);

}

int main() {
	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);

	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}

	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);

	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	// Bucle principal
	float x = 0;
	double xposMouse = 0;
	double yposMouse = 0;
	int width = 415;
	int height = 304;
	ltex_t *tex = createMyTexture("../data/wall.jpg", &width, &height);
	if (tex == nullptr) {
		cout << "EVERYTHING IS FUCKED UP!";
		getchar();
		return 0;
	}

	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);


		// Actualizacion de logica del programa
		glfwGetCursorPos(window, &xposMouse, &yposMouse);
		
		Vec2 *mousePos = new Vec2(xposMouse, yposMouse);

		ltex_drawrotsized(tex, width, float y,
		float angle, float pivotx, float pivoty,
		float width, float height, float u0, float v0, float u1, float v1);*/

















		
		
		/*if (angleCircle < 360)
			angleCircle += 32 * deltaTime;
		else
			angleCircle = 0;*/

		// Pintado
		/*lgfx_clearcolorbuffer(0, 0, 0);
		lgfx_setcolor(1, 0, 0, 1);
		lgfx_drawrect(centerPos->x -25, centerPos->y - 25, 50, 50);

		lgfx_setcolor(1, 1, 1, 1);
		lgfx_drawrect(squarePos->x - 25, squarePos->y - 25, 50, 50);

		lgfx_setcolor(1, 1, 0, 1);
		lgfx_drawoval(circlePos->x - 10, circlePos->y - 10, 20, 20);*/

		
		/*glfwSetWindowTitle(window, title.c_str());*/



		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
		delete(mousePos);
		
	}

    return 0;
}

