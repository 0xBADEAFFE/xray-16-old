#pragma once

#include "NET_Shared.h"
#include "NET_Common.h"
#include "xrCommon/xr_deque.h"
#include "xrCommon/xr_vector.h"
#include "Common/Noncopyable.hpp"
#include "xrCore/xrstring.h"

struct ip_address;
class Lock;

class XRNETSERVER_API INetQueue : private Noncopyable
{
	Lock		*pcs;
	xr_deque<NET_Packet*>	ready;
	xr_vector<NET_Packet*>	unused;
public:
	INetQueue();
	~INetQueue();

	NET_Packet*			Create	();
	NET_Packet*			Create	(const NET_Packet& _other);
	NET_Packet*			Retreive();
	void				Release	();
	void				LockQ	();
	void				UnlockQ	();
};


//==============================================================================

// DPlay
extern "C" {
typedef struct	_DPN_APPLICATION_DESC DPN_APPLICATION_DESC;
struct IDirectPlay8Address;
struct IDirectPlay8Client;
}

class XRNETSERVER_API
IPureClient
  : private MultipacketReciever,
    private MultipacketSender,
	private Noncopyable
{
	enum ConnectionState
	{
		EnmConnectionFails=0,
		EnmConnectionWait=-1,
		EnmConnectionCompleted=1
	};
	friend void 				sync_thread(void*);
protected:
	struct HOST_NODE : Noncopyable //deprecated...
	{
		HOST_NODE();
		HOST_NODE(const HOST_NODE& rhs);
		HOST_NODE(HOST_NODE&& rhs) noexcept;
		~HOST_NODE() noexcept;

		DPN_APPLICATION_DESC*	pdpAppDesc;
		IDirectPlay8Address*	pHostAddress;
		shared_str				dpSessionName;
	};
	GameDescriptionData		m_game_description;
	CTimer*					device_timer;
protected:
	IDirectPlay8Client*		NET;
	IDirectPlay8Address*	net_Address_device;
	IDirectPlay8Address*	net_Address_server;

	Lock		*net_csEnumeration;
	xr_vector<HOST_NODE>	net_Hosts;

	NET_Compressor			net_Compressor;

	ConnectionState			net_Connected;
	BOOL					net_Syncronised;
	BOOL					net_Disconnected;

	INetQueue				net_Queue;
	IClientStatistic		net_Statistic;

	u32						net_Time_LastUpdate;
	s32						net_TimeDelta;
	s32						net_TimeDelta_Calculated;
	s32						net_TimeDelta_User;

	void					Sync_Thread		();
	void					Sync_Average	();

	void					SetClientID		(ClientID const & local_client) { net_ClientID = local_client; };


	IC virtual	void			SendTo_LL				(void* data, u32 size, u32 dwFlags= 0x0008 /*DPNSEND_GUARANTEED*/, u32 dwTimeout=0);

public:
	IPureClient				(CTimer* tm);
	virtual ~IPureClient	();
	HRESULT					net_Handler				(u32 dwMessageType, PVOID pMessage);

	BOOL					Connect					(LPCSTR server_name);
	void					Disconnect				();

	void					net_Syncronize			();
	BOOL					net_isCompleted_Connect	()	{ return net_Connected==EnmConnectionCompleted;}
	BOOL					net_isFails_Connect		()	{ return net_Connected==EnmConnectionFails;}
	BOOL					net_isCompleted_Sync	()	{ return net_Syncronised;	}
	BOOL					net_isDisconnected		()	{ return net_Disconnected;	}
	IC GameDescriptionData const & get_net_DescriptionData() const { return m_game_description; }
	LPCSTR					net_SessionName			()	{ return *(net_Hosts.front().dpSessionName); }

	// receive
	IC void							StartProcessQueue		()	{ net_Queue.LockQ(); }; // WARNING ! after Start mast be End !!! <-
	IC virtual	NET_Packet*			net_msg_Retreive		()	{ return net_Queue.Retreive();	};//							|
	IC void							net_msg_Release			()	{ net_Queue.Release();			};//							|
	IC void							EndProcessQueue			()	{ net_Queue.UnlockQ();			};//							<-

	// send
	virtual	void			Send					(NET_Packet& P, u32 dwFlags= 0x0008 /*DPNSEND_GUARANTEED*/, u32 dwTimeout=0);
	virtual void			Flush_Send_Buffer		();
	virtual void			OnMessage				(void* data, u32 size);
	virtual void			OnInvalidHost			()	{};
	virtual void			OnInvalidPassword		()	{};
	virtual void			OnSessionFull			()	{};
	virtual void			OnConnectRejected		()	{};
	BOOL					net_HasBandwidth		();
	void					ClearStatistic			();
	IClientStatistic&		GetStatistic			() {return  net_Statistic; }
	void					UpdateStatistic			();
	ClientID const &		GetClientID				() { return net_ClientID; };

			bool			GetServerAddress		(ip_address& pAddress, DWORD* pPort);

	// time management
	IC u32					timeServer				()	{ return TimeGlobal(device_timer) + net_TimeDelta + net_TimeDelta_User; }
	IC u32					timeServer_Async		()	{ return TimerAsync(device_timer) + net_TimeDelta + net_TimeDelta_User; }
	IC u32					timeServer_Delta		()	{ return net_TimeDelta; }
	IC void					timeServer_UserDelta	(s32 d)						{ net_TimeDelta_User=d;	}
	IC void					timeServer_Correct		(u32 sv_time, u32 cl_time);

	virtual	BOOL			net_IsSyncronised		();

	virtual	LPCSTR			GetMsgId2Name			(u16 ID) { return ""; }
	virtual void			OnSessionTerminate		(LPCSTR reason){};

	virtual bool			TestLoadBEClient		() { return false; }

private:
	ClientID				net_ClientID;

    virtual void    _Recieve( const void* data, u32 data_size, u32 param );
    virtual void    _SendTo_LL( const void* data, u32 size, u32 flags, u32 timeout );
};
