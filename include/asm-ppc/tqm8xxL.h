multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * the TQ Systems TQM850L modules.  This was originally created for the&n; * MBX860, and probably needs revisions for other boards (like the 821).&n; * When this file gets out of control, we can split it up into more&n; * meaningful pieces.&n; *&n; * Based on mbx.h, Copyright (c) 1997 Dan Malek (dmalek@jlc.net)&n; *&n; * Copyright (c) 1999 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __MACH_TQM8xxL_DEFS
DECL|macro|__MACH_TQM8xxL_DEFS
mdefine_line|#define __MACH_TQM8xxL_DEFS
multiline_comment|/* A Board Information structure that is given to a program when&n; * EPPC-Bug starts it up.&n; */
DECL|struct|bd_info
r_typedef
r_struct
id|bd_info
(brace
DECL|member|bi_memstart
r_int
r_int
id|bi_memstart
suffix:semicolon
multiline_comment|/* start of  DRAM memory */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* size  of  DRAM memory in bytes */
DECL|member|bi_flashstart
r_int
r_int
id|bi_flashstart
suffix:semicolon
multiline_comment|/* start of FLASH memory */
DECL|member|bi_flashsize
r_int
r_int
id|bi_flashsize
suffix:semicolon
multiline_comment|/* size  of FLASH memory */
DECL|member|bi_flashoffset
r_int
r_int
id|bi_flashoffset
suffix:semicolon
multiline_comment|/* reserved area for startup monitor */
DECL|member|bi_sramstart
r_int
r_int
id|bi_sramstart
suffix:semicolon
multiline_comment|/* start of  SRAM memory */
DECL|member|bi_sramsize
r_int
r_int
id|bi_sramsize
suffix:semicolon
multiline_comment|/* size  of  SRAM memory */
DECL|member|bi_immr_base
r_int
r_int
id|bi_immr_base
suffix:semicolon
multiline_comment|/* base of IMMR register */
DECL|member|bi_bootflags
r_int
r_int
id|bi_bootflags
suffix:semicolon
multiline_comment|/* boot / reboot flag (for LynxOS) */
DECL|member|bi_ip_addr
r_int
r_int
id|bi_ip_addr
suffix:semicolon
multiline_comment|/* IP Address */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Ethernet adress */
DECL|member|bi_reserved
r_int
r_char
id|bi_reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* -- just for alignment -- */
DECL|member|bi_putchar
r_int
r_int
id|bi_putchar
suffix:semicolon
multiline_comment|/* Addr of monitor putchar() to Console&t;*/
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Internal Freq, in MHz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus Freq, in MHz */
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
multiline_comment|/* Console Baudrate */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
multiline_comment|/* Configuration options for TQ Systems TQM850L mini module&n; */
DECL|macro|TQM_RESET_ADDR
mdefine_line|#define&t;TQM_RESET_ADDR&t;0x40000100&t;/* Monitor Reset Entry */
DECL|macro|TQM_IMMR_BASE
mdefine_line|#define&t;TQM_IMMR_BASE&t;0xFFF00000&t;/* phys. addr of IMMR */
DECL|macro|TQM_IMAP_SIZE
mdefine_line|#define&t;TQM_IMAP_SIZE&t;(64 * 1024)&t;/* size of mapped area */
DECL|macro|TQM_CLOCKRATE
mdefine_line|#define&t;TQM_CLOCKRATE&t;50&t;&t;/* 50 MHz Clock */
multiline_comment|/*#define&t;TQM_BAUDRATE&t;115200&t;*/
multiline_comment|/* Console baud rate */
DECL|macro|TQM_BAUDRATE
mdefine_line|#define&t;TQM_BAUDRATE&t;38400&t;&t;/* Console baud rate */
DECL|macro|TQM_IP_ADDR
mdefine_line|#define&t;TQM_IP_ADDR&t;0x0A000063&t;/* IP addr: 10.0.0.99 */
DECL|macro|TQM_SERVER_IP
mdefine_line|#define&t;TQM_SERVER_IP&t;&quot;10.0.0.2&quot;&t;/* NFS server IP addr */
DECL|macro|TQM_SERVER_DIR
mdefine_line|#define&t;TQM_SERVER_DIR&t;&quot;/LinuxPPC&quot;&t;/* NFS exported root */
DECL|macro|IMAP_ADDR
mdefine_line|#define&t;IMAP_ADDR&t;TQM_IMMR_BASE&t;/* physical base address of IMMR area */
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;TQM_IMAP_SIZE&t;/* mapped size of IMMR area */
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
multiline_comment|/* Generic 8xx type&n;*/
DECL|macro|_MACH_8xx
mdefine_line|#define _MACH_8xx (_MACH_tqm8xxL)
macro_line|#endif&t;/* __MACH_TQM8xxL_DEFS */
macro_line|#endif /* __KERNEL__ */
eof
