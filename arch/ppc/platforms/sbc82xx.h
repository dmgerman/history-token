multiline_comment|/* Board information for the SBCPowerQUICCII, which should be generic for&n; * all 8260 boards.  The IMMR is now given to us so the hard define&n; * will soon be removed.  All of the clock values are computed from&n; * the configuration SCMR and the Power-On-Reset word.&n; */
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;&t;&t;0xf0000000
DECL|macro|SBC82xx_TODC_NVRAM_ADDR
mdefine_line|#define SBC82xx_TODC_NVRAM_ADDR&t;&t;0x80000000
DECL|macro|SBC82xx_MACADDR_NVRAM_FCC1
mdefine_line|#define SBC82xx_MACADDR_NVRAM_FCC1&t;0x220000c9&t;/* JP6B */
DECL|macro|SBC82xx_MACADDR_NVRAM_SCC1
mdefine_line|#define SBC82xx_MACADDR_NVRAM_SCC1&t;0x220000cf&t;/* JP6A */
DECL|macro|SBC82xx_MACADDR_NVRAM_FCC2
mdefine_line|#define SBC82xx_MACADDR_NVRAM_FCC2&t;0x220000d5&t;/* JP7A */
DECL|macro|SBC82xx_MACADDR_NVRAM_FCC3
mdefine_line|#define SBC82xx_MACADDR_NVRAM_FCC3&t;0x220000db&t;/* JP7B */
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
DECL|member|bi_enetaddrs
r_int
r_char
id|bi_enetaddrs
(braket
l_int|4
)braket
(braket
l_int|6
)braket
suffix:semicolon
DECL|macro|bi_enetaddr
mdefine_line|#define bi_enetaddr&t;bi_enetaddrs[0]
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
r_extern
id|bd_t
id|m8xx_board_info
suffix:semicolon
eof
