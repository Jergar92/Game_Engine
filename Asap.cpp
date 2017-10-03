#include "Asap.h"
#include "Globals.h"
Asap::Asap()
{
}

Asap::~Asap()
{
}

bool Asap::LoadMesh(const char * path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading mesh path: %s", path);
	return false;
}
