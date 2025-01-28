
// ʹ�ñ�׼��MOSFET����ģ�ͣ������Ž���Ϊ������������������֡�
// �����Ϊһ�������ܿ�Դ�������Ϊ������ĵ�ѹԴ��
// �ο����������ӻ���ϵͳ����ѧ��������ơ���5�£���ҵ���������Զ���ʵ�֡�

#include <cctl/numerical_solver/solver_base.hpp>

#ifndef _FILE_HALF_BRIDGE_SWITCH_HPP_
#define _FILE_HALF_BRIDGE_SWITCH_HPP_


template <typename template_type> class mdl_idel_half_bridge
{
  public:
    typedef typename template_type _T;
    typedef typename st_null<_T> _st;

  public:
    // parameters
    _T R_on;

    // input variables
    // upper side switch
    uint_fast8_t *sw;

    _T *Ubus;
    _T *Ibridge;

    // output variables
    _T Ubridge; //  Uout = Uin - Iout*R_on
    _T Ibus;

  public:
    void operator()()
    {
        if (*sw)
        {
            this->Ibus = (*Ibridge);
            this->Ubridge = (*Ubus) - this->Ibus * R_on;
        }
        else
        {
            this->Ibus = 0;
            this->Ubridge = -(*Ibridge) * R_on;
        }
    }

    void bind(_T *Ubus, _T *Ibridge, uint_fast8_t *sw)
    {
        this->Ubus = Ubus;
        this->Ibridge = Ibridge;
        this->sw = sw;
    }
};

#endif // _FILE_HALF_BRIDGE_SWITCH_HPP_

