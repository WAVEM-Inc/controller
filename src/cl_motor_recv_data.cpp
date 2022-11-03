#include "motor_subscriber/cl_motor_recv_data.hpp"

cl_motor_recv_data::cl_motor_recv_data(){
    m_old_left_move=0;
    m_left_move=0;
    m_old_right_move=0;
    m_right_move=0;
}

void cl_motor_recv_data::fn_set_old_left_move(int old_left_move){
    this->m_old_left_move=old_left_move;
}
void cl_motor_recv_data::fn_set_left_move(int left_move){
    this->m_left_move = left_move;
}
void cl_motor_recv_data::fn_set_old_right_move(int old_right_move){
    this->m_old_right_move = old_right_move;
}

void cl_motor_recv_data::fn_set_right_move(int right_move){
    this->m_right_move = right_move;
}

int cl_motor_recv_data::fn_get_old_left_move(){
    return m_old_left_move;
}
int cl_motor_recv_data::fn_get_left_move(){
    return m_left_move;
}     
int cl_motor_recv_data::fn_get_old_right_move(){
    return m_old_right_move;
}
int cl_motor_recv_data::fn_get_right_move(){
    return m_right_move;
}