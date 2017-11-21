#include <textures.h>

ltex_t* createTexture(const char *filename, int *width, int *height) {
	
	unsigned char* buffer = stbi_load(filename, width, height, nullptr, 4);

	ltex_t* tex = ltex_alloc(*width, *height, 0);
	ltex_setpixels(tex, buffer);

	stbi_image_free(buffer);

	return tex;
	//ltex_free(ltex_t* tex);

}