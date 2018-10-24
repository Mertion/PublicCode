#pragma once

///////////////////////////////////////////////////////////
//  CComCommunication.h
//  Implementation of the Class CComCommunication
//  Created on:      01-11ÔÂ-2017 18:18:35
//  Original author: Administrator
///////////////////////////////////////////////////////////

#if !defined(EA_003C5C19_1977_4e1e_9EB3_F0FBE878D69B__INCLUDED_)
#define EA_003C5C19_1977_4e1e_9EB3_F0FBE878D69B__INCLUDED_
#pragma once

#include "stdafx.h"
#include "ConnectionIF.h"

class ConnectionCom : public ConnectionIF
{

public:
	ConnectionCom();
	int Connect();
	int DisConnect();
	bool ISConnect();
	int Receive(char* p_pchrData, const int p_nDataSize,int& p_nRecDatalen);
	int Send();

private:
	~ConnectionCom();

};
#endif // !defined(EA_003C5C19_1977_4e1e_9EB3_F0FBE878D69B__INCLUDED_)
