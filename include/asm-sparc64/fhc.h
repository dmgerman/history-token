multiline_comment|/* $Id: fhc.h,v 1.5 1999/09/21 14:39:29 davem Exp $&n; * fhc.h: Structures for central/fhc pseudo driver on Sunfire/Starfire/Wildfire.&n; *&n; * Copyright (C) 1997, 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef _SPARC64_FHC_H
DECL|macro|_SPARC64_FHC_H
mdefine_line|#define _SPARC64_FHC_H
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/upa.h&gt;
r_struct
id|linux_fhc
suffix:semicolon
multiline_comment|/* Clock board register offsets. */
DECL|macro|CLOCK_CTRL
mdefine_line|#define CLOCK_CTRL&t;0x00UL&t;/* Main control */
DECL|macro|CLOCK_STAT1
mdefine_line|#define CLOCK_STAT1&t;0x10UL&t;/* Status one */
DECL|macro|CLOCK_STAT2
mdefine_line|#define CLOCK_STAT2&t;0x20UL&t;/* Status two */
DECL|macro|CLOCK_PWRSTAT
mdefine_line|#define CLOCK_PWRSTAT&t;0x30UL&t;/* Power status */
DECL|macro|CLOCK_PWRPRES
mdefine_line|#define CLOCK_PWRPRES&t;0x40UL&t;/* Power presence */
DECL|macro|CLOCK_TEMP
mdefine_line|#define CLOCK_TEMP&t;0x50UL&t;/* Temperature */
DECL|macro|CLOCK_IRQDIAG
mdefine_line|#define CLOCK_IRQDIAG&t;0x60UL&t;/* IRQ diagnostics */
DECL|macro|CLOCK_PWRSTAT2
mdefine_line|#define CLOCK_PWRSTAT2&t;0x70UL&t;/* Power status two */
DECL|macro|CLOCK_CTRL_LLED
mdefine_line|#define CLOCK_CTRL_LLED&t;&t;0x04&t;/* Left LED, 0 == on */
DECL|macro|CLOCK_CTRL_MLED
mdefine_line|#define CLOCK_CTRL_MLED&t;&t;0x02&t;/* Mid LED, 1 == on */
DECL|macro|CLOCK_CTRL_RLED
mdefine_line|#define CLOCK_CTRL_RLED&t;&t;0x01&t;/* RIght LED, 1 == on */
DECL|struct|linux_central
r_struct
id|linux_central
(brace
DECL|member|child
r_struct
id|linux_fhc
op_star
id|child
suffix:semicolon
DECL|member|cfreg
r_int
r_int
id|cfreg
suffix:semicolon
DECL|member|clkregs
r_int
r_int
id|clkregs
suffix:semicolon
DECL|member|clkver
r_int
r_int
id|clkver
suffix:semicolon
DECL|member|slots
r_int
id|slots
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|central_ranges
r_struct
id|linux_prom_ranges
id|central_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_central_ranges
r_int
id|num_central_ranges
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Firehose controller register offsets */
DECL|struct|fhc_regs
r_struct
id|fhc_regs
(brace
DECL|member|pregs
r_int
r_int
id|pregs
suffix:semicolon
multiline_comment|/* FHC internal regs */
DECL|macro|FHC_PREGS_ID
mdefine_line|#define FHC_PREGS_ID&t;0x00UL&t;/* FHC ID */
DECL|macro|FHC_ID_VERS
mdefine_line|#define  FHC_ID_VERS&t;&t;0xf0000000 /* Version of this FHC&t;&t;*/
DECL|macro|FHC_ID_PARTID
mdefine_line|#define  FHC_ID_PARTID&t;&t;0x0ffff000 /* Part ID code (0x0f9f == FHC)&t;*/
DECL|macro|FHC_ID_MANUF
mdefine_line|#define  FHC_ID_MANUF&t;&t;0x0000007e /* Manufacturer (0x3e == SUN&squot;s JEDEC)*/
DECL|macro|FHC_ID_RESV
mdefine_line|#define  FHC_ID_RESV&t;&t;0x00000001 /* Read as one&t;&t;&t;*/
DECL|macro|FHC_PREGS_RCS
mdefine_line|#define FHC_PREGS_RCS&t;0x10UL&t;/* FHC Reset Control/Status Register */
DECL|macro|FHC_RCS_POR
mdefine_line|#define  FHC_RCS_POR&t;&t;0x80000000 /* Last reset was a power cycle&t;*/
DECL|macro|FHC_RCS_SPOR
mdefine_line|#define  FHC_RCS_SPOR&t;&t;0x40000000 /* Last reset was sw power on reset&t;*/
DECL|macro|FHC_RCS_SXIR
mdefine_line|#define  FHC_RCS_SXIR&t;&t;0x20000000 /* Last reset was sw XIR reset&t;*/
DECL|macro|FHC_RCS_BPOR
mdefine_line|#define  FHC_RCS_BPOR&t;&t;0x10000000 /* Last reset was due to POR button&t;*/
DECL|macro|FHC_RCS_BXIR
mdefine_line|#define  FHC_RCS_BXIR&t;&t;0x08000000 /* Last reset was due to XIR button&t;*/
DECL|macro|FHC_RCS_WEVENT
mdefine_line|#define  FHC_RCS_WEVENT&t;&t;0x04000000 /* CPU reset was due to wakeup event&t;*/
DECL|macro|FHC_RCS_CFATAL
mdefine_line|#define  FHC_RCS_CFATAL&t;&t;0x02000000 /* Centerplane Fatal Error signalled&t;*/
DECL|macro|FHC_RCS_FENAB
mdefine_line|#define  FHC_RCS_FENAB&t;&t;0x01000000 /* Fatal errors elicit system reset&t;*/
DECL|macro|FHC_PREGS_CTRL
mdefine_line|#define FHC_PREGS_CTRL&t;0x20UL&t;/* FHC Control Register */
DECL|macro|FHC_CONTROL_ICS
mdefine_line|#define  FHC_CONTROL_ICS&t;0x00100000 /* Ignore Centerplane Signals&t;*/
DECL|macro|FHC_CONTROL_FRST
mdefine_line|#define  FHC_CONTROL_FRST&t;0x00080000 /* Fatal Error Reset Enable&t;&t;*/
DECL|macro|FHC_CONTROL_LFAT
mdefine_line|#define  FHC_CONTROL_LFAT&t;0x00040000 /* AC/DC signalled a local error&t;*/
DECL|macro|FHC_CONTROL_SLINE
mdefine_line|#define  FHC_CONTROL_SLINE&t;0x00010000 /* Firmware Synchronization Line&t;*/
DECL|macro|FHC_CONTROL_DCD
mdefine_line|#define  FHC_CONTROL_DCD&t;0x00008000 /* DC--&gt;DC Converter Disable&t;&t;*/
DECL|macro|FHC_CONTROL_POFF
mdefine_line|#define  FHC_CONTROL_POFF&t;0x00004000 /* AC/DC Controller PLL Disable&t;*/
DECL|macro|FHC_CONTROL_FOFF
mdefine_line|#define  FHC_CONTROL_FOFF&t;0x00002000 /* FHC Controller PLL Disable&t;*/
DECL|macro|FHC_CONTROL_AOFF
mdefine_line|#define  FHC_CONTROL_AOFF&t;0x00001000 /* CPU A SRAM/SBD Low Power Mode&t;*/
DECL|macro|FHC_CONTROL_BOFF
mdefine_line|#define  FHC_CONTROL_BOFF&t;0x00000800 /* CPU B SRAM/SBD Low Power Mode&t;*/
DECL|macro|FHC_CONTROL_PSOFF
mdefine_line|#define  FHC_CONTROL_PSOFF&t;0x00000400 /* Turns off this FHC&squot;s power supply&t;*/
DECL|macro|FHC_CONTROL_IXIST
mdefine_line|#define  FHC_CONTROL_IXIST&t;0x00000200 /* 0=FHC tells clock board it exists&t;*/
DECL|macro|FHC_CONTROL_XMSTR
mdefine_line|#define  FHC_CONTROL_XMSTR&t;0x00000100 /* 1=Causes this FHC to be XIR master*/
DECL|macro|FHC_CONTROL_LLED
mdefine_line|#define  FHC_CONTROL_LLED&t;0x00000040 /* 0=Left LED ON&t;&t;&t;*/
DECL|macro|FHC_CONTROL_MLED
mdefine_line|#define  FHC_CONTROL_MLED&t;0x00000020 /* 1=Middle LED ON&t;&t;&t;*/
DECL|macro|FHC_CONTROL_RLED
mdefine_line|#define  FHC_CONTROL_RLED&t;0x00000010 /* 1=Right LED&t;&t;&t;*/
DECL|macro|FHC_CONTROL_BPINS
mdefine_line|#define  FHC_CONTROL_BPINS&t;0x00000003 /* Spare Bidirectional Pins&t;&t;*/
DECL|macro|FHC_PREGS_BSR
mdefine_line|#define FHC_PREGS_BSR&t;0x30UL&t;/* FHC Board Status Register */
DECL|macro|FHC_BSR_DA64
mdefine_line|#define  FHC_BSR_DA64&t;&t;0x00040000 /* Port A: 0=128bit 1=64bit data path */
DECL|macro|FHC_BSR_DB64
mdefine_line|#define  FHC_BSR_DB64&t;&t;0x00020000 /* Port B: 0=128bit 1=64bit data path */
DECL|macro|FHC_BSR_BID
mdefine_line|#define  FHC_BSR_BID&t;&t;0x0001e000 /* Board ID                           */
DECL|macro|FHC_BSR_SA
mdefine_line|#define  FHC_BSR_SA&t;&t;0x00001c00 /* Port A UPA Speed (from the pins)   */
DECL|macro|FHC_BSR_SB
mdefine_line|#define  FHC_BSR_SB&t;&t;0x00000380 /* Port B UPA Speed (from the pins)   */
DECL|macro|FHC_BSR_NDIAG
mdefine_line|#define  FHC_BSR_NDIAG&t;&t;0x00000040 /* Not in Diag Mode                   */
DECL|macro|FHC_BSR_NTBED
mdefine_line|#define  FHC_BSR_NTBED&t;&t;0x00000020 /* Not in TestBED Mode                */
DECL|macro|FHC_BSR_NIA
mdefine_line|#define  FHC_BSR_NIA&t;&t;0x0000001c /* Jumper, bit 18 in PROM space       */
DECL|macro|FHC_BSR_SI
mdefine_line|#define  FHC_BSR_SI&t;&t;0x00000001 /* Spare input pin value              */
DECL|macro|FHC_PREGS_ECC
mdefine_line|#define FHC_PREGS_ECC&t;0x40UL&t;/* FHC ECC Control Register (16 bits) */
DECL|macro|FHC_PREGS_JCTRL
mdefine_line|#define FHC_PREGS_JCTRL&t;0x50UL&t;/* FHC JTAG Control Register */
DECL|macro|FHC_JTAG_CTRL_MENAB
mdefine_line|#define  FHC_JTAG_CTRL_MENAB&t;0x80000000 /* Indicates this is JTAG Master&t; */
DECL|macro|FHC_JTAG_CTRL_MNONE
mdefine_line|#define  FHC_JTAG_CTRL_MNONE&t;0x40000000 /* Indicates no JTAG Master present&t; */
DECL|macro|FHC_PREGS_JCMD
mdefine_line|#define FHC_PREGS_JCMD&t;0x60UL&t;/* FHC JTAG Command Register */
DECL|member|ireg
r_int
r_int
id|ireg
suffix:semicolon
multiline_comment|/* FHC IGN reg */
DECL|macro|FHC_IREG_IGN
mdefine_line|#define FHC_IREG_IGN&t;0x00UL&t;/* This FHC&squot;s IGN */
DECL|member|ffregs
r_int
r_int
id|ffregs
suffix:semicolon
multiline_comment|/* FHC fanfail regs */
DECL|macro|FHC_FFREGS_IMAP
mdefine_line|#define FHC_FFREGS_IMAP&t;0x00UL&t;/* FHC Fanfail IMAP */
DECL|macro|FHC_FFREGS_ICLR
mdefine_line|#define FHC_FFREGS_ICLR&t;0x10UL&t;/* FHC Fanfail ICLR */
DECL|member|sregs
r_int
r_int
id|sregs
suffix:semicolon
multiline_comment|/* FHC system regs */
DECL|macro|FHC_SREGS_IMAP
mdefine_line|#define FHC_SREGS_IMAP&t;0x00UL&t;/* FHC System IMAP */
DECL|macro|FHC_SREGS_ICLR
mdefine_line|#define FHC_SREGS_ICLR&t;0x10UL&t;/* FHC System ICLR */
DECL|member|uregs
r_int
r_int
id|uregs
suffix:semicolon
multiline_comment|/* FHC uart regs */
DECL|macro|FHC_UREGS_IMAP
mdefine_line|#define FHC_UREGS_IMAP&t;0x00UL&t;/* FHC Uart IMAP */
DECL|macro|FHC_UREGS_ICLR
mdefine_line|#define FHC_UREGS_ICLR&t;0x10UL&t;/* FHC Uart ICLR */
DECL|member|tregs
r_int
r_int
id|tregs
suffix:semicolon
multiline_comment|/* FHC TOD regs */
DECL|macro|FHC_TREGS_IMAP
mdefine_line|#define FHC_TREGS_IMAP&t;0x00UL&t;/* FHC TOD IMAP */
DECL|macro|FHC_TREGS_ICLR
mdefine_line|#define FHC_TREGS_ICLR&t;0x10UL&t;/* FHC TOD ICLR */
)brace
suffix:semicolon
DECL|struct|linux_fhc
r_struct
id|linux_fhc
(brace
DECL|member|next
r_struct
id|linux_fhc
op_star
id|next
suffix:semicolon
DECL|member|parent
r_struct
id|linux_central
op_star
id|parent
suffix:semicolon
multiline_comment|/* NULL if not central FHC */
DECL|member|fhc_regs
r_struct
id|fhc_regs
id|fhc_regs
suffix:semicolon
DECL|member|board
r_int
id|board
suffix:semicolon
DECL|member|jtag_master
r_int
id|jtag_master
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|fhc_ranges
r_struct
id|linux_prom_ranges
id|fhc_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_fhc_ranges
r_int
id|num_fhc_ranges
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|linux_central
op_star
id|central_bus
suffix:semicolon
r_extern
r_void
id|apply_central_ranges
c_func
(paren
r_struct
id|linux_central
op_star
id|central
comma
r_struct
id|linux_prom_registers
op_star
id|regs
comma
r_int
id|nregs
)paren
suffix:semicolon
r_extern
r_void
id|apply_fhc_ranges
c_func
(paren
r_struct
id|linux_fhc
op_star
id|fhc
comma
r_struct
id|linux_prom_registers
op_star
id|regs
comma
r_int
id|nregs
)paren
suffix:semicolon
macro_line|#endif /* !(_SPARC64_FHC_H) */
eof
