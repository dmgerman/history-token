multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * the Motorola 860T FADS board.  Copied from the MBX stuff.&n; *&n; * Copyright (c) 1998 Dan Malek (dmalek@jlc.net)&n; */
macro_line|#ifndef __MACH_FADS_DEFS
DECL|macro|__MACH_FADS_DEFS
mdefine_line|#define __MACH_FADS_DEFS
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
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
r_extern
id|bd_t
id|m8xx_board_info
suffix:semicolon
multiline_comment|/* Memory map is configured by the PROM startup.&n; * I tried to follow the FADS manual, although the startup PROM&n; * dictates this.&n; */
DECL|macro|BCSR_ADDR
mdefine_line|#define BCSR_ADDR&t;&t;((uint)0x02100000)
DECL|macro|BCSR_SIZE
mdefine_line|#define BCSR_SIZE&t;&t;((uint)(64 * 1024))
DECL|macro|BCSR0
mdefine_line|#define&t;BCSR0&t;&t;&t;((uint)0x02100000)
DECL|macro|BCSR1
mdefine_line|#define&t;BCSR1&t;&t;&t;((uint)0x02100004)
DECL|macro|BCSR2
mdefine_line|#define&t;BCSR2&t;&t;&t;((uint)0x02100008)
DECL|macro|BCSR3
mdefine_line|#define&t;BCSR3&t;&t;&t;((uint)0x0210000c)
DECL|macro|BCSR4
mdefine_line|#define&t;BCSR4&t;&t;&t;((uint)0x02100010)
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;&t;((uint)0x02200000)
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;&t;((uint)(64 * 1024))
DECL|macro|PCMCIA_MEM_ADDR
mdefine_line|#define PCMCIA_MEM_ADDR&t;&t;((uint)0x04000000)
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;&t;((uint)(64 * 1024))
macro_line|#endif
eof
