multiline_comment|/*&n; *  linux/include/asm-arm/hardware/dec21285.h&n; *&n; *  Copyright (C) 1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  DC21285 registers&n; */
DECL|macro|DC21285_PCI_IACK
mdefine_line|#define DC21285_PCI_IACK&t;&t;0x79000000
DECL|macro|DC21285_ARMCSR_BASE
mdefine_line|#define DC21285_ARMCSR_BASE&t;&t;0x42000000
DECL|macro|DC21285_PCI_TYPE_0_CONFIG
mdefine_line|#define DC21285_PCI_TYPE_0_CONFIG&t;0x7b000000
DECL|macro|DC21285_PCI_TYPE_1_CONFIG
mdefine_line|#define DC21285_PCI_TYPE_1_CONFIG&t;0x7a000000
DECL|macro|DC21285_OUTBOUND_WRITE_FLUSH
mdefine_line|#define DC21285_OUTBOUND_WRITE_FLUSH&t;0x78000000
DECL|macro|DC21285_FLASH
mdefine_line|#define DC21285_FLASH&t;&t;&t;0x41000000
DECL|macro|DC21285_PCI_IO
mdefine_line|#define DC21285_PCI_IO&t;&t;&t;0x7c000000
DECL|macro|DC21285_PCI_MEM
mdefine_line|#define DC21285_PCI_MEM&t;&t;&t;0x80000000
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/arch/hardware.h&gt;
DECL|macro|DC21285_IO
mdefine_line|#define DC21285_IO(x)&t;&t;((volatile unsigned long *)(ARMCSR_BASE+(x)))
macro_line|#else
DECL|macro|DC21285_IO
mdefine_line|#define DC21285_IO(x)&t;&t;(x)
macro_line|#endif
DECL|macro|CSR_PCICMD
mdefine_line|#define CSR_PCICMD&t;&t;DC21285_IO(0x0004)
DECL|macro|CSR_CLASSREV
mdefine_line|#define CSR_CLASSREV&t;&t;DC21285_IO(0x0008)
DECL|macro|CSR_PCICACHELINESIZE
mdefine_line|#define CSR_PCICACHELINESIZE&t;DC21285_IO(0x000c)
DECL|macro|CSR_PCICSRBASE
mdefine_line|#define CSR_PCICSRBASE&t;&t;DC21285_IO(0x0010)
DECL|macro|CSR_PCICSRIOBASE
mdefine_line|#define CSR_PCICSRIOBASE&t;DC21285_IO(0x0014)
DECL|macro|CSR_PCISDRAMBASE
mdefine_line|#define CSR_PCISDRAMBASE&t;DC21285_IO(0x0018)
DECL|macro|CSR_PCIROMBASE
mdefine_line|#define CSR_PCIROMBASE&t;&t;DC21285_IO(0x0030)
DECL|macro|CSR_MBOX0
mdefine_line|#define CSR_MBOX0&t;&t;DC21285_IO(0x0050)
DECL|macro|CSR_MBOX1
mdefine_line|#define CSR_MBOX1&t;&t;DC21285_IO(0x0054)
DECL|macro|CSR_MBOX2
mdefine_line|#define CSR_MBOX2&t;&t;DC21285_IO(0x0058)
DECL|macro|CSR_MBOX3
mdefine_line|#define CSR_MBOX3&t;&t;DC21285_IO(0x005c)
DECL|macro|CSR_DOORBELL
mdefine_line|#define CSR_DOORBELL&t;&t;DC21285_IO(0x0060)
DECL|macro|CSR_DOORBELL_SETUP
mdefine_line|#define CSR_DOORBELL_SETUP&t;DC21285_IO(0x0064)
DECL|macro|CSR_ROMWRITEREG
mdefine_line|#define CSR_ROMWRITEREG&t;&t;DC21285_IO(0x0068)
DECL|macro|CSR_CSRBASEMASK
mdefine_line|#define CSR_CSRBASEMASK&t;&t;DC21285_IO(0x00f8)
DECL|macro|CSR_CSRBASEOFFSET
mdefine_line|#define CSR_CSRBASEOFFSET&t;DC21285_IO(0x00fc)
DECL|macro|CSR_SDRAMBASEMASK
mdefine_line|#define CSR_SDRAMBASEMASK&t;DC21285_IO(0x0100)
DECL|macro|CSR_SDRAMBASEOFFSET
mdefine_line|#define CSR_SDRAMBASEOFFSET&t;DC21285_IO(0x0104)
DECL|macro|CSR_ROMBASEMASK
mdefine_line|#define CSR_ROMBASEMASK&t;&t;DC21285_IO(0x0108)
DECL|macro|CSR_SDRAMTIMING
mdefine_line|#define CSR_SDRAMTIMING&t;&t;DC21285_IO(0x010c)
DECL|macro|CSR_SDRAMADDRSIZE0
mdefine_line|#define CSR_SDRAMADDRSIZE0&t;DC21285_IO(0x0110)
DECL|macro|CSR_SDRAMADDRSIZE1
mdefine_line|#define CSR_SDRAMADDRSIZE1&t;DC21285_IO(0x0114)
DECL|macro|CSR_SDRAMADDRSIZE2
mdefine_line|#define CSR_SDRAMADDRSIZE2&t;DC21285_IO(0x0118)
DECL|macro|CSR_SDRAMADDRSIZE3
mdefine_line|#define CSR_SDRAMADDRSIZE3&t;DC21285_IO(0x011c)
DECL|macro|CSR_I2O_INFREEHEAD
mdefine_line|#define CSR_I2O_INFREEHEAD&t;DC21285_IO(0x0120)
DECL|macro|CSR_I2O_INPOSTTAIL
mdefine_line|#define CSR_I2O_INPOSTTAIL&t;DC21285_IO(0x0124)
DECL|macro|CSR_I2O_OUTPOSTHEAD
mdefine_line|#define CSR_I2O_OUTPOSTHEAD&t;DC21285_IO(0x0128)
DECL|macro|CSR_I2O_OUTFREETAIL
mdefine_line|#define CSR_I2O_OUTFREETAIL&t;DC21285_IO(0x012c)
DECL|macro|CSR_I2O_INFREECOUNT
mdefine_line|#define CSR_I2O_INFREECOUNT&t;DC21285_IO(0x0130)
DECL|macro|CSR_I2O_OUTPOSTCOUNT
mdefine_line|#define CSR_I2O_OUTPOSTCOUNT&t;DC21285_IO(0x0134)
DECL|macro|CSR_I2O_INPOSTCOUNT
mdefine_line|#define CSR_I2O_INPOSTCOUNT&t;DC21285_IO(0x0138)
DECL|macro|CSR_SA110_CNTL
mdefine_line|#define CSR_SA110_CNTL&t;&t;DC21285_IO(0x013c)
DECL|macro|SA110_CNTL_INITCMPLETE
mdefine_line|#define SA110_CNTL_INITCMPLETE&t;&t;(1 &lt;&lt; 0)
DECL|macro|SA110_CNTL_ASSERTSERR
mdefine_line|#define SA110_CNTL_ASSERTSERR&t;&t;(1 &lt;&lt; 1)
DECL|macro|SA110_CNTL_RXSERR
mdefine_line|#define SA110_CNTL_RXSERR&t;&t;(1 &lt;&lt; 3)
DECL|macro|SA110_CNTL_SA110DRAMPARITY
mdefine_line|#define SA110_CNTL_SA110DRAMPARITY&t;(1 &lt;&lt; 4)
DECL|macro|SA110_CNTL_PCISDRAMPARITY
mdefine_line|#define SA110_CNTL_PCISDRAMPARITY&t;(1 &lt;&lt; 5)
DECL|macro|SA110_CNTL_DMASDRAMPARITY
mdefine_line|#define SA110_CNTL_DMASDRAMPARITY&t;(1 &lt;&lt; 6)
DECL|macro|SA110_CNTL_DISCARDTIMER
mdefine_line|#define SA110_CNTL_DISCARDTIMER&t;&t;(1 &lt;&lt; 8)
DECL|macro|SA110_CNTL_PCINRESET
mdefine_line|#define SA110_CNTL_PCINRESET&t;&t;(1 &lt;&lt; 9)
DECL|macro|SA110_CNTL_I2O_256
mdefine_line|#define SA110_CNTL_I2O_256&t;&t;(0 &lt;&lt; 10)
DECL|macro|SA110_CNTL_I20_512
mdefine_line|#define SA110_CNTL_I20_512&t;&t;(1 &lt;&lt; 10)
DECL|macro|SA110_CNTL_I2O_1024
mdefine_line|#define SA110_CNTL_I2O_1024&t;&t;(2 &lt;&lt; 10)
DECL|macro|SA110_CNTL_I2O_2048
mdefine_line|#define SA110_CNTL_I2O_2048&t;&t;(3 &lt;&lt; 10)
DECL|macro|SA110_CNTL_I2O_4096
mdefine_line|#define SA110_CNTL_I2O_4096&t;&t;(4 &lt;&lt; 10)
DECL|macro|SA110_CNTL_I2O_8192
mdefine_line|#define SA110_CNTL_I2O_8192&t;&t;(5 &lt;&lt; 10)
DECL|macro|SA110_CNTL_I2O_16384
mdefine_line|#define SA110_CNTL_I2O_16384&t;&t;(6 &lt;&lt; 10)
DECL|macro|SA110_CNTL_I2O_32768
mdefine_line|#define SA110_CNTL_I2O_32768&t;&t;(7 &lt;&lt; 10)
DECL|macro|SA110_CNTL_WATCHDOG
mdefine_line|#define SA110_CNTL_WATCHDOG&t;&t;(1 &lt;&lt; 13)
DECL|macro|SA110_CNTL_ROMWIDTH_UNDEF
mdefine_line|#define SA110_CNTL_ROMWIDTH_UNDEF&t;(0 &lt;&lt; 14)
DECL|macro|SA110_CNTL_ROMWIDTH_16
mdefine_line|#define SA110_CNTL_ROMWIDTH_16&t;&t;(1 &lt;&lt; 14)
DECL|macro|SA110_CNTL_ROMWIDTH_32
mdefine_line|#define SA110_CNTL_ROMWIDTH_32&t;&t;(2 &lt;&lt; 14)
DECL|macro|SA110_CNTL_ROMWIDTH_8
mdefine_line|#define SA110_CNTL_ROMWIDTH_8&t;&t;(3 &lt;&lt; 14)
DECL|macro|SA110_CNTL_ROMACCESSTIME
mdefine_line|#define SA110_CNTL_ROMACCESSTIME(x)&t;((x)&lt;&lt;16)
DECL|macro|SA110_CNTL_ROMBURSTTIME
mdefine_line|#define SA110_CNTL_ROMBURSTTIME(x)&t;((x)&lt;&lt;20)
DECL|macro|SA110_CNTL_ROMTRISTATETIME
mdefine_line|#define SA110_CNTL_ROMTRISTATETIME(x)&t;((x)&lt;&lt;24)
DECL|macro|SA110_CNTL_XCSDIR
mdefine_line|#define SA110_CNTL_XCSDIR(x)&t;&t;((x)&lt;&lt;28)
DECL|macro|SA110_CNTL_PCICFN
mdefine_line|#define SA110_CNTL_PCICFN&t;&t;(1 &lt;&lt; 31)
multiline_comment|/*&n; * footbridge_cfn_mode() is used when we want&n; * to check whether we are the central function&n; */
DECL|macro|__footbridge_cfn_mode
mdefine_line|#define __footbridge_cfn_mode() (*CSR_SA110_CNTL &amp; SA110_CNTL_PCICFN)
macro_line|#if defined(CONFIG_FOOTBRIDGE_HOST) &amp;&amp; defined(CONFIG_FOOTBRIDGE_ADDIN)
DECL|macro|footbridge_cfn_mode
mdefine_line|#define footbridge_cfn_mode() __footbridge_cfn_mode()
macro_line|#elif defined(CONFIG_FOOTBRIDGE_HOST)
DECL|macro|footbridge_cfn_mode
mdefine_line|#define footbridge_cfn_mode() (1)
macro_line|#else
DECL|macro|footbridge_cfn_mode
mdefine_line|#define footbridge_cfn_mode() (0)
macro_line|#endif
DECL|macro|CSR_PCIADDR_EXTN
mdefine_line|#define CSR_PCIADDR_EXTN&t;DC21285_IO(0x0140)
DECL|macro|CSR_PREFETCHMEMRANGE
mdefine_line|#define CSR_PREFETCHMEMRANGE&t;DC21285_IO(0x0144)
DECL|macro|CSR_XBUS_CYCLE
mdefine_line|#define CSR_XBUS_CYCLE&t;&t;DC21285_IO(0x0148)
DECL|macro|CSR_XBUS_IOSTROBE
mdefine_line|#define CSR_XBUS_IOSTROBE&t;DC21285_IO(0x014c)
DECL|macro|CSR_DOORBELL_PCI
mdefine_line|#define CSR_DOORBELL_PCI&t;DC21285_IO(0x0150)
DECL|macro|CSR_DOORBELL_SA110
mdefine_line|#define CSR_DOORBELL_SA110&t;DC21285_IO(0x0154)
DECL|macro|CSR_UARTDR
mdefine_line|#define CSR_UARTDR&t;&t;DC21285_IO(0x0160)
DECL|macro|CSR_RXSTAT
mdefine_line|#define CSR_RXSTAT&t;&t;DC21285_IO(0x0164)
DECL|macro|CSR_H_UBRLCR
mdefine_line|#define CSR_H_UBRLCR&t;&t;DC21285_IO(0x0168)
DECL|macro|CSR_M_UBRLCR
mdefine_line|#define CSR_M_UBRLCR&t;&t;DC21285_IO(0x016c)
DECL|macro|CSR_L_UBRLCR
mdefine_line|#define CSR_L_UBRLCR&t;&t;DC21285_IO(0x0170)
DECL|macro|CSR_UARTCON
mdefine_line|#define CSR_UARTCON&t;&t;DC21285_IO(0x0174)
DECL|macro|CSR_UARTFLG
mdefine_line|#define CSR_UARTFLG&t;&t;DC21285_IO(0x0178)
DECL|macro|CSR_IRQ_STATUS
mdefine_line|#define CSR_IRQ_STATUS&t;&t;DC21285_IO(0x0180)
DECL|macro|CSR_IRQ_RAWSTATUS
mdefine_line|#define CSR_IRQ_RAWSTATUS&t;DC21285_IO(0x0184)
DECL|macro|CSR_IRQ_ENABLE
mdefine_line|#define CSR_IRQ_ENABLE&t;&t;DC21285_IO(0x0188)
DECL|macro|CSR_IRQ_DISABLE
mdefine_line|#define CSR_IRQ_DISABLE&t;&t;DC21285_IO(0x018c)
DECL|macro|CSR_IRQ_SOFT
mdefine_line|#define CSR_IRQ_SOFT&t;&t;DC21285_IO(0x0190)
DECL|macro|CSR_FIQ_STATUS
mdefine_line|#define CSR_FIQ_STATUS&t;&t;DC21285_IO(0x0280)
DECL|macro|CSR_FIQ_RAWSTATUS
mdefine_line|#define CSR_FIQ_RAWSTATUS&t;DC21285_IO(0x0284)
DECL|macro|CSR_FIQ_ENABLE
mdefine_line|#define CSR_FIQ_ENABLE&t;&t;DC21285_IO(0x0288)
DECL|macro|CSR_FIQ_DISABLE
mdefine_line|#define CSR_FIQ_DISABLE&t;&t;DC21285_IO(0x028c)
DECL|macro|CSR_FIQ_SOFT
mdefine_line|#define CSR_FIQ_SOFT&t;&t;DC21285_IO(0x0290)
DECL|macro|CSR_TIMER1_LOAD
mdefine_line|#define CSR_TIMER1_LOAD&t;&t;DC21285_IO(0x0300)
DECL|macro|CSR_TIMER1_VALUE
mdefine_line|#define CSR_TIMER1_VALUE&t;DC21285_IO(0x0304)
DECL|macro|CSR_TIMER1_CNTL
mdefine_line|#define CSR_TIMER1_CNTL&t;&t;DC21285_IO(0x0308)
DECL|macro|CSR_TIMER1_CLR
mdefine_line|#define CSR_TIMER1_CLR&t;&t;DC21285_IO(0x030c)
DECL|macro|CSR_TIMER2_LOAD
mdefine_line|#define CSR_TIMER2_LOAD&t;&t;DC21285_IO(0x0320)
DECL|macro|CSR_TIMER2_VALUE
mdefine_line|#define CSR_TIMER2_VALUE&t;DC21285_IO(0x0324)
DECL|macro|CSR_TIMER2_CNTL
mdefine_line|#define CSR_TIMER2_CNTL&t;&t;DC21285_IO(0x0328)
DECL|macro|CSR_TIMER2_CLR
mdefine_line|#define CSR_TIMER2_CLR&t;&t;DC21285_IO(0x032c)
DECL|macro|CSR_TIMER3_LOAD
mdefine_line|#define CSR_TIMER3_LOAD&t;&t;DC21285_IO(0x0340)
DECL|macro|CSR_TIMER3_VALUE
mdefine_line|#define CSR_TIMER3_VALUE&t;DC21285_IO(0x0344)
DECL|macro|CSR_TIMER3_CNTL
mdefine_line|#define CSR_TIMER3_CNTL&t;&t;DC21285_IO(0x0348)
DECL|macro|CSR_TIMER3_CLR
mdefine_line|#define CSR_TIMER3_CLR&t;&t;DC21285_IO(0x034c)
DECL|macro|CSR_TIMER4_LOAD
mdefine_line|#define CSR_TIMER4_LOAD&t;&t;DC21285_IO(0x0360)
DECL|macro|CSR_TIMER4_VALUE
mdefine_line|#define CSR_TIMER4_VALUE&t;DC21285_IO(0x0364)
DECL|macro|CSR_TIMER4_CNTL
mdefine_line|#define CSR_TIMER4_CNTL&t;&t;DC21285_IO(0x0368)
DECL|macro|CSR_TIMER4_CLR
mdefine_line|#define CSR_TIMER4_CLR&t;&t;DC21285_IO(0x036c)
DECL|macro|TIMER_CNTL_ENABLE
mdefine_line|#define TIMER_CNTL_ENABLE&t;(1 &lt;&lt; 7)
DECL|macro|TIMER_CNTL_AUTORELOAD
mdefine_line|#define TIMER_CNTL_AUTORELOAD&t;(1 &lt;&lt; 6)
DECL|macro|TIMER_CNTL_DIV1
mdefine_line|#define TIMER_CNTL_DIV1&t;&t;(0)
DECL|macro|TIMER_CNTL_DIV16
mdefine_line|#define TIMER_CNTL_DIV16&t;(1 &lt;&lt; 2)
DECL|macro|TIMER_CNTL_DIV256
mdefine_line|#define TIMER_CNTL_DIV256&t;(2 &lt;&lt; 2)
DECL|macro|TIMER_CNTL_CNTEXT
mdefine_line|#define TIMER_CNTL_CNTEXT&t;(3 &lt;&lt; 2)
eof
