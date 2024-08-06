#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb_image.h>
#include <glad/glad.h>
#include <cstring> 
#include <string>
#include <iostream>

class Texture2D {
private:
	unsigned int m_textureId;
	int m_warpS = GL_REPEAT;
	int m_warpT = GL_REPEAT;
	int m_minFilter = GL_LINEAR;
	int m_magFilter = GL_LINEAR;

	std::string m_imgPath;
	int m_width;
	int m_height;
	int m_channels;
public:
	Texture2D(std::string imgPath) {
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		
		// Set wrapping and filtering methods.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_warpS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_warpT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
	
		m_imgPath = imgPath;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(m_imgPath.c_str(), &m_width, &m_height, &m_channels, 0);
		if (data)
		{
			GLenum format;
			if (m_channels == 1)
				format = GL_RED;
			else if (m_channels == 3)
				format = GL_RGB;
			else if (m_channels == 4)
				format = GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	void bind() {
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	~Texture2D() {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &m_textureId);
	}
};
#endif
