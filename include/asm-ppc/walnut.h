multiline_comment|/*&n; * BK Id: SCCS/s.walnut.h 1.10 09/14/01 17:37:56 trini&n; */
multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Copyright 2000 MontaVista Software Inc.&n; *&t;PPC405 modifications&n; * &t;Author: MontaVista Software, Inc.&n; *         &t;frank_rowand@mvista.com or source@mvista.com&n; * &t;   &t;debbie_chu@mvista.com&n; *&n; *    Module name: ppc405.h&n; *&n; *    Description:&n; *      Macros, definitions, and data structures specific to the IBM PowerPC&n; *      based boards.&n; *&n; *      This includes:&n; *&n; *         405GP &quot;Walnut&quot; evaluation board&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef&t;__WALNUT_H__
DECL|macro|__WALNUT_H__
mdefine_line|#define&t;__WALNUT_H__
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
DECL|member|bi_procfreq
r_int
r_int
id|bi_procfreq
suffix:semicolon
multiline_comment|/* Processor speed, in Hz */
DECL|member|bi_plb_busfreq
r_int
r_int
id|bi_plb_busfreq
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
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* Memory map for the IBM &quot;Walnut&quot; 405GP evaluation board.&n; * Generic 4xx plus RTC.&n; */
DECL|macro|WALNUT_RTC_ADDR
mdefine_line|#define WALNUT_RTC_ADDR&t;&t;((uint)0xf0001000)
DECL|macro|WALNUT_RTC_SIZE
mdefine_line|#define WALNUT_RTC_SIZE&t;&t;((uint)4*1024)
macro_line|#endif /* __WALNUT_H__ */
macro_line|#endif /* __KERNEL__ */
eof
