#pragma once
#include "PHShell.h"

class CPhysicsShellAnimatorBoneData//�������� ���������� �� ������� ������� ��������
{
	friend class CPhysicsShellAnimator;
	dJointID					m_anim_fixed_dJointID;
	CPHElement*					m_element;
};
