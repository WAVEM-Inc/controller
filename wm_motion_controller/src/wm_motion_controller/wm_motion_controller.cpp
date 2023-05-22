#include "wm_motion_controller/wm_motion_controller.hpp"
#include "converter/ugv_converter.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"
/**
 * @brief Construct a new Wm Motion Controller:: Wm Motion Controller object
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
WmMotionController::WmMotionController(std::shared_ptr<IMotionMediator> motion_mediator,std::shared_ptr<CanMGR> can_mgr)
:Node("WmMotionControllerNode"),
IMotionColleague(motion_mediator),
m_can_manager(can_mgr),
m_steer_max_ang(STEER_MAX_ANGLE),
m_tp_cmdvel(TP_CMDVEL),
m_tp_queue_size(TP_QUEUE_SIZE),
m_tp_can_chw(TP_CONTROL_HARD_WARE),
tp_imu_(TP_IMU),
pose_yaw_(0),
prev_pose_yaw_(0),
odom_dist_(0),
lo_x_(0),
lo_y_(0),
origin_corr_(0),
origin_x_(0),
origin_y_(0){
	std::cout<<"WmMotionContoller Start"<<std::endl;
	
	//m_can_manager = new CanMGR(motion_mediator);
	last_time_ = current_time_= imu_time_ =this->now();
	//
	prev_ugv_ = std::make_shared<ENTITY::UGV>();
	(*prev_ugv_).set_cur_rpm(0);
	(*prev_ugv_).set_cur_time(std::chrono::system_clock::now());
	cur_ugv_ = std::make_shared<ENTITY::UGV>();
	
	//
	m_cb_group_cmd_vel = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	m_cb_group_can_chw = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	cb_group_imu_ = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

	rclcpp::SubscriptionOptions sub_cmdvel_options;
	rclcpp::SubscriptionOptions sub_can_chw_options;
	rclcpp::SubscriptionOptions sub_imu_options;

	sub_cmdvel_options.callback_group = m_cb_group_cmd_vel;
	sub_can_chw_options.callback_group = m_cb_group_can_chw;
	sub_imu_options.callback_group = cb_group_imu_;

	m_sub_cmdvel = this->create_subscription<geometry_msgs::msg::Twist>(m_tp_cmdvel,m_tp_queue_size,std::bind(&WmMotionController::fn_cmdvel_callback,this,_1),sub_cmdvel_options);
	m_sub_can_chw = this->create_subscription<can_msgs::msg::ControlHardware>(m_tp_can_chw,m_tp_queue_size,std::bind(&WmMotionController::fn_can_chw_callback,this,_1),sub_can_chw_options);
	sub_imu_ = this->create_subscription<sensor_msgs::msg::Imu>(tp_imu_,m_tp_queue_size,std::bind(&WmMotionController::imu_callback,this,_1),sub_imu_options);
	//
	//pub_odom_ = this->create_publisher<nav_msgs::msg::Odometry>("/imu/data", 1);
	//
	std::thread thread_run(&CanMGR::fn_can_run,m_can_manager);
    thread_run.detach();
}
WmMotionController::~WmMotionController(){

}

/**
 * @brief Callback function for controlling horn, light, when can_msgs:msgControlHardWare message is received
 * @author changunAn(changun516@wavem.net)
 * @param can_chw 
 */
void WmMotionController::fn_can_chw_callback(const can_msgs::msg::ControlHardware::SharedPtr can_chw){
	std::cout<< "chw_callback : "<< can_chw->horn << " : " << can_chw->head_light <<" : "<<can_chw->right_light<<" : "<<can_chw->left_light<<std::endl; 
	m_can_manager->fn_send_control_hardware(can_chw->horn,can_chw->head_light,can_chw->right_light,can_chw->left_light);
}

