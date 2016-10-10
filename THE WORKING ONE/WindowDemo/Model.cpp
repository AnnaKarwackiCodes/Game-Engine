#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model()
{
	vertArr = 0;
	vertCount = 0;
}

Model::Model(char * nm, int type)
{
	name = nm;
	collisionType = type;
	vertArr = 0;
	vertCount = 0;
}


Model::~Model()
{
}

void Model::transMat()
{
	obj.trans.transMat = glm::translate(obj.trans.location) * 
		glm::yawPitchRoll(obj.trans.rotation.x, obj.trans.rotation.y, obj.trans.rotation.z)* 
		glm::scale(obj.trans.size);
}

bool Model::render()
{
	
	glUniformMatrix4fv(3, 1, GL_FALSE, &obj.trans.transMat[0][0]);
	
	glBindTexture(GL_TEXTURE_2D, text.texID);
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);

	//glBindVertexArray(vertArr);
	//glDrawArrays(GL_TRIANGLES, 0, vertCount);

	return true;
}

bool Model::bufferModel(std::string objFile)
{
	std::vector<glm::vec3> locations;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<VertInds> VertInd;

	std::string line;
	std::ifstream inFile;
	
	inFile.open(objFile);
	if (inFile.is_open())
	{
		while (std::getline(inFile, line))
		{
			std::istringstream fileShit(line);
			std::string label;
			fileShit >> label;
			if (label == "v") //location
			{
				float nums[3];
				fileShit >> nums[0] >> nums[1] >> nums[2];
				locations.push_back(glm::vec3(nums[0], nums[1], nums[2]));
			}
			else if (label == "vt")//uvs
			{
				float nums[2];
				fileShit >> nums[0] >> nums[1];
				uvs.push_back(glm::vec2(nums[0], nums[1]));
			}
			else if (label == "vn")//normal
			{
				float nums[3];
				fileShit >> nums[0] >> nums[1] >> nums[2];
				normals.push_back(glm::vec3(nums[0], nums[1], nums[2]));
			}
			else if (label == "f")//indices
			{
				unsigned int nums[3];
				char slash[2];
				for (int i = 0; i < 3; i++)
				{
					fileShit >> nums[0] >> slash[0] >> nums[1] >> slash[1] >> nums[2];
					for (int i = 0; i < 3; i++)
					{
						nums[i]--;
					}
					VertInds vi = { nums[0],nums[1],nums[2] };
					VertInd.push_back(vi);
				}
			}
		}
		inFile.close();
	}
	vertCount = VertInd.size();
	std::vector<Vertex> vertBufData(vertCount);
	for (int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = {
			locations[VertInd[i].locInd],
			uvs[VertInd[i].uvInd],
			normals[VertInd[i].normInd]
		};
	}
	
	GLuint vertBuf;
	
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);
	
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertCount, &vertBufData[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(glm::vec3));
	
	glEnableVertexAttribArray(1);
	

	glEnableVertexAttribArray(2); //normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
	glBindVertexArray(0);
	//lighting stuff
	//glVertexAttribPointer()

	// color
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	return true;
}

bool Model::setup()
{
	text.loadTexture(name);
	obj.trans.location = glm::vec3(0, 0, 0);
	obj.trans.rotation = glm::vec3(0, 0, 0);
	obj.trans.size = glm::vec3(.2, .2, .2);

	obj.bod.mass = 0.0f;
	obj.bod.force = glm::vec3(0,0,0);
	obj.bod.velocity = glm::vec3(0, 0, 0);
	return true;
}

bool Model::setup(glm::vec3 loc, glm::vec3 rot, glm::vec3 size)
{
	text.loadTexture(name);
	obj.trans.location = loc;
	obj.trans.rotation = rot;
	obj.trans.size = size;
	
	obj.bod.mass = 0.0f;
	obj.bod.force = glm::vec3(0, 0, 0);
	obj.bod.velocity = glm::vec3(0, 0, 0);
	return true;
}

void Model::newt(float delta, glm::vec3 dForce)
{
	vec = (dForce / delta) + obj.bod.velocity;

	accel = (vec - obj.bod.velocity) / delta;

	obj.bod.force = obj.bod.mass * accel;

	obj.bod.velocity = vec;

	glm::vec3 dp = obj.trans.location * obj.bod.force;
	glm::vec3 deltaR = obj.bod.velocity * delta;

	obj.trans.location += deltaR;
}

void Model::clearVel()
{
	obj.bod.velocity = glm::vec3(0, 0, 0);
}

bool Model::CollideWith(const Model& mod)
{
	// checks for colliderless collisions
	if (mod.collisionType == 1 || collisionType == 1) 
	{
		return false;
	}
	// checks for sphere
	else if (mod.collisionType == 2 && collisionType == 2)
	{
		if (sqrt(pow((mod.obj.trans.location.z - obj.trans.location.z), 2) + pow((mod.obj.trans.location.x - obj.trans.location.x), 2) + pow((mod.obj.trans.location.y - obj.trans.location.y), 2) ) > mod.obj.trans.size.x + obj.trans.size.x)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	// check for aabb
	else if (mod.collisionType == 3 && collisionType == 3)
	{
		//minx of mod and maxx of this
		if (mod.obj.trans.location.x - mod.obj.trans.size.x > obj.trans.location.x + obj.trans.size.x)
		{
			return false;
		}
		//maxx of mod and minx of this
		else if (mod.obj.trans.location.x + mod.obj.trans.size.x < obj.trans.location.x - obj.trans.size.x) 
		{
			return false;
		}
		//miny of mod and miny of this
		else if (mod.obj.trans.location.y - mod.obj.trans.size.y > obj.trans.location.y + obj.trans.size.y)
		{
			return false;
		}
		//maxy of mod and miny of this
		else if (mod.obj.trans.location.y + mod.obj.trans.size.y < obj.trans.location.y - obj.trans.size.y)
		{
			return false;
		}
		//minz of mod and maxz of this
		else if (mod.obj.trans.location.z - mod.obj.trans.size.z > obj.trans.location.z + obj.trans.size.z)
		{
			return false;
		}
		//maxz of mod and minz of this
		else if (mod.obj.trans.location.z + mod.obj.trans.size.z < obj.trans.location.z - obj.trans.size.z)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	//if they are either one or the other
	else if ((mod.collisionType == 2 || mod.collisionType == 3) && (collisionType == 2 || collisionType == 3))
	{
		float distance = 0.0f;
		if (mod.collisionType == 3)
		{
			for (int i = 0; i < 3; i++)
			{
				float min = mod.obj.trans.location[i] - mod.obj.trans.size[i];
				float max = mod.obj.trans.location[i] + mod.obj.trans.size[i];
				float v = obj.trans.location[i];

				if (v < min) distance += (min - v)*(min - v);
				if (v > max) distance += (v - max)*(v - max);
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				float min = obj.trans.location[i] - obj.trans.size[i];
				float max = obj.trans.location[i] + obj.trans.size[i];
				float v = mod.obj.trans.location[i];

				if (v < min) distance += (min - v)*(min - v);
				if (v > max) distance += (v - max)*(v - max);
			}
		}
		return distance < mod.obj.trans.size.x * obj.trans.size.x;
	}
	// else return true
	else 
	{
		return true;
	}
}

void Model::TextureChange(char * nm)
{
	name = nm;
}
