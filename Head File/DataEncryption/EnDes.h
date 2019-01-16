/************************************************************************/
/* 作者:周哲                                                            */
/* DES应用加解密                                                        */
/************************************************************************/

#ifndef _ENDES_H
#define _ENDES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENCRYPT   0
#define DECRYPT   1
#define BYTE      unsigned char
#define WORD      unsigned short


	//PACK8 Pack 64 bytes at 1 bit/byte into 8 bytes at 8 bits/byte
	static void pack8(BYTE *packed,BYTE *binary);
	
	//UNPACK8 Unpack 8 bytes at 8 bits/byte into 64 bytes at 1 bit/byte
	static void unpack8(BYTE *packed,BYTE *binary);
	
	//异或
	void Do_XOR(unsigned char *dest,unsigned char *source,int size);
	
	//异或
	void BitXor(BYTE *Data1, BYTE *Data2, int Len, BYTE *Dest);
	
	//设置加解密参数以及密钥 Decrypt: 0-加密 1-解密 key:密钥,8字节
	void DES_setkey( BYTE sw,BYTE *pkey);
	
	//DES计算
	void DES_calcul(BYTE *in,BYTE *out);
	
	//加解密函数 Decrypt: 0-加密 1-解密 key:密钥,8字节 Data:数据,8字节 Result:结果,8字节
	void DES(BYTE Decrypt,BYTE *Key,BYTE *Data,BYTE *Result );
	
	//3DES加解密函数 Decrypt: 0-加密 1-解密 key:密钥,16字节 Data:数据,8字节 Result:结果,8字节
	void Triple_DES(BYTE Decrypt,BYTE* Key,BYTE* Data,BYTE* X_Data );
	
	//3DES加解密函数 Decrypt: 0-加密 1-解密 key:密钥,16字节 Data:数据,长度不限 Result:结果,长度不限
	void CString_TripleDES_EncryptionA( BYTE * p_Key, CStringA  p_strSourceData, CStringA & p_strTargetData);


	//Key schedule of 16 48-bit subkeys generated from 64-bit key



#endif