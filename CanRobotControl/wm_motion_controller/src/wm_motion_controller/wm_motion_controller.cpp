#include "wm_motion_controller/wm_motion_controller.hpp"
#include "converter/ugv_converter.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "entity/df_ugv.hpp"
#include "tf2/LinearMath/Quaternion.h"
/**
 * @brief Construct a new Wm Motion Controller:: Wm Motion Controller object
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
WmMotionController::WmMotionController(std::shared_ptr<IMotionMediator> motion_mediator,std::shared_ptr<CanMGR> can_mgr)
:Node("WmMotionControllerNode"),
IMotionColleague(motion_mediator), 
m_can_manager(can_mgr),
pose_yaw_(0),
prev_pose_yaw_(0),
odom_dist_(0),
lo_x_(0),
lo_y_(0),
origin_corr_(0),
origin_x_(0),
origin_y_(0){
	std::cout<<"===="<<'\n';
	this->declare_parameter<float>("correction", correction_);
  
    this->get_parameter("correction", correction_);
	std::cout <<"test : "<<correction_<<'\n';
	constants_ = std::make_shared<WmMotionControllerConstants>();
	std::cout<<constants_->log_constructor<<std::endl;
	control_mode_ = false;
	last_time_ = current_time_= imu_time_ =odom_time_=this->now();

	prev_ugv_ = std::make_shared<ENTITY::UGV>();
	(*prev_ugv_).set_cur_rpm(constants_->rpm_center_);
	(*prev_ugv_).set_cur_time(std::chrono::system_clock::now());
	cur_ugv_ = std::make_shared<ENTITY::UGV>();

	//
	m_cb_group_cmd_vel = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	m_cb_group_can_chw = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	cb_group_imu_ = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	cb_group_odom_ = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	cb_group_rtt_odom_ = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	cb_group_mode_ = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	cbg_emergency_ = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
	rclcpp::SubscriptionOptions sub_cmdvel_options;
	rclcpp::SubscriptionOptions sub_can_chw_options;
	rclcpp::SubscriptionOptions sub_imu_options;
	rclcpp::SubscriptionOptions sub_controller_mode_options;
	rclcpp::PublisherOptions pub_odom_options;
	rclcpp::PublisherOptions pub_rtt_odom_options;
	rclcpp::SubscriptionOptions sub_emergency_options;

	sub_cmdvel_options.callback_group = m_cb_group_cmd_vel;
	sub_can_chw_options.callback_group = m_cb_group_can_chw;
	sub_imu_options.callback_group = cb_group_imu_;
	sub_controller_mode_options.callback_group = cb_group_mode_;
	pub_odom_options.callback_group = cb_group_odom_;
	pub_rtt_odom_options.callback_group = cb_group_rtt_odom_;
	sub_emergency_options.callback_group = cbg_emergency_;

	m_sub_cmdvel = this->create_subscription<geometry_msgs::msg::Twist>(constants_->m_tp_cmdvel,constants_->m_tp_queue_size,std::bind(&WmMotionController::fn_cmdvel_callback,this,_1),sub_cmdvel_options);
	m_sub_can_chw = this->create_subscription<can_msgs::msg::ControlHardware>(constants_->m_tp_can_chw,constants_->m_tp_queue_size,std::bind(&WmMotionController::fn_can_chw_callback,this,_1),sub_can_chw_options);
	sub_imu_ = this->create_subscription<sensor_msgs::msg::Imu>(constants_->tp_imu_,constants_->m_tp_queue_size,std::bind(&WmMotionController::imu_callback,this,_1),sub_imu_options);
	sub_mode_ = this->create_subscription<can_msgs::msg::Mode>(constants_->tp_slam_mode_,1,std::bind(&WmMotionController::slam_mode_callback,this,_1),sub_controller_mode_options);
	
	sub_emergency_ = this->create_subscription<can_msgs::msg::Emergency>("drive/can/emergency",1,std::bind(&WmMotionController::fn_emergency_callback,this,_1),sub_emergency_options);
	//
	pub_odom_ = this->create_publisher<nav_msgs::msg::Odometry>(constants_->tp_odom_, 1,pub_odom_options);
	pub_rtt_ = this->create_publisher<geometry_msgs::msg::PoseStamped>(constants_->tp_rtt_odom_,10,pub_rtt_odom_options);

	timer_ = this->create_wall_timer(100ms,std::bind(&WmMotionController::pub_odometry,this));
	tf_timer_ = this->create_wall_timer(100ms,std::bind(&WmMotionController::update_transform,this));
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
	//std::cout<<constants_->log_chw_callback<<' '<<can_chw->horn<<' '<<can_chw->head_light<<' '<<can_chw->right_light<<' '<<can_chw->left_light<<'\n'; 
	m_can_manager->fn_send_control_hardware(can_chw->horn,can_chw->head_light,can_chw->right_light,can_chw->left_light);
}

/**
 * @brief cmd_vel receive function for robot control
 * @param twist_aux Received cmd_vel data
 * @author changunAn(changun516@wavem.net)
 * @date 23.04.06
 */
