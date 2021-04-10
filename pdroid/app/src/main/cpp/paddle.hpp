#ifndef _PADDLE_DROID_PADDLE_HPP
#define _PADDLE_DROID_PADDLE_HPP

static const float PADDLE_HALF_WIDTH = 0.15f;
static const float PADDLE_HALF_HEIGHT = 0.020f;
static const float PADDLE_START_X = 0.0f;
static const float PADDLE_START_Y = -0.725f;
static const float PADDLE_LEFT_BOUND = (-1.0f + PADDLE_HALF_WIDTH);
static const float PADDLE_RIGHT_BOUND = (1.0f - PADDLE_HALF_WIDTH);
static const float PADDLE_TOUCH_OFFSET = 0.35f;

typedef struct Paddle {
	float x;
	float y;
} Paddle;

// TODO: implement Renderable 
// paddle.render(..);

#endif
