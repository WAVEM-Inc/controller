#ifndef WM_MOTION_CONTROLLER__QUATERNION_HPP_
#define WM_MOTION_CONTROLLER__QUATERNION_HPP_

#include<iostream>
#include<cmath>
#include<math.h>
#define _USE_MATH_DEFINES
class Quaternion
{
	private :
		double x, y, z, w;
		double roll, pitch, yaw;
		double qr_distance;
		double height;
		double base_line;
		double double_radian;
		
		double euler_x;
		double euler_y;
		double euler_z;
		double euler_w;

	public :
		Quaternion();
		~Quaternion();
		double degreeToRadian(double degree);
		double getHeight();
		double getBaseLine();
		
		void QuaternionToEulerAngles();
		double getterRoll();
		double getterPitch();
		double getterYaw();
		void setterX(double setX);
		void setterY(double setY);
		void setterZ(double setZ);
		void setterW(double setW);
	 	float getterX();
		float getterY();
		float getterZ();
		float getterW();
		void EulerToQuaternion(double yaw,double pitch,double roll);		
		double getterEulerX();
		double getterEulerY();
		double getterEulerZ();
		double getterEulerW();

};

#endif