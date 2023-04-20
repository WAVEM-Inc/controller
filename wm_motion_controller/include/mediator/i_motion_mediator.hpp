#ifndef I_MOTION_MEDIATOR
#define I_MOTION_MEDIATOR
class IMotionMediator{
    public :
        virtual void fn_send_value_to_wm_motion_controller(int value)=0;
};
#endif