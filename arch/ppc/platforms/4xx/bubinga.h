multiline_comment|/*&n; * Support for IBM PPC 405EP evaluation board (Bubinga).&n; *&n; * Author: SAW (IBM), derived from walnut.h.&n; *         Maintained by MontaVista Software &lt;source@mvista.com&gt;&n; *&n; * 2003 (c) MontaVista Softare Inc.  This file is licensed under the&n; * terms of the GNU General Public License version 2. This program is&n; * licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __BUBINGA_H__
DECL|macro|__BUBINGA_H__
mdefine_line|#define __BUBINGA_H__
multiline_comment|/* 405EP */
macro_line|#include &lt;platforms/4xx/ibm405ep.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Data structure defining board information maintained by the boot&n; * ROM on IBM&squot;s evaluation board. An effort has been made to&n; * keep the field names consistent with the 8xx &squot;bd_t&squot; board info&n; * structures.&n; */
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
DECL|member|bi_pci_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|2
)braket
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Local Ethernet MAC address */
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
DECL|member|bi_opb_busfreq
r_int
r_int
id|bi_opb_busfreq
suffix:semicolon
multiline_comment|/* OPB Bus speed, in Hz */
DECL|member|bi_pllouta_freq
r_int
r_int
id|bi_pllouta_freq
suffix:semicolon
multiline_comment|/* PLL OUTA speed, in Hz */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
multiline_comment|/* Some 4xx parts use a different timebase frequency from the internal clock.&n;*/
DECL|macro|bi_tbfreq
mdefine_line|#define bi_tbfreq bi_intfreq
multiline_comment|/* Memory map for the Bubinga board.&n; * Generic 4xx plus RTC.&n; */
r_extern
r_void
op_star
id|bubinga_rtc_base
suffix:semicolon
DECL|macro|BUBINGA_RTC_PADDR
mdefine_line|#define BUBINGA_RTC_PADDR&t;((uint)0xf0000000)
DECL|macro|BUBINGA_RTC_VADDR
mdefine_line|#define BUBINGA_RTC_VADDR&t;BUBINGA_RTC_PADDR
DECL|macro|BUBINGA_RTC_SIZE
mdefine_line|#define BUBINGA_RTC_SIZE&t;((uint)8*1024)
multiline_comment|/* The UART clock is based off an internal clock -&n; * define BASE_BAUD based on the internal clock and divider(s).&n; * Since BASE_BAUD must be a constant, we will initialize it&n; * using clock/divider values which OpenBIOS initializes&n; * for typical configurations at various CPU speeds.&n; * The base baud is calculated as (FWDA / EXT UART DIV / 16)&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD       0
DECL|macro|BUBINGA_FPGA_BASE
mdefine_line|#define BUBINGA_FPGA_BASE      0xF0300000
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME     &quot;IBM Bubinga&quot;
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __BUBINGA_H__ */
macro_line|#endif /* __KERNEL__ */
eof
