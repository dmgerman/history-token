multiline_comment|/*&n; * BK Id: SCCS/s.bseip.h 1.10 08/17/01 15:23:17 paulus&n; */
multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * the Bright Star Engineering ip-Engine board.  Copied from the MBX stuff.&n; *&n; * Copyright (c) 1998 Dan Malek (dmalek@jlc.net)&n; */
macro_line|#ifndef __MACH_BSEIP_DEFS
DECL|macro|__MACH_BSEIP_DEFS
mdefine_line|#define __MACH_BSEIP_DEFS
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* A Board Information structure that is given to a program when&n; * prom starts it up.&n; */
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
multiline_comment|/* Memory start address */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* Memory (end) size in bytes */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Internal Freq, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus Freq, in Hz */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
r_extern
id|bd_t
id|m8xx_board_info
suffix:semicolon
multiline_comment|/* Memory map is configured by the PROM startup.&n; * All we need to get started is the IMMR.&n; */
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;&t;((uint)0xff000000)
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;&t;((uint)(64 * 1024))
DECL|macro|PCMCIA_MEM_ADDR
mdefine_line|#define PCMCIA_MEM_ADDR&t;&t;((uint)0x04000000)
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;&t;((uint)(64 * 1024))
macro_line|#endif&t;/* !__ASSEMBLY__ */
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif
eof
