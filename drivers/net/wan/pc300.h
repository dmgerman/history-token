multiline_comment|/*&n; * pc300.h&t;Cyclades-PC300(tm) Kernel API Definitions.&n; *&n; * Author:&t;Ivan Passos &lt;ivan@cyclades.com&gt;&n; *&n; * Copyright:&t;(c) 1999-2002 Cyclades Corp.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; * $Log: pc300.h,v $&n; * Revision 3.12  2002/03/07 14:17:09  henrique&n; * License data fixed&n; *&n; * Revision 3.11  2002/01/28 21:09:39  daniela&n; * Included &squot;;&squot; after pc300hw.bus.&n; *&n; * Revision 3.10  2002/01/17 17:58:52  ivan&n; * Support for PC300-TE/M (PMC).&n; *&n; * Revision 3.9  2001/09/28 13:30:53  daniela&n; * Renamed dma_start routine to rx_dma_start.&n; *&n; * Revision 3.8  2001/09/24 13:03:45  daniela&n; * Fixed BOF interrupt treatment. Created dma_start routine.&n; *&n; * Revision 3.7  2001/08/10 17:19:58  daniela&n; * Fixed IOCTLs defines.&n; *&n; * Revision 3.6  2001/07/18 19:24:42  daniela&n; * Included kernel version.&n; *&n; * Revision 3.5  2001/07/05 18:38:08  daniela&n; * DMA transmission bug fix.&n; *&n; * Revision 3.4  2001/06/26 17:10:40  daniela&n; * New configuration parameters (line code, CRC calculation and clock).&n; *&n; * Revision 3.3  2001/06/22 13:13:02  regina&n; * MLPPP implementation&n; *&n; * Revision 3.2  2001/06/18 17:56:09  daniela&n; * Increased DEF_MTU and TX_QUEUE_LEN.&n; *&n; * Revision 3.1  2001/06/15 12:41:10  regina&n; * upping major version number&n; *&n; * Revision 1.1.1.1  2001/06/13 20:25:06  daniela&n; * PC300 initial CVS version (3.4.0-pre1)&n; *&n; * Revision 2.3 2001/03/05 daniela&n; * Created struct pc300conf, to provide the hardware information to pc300util.&n; * Inclusion of &squot;alloc_ramsize&squot; field on structure &squot;pc300hw&squot;.&n; * &n; * Revision 2.2 2000/12/22 daniela&n; * Structures and defines to support pc300util: statistics, status, &n; * loopback tests, trace.&n; * &n; * Revision 2.1 2000/09/28 ivan&n; * Inclusion of &squot;iophys&squot; and &squot;iosize&squot; fields on structure &squot;pc300hw&squot;, to &n; * allow release of I/O region at module unload.&n; * Changed location of include files.&n; *&n; * Revision 2.0 2000/03/27 ivan&n; * Added support for the PC300/TE cards.&n; *&n; * Revision 1.1 2000/01/31 ivan&n; * Replaced &squot;pc300[drv|sca].h&squot; former PC300 driver include files.&n; *&n; * Revision 1.0 1999/12/16 ivan&n; * First official release.&n; * Inclusion of &squot;nchan&squot; field on structure &squot;pc300hw&squot;, to allow variable &n; * number of ports per card.&n; * Inclusion of &squot;if_ptr&squot; field on structure &squot;pc300dev&squot;.&n; *&n; * Revision 0.6 1999/11/17 ivan&n; * Changed X.25-specific function names to comply with adopted convention.&n; *&n; * Revision 0.5 1999/11/16 Daniela Squassoni&n; * X.25 support.&n; *&n; * Revision 0.4 1999/11/15 ivan&n; * Inclusion of &squot;clock&squot; field on structure &squot;pc300hw&squot;.&n; *&n; * Revision 0.3 1999/11/10 ivan&n; * IOCTL name changing.&n; * Inclusion of driver function prototypes.&n; *&n; * Revision 0.2 1999/11/03 ivan&n; * Inclusion of &squot;tx_skb&squot; and union &squot;ifu&squot; on structure &squot;pc300dev&squot;.&n; *&n; * Revision 0.1 1999/01/15 ivan&n; * Initial version.&n; *&n; */
macro_line|#ifndef&t;_PC300_H
DECL|macro|_PC300_H
mdefine_line|#define&t;_PC300_H
macro_line|#include &lt;linux/hdlc.h&gt;
macro_line|#include &quot;hd64572.h&quot;
macro_line|#include &quot;pc300-falc-lh.h&quot;
macro_line|#ifndef CY_TYPES
DECL|macro|CY_TYPES
mdefine_line|#define CY_TYPES
macro_line|#if defined(__alpha__)
DECL|typedef|ucdouble
r_typedef
r_int
r_int
id|ucdouble
suffix:semicolon
multiline_comment|/* 64 bits, unsigned */
DECL|typedef|uclong
r_typedef
r_int
r_int
id|uclong
suffix:semicolon
multiline_comment|/* 32 bits, unsigned */
macro_line|#else
DECL|typedef|uclong
r_typedef
r_int
r_int
id|uclong
suffix:semicolon
multiline_comment|/* 32 bits, unsigned */
macro_line|#endif
DECL|typedef|ucshort
r_typedef
r_int
r_int
id|ucshort
suffix:semicolon
multiline_comment|/* 16 bits, unsigned */
DECL|typedef|ucchar
r_typedef
r_int
r_char
id|ucchar
suffix:semicolon
multiline_comment|/* 8 bits, unsigned */
macro_line|#endif /* CY_TYPES */
DECL|macro|PC300_PROTO_MLPPP
mdefine_line|#define PC300_PROTO_MLPPP 1&t;&t;
DECL|macro|PC300_KERNEL
mdefine_line|#define PC300_KERNEL&t;&quot;2.4.x&quot;&t;/* Kernel supported by this driver */
DECL|macro|PC300_DEVNAME
mdefine_line|#define&t;PC300_DEVNAME&t;&quot;hdlc&quot;&t;/* Dev. name base (for hdlc0, hdlc1, etc.) */
DECL|macro|PC300_MAXINDEX
mdefine_line|#define PC300_MAXINDEX&t;100&t;/* Max dev. name index (the &squot;0&squot; in hdlc0) */
DECL|macro|PC300_MAXCARDS
mdefine_line|#define&t;PC300_MAXCARDS&t;4&t;/* Max number of cards per system */
DECL|macro|PC300_MAXCHAN
mdefine_line|#define&t;PC300_MAXCHAN&t;2&t;/* Number of channels per card */
DECL|macro|PC300_PLX_WIN
mdefine_line|#define&t;PC300_PLX_WIN&t;0x80    /* PLX control window size (128b) */
DECL|macro|PC300_RAMSIZE
mdefine_line|#define&t;PC300_RAMSIZE&t;0x40000 /* RAM window size (256Kb) */
DECL|macro|PC300_SCASIZE
mdefine_line|#define&t;PC300_SCASIZE&t;0x400   /* SCA window size (1Kb) */
DECL|macro|PC300_FALCSIZE
mdefine_line|#define&t;PC300_FALCSIZE&t;0x400&t;/* FALC window size (1Kb) */
DECL|macro|PC300_OSC_CLOCK
mdefine_line|#define PC300_OSC_CLOCK&t;24576000
DECL|macro|PC300_PCI_CLOCK
mdefine_line|#define PC300_PCI_CLOCK&t;33000000
DECL|macro|BD_DEF_LEN
mdefine_line|#define BD_DEF_LEN&t;0x0800&t;/* DMA buffer length (2KB) */
DECL|macro|DMA_TX_MEMSZ
mdefine_line|#define DMA_TX_MEMSZ&t;0x8000&t;/* Total DMA Tx memory size (32KB/ch) */
DECL|macro|DMA_RX_MEMSZ
mdefine_line|#define DMA_RX_MEMSZ&t;0x10000&t;/* Total DMA Rx memory size (64KB/ch) */
DECL|macro|N_DMA_TX_BUF
mdefine_line|#define N_DMA_TX_BUF&t;(DMA_TX_MEMSZ / BD_DEF_LEN)&t;/* DMA Tx buffers */
DECL|macro|N_DMA_RX_BUF
mdefine_line|#define N_DMA_RX_BUF&t;(DMA_RX_MEMSZ / BD_DEF_LEN)&t;/* DMA Rx buffers */
multiline_comment|/* DMA Buffer Offsets */
DECL|macro|DMA_TX_BASE
mdefine_line|#define DMA_TX_BASE&t;((N_DMA_TX_BUF + N_DMA_RX_BUF) *&t;&bslash;&n;&t;&t;&t; PC300_MAXCHAN * sizeof(pcsca_bd_t))
DECL|macro|DMA_RX_BASE
mdefine_line|#define DMA_RX_BASE&t;(DMA_TX_BASE + PC300_MAXCHAN*DMA_TX_MEMSZ)
multiline_comment|/* DMA Descriptor Offsets */
DECL|macro|DMA_TX_BD_BASE
mdefine_line|#define DMA_TX_BD_BASE&t;0x0000
DECL|macro|DMA_RX_BD_BASE
mdefine_line|#define DMA_RX_BD_BASE&t;(DMA_TX_BD_BASE + ((PC300_MAXCHAN*DMA_TX_MEMSZ / &bslash;&n;&t;&t;&t;&t;BD_DEF_LEN) * sizeof(pcsca_bd_t)))
multiline_comment|/* DMA Descriptor Macros */
DECL|macro|TX_BD_ADDR
mdefine_line|#define TX_BD_ADDR(chan, n)&t;(DMA_TX_BD_BASE + &bslash;&n;&t;&t;&t;&t; ((N_DMA_TX_BUF*chan) + n) * sizeof(pcsca_bd_t))
DECL|macro|RX_BD_ADDR
mdefine_line|#define RX_BD_ADDR(chan, n)&t;(DMA_RX_BD_BASE + &bslash;&n;&t;&t;&t;&t; ((N_DMA_RX_BUF*chan) + n) * sizeof(pcsca_bd_t))
multiline_comment|/* Macro to access the FALC registers (TE only) */
DECL|macro|F_REG
mdefine_line|#define F_REG(reg, chan)&t;(0x200*(chan) + ((reg)&lt;&lt;2))
multiline_comment|/***************************************&n; * Memory access functions/macros      *&n; * (required to support Alpha systems) *&n; ***************************************/
macro_line|#ifdef __KERNEL__
DECL|macro|cpc_writeb
mdefine_line|#define cpc_writeb(port,val)&t;{writeb((ucchar)(val),(ulong)(port)); mb();}
DECL|macro|cpc_writew
mdefine_line|#define cpc_writew(port,val)&t;{writew((ushort)(val),(ulong)(port)); mb();}
DECL|macro|cpc_writel
mdefine_line|#define cpc_writel(port,val)&t;{writel((uclong)(val),(ulong)(port)); mb();}
DECL|macro|cpc_readb
mdefine_line|#define cpc_readb(port)&t;&t;readb(port)
DECL|macro|cpc_readw
mdefine_line|#define cpc_readw(port)&t;&t;readw(port)
DECL|macro|cpc_readl
mdefine_line|#define cpc_readl(port)&t;&t;readl(port)
macro_line|#else /* __KERNEL__ */
DECL|macro|cpc_writeb
mdefine_line|#define cpc_writeb(port,val)&t;(*(volatile ucchar *)(port) = (ucchar)(val))
DECL|macro|cpc_writew
mdefine_line|#define cpc_writew(port,val)&t;(*(volatile ucshort *)(port) = (ucshort)(val))
DECL|macro|cpc_writel
mdefine_line|#define cpc_writel(port,val)&t;(*(volatile uclong *)(port) = (uclong)(val))
DECL|macro|cpc_readb
mdefine_line|#define cpc_readb(port)&t;&t;(*(volatile ucchar *)(port))
DECL|macro|cpc_readw
mdefine_line|#define cpc_readw(port)&t;&t;(*(volatile ucshort *)(port))
DECL|macro|cpc_readl
mdefine_line|#define cpc_readl(port)&t;&t;(*(volatile uclong *)(port))
macro_line|#endif /* __KERNEL__ */
multiline_comment|/****** Data Structures *****************************************************/
multiline_comment|/*&n; *      RUNTIME_9050 - PLX PCI9050-1 local configuration and shared runtime&n; *      registers. This structure can be used to access the 9050 registers&n; *      (memory mapped).&n; */
DECL|struct|RUNTIME_9050
r_struct
id|RUNTIME_9050
(brace
DECL|member|loc_addr_range
id|uclong
id|loc_addr_range
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 00-0Ch : Local Address Ranges */
DECL|member|loc_rom_range
id|uclong
id|loc_rom_range
suffix:semicolon
multiline_comment|/* 10h : Local ROM Range */
DECL|member|loc_addr_base
id|uclong
id|loc_addr_base
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 14-20h : Local Address Base Addrs */
DECL|member|loc_rom_base
id|uclong
id|loc_rom_base
suffix:semicolon
multiline_comment|/* 24h : Local ROM Base */
DECL|member|loc_bus_descr
id|uclong
id|loc_bus_descr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 28-34h : Local Bus Descriptors */
DECL|member|rom_bus_descr
id|uclong
id|rom_bus_descr
suffix:semicolon
multiline_comment|/* 38h : ROM Bus Descriptor */
DECL|member|cs_base
id|uclong
id|cs_base
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 3C-48h : Chip Select Base Addrs */
DECL|member|intr_ctrl_stat
id|uclong
id|intr_ctrl_stat
suffix:semicolon
multiline_comment|/* 4Ch : Interrupt Control/Status */
DECL|member|init_ctrl
id|uclong
id|init_ctrl
suffix:semicolon
multiline_comment|/* 50h : EEPROM ctrl, Init Ctrl, etc */
)brace
suffix:semicolon
DECL|macro|PLX_9050_LINT1_ENABLE
mdefine_line|#define PLX_9050_LINT1_ENABLE&t;0x01
DECL|macro|PLX_9050_LINT1_POL
mdefine_line|#define PLX_9050_LINT1_POL&t;0x02
DECL|macro|PLX_9050_LINT1_STATUS
mdefine_line|#define PLX_9050_LINT1_STATUS&t;0x04
DECL|macro|PLX_9050_LINT2_ENABLE
mdefine_line|#define PLX_9050_LINT2_ENABLE&t;0x08
DECL|macro|PLX_9050_LINT2_POL
mdefine_line|#define PLX_9050_LINT2_POL&t;0x10
DECL|macro|PLX_9050_LINT2_STATUS
mdefine_line|#define PLX_9050_LINT2_STATUS&t;0x20
DECL|macro|PLX_9050_INTR_ENABLE
mdefine_line|#define PLX_9050_INTR_ENABLE&t;0x40
DECL|macro|PLX_9050_SW_INTR
mdefine_line|#define PLX_9050_SW_INTR&t;0x80
multiline_comment|/* Masks to access the init_ctrl PLX register */
DECL|macro|PC300_CLKSEL_MASK
mdefine_line|#define&t;PC300_CLKSEL_MASK&t;&t;(0x00000004UL)
DECL|macro|PC300_CHMEDIA_MASK
mdefine_line|#define&t;PC300_CHMEDIA_MASK(chan)&t;(0x00000020UL&lt;&lt;(chan*3))
DECL|macro|PC300_CTYPE_MASK
mdefine_line|#define&t;PC300_CTYPE_MASK&t;&t;(0x00000800UL)
multiline_comment|/* CPLD Registers (base addr = falcbase, TE only) */
multiline_comment|/* CPLD v. 0 */
DECL|macro|CPLD_REG1
mdefine_line|#define CPLD_REG1&t;0x140&t;/* Chip resets, DCD/CTS status */
DECL|macro|CPLD_REG2
mdefine_line|#define CPLD_REG2&t;0x144&t;/* Clock enable , LED control */
multiline_comment|/* CPLD v. 2 or higher */
DECL|macro|CPLD_V2_REG1
mdefine_line|#define CPLD_V2_REG1&t;0x100&t;/* Chip resets, DCD/CTS status */
DECL|macro|CPLD_V2_REG2
mdefine_line|#define CPLD_V2_REG2&t;0x104&t;/* Clock enable , LED control */
DECL|macro|CPLD_ID_REG
mdefine_line|#define CPLD_ID_REG&t;0x108&t;/* CPLD version */
multiline_comment|/* CPLD Register bit description: for the FALC bits, they should always be &n;   set based on the channel (use (bit&lt;&lt;(2*ch)) to access the correct bit for &n;   that channel) */
DECL|macro|CPLD_REG1_FALC_RESET
mdefine_line|#define CPLD_REG1_FALC_RESET&t;0x01
DECL|macro|CPLD_REG1_SCA_RESET
mdefine_line|#define CPLD_REG1_SCA_RESET&t;0x02
DECL|macro|CPLD_REG1_GLOBAL_CLK
mdefine_line|#define CPLD_REG1_GLOBAL_CLK&t;0x08
DECL|macro|CPLD_REG1_FALC_DCD
mdefine_line|#define CPLD_REG1_FALC_DCD&t;0x10
DECL|macro|CPLD_REG1_FALC_CTS
mdefine_line|#define CPLD_REG1_FALC_CTS&t;0x20
DECL|macro|CPLD_REG2_FALC_TX_CLK
mdefine_line|#define CPLD_REG2_FALC_TX_CLK&t;0x01
DECL|macro|CPLD_REG2_FALC_RX_CLK
mdefine_line|#define CPLD_REG2_FALC_RX_CLK&t;0x02
DECL|macro|CPLD_REG2_FALC_LED1
mdefine_line|#define CPLD_REG2_FALC_LED1&t;0x10
DECL|macro|CPLD_REG2_FALC_LED2
mdefine_line|#define CPLD_REG2_FALC_LED2&t;0x20
multiline_comment|/* Structure with FALC-related fields (TE only) */
DECL|macro|PC300_FALC_MAXLOOP
mdefine_line|#define PC300_FALC_MAXLOOP&t;0x0000ffff&t;/* for falc_issue_cmd() */
DECL|struct|falc
r_typedef
r_struct
id|falc
(brace
DECL|member|sync
id|ucchar
id|sync
suffix:semicolon
multiline_comment|/* If true FALC is synchronized */
DECL|member|active
id|ucchar
id|active
suffix:semicolon
multiline_comment|/* if TRUE then already active */
DECL|member|loop_active
id|ucchar
id|loop_active
suffix:semicolon
multiline_comment|/* if TRUE a line loopback UP was received */
DECL|member|loop_gen
id|ucchar
id|loop_gen
suffix:semicolon
multiline_comment|/* if TRUE a line loopback UP was issued */
DECL|member|num_channels
id|ucchar
id|num_channels
suffix:semicolon
DECL|member|offset
id|ucchar
id|offset
suffix:semicolon
multiline_comment|/* 1 for T1, 0 for E1 */
DECL|member|full_bandwidth
id|ucchar
id|full_bandwidth
suffix:semicolon
DECL|member|xmb_cause
id|ucchar
id|xmb_cause
suffix:semicolon
DECL|member|multiframe_mode
id|ucchar
id|multiframe_mode
suffix:semicolon
multiline_comment|/* Statistics */
DECL|member|pden
id|ucshort
id|pden
suffix:semicolon
multiline_comment|/* Pulse Density violation count */
DECL|member|los
id|ucshort
id|los
suffix:semicolon
multiline_comment|/* Loss of Signal count */
DECL|member|losr
id|ucshort
id|losr
suffix:semicolon
multiline_comment|/* Loss of Signal recovery count */
DECL|member|lfa
id|ucshort
id|lfa
suffix:semicolon
multiline_comment|/* Loss of frame alignment count */
DECL|member|farec
id|ucshort
id|farec
suffix:semicolon
multiline_comment|/* Frame Alignment Recovery count */
DECL|member|lmfa
id|ucshort
id|lmfa
suffix:semicolon
multiline_comment|/* Loss of multiframe alignment count */
DECL|member|ais
id|ucshort
id|ais
suffix:semicolon
multiline_comment|/* Remote Alarm indication Signal count */
DECL|member|sec
id|ucshort
id|sec
suffix:semicolon
multiline_comment|/* One-second timer */
DECL|member|es
id|ucshort
id|es
suffix:semicolon
multiline_comment|/* Errored second */
DECL|member|rai
id|ucshort
id|rai
suffix:semicolon
multiline_comment|/* remote alarm received */
DECL|member|bec
id|ucshort
id|bec
suffix:semicolon
DECL|member|fec
id|ucshort
id|fec
suffix:semicolon
DECL|member|cvc
id|ucshort
id|cvc
suffix:semicolon
DECL|member|cec
id|ucshort
id|cec
suffix:semicolon
DECL|member|ebc
id|ucshort
id|ebc
suffix:semicolon
multiline_comment|/* Status */
DECL|member|red_alarm
id|ucchar
id|red_alarm
suffix:semicolon
DECL|member|blue_alarm
id|ucchar
id|blue_alarm
suffix:semicolon
DECL|member|loss_fa
id|ucchar
id|loss_fa
suffix:semicolon
DECL|member|yellow_alarm
id|ucchar
id|yellow_alarm
suffix:semicolon
DECL|member|loss_mfa
id|ucchar
id|loss_mfa
suffix:semicolon
DECL|member|prbs
id|ucchar
id|prbs
suffix:semicolon
DECL|typedef|falc_t
)brace
id|falc_t
suffix:semicolon
DECL|struct|falc_status
r_typedef
r_struct
id|falc_status
(brace
DECL|member|sync
id|ucchar
id|sync
suffix:semicolon
multiline_comment|/* If true FALC is synchronized */
DECL|member|red_alarm
id|ucchar
id|red_alarm
suffix:semicolon
DECL|member|blue_alarm
id|ucchar
id|blue_alarm
suffix:semicolon
DECL|member|loss_fa
id|ucchar
id|loss_fa
suffix:semicolon
DECL|member|yellow_alarm
id|ucchar
id|yellow_alarm
suffix:semicolon
DECL|member|loss_mfa
id|ucchar
id|loss_mfa
suffix:semicolon
DECL|member|prbs
id|ucchar
id|prbs
suffix:semicolon
DECL|typedef|falc_status_t
)brace
id|falc_status_t
suffix:semicolon
DECL|struct|rsv_x21_status
r_typedef
r_struct
id|rsv_x21_status
(brace
DECL|member|dcd
id|ucchar
id|dcd
suffix:semicolon
DECL|member|dsr
id|ucchar
id|dsr
suffix:semicolon
DECL|member|cts
id|ucchar
id|cts
suffix:semicolon
DECL|member|rts
id|ucchar
id|rts
suffix:semicolon
DECL|member|dtr
id|ucchar
id|dtr
suffix:semicolon
DECL|typedef|rsv_x21_status_t
)brace
id|rsv_x21_status_t
suffix:semicolon
DECL|struct|pc300stats
r_typedef
r_struct
id|pc300stats
(brace
DECL|member|hw_type
r_int
id|hw_type
suffix:semicolon
DECL|member|line_on
id|uclong
id|line_on
suffix:semicolon
DECL|member|line_off
id|uclong
id|line_off
suffix:semicolon
DECL|member|gen_stats
r_struct
id|net_device_stats
id|gen_stats
suffix:semicolon
DECL|member|te_stats
id|falc_t
id|te_stats
suffix:semicolon
DECL|typedef|pc300stats_t
)brace
id|pc300stats_t
suffix:semicolon
DECL|struct|pc300status
r_typedef
r_struct
id|pc300status
(brace
DECL|member|hw_type
r_int
id|hw_type
suffix:semicolon
DECL|member|gen_status
id|rsv_x21_status_t
id|gen_status
suffix:semicolon
DECL|member|te_status
id|falc_status_t
id|te_status
suffix:semicolon
DECL|typedef|pc300status_t
)brace
id|pc300status_t
suffix:semicolon
DECL|struct|pc300loopback
r_typedef
r_struct
id|pc300loopback
(brace
DECL|member|loop_type
r_char
id|loop_type
suffix:semicolon
DECL|member|loop_on
r_char
id|loop_on
suffix:semicolon
DECL|typedef|pc300loopback_t
)brace
id|pc300loopback_t
suffix:semicolon
DECL|struct|pc300patterntst
r_typedef
r_struct
id|pc300patterntst
(brace
DECL|member|patrntst_on
r_char
id|patrntst_on
suffix:semicolon
multiline_comment|/* 0 - off; 1 - on; 2 - read num_errors */
DECL|member|num_errors
id|ucshort
id|num_errors
suffix:semicolon
DECL|typedef|pc300patterntst_t
)brace
id|pc300patterntst_t
suffix:semicolon
DECL|struct|pc300dev
r_typedef
r_struct
id|pc300dev
(brace
DECL|member|if_ptr
r_void
op_star
id|if_ptr
suffix:semicolon
multiline_comment|/* General purpose pointer */
DECL|member|chan
r_struct
id|pc300ch
op_star
id|chan
suffix:semicolon
DECL|member|trace_on
id|ucchar
id|trace_on
suffix:semicolon
DECL|member|line_on
id|uclong
id|line_on
suffix:semicolon
multiline_comment|/* DCD(X.21, RSV) / sync(TE) change counters */
DECL|member|line_off
id|uclong
id|line_off
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|hdlc
id|hdlc_device
op_star
id|hdlc
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
r_union
(brace
multiline_comment|/* This union has all the protocol-specific structures */
DECL|member|pppdev
r_struct
id|ppp_device
id|pppdev
suffix:semicolon
DECL|member|ifu
)brace
id|ifu
suffix:semicolon
macro_line|#ifdef CONFIG_PC300_MLPPP
DECL|member|cpc_tty
r_void
op_star
id|cpc_tty
suffix:semicolon
multiline_comment|/* information to PC300 TTY driver */
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
DECL|typedef|pc300dev_t
)brace
id|pc300dev_t
suffix:semicolon
DECL|struct|pc300hw
r_typedef
r_struct
id|pc300hw
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* RSV, X21, etc. */
DECL|member|bus
r_int
id|bus
suffix:semicolon
multiline_comment|/* Bus (PCI, PMC, etc.) */
DECL|member|nchan
r_int
id|nchan
suffix:semicolon
multiline_comment|/* number of channels */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt request level */
DECL|member|clock
id|uclong
id|clock
suffix:semicolon
multiline_comment|/* Board clock */
DECL|member|cpld_id
id|ucchar
id|cpld_id
suffix:semicolon
multiline_comment|/* CPLD ID (TE only) */
DECL|member|cpld_reg1
id|ucshort
id|cpld_reg1
suffix:semicolon
multiline_comment|/* CPLD reg 1 (TE only) */
DECL|member|cpld_reg2
id|ucshort
id|cpld_reg2
suffix:semicolon
multiline_comment|/* CPLD reg 2 (TE only) */
DECL|member|gpioc_reg
id|ucshort
id|gpioc_reg
suffix:semicolon
multiline_comment|/* PLX GPIOC reg */
DECL|member|intctl_reg
id|ucshort
id|intctl_reg
suffix:semicolon
multiline_comment|/* PLX Int Ctrl/Status reg */
DECL|member|iophys
id|uclong
id|iophys
suffix:semicolon
multiline_comment|/* PLX registers I/O base */
DECL|member|iosize
id|uclong
id|iosize
suffix:semicolon
multiline_comment|/* PLX registers I/O size */
DECL|member|plxphys
id|uclong
id|plxphys
suffix:semicolon
multiline_comment|/* PLX registers MMIO base (physical) */
DECL|member|plxbase
id|uclong
id|plxbase
suffix:semicolon
multiline_comment|/* PLX registers MMIO base (virtual) */
DECL|member|plxsize
id|uclong
id|plxsize
suffix:semicolon
multiline_comment|/* PLX registers MMIO size */
DECL|member|scaphys
id|uclong
id|scaphys
suffix:semicolon
multiline_comment|/* SCA registers MMIO base (physical) */
DECL|member|scabase
id|uclong
id|scabase
suffix:semicolon
multiline_comment|/* SCA registers MMIO base (virtual) */
DECL|member|scasize
id|uclong
id|scasize
suffix:semicolon
multiline_comment|/* SCA registers MMIO size */
DECL|member|ramphys
id|uclong
id|ramphys
suffix:semicolon
multiline_comment|/* On-board RAM MMIO base (physical) */
DECL|member|rambase
id|uclong
id|rambase
suffix:semicolon
multiline_comment|/* On-board RAM MMIO base (virtual) */
DECL|member|alloc_ramsize
id|uclong
id|alloc_ramsize
suffix:semicolon
multiline_comment|/* RAM MMIO size allocated by the PCI bridge */
DECL|member|ramsize
id|uclong
id|ramsize
suffix:semicolon
multiline_comment|/* On-board RAM MMIO size */
DECL|member|falcphys
id|uclong
id|falcphys
suffix:semicolon
multiline_comment|/* FALC registers MMIO base (physical) */
DECL|member|falcbase
id|uclong
id|falcbase
suffix:semicolon
multiline_comment|/* FALC registers MMIO base (virtual) */
DECL|member|falcsize
id|uclong
id|falcsize
suffix:semicolon
multiline_comment|/* FALC registers MMIO size */
DECL|typedef|pc300hw_t
)brace
id|pc300hw_t
suffix:semicolon
DECL|struct|pc300chconf
r_typedef
r_struct
id|pc300chconf
(brace
DECL|member|phys_settings
id|sync_serial_settings
id|phys_settings
suffix:semicolon
multiline_comment|/* Clock type/rate (in bps), &n;&t;&t;&t;&t;&t;&t;   loopback mode */
DECL|member|proto_settings
id|raw_hdlc_proto
id|proto_settings
suffix:semicolon
multiline_comment|/* Encoding, parity (CRC) */
DECL|member|media
id|uclong
id|media
suffix:semicolon
multiline_comment|/* HW media (RS232, V.35, etc.) */
DECL|member|proto
id|uclong
id|proto
suffix:semicolon
multiline_comment|/* Protocol (PPP, X.25, etc.) */
DECL|member|monitor
id|ucchar
id|monitor
suffix:semicolon
multiline_comment|/* Monitor mode (0 = off, !0 = on) */
multiline_comment|/* TE-specific parameters */
DECL|member|lcode
id|ucchar
id|lcode
suffix:semicolon
multiline_comment|/* Line Code (AMI, B8ZS, etc.) */
DECL|member|fr_mode
id|ucchar
id|fr_mode
suffix:semicolon
multiline_comment|/* Frame Mode (ESF, D4, etc.) */
DECL|member|lbo
id|ucchar
id|lbo
suffix:semicolon
multiline_comment|/* Line Build Out */
DECL|member|rx_sens
id|ucchar
id|rx_sens
suffix:semicolon
multiline_comment|/* Rx Sensitivity (long- or short-haul) */
DECL|member|tslot_bitmap
id|uclong
id|tslot_bitmap
suffix:semicolon
multiline_comment|/* bit[i]=1  =&gt;  timeslot _i_ is active */
DECL|typedef|pc300chconf_t
)brace
id|pc300chconf_t
suffix:semicolon
DECL|struct|pc300ch
r_typedef
r_struct
id|pc300ch
(brace
DECL|member|card
r_struct
id|pc300
op_star
id|card
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|d
id|pc300dev_t
id|d
suffix:semicolon
DECL|member|conf
id|pc300chconf_t
id|conf
suffix:semicolon
DECL|member|tx_first_bd
id|ucchar
id|tx_first_bd
suffix:semicolon
multiline_comment|/* First TX DMA block descr. w/ data */
DECL|member|tx_next_bd
id|ucchar
id|tx_next_bd
suffix:semicolon
multiline_comment|/* Next free TX DMA block descriptor */
DECL|member|rx_first_bd
id|ucchar
id|rx_first_bd
suffix:semicolon
multiline_comment|/* First free RX DMA block descriptor */
DECL|member|rx_last_bd
id|ucchar
id|rx_last_bd
suffix:semicolon
multiline_comment|/* Last free RX DMA block descriptor */
DECL|member|nfree_tx_bd
id|ucchar
id|nfree_tx_bd
suffix:semicolon
multiline_comment|/* Number of free TX DMA block descriptors */
DECL|member|falc
id|falc_t
id|falc
suffix:semicolon
multiline_comment|/* FALC structure (TE only) */
DECL|typedef|pc300ch_t
)brace
id|pc300ch_t
suffix:semicolon
DECL|struct|pc300
r_typedef
r_struct
id|pc300
(brace
DECL|member|hw
id|pc300hw_t
id|hw
suffix:semicolon
multiline_comment|/* hardware config. */
DECL|member|chan
id|pc300ch_t
id|chan
(braket
id|PC300_MAXCHAN
)braket
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|member|card_lock
id|spinlock_t
id|card_lock
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
DECL|typedef|pc300_t
)brace
id|pc300_t
suffix:semicolon
DECL|struct|pc300conf
r_typedef
r_struct
id|pc300conf
(brace
DECL|member|hw
id|pc300hw_t
id|hw
suffix:semicolon
DECL|member|conf
id|pc300chconf_t
id|conf
suffix:semicolon
DECL|typedef|pc300conf_t
)brace
id|pc300conf_t
suffix:semicolon
multiline_comment|/* DEV ioctl() commands */
DECL|macro|N_SPPP_IOCTLS
mdefine_line|#define&t;N_SPPP_IOCTLS&t;2
DECL|enum|pc300_ioctl_cmds
r_enum
id|pc300_ioctl_cmds
(brace
DECL|enumerator|SIOCCPCRESERVED
id|SIOCCPCRESERVED
op_assign
(paren
id|SIOCDEVPRIVATE
op_plus
id|N_SPPP_IOCTLS
)paren
comma
DECL|enumerator|SIOCGPC300CONF
id|SIOCGPC300CONF
comma
DECL|enumerator|SIOCSPC300CONF
id|SIOCSPC300CONF
comma
DECL|enumerator|SIOCGPC300STATUS
id|SIOCGPC300STATUS
comma
DECL|enumerator|SIOCGPC300FALCSTATUS
id|SIOCGPC300FALCSTATUS
comma
DECL|enumerator|SIOCGPC300UTILSTATS
id|SIOCGPC300UTILSTATS
comma
DECL|enumerator|SIOCGPC300UTILSTATUS
id|SIOCGPC300UTILSTATUS
comma
DECL|enumerator|SIOCSPC300TRACE
id|SIOCSPC300TRACE
comma
DECL|enumerator|SIOCSPC300LOOPBACK
id|SIOCSPC300LOOPBACK
comma
DECL|enumerator|SIOCSPC300PATTERNTEST
id|SIOCSPC300PATTERNTEST
comma
)brace
suffix:semicolon
multiline_comment|/* Loopback types - PC300/TE boards */
DECL|enum|pc300_loopback_cmds
r_enum
id|pc300_loopback_cmds
(brace
DECL|enumerator|PC300LOCLOOP
id|PC300LOCLOOP
op_assign
l_int|1
comma
DECL|enumerator|PC300REMLOOP
id|PC300REMLOOP
comma
DECL|enumerator|PC300PAYLOADLOOP
id|PC300PAYLOADLOOP
comma
DECL|enumerator|PC300GENLOOPUP
id|PC300GENLOOPUP
comma
DECL|enumerator|PC300GENLOOPDOWN
id|PC300GENLOOPDOWN
comma
)brace
suffix:semicolon
multiline_comment|/* Control Constant Definitions */
DECL|macro|PC300_RSV
mdefine_line|#define&t;PC300_RSV&t;0x01
DECL|macro|PC300_X21
mdefine_line|#define&t;PC300_X21&t;0x02
DECL|macro|PC300_TE
mdefine_line|#define&t;PC300_TE&t;0x03
DECL|macro|PC300_PCI
mdefine_line|#define&t;PC300_PCI&t;0x00
DECL|macro|PC300_PMC
mdefine_line|#define&t;PC300_PMC&t;0x01
DECL|macro|PC300_LC_AMI
mdefine_line|#define PC300_LC_AMI&t;0x01
DECL|macro|PC300_LC_B8ZS
mdefine_line|#define PC300_LC_B8ZS&t;0x02
DECL|macro|PC300_LC_NRZ
mdefine_line|#define PC300_LC_NRZ&t;0x03
DECL|macro|PC300_LC_HDB3
mdefine_line|#define PC300_LC_HDB3&t;0x04
multiline_comment|/* Framing (T1) */
DECL|macro|PC300_FR_ESF
mdefine_line|#define PC300_FR_ESF&t;&t;0x01
DECL|macro|PC300_FR_D4
mdefine_line|#define PC300_FR_D4&t;&t;0x02
DECL|macro|PC300_FR_ESF_JAPAN
mdefine_line|#define PC300_FR_ESF_JAPAN&t;0x03
multiline_comment|/* Framing (E1) */
DECL|macro|PC300_FR_MF_CRC4
mdefine_line|#define PC300_FR_MF_CRC4&t;0x04
DECL|macro|PC300_FR_MF_NON_CRC4
mdefine_line|#define PC300_FR_MF_NON_CRC4&t;0x05
DECL|macro|PC300_FR_UNFRAMED
mdefine_line|#define PC300_FR_UNFRAMED&t;0x06
DECL|macro|PC300_LBO_0_DB
mdefine_line|#define PC300_LBO_0_DB&t;&t;0x00
DECL|macro|PC300_LBO_7_5_DB
mdefine_line|#define PC300_LBO_7_5_DB&t;0x01
DECL|macro|PC300_LBO_15_DB
mdefine_line|#define PC300_LBO_15_DB&t;&t;0x02
DECL|macro|PC300_LBO_22_5_DB
mdefine_line|#define PC300_LBO_22_5_DB&t;0x03
DECL|macro|PC300_RX_SENS_SH
mdefine_line|#define PC300_RX_SENS_SH&t;0x01
DECL|macro|PC300_RX_SENS_LH
mdefine_line|#define PC300_RX_SENS_LH&t;0x02
DECL|macro|PC300_TX_TIMEOUT
mdefine_line|#define PC300_TX_TIMEOUT&t;(2*HZ)
DECL|macro|PC300_TX_QUEUE_LEN
mdefine_line|#define PC300_TX_QUEUE_LEN&t;100
DECL|macro|PC300_DEF_MTU
mdefine_line|#define&t;PC300_DEF_MTU&t;&t;1600
macro_line|#ifdef __KERNEL__
multiline_comment|/* Function Prototypes */
r_int
id|dma_buf_write
c_func
(paren
id|pc300_t
op_star
comma
r_int
comma
id|ucchar
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|dma_buf_read
c_func
(paren
id|pc300_t
op_star
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|tx_dma_start
c_func
(paren
id|pc300_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|rx_dma_start
c_func
(paren
id|pc300_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|tx_dma_stop
c_func
(paren
id|pc300_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|rx_dma_stop
c_func
(paren
id|pc300_t
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|cpc_queue_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_void
id|cpc_net_rx
c_func
(paren
id|hdlc_device
op_star
)paren
suffix:semicolon
r_void
id|cpc_sca_status
c_func
(paren
id|pc300_t
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|cpc_change_mtu
c_func
(paren
r_struct
id|net_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|cpc_ioctl
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|ifreq
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|ch_config
c_func
(paren
id|pc300dev_t
op_star
)paren
suffix:semicolon
r_int
id|rx_config
c_func
(paren
id|pc300dev_t
op_star
)paren
suffix:semicolon
r_int
id|tx_config
c_func
(paren
id|pc300dev_t
op_star
)paren
suffix:semicolon
r_void
id|cpc_opench
c_func
(paren
id|pc300dev_t
op_star
)paren
suffix:semicolon
r_void
id|cpc_closech
c_func
(paren
id|pc300dev_t
op_star
)paren
suffix:semicolon
r_int
id|cpc_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|cpc_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|cpc_set_media
c_func
(paren
id|hdlc_device
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* _PC300_H */
eof
