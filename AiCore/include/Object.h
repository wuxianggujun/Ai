#pragma once 
#ifndef OBJECT_H

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Texture.h>
#include <Shader.h>
#include <Camera.h>
#include <iostream>

namespace Ai 
{
	// Global light source
	// 1.Directional light
	struct DirLight
	{
		glm::vec3 m_direction;
		glm::vec3 m_color;
	};
	// 2.Point light
	struct SceneLight
	{
		glm::vec3 m_position;
		glm::vec3 m_color;

		float m_constant;
		float m_linear;
		float m_quadratic;
	};

	class PointLight 
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_color;
	public:
		PointLight() = delete;

		PointLight(glm::vec3 position, glm::vec3 color);

		glm::vec3& getPosition();

		void setPosition(glm::vec3 position);

		glm::vec3& getColor();

		void setColor(glm::vec3 color);
	};

	class AiObject 
	{
	private:
		unsigned int m_objectId;
		std::string m_objectName;
	protected:
		glm::vec3 m_translate;
		glm::vec3 m_rotate;
		glm::vec3 m_scale;

		glm::mat4 m_view;
		glm::mat4 m_projection;
	public:
		AiObject() = delete;

		AiObject(unsigned int id, std::string name): 
			m_objectId(id), 
			m_objectName(name), 
			m_translate(0.0f),
			m_rotate(0.0f),
			m_scale(1.0f)
		{

		}

		AiObject(unsigned int id):
			m_objectId(id),
			m_objectName(""),
			m_translate(0.0f),
			m_rotate(0.0f),
			m_scale(1.0f)
		{

		}

		virtual ~AiObject() 
		{

		}

		unsigned int getObjectId();

		std::string getObjectName();

		virtual void init() = 0;

		virtual void draw() = 0;

		virtual glm::vec3& getTranslate();

		virtual glm::vec3& getRotate();
		
		virtual glm::vec3& getScale();

		virtual glm::mat4& getView();

		virtual glm::mat4& getProjection();
	};

	class AiTexQuadObject : public AiObject 
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;

		static unsigned int m_shaderID;
		// If m_shaderIsGenerated is ture, means shader has been generated.
		// Else, shader should be generated first.
		static bool m_shaderIsGenerated;

		std::string m_imgPath;
		std::shared_ptr<Texture2D> m_texture;
	public:
		AiTexQuadObject() = delete;

		AiTexQuadObject(unsigned int id, std::string name, std::string imgPath);

		virtual ~AiTexQuadObject();

		virtual void draw() override;

	protected:
		virtual void init() override;

		virtual unsigned int initShader() noexcept;
	public:
		static constexpr float m_vertices[20] = 
		{
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
		};

		static constexpr unsigned int m_indices[6] = 
		{
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		// Shader source code.
		static constexpr char* vertexShaderCode = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec2 aTex;\n"
			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"out vec2 TexCoord;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = projection * view * model *  vec4(aPos, 1.0);\n"
			"   TexCoord = aTex;\n"
			"}\0";

		static constexpr char* fragmentShaderCode = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec2 TexCoord;\n"
			"uniform sampler2D tex1;\n"
			"void main()\n"
			"{\n"
			"   FragColor = texture(tex1, TexCoord);\n"
			"}\n\0";
	};

	class AiPureCubeObject : public AiObject {
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;

		static unsigned int m_shaderID;
		// If m_shaderIsGenerated is ture, means shader has been generated.
		// Else, shader should be generated first.
		static bool m_shaderIsGenerated;

		glm::vec3 m_color;
	public:
		AiPureCubeObject() = delete;

		AiPureCubeObject(unsigned int id);
		
		~AiPureCubeObject();

		virtual void draw() override;

		void setColor(float r, float g, float b);
	private:
		virtual void init() override;

		virtual unsigned int initShader() noexcept;
	private:
		static constexpr float m_vertices[24] =
		{
			-0.5f, 0.5f, 0.5f,
			 0.5f, 0.5f, 0.5f,
			 0.5f, 0.5f,-0.5f,
			-0.5f, 0.5f,-0.5f,

			-0.5f,-0.5f, 0.5f,
			 0.5f,-0.5f, 0.5f,
			 0.5f,-0.5f,-0.5f,
			-0.5f,-0.5f,-0.5f
		};

		static constexpr unsigned int m_indices[36] =
		{
			// Top
			0, 1, 2,
			0, 2, 3,
			// Front
			4, 5, 1,
			4, 1, 0,
			// Right
			5, 6, 2,
			5, 2, 1,
			// Back
			6, 7, 3,
			6, 3, 2,
			// Left
			7, 4, 0,
			7, 0, 3,
			// Bottom
			7, 6, 5,
			7, 5, 4
		};
	
		// Shader source code.
		static constexpr char* vertexShaderCode = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = projection * view * model *  vec4(aPos, 1.0);\n"
			"}\0";

		static constexpr char* fragmentShaderCode = "#version 330 core\n"
			"uniform vec4 color;\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = color;\n"
			"}\n\0";
	};

	struct Material 
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float shininess;
	};

	// TODO::Modify the draw member funciton.
	class AiQuad : public AiObject
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;

		std::shared_ptr<Shader> m_shader;

		// Object Material.
		Material m_material;

		// Light source.
		std::shared_ptr<PointLight> m_lightSource;
	public:
		AiQuad() = delete;

		AiQuad(unsigned int id, std::shared_ptr<Shader> shader, std::shared_ptr<PointLight> lightSource);

		~AiQuad();

		void setMaterail(Material& material);

		virtual void draw() override;
	private:
		virtual void init() override;
	private:
		static constexpr float m_vertices[24] =
		{
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// top right
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f	// top left 
		};

		static constexpr unsigned int m_indices[6] =
		{
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
	};

	// Quad with lighting maps.
	class AiQuadLM : public AiObject
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;

		std::shared_ptr<Shader> m_shader;

		std::shared_ptr<Texture2D> m_diffuse;
		std::shared_ptr<Texture2D> m_specular;

		// Light source.
		std::shared_ptr<PointLight> m_lightSource;

		bool m_selected;
	public:
		AiQuadLM() = delete;

		AiQuadLM(unsigned int id, std::shared_ptr<Shader> shader, std::shared_ptr<PointLight> lightSource, 
			std::shared_ptr<Texture2D> diffuse, std::shared_ptr<Texture2D> specular);

		~AiQuadLM();

		void setLightingMaps(std::shared_ptr<Texture2D> diffuse, std::shared_ptr<Texture2D> specular);

		void changeSelectedState();

		virtual void draw() override;
	private:
		virtual void init() override;

	private:
		static constexpr float m_vertices[32] =
		{
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f,  1.0f,	// top right
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f,  0.0f,	// bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,	// bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f,  1.0f	// top left 
		};

		static constexpr unsigned int m_indices[6] =
		{
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
	};
}
#endif
