#ifndef _PADDLE_DROID_BALL_HPP
#define _PADDLE_DROID_BALL_HPP

static const float BALL_HALF_WIDTH = 0.015f;
static const float BALL_HALF_HEIGHT = 0.015f;
static const float BALL_START_X = 0.0f;
static const float BALL_START_Y = 0.0f;
static const float BALL_VELOCITY = 0.015f;
static const float BALL_LEFT_BOUND = (-1.0f + BALL_HALF_WIDTH);
static const float BALL_RIGHT_BOUND = (1.0f - BALL_HALF_WIDTH);
static const float BALL_TOP_BOUND = (1.0f - BALL_HALF_HEIGHT);
static const float BALL_BOTTOM_BOUND = (-1.0f + BALL_HALF_HEIGHT);

#endif
