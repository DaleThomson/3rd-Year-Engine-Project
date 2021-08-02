#include "loadTexture.h"

using namespace std;

namespace loadTexture {

	TTF_Font* textFont = TTF_OpenFont("../Resources/Fonts/GoodTimes.ttf", 50);		//used for labels


	GLuint loadTextures(const char *fname) {

		GLuint texID;
		glGenTextures(1, &texID); // generate texture ID

		// load file - using extended SDL_image library
		SDL_Surface * tmpSurface = IMG_Load(fname);

		if (!tmpSurface) {
			std::cout << "Error loading texture" << std::endl;
		}

		// bind texture and set parameters
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		SDL_PixelFormat *format = tmpSurface->format;

		GLuint externalFormat, internalFormat;
		if (format->Amask) {
			internalFormat = GL_RGBA;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
		}
		else {
			internalFormat = GL_RGB;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
			externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
		//glGenerateMipmap(GL_TEXTURE_2D);

		SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer
		return texID;	// return value of texture ID
	}

	// textToTexture
	GLuint textToTexture(const char * str, GLuint textID, SDL_Color colour) {
		GLuint texture = textID;
		TTF_Font * font = textFont;

		SDL_Surface * stringImage = TTF_RenderText_Blended(font, str, colour);

		if (stringImage == NULL) {
			std::cout << "String surface not created." << std::endl;
		}

		if (texture == 0) {
			glGenTextures(1, &texture);
		}

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stringImage->w, stringImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, stringImage->pixels);
		glBindTexture(GL_TEXTURE_2D, NULL);

		SDL_FreeSurface(stringImage);
		return texture;
	}

	//clearing the labels text to texture
	void clearTextTexture(GLuint textID) 
	{
		if (textID != NULL) {
			glDeleteTextures(1, &textID);
		}
	}

	GLuint loadCubeMap(const char *fname[6], GLuint *texID)
	{
		glGenTextures(1, texID); // generate texture ID
		GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
							GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
							GL_TEXTURE_CUBE_MAP_POSITIVE_X,
							GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
							GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
							GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };
		SDL_Surface *tmpSurface;

		glBindTexture(GL_TEXTURE_CUBE_MAP, *texID); // bind texture and set parameters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		GLuint externalFormat;
		for (int i = 0; i < 6; i++)
		{
			// load file - using core SDL library
			tmpSurface = SDL_LoadBMP(fname[i]);
			if (!tmpSurface)
			{
				std::cout << "Error loading bitmap" << std::endl;
				return *texID;
			}

			// skybox textures should not have alpha (assuming this is true!)
			SDL_PixelFormat *format = tmpSurface->format;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;

			glTexImage2D(sides[i], 0, GL_RGB, tmpSurface->w, tmpSurface->h, 0,
				externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
			// texture loaded, free the temporary buffer
			SDL_FreeSurface(tmpSurface);
		}
		return *texID;	// return value of texure ID, redundant really
	}
}