/**
 * @brief cmd_vel receive function for robot control
 * @param twist_aux Received cmd_vel data
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
void WmMotionController::fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr cmd_vel){
	float vel_linear = 0,vel_angular = 0;
	vel_linear = cmd_vel->linear.x;
	vel_angular = cmd_vel->angular.z;
    RCLCPP_INFO(this->get_logger(),"!!!!!!@@@@@@linear = %.02f,angular = %.02f\n", vel_linear, vel_angular);
	m_can_manager->fn_send_control_steering(vel_angular);
	m_can_manager->fn_send_control_vel(vel_linear);
}


  void WmMotionController::imu_callback(const sensor_msgs::msg::Imu::SharedPtr imu){
		current_time_ = this->now();
		qua_.setterX(imu->orientation.x);
		qua_.setterY(imu->orientation.y);
		qua_.setterZ(imu->orientation.z);
		qua_.setterW(imu->orientation.w);
		qua_.QuaternionToEulerAngles();
		pose_yaw_ = qua_.getterYaw();
		auto sub_time = current_time_-imu_time_;
		double time_seconds = sub_time.seconds();
		vel_th_ = (pose_yaw_-prev_pose_yaw_)/(time_seconds);
		if(std::fabs(vel_th_)<0.008){
			vel_th_=0;
		}
		prev_pose_yaw_ = pose_yaw_;
		imu_time_ = current_time_;
  }


/**
 * @brief m/s to km/h
 * @param mps 
 * @author changunAn(changun516@wavem.net)
 * @return float 
 */
float WmMotionController::fn_mps2kmph(float mps){
	return mps * 3600 / 1000;  // mps를 kmph로 변환
}
/**
 * @brief km/h to m/s
 * @param kmph 
 * @author changunAn(changun516@wavem.net)
 * @return float 
 */
float WmMotionController::fn_kmph2mps(float kmph){
	return kmph * 1000 / 3600;  // kmph를 mps로 변환
}


/**
 * @brief Function for sending data to CanMGR via arbitrator
 * @author changunAn(changun516@wavem.net)
 * @param value 
 */
void WmMotionController::fn_send_value(const int& value){
    std::cout<< "override WmMotionController"<<std::endl;
    m_i_motion_mediator->fn_send_value(value,enable_shared_from_this<WmMotionController>::shared_from_this());
}
/**
 * @brief Function for receiving data from CanMGR through arbitrator
 * @author changunAn(changun516@wavem.net)
 * @param value 
 */
void WmMotionController::fn_recv_value(const int& value){
    std::cout<< "override WmMotionController "<<value<<std::endl;

}

void WmMotionController::fn_send_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time){
	
}
/**
 * @brief RPM data coming over CAN communication
 * 
 * @param rpm 
 * @param cur_time 
 */
void WmMotionController::fn_recv_rpm(const float& rpm,const std::chrono::system_clock::time_point& cur_time){
	std::cout<<"rpm_test!! : "<<rpm<<'\n';
	cur_ugv_->set_cur_rpm(rpm);
    std::shared_ptr<CONVERTER::UGVConverter> converter = std::make_shared<CONVERTER::UGVConverter>();
	cur_ugv_->set_cur_distance((*converter).rpm_to_distance(*prev_ugv_,*cur_ugv_));
	std::cout<<"[WM_MOTION_CONTROLLER__RECV_RPM__DISTANCE] : "<<cur_ugv_->get_cur_distnace()<<'\n';
	prev_ugv_->set_cur_rpm(cur_ugv_->get_cur_rpm());
	prev_ugv_->set_cur_time(cur_ugv_->get_cur_time());
}



