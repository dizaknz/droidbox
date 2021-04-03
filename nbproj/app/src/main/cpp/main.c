#include <android_native_app_glue.h>

#include "common.h"

static void handle_cmd(struct android_app* app, int32_t cmd) {
    // STUB
}

static int32_t handle_input(struct android_app* app, AInputEvent* event) {
    // STUB
    return 0;
}

void android_main(struct android_app* app) {
    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;
    
    sensorManager = ASensorManager_getInstance();
	  accelerometerSensor = ASensorManager_getDefaultSensor(
	      sensorManager,
	      ASENSOR_TYPE_ACCELEROMETER
    );
	  sensorEventQueue = ASensorManager_createEventQueue(
	      sensorManager,
	      app->looper,
	      LOOPER_ID_USER,
	      NULL,
        NULL
    );

    while (1) {
        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {
            if (source != NULL) {
                source->process(app, source);
            }

            if (ident == LOOPER_ID_USER) {
                if (accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0)
                    {
                        LOGD("Sensor event - accelerometer: [%f, %f, %f] time: %lld",
                             event.acceleration.x,
                             event.acceleration.y,
                             event.acceleration.z,
                             event.timestamp
                        );
                    }
                }
            }

            if (app->destroyRequested != 0) {
                // STUB - destroy
                return;
            }
        }

        // STUB - render
        LOGD("Rendering event");
    }
}


