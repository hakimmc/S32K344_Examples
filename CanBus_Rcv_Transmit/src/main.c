#include "Mcal.h"
#include "Clock_Ip.h"
#include "FlexCAN_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"

#define MSG_ID 0xC0FFEEu
#define RX_MB_IDX 1U
#define TX_MB_IDX 0U
volatile int exit_code = 0;

uint8_t systemid;

/* User includes */
uint8 dummyData[8] = {1,2,3,4,5,6,7,8};
uint8 AppStartData[8] = {'!','A','P','P','S','T','R','T'};
Flexcan_Ip_MsgBuffType rxData;

Flexcan_Ip_DataInfoType rx_info = {
            .msg_id_type = FLEXCAN_MSG_ID_EXT,
            .data_length = 8u,
            .is_polling = FALSE,
            .is_remote = FALSE
    };

Flexcan_Ip_DataInfoType tx_info = {
		.msg_id_type = FLEXCAN_MSG_ID_EXT,
		.data_length = 8u,
		.is_polling = FALSE,
		.is_remote = FALSE
	};

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
extern void CAN0_ORED_0_31_MB_IRQHandler(void);
void JumpToBoot( void );
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len);
volatile uint8_t JumpBootState;

void flexcan0_Callback(uint8 instance, Flexcan_Ip_EventType eventType, uint32 buffIdx,
		const Flexcan_Ip_StateType *flexcanState)
{
	(void)flexcanState;
	(void)instance;
	(void)buffIdx;

	switch(eventType)
	{
	case FLEXCAN_EVENT_RX_COMPLETE:

		if(Comparator(rxData.data,(uint8_t*)"!WAKEAPP",8))
		{
		    FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, MSG_ID, (uint8 *)&AppStartData);
		    JumpBootState = 1;
		}
		else
		{
			FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, MSG_ID+systemid, (uint8 *)&rxData);
			FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
		}
		break;
	default:
		break;
	}
}

static void setupCan( void )
{
	Siul2_Dio_Ip_WritePin(CAN0_EN_PORT, CAN0_EN_PIN, 1U);
	Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 1U);
	FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX, &rx_info, 0x5165+systemid);
	FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0);
}

void __attribute__((optimize("O0"))) delay_ms(uint32_t ms, volatile uint8_t *condition);

int main(void)
{
	systemid = *((volatile uint8_t*)0x500004)==0xFF?0:*((volatile uint8_t*)0x500004);
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    IntCtrl_Ip_EnableIrq(FlexCAN0_1_IRQn);
    IntCtrl_Ip_InstallHandler(FlexCAN0_1_IRQn, CAN0_ORED_0_31_MB_IRQHandler, NULL_PTR);

    tx_info.is_polling = FALSE;
    rx_info.is_polling = FALSE;
    setupCan();


    FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, MSG_ID, (uint8 *)&dummyData);
	FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
    while(1)
    {
        FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, MSG_ID+systemid, (uint8 *)&dummyData);
    	delay_ms(1000, (uint8_t*)0);
    	if(JumpBootState)	break;
    }
    IntCtrl_Ip_DisableIrq(FlexCAN0_1_IRQn);
    FlexCAN_Ip_SetStopMode(INST_FLEXCAN_0);
    FlexCAN_Ip_Deinit(INST_FLEXCAN_0);
    JumpToBoot();
    return 0;
}

uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++) {
        if (source[i] != target[i]) {
            return 0;
        }
    }
    return 1;
}

void __attribute__((optimize("O0"))) delay_ms(uint32_t ms, volatile uint8_t *condition)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
    {
        //for (j = 0; j < 40000; j++)removed for perfect timing with 160mhz clock : loop using 8 cycle; 8 x 40000 = 320.000 => 320.000 / 160.000.000 = 0.002S => 2mS
		//																			2mS is too much max loop value replaced with 20000 for 1 mS;
        for (j = 0; j < 14545; j++)
		{
            //__asm("NOP"); removed for perfect timing 160mhz clock; if i use nop asm block i will be used 9 cycle;
			if(*condition) break;
        }
		if(*condition) break;
    }
}

typedef void (*AppAddr)(void);
AppAddr JumpBootAddr = NULL;
void JumpToBoot( void )
{
	uint32 func = *(uint32 volatile *)(0x400000+ 0xC);
	func = *(uint32 volatile *)(((uint32)func) + 0x4);
	func = ((((uint32)func) & 0xFFFFFFFEU) | 1u); // with "|1u" code worked
	(* (void (*) (void)) func)();
}

/* END main */
/*!
** @}
*/
