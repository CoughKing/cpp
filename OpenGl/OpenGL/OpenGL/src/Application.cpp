#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

#include <sstream>

struct ShaderProgramSource
{
   std::string vertexShaderSource;
   std::string fragmentShaderSource;
};
//vertex shader
static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;//vertex
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;//fragemnrt
        }
        else if (type != ShaderType::NONE)
        {
            ss[(int)type] << line << '\n';
        }
        else
        {
            //
        }
    }

    return { ss[0].str(), ss[1].str() };

}
//const char *vertexShaderSource = "#version 330 core\n"
//                            "layout(location = 0) in vec3 aPos;\n"
//                            "layout(location = 1) in vec3 aColor;\n"
//                            "out vec3 ourColor;\n"  //specify A color output to the fragment shader
//                            "void main()\n"
//                            "{\n"
//                            "     gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //vec3 to vec4 conmstructor (direrctly)
//                            "     ourColor = aColor;\n" //set the output to dark red
//                            "}\0";
////unsigned int vertexShader;
////vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
////fragment shader
//const char *fragmentShaderSource = "#version 330 core\n"
//                            "out vec4 FragColor;\n"
//                            "in vec3 ourColor;\n" //input from vertexShader
//                            "void main()\n"
//                            "{\n"
//                            "FragColor = vec4(ourColor, 1.0);\n"
//                            "}\0";


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    int success;
    //char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));

        glGetShaderInfoLog(id, length,&length, message);
        std::cout << "Failed to Compile. The Error : \n"<<(type == GL_VERTEX_SHADER ? "Vertex" : "Fragement") 
            << "Shader!!!" <<std::endl << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glewInit();
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Triangle Fortress", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) 
		std::cout << "Error initializing GLEW" << std::endl;
   
    
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    //--------
   /* int success;
    char infoLog[512];*/
    //vertex array obj

    
    /*unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &source.vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error : \n" << infoLog << std::endl;
    }
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &source.fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); 
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error : \n" << infoLog << std::endl;
    }*/
    /*unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error : \n" << infoLog << std::endl;
    }*/
    /*glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);*/
    //--
    float positions[] = { 
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,// 0
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,// 1
        0.5f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,// 2
       -0.5f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,// 3
       -0.35f, 0.2f, 0.0f,   0.0f, 1.0f, 0.0f,// 4
       -0.15f, 0.2f, 0.0f,   1.0f, 0.0f, 1.0f,// 5
        0.15f, 0.2f, 0.0f,   0.0f, 1.0f, 0.0f,// 6
        0.35f, 0.2f, 0.0f,   1.0f, 1.0f, 0.0f,// 7
       -0.25f, 0.4f, 0.0f,   1.0f, 0.0f,1.0f,// 8
        0.25f, 0.4f, 0.0f,    0.0f, 0.0f, 1.0f// 9
    };

    unsigned int indices[] = {
        //wall
        0, 1, 2,
        2, 3, 0,
        // Left tower body
        3, 4, 5,
        5, 3, 0,
        // Left tower roof
        4, 5, 8,
        // Right tower body
        2, 6, 7,
        6, 2, 1,
        // Right tower roof
        6, 7, 9
    };

    //vertex buffer obj
	unsigned int VBO, VAO, EBO;
    
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,   sizeof(positions), positions, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position atrribite
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  
   /* glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error : \n" << infoLog << std::endl;
    }*/
    
    //glUseProgram(shaderProgram);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    std::cout << source.vertexShaderSource << "\n" << source.fragmentShaderSource << std::endl;
    unsigned int prgrm = CreateShader(source.vertexShaderSource, source.fragmentShaderSource);
    glUseProgram(prgrm);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //cleear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //load the program ie activate the shader
        /*unsigned int prgrm = CreateShader(source.vertexShaderSource, source.fragmentShaderSource);
        glUseProgram(prgrm);*/
        //for varying color
        double timeValue = glfwGetTime();
        double greenValue = ((sin(timeValue) / 2.0f) + 0.5f);
        int vertexColorLocation = glGetUniformLocation(prgrm, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        //render the triangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glBindVertexArray(0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(prgrm);

    glfwTerminate();
    return 0;
}

