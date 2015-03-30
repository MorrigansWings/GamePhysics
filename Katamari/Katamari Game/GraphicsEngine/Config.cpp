#include "Config.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "GraphicsManager.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "Log.h"
#include "Entity.h"
#include "Scene.h"
#include "HeightMap.h"
#include "Camera.h"

Map<ConfigKey, vec4> Config::s_ConfigVec4;

Map<ConfigKey, vec3> Config::s_ConfigVec3;

Map<ConfigKey, vec2> Config::s_ConfigVec2;

Map<ConfigKey, string> Config::s_ConfigString;

Map<ConfigKey, bool> Config::s_ConfigBool;

Map<ConfigKey, float> Config::s_ConfigFloat;

Map<ConfigKey, int> Config::s_ConfigInt;

void Config::LoadFile( const string& filename )
{
	Log::InfoFmt("Config", "Loading file %s", filename.c_str());

	Buffer file = Buffer::LoadFromFile(filename);
	const string& dirname = Arc_Dirname(filename);

	int offset = 0;

	while ( ! file.endOfBuffer())
	{
		string line = file.readNextLine();

		offset = 0;

		if (line.size() == 0)
			continue;

		int  lineStartInd = 0;
		bool skipLine   = false;
		bool hasCommand = false;

		bool allWhitespace = true;
		for (unsigned int i = 0; i < line.size(); ++i)
		{
			char& ch = line[i];

			if (ch == '#')
			{
				skipLine = true;
				break;
			}
			else if (ch == '!')
			{
				hasCommand = true;
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
			else if (ch != ' ' && ch != '\t' && ch != '\n')
			{
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
		}

		if (skipLine || allWhitespace)
			continue;

		if (hasCommand)
		{
			++lineStartInd; // Skip the bang
			const string& cmd = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (cmd == "Include")
			{
				const string& newFilename = ReadString(line, lineStartInd, offset);
				lineStartInd += offset;

				if (newFilename.size() != 0)
					LoadFile(dirname + "/" + newFilename);
			}
			else if (cmd == "LoadModel")
			{
				const string& filename = ReadString(line, lineStartInd, offset);
				lineStartInd += offset;

				GraphicsManager::GetInstance()->getResourceManager()->loadModelFile(filename);
			}
			else if (cmd == "Scene")
			{
				const string& name = ReadString(line, lineStartInd, offset);
				lineStartInd += offset;

				GraphicsManager::GetInstance()->getSceneManager()->addScene(name, ReadScene(name, file, dirname));
			}
			else if (cmd == "InitialScene")
			{
				const string& name = ReadString(line, lineStartInd, offset);
				lineStartInd += offset;

				GraphicsManager::GetInstance()->getSceneManager()->setCurrentScene(name);
			}
			else if (cmd == "Shader")
			{
				const string& name = ReadString(line, lineStartInd, offset);
				lineStartInd += offset;

				ReadShader(name, file, dirname);
			}
		}
		else // No command, must be config data
		{
			const string& name = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			const string& type = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (type == "string")
			{
				const string& val = ReadString(line, lineStartInd, offset);
				s_ConfigString.add(name, val);
				lineStartInd += offset;
			}
			else if (type == "int")
			{
				const int& val = ReadInt(line, lineStartInd, offset);
				s_ConfigInt.add(name, val);
				lineStartInd += offset;
			}
			else if (type == "float")
			{
				const float& val = ReadFloat(line, lineStartInd, offset);
				s_ConfigFloat.add(name, val);
				lineStartInd += offset;
			}
			else if (type == "bool")
			{
				const bool& val = ReadBool(line, lineStartInd, offset);
				s_ConfigBool.add(name, val);
				lineStartInd += offset;
			}
			else if (type == "vec2")
			{
				const vec2& val = ReadVec2(line, lineStartInd, offset);
				s_ConfigVec2.add(name, val);
				lineStartInd += offset;
			}
			else if (type == "vec3")
			{
				const vec3& val = ReadVec3(line, lineStartInd, offset);
				s_ConfigVec3.add(name, val);
				lineStartInd += offset;
			}
			else if (type == "vec4")
			{
				const vec4& val = ReadVec4(line, lineStartInd, offset);
				s_ConfigVec4.add(name, val);
				lineStartInd += offset;
			}
			else if (type == "color")
			{
				const vec4& val = ReadColor(line, lineStartInd, offset);
				s_ConfigVec4.add(name, val);
				lineStartInd += offset;
			}
		}
	}
}

Scene* Config::ReadScene( const string& name, Buffer& file, const string& dirname )
{
	Scene* pScene = New Scene();

	string skyboxTex;

	int offset = 0;

	while ( ! file.endOfBuffer())
	{
		string line = file.readNextLine();

		if (line.size() == 0)
			continue;

		offset = 0;

		int  lineStartInd = 0;
		bool skipLine   = false;
		bool hasCommand = false;

		bool allWhitespace = true;
		for (unsigned int i = 0; i < line.size(); ++i)
		{
			char& ch = line[i];

			if (ch == '#')
			{
				skipLine = true;
				break;
			}
			else if (ch == '!')
			{
				hasCommand = true;
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
			else if (ch != ' ' && ch != '\t' && ch != '\n')
			{
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
		}

		if (skipLine || allWhitespace)
			continue;

		if (hasCommand)
		{
			++lineStartInd; // Skip the bang
			const string& cmd = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;
			
			if (cmd == "EndScene")
			{
				break;
			}
			else if (cmd == "Include")
			{
				const string& newFilename = ReadString(line, lineStartInd, offset);

				if (newFilename.size() != 0)
					LoadFile(dirname + "/" + newFilename);
			}
			else if (cmd == "LoadModel")
			{
				const string& filename = ReadString(line, lineStartInd, offset);

				GraphicsManager::GetInstance()->getResourceManager()->loadModelFile(filename);
			}
			else if (cmd == "Skybox")
			{
				skyboxTex = ReadString(line, lineStartInd, offset);
			}
			else if (cmd == "HeightMap")
			{
				const string& name = ReadString(line, lineStartInd, offset);

				pScene->addHeightMap(name, ReadHeightMap(name, file, dirname));
			}
			else if (cmd == "Camera")
			{
				const string& name = ReadString(line, lineStartInd, offset);

				Camera* pCamera = ReadCamera(name, file, dirname);

				pScene->addCamera(name, pCamera);
			}
			else if (cmd == "InitialCamera")
			{
				const string& name = ReadString(line, lineStartInd, offset);

				pScene->setCurrentCamera(name);
			}
			else if (cmd == "Entity")
			{
				const string& name = ReadString(line, lineStartInd, offset);

				pScene->addEntity(name, ReadEntity(name, file, dirname));
			}
		}
		else // No command, must be config data
		{
			const string& name = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

		}
	}

	pScene->loadSkybox(skyboxTex);

	return pScene;
}

Camera* Config::ReadCamera( const string& name, Buffer& file, const string& dirname )
{
	GLfloat fov = 0.0f, vNear = 0.0f, vFar = 0.0f, speed = 0.0f;
	vec3 pos(0.0f), dir(0.0f), up(0.0f);

	int offset = 0;

	while ( ! file.endOfBuffer())
	{
		string line = file.readNextLine();

		if (line.size() == 0)
			continue;

		offset = 0;

		int  lineStartInd = 0;
		bool skipLine   = false;
		bool hasCommand = false;

		bool allWhitespace = true;
		for (unsigned int i = 0; i < line.size(); ++i)
		{
			char& ch = line[i];

			if (ch == '#')
			{
				skipLine = true;
				break;
			}
			else if (ch == '!')
			{
				hasCommand = true;
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
			else if (ch != ' ' && ch != '\t' && ch != '\n')
			{
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
		}

		if (skipLine || allWhitespace)
			continue;

		if (hasCommand)
		{
			++lineStartInd; // Skip the bang
			const string& cmd = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (cmd == "EndCamera")
			{
				break;
			}
			else if (cmd == "Include")
			{
				const string& newFilename = ReadString(line, lineStartInd, offset);

				if (newFilename.size() != 0)
					LoadFile(dirname + "/" + newFilename);
			}
		}
		else // No command, must be config data
		{
			const string& name = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (name == "Position")
			{
				pos = ReadVec3(line, lineStartInd, offset);
			}
			else if (name == "Direction")
			{
				dir = ReadVec3(line, lineStartInd, offset);
			}
			else if (name == "Up")
			{
				up = ReadVec3(line, lineStartInd, offset);
			}
			else if (name == "FOV")
			{
				fov = ReadFloat(line, lineStartInd, offset);
			}
			else if (name == "Near")
			{
				vNear = ReadFloat(line, lineStartInd, offset);
			}
			else if (name == "Far")
			{
				vFar = ReadFloat(line, lineStartInd, offset);
			}
			else if (name == "Speed")
			{
				speed = ReadFloat(line, lineStartInd, offset);
			}
		}
	}

	return New Camera((GLfloat)GraphicsManager::GetInstance()->getWidth(), (GLfloat)GraphicsManager::GetInstance()->getHeight(), pos, dir, up, fov, vNear, vFar, speed);
}

Entity* Config::ReadEntity( const string& name, Buffer& file, const string& dirname )
{
	vec3 pos, rot, scale;
	ArrayList<string> modelNames;

	int offset = 0;

	while ( ! file.endOfBuffer())
	{
		string line = file.readNextLine();

		if (line.size() == 0)
			continue;

		offset = 0;

		int  lineStartInd = 0;
		bool skipLine   = false;
		bool hasCommand = false;

		bool allWhitespace = true;
		for (unsigned int i = 0; i < line.size(); ++i)
		{
			char& ch = line[i];

			if (ch == '#')
			{
				skipLine = true;
				break;
			}
			else if (ch == '!')
			{
				hasCommand = true;
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
			else if (ch != ' ' && ch != '\t' && ch != '\n')
			{
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
		}

		if (skipLine || allWhitespace)
			continue;

		if (hasCommand)
		{
			++lineStartInd; // Skip the bang
			const string& cmd = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (cmd == "EndEntity")
			{
				break;
			}
			else if (cmd == "Include")
			{
				const string& newFilename = ReadString(line, lineStartInd, offset);

				if (newFilename.size() != 0)
					LoadFile(dirname + "/" + newFilename);
			}
		}
		else // No command, must be config data
		{
			const string& name = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (name == "Position")
			{
				pos = ReadVec3(line, lineStartInd, offset);
			}
			else if (name == "Rotation")
			{
				rot = ReadVec3(line, lineStartInd, offset);
			}
			else if (name == "Scale")
			{
				scale = ReadVec3(line, lineStartInd, offset);
			}
			else if (name == "Model")
			{
				modelNames.add(ReadString(line, lineStartInd, offset));
			}
		}
	}

	Entity* pEntity = New Entity(pos, rot, scale);

	for (unsigned int i = 0; i < modelNames.getSize(); ++i)
	{
		pEntity->addModel(GraphicsManager::GetInstance()->getResourceManager()->getModel(modelNames[i]));
	}

	return pEntity;
}

HeightMap* Config::ReadHeightMap( const string& name, Buffer& file, const string& dirname )
{
	GLfloat width, height, minHeight, maxHeight;
	int samples;
	vec3 pos(0.0f);
	string heightDataFilename, textureFilename;

	int offset = 0;

	while ( ! file.endOfBuffer())
	{
		string line = file.readNextLine();

		if (line.size() == 0)
			continue;

		offset = 0;

		int  lineStartInd = 0;
		bool skipLine   = false;
		bool hasCommand = false;

		bool allWhitespace = true;
		for (unsigned int i = 0; i < line.size(); ++i)
		{
			char& ch = line[i];

			if (ch == '#')
			{
				skipLine = true;
				break;
			}
			else if (ch == '!')
			{
				hasCommand = true;
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
			else if (ch != ' ' && ch != '\t' && ch != '\n')
			{
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
		}

		if (skipLine || allWhitespace)
			continue;

		if (hasCommand)
		{
			++lineStartInd; // Skip the bang
			const string& cmd = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (cmd == "EndHeightMap")
			{
				break;
			}
			else if (cmd == "Include")
			{
				const string& newFilename = ReadString(line, lineStartInd, offset);

				if (newFilename.size() != 0)
					LoadFile(dirname + "/" + newFilename);
			}
		}
		else // No command, must be config data
		{
			const string& name = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (name == "Position")
			{
				pos = ReadVec3(line, lineStartInd, offset);
			}
			else if (name == "Width")
			{
				width = ReadFloat(line, lineStartInd, offset);
			}
			else if (name == "Height")
			{
				height = ReadFloat(line, lineStartInd, offset);
			}
			else if (name == "Samples")
			{
				samples = ReadInt(line, lineStartInd, offset);
			}
			else if (name == "MaxHeight")
			{
				maxHeight = ReadFloat(line, lineStartInd, offset);
			}
			else if (name == "MinHeight")
			{
				minHeight = ReadFloat(line, lineStartInd, offset);
			}
			else if (name == "HeightDataFile")
			{
				heightDataFilename = ReadString(line, lineStartInd, offset);
			}
			else if (name == "TextureFile")
			{
				textureFilename = ReadString(line, lineStartInd, offset);
			}
		}
	}

	return New HeightMap(heightDataFilename, textureFilename, width, height, maxHeight, minHeight, samples);
}

void Config::ReadShader( const string& name, Buffer& file, const string& dirname )
{
	ArrayList<Shader> shaders;

	int offset = 0;

	while ( ! file.endOfBuffer())
	{
		string line = file.readNextLine();

		if (line.size() == 0)
			continue;

		offset = 0;

		int  lineStartInd = 0;
		bool skipLine   = false;
		bool hasCommand = false;

		bool allWhitespace = true;
		for (unsigned int i = 0; i < line.size(); ++i)
		{
			char& ch = line[i];

			if (ch == '#')
			{
				skipLine = true;
				break;
			}
			else if (ch == '!')
			{
				hasCommand = true;
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
			else if (ch != ' ' && ch != '\t' && ch != '\n')
			{
				allWhitespace = false;

				if (lineStartInd == 0)
					lineStartInd = i;

				break;
			}
		}

		if (skipLine || allWhitespace)
			continue;

		if (hasCommand)
		{
			++lineStartInd; // Skip the bang
			const string& cmd = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (cmd == "EndShader")
			{
				break;
			}
			else if (cmd == "Include")
			{
				const string& newFilename = ReadString(line, lineStartInd, offset);

				if (newFilename.size() != 0)
					LoadFile(dirname + "/" + newFilename);
			}
		}
		else // No command, must be config data
		{
			const string& name = ReadUntilWhitespace(line, lineStartInd, offset);
			lineStartInd += offset;

			if (name == "Vert")
			{
				const string& filename = ReadString(line, lineStartInd, offset);
				lineStartInd += offset;

				shaders.add(Shader(filename, GL_VERTEX_SHADER));
			}
			else if (name == "Frag")
			{
				const string& filename = ReadString(line, lineStartInd, offset);
				lineStartInd += offset;

				shaders.add(Shader(filename, GL_FRAGMENT_SHADER));
			}
		}
	}

	GraphicsManager::GetInstance()->getShaderManager()->loadProgram(name, shaders);
}

string Config::ReadUntilWhitespace( const string& str, const int& start, int& offset )
{
	int realStart = -1;
	int end = -1;
	bool inString = false;

	for (unsigned int i = start; i < str.size(); ++i)
	{
		const char& ch = str[i];

		if (ch == ' ' || ch == '\t' || ch == '\n')
		{
			if (inString)
			{
				end = i - 1;
				break;
			}
		}
		else
		{
			if ( ! inString)
			{
				inString = true;
				realStart = i;
			}
		}
	}

	if (realStart == -1)
		return "";

	if (end == -1)
		end = str.size() - 1;

	offset = (end - start + 1);

	return str.substr(realStart, end - realStart + 1);
}

string Config::ReadString( const string& str, const int& start, int& offset )
{
	int realStart = -1;
	int end = -1;
	bool inString = false;

	for (unsigned int i = start; i < str.size(); ++i)
	{
		const char& ch = str[i];

		if (ch == '"')
		{
			if (inString)
			{
				end = i - 1;
			}
			else
			{
				inString = true;
				realStart = i + 1;
			}
		}

	}

	if (realStart == -1)
		return "";

	if (end == -1)
		end = str.size() - 1;

	offset = (end - start + 1);

	return str.substr(realStart, end - realStart + 1);
}

int Config::ReadInt( const string& str, const int& start, int& offset )
{
	const string& raw = ReadUntilWhitespace(str, start, offset);

	return Arc_ParseInt(raw);
}

float Config::ReadFloat( const string& str, const int& start, int& offset )
{
	const string& raw = ReadUntilWhitespace(str, start, offset);

	return Arc_ParseFloat(raw);
}

bool Config::ReadBool( const string& str, const int& start, int& offset )
{
	const string& raw = ReadUntilWhitespace(str, start, offset);

	return Arc_ParseBool(raw);
}

vec2 Config::ReadVec2( const string& str, const int& start, int& offset )
{
	int tmpOffset = 0;
	offset = 0;

	const string& raw1 = ReadUntilWhitespace(str, start, tmpOffset);
	offset += tmpOffset;

	const string& raw2 = ReadUntilWhitespace(str, start + offset, tmpOffset);
	offset += tmpOffset;

	return vec2(Arc_ParseFloat(raw1), Arc_ParseFloat(raw2));
}

vec3 Config::ReadVec3( const string& str, const int& start, int& offset )
{
	int tmpOffset = 0;
	offset = 0;

	const string& raw1 = ReadUntilWhitespace(str, start, tmpOffset);
	offset += tmpOffset;

	const string& raw2 = ReadUntilWhitespace(str, start + offset, tmpOffset);
	offset += tmpOffset;

	const string& raw3 = ReadUntilWhitespace(str, start + offset, tmpOffset);
	offset += tmpOffset;

	return vec3(Arc_ParseFloat(raw1), Arc_ParseFloat(raw2), Arc_ParseFloat(raw3));
}

vec4 Config::ReadVec4( const string& str, const int& start, int& offset )
{
	int tmpOffset = 0;
	offset = 0;

	const string& raw1 = ReadUntilWhitespace(str, start, tmpOffset);
	offset += tmpOffset;

	const string& raw2 = ReadUntilWhitespace(str, start + offset, tmpOffset);
	offset += tmpOffset;

	const string& raw3 = ReadUntilWhitespace(str, start + offset, tmpOffset);
	offset += tmpOffset;

	const string& raw4 = ReadUntilWhitespace(str, start + offset, tmpOffset);
	offset += tmpOffset;

	return vec4(Arc_ParseFloat(raw1), Arc_ParseFloat(raw2), Arc_ParseFloat(raw3), Arc_ParseFloat(raw4));
}

vec4 Config::ReadColor( const string& str, const int& start, int& offset )
{
	return ReadVec4(str, start, offset) / 255.0f;
}