multiline_comment|/*&n; * SA-1101.h&n; *&n; * Copyright (c) Peter Danielsson 1999&n; *&n; * Definition of constants related to the sa1101&n; * support chip for the sa1100&n; *&n; */
multiline_comment|/* Be sure that virtual mapping is defined right */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error You must include hardware.h not SA-1101.h
macro_line|#endif
macro_line|#ifndef SA1101_BASE
macro_line|#error You must define SA-1101 physical base address
macro_line|#endif
macro_line|#ifndef LANGUAGE
macro_line|# ifdef __ASSEMBLY__
DECL|macro|LANGUAGE
macro_line|#  define LANGUAGE Assembly
macro_line|# else
DECL|macro|LANGUAGE
macro_line|#  define LANGUAGE C
macro_line|# endif
macro_line|#endif
macro_line|#ifndef SA1101_p2v
DECL|macro|SA1101_p2v
mdefine_line|#define SA1101_p2v(PhAdd)  (PhAdd)
macro_line|#endif
macro_line|#include &lt;asm/arch/bitfield.h&gt;
DECL|macro|C
mdefine_line|#define C               0
DECL|macro|Assembly
mdefine_line|#define Assembly        1
multiline_comment|/*&n; * Memory map&n; */
DECL|macro|__SHMEM_CONTROL0
mdefine_line|#define __SHMEM_CONTROL0&t;0x00000000
DECL|macro|__SYSTEM_CONTROL1
mdefine_line|#define __SYSTEM_CONTROL1&t;0x00000400
DECL|macro|__ARBITER
mdefine_line|#define __ARBITER&t;&t;0x00020000
DECL|macro|__SYSTEM_CONTROL2
mdefine_line|#define __SYSTEM_CONTROL2&t;0x00040000
DECL|macro|__SYSTEM_CONTROL3
mdefine_line|#define __SYSTEM_CONTROL3&t;0x00060000
DECL|macro|__PARALLEL_PORT
mdefine_line|#define __PARALLEL_PORT&t;&t;0x00080000
DECL|macro|__VIDMEM_CONTROL
mdefine_line|#define __VIDMEM_CONTROL&t;0x00100000
DECL|macro|__UPDATE_FIFO
mdefine_line|#define __UPDATE_FIFO&t;&t;0x00120000
DECL|macro|__SHMEM_CONTROL1
mdefine_line|#define __SHMEM_CONTROL1&t;0x00140000
DECL|macro|__INTERRUPT_CONTROL
mdefine_line|#define __INTERRUPT_CONTROL&t;0x00160000
DECL|macro|__USB_CONTROL
mdefine_line|#define __USB_CONTROL&t;&t;0x00180000
DECL|macro|__TRACK_INTERFACE
mdefine_line|#define __TRACK_INTERFACE&t;0x001a0000
DECL|macro|__MOUSE_INTERFACE
mdefine_line|#define __MOUSE_INTERFACE&t;0x001b0000
DECL|macro|__KEYPAD_INTERFACE
mdefine_line|#define __KEYPAD_INTERFACE&t;0x001c0000
DECL|macro|__PCMCIA_INTERFACE
mdefine_line|#define __PCMCIA_INTERFACE&t;0x001e0000
DECL|macro|__VGA_CONTROL
mdefine_line|#define&t;__VGA_CONTROL&t;&t;0x00200000
DECL|macro|__GPIO_INTERFACE
mdefine_line|#define __GPIO_INTERFACE&t;0x00300000
multiline_comment|/*&n; * Macro that calculates real address for registers in the SA-1101&n; */
DECL|macro|_SA1101
mdefine_line|#define _SA1101( x )    ((x) + SA1101_BASE)
multiline_comment|/*&n; * Interface and shared memory controller registers&n; *&n; * Registers&n; *&t;SKCR&t;&t;SA-1101 control register (read/write)&n; *&t;SMCR&t;&t;Shared Memory Controller Register&n; *&t;SNPR&t;&t;Snoop Register&n; */
DECL|macro|_SKCR
mdefine_line|#define _SKCR&t;&t;_SA1101( 0x00000000 ) /* SA-1101 Control Reg. */
DECL|macro|_SMCR
mdefine_line|#define _SMCR&t;&t;_SA1101( 0x00140000 ) /* Shared Mem. Control Reg. */
DECL|macro|_SNPR
mdefine_line|#define _SNPR&t;&t;_SA1101( 0x00140400 ) /* Snoop Reg. */
macro_line|#if LANGUAGE == C
DECL|macro|SKCR
mdefine_line|#define SKCR&t;&t;(*((volatile Word *) SA1101_p2v (_SKCR)))
DECL|macro|SMCR
mdefine_line|#define SMCR&t;&t;(*((volatile Word *) SA1101_p2v (_SMCR)))
DECL|macro|SNPR
mdefine_line|#define SNPR&t;&t;(*((volatile Word *) SA1101_p2v (_SNPR)))
DECL|macro|SKCR_PLLEn
mdefine_line|#define SKCR_PLLEn&t;  0x0001&t;  /* Enable On-Chip PLL */
DECL|macro|SKCR_BCLKEn
mdefine_line|#define SKCR_BCLKEn&t;  0x0002&t;  /* Enables BCLK */
DECL|macro|SKCR_Sleep
mdefine_line|#define SKCR_Sleep&t;  0x0004&t;  /* Sleep Mode */
DECL|macro|SKCR_IRefEn
mdefine_line|#define SKCR_IRefEn&t;  0x0008&t;  /* DAC Iref input enable */
DECL|macro|SKCR_VCOON
mdefine_line|#define SKCR_VCOON&t;  0x0010&t;  /* VCO bias */
DECL|macro|SKCR_ScanTestEn
mdefine_line|#define SKCR_ScanTestEn&t;  0x0020&t;  /* Enables scan test */
DECL|macro|SKCR_ClockTestEn
mdefine_line|#define SKCR_ClockTestEn  0x0040&t;  /* Enables clock test */
DECL|macro|SMCR_DCAC
mdefine_line|#define SMCR_DCAC&t;  Fld(2,0)&t;  /* Number of column address bits */
DECL|macro|SMCR_DRAC
mdefine_line|#define SMCR_DRAC&t;  Fld(2,2)&t;  /* Number of row address bits */
DECL|macro|SMCR_ArbiterBias
mdefine_line|#define SMCR_ArbiterBias  0x0008&t;  /* favor video or USB */
DECL|macro|SMCR_TopVidMem
mdefine_line|#define SMCR_TopVidMem&t;  Fld(4,5)&t;  /* Top 4 bits of vidmem addr. */
DECL|macro|SMCR_ColAdrBits
mdefine_line|#define SMCR_ColAdrBits( x )&t;&t;  /* col. addr bits 8..11 */ &bslash;&n;&t;(( (x) - 8 ) &lt;&lt; FShft (SMCR_DCAC))
DECL|macro|SMCR_RowAdrBits
mdefine_line|#define SMCR_RowAdrBits( x )&t;&t;  /* row addr bits 9..12 */&bslash;&n;&t;(( (x) - 9 ) &lt;&lt; FShft (SMCR_DRAC)
DECL|macro|SNPR_VFBstart
mdefine_line|#define SNPR_VFBstart&t;  Fld(12,0)&t;/* Video frame buffer addr */
DECL|macro|SNPR_VFBsize
mdefine_line|#define SNPR_VFBsize&t;  Fld(11,12)&t;/* Video frame buffer size */
DECL|macro|SNPR_WholeBank
mdefine_line|#define SNPR_WholeBank&t;  (1 &lt;&lt; 23)&t;/* Whole bank bit */
DECL|macro|SNPR_BankSelect
mdefine_line|#define SNPR_BankSelect&t;  Fld(2,27)&t;/* Bank select */
DECL|macro|SNPR_SnoopEn
mdefine_line|#define SNPR_SnoopEn&t;  (1 &lt;&lt; 31)&t;/* Enable snoop operation */
DECL|macro|SNPR_Set_VFBsize
mdefine_line|#define SNPR_Set_VFBsize( x )   /* set frame buffer size (in kb) */ &bslash;&n;&t;( (x) &lt;&lt; FShft (SNPR_VFBsize))
DECL|macro|SNPR_Select_Bank
mdefine_line|#define SNPR_Select_Bank(x)     /* select bank 0 or 1 */  &bslash;&n;&t;(( (x) + 1 ) &lt;&lt; FShft (SNPR_BankSelect ))
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * Video Memory Controller&n; *&n; * Registers&n; *    VMCCR&t;Configuration register&n; *    VMCAR&t;VMC address register&n; *    VMCDR&t;VMC data register&n; *&n; */
DECL|macro|_VMCCR
mdefine_line|#define _VMCCR&t;&t;_SA1101( 0x00100000 )&t;/* Configuration register */
DECL|macro|_VMCAR
mdefine_line|#define _VMCAR&t;&t;_SA1101( 0x00101000 )&t;/* VMC address register */
DECL|macro|_VMCDR
mdefine_line|#define _VMCDR&t;&t;_SA1101( 0x00101400 )&t;/* VMC data register */
macro_line|#if LANGUAGE == C
DECL|macro|VMCCR
mdefine_line|#define VMCCR&t;&t;(*((volatile Word *) SA1101_p2v (_VMCCR)))
DECL|macro|VMCAR
mdefine_line|#define VMCAR&t;&t;(*((volatile Word *) SA1101_p2v (_VMCAR)))
DECL|macro|VMCDR
mdefine_line|#define VMCDR&t;&t;(*((volatile Word *) SA1101_p2v (_VMCDR)))
DECL|macro|VMCCR_RefreshEn
mdefine_line|#define VMCCR_RefreshEn&t;    0x0000&t;  /* Enable memory refresh */
DECL|macro|VMCCR_Config
mdefine_line|#define VMCCR_Config&t;    0x0001&t;  /* DRAM size */
DECL|macro|VMCCR_RefPeriod
mdefine_line|#define VMCCR_RefPeriod&t;    Fld(2,3)&t;  /* Refresh period */
DECL|macro|VMCCR_StaleDataWait
mdefine_line|#define VMCCR_StaleDataWait Fld(4,5)&t;  /* Stale FIFO data timeout counter */
DECL|macro|VMCCR_SleepState
mdefine_line|#define VMCCR_SleepState    (1&lt;&lt;9)&t;  /* State of interface pins in sleep*/
DECL|macro|VMCCR_RefTest
mdefine_line|#define VMCCR_RefTest&t;    (1&lt;&lt;10)&t;  /* refresh test */
DECL|macro|VMCCR_RefLow
mdefine_line|#define VMCCR_RefLow&t;    Fld(6,11)&t;  /* refresh low counter */
DECL|macro|VMCCR_RefHigh
mdefine_line|#define VMCCR_RefHigh&t;    Fld(7,17)&t;  /* refresh high counter */
DECL|macro|VMCCR_SDTCTest
mdefine_line|#define VMCCR_SDTCTest&t;    Fld(7,24)&t;  /* stale data timeout counter */
DECL|macro|VMCCR_ForceSelfRef
mdefine_line|#define VMCCR_ForceSelfRef  (1&lt;&lt;31)&t;  /* Force self refresh */
macro_line|#endif LANGUAGE == C
multiline_comment|/* Update FIFO&n; *&n; * Registers&n; *    UFCR&t;Update FIFO Control Register&n; *    UFSR&t;Update FIFO Status Register&n; *    UFLVLR&t;update FIFO level register&n; *    UFDR&t;update FIFO data register&n; */
DECL|macro|_UFCR
mdefine_line|#define _UFCR&t;_SA1101(0x00120000)   /* Update FIFO Control Reg. */
DECL|macro|_UFSR
mdefine_line|#define _UFSR&t;_SA1101(0x00120400)   /* Update FIFO Status Reg. */&t;
DECL|macro|_UFLVLR
mdefine_line|#define _UFLVLR&t;_SA1101(0x00120800)   /* Update FIFO level reg. */
DECL|macro|_UFDR
mdefine_line|#define _UFDR&t;_SA1101(0x00120c00)   /* Update FIFO data reg. */
macro_line|#if LANGUAGE == C
DECL|macro|UFCR
mdefine_line|#define UFCR &t;(*((volatile Word *) SA1101_p2v (_UFCR)))
DECL|macro|UFSR
mdefine_line|#define UFSR&t;(*((volatile Word *) SA1101_p2v (_UFSR)))
DECL|macro|UFLVLR
mdefine_line|#define UFLVLR&t;(*((volatile Word *) SA1101_p2v (_UFLVLR))) 
DECL|macro|UFDR
mdefine_line|#define UFDR&t;(*((volatile Word *) SA1101_p2v (_UFDR)))
DECL|macro|UFCR_FifoThreshhold
mdefine_line|#define UFCR_FifoThreshhold&t;Fld(7,0)&t;/* Level for FifoGTn flag */
DECL|macro|UFSR_FifoGTnFlag
mdefine_line|#define UFSR_FifoGTnFlag&t;0x01&t;&t;/* FifoGTn flag */#define UFSR_FifoEmpty&t;&t;0x80&t;&t;/* FIFO is empty */
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/* System Controller&n; *&n; * Registers&n; *    SKPCR&t;Power Control Register&n; *    SKCDR&t;Clock Divider Register&n; *    DACDR1&t;DAC1 Data register&n; *    DACDR2&t;DAC2 Data register&n; */
DECL|macro|_SKPCR
mdefine_line|#define _SKPCR&t;&t;_SA1101(0x00000400)
DECL|macro|_SKCDR
mdefine_line|#define _SKCDR&t;&t;_SA1101(0x00040000)
DECL|macro|_DACDR1
mdefine_line|#define _DACDR1&t;&t;_SA1101(0x00060000)
DECL|macro|_DACDR2
mdefine_line|#define _DACDR2&t;&t;_SA1101(0x00060400)
macro_line|#if LANGUAGE == C
DECL|macro|SKPCR
mdefine_line|#define SKPCR &t;(*((volatile Word *) SA1101_p2v (_SKPCR)))
DECL|macro|SKCDR
mdefine_line|#define SKCDR&t;(*((volatile Word *) SA1101_p2v (_SKCDR)))
DECL|macro|DACDR1
mdefine_line|#define DACDR1&t;(*((volatile Word *) SA1101_p2v (_DACDR1)))
DECL|macro|DACDR2
mdefine_line|#define DACDR2&t;(*((volatile Word *) SA1101_p2v (_DACDR2)))
DECL|macro|SKPCR_UCLKEn
mdefine_line|#define SKPCR_UCLKEn&t;     0x01    /* USB Enable */
DECL|macro|SKPCR_PCLKEn
mdefine_line|#define SKPCR_PCLKEn&t;     0x02    /* PS/2 Enable */
DECL|macro|SKPCR_ICLKEn
mdefine_line|#define SKPCR_ICLKEn&t;     0x04    /* Interrupt Controller Enable */
DECL|macro|SKPCR_VCLKEn
mdefine_line|#define SKPCR_VCLKEn&t;     0x08    /* Video Controller Enable */
DECL|macro|SKPCR_PICLKEn
mdefine_line|#define SKPCR_PICLKEn&t;     0x10    /* parallel port Enable */
DECL|macro|SKPCR_DCLKEn
mdefine_line|#define SKPCR_DCLKEn&t;     0x20    /* DACs Enable */
DECL|macro|SKPCR_nKPADEn
mdefine_line|#define SKPCR_nKPADEn&t;     0x40    /* Multiplexer */
DECL|macro|SKCDR_PLLMul
mdefine_line|#define SKCDR_PLLMul&t;     Fld(7,0)&t;/* PLL Multiplier */
DECL|macro|SKCDR_VCLKEn
mdefine_line|#define SKCDR_VCLKEn&t;     Fld(2,7)&t;/* Video controller clock divider */
DECL|macro|SKDCR_BCLKEn
mdefine_line|#define SKDCR_BCLKEn&t;     (1&lt;&lt;9)&t;/* BCLK Divider */
DECL|macro|SKDCR_UTESTCLKEn
mdefine_line|#define SKDCR_UTESTCLKEn     (1&lt;&lt;10)&t;/* Route USB clock during test mode */
DECL|macro|SKDCR_DivRValue
mdefine_line|#define SKDCR_DivRValue&t;     Fld(6,11)&t;/* Input clock divider for PLL */
DECL|macro|SKDCR_DivNValue
mdefine_line|#define SKDCR_DivNValue&t;     Fld(5,17)&t;/* Output clock divider for PLL */
DECL|macro|SKDCR_PLLRSH
mdefine_line|#define SKDCR_PLLRSH&t;     Fld(3,22)&t;/* PLL bandwidth control */
DECL|macro|SKDCR_ChargePump
mdefine_line|#define SKDCR_ChargePump     (1&lt;&lt;25)&t;/* Charge pump control */
DECL|macro|SKDCR_ClkTestMode
mdefine_line|#define SKDCR_ClkTestMode    (1&lt;&lt;26)&t;/* Clock output test mode */
DECL|macro|SKDCR_ClkTestEn
mdefine_line|#define SKDCR_ClkTestEn&t;     (1&lt;&lt;27)&t;/* Test clock generator */
DECL|macro|SKDCR_ClkJitterCntl
mdefine_line|#define SKDCR_ClkJitterCntl  Fld(3,28)&t;/* video clock jitter compensation */
DECL|macro|DACDR_DACCount
mdefine_line|#define DACDR_DACCount&t;     Fld(8,0)&t;/* Count value */
DECL|macro|DACDR1_DACCount
mdefine_line|#define DACDR1_DACCount&t;     DACDR_DACCount
DECL|macro|DACDR2_DACCount
mdefine_line|#define DACDR2_DACCount&t;     DACDR_DACCount
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * Parallel Port Interface&n; *&n; * Registers&n; *    IEEE_Config&t;IEEE mode selection and programmable attributes&n; *    IEEE_Control&t;Controls the states of IEEE port control outputs&n; *    IEEE_Data&t;&t;Forward transfer data register&n; *    IEEE_Addr&t;&t;Forward transfer address register&n; *    IEEE_Status&t;Port IO signal status register&n; *    IEEE_IntStatus&t;Port interrupts status register&n; *    IEEE_FifoLevels   Rx and Tx FIFO interupt generation levels&n; *    IEEE_InitTime&t;Forward timeout counter initial value&n; *    IEEE_TimerStatus&t;Forward timeout counter current value&n; *    IEEE_FifoReset&t;Reset forward transfer FIFO&n; *    IEEE_ReloadValue&t;Counter reload value&n; *    IEEE_TestControl&t;Control testmode&n; *    IEEE_TestDataIn&t;Test data register&n; *    IEEE_TestDataInEn&t;Enable test data&n; *    IEEE_TestCtrlIn&t;Test control signals&n; *    IEEE_TestCtrlInEn&t;Enable test control signals&n; *    IEEE_TestDataStat&t;Current data bus value&n; *&n; */
multiline_comment|/*&n; * The control registers are defined as offsets from a base address &n; */
DECL|macro|_IEEE
mdefine_line|#define _IEEE( x ) _SA1101( (x) + __PARALLEL_PORT )
DECL|macro|_IEEE_Config
mdefine_line|#define _IEEE_Config&t;    _IEEE( 0x0000 )
DECL|macro|_IEEE_Control
mdefine_line|#define _IEEE_Control&t;    _IEEE( 0x0400 )
DECL|macro|_IEEE_Data
mdefine_line|#define _IEEE_Data&t;    _IEEE( 0x4000 )
DECL|macro|_IEEE_Addr
mdefine_line|#define _IEEE_Addr&t;    _IEEE( 0x0800 )
DECL|macro|_IEEE_Status
mdefine_line|#define _IEEE_Status&t;    _IEEE( 0x0c00 )
DECL|macro|_IEEE_IntStatus
mdefine_line|#define _IEEE_IntStatus&t;    _IEEE( 0x1000 )
DECL|macro|_IEEE_FifoLevels
mdefine_line|#define _IEEE_FifoLevels    _IEEE( 0x1400 )
DECL|macro|_IEEE_InitTime
mdefine_line|#define _IEEE_InitTime&t;    _IEEE( 0x1800 )
DECL|macro|_IEEE_TimerStatus
mdefine_line|#define _IEEE_TimerStatus   _IEEE( 0x1c00 )
DECL|macro|_IEEE_FifoReset
mdefine_line|#define _IEEE_FifoReset&t;    _IEEE( 0x2000 )
DECL|macro|_IEEE_ReloadValue
mdefine_line|#define _IEEE_ReloadValue   _IEEE( 0x3c00 )
DECL|macro|_IEEE_TestControl
mdefine_line|#define _IEEE_TestControl   _IEEE( 0x2400 )
DECL|macro|_IEEE_TestDataIn
mdefine_line|#define _IEEE_TestDataIn    _IEEE( 0x2800 )
DECL|macro|_IEEE_TestDataInEn
mdefine_line|#define _IEEE_TestDataInEn  _IEEE( 0x2c00 )
DECL|macro|_IEEE_TestCtrlIn
mdefine_line|#define _IEEE_TestCtrlIn    _IEEE( 0x3000 )
DECL|macro|_IEEE_TestCtrlInEn
mdefine_line|#define _IEEE_TestCtrlInEn  _IEEE( 0x3400 )
DECL|macro|_IEEE_TestDataStat
mdefine_line|#define _IEEE_TestDataStat  _IEEE( 0x3800 )
macro_line|#if LANGUAGE == C
DECL|macro|IEEE_Config
mdefine_line|#define IEEE_Config&t;    (*((volatile Word *) SA1101_p2v (_IEEE_Config)))
DECL|macro|IEEE_Control
mdefine_line|#define IEEE_Control&t;    (*((volatile Word *) SA1101_p2v (_IEEE_Control)))
DECL|macro|IEEE_Data
mdefine_line|#define IEEE_Data&t;    (*((volatile Word *) SA1101_p2v (_IEEE_Data)))
DECL|macro|IEEE_Addr
mdefine_line|#define IEEE_Addr&t;    (*((volatile Word *) SA1101_p2v (_IEEE_Addr)))
DECL|macro|IEEE_Status
mdefine_line|#define IEEE_Status&t;    (*((volatile Word *) SA1101_p2v (_IEEE_Status)))
DECL|macro|IEEE_IntStatus
mdefine_line|#define IEEE_IntStatus&t;    (*((volatile Word *) SA1101_p2v (_IEEE_IntStatus)))
DECL|macro|IEEE_FifoLevels
mdefine_line|#define IEEE_FifoLevels&t;    (*((volatile Word *) SA1101_p2v (_IEEE_FifoLevels)))
DECL|macro|IEEE_InitTime
mdefine_line|#define IEEE_InitTime&t;    (*((volatile Word *) SA1101_p2v (_IEEE_InitTime)))
DECL|macro|IEEE_TimerStatus
mdefine_line|#define IEEE_TimerStatus    (*((volatile Word *) SA1101_p2v (_IEEE_TimerStatus)))
DECL|macro|IEEE_FifoReset
mdefine_line|#define IEEE_FifoReset&t;    (*((volatile Word *) SA1101_p2v (_IEEE_FifoReset)))
DECL|macro|IEEE_ReloadValue
mdefine_line|#define IEEE_ReloadValue    (*((volatile Word *) SA1101_p2v (_IEEE_ReloadValue)))
DECL|macro|IEEE_TestControl
mdefine_line|#define IEEE_TestControl    (*((volatile Word *) SA1101_p2v (_IEEE_TestControl)))
DECL|macro|IEEE_TestDataIn
mdefine_line|#define IEEE_TestDataIn     (*((volatile Word *) SA1101_p2v (_IEEE_TestDataIn)))
DECL|macro|IEEE_TestDataInEn
mdefine_line|#define IEEE_TestDataInEn   (*((volatile Word *) SA1101_p2v (_IEEE_TestDataInEn)))
DECL|macro|IEEE_TestCtrlIn
mdefine_line|#define IEEE_TestCtrlIn     (*((volatile Word *) SA1101_p2v (_IEEE_TestCtrlIn)))
DECL|macro|IEEE_TestCtrlInEn
mdefine_line|#define IEEE_TestCtrlInEn   (*((volatile Word *) SA1101_p2v (_IEEE_TestCtrlInEn)))
DECL|macro|IEEE_TestDataStat
mdefine_line|#define IEEE_TestDataStat   (*((volatile Word *) SA1101_p2v (_IEEE_TestDataStat)))
DECL|macro|IEEE_Config_M
mdefine_line|#define IEEE_Config_M&t;    Fld(3,0)&t; /* Mode select */
DECL|macro|IEEE_Config_D
mdefine_line|#define IEEE_Config_D&t;    0x04&t; /* FIFO access enable */
DECL|macro|IEEE_Config_B
mdefine_line|#define IEEE_Config_B&t;    0x08&t; /* 9-bit word enable */
DECL|macro|IEEE_Config_T
mdefine_line|#define IEEE_Config_T&t;    0x10&t; /* Data transfer enable */
DECL|macro|IEEE_Config_A
mdefine_line|#define IEEE_Config_A&t;    0x20&t; /* Data transfer direction */
DECL|macro|IEEE_Config_E
mdefine_line|#define IEEE_Config_E&t;    0x40&t; /* Timer enable */
DECL|macro|IEEE_Control_A
mdefine_line|#define IEEE_Control_A&t;    0x08&t; /* AutoFd output */
DECL|macro|IEEE_Control_E
mdefine_line|#define IEEE_Control_E&t;    0x04&t; /* Selectin output */
DECL|macro|IEEE_Control_T
mdefine_line|#define IEEE_Control_T&t;    0x02&t; /* Strobe output */
DECL|macro|IEEE_Control_I
mdefine_line|#define IEEE_Control_I&t;    0x01&t; /* Port init output */
DECL|macro|IEEE_Data_C
mdefine_line|#define IEEE_Data_C&t;    (1&lt;&lt;31)&t; /* Byte count */
DECL|macro|IEEE_Data_Db
mdefine_line|#define IEEE_Data_Db&t;    Fld(9,16)&t; /* Data byte 2 */
DECL|macro|IEEE_Data_Da
mdefine_line|#define IEEE_Data_Da&t;    Fld(9,0)&t; /* Data byte 1 */
DECL|macro|IEEE_Addr_A
mdefine_line|#define IEEE_Addr_A&t;    Fld(8,0)&t; /* forward address transfer byte */
DECL|macro|IEEE_Status_A
mdefine_line|#define IEEE_Status_A&t;    0x0100&t; /* nAutoFd port output status */
DECL|macro|IEEE_Status_E
mdefine_line|#define IEEE_Status_E&t;    0x0080&t; /* nSelectIn port output status */
DECL|macro|IEEE_Status_T
mdefine_line|#define IEEE_Status_T&t;    0x0040&t; /* nStrobe port output status */
DECL|macro|IEEE_Status_I
mdefine_line|#define IEEE_Status_I&t;    0x0020&t; /* nInit port output status */
DECL|macro|IEEE_Status_B
mdefine_line|#define IEEE_Status_B&t;    0x0010&t; /* Busy port inout status */
DECL|macro|IEEE_Status_S
mdefine_line|#define IEEE_Status_S&t;    0x0008&t; /* Select port input status */
DECL|macro|IEEE_Status_K
mdefine_line|#define IEEE_Status_K&t;    0x0004&t; /* nAck port input status */
DECL|macro|IEEE_Status_F
mdefine_line|#define IEEE_Status_F&t;    0x0002&t; /* nFault port input status */
DECL|macro|IEEE_Status_R
mdefine_line|#define IEEE_Status_R&t;    0x0001&t; /* pError port input status */
DECL|macro|IEEE_IntStatus_IntReqDat
mdefine_line|#define IEEE_IntStatus_IntReqDat&t; 0x0100
DECL|macro|IEEE_IntStatus_IntReqEmp
mdefine_line|#define IEEE_IntStatus_IntReqEmp&t; 0x0080
DECL|macro|IEEE_IntStatus_IntReqInt
mdefine_line|#define IEEE_IntStatus_IntReqInt&t; 0x0040
DECL|macro|IEEE_IntStatus_IntReqRav
mdefine_line|#define IEEE_IntStatus_IntReqRav&t; 0x0020
DECL|macro|IEEE_IntStatus_IntReqTim
mdefine_line|#define IEEE_IntStatus_IntReqTim&t; 0x0010
DECL|macro|IEEE_IntStatus_RevAddrComp
mdefine_line|#define IEEE_IntStatus_RevAddrComp&t; 0x0008
DECL|macro|IEEE_IntStatus_RevDataComp
mdefine_line|#define IEEE_IntStatus_RevDataComp&t; 0x0004
DECL|macro|IEEE_IntStatus_FwdAddrComp
mdefine_line|#define IEEE_IntStatus_FwdAddrComp&t; 0x0002
DECL|macro|IEEE_IntStatus_FwdDataComp
mdefine_line|#define IEEE_IntStatus_FwdDataComp&t; 0x0001
DECL|macro|IEEE_FifoLevels_RevFifoLevel
mdefine_line|#define IEEE_FifoLevels_RevFifoLevel&t; 2
DECL|macro|IEEE_FifoLevels_FwdFifoLevel
mdefine_line|#define IEEE_FifoLevels_FwdFifoLevel&t; 1
DECL|macro|IEEE_InitTime_TimValInit
mdefine_line|#define IEEE_InitTime_TimValInit&t; Fld(22,0)
DECL|macro|IEEE_TimerStatus_TimValStat
mdefine_line|#define IEEE_TimerStatus_TimValStat&t; Fld(22,0)
DECL|macro|IEEE_ReloadValue_Reload
mdefine_line|#define IEEE_ReloadValue_Reload&t;&t; Fld(4,0)
DECL|macro|IEEE_TestControl_RegClk
mdefine_line|#define IEEE_TestControl_RegClk&t;&t; 0x04
DECL|macro|IEEE_TestControl_ClockSelect
mdefine_line|#define IEEE_TestControl_ClockSelect&t; Fld(2,1)
DECL|macro|IEEE_TestControl_TimerTestModeEn
mdefine_line|#define IEEE_TestControl_TimerTestModeEn 0x01
DECL|macro|IEEE_TestCtrlIn_PError
mdefine_line|#define IEEE_TestCtrlIn_PError&t;&t; 0x10
DECL|macro|IEEE_TestCtrlIn_nFault
mdefine_line|#define IEEE_TestCtrlIn_nFault&t;&t; 0x08
DECL|macro|IEEE_TestCtrlIn_nAck
mdefine_line|#define IEEE_TestCtrlIn_nAck&t;&t; 0x04
DECL|macro|IEEE_TestCtrlIn_PSel
mdefine_line|#define IEEE_TestCtrlIn_PSel&t;&t; 0x02
DECL|macro|IEEE_TestCtrlIn_Busy
mdefine_line|#define IEEE_TestCtrlIn_Busy&t;&t; 0x01
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * VGA Controller&n; *&n; * Registers&n; *    VideoControl&t;Video Control Register&n; *    VgaTiming0&t;VGA Timing Register 0&n; *    VgaTiming1&t;VGA Timing Register 1&n; *    VgaTiming2&t;VGA Timing Register 2&n; *    VgaTiming3&t;VGA Timing Register 3&n; *    VgaBorder&t;&t;VGA Border Color Register&n; *    VgaDBAR&t;&t;VGADMA Base Address Register&n; *    VgaDCAR&t;&t;VGADMA Channel Current Address Register&n; *    VgaStatus&t;&t;VGA Status Register&n; *    VgaInterruptMask&t;VGA Interrupt Mask Register&n; *    VgaPalette&t;VGA Palette Registers&n; *    DacControl&t;DAC Control Register&n; *    VgaTest&t;&t;VGA Controller Test Register&n; */
DECL|macro|_VGA
mdefine_line|#define _VGA( x )&t;_SA1101( ( x ) + __VGA_CONTROL )
DECL|macro|_VideoControl
mdefine_line|#define _VideoControl&t;    _VGA( 0x0000 )
DECL|macro|_VgaTiming0
mdefine_line|#define _VgaTiming0&t;    _VGA( 0x0400 )
DECL|macro|_VgaTiming1
mdefine_line|#define _VgaTiming1&t;    _VGA( 0x0800 )
DECL|macro|_VgaTiming2
mdefine_line|#define _VgaTiming2&t;    _VGA( 0x0c00 )
DECL|macro|_VgaTiming3
mdefine_line|#define _VgaTiming3&t;    _VGA( 0x1000 )
DECL|macro|_VgaBorder
mdefine_line|#define _VgaBorder&t;    _VGA( 0x1400 )
DECL|macro|_VgaDBAR
mdefine_line|#define _VgaDBAR&t;    _VGA( 0x1800 )
DECL|macro|_VgaDCAR
mdefine_line|#define _VgaDCAR&t;    _VGA( 0x1c00 )
DECL|macro|_VgaStatus
mdefine_line|#define _VgaStatus&t;    _VGA( 0x2000 )
DECL|macro|_VgaInterruptMask
mdefine_line|#define _VgaInterruptMask   _VGA( 0x2400 )
DECL|macro|_VgaPalette
mdefine_line|#define _VgaPalette&t;    _VGA( 0x40000 )
DECL|macro|_DacControl
mdefine_line|#define _DacControl&t;    _VGA( 0x3000 )
DECL|macro|_VgaTest
mdefine_line|#define _VgaTest&t;    _VGA( 0x2c00 )
macro_line|#if (LANGUAGE == C)
DECL|macro|VideoControl
mdefine_line|#define VideoControl   (*((volatile Word *) SA1101_p2v (_VideoControl)))
DECL|macro|VgaTiming0
mdefine_line|#define VgaTiming0     (*((volatile Word *) SA1101_p2v (_VgaTiming0)))
DECL|macro|VgaTiming1
mdefine_line|#define VgaTiming1     (*((volatile Word *) SA1101_p2v (_VgaTiming1)))
DECL|macro|VgaTiming2
mdefine_line|#define VgaTiming2     (*((volatile Word *) SA1101_p2v (_VgaTiming2)))
DECL|macro|VgaTiming3
mdefine_line|#define VgaTiming3     (*((volatile Word *) SA1101_p2v (_VgaTiming3)))
DECL|macro|VgaBorder
mdefine_line|#define VgaBorder      (*((volatile Word *) SA1101_p2v (_VgaBorder)))
DECL|macro|VgaDBAR
mdefine_line|#define VgaDBAR&t;       (*((volatile Word *) SA1101_p2v (_VgaDBAR)))
DECL|macro|VgaDCAR
mdefine_line|#define VgaDCAR&t;       (*((volatile Word *) SA1101_p2v (_VgaDCAR)))
DECL|macro|VgaStatus
mdefine_line|#define VgaStatus      (*((volatile Word *) SA1101_p2v (_VgaStatus)))
DECL|macro|VgaInterruptMask
mdefine_line|#define VgaInterruptMask (*((volatile Word *) SA1101_p2v (_VgaInterruptMask)))
DECL|macro|VgaPalette
mdefine_line|#define VgaPalette     (*((volatile Word *) SA1101_p2v (_VgaPalette)))
DECL|macro|DacControl
mdefine_line|#define DacControl     (*((volatile Word *) SA1101_p2v (_DacControl))
DECL|macro|VgaTest
mdefine_line|#define VgaTest        (*((volatile Word *) SA1101_p2v (_VgaTest)))
DECL|macro|VideoControl_VgaEn
mdefine_line|#define VideoControl_VgaEn    0x00000000
DECL|macro|VideoControl_BGR
mdefine_line|#define VideoControl_BGR      0x00000001
DECL|macro|VideoControl_VCompVal
mdefine_line|#define VideoControl_VCompVal Fld(2,2)
DECL|macro|VideoControl_VgaReq
mdefine_line|#define VideoControl_VgaReq   Fld(4,4)
DECL|macro|VideoControl_VBurstL
mdefine_line|#define VideoControl_VBurstL  Fld(4,8)
DECL|macro|VideoControl_VMode
mdefine_line|#define VideoControl_VMode    (1&lt;&lt;12)
DECL|macro|VideoControl_PalRead
mdefine_line|#define VideoControl_PalRead  (1&lt;&lt;13)
DECL|macro|VgaTiming0_PPL
mdefine_line|#define VgaTiming0_PPL&t;      Fld(6,2)
DECL|macro|VgaTiming0_HSW
mdefine_line|#define VgaTiming0_HSW&t;      Fld(8,8)
DECL|macro|VgaTiming0_HFP
mdefine_line|#define VgaTiming0_HFP&t;      Fld(8,16)
DECL|macro|VgaTiming0_HBP
mdefine_line|#define VgaTiming0_HBP&t;      Fld(8,24)
DECL|macro|VgaTiming1_LPS
mdefine_line|#define VgaTiming1_LPS&t;      Fld(10,0)
DECL|macro|VgaTiming1_VSW
mdefine_line|#define VgaTiming1_VSW&t;      Fld(6,10)
DECL|macro|VgaTiming1_VFP
mdefine_line|#define VgaTiming1_VFP&t;      Fld(8,16)
DECL|macro|VgaTiming1_VBP
mdefine_line|#define VgaTiming1_VBP&t;      Fld(8,24)
DECL|macro|VgaTiming2_IVS
mdefine_line|#define VgaTiming2_IVS&t;      0x01
DECL|macro|VgaTiming2_IHS
mdefine_line|#define VgaTiming2_IHS&t;      0x02
DECL|macro|VgaTiming2_CVS
mdefine_line|#define VgaTiming2_CVS&t;      0x04
DECL|macro|VgaTiming2_CHS
mdefine_line|#define VgaTiming2_CHS&t;      0x08
DECL|macro|VgaTiming3_HBS
mdefine_line|#define VgaTiming3_HBS&t;      Fld(8,0)
DECL|macro|VgaTiming3_HBE
mdefine_line|#define VgaTiming3_HBE&t;      Fld(8,8)
DECL|macro|VgaTiming3_VBS
mdefine_line|#define VgaTiming3_VBS&t;      Fld(8,16)
DECL|macro|VgaTiming3_VBE
mdefine_line|#define VgaTiming3_VBE&t;      Fld(8,24)
DECL|macro|VgaBorder_BCOL
mdefine_line|#define VgaBorder_BCOL&t;      Fld(24,0)
DECL|macro|VgaStatus_VFUF
mdefine_line|#define VgaStatus_VFUF&t;      0x01
DECL|macro|VgaStatus_VNext
mdefine_line|#define VgaStatus_VNext&t;      0x02
DECL|macro|VgaStatus_VComp
mdefine_line|#define VgaStatus_VComp&t;      0x04
DECL|macro|VgaInterruptMask_VFUFMask
mdefine_line|#define VgaInterruptMask_VFUFMask   0x00
DECL|macro|VgaInterruptMask_VNextMask
mdefine_line|#define VgaInterruptMask_VNextMask  0x01
DECL|macro|VgaInterruptMask_VCompMask
mdefine_line|#define VgaInterruptMask_VCompMask  0x02
DECL|macro|VgaPalette_R
mdefine_line|#define VgaPalette_R&t;      Fld(8,0)
DECL|macro|VgaPalette_G
mdefine_line|#define VgaPalette_G&t;      Fld(8,8)
DECL|macro|VgaPalette_B
mdefine_line|#define VgaPalette_B&t;      Fld(8,16)
DECL|macro|DacControl_DACON
mdefine_line|#define DacControl_DACON      0x0001
DECL|macro|DacControl_COMPON
mdefine_line|#define DacControl_COMPON     0x0002
DECL|macro|DacControl_PEDON
mdefine_line|#define DacControl_PEDON      0x0004
DECL|macro|DacControl_RTrim
mdefine_line|#define DacControl_RTrim      Fld(5,4)
DECL|macro|DacControl_GTrim
mdefine_line|#define DacControl_GTrim      Fld(5,9)
DECL|macro|DacControl_BTrim
mdefine_line|#define DacControl_BTrim      Fld(5,14)
DECL|macro|VgaTest_TDAC
mdefine_line|#define VgaTest_TDAC&t;      0x00
DECL|macro|VgaTest_Datatest
mdefine_line|#define VgaTest_Datatest      Fld(4,1)
DECL|macro|VgaTest_DACTESTDAC
mdefine_line|#define VgaTest_DACTESTDAC    0x10
DECL|macro|VgaTest_DACTESTOUT
mdefine_line|#define VgaTest_DACTESTOUT    Fld(3,5)
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * USB Host Interface Controller&n; *&n; * Registers&n; *    Revision&n; *    Control&n; *    CommandStatus&n; *    InterruptStatus&n; *    InterruptEnable&n; *    HCCA&n; *    PeriodCurrentED&n; *    ControlHeadED&n; *    BulkHeadED&n; *    BulkCurrentED&n; *    DoneHead&n; *    FmInterval&n; *    FmRemaining&n; *    FmNumber&n; *    PeriodicStart&n; *    LSThreshold&n; *    RhDescriptorA&n; *    RhDescriptorB&n; *    RhStatus&n; *    RhPortStatus&n; *    USBStatus&n; *    USBReset&n; *    USTAR&n; *    USWER&n; *    USRFR&n; *    USNFR&n; *    USTCSR&n; *    USSR&n; *    &n; */
DECL|macro|_USB
mdefine_line|#define _USB( x )&t;_SA1101( ( x ) + __USB_CONTROL )
DECL|macro|_Revision
mdefine_line|#define _Revision&t;  _USB( 0x0000 )
DECL|macro|_Control
mdefine_line|#define _Control&t;  _USB( 0x0888 )
DECL|macro|_CommandStatus
mdefine_line|#define _CommandStatus&t;  _USB( 0x0c00 )
DECL|macro|_InterruptStatus
mdefine_line|#define _InterruptStatus  _USB( 0x1000 )
DECL|macro|_InterruptEnable
mdefine_line|#define _InterruptEnable  _USB( 0x1400 )
DECL|macro|_HCCA
mdefine_line|#define _HCCA&t;&t;  _USB( 0x1800 )
DECL|macro|_PeriodCurrentED
mdefine_line|#define _PeriodCurrentED  _USB( 0x1c00 )
DECL|macro|_ControlHeadED
mdefine_line|#define _ControlHeadED&t;  _USB( 0x2000 )
DECL|macro|_BulkHeadED
mdefine_line|#define _BulkHeadED&t;  _USB( 0x2800 )
DECL|macro|_BulkCurrentED
mdefine_line|#define _BulkCurrentED&t;  _USB( 0x2c00 )
DECL|macro|_DoneHead
mdefine_line|#define _DoneHead&t;  _USB( 0x3000 )
DECL|macro|_FmInterval
mdefine_line|#define _FmInterval&t;  _USB( 0x3400 )
DECL|macro|_FmRemaining
mdefine_line|#define _FmRemaining&t;  _USB( 0x3800 )
DECL|macro|_FmNumber
mdefine_line|#define _FmNumber&t;  _USB( 0x3c00 )
DECL|macro|_PeriodicStart
mdefine_line|#define _PeriodicStart&t;  _USB( 0x4000 )
DECL|macro|_LSThreshold
mdefine_line|#define _LSThreshold&t;  _USB( 0x4400 )
DECL|macro|_RhDescriptorA
mdefine_line|#define _RhDescriptorA&t;  _USB( 0x4800 )
DECL|macro|_RhDescriptorB
mdefine_line|#define _RhDescriptorB&t;  _USB( 0x4c00 )
DECL|macro|_RhStatus
mdefine_line|#define _RhStatus&t;  _USB( 0x5000 )
DECL|macro|_RhPortStatus
mdefine_line|#define _RhPortStatus&t;  _USB( 0x5400 )
DECL|macro|_USBStatus
mdefine_line|#define _USBStatus&t;  _USB( 0x11800 )
DECL|macro|_USBReset
mdefine_line|#define _USBReset&t;  _USB( 0x11c00 )
DECL|macro|_USTAR
mdefine_line|#define _USTAR&t;&t;  _USB( 0x10400 )
DECL|macro|_USWER
mdefine_line|#define _USWER&t;&t;  _USB( 0x10800 )
DECL|macro|_USRFR
mdefine_line|#define _USRFR&t;&t;  _USB( 0x10c00 )
DECL|macro|_USNFR
mdefine_line|#define _USNFR&t;&t;  _USB( 0x11000 )
DECL|macro|_USTCSR
mdefine_line|#define _USTCSR&t;&t;  _USB( 0x11400 )
DECL|macro|_USSR
mdefine_line|#define _USSR&t;&t;  _USB( 0x11800 )
macro_line|#if (LANGUAGE == C)
DECL|macro|Revision
mdefine_line|#define Revision&t;(*((volatile Word *) SA1101_p2v (_Revision)))
DECL|macro|Control
mdefine_line|#define Control&t;&t;(*((volatile Word *) SA1101_p2v (_Control)))
DECL|macro|CommandStatus
mdefine_line|#define CommandStatus&t;(*((volatile Word *) SA1101_p2v (_CommandStatus)))
DECL|macro|InterruptStatus
mdefine_line|#define InterruptStatus&t;(*((volatile Word *) SA1101_p2v (_InterruptStatus)))
DECL|macro|InterruptEnable
mdefine_line|#define InterruptEnable&t;(*((volatile Word *) SA1101_p2v (_InterruptEnable)))
DECL|macro|HCCA
mdefine_line|#define HCCA&t;&t;(*((volatile Word *) SA1101_p2v (_HCCA)))
DECL|macro|PeriodCurrentED
mdefine_line|#define PeriodCurrentED&t;(*((volatile Word *) SA1101_p2v (_PeriodCurrentED)))
DECL|macro|ControlHeadED
mdefine_line|#define ControlHeadED&t;(*((volatile Word *) SA1101_p2v (_ControlHeadED)))
DECL|macro|BulkHeadED
mdefine_line|#define BulkHeadED&t;(*((volatile Word *) SA1101_p2v (_BulkHeadED)))
DECL|macro|BulkCurrentED
mdefine_line|#define BulkCurrentED&t;(*((volatile Word *) SA1101_p2v (_BulkCurrentED)))
DECL|macro|DoneHead
mdefine_line|#define DoneHead&t;(*((volatile Word *) SA1101_p2v (_DoneHead)))
DECL|macro|FmInterval
mdefine_line|#define FmInterval&t;(*((volatile Word *) SA1101_p2v (_FmInterval)))
DECL|macro|FmRemaining
mdefine_line|#define FmRemaining&t;(*((volatile Word *) SA1101_p2v (_FmRemaining)))
DECL|macro|FmNumber
mdefine_line|#define FmNumber&t;(*((volatile Word *) SA1101_p2v (_FmNumber)))
DECL|macro|PeriodicStart
mdefine_line|#define PeriodicStart&t;(*((volatile Word *) SA1101_p2v (_PeriodicStart)))
DECL|macro|LSThreshold
mdefine_line|#define LSThreshold&t;(*((volatile Word *) SA1101_p2v (_LSThreshold)))
DECL|macro|RhDescriptorA
mdefine_line|#define RhDescriptorA&t;(*((volatile Word *) SA1101_p2v (_RhDescriptorA)))
DECL|macro|RhDescriptorB
mdefine_line|#define RhDescriptorB&t;(*((volatile Word *) SA1101_p2v (_RhDescriptorB)))
DECL|macro|RhStatus
mdefine_line|#define RhStatus&t;(*((volatile Word *) SA1101_p2v (_RhStatus)))
DECL|macro|RhPortStatus
mdefine_line|#define RhPortStatus&t;(*((volatile Word *) SA1101_p2v (_RhPortStatus)))
DECL|macro|USBStatus
mdefine_line|#define USBStatus&t;(*((volatile Word *) SA1101_p2v (_USBStatus)))
DECL|macro|USBReset
mdefine_line|#define USBReset&t;(*((volatile Word *) SA1101_p2v (_USBReset)))
DECL|macro|USTAR
mdefine_line|#define USTAR&t;&t;(*((volatile Word *) SA1101_p2v (_USTAR)))
DECL|macro|USWER
mdefine_line|#define USWER&t;&t;(*((volatile Word *) SA1101_p2v (_USWER)))
DECL|macro|USRFR
mdefine_line|#define USRFR&t;&t;(*((volatile Word *) SA1101_p2v (_USRFR)))
DECL|macro|USNFR
mdefine_line|#define USNFR&t;&t;(*((volatile Word *) SA1101_p2v (_USNFR)))
DECL|macro|USTCSR
mdefine_line|#define USTCSR&t;&t;(*((volatile Word *) SA1101_p2v (_USTCSR)))
DECL|macro|USSR
mdefine_line|#define USSR&t;&t;(*((volatile Word *) SA1101_p2v (_USSR)))
DECL|macro|USBStatus_IrqHciRmtWkp
mdefine_line|#define USBStatus_IrqHciRmtWkp&t;     (1&lt;&lt;7)
DECL|macro|USBStatus_IrqHciBuffAcc
mdefine_line|#define USBStatus_IrqHciBuffAcc&t;     (1&lt;&lt;8)
DECL|macro|USBStatus_nIrqHciM
mdefine_line|#define USBStatus_nIrqHciM&t;     (1&lt;&lt;9)
DECL|macro|USBStatus_nHciMFClr
mdefine_line|#define USBStatus_nHciMFClr&t;     (1&lt;&lt;10)
DECL|macro|USBReset_ForceIfReset
mdefine_line|#define USBReset_ForceIfReset&t;     0x01
DECL|macro|USBReset_ForceHcReset
mdefine_line|#define USBReset_ForceHcReset&t;     0x02
DECL|macro|USBReset_ClkGenReset
mdefine_line|#define USBReset_ClkGenReset&t;     0x04
DECL|macro|USTCR_RdBstCntrl
mdefine_line|#define USTCR_RdBstCntrl&t;     Fld(3,0)
DECL|macro|USTCR_ByteEnable
mdefine_line|#define USTCR_ByteEnable&t;     Fld(4,3)
DECL|macro|USTCR_WriteEn
mdefine_line|#define USTCR_WriteEn&t;&t;     (1&lt;&lt;7)
DECL|macro|USTCR_FifoCir
mdefine_line|#define USTCR_FifoCir&t;&t;     (1&lt;&lt;8)
DECL|macro|USTCR_TestXferSel
mdefine_line|#define USTCR_TestXferSel&t;     (1&lt;&lt;9)
DECL|macro|USTCR_FifoCirAtEnd
mdefine_line|#define USTCR_FifoCirAtEnd&t;     (1&lt;&lt;10)
DECL|macro|USTCR_nSimScaleDownClk
mdefine_line|#define USTCR_nSimScaleDownClk&t;     (1&lt;&lt;11)
DECL|macro|USSR_nAppMDEmpty
mdefine_line|#define USSR_nAppMDEmpty&t;     0x01
DECL|macro|USSR_nAppMDFirst
mdefine_line|#define USSR_nAppMDFirst&t;     0x02
DECL|macro|USSR_nAppMDLast
mdefine_line|#define USSR_nAppMDLast&t;&t;     0x04
DECL|macro|USSR_nAppMDFull
mdefine_line|#define USSR_nAppMDFull&t;&t;     0x08
DECL|macro|USSR_nAppMAFull
mdefine_line|#define USSR_nAppMAFull&t;&t;     0x10
DECL|macro|USSR_XferReq
mdefine_line|#define USSR_XferReq&t;&t;     0x20
DECL|macro|USSR_XferEnd
mdefine_line|#define USSR_XferEnd&t;&t;     0x40
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * Interrupt Controller&n; *&n; * Registers&n; *    INTTEST0&t;&t;Test register 0&n; *    INTTEST1&t;&t;Test register 1&n; *    INTENABLE0&t;Interrupt Enable register 0&n; *    INTENABLE1&t;Interrupt Enable register 1&n; *    INTPOL0&t;&t;Interrupt Polarity selection 0&n; *    INTPOL1&t;&t;Interrupt Polarity selection 1&n; *    INTTSTSEL&t;&t;Interrupt source selection&n; *    INTSTATCLR0&t;Interrupt Status 0&n; *    INTSTATCLR1&t;Interrupt Status 1&n; *    INTSET0&t;&t;Interrupt Set 0&n; *    INTSET1&t;&t;Interrupt Set 1&n; */
DECL|macro|_INT
mdefine_line|#define _INT( x )&t;_SA1101( ( x ) + __INTERRUPT_CONTROL)
DECL|macro|_INTTEST0
mdefine_line|#define _INTTEST0&t;_INT( 0x1000 )
DECL|macro|_INTTEST1
mdefine_line|#define _INTTEST1&t;_INT( 0x1400 )
DECL|macro|_INTENABLE0
mdefine_line|#define _INTENABLE0&t;_INT( 0x2000 )
DECL|macro|_INTENABLE1
mdefine_line|#define _INTENABLE1&t;_INT( 0x2400 )
DECL|macro|_INTPOL0
mdefine_line|#define _INTPOL0&t;_INT( 0x3000 )
DECL|macro|_INTPOL1
mdefine_line|#define _INTPOL1&t;_INT( 0x3400 )
DECL|macro|_INTTSTSEL
mdefine_line|#define _INTTSTSEL     &t;_INT( 0x5000 )
DECL|macro|_INTSTATCLR0
mdefine_line|#define _INTSTATCLR0&t;_INT( 0x6000 )
DECL|macro|_INTSTATCLR1
mdefine_line|#define _INTSTATCLR1&t;_INT( 0x6400 )
DECL|macro|_INTSET0
mdefine_line|#define _INTSET0&t;_INT( 0x7000 )
DECL|macro|_INTSET1
mdefine_line|#define _INTSET1&t;_INT( 0x7400 )
macro_line|#if ( LANGUAGE == C )
DECL|macro|INTTEST0
mdefine_line|#define INTTEST0&t;(*((volatile Word *) SA1101_p2v (_INTTEST0)))
DECL|macro|INTTEST1
mdefine_line|#define INTTEST1&t;(*((volatile Word *) SA1101_p2v (_INTTEST1)))
DECL|macro|INTENABLE0
mdefine_line|#define INTENABLE0&t;(*((volatile Word *) SA1101_p2v (_INTENABLE0)))
DECL|macro|INTENABLE1
mdefine_line|#define INTENABLE1&t;(*((volatile Word *) SA1101_p2v (_INTENABLE1)))
DECL|macro|INTPOL0
mdefine_line|#define INTPOL0&t;&t;(*((volatile Word *) SA1101_p2v (_INTPOL0)))
DECL|macro|INTPOL1
mdefine_line|#define INTPOL1&t;&t;(*((volatile Word *) SA1101_p2v (_INTPOL1)))
DECL|macro|INTTSTSEL
mdefine_line|#define INTTSTSEL&t;(*((volatile Word *) SA1101_p2v (_INTTSTSEL)))
DECL|macro|INTSTATCLR0
mdefine_line|#define INTSTATCLR0&t;(*((volatile Word *) SA1101_p2v (_INTSTATCLR0)))
DECL|macro|INTSTATCLR1
mdefine_line|#define INTSTATCLR1&t;(*((volatile Word *) SA1101_p2v (_INTSTATCLR1)))
DECL|macro|INTSET0
mdefine_line|#define INTSET0&t;&t;(*((volatile Word *) SA1101_p2v (_INTSET0)))
DECL|macro|INTSET1
mdefine_line|#define INTSET1&t;&t;(*((volatile Word *) SA1101_p2v (_INTSET1)))
macro_line|#endif /* LANGUAGE == C */
multiline_comment|/*&n; * PS/2 Trackpad and Mouse Interfaces&n; *&n; * Registers   (prefix kbd applies to trackpad interface, mse to mouse)&n; *    KBDCR&t;&t;Control Register&n; *    KBDSTAT&t;&t;Status Register&n; *    KBDDATA&t;&t;Transmit/Receive Data register&n; *    KBDCLKDIV&t;&t;Clock Division Register&n; *    KBDPRECNT&t;&t;Clock Precount Register&n; *    KBDTEST1&t;&t;Test register 1&n; *    KBDTEST2&t;&t;Test register 2&n; *    KBDTEST3&t;&t;Test register 3&n; *    KBDTEST4&t;&t;Test register 4&n; *    MSECR&t;&n; *    MSESTAT&n; *    MSEDATA&n; *    MSECLKDIV&n; *    MSEPRECNT&n; *    MSETEST1&n; *    MSETEST2&n; *    MSETEST3&n; *    MSETEST4&n; *     &n; */
DECL|macro|_KBD
mdefine_line|#define _KBD( x )&t;_SA1101( ( x ) + __TRACK_INTERFACE )
DECL|macro|_MSE
mdefine_line|#define _MSE( x )&t;_SA1101( ( x ) + __MOUSE_INTERFACE )
DECL|macro|_KBDCR
mdefine_line|#define _KBDCR&t;&t;_KBD( 0x0000 )
DECL|macro|_KBDSTAT
mdefine_line|#define _KBDSTAT&t;_KBD( 0x0400 )
DECL|macro|_KBDDATA
mdefine_line|#define _KBDDATA&t;_KBD( 0x0800 )
DECL|macro|_KBDCLKDIV
mdefine_line|#define _KBDCLKDIV&t;_KBD( 0x0c00 )
DECL|macro|_KBDPRECNT
mdefine_line|#define _KBDPRECNT&t;_KBD( 0x1000 )
DECL|macro|_KBDTEST1
mdefine_line|#define&t;_KBDTEST1&t;_KBD( 0x2000 )
DECL|macro|_KBDTEST2
mdefine_line|#define _KBDTEST2&t;_KBD( 0x2400 )
DECL|macro|_KBDTEST3
mdefine_line|#define _KBDTEST3&t;_KBD( 0x2800 )
DECL|macro|_KBDTEST4
mdefine_line|#define _KBDTEST4&t;_KBD( 0x2c00 )
DECL|macro|_MSECR
mdefine_line|#define _MSECR&t;&t;_MSE( 0x0000 )
DECL|macro|_MSESTAT
mdefine_line|#define _MSESTAT&t;_MSE( 0x0400 )
DECL|macro|_MSEDATA
mdefine_line|#define _MSEDATA&t;_MSE( 0x0800 )
DECL|macro|_MSECLKDIV
mdefine_line|#define _MSECLKDIV&t;_MSE( 0x0c00 )
DECL|macro|_MSEPRECNT
mdefine_line|#define _MSEPRECNT&t;_MSE( 0x1000 )
DECL|macro|_MSETEST1
mdefine_line|#define&t;_MSETEST1&t;_MSE( 0x2000 )
DECL|macro|_MSETEST2
mdefine_line|#define _MSETEST2&t;_MSE( 0x2400 )
DECL|macro|_MSETEST3
mdefine_line|#define _MSETEST3&t;_MSE( 0x2800 )
DECL|macro|_MSETEST4
mdefine_line|#define _MSETEST4&t;_MSE( 0x2c00 )
macro_line|#if ( LANGUAGE == C )
DECL|macro|KBDCR
mdefine_line|#define KBDCR&t;    (*((volatile Word *) SA1101_p2v (_KBDCR)))
DECL|macro|KBDSTAT
mdefine_line|#define KBDSTAT&t;    (*((volatile Word *) SA1101_p2v (_KBDSTAT)))
DECL|macro|KBDDATA
mdefine_line|#define KBDDATA&t;    (*((volatile Word *) SA1101_p2v (_KBDDATA)))
DECL|macro|KBDCLKDIV
mdefine_line|#define KBDCLKDIV   (*((volatile Word *) SA1101_p2v (_KBDCLKDIV)))
DECL|macro|KBDPRECNT
mdefine_line|#define KBDPRECNT   (*((volatile Word *) SA1101_p2v (_KBDPRECNT)))
DECL|macro|KBDTEST1
mdefine_line|#define KBDTEST1    (*((volatile Word *) SA1101_p2v (_KBDTEST1)))
DECL|macro|KBDTEST2
mdefine_line|#define KBDTEST2    (*((volatile Word *) SA1101_p2v (_KBDTEST2)))
DECL|macro|KBDTEST3
mdefine_line|#define KBDTEST3    (*((volatile Word *) SA1101_p2v (_KBDTEST3)))
DECL|macro|KBDTEST4
mdefine_line|#define KBDTEST4    (*((volatile Word *) SA1101_p2v (_KBDTEST4)))
DECL|macro|MSECR
mdefine_line|#define MSECR&t;    (*((volatile Word *) SA1101_p2v (_MSECR)))
DECL|macro|MSESTAT
mdefine_line|#define MSESTAT&t;    (*((volatile Word *) SA1101_p2v (_MSESTAT)))
DECL|macro|MSEDATA
mdefine_line|#define MSEDATA&t;    (*((volatile Word *) SA1101_p2v (_MSEDATA)))
DECL|macro|MSECLKDIV
mdefine_line|#define MSECLKDIV   (*((volatile Word *) SA1101_p2v (_MSECLKDIV)))
DECL|macro|MSEPRECNT
mdefine_line|#define MSEPRECNT   (*((volatile Word *) SA1101_p2v (_MSEPRECNT)))
DECL|macro|MSETEST1
mdefine_line|#define MSETEST1    (*((volatile Word *) SA1101_p2v (_MSETEST1)))
DECL|macro|MSETEST2
mdefine_line|#define MSETEST2    (*((volatile Word *) SA1101_p2v (_MSETEST2)))
DECL|macro|MSETEST3
mdefine_line|#define MSETEST3    (*((volatile Word *) SA1101_p2v (_MSETEST3)))
DECL|macro|MSETEST4
mdefine_line|#define MSETEST4    (*((volatile Word *) SA1101_p2v (_MSETEST4)))
DECL|macro|KBDCR_ENA
mdefine_line|#define KBDCR_ENA&t;&t; 0x08
DECL|macro|KBDCR_FKD
mdefine_line|#define KBDCR_FKD&t;&t; 0x02
DECL|macro|KBDCR_FKC
mdefine_line|#define KBDCR_FKC&t;&t; 0x01
DECL|macro|KBDSTAT_TXE
mdefine_line|#define KBDSTAT_TXE&t;&t; 0x80
DECL|macro|KBDSTAT_TXB
mdefine_line|#define KBDSTAT_TXB&t;&t; 0x40
DECL|macro|KBDSTAT_RXF
mdefine_line|#define KBDSTAT_RXF&t;&t; 0x20
DECL|macro|KBDSTAT_RXB
mdefine_line|#define KBDSTAT_RXB&t;&t; 0x10
DECL|macro|KBDSTAT_ENA
mdefine_line|#define KBDSTAT_ENA&t;&t; 0x08
DECL|macro|KBDSTAT_RXP
mdefine_line|#define KBDSTAT_RXP&t;&t; 0x04
DECL|macro|KBDSTAT_KBD
mdefine_line|#define KBDSTAT_KBD&t;&t; 0x02
DECL|macro|KBDSTAT_KBC
mdefine_line|#define KBDSTAT_KBC&t;&t; 0x01
DECL|macro|KBDCLKDIV_DivVal
mdefine_line|#define KBDCLKDIV_DivVal&t; Fld(4,0)
DECL|macro|MSECR_ENA
mdefine_line|#define MSECR_ENA&t;&t; 0x08
DECL|macro|MSECR_FKD
mdefine_line|#define MSECR_FKD&t;&t; 0x02
DECL|macro|MSECR_FKC
mdefine_line|#define MSECR_FKC&t;&t; 0x01
DECL|macro|MSESTAT_TXE
mdefine_line|#define MSESTAT_TXE&t;&t; 0x80
DECL|macro|MSESTAT_TXB
mdefine_line|#define MSESTAT_TXB&t;&t; 0x40
DECL|macro|MSESTAT_RXF
mdefine_line|#define MSESTAT_RXF&t;&t; 0x20
DECL|macro|MSESTAT_RXB
mdefine_line|#define MSESTAT_RXB&t;&t; 0x10
DECL|macro|MSESTAT_ENA
mdefine_line|#define MSESTAT_ENA&t;&t; 0x08
DECL|macro|MSESTAT_RXP
mdefine_line|#define MSESTAT_RXP&t;&t; 0x04&t;
DECL|macro|MSESTAT_MSD
mdefine_line|#define MSESTAT_MSD&t;&t; 0x02
DECL|macro|MSESTAT_MSC
mdefine_line|#define MSESTAT_MSC&t;&t; 0x01
DECL|macro|MSECLKDIV_DivVal
mdefine_line|#define MSECLKDIV_DivVal&t; Fld(4,0)
DECL|macro|KBDTEST1_CD
mdefine_line|#define KBDTEST1_CD&t;&t; 0x80
DECL|macro|KBDTEST1_RC1
mdefine_line|#define KBDTEST1_RC1&t;&t; 0x40
DECL|macro|KBDTEST1_MC
mdefine_line|#define KBDTEST1_MC&t;&t; 0x20
DECL|macro|KBDTEST1_C
mdefine_line|#define KBDTEST1_C&t;&t; Fld(2,3)
DECL|macro|KBDTEST1_T2
mdefine_line|#define KBDTEST1_T2&t;&t; 0x40
DECL|macro|KBDTEST1_T1
mdefine_line|#define KBDTEST1_T1&t;&t; 0x20
DECL|macro|KBDTEST1_T0
mdefine_line|#define KBDTEST1_T0&t;&t; 0x10
DECL|macro|KBDTEST2_TICBnRES
mdefine_line|#define KBDTEST2_TICBnRES&t; 0x08
DECL|macro|KBDTEST2_RKC
mdefine_line|#define KBDTEST2_RKC&t;&t; 0x04
DECL|macro|KBDTEST2_RKD
mdefine_line|#define KBDTEST2_RKD&t;&t; 0x02
DECL|macro|KBDTEST2_SEL
mdefine_line|#define KBDTEST2_SEL&t;&t; 0x01
DECL|macro|KBDTEST3_ms_16
mdefine_line|#define KBDTEST3_ms_16&t;&t; 0x80
DECL|macro|KBDTEST3_us_64
mdefine_line|#define KBDTEST3_us_64&t;&t; 0x40
DECL|macro|KBDTEST3_us_16
mdefine_line|#define KBDTEST3_us_16&t;&t; 0x20
DECL|macro|KBDTEST3_DIV8
mdefine_line|#define KBDTEST3_DIV8&t;&t; 0x10
DECL|macro|KBDTEST3_DIn
mdefine_line|#define KBDTEST3_DIn&t;&t; 0x08
DECL|macro|KBDTEST3_CIn
mdefine_line|#define KBDTEST3_CIn&t;&t; 0x04
DECL|macro|KBDTEST3_KD
mdefine_line|#define KBDTEST3_KD&t;&t; 0x02
DECL|macro|KBDTEST3_KC
mdefine_line|#define KBDTEST3_KC&t;&t; 0x01
DECL|macro|KBDTEST4_BC12
mdefine_line|#define KBDTEST4_BC12&t;&t; 0x80
DECL|macro|KBDTEST4_BC11
mdefine_line|#define KBDTEST4_BC11&t;&t; 0x40
DECL|macro|KBDTEST4_TRES
mdefine_line|#define KBDTEST4_TRES&t;&t; 0x20
DECL|macro|KBDTEST4_CLKOE
mdefine_line|#define KBDTEST4_CLKOE&t;&t; 0x10
DECL|macro|KBDTEST4_CRES
mdefine_line|#define KBDTEST4_CRES&t;&t; 0x08
DECL|macro|KBDTEST4_RXB
mdefine_line|#define KBDTEST4_RXB&t;&t; 0x04
DECL|macro|KBDTEST4_TXB
mdefine_line|#define KBDTEST4_TXB&t;&t; 0x02
DECL|macro|KBDTEST4_SRX
mdefine_line|#define KBDTEST4_SRX&t;&t; 0x01
DECL|macro|MSETEST1_CD
mdefine_line|#define MSETEST1_CD&t;&t; 0x80
DECL|macro|MSETEST1_RC1
mdefine_line|#define MSETEST1_RC1&t;&t; 0x40
DECL|macro|MSETEST1_MC
mdefine_line|#define MSETEST1_MC&t;&t; 0x20
DECL|macro|MSETEST1_C
mdefine_line|#define MSETEST1_C&t;&t; Fld(2,3)
DECL|macro|MSETEST1_T2
mdefine_line|#define MSETEST1_T2&t;&t; 0x40
DECL|macro|MSETEST1_T1
mdefine_line|#define MSETEST1_T1&t;&t; 0x20
DECL|macro|MSETEST1_T0
mdefine_line|#define MSETEST1_T0&t;&t; 0x10
DECL|macro|MSETEST2_TICBnRES
mdefine_line|#define MSETEST2_TICBnRES&t; 0x08
DECL|macro|MSETEST2_RKC
mdefine_line|#define MSETEST2_RKC&t;&t; 0x04
DECL|macro|MSETEST2_RKD
mdefine_line|#define MSETEST2_RKD&t;&t; 0x02
DECL|macro|MSETEST2_SEL
mdefine_line|#define MSETEST2_SEL&t;&t; 0x01
DECL|macro|MSETEST3_ms_16
mdefine_line|#define MSETEST3_ms_16&t;&t; 0x80
DECL|macro|MSETEST3_us_64
mdefine_line|#define MSETEST3_us_64&t;&t; 0x40
DECL|macro|MSETEST3_us_16
mdefine_line|#define MSETEST3_us_16&t;&t; 0x20
DECL|macro|MSETEST3_DIV8
mdefine_line|#define MSETEST3_DIV8&t;&t; 0x10
DECL|macro|MSETEST3_DIn
mdefine_line|#define MSETEST3_DIn&t;&t; 0x08
DECL|macro|MSETEST3_CIn
mdefine_line|#define MSETEST3_CIn&t;&t; 0x04
DECL|macro|MSETEST3_KD
mdefine_line|#define MSETEST3_KD&t;&t; 0x02
DECL|macro|MSETEST3_KC
mdefine_line|#define MSETEST3_KC&t;&t; 0x01
DECL|macro|MSETEST4_BC12
mdefine_line|#define MSETEST4_BC12&t;&t; 0x80
DECL|macro|MSETEST4_BC11
mdefine_line|#define MSETEST4_BC11&t;&t; 0x40
DECL|macro|MSETEST4_TRES
mdefine_line|#define MSETEST4_TRES&t;&t; 0x20
DECL|macro|MSETEST4_CLKOE
mdefine_line|#define MSETEST4_CLKOE&t;&t; 0x10
DECL|macro|MSETEST4_CRES
mdefine_line|#define MSETEST4_CRES&t;&t; 0x08
DECL|macro|MSETEST4_RXB
mdefine_line|#define MSETEST4_RXB&t;&t; 0x04
DECL|macro|MSETEST4_TXB
mdefine_line|#define MSETEST4_TXB&t;&t; 0x02
DECL|macro|MSETEST4_SRX
mdefine_line|#define MSETEST4_SRX&t;&t; 0x01
macro_line|#endif  /* LANGUAGE == C */
multiline_comment|/*&n; * General-Purpose I/O Interface&n; *&n; * Registers&n; *    PADWR&t;Port A Data Write Register&n; *    PBDWR&t;Port B Data Write Register&n; *    PADRR&t;Port A Data Read Register&n; *    PBDRR&t;Port B Data Read Register&n; *    PADDR&t;Port A Data Direction Register&n; *    PBDDR&t;Port B Data Direction Register&n; *    PASSR&t;Port A Sleep State Register&n; *    PBSSR&t;Port B Sleep State Register&n; *&n; */
DECL|macro|_PIO
mdefine_line|#define _PIO( x )      _SA1101( ( x ) + __GPIO_INTERFACE )
DECL|macro|_PADWR
mdefine_line|#define _PADWR&t;       _PIO( 0x0000 )
DECL|macro|_PBDWR
mdefine_line|#define _PBDWR&t;       _PIO( 0x0400 )
DECL|macro|_PADRR
mdefine_line|#define _PADRR&t;       _PIO( 0x0000 )
DECL|macro|_PBDRR
mdefine_line|#define _PBDRR&t;       _PIO( 0x0400 )
DECL|macro|_PADDR
mdefine_line|#define _PADDR&t;       _PIO( 0x0800 )
DECL|macro|_PBDDR
mdefine_line|#define _PBDDR&t;       _PIO( 0x0c00 )
DECL|macro|_PASSR
mdefine_line|#define _PASSR&t;       _PIO( 0x1000 )
DECL|macro|_PBSSR
mdefine_line|#define _PBSSR&t;       _PIO( 0x1400 )
macro_line|#if ( LANGUAGE == C )
DECL|macro|PADWR
mdefine_line|#define PADWR&t;    (*((volatile Word *) SA1101_p2v (_PADWR)))
DECL|macro|PBDWR
mdefine_line|#define PBDWR&t;    (*((volatile Word *) SA1101_p2v (_PBDWR)))
DECL|macro|PADRR
mdefine_line|#define PADRR&t;    (*((volatile Word *) SA1101_p2v (_PADRR)))
DECL|macro|PBDRR
mdefine_line|#define PBDRR&t;    (*((volatile Word *) SA1101_p2v (_PBDRR)))
DECL|macro|PADDR
mdefine_line|#define PADDR&t;    (*((volatile Word *) SA1101_p2v (_PADDR)))
DECL|macro|PBDDR
mdefine_line|#define PBDDR&t;    (*((volatile Word *) SA1101_p2v (_PBDDR)))
DECL|macro|PASSR
mdefine_line|#define PASSR&t;    (*((volatile Word *) SA1101_p2v (_PASSR)))
DECL|macro|PBSSR
mdefine_line|#define PBSSR&t;    (*((volatile Word *) SA1101_p2v (_PBSSR)))
macro_line|#endif
multiline_comment|/*&n; * Keypad Interface&n; *&n; * Registers&n; *    PXDWR&n; *    PXDRR&n; *    PYDWR&n; *    PYDRR&n; *&n; */
DECL|macro|_KEYPAD
mdefine_line|#define _KEYPAD( x )&t;_SA1101( ( x ) + __KEYPAD_INTERFACE ) 
DECL|macro|_PXDWR
mdefine_line|#define _PXDWR&t;   _KEYPAD( 0x0000 )
DECL|macro|_PXDRR
mdefine_line|#define _PXDRR&t;   _KEYPAD( 0x0000 )
DECL|macro|_PYDWR
mdefine_line|#define _PYDWR&t;   _KEYPAD( 0x0400 )
DECL|macro|_PYDRR
mdefine_line|#define _PYDRR&t;   _KEYPAD( 0x0400 )
macro_line|#if ( LANGUAGE == C )
DECL|macro|PXDWR
mdefine_line|#define PXDWR&t;    (*((volatile Word *) SA1101_p2v (_PXDWR)))
DECL|macro|PXDRR
mdefine_line|#define PXDRR&t;    (*((volatile Word *) SA1101_p2v (_PXDRR)))
DECL|macro|PYDWR
mdefine_line|#define PYDWR&t;    (*((volatile Word *) SA1101_p2v (_PYDWR)))
DECL|macro|PYDRR
mdefine_line|#define PYDRR&t;    (*((volatile Word *) SA1101_p2v (_PYDRR)))
macro_line|#endif
multiline_comment|/*&n; * PCMCIA Interface&n; *&n; * Registers&n; *    PCSR&t;Status Register&n; *    PCCR&t;Control Register&n; *    PCSSR&t;Sleep State Register&n; *&n; */
DECL|macro|_CARD
mdefine_line|#define _CARD( x )&t;_SA1101( ( x ) + __PCMCIA_INTERFACE )
DECL|macro|_PCSR
mdefine_line|#define _PCSR&t;   _CARD( 0x0000 )
DECL|macro|_PCCR
mdefine_line|#define _PCCR&t;   _CARD( 0x0400 )
DECL|macro|_PCSSR
mdefine_line|#define _PCSSR&t;   _CARD( 0x0800 )
macro_line|#if ( LANGUAGE == C )
DECL|macro|PCSR
mdefine_line|#define PCSR    (*((volatile Word *) SA1101_p2v (_PCSR)))
DECL|macro|PCCR
mdefine_line|#define PCCR&t;(*((volatile Word *) SA1101_p2v (_PCCR)))
DECL|macro|PCSSR
mdefine_line|#define PCSSR&t;(*((volatile Word *) SA1101_p2v (_PCSSR)))
DECL|macro|PCSR_S0_ready
mdefine_line|#define PCSR_S0_ready&t;&t;0x0001
DECL|macro|PCSR_S1_ready
mdefine_line|#define PCSR_S1_ready&t;&t;0x0002
DECL|macro|PCSR_S0_detected
mdefine_line|#define PCSR_S0_detected&t;0x0004
DECL|macro|PCSR_S1_detected
mdefine_line|#define PCSR_S1_detected&t;0x0008
DECL|macro|PCSR_S0_VS1
mdefine_line|#define PCSR_S0_VS1&t;&t;0x0010
DECL|macro|PCSR_S0_VS2
mdefine_line|#define PCSR_S0_VS2&t;&t;0x0020
DECL|macro|PCSR_S1_VS1
mdefine_line|#define PCSR_S1_VS1&t;&t;0x0040
DECL|macro|PCSR_S1_VS2
mdefine_line|#define PCSR_S1_VS2&t;&t;0x0080
DECL|macro|PCSR_S0_WP
mdefine_line|#define PCSR_S0_WP&t;&t;0x0100
DECL|macro|PCSR_S1_WP
mdefine_line|#define PCSR_S1_WP&t;&t;0x0200
DECL|macro|PCSR_S0_BVD1_nSTSCHG
mdefine_line|#define PCSR_S0_BVD1_nSTSCHG&t;0x0400
DECL|macro|PCSR_S0_BVD2_nSPKR
mdefine_line|#define PCSR_S0_BVD2_nSPKR&t;0x0800
DECL|macro|PCSR_S1_BVD1_nSTSCHG
mdefine_line|#define PCSR_S1_BVD1_nSTSCHG&t;0x1000
DECL|macro|PCSR_S1_BVD2_nSPKR
mdefine_line|#define PCSR_S1_BVD2_nSPKR&t;0x2000
DECL|macro|PCCR_S0_VPP0
mdefine_line|#define PCCR_S0_VPP0&t;&t;0x0001
DECL|macro|PCCR_S0_VPP1
mdefine_line|#define PCCR_S0_VPP1&t;&t;0x0002
DECL|macro|PCCR_S0_VCC0
mdefine_line|#define PCCR_S0_VCC0&t;&t;0x0004
DECL|macro|PCCR_S0_VCC1
mdefine_line|#define PCCR_S0_VCC1&t;&t;0x0008
DECL|macro|PCCR_S1_VPP0
mdefine_line|#define PCCR_S1_VPP0&t;&t;0x0010
DECL|macro|PCCR_S1_VPP1
mdefine_line|#define PCCR_S1_VPP1&t;&t;0x0020
DECL|macro|PCCR_S1_VCC0
mdefine_line|#define PCCR_S1_VCC0&t;&t;0x0040
DECL|macro|PCCR_S1_VCC1
mdefine_line|#define PCCR_S1_VCC1&t;&t;0x0080
DECL|macro|PCCR_S0_reset
mdefine_line|#define PCCR_S0_reset&t;&t;0x0100
DECL|macro|PCCR_S1_reset
mdefine_line|#define PCCR_S1_reset&t;&t;0x0200
DECL|macro|PCCR_S0_float
mdefine_line|#define PCCR_S0_float&t;&t;0x0400
DECL|macro|PCCR_S1_float
mdefine_line|#define PCCR_S1_float&t;&t;0x0800
DECL|macro|PCSSR_S0_VCC0
mdefine_line|#define PCSSR_S0_VCC0&t;&t;0x0001
DECL|macro|PCSSR_S0_VCC1
mdefine_line|#define PCSSR_S0_VCC1&t;&t;0x0002
DECL|macro|PCSSR_S0_VPP0
mdefine_line|#define PCSSR_S0_VPP0&t;&t;0x0004
DECL|macro|PCSSR_S0_VPP1
mdefine_line|#define PCSSR_S0_VPP1&t;&t;0x0008
DECL|macro|PCSSR_S0_control
mdefine_line|#define PCSSR_S0_control&t;0x0010
DECL|macro|PCSSR_S1_VCC0
mdefine_line|#define PCSSR_S1_VCC0&t;&t;0x0020
DECL|macro|PCSSR_S1_VCC1
mdefine_line|#define PCSSR_S1_VCC1&t;&t;0x0040
DECL|macro|PCSSR_S1_VPP0
mdefine_line|#define PCSSR_S1_VPP0&t;&t;0x0080
DECL|macro|PCSSR_S1_VPP1
mdefine_line|#define PCSSR_S1_VPP1&t;&t;0x0100
DECL|macro|PCSSR_S1_control
mdefine_line|#define PCSSR_S1_control&t;0x0200
macro_line|#endif
DECL|macro|C
macro_line|#undef C
DECL|macro|Assembly
macro_line|#undef Assembly
eof
