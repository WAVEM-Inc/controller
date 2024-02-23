#ifndef MOTION_CONTROLLER__MANAGER__HPP__
#define MOTION_CONTROLLER__MANAGER__HPP__
//can header
#include "can/can_manager.hpp"
// motion_controller header
#include "wm_motion_controller/wm_motion_controller.hpp"
//
#include "common/common.hpp"

//defualt header
#include <memory>
#include <map>
class WmMotionController;
class CanMGR;
class Manager{
    public :
        Manager();
        
        virtual ~Manager();
        void fn_run();
        void fn_map_up(std::string key, MANAGER::SETUP value);
        //
        void fn_motion_send_data(int test);

    private : 
        std::map<std::string,MANAGER::SETUP> map_setup_;
        std::shared_ptr<CanMGR> can_manager_;
        std::shared_ptr<WmMotionController> wm_motion_controller_;
};

#endif