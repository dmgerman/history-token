multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Copyright 2000 MontaVista Software Inc.&n; *&t;PPC405 modifications&n; * &t;Author: MontaVista Software, Inc.&n; *         &t;frank_rowand@mvista.com or source@mvista.com&n; * &t;   &t;debbie_chu@mvista.com&n; *&n; *    Module name: ppc405.h&n; *&n; *    Description:&n; *      Macros, definitions, and data structures specific to the IBM PowerPC&n; *      based boards.&n; *&n; *      This includes:&n; *&n; *         405GP &quot;Walnut&quot; evaluation board&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_WALNUT_H__
DECL|macro|__ASM_WALNUT_H__
mdefine_line|#define __ASM_WALNUT_H__
multiline_comment|/* We have a 405GP core */
macro_line|#include &lt;platforms/ibm405gp.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Data structure defining board information maintained by the boot&n; * ROM on IBM&squot;s &quot;Walnut&quot; evaluation board. An effort has been made to&n; * keep the field names consistent with the 8xx &squot;bd_t&squot; board info&n; * structures.&n; */
DECL|struct|board_info
r_typedef
r_struct
id|board_info
(brace
DECL|member|bi_s_version
r_int
r_char
id|bi_s_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Version of this structure */
DECL|member|bi_r_version
r_int
r_char
id|bi_r_version
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* Version of the IBM ROM */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* DRAM installed, in bytes */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Local Ethernet MAC address */
DECL|member|bi_pci_enetaddr
r_int
r_char
id|bi_pci_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* PCI Ethernet MAC address */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Processor speed, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* PLB Bus speed, in Hz */
DECL|member|bi_pci_busfreq
r_int
r_int
id|bi_pci_busfreq
suffix:semicolon
multiline_comment|/* PCI Bus speed, in Hz */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
multiline_comment|/* Some 4xx parts use a different timebase frequency from the internal clock.&n;*/
DECL|macro|bi_tbfreq
mdefine_line|#define bi_tbfreq bi_intfreq
multiline_comment|/* Memory map for the IBM &quot;Walnut&quot; 405GP evaluation board.&n; * Generic 4xx plus RTC.&n; */
r_extern
r_void
op_star
id|walnut_rtc_base
suffix:semicolon
DECL|macro|WALNUT_RTC_PADDR
mdefine_line|#define WALNUT_RTC_PADDR&t;((uint)0xf0000000)
DECL|macro|WALNUT_RTC_VADDR
mdefine_line|#define WALNUT_RTC_VADDR&t;WALNUT_RTC_PADDR
DECL|macro|WALNUT_RTC_SIZE
mdefine_line|#define WALNUT_RTC_SIZE&t;&t;((uint)8*1024)
multiline_comment|/* ps2 keyboard and mouse */
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;25
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ&t;&t;&t;26
macro_line|#ifdef CONFIG_PPC405GP_INTERNAL_CLOCK
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;201600
macro_line|#else
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;691200
macro_line|#endif
DECL|macro|WALNUT_PS2_BASE
mdefine_line|#define WALNUT_PS2_BASE&t;&t;0xF0100000
DECL|macro|WALNUT_FPGA_BASE
mdefine_line|#define WALNUT_FPGA_BASE&t;0xF0300000
r_extern
r_void
op_star
id|kb_cs
suffix:semicolon
r_extern
r_void
op_star
id|kb_data
suffix:semicolon
DECL|macro|kbd_read_input
mdefine_line|#define kbd_read_input()&t;readb(kb_data)
DECL|macro|kbd_read_status
mdefine_line|#define kbd_read_status()&t;readb(kb_cs)
DECL|macro|kbd_write_output
mdefine_line|#define kbd_write_output(val)&t;writeb(val, kb_data)
DECL|macro|kbd_write_command
mdefine_line|#define kbd_write_command(val)&t;writeb(val, kb_cs)
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME&t;&quot;IBM Walnut&quot;
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_WALNUT_H__ */
macro_line|#endif /* __KERNEL__ */
eof
