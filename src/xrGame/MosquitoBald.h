#pragma once

#include "customzone.h"

class CMosquitoBald : public CCustomZone
{
private:
	typedef	CCustomZone	inherited;
public:
					CMosquitoBald				();
	virtual			~CMosquitoBald				();

	virtual void	Load						(LPCSTR section);

	virtual void	Affect						(SZoneObjectInfo* O);

protected:
	virtual bool	BlowoutState				();
	virtual	void	UpdateSecondaryHit			();
	//��� ���� ����� blowout ��������� ���� ���
	//����� ���� ��� ���� ������������ � ������ ���������
	bool			m_bLastBlowoutUpdate;
};