void WmMotionController::pub_odometry(){
	calculate_next_position();
	calculate_next_orientation();
	nav_msgs::msg::Odometry::SharedPtr odom;
	odom->header.frame_id = "/odom";    // LJM 160110: map
	odom->child_frame_id = "base_footprint";
	//! 위치 값 채우기 
	odom->header.stamp = current_time_;
	
	odom->pose.pose.position.x = lo_x_;
	odom->pose.pose.position.y = lo_y_;
	odom->pose.pose.position.z = 0.0;
	odom->pose.pose.orientation = odom_quat_;

	//! 속도 값 채우기
	odom->twist.twist.linear.x = vel_x_;
	odom->twist.twist.linear.y = 0.0;
	odom->twist.twist.linear.z = 0.0;
	odom->twist.twist.angular.x = 0.0;
	odom->twist.twist.angular.y = 0.0;
	odom->twist.twist.angular.z = vel_th_;

	last_time_ = current_time_;
	pub_odom_->publish(*odom);
}
void WmMotionController::update_transform(){
	geometry_msgs::msg::TransformStamped::SharedPtr odom_trans;
	//odom_trans->header.frame_id = "/odom";    // LJM 160110: map
	//odom_trans->child_frame_id = "base_footprint";
	//auto cur_time = this->now();
	std::unique_ptr<tf2_ros::TransformBroadcaster> m_broadcaster;
	odom_trans->header.stamp = current_time_;	
	odom_trans->transform.translation.x = lo_x_;
	odom_trans->transform.translation.y = lo_y_;
	odom_trans->transform.translation.z = 0.0;
	//odom_trans.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(m_qua.getterRoll(),m_qua.getterPitch(),m_qua.getterYaw());
	odom_trans->transform.rotation.x=qua_.getterX();
	odom_trans->transform.rotation.y=qua_.getterY();
	odom_trans->transform.rotation.w=qua_.getterW();
	odom_trans->transform.rotation.z=qua_.getterZ();
	//m_broadcaster->sendTransform(*odom_trans);    
	

}
void WmMotionController::calculate_next_position(){
	current_time_ = this->now();
	// calculate odomety
	/*
	if ((right_enc == right_enc_old) && (left_enc == left_enc_old) )  {
		distance_left = 0.0;
		distance_right = 0.0;
	} 
	else {
		//20160812 KKY -begin
		//wheel angular_velocity
		//20161122 KKY
		std::cout<<"[left_enc] "<< left_enc << " "<< right_enc<<std::endl;
		angular_left =   (left_enc / 100) *1.5;
		angular_right =  (right_enc / 100) *1.5;

		//wheel linear_velocity
		//2021-01-21 JBK 0.135 -> 0.15 
		// @date 2022-10-18 ACU 0.15 -> 0.05 Wheel 100mm
		distance_left =  angular_left/6.5	;  //   * ticks_per_meter; // ( (left_enc - left_enc_old) * 2*M_PI *65.0 ) / ticks_per_meter;
		distance_right = angular_right/6.5;      //    * ticks_per_meter;  // ( (right_enc - right_enc_old) *  2*M_PI * 65.0 )   /  ticks_per_meter;
		//20160812 KKY -end
	}

	left_enc_old = left_enc;
	right_enc_old = right_enc;
	//printf("@@%f , %f\n",distance_left,distance_right);
	//20160812 KKY mpc linear velocity
	*/
	// dxy = (distance_left + distance_right) / 2.0; 확인 필요
	
	dxy_ = (cur_ugv_->get_cur_distnace())/2.0;

	odom_dist_+= dxy_;
	auto sub_time = current_time_-odom_time_;
	double time_seconds = sub_time.seconds();
	vel_x_ = dxy_/time_seconds;
	if (dxy_ != 0) {
		lo_x_ += ( dxy_ * cosf( qua_.getterYaw()));	//minseok 200611 before x
		lo_y_ += ( dxy_ * sinf(  qua_.getterYaw()));
		origin_x_ += ( dxy_ * cosf( qua_.getterYaw()+origin_corr_ ));	//minseok 200611 before x
		origin_y_ += ( dxy_ * sinf(  qua_.getterYaw()+origin_corr_));
	}
	if(imu_th_ != 0 && imu_th_ != prev_imu_th_){
//		th = gyro_theta + initial_th;
		lo_th_ = qua_.getterYaw();
	}
	prev_imu_th_ = imu_th_;
	odom_time_ = current_time_;
}
void WmMotionController::calculate_next_orientation(){
	odom_quat_.x=qua_.getterX();
	odom_quat_.y=qua_.getterY();
	odom_quat_.w=qua_.getterW();
	odom_quat_.z=qua_.getterZ();

}