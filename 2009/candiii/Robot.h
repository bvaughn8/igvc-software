#ifndef ROBOT_H_
#define ROBOT_H_

/*
 * This file represents the robot and all its functions
 *   by: Chris McClanahan
 *
 */

#include "CVcam.h"
#include "GuppyCam.h"
#include <stdlib.h>
#include "highgui.h"

/* Determines camera compatability.
 * Also, this must be set to 0 to load videos via command line. */
#define USE_FIREWIRE_CAMERA 0




class Robot {
public:
    // default constructor, use a camera
    Robot();

    // constructor for loading a camera, or a video file
    Robot(const char* filename);

    // destructor
    virtual ~Robot();

    /* Cleans up any resources that were allocated
     * Init will have this called on atexit (stdlib.h) so the
     * user does not need to call this */
    static void destroy();

    /* the vision source */
#if USE_FIREWIRE_CAMERA

    GuppyCam camera;
#else

    CVcam camera;
#endif

    // initializes various things before main loop (mainly CV images)
    int init();

    // runs the robot (loops processFunc)
    void Go();

    // MAIN LOOP
    void processFunc();

    // initializes opengl and glut
    void initGlut();

    // refreshes glut window with raw image data
    void updateGlutDisplay();

    // starts the robot
    void startRobotThread(void* obj);

    /* the robot thread
     * this is static so "atexit()" works */
    static pthread_t robotThread;

    // connects to the camera (USB or 1394)
    void connectToCamera();


	
	// structure for saving video
	CvVideoWriter* cvVideoWriter;
	void createVideoWriter();



};

#endif /*ROBOT_H_*/
