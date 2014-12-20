// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EGRAPHIC_CMD_BUFFER_H__
#define _EGRAPHIC_CMD_BUFFER_H__

#include <vector>

namespace end2 {

//! Grapphic Command Buffer. The device state can be changed by this buffer
class EGraphicCmdBuffer {
public:

    //////////////////////////////////////////////////////////////////////

    enum E_CMD_TYPE {

        E_LIGHT_PROC_ENABLE = 0,

        E_LIGHT_ACTIVATE,
        E_LIGHT_ACTIVATE_AS_DIRECTIONAL,
        E_LIGHT_ACTIVATE_AS_POINT,
        E_LIGHT_ACTIVATE_AS_SPOT,

        E_SAMPLER_FILTER_KEEPCURRENT,
        E_SAMPLER_FILTER_NONE,
        E_SAMPLER_FILTER_POINT,
        E_SAMPLER_FILTER_LINEAR,
        E_SAMPLER_FILTER_ANISOTROPIC,

        E_CMD_NUM
    };

    //////////////////////////////////////////////////////////////////////

    class EGraphicCmd {
    public:

        E_CMD_TYPE getType() const {
            return cmd_.type_;
        }

    private:
        friend class EGraphicCmdBuffer;

        // cmd type or extra value
        union CMD_TYPE_EXTRA {
            E_CMD_TYPE type_;
            int extra_int_;

        } cmd_;

        // cmd params
        union CMD_PARAM {
            int param_int_;
            bool param_bool_;
            float param_float_;

        } param_[3];

        // default constructor
        EGraphicCmd(){
        }

        // cmd such like proc enable / diable
        EGraphicCmd(E_CMD_TYPE _cmd_type, bool _param_bool) {
            cmd_.type_ = _cmd_type;
            param_[0].param_bool_ = _param_bool;
        }

        // cmd such like index(stage) enable / disable
        EGraphicCmd(E_CMD_TYPE _cmd_type, int _param_int, bool _param_bool) {
            cmd_.type_ = _cmd_type;
            param_[0].param_int_ = _param_int;
            param_[1].param_bool_ = _param_bool;
        }

        void getParamAsInt_(int& _out, int _param_idx = 0) const {
            _out = param_[_param_idx].param_int_;
        }

        void getParamAsBool_(bool& _out, int _param_idx = 0) const {
            _out = param_[_param_idx].param_bool_;
        }

        void getParamAsFloat_(float& _out, int _param_idx = 0) const {
            _out = param_[_param_idx].param_float_;
        }

        void getParamAsIndexAndEnabled_(int& _idx, bool& _enalbe) const {
            _idx = param_[0].param_int_;
            _enalbe = param_[1].param_bool_;
        }

        void getParamAsVector3_(float* _out) const {
            _out[0] = param_[0].param_float_;
            _out[1] = param_[1].param_float_;
            _out[2] = param_[2].param_float_;
        }

        void getParamAsColor4_(int* _out) const {
            _out[0] = param_[0].param_int_;
            _out[1] = param_[1].param_int_;
            _out[2] = param_[2].param_int_;
            _out[3] = cmd_.extra_int_;
        }

    };

    //////////////////////////////////////////////////////////////////////

    //! constructor
    EGraphicCmdBuffer() {
    }

    //! destructor
    virtual ~EGraphicCmdBuffer() {
    }

    //////////////////////////////////////////////////////////////////////

    //! the type definition for the cmd list
    typedef std::vector<EGraphicCmd> EGraphicCmdList;

    //! gets the cmd list
    const EGraphicCmdList& getCmdList() const {
        return cmds_;
    }

    //! clears the cmd list
    void clearCmdList() {
        cmds_.clear();
    }

    //////////////////////////////////////////////////////////////////////

    void addCmdLightProcEnable(bool _enable) {
        cmds_.push_back(EGraphicCmd(E_LIGHT_PROC_ENABLE, _enable));
    }

    static void seekCmdLightProcEnable(
            EGraphicCmdList::const_iterator& _itr,
            bool& _enabled) {
        _itr->getParamAsBool_(_enabled);
        ++_itr;
    }

    void addCmdLightActivate(int _light_index, bool _activate) {
        cmds_.push_back(EGraphicCmd(E_LIGHT_ACTIVATE, _light_index, _activate));
    }

    static void seekCmdLightActivate(
            EGraphicCmdList::const_iterator& _itr,
            int& _light_index,
            bool& _activated) {
        _itr->getParamAsIndexAndEnabled_(_light_index, _activated);
        ++_itr;
    }

    void addCmdLightActivateAsDirectional(
            int _light_index,
            const float* _dir,
            const int* _ambientRGBA,
            const int* _diffuseRGBA) {
        addCmdLightActivateAs_(
                E_LIGHT_ACTIVATE_AS_DIRECTIONAL,
                _light_index,
                0,
                _dir,
                _ambientRGBA,
                _diffuseRGBA);
    }

    static void seekCmdLightActivateAsDirectional(
            EGraphicCmdList::const_iterator& itr,
            int& _light_index,
            float* _dir,
            int* _ambientRGBA,
            int* _diffuseRGBA) {
        seekCmdLightSetTo_(
                itr,
                _light_index,
                0,
                _dir,
                _ambientRGBA,
                _diffuseRGBA);
    }

    //////////////////////////////////////////////////////////////////////

private:

    void addCmdLightActivateAs_(
            E_CMD_TYPE _cmd_type,
            int _light_index,
            const float* _pos,
            const float* _dir,
            const int* _ambient,
            const int* _diffuse) {
        EGraphicCmd cmd;
        cmd.cmd_.type_ = _cmd_type;
        cmd.param_[0].param_int_ = _light_index;
        cmds_.push_back(cmd);

        if(_pos) {
            cmd.param_[0].param_float_ = _pos[0];
            cmd.param_[1].param_float_ = _pos[1];
            cmd.param_[2].param_float_ = _pos[2];
            cmds_.push_back(cmd);
        }

        if(_dir) {
            cmd.param_[0].param_float_ = _dir[0];
            cmd.param_[1].param_float_ = _dir[1];
            cmd.param_[2].param_float_ = _dir[2];
            cmds_.push_back(cmd);
        }

        cmd.param_[0].param_int_ = _ambient[0];
        cmd.param_[1].param_int_ = _ambient[1];
        cmd.param_[2].param_int_ = _ambient[2];
        cmd.cmd_.extra_int_ = _ambient[3];
        cmds_.push_back(cmd);

        cmd.param_[0].param_int_ = _diffuse[0];
        cmd.param_[1].param_int_ = _diffuse[1];
        cmd.param_[2].param_int_ = _diffuse[2];
        cmd.cmd_.extra_int_ = _diffuse[3];
        cmds_.push_back(cmd);
    }

    static void seekCmdLightSetTo_(
            EGraphicCmdList::const_iterator& _itr,
            int& _light_index,
            float* _pos,
            float* _dir,
            int* _ambientRGBA,
            int* _diffuseRGBA) {
        _itr->getParamAsInt_(_light_index, 0);
        ++_itr;

        if(_pos) {
            _itr->getParamAsVector3_(_pos);
            ++_itr;
        }

        if(_dir) {
            _itr->getParamAsVector3_(_dir);
            ++_itr;
        }

        _itr->getParamAsColor4_(_ambientRGBA);
        ++_itr;

        _itr->getParamAsColor4_(_diffuseRGBA);
        ++_itr;
    }

    std::vector<EGraphicCmd> cmds_;
};

}

#endif //_EGRAPHIC_CMD_BUFFER_H__
// vim: ts=4:sw=4
