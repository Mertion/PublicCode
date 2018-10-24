#pragma once
class CBYTEARRAY
{
public:
	CBYTEARRAY();
	~CBYTEARRAY();

	void PushBack(IN BYTE * p_pBYTEArray, IN unsigned long p_ulArraySize);
	unsigned long GetBYTE(IN unsigned long p_ulStartPosition, IN unsigned long p_ulLen, OUT BYTE * p_pBYTEArray);
	unsigned long GetBYTE(IN unsigned long p_ulSize, OUT BYTE * p_pBYTEArray);
	
	unsigned long GetSize();
	void Empty();
private:
	BYTE * m_BYTEArray;
	unsigned long m_ulArraySize;
};

