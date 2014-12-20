// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ESYSTEM_H__
#define _ESYSTEM_H__

#include <vector>
#include <string>

#include "EAssert.h"

namespace end2 {

//! The System Class
/**
 This class is singleton.
 ESystem instance only can be created by ESystem::newSystem()
 and can be destroyed by ESystem::deleteSystem().

 ESystem manages modules.
 The modules can be created by ESystem.
 And if you want to use the module,
 you can get that from ESystem::getModule<Module>().
 **/
class ESystem {
private:

    class ESystemObject {
    protected:

        friend class ESystem;

        //! constructor
        ESystemObject() {
        }

        //! destructor
        virtual ~ESystemObject() {
        }
    };

    template<typename T_Module>
    class EModule: public ESystemObject {
    private:

        // the id for getting the module
        friend class ESystem;

        EModule() {
            *getModulePtrPtr_() = 0;
        }

        virtual ~EModule() {
            delete *getModulePtrPtr_();
            *getModulePtrPtr_() = 0;
        }

        static T_Module** getModulePtrPtr_(){
            static T_Module* module_ptr;
            return &module_ptr;
        }
    };

    // System Instance
    static ESystem* system_singleton_ptr_;

    // System Objects
    std::vector<ESystemObject*> system_object_instances_;

public:

    //! construction
    static void newSystem() {
        EASSERT(system_singleton_ptr_ == 0);
        system_singleton_ptr_ = new ESystem;
    }

    //! destruction
    static void deleteSystem() {
        delete system_singleton_ptr_;
        system_singleton_ptr_ = 0;
    }

    //! gets the system instance
    static ESystem& getSystem() {
        EASSERT(system_singleton_ptr_ != 0);
        return *system_singleton_ptr_;
    }

    //! creates the module
    template<typename T_Module>
    T_Module* createModule() {
        return createModule<T_Module, T_Module>();
    }

    //! creates sub module from super class module
    template<typename T_ModuleImpl, typename T_ModuleParent>
    T_ModuleImpl* createModule() {
        // Create module wrapper
        ESystemObject* system_object = new EModule<T_ModuleParent>();
        system_object_instances_.push_back(system_object);

        T_ModuleImpl* module = new T_ModuleImpl;
        *EModule<T_ModuleParent>::getModulePtrPtr_() = module;

        return module;
    }

    //! gets the module
    template<typename T_Module>
    T_Module* getModule() {
        return *EModule<T_Module>::getModulePtrPtr_();
    }

    //! gets numbers of modules
    int getModuleCount() {
        return (int) system_object_instances_.size();
    }

    //! clears modules
    void clearModules() {
        int cnt = (int) system_object_instances_.size();
        if(cnt > 0) {
            // First Creation - Last Deletion
            for(int i = cnt - 1; i >= 0; --i) {
                ESystemObject* system_object = system_object_instances_[i];
                delete system_object;
            }
            system_object_instances_.clear();
        }
    }

private:

    // constructor
    ESystem() {
    }

    // destructor
    ~ESystem() {
        EASSERT(system_object_instances_.empty());
    }
};

}

#endif	//_ESYSTEM_H__
// vim: ts=4:sw=4
