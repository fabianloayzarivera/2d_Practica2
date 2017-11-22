#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <stb_image.h>
#include <Vec2.h>
using namespace std;

ltex_t* createTexture(const char *filename, int *width, int *height) {
	
	unsigned char* buffer = stbi_load(filename, width, height, nullptr, 4);

	if (buffer != NULL) {
		//cout << "has size";
	}
	else {
		cout << "buffer empty";
	}

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
	
	//Load Wall Texture
	int widthWall = 415;
	int heightWall = 304;
	ltex_t *texWall = createTexture("./data/wall.jpg", &widthWall, &heightWall);
	if (texWall == NULL) {
		cout << "EVERYTHING IS FUCKED UP!";
		getchar();
		return 0;
	}

	//Load Fire Texture
	double xposMouse = 0;
	double yposMouse = 0;
	int widthFire = 256;
	int heightFire = 256;
	ltex_t *texFire = createTexture("./data/fire.png", &widthFire, &heightFire);
	if (texFire == NULL) {
		cout << "EVERYTHING IS FUCKED UP!";
		getchar();
		return 0;
	}

	//Load Grille Texture
	int widthGrille = 205;
	int heightGrille = 205;
	ltex_t *texGrille = createTexture("./data/grille.png", &widthGrille, &heightGrille);
	if (texGrille == NULL) {
		cout << "EVERYTHING IS FUCKED UP!";
		getchar();
		return 0;
	}

	//Load Light Texture
	int widthLight  = 205;
	int heightLight = 205;
	ltex_t *texLight = createTexture("./data/light.png", &widthLight, &heightLight);
	if (texLight == NULL) {
		cout << "EVERYTHING IS FUCKED UP!";
		getchar();
		return 0;
	}

	float angleFire = 0;
	bool rotateLeft = true;
	bool enlarge = true;
	float widthFireF  = static_cast<float>(widthFire);
	float heightFireF = static_cast<float>(heightFire);
	float widthFireForignal   = widthFireF;
	float heightFireForiginal = heightFireF;
	// Bucle principal
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

		//draw wall
		float u1Wall = (static_cast<float>(screenWidth)/ static_cast<float>(widthWall));
		float v1Wall = (static_cast<float>(screenHeight) / static_cast<float>(heightWall));
		lgfx_setblend(BLEND_SOLID);
		ltex_drawrotsized(texWall, 0, 0, 0, 0, 0, screenWidth, screenHeight, 0, 0, u1Wall, v1Wall);
		
		//draw fire
		lgfx_setblend(BLEND_ADD);		
		if (rotateLeft) {
			angleFire += (10 * deltaTime);
			if (angleFire >= 10)
				rotateLeft = false;
		}
		else {
			angleFire -= (10 * deltaTime);
			if (angleFire <= -10)
				rotateLeft = true;
		}

		if (enlarge) {
			widthFireF  += (widthFireForignal * 0.5f * deltaTime);
			heightFireF += (heightFireForiginal * 0.5f * deltaTime);
			if ((widthFireF * heightFireF) >= ((widthFireForignal * heightFireForiginal) * 1.2f))
				enlarge = false;
		}
		else {
			widthFireF  -= (widthFireForignal * 0.5f * deltaTime);
			heightFireF -= (heightFireForiginal * 0.5f * deltaTime);
			if ((widthFireF * heightFireF) <= ((widthFireForignal * heightFireForiginal) * 0.8f))
				enlarge = true;
		}

		ltex_drawrotsized(texFire, mousePos->x , mousePos->y , angleFire, 0.5f, 0.75f, widthFireF, heightFireF, 0, 0, 1, 1);

		//draw grille
		float u1Grille = (static_cast<float>(screenWidth) / static_cast<float>(widthGrille));
		float v1Grille = (static_cast<float>(screenHeight) / static_cast<float>(heightGrille));
		lgfx_setblend(BLEND_ALPHA);
		ltex_drawrotsized(texGrille, 0, 0, 0, 0, 0, screenWidth, screenHeight, 0, 0, u1Grille, v1Grille);

		//draw light
		lgfx_setblend(BLEND_MUL);
		ltex_drawrotsized(texLight, mousePos->x, mousePos->y , 0, 0.5f, 0.5f, widthLight, heightLight, 0, 0, 1, 1);

		//draw rectangles
		float rectLeftWidth = screenWidth -(screenWidth - (mousePos->x - (widthLight / 2)));
		float rectRightWidth = screenWidth - (mousePos->x + (widthLight / 2));
		float rectTopHeight = screenHeight - (screenHeight - (mousePos->y - (heightLight/2)));
		float rectBotHeight = screenHeight - (mousePos->y + (heightLight / 2));
		lgfx_setblend(BLEND_SOLID);
		lgfx_setcolor(0, 0, 0, 0);
		lgfx_drawrect(0, 0, rectLeftWidth, screenHeight);
		lgfx_drawrect((mousePos->x + (widthLight / 2)), 0, rectRightWidth, screenHeight);
		lgfx_drawrect(rectLeftWidth, 0, widthLight, rectTopHeight);
		lgfx_drawrect(rectLeftWidth, (mousePos->y + (heightLight / 2)), widthLight, rectBotHeight);
		lgfx_setcolor(1, 1, 1, 1);
		
		



		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
		delete(mousePos);

	}

	return 0;
}