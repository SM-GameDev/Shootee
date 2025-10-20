#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"

typedef enum Anchor {
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	CENTER
} Anchor;

class Screen {
	RenderTexture texture;
	const unsigned int width;
	const unsigned int height;
	Rectangle outputBounds;
	
	public:
	Screen(const unsigned int width = 640, const unsigned int height = 480);

	~Screen();

	/**
	 * @brief Sets render mode to the screen's render texture
	 */
	void beginDrawing() const;
	
	/**
	 * @brief Sets render mode back to the window texture
	 */
	void endDrawing() const;
	
	/**
	 * @brief Renders the screen scaled to fill the destination without stretching
	 * @oaram destination The texture to be drawn to
	 * @param destinationBounds The rectangle to which the screen will be rendered
	 * @param anchorPoint Determines the positional offset if the screen and destination have different aspect ratios
	 * @note textureMode will be set to the window texture after execution
	 */
	void renderTo(const Rectangle& destinationBounds, const Anchor anchorPoint, RenderTexture* destination = nullptr);

	Rectangle getOutputBounds() const;
	
	Vector2 getDimensions() const;
};

#endif
