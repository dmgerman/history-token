multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * ioc.h: Definitions for SGI I/O Controller&n; *&n; * Copyright (C) 1996 David S. Miller&n; * Copyright (C) 1997, 1998, 1999, 2000 Ralf Baechle&n; * Copyright (C) 2001, 2003 Ladislav Michl&n; */
macro_line|#ifndef _SGI_IOC_H
DECL|macro|_SGI_IOC_H
mdefine_line|#define _SGI_IOC_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sgi/pi1.h&gt;
multiline_comment|/* &n; * All registers are 8-bit wide alligned on 32-bit boundary. Bad things&n; * happen if you try word access them. You have been warned.&n; */
DECL|struct|sgioc_uart_regs
r_struct
id|sgioc_uart_regs
(brace
DECL|member|_ctrl1
id|u8
id|_ctrl1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ctrl1
r_volatile
id|u8
id|ctrl1
suffix:semicolon
DECL|member|_data1
id|u8
id|_data1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data1
r_volatile
id|u8
id|data1
suffix:semicolon
DECL|member|_ctrl2
id|u8
id|_ctrl2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ctrl2
r_volatile
id|u8
id|ctrl2
suffix:semicolon
DECL|member|_data2
id|u8
id|_data2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data2
r_volatile
id|u8
id|data2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sgioc_keyb_regs
r_struct
id|sgioc_keyb_regs
(brace
DECL|member|_data
id|u8
id|_data
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data
r_volatile
id|u8
id|data
suffix:semicolon
DECL|member|_command
id|u8
id|_command
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|command
r_volatile
id|u8
id|command
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sgint_regs
r_struct
id|sgint_regs
(brace
DECL|member|_istat0
id|u8
id|_istat0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|istat0
r_volatile
id|u8
id|istat0
suffix:semicolon
multiline_comment|/* Interrupt status zero */
DECL|macro|SGINT_ISTAT0_FFULL
mdefine_line|#define SGINT_ISTAT0_FFULL&t;0x01
DECL|macro|SGINT_ISTAT0_SCSI0
mdefine_line|#define SGINT_ISTAT0_SCSI0&t;0x02
DECL|macro|SGINT_ISTAT0_SCSI1
mdefine_line|#define SGINT_ISTAT0_SCSI1&t;0x04
DECL|macro|SGINT_ISTAT0_ENET
mdefine_line|#define SGINT_ISTAT0_ENET&t;0x08
DECL|macro|SGINT_ISTAT0_GFXDMA
mdefine_line|#define SGINT_ISTAT0_GFXDMA&t;0x10
DECL|macro|SGINT_ISTAT0_PPORT
mdefine_line|#define SGINT_ISTAT0_PPORT&t;0x20
DECL|macro|SGINT_ISTAT0_HPC2
mdefine_line|#define SGINT_ISTAT0_HPC2&t;0x40
DECL|macro|SGINT_ISTAT0_LIO2
mdefine_line|#define SGINT_ISTAT0_LIO2&t;0x80
DECL|member|_imask0
id|u8
id|_imask0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|imask0
r_volatile
id|u8
id|imask0
suffix:semicolon
multiline_comment|/* Interrupt mask zero */
DECL|member|_istat1
id|u8
id|_istat1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|istat1
r_volatile
id|u8
id|istat1
suffix:semicolon
multiline_comment|/* Interrupt status one */
DECL|macro|SGINT_ISTAT1_ISDNI
mdefine_line|#define SGINT_ISTAT1_ISDNI&t;0x01
DECL|macro|SGINT_ISTAT1_PWR
mdefine_line|#define SGINT_ISTAT1_PWR&t;0x02
DECL|macro|SGINT_ISTAT1_ISDNH
mdefine_line|#define SGINT_ISTAT1_ISDNH&t;0x04
DECL|macro|SGINT_ISTAT1_LIO3
mdefine_line|#define SGINT_ISTAT1_LIO3&t;0x08
DECL|macro|SGINT_ISTAT1_HPC3
mdefine_line|#define SGINT_ISTAT1_HPC3&t;0x10
DECL|macro|SGINT_ISTAT1_AFAIL
mdefine_line|#define SGINT_ISTAT1_AFAIL&t;0x20
DECL|macro|SGINT_ISTAT1_VIDEO
mdefine_line|#define SGINT_ISTAT1_VIDEO&t;0x40
DECL|macro|SGINT_ISTAT1_GIO2
mdefine_line|#define SGINT_ISTAT1_GIO2&t;0x80
DECL|member|_imask1
id|u8
id|_imask1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|imask1
r_volatile
id|u8
id|imask1
suffix:semicolon
multiline_comment|/* Interrupt mask one */
DECL|member|_vmeistat
id|u8
id|_vmeistat
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|vmeistat
r_volatile
id|u8
id|vmeistat
suffix:semicolon
multiline_comment|/* VME interrupt status */
DECL|member|_cmeimask0
id|u8
id|_cmeimask0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmeimask0
r_volatile
id|u8
id|cmeimask0
suffix:semicolon
multiline_comment|/* VME interrupt mask zero */
DECL|member|_cmeimask1
id|u8
id|_cmeimask1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmeimask1
r_volatile
id|u8
id|cmeimask1
suffix:semicolon
multiline_comment|/* VME interrupt mask one */
DECL|member|_cmepol
id|u8
id|_cmepol
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmepol
r_volatile
id|u8
id|cmepol
suffix:semicolon
multiline_comment|/* VME polarity */
DECL|member|_tclear
id|u8
id|_tclear
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tclear
r_volatile
id|u8
id|tclear
suffix:semicolon
DECL|member|_errstat
id|u8
id|_errstat
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|errstat
r_volatile
id|u8
id|errstat
suffix:semicolon
multiline_comment|/* Error status reg, reserved on INT2 */
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|_tcnt0
id|u8
id|_tcnt0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tcnt0
r_volatile
id|u8
id|tcnt0
suffix:semicolon
multiline_comment|/* counter 0 */
DECL|member|_tcnt1
id|u8
id|_tcnt1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tcnt1
r_volatile
id|u8
id|tcnt1
suffix:semicolon
multiline_comment|/* counter 1 */
DECL|member|_tcnt2
id|u8
id|_tcnt2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tcnt2
r_volatile
id|u8
id|tcnt2
suffix:semicolon
multiline_comment|/* counter 2 */
DECL|member|_tcword
id|u8
id|_tcword
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tcword
r_volatile
id|u8
id|tcword
suffix:semicolon
multiline_comment|/* control word */
DECL|macro|SGINT_TCWORD_BCD
mdefine_line|#define SGINT_TCWORD_BCD&t;0x01&t;/* Use BCD mode for counters */
DECL|macro|SGINT_TCWORD_MMASK
mdefine_line|#define SGINT_TCWORD_MMASK&t;0x0e&t;/* Mode bitmask. */
DECL|macro|SGINT_TCWORD_MITC
mdefine_line|#define SGINT_TCWORD_MITC&t;0x00&t;/* IRQ on terminal count (doesn&squot;t work) */
DECL|macro|SGINT_TCWORD_MOS
mdefine_line|#define SGINT_TCWORD_MOS&t;0x02&t;/* One-shot IRQ mode. */
DECL|macro|SGINT_TCWORD_MRGEN
mdefine_line|#define SGINT_TCWORD_MRGEN&t;0x04&t;/* Normal rate generation */
DECL|macro|SGINT_TCWORD_MSWGEN
mdefine_line|#define SGINT_TCWORD_MSWGEN&t;0x06&t;/* Square wave generator mode */
DECL|macro|SGINT_TCWORD_MSWST
mdefine_line|#define SGINT_TCWORD_MSWST&t;0x08&t;/* Software strobe */
DECL|macro|SGINT_TCWORD_MHWST
mdefine_line|#define SGINT_TCWORD_MHWST&t;0x0a&t;/* Hardware strobe */
DECL|macro|SGINT_TCWORD_CMASK
mdefine_line|#define SGINT_TCWORD_CMASK&t;0x30&t;/* Command mask */
DECL|macro|SGINT_TCWORD_CLAT
mdefine_line|#define SGINT_TCWORD_CLAT&t;0x00&t;/* Latch command */
DECL|macro|SGINT_TCWORD_CLSB
mdefine_line|#define SGINT_TCWORD_CLSB&t;0x10&t;/* LSB read/write */
DECL|macro|SGINT_TCWORD_CMSB
mdefine_line|#define SGINT_TCWORD_CMSB&t;0x20&t;/* MSB read/write */
DECL|macro|SGINT_TCWORD_CALL
mdefine_line|#define SGINT_TCWORD_CALL&t;0x30&t;/* Full counter read/write */
DECL|macro|SGINT_TCWORD_CNT0
mdefine_line|#define SGINT_TCWORD_CNT0&t;0x00&t;/* Select counter zero */
DECL|macro|SGINT_TCWORD_CNT1
mdefine_line|#define SGINT_TCWORD_CNT1&t;0x40&t;/* Select counter one */
DECL|macro|SGINT_TCWORD_CNT2
mdefine_line|#define SGINT_TCWORD_CNT2&t;0x80&t;/* Select counter two */
DECL|macro|SGINT_TCWORD_CRBCK
mdefine_line|#define SGINT_TCWORD_CRBCK&t;0xc0&t;/* Readback command */
)brace
suffix:semicolon
multiline_comment|/*&n; * The timer is the good old 8254.  Unlike in PCs it&squot;s clocked at exactly 1MHz&n; */
DECL|macro|SGINT_TIMER_CLOCK
mdefine_line|#define SGINT_TIMER_CLOCK&t;1000000
multiline_comment|/*&n; * This is the constant we&squot;re using for calibrating the counter.&n; */
DECL|macro|SGINT_TCSAMP_COUNTER
mdefine_line|#define SGINT_TCSAMP_COUNTER&t;((SGINT_TIMER_CLOCK / HZ) + 255)
multiline_comment|/* We need software copies of these because they are write only. */
r_extern
id|u8
id|sgi_ioc_reset
comma
id|sgi_ioc_write
suffix:semicolon
DECL|struct|sgioc_regs
r_struct
id|sgioc_regs
(brace
DECL|member|pport
r_struct
id|pi1_regs
id|pport
suffix:semicolon
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|uart
r_struct
id|sgioc_uart_regs
id|uart
suffix:semicolon
DECL|member|kbdmouse
r_struct
id|sgioc_keyb_regs
id|kbdmouse
suffix:semicolon
DECL|member|_gcsel
id|u8
id|_gcsel
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|gcsel
r_volatile
id|u8
id|gcsel
suffix:semicolon
DECL|member|_genctrl
id|u8
id|_genctrl
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|genctrl
r_volatile
id|u8
id|genctrl
suffix:semicolon
DECL|member|_panel
id|u8
id|_panel
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|panel
r_volatile
id|u8
id|panel
suffix:semicolon
DECL|macro|SGIOC_PANEL_POWERON
mdefine_line|#define SGIOC_PANEL_POWERON&t;0x01
DECL|macro|SGIOC_PANEL_POWERINTR
mdefine_line|#define SGIOC_PANEL_POWERINTR&t;0x02
DECL|macro|SGIOC_PANEL_VOLDNINTR
mdefine_line|#define SGIOC_PANEL_VOLDNINTR&t;0x10
DECL|macro|SGIOC_PANEL_VOLDNHOLD
mdefine_line|#define SGIOC_PANEL_VOLDNHOLD&t;0x20
DECL|macro|SGIOC_PANEL_VOLUPINTR
mdefine_line|#define SGIOC_PANEL_VOLUPINTR&t;0x40
DECL|macro|SGIOC_PANEL_VOLUPHOLD
mdefine_line|#define SGIOC_PANEL_VOLUPHOLD&t;0x80
DECL|member|_unused1
id|u32
id|_unused1
suffix:semicolon
DECL|member|_sysid
id|u8
id|_sysid
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|sysid
r_volatile
id|u8
id|sysid
suffix:semicolon
DECL|macro|SGIOC_SYSID_FULLHOUSE
mdefine_line|#define SGIOC_SYSID_FULLHOUSE&t;0x01
DECL|macro|SGIOC_SYSID_BOARDREV
mdefine_line|#define SGIOC_SYSID_BOARDREV(x)&t;((x &amp; 0xe0) &gt; 5) 
DECL|macro|SGIOC_SYSID_CHIPREV
mdefine_line|#define SGIOC_SYSID_CHIPREV(x)&t;((x &amp; 0x1e) &gt; 1)
DECL|member|_unused2
id|u32
id|_unused2
suffix:semicolon
DECL|member|_read
id|u8
id|_read
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|read
r_volatile
id|u8
id|read
suffix:semicolon
DECL|member|_unused3
id|u32
id|_unused3
suffix:semicolon
DECL|member|_dmasel
id|u8
id|_dmasel
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|dmasel
r_volatile
id|u8
id|dmasel
suffix:semicolon
DECL|macro|SGIOC_DMASEL_SCLK10MHZ
mdefine_line|#define SGIOC_DMASEL_SCLK10MHZ&t;0x00&t;/* use 10MHZ serial clock */
DECL|macro|SGIOC_DMASEL_ISDNB
mdefine_line|#define SGIOC_DMASEL_ISDNB&t;0x01&t;/* enable isdn B */
DECL|macro|SGIOC_DMASEL_ISDNA
mdefine_line|#define SGIOC_DMASEL_ISDNA&t;0x02&t;/* enable isdn A */
DECL|macro|SGIOC_DMASEL_PPORT
mdefine_line|#define SGIOC_DMASEL_PPORT&t;0x04&t;/* use parallel DMA */
DECL|macro|SGIOC_DMASEL_SCLK667MHZ
mdefine_line|#define SGIOC_DMASEL_SCLK667MHZ&t;0x10&t;/* use 6.67MHZ serial clock */
DECL|macro|SGIOC_DMASEL_SCLKEXT
mdefine_line|#define SGIOC_DMASEL_SCLKEXT&t;0x20&t;/* use external serial clock */
DECL|member|_unused4
id|u32
id|_unused4
suffix:semicolon
DECL|member|_reset
id|u8
id|_reset
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reset
r_volatile
id|u8
id|reset
suffix:semicolon
DECL|macro|SGIOC_RESET_PPORT
mdefine_line|#define SGIOC_RESET_PPORT&t;0x01&t;/* 0=parport reset, 1=nornal */
DECL|macro|SGIOC_RESET_KBDMOUSE
mdefine_line|#define SGIOC_RESET_KBDMOUSE&t;0x02&t;/* 0=kbdmouse reset, 1=normal */
DECL|macro|SGIOC_RESET_EISA
mdefine_line|#define SGIOC_RESET_EISA&t;0x04&t;/* 0=eisa reset, 1=normal */
DECL|macro|SGIOC_RESET_ISDN
mdefine_line|#define SGIOC_RESET_ISDN&t;0x08&t;/* 0=isdn reset, 1=normal */
DECL|macro|SGIOC_RESET_LC0OFF
mdefine_line|#define SGIOC_RESET_LC0OFF&t;0x10&t;/* guiness: turn led off (red, else green) */
DECL|macro|SGIOC_RESET_LC1OFF
mdefine_line|#define SGIOC_RESET_LC1OFF&t;0x20&t;/* guiness: turn led off (green, else amber) */
DECL|member|_unused5
id|u32
id|_unused5
suffix:semicolon
DECL|member|_write
id|u8
id|_write
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|write
r_volatile
id|u8
id|write
suffix:semicolon
DECL|macro|SGIOC_WRITE_NTHRESH
mdefine_line|#define SGIOC_WRITE_NTHRESH&t;0x01&t;/* use 4.5db threshhold */
DECL|macro|SGIOC_WRITE_TPSPEED
mdefine_line|#define SGIOC_WRITE_TPSPEED&t;0x02&t;/* use 100ohm TP speed */
DECL|macro|SGIOC_WRITE_EPSEL
mdefine_line|#define SGIOC_WRITE_EPSEL&t;0x04&t;/* force cable mode: 1=AUI 0=TP */
DECL|macro|SGIOC_WRITE_EASEL
mdefine_line|#define SGIOC_WRITE_EASEL&t;0x08&t;/* 1=autoselect 0=manual cable selection */
DECL|macro|SGIOC_WRITE_U1AMODE
mdefine_line|#define SGIOC_WRITE_U1AMODE&t;0x10&t;/* 1=PC 0=MAC UART mode */
DECL|macro|SGIOC_WRITE_U0AMODE
mdefine_line|#define SGIOC_WRITE_U0AMODE&t;0x20&t;/* 1=PC 0=MAC UART mode */
DECL|macro|SGIOC_WRITE_MLO
mdefine_line|#define SGIOC_WRITE_MLO&t;&t;0x40&t;/* 1=4.75V 0=+5V */
DECL|macro|SGIOC_WRITE_MHI
mdefine_line|#define SGIOC_WRITE_MHI&t;&t;0x80&t;/* 1=5.25V 0=+5V */
DECL|member|_unused6
id|u32
id|_unused6
suffix:semicolon
DECL|member|int3
r_struct
id|sgint_regs
id|int3
suffix:semicolon
DECL|member|_unused7
id|u32
id|_unused7
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|extio
r_volatile
id|u32
id|extio
suffix:semicolon
multiline_comment|/* FullHouse only */
DECL|macro|EXTIO_S0_IRQ_3
mdefine_line|#define EXTIO_S0_IRQ_3&t;&t;0x8000&t;/* S0: vid.vsync */
DECL|macro|EXTIO_S0_IRQ_2
mdefine_line|#define EXTIO_S0_IRQ_2&t;&t;0x4000&t;/* S0: gfx.fifofull */
DECL|macro|EXTIO_S0_IRQ_1
mdefine_line|#define EXTIO_S0_IRQ_1&t;&t;0x2000&t;/* S0: gfx.int */
DECL|macro|EXTIO_S0_RETRACE
mdefine_line|#define EXTIO_S0_RETRACE&t;0x1000
DECL|macro|EXTIO_SG_IRQ_3
mdefine_line|#define EXTIO_SG_IRQ_3&t;&t;0x0800&t;/* SG: vid.vsync */
DECL|macro|EXTIO_SG_IRQ_2
mdefine_line|#define EXTIO_SG_IRQ_2&t;&t;0x0400&t;/* SG: gfx.fifofull */
DECL|macro|EXTIO_SG_IRQ_1
mdefine_line|#define EXTIO_SG_IRQ_1&t;&t;0x0200&t;/* SG: gfx.int */
DECL|macro|EXTIO_SG_RETRACE
mdefine_line|#define EXTIO_SG_RETRACE&t;0x0100
DECL|macro|EXTIO_GIO_33MHZ
mdefine_line|#define EXTIO_GIO_33MHZ&t;&t;0x0080
DECL|macro|EXTIO_EISA_BUSERR
mdefine_line|#define EXTIO_EISA_BUSERR&t;0x0040
DECL|macro|EXTIO_MC_BUSERR
mdefine_line|#define EXTIO_MC_BUSERR&t;&t;0x0020
DECL|macro|EXTIO_HPC3_BUSERR
mdefine_line|#define EXTIO_HPC3_BUSERR&t;0x0010
DECL|macro|EXTIO_S0_STAT_1
mdefine_line|#define EXTIO_S0_STAT_1&t;&t;0x0008
DECL|macro|EXTIO_S0_STAT_0
mdefine_line|#define EXTIO_S0_STAT_0&t;&t;0x0004
DECL|macro|EXTIO_SG_STAT_1
mdefine_line|#define EXTIO_SG_STAT_1&t;&t;0x0002
DECL|macro|EXTIO_SG_STAT_0
mdefine_line|#define EXTIO_SG_STAT_0&t;&t;0x0001
)brace
suffix:semicolon
r_extern
r_struct
id|sgioc_regs
op_star
id|sgioc
suffix:semicolon
r_extern
r_struct
id|sgint_regs
op_star
id|sgint
suffix:semicolon
macro_line|#endif
eof
