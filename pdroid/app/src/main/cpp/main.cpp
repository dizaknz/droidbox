#include <jni.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <cstdlib>
#include <cstring>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "engine.hpp"

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
	//Engine *engine = static_cast<Engine*>(app->userData);
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		int32_t ret = 0;

		int32_t action = AMotionEvent_getAction(event);
		if (action == AMOTION_EVENT_ACTION_DOWN || action == AMOTION_EVENT_ACTION_MOVE) {
            // touchdown
			// engine->touchIsDown(true);
			ret = 1;
		}
		else if (action == AMOTION_EVENT_ACTION_UP) {
			// engine->touchIsDown(false);
			ret = 1;
		}

		if (ret) {
			//engine->SetTouchX(static_cast<float>(AMotionEvent_getRawX(event, 0)));
			//engine->SetTouchY(static_cast<float>(AMotionEvent_getRawY(event, 0)));
		}
		return ret;
	}
	return 0;
}

static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
	Engine *engine = static_cast<Engine*>(app->userData);
	switch (cmd) {
	case APP_CMD_INIT_WINDOW:
		if (engine->Active()) {
            engine->Init();
            // engine->Render();
		}
		break;
	case APP_CMD_TERM_WINDOW:
        engine->Close();
		break;
	}
}

void android_main(struct android_app* app) {
	Engine engine = Engine(app);
	app->userData = &engine;
	app->onAppCmd = engine_handle_cmd;
	app->onInputEvent = engine_handle_input;

	while (1) {
		int ident;
		int events;
		struct android_poll_source* source;

        // engine->Animating() ? 0 : -1
		while ((ident=ALooper_pollAll(0, NULL, &events, reinterpret_cast<void**>(&source))) >= 0)
		{
			if (source != NULL) {
				source->process(app, source);
			}
			if (app->destroyRequested != 0) {
				// engine->Close();
				return;
			}
		}
        // engine->Update();
        // engine->Render();
	}
}
