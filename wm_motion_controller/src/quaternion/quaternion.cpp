#include "quaternion/quaternion.hpp"
Quaternion::Quaternion() {
	x = 0;
	y = 0;
	z = 0;
	w = 1.0;
	roll = 0;
	pitch = 0;
	yaw = 0;
	qr_distance =0.35;
	double_radian=0;
	euler_x=0;
	euler_y=0;
	euler_z=0;
	euler_w=0;
}
Quaternion::~Quaternion() {}
void Quaternion::QuaternionToEulerAngles()
{
	double sinr_cosp = 2 * (w * x +y * z);
	double cosr_cosp = 1 - 2 * (x * x + y * y);
	roll = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (w * y - x * z));	
	double cosp = std::sqrt(1 - 2 * (w * y - x * z));
	pitch = 2 * std::atan2(sinp, cosp) - M_PI / 2;	

	if(pitch==1.5708){
		pitch=1.5918;
	}
	else if(pitch==-1.5708){
		pitch=-1.5918;
	}
	double siny_cosp = 2 * (w * z + x * y);
	double cosy_cosp = 1 - 2 * (y * y + z * z);
	yaw = std::atan2(siny_cosp, cosy_cosp);
}

double Quaternion::getterRoll()
{
	return roll;
}

double Quaternion::getterPitch()
{
	return pitch;
}

double Quaternion::getterYaw()
{
	return yaw;
}

double  Quaternion::degreeToRadian(double degree){
	double_radian= degree*M_PI/180;
	return double_radian;
}

double  Quaternion::getHeight(){
	height=sin(double_radian)*qr_distance;
	return height;
}
double  Quaternion::getBaseLine(){
	double temp_height=height;
	double temp_qr_distance=qr_distance;
	temp_height=pow(temp_height,2);
	temp_qr_distance=pow(temp_qr_distance,2);
	base_line=temp_height+temp_qr_distance ;
	base_line=sqrt(base_line);
	return base_line;
}

void Quaternion::setterX(double setX){
	x=setX;
}
void Quaternion::setterY(double setY){
	y=setY;
}

void Quaternion::setterZ(double setZ){
	z=setZ;
}
void Quaternion::setterW(double setW){
	w=setW;
}
float Quaternion::getterX(){
	return (float)x;
}
float Quaternion::getterY(){
	return (float)y;
}
float Quaternion::getterZ(){
	return (float)z;
}
float Quaternion::getterW(){
	return (float)w;
}

void Quaternion::EulerToQuaternion(double yaw,double pitch, double roll){
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);
	euler_x= sr * cp * cy - cr * sp * sy;

	euler_y= cr * sp * cy + sr * cp * sy;

	euler_z= cr * cp * sy - sr * sp * cy;

	euler_w= cr * cp * cy + sr * sp * sy;
}

double Quaternion::getterEulerW()
{
	return euler_w;
}
double Quaternion::getterEulerZ()
{
	return euler_z;
}
double Quaternion::getterEulerX()
{
	return euler_x;
}
double Quaternion::getterEulerY()
{
	return euler_y;
}