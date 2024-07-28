#include "Object.h"

namespace Ai {
	unsigned int AiObject::getObjectId() 
	{
		return m_objectId;
	}

	std::string AiObject::getObjectName() 
	{
		return m_objectName;
	}

	glm::vec3& AiObject::getTranslate() 
	{
		return m_translate;
	}

	glm::vec3& AiObject::getRotate() 
	{
		return m_rotate;
	}

	glm::vec3& AiObject::getScale() 
	{
		return m_scale;
	}

	glm::mat4& AiObject::getView()
	{
		return m_view;
	}

	glm::mat4& AiObject::getProjection()
	{
		return m_projection;
	}

	// ----------------------------------------------------------------------------------------------------
	// Class AiTexQuadObject
	unsigned int AiTexQuadObject::m_shaderID = 0;
	bool AiTexQuadObject::m_shaderIsGenerated = false;

	AiTexQuadObject::AiTexQuadObject(unsigned int id, std::string name, std::string imgPath) 
        : AiObject(id, name), m_imgPath(imgPath)
    {
        // Generate vertex array object.
        init();
        // Init the only texture.
        m_texture = std::make_shared<Texture2D>(m_imgPath);
		// Init the shader.
		if (!m_shaderIsGenerated) {
			m_shaderID = initShader();
			m_shaderIsGenerated = true;
		}
	}

	AiTexQuadObject::~AiTexQuadObject()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}

	void AiTexQuadObject::init() 
	{
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}

	void AiTexQuadObject::draw() 
	{
		// Active texture0 slot and bind m_texture.
		glActiveTexture(GL_TEXTURE0);
		m_texture->bind();
		// Use shader.
		glUseProgram(m_shaderID);

		//----------------------------------------------------------------------------------------------------
		// ::Beta Code
		glm::mat4 model(1.0f);
		model = glm::translate(model, m_translate);
		model = glm::rotate(model, glm::radians(m_rotate.x), glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, glm::radians(m_rotate.y), glm::vec3(0.0, 1.0, 0.0));
		model = glm::rotate(model, glm::radians(m_rotate.z), glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, m_scale);
		unsigned int modelLoc = glGetUniformLocation(m_shaderID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		unsigned int viewLoc = glGetUniformLocation(m_shaderID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
		unsigned int projectionLoc = glGetUniformLocation(m_shaderID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
		//----------------------------------------------------------------------------------------------------
		
		// Bind m_VAO.
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

    unsigned int AiTexQuadObject::initShader() noexcept
	{
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShader);
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) 
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
    }
	// ====================================================================================================


	// ----------------------------------------------------------------------------------------------------
	// Class AiPureCubeObject
	unsigned int AiPureCubeObject::m_shaderID = 0;
	bool AiPureCubeObject::m_shaderIsGenerated = false;

	AiPureCubeObject::AiPureCubeObject(unsigned int id) :
		AiObject(id)
	{
		m_color = glm::vec4(1.0f);
		// Generate vertex array object.
		init();

		// Init the shader.
		if (!m_shaderIsGenerated) {
			m_shaderID = initShader();
			m_shaderIsGenerated = true;
		}
	}

	AiPureCubeObject::~AiPureCubeObject()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}

	void AiPureCubeObject::draw()
	{
		// Use shader.
		glUseProgram(m_shaderID);

		glm::mat4 model(1.0f);
		model = glm::translate(model, m_translate);
		model = glm::rotate(model, glm::radians(m_rotate.x), glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, glm::radians(m_rotate.y), glm::vec3(0.0, 1.0, 0.0));
		model = glm::rotate(model, glm::radians(m_rotate.z), glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, m_scale);
		unsigned int modelLoc = glGetUniformLocation(m_shaderID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		unsigned int viewLoc = glGetUniformLocation(m_shaderID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
		unsigned int projectionLoc = glGetUniformLocation(m_shaderID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
		unsigned int colorLoc = glGetUniformLocation(m_shaderID, "color");
		glUniform4fv(colorLoc, 1, glm::value_ptr(m_color));

		// Bind m_VAO.
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	void AiPureCubeObject::setColor(float r, float g, float b)
	{
		m_color = glm::vec4(r, g, b, 1.0f);
	}

	void AiPureCubeObject::init()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	// TODO::Simplify shader initialization code.
	unsigned int AiPureCubeObject::initShader() noexcept
	{
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShader);
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}
	// ====================================================================================================
}
