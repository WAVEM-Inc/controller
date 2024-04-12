#ifndef MOTION_CONTROLLER__MANAGER__HPP__
#define MOTION_CONTROLLER__MANAGER__HPP__
//can header

// motion_controller header
#include "wm_motion_controller/wm_motion_controller.hpp"
//
#include "common/common.hpp"
#include "common/test.h"
#include "manager/motion.hpp"
#include "manager/i_can.hpp"
//defualt header
#include <memory>
#include <map>
class WmMotionController;
class Manager{
    public :
        Manager();
        virtual ~Manager();
        void fn_run();
        void fn_map_up(std::string key, MANAGER::SETUP value);
        //
       

    private : 
        std::map<std::string,MANAGER::SETUP> map_setup_;

        std::shared_ptr<WmMotionController> wm_motion_controller_;
};

#endif