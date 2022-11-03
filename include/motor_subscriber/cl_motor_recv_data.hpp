#ifndef MOTOR_RECV_DATA
#define MOTOR_RECV_DATA
class cl_motor_recv_data{
    private : 
        int m_old_left_move;
        int m_left_move;
        int m_old_right_move;
        int m_right_move;
    public :
        cl_motor_recv_data();

        void fn_set_old_left_move(int old_left_move);
        void fn_set_left_move(int left_move);
        void fn_set_old_right_move(int old_right_move);
        void fn_set_right_move(int right_move);
        
        int fn_get_old_left_move();
        int fn_get_left_move();     
        int fn_get_old_right_move();
        int fn_get_right_move();
};

#endif