/* ----------------README-----------------------------------------------------
This camera was originally developed for the final project along 
with Pasindu Gunasekara(1412115). 

The code for the camera used for this assignment might look similar because 
we developed it together.

We both informed Dr. Gwosdz and recieved his approval in using this code
-----------------------------------------------------------------------------*/

#ifndef CAMERA_H
#define CAMERA_H

// classes uses 3D math class
#include "math3D.h"

// camera direction for which direction you are moving
enum CameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARD, BACK
};

// camera direction for which way you are spinning
enum CameraSpinDirection {
	SUP, SDOWN, SLEFT, SRIGHT
};

// class for the camera
class Camera {
	public:
		// constructor
		Camera();
		Camera(int tSize);
		// destructor
		~Camera();

		// update the camera after any transformation
		void Update();

		// translate the camera in a set direction
		// add float for amount
		void Move(CameraDirection dir);
		// rotate the camera in a set direction by a certain amount of degrees
		void Spin(CameraSpinDirection dir,float degrees);

		// temporarily changes angle around y
		void ChangeHeading(float degrees);
		// temporarily changes angle around x
		void ChangePitch(float degrees);

		bool checkHitBox(vec3D position,vec3D delta,Mesh3D mesh);

		// amount that you scale
		float camera_scale;
		// angle around x and y axis
		float camera_heading,camera_pitch;
		// boolean whether you just rotated the camera or not
		bool rotate_camera;

		// vectors holding on to your current camera position, change in camera position, point you are looking at, camera direction and up vector
		vec3D camera_position;
		vec3D camera_position_delta;
		vec3D camera_look_at;
		vec3D camera_direction;
		vec3D camera_up;
		vec3D light_position;
		vec3D spot_direction;
};


#endif