#include "ComponentImage.h"





ComponentImage::ComponentImage(GameObject * my_go):Component(my_go)
{
	component_name = "Image";
	type = CANVAS_IMAGE;

}

ComponentImage::~ComponentImage()
{
}

Quad::Quad(int pos_x, int pos_y, int width, int height):pos_x(pos_x),pos_y(pos_y),width(width),height(height)
{
	SetUpVertices();
}

void Quad::SetUpVertices()
{
	vertices[0] = pos_x;
	vertices[1] = pos_y;
	vertices[3] = pos_x;
	vertices[4] = pos_y + height;
	vertices[6] = pos_x + width;
	vertices[7] = pos_y + height;
	vertices[9] = pos_x + width;
	vertices[10] = pos_y;

}
