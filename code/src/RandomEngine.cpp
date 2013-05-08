#include "RandomEngine.h"

RandomEngine* RandomEngine::engineInstance = NULL;

RandomEngine::RandomEngine():
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	intDistribution(),
	realDistribution()
{ }

RandomEngine::~RandomEngine()
{ }

RandomEngine* RandomEngine::getRandomEngineInstance()
{
	if (!engineInstance) { engineInstance = new RandomEngine(); }
	return engineInstance;
}

int RandomEngine::getRandomInt(int min, int max)
{
	std::uniform_int_distribution<int>::param_type ptype;
	ptype = std::uniform_int_distribution<int>::param_type(min, max);
	intDistribution.param(ptype);

	return intDistribution(generator);
}

float RandomEngine::getRandomFloat(float min, float max)
{
	std::uniform_real_distribution<float>::param_type ptype;
	ptype = std::uniform_real_distribution<float>::param_type(min, max);
	realDistribution.param(ptype);

	return realDistribution(generator);
}
