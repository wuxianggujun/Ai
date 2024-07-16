#include <AiCore.h>

namespace Ai {
    GLFWwindow* window;

    struct PainterObject {
        unsigned int VAO;
        unsigned int VBO;
    };

    PainterObject g_triangle;
    PainterObject g_square;

    float triangleVertices[9] = {
         0.0f, 0.1f, 1.0f,
         0.1f,-0.1f, 1.0f,
        -0.1f,-0.1f, 1.0f
    };

    std::vector<std::unique_ptr<Painter>> RenderObjectVector;

    std::map<std::string, unsigned int> ShaderMap;

    void renderAiInit() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(1000, 1000, "HelloWindow~", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(1);
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(1);
        }

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        g_triangle.VAO = VAO;
        g_triangle.VBO = VBO;

        addCanvasShader();
    }

    void renderAi()
    {
        while (!glfwWindowShouldClose(window))
        {
            if (RenderObjectVector.size() != 0) {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glUseProgram(ShaderMap["Canvas"]);

                int vertexScaleLocation;
                int vertexPosLocation;
                int vertexColorLocation;

                for (int i = 0; i < RenderObjectVector.size(); i++) {
                    switch (RenderObjectVector[i]->getObjectType()) {
                        case ObjectType::TRIANGLE:
                            glBindVertexArray(g_triangle.VAO);
                            vertexScaleLocation = glGetUniformLocation(ShaderMap["Canvas"], "scale");
                            std::pair<float, float> scale = RenderObjectVector[i]->getScale();
                            glUniform2f(vertexScaleLocation, scale.first, scale.second);
                            std::pair<float, float> pos = RenderObjectVector[i]->getPosition();
                            vertexPosLocation = glGetUniformLocation(ShaderMap["Canvas"], "pos");
                            glUniform2f(vertexPosLocation, pos.first, pos.second);
                            vertexColorLocation = glGetUniformLocation(ShaderMap["Canvas"], "ourColor");
                            glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
                            glDrawArrays(GL_TRIANGLES, 0, 3);
                            break;
                    }
                }
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            else {
                std::cout << "Nothing to rendering~" << std::endl;
                break;
            }
        }
    }

    void addCanvasShader()
	{
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "uniform vec2 pos;\n"
            "uniform vec2 scale;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x * scale.x, aPos.y * scale.y, aPos.z, 1.0) + vec4(pos, 0.0, 0.0);\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec4 ourColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = ourColor;\n"
            "}\n\0";
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        ShaderMap["Canvas"] = shaderProgram;
	}

    void addTriangle(float xscale, float yscale, float xpos, float ypos) {
        RenderObjectVector.push_back(std::make_unique<Triangle>(xscale, yscale, xpos, ypos));
    }
}