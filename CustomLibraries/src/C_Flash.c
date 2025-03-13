/**
 * @file C_Flash.c
 * @brief Flash read/write actions.
 * @details This file including many functions about flash read/writing.
 *
 * @author hakimmc
 * @date 2025-01-31
 */

#include "C_Flash.h"

/**
 * @brief CRC Hesaplama Fonksiyonu
 * @param input Giriş verisi
 * @param max_len Hesaba katma uzunluğu
 * @return CRC değeri
 */
uint8_t CRC_Calculator(uint8_t* input,uint8_t max_len)
{
	uint32_t SummOfBytes = 0;
	for(int i=0;i<max_len;i++)
    {
		SummOfBytes += input[i];
	}
	return ((uint8_t)(SummOfBytes%255));
}

/**
 * @brief Flash'a data yazan fonksiyon
 * @param Addr Yazılacak adres verisi
 * @param Data Yazılacak veri
 * @param Length Yazma uzunluğu
 * @MASTER_ID MASTER ID
 * @return Yazma sonucu
 */
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint8_t Length, uint8_t MASTER_ID)
{
	C40_Ip_StatusType c40Status;
	/* Flash Unlock */
	if (STATUS_C40_IP_SECTOR_PROTECTED == C40_Ip_GetSectorNumberFromAddress(Addr))
	{
		C40_Ip_ClearLock(C40_Ip_GetSectorNumberFromAddress(Addr), FLS_MASTER_ID);
	}
	/* Erase Flash */
	do
	{
		c40Status = C40_Ip_MainInterfaceSectorEraseStatus();
	}
	while (STATUS_C40_IP_BUSY == c40Status);
	/* Write Flash */
    C40_Ip_MainInterfaceWrite(C40_Ip_GetSectorNumberFromAddress(Addr), Length, Data, MASTER_ID);
    /* Check Last Status */
    do
	{
		c40Status = C40_Ip_MainInterfaceWriteStatus();
	}
	while (STATUS_C40_IP_BUSY == c40Status);
    return (c40Status==STATUS_C40_IP_SUCCESS?1:0);
}