#include "Engine.h"
#include "Texture.h"

int main()
{
	Engine engine;
	Texture text;

	if (!engine.init())
		return -1;

	if (engine.useShaders())
	{
		engine.loadModel();
		engine.bufferModels();
		engine.gameLoop();
	}
     return 0;
}