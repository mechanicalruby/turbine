#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>

enum BlendMode {
	BLENDING_OFF,
	BLENDING_ALPHA
};

enum ViewportMode {
	VIEWPORT_2D, // Expand viewport
	VIEWPORT_KEEP_WIDTH,
	VIEWPORT_KEEP_HEIGHT,
};

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	virtual bool should_window_close() = 0;
	// initialization
	virtual void initialize();
	virtual void cleanup();

	// control
	virtual void begin_frame();
	virtual void end_frame();

	virtual void clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	virtual void set_blend_mode(BlendMode mode);
};

#endif