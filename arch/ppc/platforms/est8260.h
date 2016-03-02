multiline_comment|/* Board information for the EST8260, which should be generic for&n; * all 8260 boards.  The IMMR is now given to us so the hard define&n; * will soon be removed.  All of the clock values are computed from&n; * the configuration SCMR and the Power-On-Reset word.&n; */
macro_line|#ifndef __EST8260_PLATFORM
DECL|macro|__EST8260_PLATFORM
mdefine_line|#define __EST8260_PLATFORM
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR&t;&t;((uint)0xf0000000)
DECL|macro|BOOTROM_RESTART_ADDR
mdefine_line|#define BOOTROM_RESTART_ADDR&t;((uint)0xff000104)
multiline_comment|/* For our show_cpuinfo hooks. */
DECL|macro|CPUINFO_VENDOR
mdefine_line|#define CPUINFO_VENDOR&t;&t;&quot;EST Corporation&quot;
DECL|macro|CPUINFO_MACHINE
mdefine_line|#define CPUINFO_MACHINE&t;&t;&quot;SBC8260 PowerPC&quot;
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
multiline_comment|/* Bus Freq, in MHz */
DECL|member|bi_cpmfreq
r_int
r_int
id|bi_cpmfreq
suffix:semicolon
multiline_comment|/* CPM Freq, in MHz */
DECL|member|bi_brgfreq
r_int
r_int
id|bi_brgfreq
suffix:semicolon
multiline_comment|/* BRG Freq, in MHz */
DECL|member|bi_vco
r_int
r_int
id|bi_vco
suffix:semicolon
multiline_comment|/* VCO Out from PLL */
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
multiline_comment|/* Default console baud rate */
DECL|member|bi_immr
r_int
r_int
id|bi_immr
suffix:semicolon
multiline_comment|/* IMMR when called from boot rom */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
r_extern
id|bd_t
id|m8xx_board_info
suffix:semicolon
macro_line|#endif &t;/* __EST8260_PLATFORM */
eof
