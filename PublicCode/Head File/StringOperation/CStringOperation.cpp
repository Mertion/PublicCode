#include "stdafx.h"
#include "CStringOperation.h"

//拷贝CStringA字符串到Char数组
//返回0-正确，1-CStringA字符串大于Char长度
int CStringOperation::CopyCStringToCharA(OUT char * p_cstrTarget, IN int p_nCharSizeOf, IN CStringA p_strSource)
{
	int t_nRet = 0;
	int t_nLen = p_strSource.GetLength();
	CStringA t_str;
	
	memset(p_cstrTarget, 0, p_nCharSizeOf);

	if (t_nLen >= p_nCharSizeOf)
	{
		t_nLen = p_nCharSizeOf;
		t_str = p_strSource.Right(t_nLen);
		t_nRet = 1;
	}
	else
	{
		t_str = p_strSource;
	}

	memcpy(p_cstrTarget, t_str, t_nLen);
	p_cstrTarget[t_nLen] = 0;

	return t_nRet;
}

//拷贝Char字符串到Char数组
//返回拷贝后字符串长度
int CStringOperation::CopyCharToCharA(OUT char * p_cstrTarget, IN int p_nCharSizeOf, IN char * p_cstrSource)
{
	int t_nLen = 0;

	CString strTmp = _T("");
	strTmp.Format(_T("%s"), p_cstrSource);
	CopyCStringToCharA(p_cstrTarget, p_nCharSizeOf, CStringA(strTmp));

	t_nLen = strlen(p_cstrTarget);
	return t_nLen;
}





int CStringOperation::ctoi(char cSingle)
{
	int nRes = 0;
	if ((cSingle >= '0') && (cSingle <= '9'))
	{
		nRes = (cSingle - '0');
	}

	else if ((cSingle >= 'a') && (cSingle <= 'f'))
	{
		nRes = (cSingle - 'a') + 10;
	}
	else if ((cSingle >= 'A') && (cSingle <= 'F'))
	{
		nRes = (cSingle - 'A') + 10;
	}
	return nRes;
}

BOOL CStringOperation::BCD2ASC(char *strBCD, char *strASC, int lenBCD)
{
	int i;
	memset(strASC, 0, sizeof(lenBCD * 2 + 1));
	for (i = 0; i < lenBCD; i++)
	{
		strASC[i + i] = ((*(strBCD + i)) >> 4) & 0x0f;
		strASC[i + i + 1] = (*(strBCD + i)) & 0x0f;
	}
	for (i = 0; i < lenBCD * 2; i++)
	{
		if ((strASC[i] >= 0) && (strASC[i] < 10))
			strASC[i] += '0';
		else
			strASC[i] = strASC[i] + 'A' - 10;
	}

	strASC[lenBCD * 2] = 0x00;
	return TRUE;
}


int CStringOperation::AscToInt(char cIn)
{
	int nRet;
	if (cIn <= '9' && cIn >= '0')
		nRet = cIn - '0';
	else if (cIn <= 'f' && cIn >= 'a')
		nRet = cIn - 'a' + 10;
	else if (cIn <= 'F' && cIn >= 'A')
		nRet = cIn - 'A' + 10;
	else
		//如果为非法字符就让其大于16
		nRet = cIn + 16;
	return (nRet);
}

BOOL CStringOperation::ASC2BCD(char *strASC, char *strBCD, int lenBCD)
{
	int i, nTemp, nP;
	BOOL bOne = TRUE;
	char*	chrTemp;

	chrTemp = new char[lenBCD * 2 + 1];

	nP = 0;
	memcpy(chrTemp, strASC, lenBCD * 2);

	for (i = 0; i < lenBCD * 2; i++)
	{
		nTemp = AscToInt(chrTemp[i]);
		if (nTemp < 16)
		{
			if (bOne)
			{
				nTemp = nTemp * 16;
				strBCD[nP] = nTemp;
			}
			else
			{
				strBCD[nP] = strBCD[nP] + nTemp;
				nP = nP + 1;
			}
			bOne = !bOne;
		}
	}

	delete[] chrTemp;
	return TRUE;
}

bool CStringOperation::getXMLKEYValueForInt(IN CString p_strXML, IN CString p_strKEY, OUT int & p_nValue, IN int t_nDefaultValue)
{
	bool t_bFlag = false;
	CString p_strValue;

	p_nValue = 0;
	t_bFlag = getXMLKEYValueForString(p_strXML, p_strKEY, p_strValue);
	if (t_bFlag)
	{
		t_bFlag = true;
		p_nValue = _ttoi(p_strValue);
	}
	else
	{
		p_nValue = t_nDefaultValue;
	}

	return t_bFlag;
}

bool CStringOperation::getXMLKEYValueForString(IN CString p_strXML, IN CString p_strKEY, OUT CString & p_strValue)
{
	bool t_bFlag = false;

	int t_nStart = 0;
	int t_nEnd = 0;

	CString t_strStartKEY;
	CString t_strENDKEY ;

	t_strStartKEY = _T("<") + p_strKEY +_T(">");
	t_strENDKEY = _T("</") + p_strKEY + _T(">");

	t_nStart = p_strXML.Find(t_strStartKEY, 0) + t_strStartKEY.GetLength();
	t_nEnd = p_strXML.Find(t_strENDKEY, 0);

	if( (-1 == t_nStart) || (-1 == t_nEnd))
	{
		t_bFlag = false;
	}
	else
	{
		t_bFlag = true;
		p_strValue = p_strXML.Mid(t_nStart, (t_nEnd - t_nStart));
	}
	
	return t_bFlag;
}
