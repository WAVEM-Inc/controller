#ifndef I_CAN_CONNECT
#define I_CAN_CONNECT
class ICanConnect{
    public : 
        virtual int fn_can_init()=0;
        virtual void fn_can_run()=0;  
};
#endif