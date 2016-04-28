#include "ShaderManager.h"

using std::ifstream;
using std::ios;

using std::cout;
using std::endl;

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

GLuint ShaderManager::getProgram() const
{
	return program;
}

bool ShaderManager::loadShaders(const char * vertexFile, const char * fragmentFile)
{
	GLuint vert = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vert == 0)
	{
		cout << "loadShaders fail" << endl;
		return 0;
	}
	GLuint frag = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (frag == 0)
	{
		return 0;
	}

	program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);

	GLint* var = new GLint();
	glGetProgramiv(program, GL_LINK_STATUS, var);

	if (*var == 0)
	{
		GLint* logLength = new GLint();
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, logLength);

		GLchar* error = new GLchar();
		glGetProgramInfoLog(program, *logLength, 0, error);
		cout << error << endl;

		glDeleteShader(program);
		delete[] logLength;
		delete[] error;
		delete[] var;
		return false;
	}

	delete[] var;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

GLuint ShaderManager::loadShader(const char * file, GLenum shaderType)
{
	ifstream binary(file, ios::binary);
	if (binary.is_open())
	{
		// get length
		binary.seekg(0, ios::end);
		unsigned int length = (int)binary.tellg();
		binary.seekg(0, ios::beg);

		// read file
		char* fileContents = new char[length + 1];
		binary.read(fileContents, length);
		fileContents[length] = '\0';

		binary.close();

		GLuint shadObj = glCreateShader(shaderType);
		glShaderSource(shadObj, 1, &fileContents, 0);
		glCompileShader(shadObj);

		delete[] fileContents;

		GLint* var = new GLint();
		glGetShaderiv(shadObj, GL_COMPILE_STATUS, var);

		if (*var != 0)
		{
			return shadObj;
		}
		else
		{
			GLint* logLength = new GLint();
			glGetShaderiv(shadObj, GL_INFO_LOG_LENGTH, logLength);
			GLchar* error = new GLchar[*logLength];
			glGetShaderInfoLog(shadObj, *logLength, 0, error);

			cout << error << endl;
			glDeleteShader(shadObj);
			delete[] logLength;
			delete[] error;
			delete[] var;
			return 0;
		}
	}
	else
	{
		cout << "loadshader fail" << endl;
	}
	return GLuint();
}
