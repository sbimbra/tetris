#include "GameObject.h"

Image* GameObject::getImage()
{
	return myImage;
}

Rectangle& GameObject::getBounds()
{
	return bounds;
}

void GameObject::resized(int width, int height)
{
}

void GameObject::lockImage()
{
	imageCriticalSection.enter();
}

void GameObject::unlockImage()
{
	imageCriticalSection.exit();
}