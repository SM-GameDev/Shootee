#include "screen.h"
#include <algorithm>

Screen::Screen(const unsigned int width, const unsigned int height)
	: width(width), height(height)
{
	texture = LoadRenderTexture(width, height);
	//SetTextureFilter(texture.texture, TEXTURE_FILTER_BILINEAR);
}

Screen::~Screen() {
	if(IsRenderTextureValid(texture)) {
		UnloadRenderTexture(texture);
	}
}

void Screen::beginDrawing() const {
	BeginTextureMode(texture);
}

void Screen::endDrawing() const {
	EndTextureMode();
}

void Screen::renderTo(const Rectangle& destinationBounds, const Anchor anchorPoint, RenderTexture* destination) {
	float scaleX =	destinationBounds.width / width; 
	float scaleY = destinationBounds.height / height;
	float scale = std::min(scaleX, scaleY);
	outputBounds = Rectangle{destinationBounds.x, destinationBounds.y, width*scale, height*scale};
	
	//Adjusting X-Bounds
	if(anchorPoint == TOP_RIGHT || anchorPoint == BOTTOM_RIGHT) {
		outputBounds.x += (destinationBounds.width - outputBounds.width);
	} else if(anchorPoint == CENTER) {
		outputBounds.x += (destinationBounds.width - outputBounds.width) / 2;
	}

	//Adjusting Y-Bounds
	if(anchorPoint == BOTTOM_LEFT || anchorPoint == BOTTOM_RIGHT) {
		outputBounds.y += (destinationBounds.height - outputBounds.height);
	} else if(anchorPoint == CENTER) {
		outputBounds.y += (destinationBounds.height - outputBounds.height) / 2;
	}

	//Drawing
	if(destination != nullptr) {
		BeginTextureMode(*destination);
	}
	
	DrawTexturePro(texture.texture, Rectangle{0, float(height), (float)width, -(float)height}, outputBounds, Vector2{0, 0}, 0, WHITE);
	
	if(destination != nullptr) {
		EndTextureMode();	
	}
}

Rectangle Screen::getOutputBounds() const {
	return outputBounds;
}

Vector2 Screen::getDimensions() const {
	return Vector2{(float)width, (float)height};
}
