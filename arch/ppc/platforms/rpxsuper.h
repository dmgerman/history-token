multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * the Embedded Planet RPX6 (or RPX Super) MPC8260 board.&n; * Copied from the RPX-Classic and SBS8260 stuff.&n; *&n; * Copyright (c) 2001 Dan Malek &lt;dan@embeddededge.com&gt;&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PLATFORMS_RPXSUPER_H__
DECL|macro|__ASM_PLATFORMS_RPXSUPER_H__
mdefine_line|#define __ASM_PLATFORMS_RPXSUPER_H__
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
DECL|member|bi_nvsize
r_int
r_int
id|bi_nvsize
suffix:semicolon
multiline_comment|/* NVRAM size in bytes (can be 0) */
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
multiline_comment|/* Memory map is configured by the PROM startup.&n; * We just map a few things we need.  The CSR is actually 4 byte-wide&n; * registers that can be accessed as 8-, 16-, or 32-bit values.&n; */
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;&t;((uint)0xf0000000)
DECL|macro|RPX_CSR_ADDR
mdefine_line|#define RPX_CSR_ADDR&t;&t;((uint)0xfa000000)
DECL|macro|RPX_CSR_SIZE
mdefine_line|#define RPX_CSR_SIZE&t;&t;((uint)(512 * 1024))
DECL|macro|RPX_NVRTC_ADDR
mdefine_line|#define RPX_NVRTC_ADDR&t;&t;((uint)0xfa080000)
DECL|macro|RPX_NVRTC_SIZE
mdefine_line|#define RPX_NVRTC_SIZE&t;&t;((uint)(512 * 1024))
multiline_comment|/* The RPX6 has 16, byte wide control/status registers.&n; * Not all are used (yet).&n; */
r_extern
r_volatile
id|u_char
op_star
id|rpx6_csr_addr
suffix:semicolon
multiline_comment|/* Things of interest in the CSR.&n;*/
DECL|macro|BCSR0_ID_MASK
mdefine_line|#define BCSR0_ID_MASK&t;&t;((u_char)0xf0)&t;&t;/* Read only */
DECL|macro|BCSR0_SWITCH_MASK
mdefine_line|#define BCSR0_SWITCH_MASK&t;((u_char)0x0f)&t;&t;/* Read only */
DECL|macro|BCSR1_XCVR_SMC1
mdefine_line|#define BCSR1_XCVR_SMC1&t;&t;((u_char)0x80)
DECL|macro|BCSR1_XCVR_SMC2
mdefine_line|#define BCSR1_XCVR_SMC2&t;&t;((u_char)0x40)
DECL|macro|BCSR2_FLASH_WENABLE
mdefine_line|#define BCSR2_FLASH_WENABLE&t;((u_char)0x20)
DECL|macro|BCSR2_NVRAM_ENABLE
mdefine_line|#define BCSR2_NVRAM_ENABLE&t;((u_char)0x10)
DECL|macro|BCSR2_ALT_IRQ2
mdefine_line|#define BCSR2_ALT_IRQ2&t;&t;((u_char)0x08)
DECL|macro|BCSR2_ALT_IRQ3
mdefine_line|#define BCSR2_ALT_IRQ3&t;&t;((u_char)0x04)
DECL|macro|BCSR2_PRST
mdefine_line|#define BCSR2_PRST&t;&t;((u_char)0x02)&t;&t;/* Force reset */
DECL|macro|BCSR2_ENPRST
mdefine_line|#define BCSR2_ENPRST&t;&t;((u_char)0x01)&t;&t;/* Enable POR */
DECL|macro|BCSR3_MODCLK_MASK
mdefine_line|#define BCSR3_MODCLK_MASK&t;((u_char)0xe0)
DECL|macro|BCSR3_ENCLKHDR
mdefine_line|#define BCSR3_ENCLKHDR&t;&t;((u_char)0x10)
DECL|macro|BCSR3_LED5
mdefine_line|#define BCSR3_LED5&t;&t;((u_char)0x04)&t;&t;/* 0 == on */
DECL|macro|BCSR3_LED6
mdefine_line|#define BCSR3_LED6&t;&t;((u_char)0x02)&t;&t;/* 0 == on */
DECL|macro|BCSR3_LED7
mdefine_line|#define BCSR3_LED7&t;&t;((u_char)0x01)&t;&t;/* 0 == on */
DECL|macro|BCSR4_EN_PHY
mdefine_line|#define BCSR4_EN_PHY&t;&t;((u_char)0x80)&t;&t;/* Enable PHY */
DECL|macro|BCSR4_EN_MII
mdefine_line|#define BCSR4_EN_MII&t;&t;((u_char)0x40)&t;&t;/* Enable PHY */
DECL|macro|BCSR4_MII_READ
mdefine_line|#define BCSR4_MII_READ&t;&t;((u_char)0x04)
DECL|macro|BCSR4_MII_MDC
mdefine_line|#define BCSR4_MII_MDC&t;&t;((u_char)0x02)
DECL|macro|BCSR4_MII_MDIO
mdefine_line|#define BCSR4_MII_MDIO&t;&t;((u_char)0x02)
DECL|macro|BCSR13_FETH_IRQMASK
mdefine_line|#define BCSR13_FETH_IRQMASK&t;((u_char)0xf0)
DECL|macro|BCSR15_FETH_IRQ
mdefine_line|#define BCSR15_FETH_IRQ&t;&t;((u_char)0x20)
macro_line|#endif /* __ASM_PLATFORMS_RPXSUPER_H__ */
macro_line|#endif /* __KERNEL__ */
eof