void WmMotionController::fn_cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr cmd_vel){
    //RCLCPP_INFO(this->get_logger(),constants_->log_cmd_callback+"linear = %.02f,angular = %.02f\n", cmd_vel->linear.x, cmd_vel->angular.z);
	float vel_linear = 0,vel_angular = 0;
	vel_linear = cmd_vel->linear.x;
	vel_angular = cmd_angel_convert(cmd_vel->angular.z,vel_linear);
	float cur_rpm = cur_ugv_->get_cur_rpm();
	//==
	
	if(vel_angular==0 || control_mode_==false){
		(vel_linear<0)?m_can_manager->fn_send_control_hardware(true,false,false,false):m_can_manager->fn_send_control_hardware(false,false,false,false);
		cmd_vel_break(vel_linear, cur_rpm);
		cmd_vel_run(vel_linear,vel_angular);
	}else{
		cmd_vel_break(vel_linear, cur_rpm);
		if(vel_linear>0){
			m_can_manager->fn_send_control_hardware(false,false,false,false);
			if(vel_linear>constants_->slam_mode_fast_speed_){
				cmd_vel_run(vel_linear,vel_angular);
			}
			else{
				cmd_vel_run(vel_linear+vel_angular/constants_->slam_mode_ang_cor_,vel_angular);
			}
		}
		else if(vel_linear<0){
			m_can_manager->fn_send_control_hardware(true,false,false,false);
			if(vel_linear<-(constants_->slam_mode_fast_speed_)){
				cmd_vel_run(vel_linear,vel_angular);
			}
			else{
				cmd_vel_run(vel_linear-vel_angular/constants_->slam_mode_ang_cor_,vel_angular);
			}
		}
		else{
			m_can_manager->fn_send_control_hardware(false,false,false,false);
			cmd_vel_run(std::fabs(vel_angular/constants_->slam_mode_ang_cor_),vel_angular);
		}
	}
	//	
}
void WmMotionController::cmd_vel_run(float vel_linear, float vel_angular){
	m_can_manager->fn_send_control_steering(vel_angular);
	m_can_manager->fn_send_control_vel(vel_linear);
}

