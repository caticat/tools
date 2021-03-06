﻿#include "pmsg.h"

PMsg::PMsg() : m_msg(""),
	m_pos(m_headLen),
	m_msgLen(m_headLen)
{
	Write((uint32)0); // 将协议头清零
	//*(uint16*)(m_msg.c_str()) = (uint16)0;
	//*((uint16*)(m_msg.c_str())+1) = (uint16)0;
}

PMsg::PMsg(const char* msg,int16 msgLen) : m_msg(""),
	m_pos(m_headLen),
	m_msgLen(m_headLen)
{
	_WriteData(msg,msgLen);
}

void PMsg::SetProto(uint16 proto)
{
	*((uint16*)(m_msg.c_str())+1) = proto;
}

uint16 PMsg::GetProto() const
{
	return *((uint16*)(m_msg.c_str())+1);
}

uint16 PMsg::GetPos() const
{
	return m_pos;
}

const std::string& PMsg::GetData() const
{
	return m_msg;
}

uint16 PMsg::GetDataLen() const
{
	return *(uint16*)(m_msg.c_str());
}

void PMsg::ResetPos()
{
	m_pos = m_headLen;
}

void PMsg::Reset()
{
	m_msg = "";
	m_pos = m_headLen;
	m_msgLen = m_headLen;
	Write((uint32)0);
}

void PMsg::_WriteData(const void* pData,uint16 dataLen)
{
	m_msg.insert(m_msg.length(),(char*)pData,dataLen);
	*(uint16*)(m_msg.c_str()) = (uint16)m_msg.length()-m_headLen; // 更新长度
}
