#include <Texture.h>

namespace Ai
{
	std::vector<std::string> SkyBoxTexture::m_faces
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	SkyBoxTexture::SkyBoxTexture(std::string filepath):
		m_filepath(filepath)
	{
		init();
	}

	void SkyBoxTexture::init()
	{
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);

		int width, height, nrChannels;
		unsigned char* data;

		stbi_set_flip_vertically_on_load(false);

		for (unsigned int i = 0; i < m_faces.size(); i++)
		{
			// Concat image filepath.
			std::string imgFilepath = m_filepath;
			if (imgFilepath[imgFilepath.size() - 1] != '/')
			{
				imgFilepath += "/";
				imgFilepath += m_faces[i];
			}
			else
			{
				imgFilepath += m_faces[i];
			}

			// Load image.
			data = stbi_load(imgFilepath.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << imgFilepath << std::endl;
				stbi_image_free(data);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	unsigned int SkyBoxTexture::getTextureId()
	{
		return m_textureId;
	}
}