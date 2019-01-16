#pragma once
enum Enum_CSecurityVerification
{
	enum_Verification_OK = 0,
	enum_Verification_Failed,
};

typedef struct _VerifiParameter
{
	static const int nRanLen = 32;
	char c_arrRandom[nRanLen+1];	//Ëæ»úÊý
	char c_arrVerifi[nRanLen+1];	//ÑéËãÂë

	_VerifiParameter()
	{
		memset(c_arrRandom, 0, sizeof(c_arrRandom));
		memset(c_arrVerifi, 0, sizeof(c_arrVerifi));
	}
}struVerifiParameter, *pVerifiParameter;

class CSecurityVerification
{
public:
	CSecurityVerification();
	~CSecurityVerification();

	int getRandom(OUT struVerifiParameter &p_VerifiParameter);
	int getVerifi(IN OUT struVerifiParameter &p_VerifiParameter);
	int Verification(IN const struVerifiParameter &p_VerifiParameter);

private:
	BYTE SetCardkey[16];
};