void WmMotionController::cmd_vel_break(float vel_linear, float cur_rpm){
	if(std::fabs(vel_linear)<0.001 && constants_->rpm_center_+constants_->rpm_break > cur_rpm&&
	constants_->rpm_center_-constants_->rpm_break< cur_rpm){
		prev_ugv_->get_cur_rpm();
		cur_ugv_->get_cur_rpm();
		m_can_manager->static_break(UGV::BREAK::LED);
	}
	else if(std::fabs(vel_linear)<0.001 && constants_->rpm_center_+constants_->rpm_break < cur_rpm&&
	constants_->rpm_center_-constants_->rpm_break > cur_rpm){
		prev_ugv_->get_cur_rpm();
		cur_ugv_->get_cur_rpm();
		m_can_manager->static_break(UGV::BREAK::STOP);
	}
	else{
		m_can_manager->static_break(UGV::BREAK::GO);
	}
}


  void WmMotionController::imu_callback(const sensor_msgs::msg::Imu::SharedPtr imu){
		//RCLCPP_INFO(this->get_logger(),constants_->log_imu_callback);
		current_time_ = this->now();
		qua_.setterX(imu->orientation.x);
		qua_.setterY(imu->orientation.y);
		qua_.setterZ(imu->orientation.z);
		qua_.setterW(imu->orientation.w);
		
		qua_.QuaternionToEulerAngles();

		qua_.EulerToQuaternion(qua_.getterYaw()+(180+correction_)*M_PI/180,-qua_.getterRoll(), qua_.getterPitch());
		//qua_.EulerToQuaternion(qua_.getterYaw()+(180+correction_)*M_PI/180,qua_.getterPitch(), qua_.getterRoll());
			
		qua_.setterX(qua_.getterEulerX());
		qua_.setterY(qua_.getterEulerY());
		qua_.setterW(qua_.getterEulerW());
		qua_.setterZ(qua_.getterEulerZ());

		//tf2::Quaternion q;
		//q.setRPY(0,0,qua_.getterYaw());
		qua_.QuaternionToEulerAngles();
		pose_yaw_ = qua_.getterYaw();
		auto sub_time = current_time_-imu_time_;
		double time_seconds = sub_time.seconds();
		vel_th_ = (pose_yaw_-prev_pose_yaw_)/(time_seconds);
		if(std::fabs(vel_th_)<constants_->zero_approximation_){
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
	//RCLCPP_INFO(this->get_logger(),constants_->log_mediator_recv_rpm_check+"%.02f",rpm);
	cur_ugv_->set_cur_rpm(rpm);
	cur_ugv_->set_cur_time(cur_time);
    std::shared_ptr<CONVERTER::UGVConverter> converter = std::make_shared<CONVERTER::UGVConverter>();
	cur_ugv_->set_cur_distance((*converter).rpm_to_distance(*prev_ugv_,*cur_ugv_));
	//RCLCPP_INFO(this->get_logger(),constants_->log_mediator_recv_rpm_distance+"%.02f",cur_ugv_->get_cur_distnace());
	prev_ugv_->set_cur_rpm(cur_ugv_->get_cur_rpm());
	prev_ugv_->set_cur_time(cur_ugv_->get_cur_time());
}


/**
 * @brief 
 * 
 */
void WmMotionController::pub_odometry(){
	calculate_next_position();
	calculate_next_orientation();
	nav_msgs::msg::Odometry odom;
	odom.header.frame_id = constants_->odom_frame_id_;    // LJM 160110: map
	odom.child_frame_id = constants_->child_frame_id_;
	odom.header.stamp = current_time_;
	odom.pose.pose.position.x = lo_x_;
	odom.pose.pose.position.y = lo_y_;
	odom.pose.pose.position.z = constants_->clear_zero_;
	odom.pose.pose.orientation.w = odom_quat_.w;
	odom.pose.pose.orientation.z = odom_quat_.z;
	odom.twist.twist.linear.x = vel_x_;
	odom.twist.twist.linear.y = constants_->clear_zero_;
	odom.twist.twist.linear.z = constants_->clear_zero_;
	odom.twist.twist.angular.x = constants_->clear_zero_;
	odom.twist.twist.angular.y = constants_->clear_zero_;
	odom.twist.twist.angular.z = vel_th_;
	last_time_ = current_time_;
	pub_odom_->publish(odom);
	geometry_msgs::msg::PoseStamped rtt_value;
	rtt_value.pose.position.x = odom_dist_;

	rtt_value.pose.orientation.x = qua_.getterYaw();//+90*M_PI/180;
//	if(qua_.getterYaw()/*-90*M_PI/180*/>M_PI){ 
//		rtt_value.pose.orientation.x -= 2*M_PI;
//	}
//	else if(qua_.getterYaw()/*-90*M_PI/180*/<-M_PI){
//		rtt_value.pose.orientation.x += 2*M_PI;
//	} //+ (-180*M_PI/180)/*+origin_corr*/;
	if(rtt_value.pose.orientation.x/*-90*M_PI/180*/>M_PI){ 
		rtt_value.pose.orientation.x -= 2*M_PI;
	}
	else if(rtt_value.pose.orientation.x/*-90*M_PI/180*/<-M_PI){
		rtt_value.pose.orientation.x += 2*M_PI;
	} //+ (-180*M_PI/180)/*+origin_corr*/;
	//rtt_value.pose.orientation.y = (qua_.getterYaw() -90*M_PI/180 )*180/M_PI;
	rtt_value.pose.orientation.y = (rtt_value.pose.orientation.x)*180/M_PI;

	pub_rtt_->publish(rtt_value);
}
/**
 * @brief 
 * 
 */
void WmMotionController::update_transform(){
	geometry_msgs::msg::TransformStamped odom_trans;
	odom_trans.header.frame_id = constants_->odom_frame_id_;
	odom_trans.child_frame_id = constants_->child_frame_id_;
	std::unique_ptr<tf2_ros::TransformBroadcaster> broadcaster = std::make_unique<tf2_ros::TransformBroadcaster>(this);
	odom_trans.header.stamp = current_time_;	
	odom_trans.transform.translation.x = lo_x_;
	odom_trans.transform.translation.y = lo_y_;
	//odom_trans.transform.translation.z = constants_->clear_zero_;
	//odom_trans.transform.translation.x = q.getX();
	//odom_trans.transform.translation.y = q.getY();
	//odom_trans.transform.rotation = q.getW();
	//odom_trans.transform.translation.z= q.getAngle();
	
	odom_trans.transform.rotation.x=qua_.getterX();
	odom_trans.transform.rotation.y=qua_.getterY();
	odom_trans.transform.rotation.w=qua_.getterW();
	odom_trans.transform.rotation.z=qua_.getterZ();
	
	broadcaster->sendTransform(odom_trans); 
	
	odom_trans.header.frame_id = constants_->odom_frame_id_;
	odom_trans.child_frame_id = "base_map_link";
	odom_trans.header.stamp = current_time_;	
	odom_trans.transform.translation.x = lo_x_;
	odom_trans.transform.translation.y = lo_y_;
	qua_.EulerToQuaternion(qua_.getterYaw(),0,0);
			
		qua_.setterX(qua_.getterEulerX());
		qua_.setterY(qua_.getterEulerY());
		qua_.setterW(qua_.getterEulerW());
		qua_.setterZ(qua_.getterEulerZ());

		qua_.QuaternionToEulerAngles();

	odom_trans.transform.rotation.x=qua_.getterX();
	odom_trans.transform.rotation.y=qua_.getterY();
	odom_trans.transform.rotation.w=qua_.getterW();
	odom_trans.transform.rotation.z=qua_.getterZ();
	broadcaster->sendTransform(odom_trans); 
}
/**
 * @brief 
 * 
 */
void WmMotionController::calculate_next_position(){
	current_time_ = this->now();	
	dxy_ = static_cast<double>(cur_ugv_->get_cur_distnace());
	test += dxy_;
	odom_dist_+= dxy_;
	auto sub_time = current_time_-odom_time_;
	double time_seconds = sub_time.seconds();
	vel_x_ = dxy_*10;
	//std::cout<<"calculate_next_position"<< lo_x_<<' '<<dxy_<<' '<<test<<'\n';
	if (dxy_ != 0) {
		lo_x_ += ( dxy_ * cosf( qua_.getterYaw()));	//minseok 200611 before x
		lo_y_ += ( dxy_ * sinf(  qua_.getterYaw() ));
		//lo_x_ += ( dxy_ * cosf( qua_.getterYaw()));	//minseok 200611 before x
		//lo_y_ += ( dxy_ * sinf(  qua_.getterYaw() ));
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
/**
 * @brief 
 * 
 */
void WmMotionController::calculate_next_orientation(){
	odom_quat_.x=qua_.getterX();
	odom_quat_.y=qua_.getterY();
	odom_quat_.w=qua_.getterW();
	odom_quat_.z=qua_.getterZ();
}

float WmMotionController::cmd_angel_convert(const float& ori_angel,const float& ori_linear){
	int MAX = 30;
	/*
	float result = 0.0;
	result = ori_data*30/1;
	return (result>=30)?30:result;
	*/
	float steer_angle, steer_val;
	steer_angle= (ori_angel)/(0.0001+ori_linear*2)*3;
	if(steer_angle > 0.7){
		steer_angle = 0.7;
	}
	else if(steer_angle < -0.7){
		steer_angle = -0.7;
	}
	steer_angle= steer_angle/0.7*30;
	std::cout << "!!!!!!!!!!!!!!bms "<< steer_angle<<'\n';
	return steer_angle;
	//return steer_angle;
	//return 0;
}

void WmMotionController::slam_mode_callback(const can_msgs::msg::Mode::SharedPtr mode){
	control_mode_ = mode->slam_mode;
}
void WmMotionController::fn_emergency_callback(const can_msgs::msg::Emergency::SharedPtr data){
	if(data->stop){
			m_can_manager->static_break(UGV::BREAK::STOP);
	}
	else{
		m_can_manager->static_break(UGV::BREAK::GO);
	}
}