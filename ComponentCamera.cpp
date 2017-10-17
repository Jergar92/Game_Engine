#include "ComponentCamera.h"



ComponentCamera::ComponentCamera(GameObject* my_go) :Component(my_go)
{

}


ComponentCamera::~ComponentCamera()
{
}

bool ComponentCamera::ObjectInside()
{
	return false;
}
