multiline_comment|/*----------------------------------------------------------------------------+&n;|       This source code has been made available to you by IBM on an AS-IS&n;|       basis.  Anyone receiving this source is licensed under IBM&n;|       copyrights to use it in any way he or she deems fit, including&n;|       copying it, modifying it, compiling it, and redistributing it either&n;|       with or without modifications.  No license under IBM patents or&n;|       patent applications is to be implied by the copyright license.&n;|&n;|       Any user of this software should understand that IBM cannot provide&n;|       technical support for this software and will not be responsible for&n;|       any consequences resulting from the use of this software.&n;|&n;|       Any person who transfers this source code or any derivative work&n;|       must include the IBM copyright notice, this paragraph, and the&n;|       preceding two paragraphs in the transferred software.&n;|&n;|       COPYRIGHT   I B M   CORPORATION 1999&n;|       LICENSED MATERIAL  -  PROGRAM PROPERTY OF I B M&n;+----------------------------------------------------------------------------*/
multiline_comment|/*----------------------------------------------------------------------------+&n;| Author: Maciej P. Tyrlik&n;| Component: Include file.&n;| File: stb.h&n;| Purpose: Common Set-tob-box definitions.&n;| Changes:&n;| Date:         Comment:&n;| -----         --------&n;| 14-Jan-97     Created for ElPaso pass 1                                   MPT&n;| 13-May-97     Added function prototype and global variables               MPT&n;| 08-Dec-98     Added RAW IR task information                               MPT&n;| 19-Jan-99     Port to Romeo                                               MPT&n;| 19-May-00     Changed SDRAM to 32MB contiguous 0x1F000000 - 0x20FFFFFF    RLB&n;+----------------------------------------------------------------------------*/
macro_line|#ifndef _stb_h_
DECL|macro|_stb_h_
mdefine_line|#define _stb_h_
multiline_comment|/*----------------------------------------------------------------------------+&n;| Read/write from I/O macros.&n;+----------------------------------------------------------------------------*/
DECL|macro|inbyte
mdefine_line|#define inbyte(port)            (*((unsigned char volatile *)(port)))
DECL|macro|outbyte
mdefine_line|#define outbyte(port,data)      *(unsigned char volatile *)(port)=&bslash;&n;                                (unsigned char)(data)
DECL|macro|inshort
mdefine_line|#define inshort(port)           (*((unsigned short volatile *)(port)))
DECL|macro|outshort
mdefine_line|#define outshort(port,data)     *(unsigned short volatile *)(port)=&bslash;&n;                                (unsigned short)(data)
DECL|macro|inword
mdefine_line|#define inword(port)            (*((unsigned long volatile *)(port)))
DECL|macro|outword
mdefine_line|#define outword(port,data)      *(unsigned long volatile *)(port)=&bslash;&n;                                (unsigned long)(data)
multiline_comment|/*----------------------------------------------------------------------------+&n;| STB interrupts.&n;+----------------------------------------------------------------------------*/
DECL|macro|STB_XP_TP_INT
mdefine_line|#define STB_XP_TP_INT           0
DECL|macro|STB_XP_APP_INT
mdefine_line|#define STB_XP_APP_INT          1
DECL|macro|STB_AUD_INT
mdefine_line|#define STB_AUD_INT             2
DECL|macro|STB_VID_INT
mdefine_line|#define STB_VID_INT             3
DECL|macro|STB_DMA0_INT
mdefine_line|#define STB_DMA0_INT            4
DECL|macro|STB_DMA1_INT
mdefine_line|#define STB_DMA1_INT            5
DECL|macro|STB_DMA2_INT
mdefine_line|#define STB_DMA2_INT            6
DECL|macro|STB_DMA3_INT
mdefine_line|#define STB_DMA3_INT            7
DECL|macro|STB_SCI_INT
mdefine_line|#define STB_SCI_INT             8
DECL|macro|STB_I2C1_INT
mdefine_line|#define STB_I2C1_INT            9
DECL|macro|STB_I2C2_INT
mdefine_line|#define STB_I2C2_INT            10
DECL|macro|STB_GPT_PWM0
mdefine_line|#define STB_GPT_PWM0            11
DECL|macro|STB_GPT_PWM1
mdefine_line|#define STB_GPT_PWM1            12
DECL|macro|STB_SCP_INT
mdefine_line|#define STB_SCP_INT             13
DECL|macro|STB_SSP_INT
mdefine_line|#define STB_SSP_INT             14
DECL|macro|STB_GPT_PWM2
mdefine_line|#define STB_GPT_PWM2            15
DECL|macro|STB_EXT5_INT
mdefine_line|#define STB_EXT5_INT            16
DECL|macro|STB_EXT6_INT
mdefine_line|#define STB_EXT6_INT            17
DECL|macro|STB_EXT7_INT
mdefine_line|#define STB_EXT7_INT            18
DECL|macro|STB_EXT8_INT
mdefine_line|#define STB_EXT8_INT            19
DECL|macro|STB_SCC_INT
mdefine_line|#define STB_SCC_INT             20
DECL|macro|STB_SICC_RECV_INT
mdefine_line|#define STB_SICC_RECV_INT       21
DECL|macro|STB_SICC_TRAN_INT
mdefine_line|#define STB_SICC_TRAN_INT       22
DECL|macro|STB_PPU_INT
mdefine_line|#define STB_PPU_INT             23
DECL|macro|STB_DCRX_INT
mdefine_line|#define STB_DCRX_INT            24
DECL|macro|STB_EXT0_INT
mdefine_line|#define STB_EXT0_INT            25
DECL|macro|STB_EXT1_INT
mdefine_line|#define STB_EXT1_INT            26
DECL|macro|STB_EXT2_INT
mdefine_line|#define STB_EXT2_INT            27
DECL|macro|STB_EXT3_INT
mdefine_line|#define STB_EXT3_INT            28
DECL|macro|STB_EXT4_INT
mdefine_line|#define STB_EXT4_INT            29
DECL|macro|STB_REDWOOD_ENET_INT
mdefine_line|#define STB_REDWOOD_ENET_INT    STB_EXT1_INT
multiline_comment|/*----------------------------------------------------------------------------+&n;| STB tasks, task stack sizes, and task priorities.  The actual task priority&n;| is 1 more than the specified number since priority 0 is reserved (system&n;| internaly adds 1 to supplied priority number).&n;+----------------------------------------------------------------------------*/
DECL|macro|STB_IDLE_TASK_SS
mdefine_line|#define STB_IDLE_TASK_SS        (5* 1024)
DECL|macro|STB_IDLE_TASK_PRIO
mdefine_line|#define STB_IDLE_TASK_PRIO      0
DECL|macro|STB_LEDTEST_SS
mdefine_line|#define STB_LEDTEST_SS          (2* 1024)
DECL|macro|STB_LEDTEST_PRIO
mdefine_line|#define STB_LEDTEST_PRIO        0
DECL|macro|STB_CURSOR_TASK_SS
mdefine_line|#define STB_CURSOR_TASK_SS      (10* 1024)
DECL|macro|STB_CURSOR_TASK_PRIO
mdefine_line|#define STB_CURSOR_TASK_PRIO    7
DECL|macro|STB_MPEG_TASK_SS
mdefine_line|#define STB_MPEG_TASK_SS        (10* 1024)
DECL|macro|STB_MPEG_TASK_PRIO
mdefine_line|#define STB_MPEG_TASK_PRIO      9
DECL|macro|STB_DEMUX_TASK_SS
mdefine_line|#define STB_DEMUX_TASK_SS       (10* 1024)
DECL|macro|STB_DEMUX_TASK_PRIO
mdefine_line|#define STB_DEMUX_TASK_PRIO     20
DECL|macro|RAW_STB_IR_TASK_SS
mdefine_line|#define RAW_STB_IR_TASK_SS      (10* 1024)
DECL|macro|RAW_STB_IR_TASK_PRIO
mdefine_line|#define RAW_STB_IR_TASK_PRIO    20
DECL|macro|STB_SERIAL_ER_TASK_SS
mdefine_line|#define STB_SERIAL_ER_TASK_SS   (10* 1024)
DECL|macro|STB_SERIAL_ER_TASK_PRIO
mdefine_line|#define STB_SERIAL_ER_TASK_PRIO 1
DECL|macro|STB_CA_TASK_SS
mdefine_line|#define STB_CA_TASK_SS          (10* 1024)
DECL|macro|STB_CA_TASK_PRIO
mdefine_line|#define STB_CA_TASK_PRIO        8
DECL|macro|INIT_DEFAULT_VIDEO_SS
mdefine_line|#define INIT_DEFAULT_VIDEO_SS   (10* 1024)
DECL|macro|INIT_DEFAULT_VIDEO_PRIO
mdefine_line|#define INIT_DEFAULT_VIDEO_PRIO 8
DECL|macro|INIT_DEFAULT_SERVI_SS
mdefine_line|#define INIT_DEFAULT_SERVI_SS   (10* 1024)
DECL|macro|INIT_DEFAULT_SERVI_PRIO
mdefine_line|#define INIT_DEFAULT_SERVI_PRIO 8
DECL|macro|INIT_DEFAULT_POST_SS
mdefine_line|#define INIT_DEFAULT_POST_SS    (10* 1024)
DECL|macro|INIT_DEFAULT_POST_PRIO
mdefine_line|#define INIT_DEFAULT_POST_PRIO  8
DECL|macro|INIT_DEFAULT_INTER_SS
mdefine_line|#define INIT_DEFAULT_INTER_SS   (10* 1024)
DECL|macro|INIT_DEFAULT_INTER_PRIO
mdefine_line|#define INIT_DEFAULT_INTER_PRIO 8
DECL|macro|INIT_DEFAULT_BR_SS
mdefine_line|#define INIT_DEFAULT_BR_SS      (10* 1024)
DECL|macro|INIT_DEFAULT_BR_PRIO
mdefine_line|#define INIT_DEFAULT_BR_PRIO    8
DECL|macro|INITIAL_TASK_STACK_SIZE
mdefine_line|#define INITIAL_TASK_STACK_SIZE (32* 1024)
macro_line|#ifdef VESTA
multiline_comment|/*----------------------------------------------------------------------------+&n;| Vesta Overall Address Map (all addresses are double mapped, bit 0 of the&n;| address is not decoded.  Numbers below are dependent on board configuration.&n;| FLASH, SDRAM, DRAM numbers can be affected by actual board setup.&n;|&n;|    FFE0,0000 - FFFF,FFFF        FLASH&n;|    F200,0000 - F210,FFFF        FPGA logic&n;|                                   Ethernet       = F200,0000&n;|                                   LED Display    = F200,0100&n;|                                   Xilinx #1 Regs = F204,0000&n;|                                   Xilinx #2 Regs = F208,0000&n;|                                   Spare          = F20C,0000&n;|                                   IDE CS0        = F210,0000&n;|    F410,0000 - F410,FFFF        IDE CS1&n;|    C000,0000 - C7FF,FFFF        OBP&n;|    C000,0000 - C000,0014        SICC  (16550 + infra red)&n;|    C001,0000 - C001,0018        PPU   (Parallel Port)&n;|    C002,0000 - C002,001B        SC0   (Smart Card 0)&n;|    C003,0000 - C003,000F        I2C0&n;|    C004,0000 - C004,0009        SCC   (16550 UART)&n;|    C005,0000 - C005,0124        GPT   (Timers)&n;|    C006,0000 - C006,0058        GPIO0&n;|    C007,0000 - C007,001b        SC1   (Smart Card 1)&n;|    C008,0000 - C008,FFFF        Unused&n;|    C009,0000 - C009,FFFF        Unused&n;|    C00A,0000 - C00A,FFFF        Unused&n;|    C00B,0000 - C00B,000F        I2C1&n;|    C00C,0000 - C00C,0006        SCP&n;|    C00D,0000 - C00D,0010        SSP&n;|    A000,0000 - A0FF,FFFF        SDRAM1  (16M)&n;|    0000,0000 - 00FF,FFFF        SDRAM0  (16M)&n;+----------------------------------------------------------------------------*/
DECL|macro|STB_FLASH_BASE_ADDRESS
mdefine_line|#define STB_FLASH_BASE_ADDRESS  0xFFE00000
DECL|macro|STB_FPGA_BASE_ADDRESS
mdefine_line|#define STB_FPGA_BASE_ADDRESS   0xF2000000
DECL|macro|STB_SICC_BASE_ADDRESS
mdefine_line|#define STB_SICC_BASE_ADDRESS   0xC0000000
DECL|macro|STB_PPU_BASE_ADDR
mdefine_line|#define STB_PPU_BASE_ADDR       0xC0010000
DECL|macro|STB_SC0_BASE_ADDRESS
mdefine_line|#define STB_SC0_BASE_ADDRESS    0xC0020000
DECL|macro|STB_I2C1_BASE_ADDRESS
mdefine_line|#define STB_I2C1_BASE_ADDRESS   0xC0030000
DECL|macro|STB_SCC_BASE_ADDRESS
mdefine_line|#define STB_SCC_BASE_ADDRESS    0xC0040000
DECL|macro|STB_TIMERS_BASE_ADDRESS
mdefine_line|#define STB_TIMERS_BASE_ADDRESS 0xC0050000
DECL|macro|STB_GPIO0_BASE_ADDRESS
mdefine_line|#define STB_GPIO0_BASE_ADDRESS  0xC0060000
DECL|macro|STB_SC1_BASE_ADDRESS
mdefine_line|#define STB_SC1_BASE_ADDRESS    0xC0070000
DECL|macro|STB_I2C2_BASE_ADDRESS
mdefine_line|#define STB_I2C2_BASE_ADDRESS   0xC00B0000
DECL|macro|STB_SCP_BASE_ADDRESS
mdefine_line|#define STB_SCP_BASE_ADDRESS    0xC00C0000
DECL|macro|STB_SSP_BASE_ADDRESS
mdefine_line|#define STB_SSP_BASE_ADDRESS    0xC00D0000
multiline_comment|/*----------------------------------------------------------------------------+&n;|The following are used by the IBM RTOS SW.&n;|15-May-00 Changed these values to reflect movement of base addresses in&n;|order to support 32MB of contiguous SDRAM space.&n;|Points to the cacheable region since these values are used in IBM RTOS&n;|to establish the vector address.&n;+----------------------------------------------------------------------------*/
DECL|macro|STB_SDRAM1_BASE_ADDRESS
mdefine_line|#define STB_SDRAM1_BASE_ADDRESS 0x20000000
DECL|macro|STB_SDRAM1_SIZE
mdefine_line|#define STB_SDRAM1_SIZE         0x01000000
DECL|macro|STB_SDRAM0_BASE_ADDRESS
mdefine_line|#define STB_SDRAM0_BASE_ADDRESS 0x1F000000
DECL|macro|STB_SDRAM0_SIZE
mdefine_line|#define STB_SDRAM0_SIZE         0x01000000
macro_line|#else
multiline_comment|/*----------------------------------------------------------------------------+&n;| ElPaso Overall Address Map (all addresses are double mapped, bit 0 of the&n;| address is not decoded.  Numbers below are dependent on board configuration.&n;| FLASH, SDRAM, DRAM numbers can be affected by actual board setup.  OPB&n;| devices are inside the ElPaso chip.&n;|    FFE0,0000 - FFFF,FFFF        FLASH&n;|    F144,0000 - F104,FFFF        FPGA logic&n;|    F140,0000 - F100,0000        ethernet (through FPGA logic)&n;|    C000,0000 - C7FF,FFFF        OBP&n;|    C000,0000 - C000,0014        SICC (16550+ infra red)&n;|    C001,0000 - C001,0016        PPU (parallel port)&n;|    C002,0000 - C002,001B        SC (smart card)&n;|    C003,0000 - C003,000F        I2C 1&n;|    C004,0000 - C004,0009        SCC (16550 UART)&n;|    C005,0000 - C005,0124        Timers&n;|    C006,0000 - C006,0058        GPIO0&n;|    C007,0000 - C007,0058        GPIO1&n;|    C008,0000 - C008,0058        GPIO2&n;|    C009,0000 - C009,0058        GPIO3&n;|    C00A,0000 - C00A,0058        GPIO4&n;|    C00B,0000 - C00B,000F        I2C 2&n;|    C00C,0000 - C00C,0006        SCP&n;|    C00D,0000 - C00D,0006        SSP&n;|    A000,0000 - A0FF,FFFF        SDRAM 16M&n;|    0000,0000 - 00FF,FFFF        DRAM 16M&n;+----------------------------------------------------------------------------*/
DECL|macro|STB_FLASH_BASE_ADDRESS
mdefine_line|#define STB_FLASH_BASE_ADDRESS  0xFFE00000
DECL|macro|STB_FPGA_BASE_ADDRESS
mdefine_line|#define STB_FPGA_BASE_ADDRESS   0xF1440000
DECL|macro|STB_ENET_BASE_ADDRESS
mdefine_line|#define STB_ENET_BASE_ADDRESS   0xF1400000
DECL|macro|STB_SICC_BASE_ADDRESS
mdefine_line|#define STB_SICC_BASE_ADDRESS   0xC0000000
DECL|macro|STB_PPU_BASE_ADDR
mdefine_line|#define STB_PPU_BASE_ADDR       0xC0010000
DECL|macro|STB_SC_BASE_ADDRESS
mdefine_line|#define STB_SC_BASE_ADDRESS     0xC0020000
DECL|macro|STB_I2C1_BASE_ADDRESS
mdefine_line|#define STB_I2C1_BASE_ADDRESS   0xC0030000
DECL|macro|STB_SCC_BASE_ADDRESS
mdefine_line|#define STB_SCC_BASE_ADDRESS    0xC0040000
DECL|macro|STB_TIMERS_BASE_ADDRESS
mdefine_line|#define STB_TIMERS_BASE_ADDRESS 0xC0050000
DECL|macro|STB_GPIO0_BASE_ADDRESS
mdefine_line|#define STB_GPIO0_BASE_ADDRESS  0xC0060000
DECL|macro|STB_GPIO1_BASE_ADDRESS
mdefine_line|#define STB_GPIO1_BASE_ADDRESS  0xC0070000
DECL|macro|STB_GPIO2_BASE_ADDRESS
mdefine_line|#define STB_GPIO2_BASE_ADDRESS  0xC0080000
DECL|macro|STB_GPIO3_BASE_ADDRESS
mdefine_line|#define STB_GPIO3_BASE_ADDRESS  0xC0090000
DECL|macro|STB_GPIO4_BASE_ADDRESS
mdefine_line|#define STB_GPIO4_BASE_ADDRESS  0xC00A0000
DECL|macro|STB_I2C2_BASE_ADDRESS
mdefine_line|#define STB_I2C2_BASE_ADDRESS   0xC00B0000
DECL|macro|STB_SCP_BASE_ADDRESS
mdefine_line|#define STB_SCP_BASE_ADDRESS    0xC00C0000
DECL|macro|STB_SSP_BASE_ADDRESS
mdefine_line|#define STB_SSP_BASE_ADDRESS    0xC00D0000
DECL|macro|STB_SDRAM_BASE_ADDRESS
mdefine_line|#define STB_SDRAM_BASE_ADDRESS  0xA0000000
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------------------+&n;| Other common defines.&n;+----------------------------------------------------------------------------*/
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE    1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE   0
macro_line|#endif
macro_line|#endif /* _stb_h_ */
eof
