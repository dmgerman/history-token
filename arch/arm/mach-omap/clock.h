multiline_comment|/*&n; *  linux/arch/arm/mach-omap/clock.h&n; *&n; *  Copyright (C) 2004 Nokia corporation&n; *  Written by Tuukka Tikkanen &lt;tuukka.tikkanen@elektrobit.com&gt;&n; *  Based on clocks.h by Tony Lindgren, Gordon McNutt and RidgeRun, Inc&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ARCH_ARM_OMAP_CLOCK_H
DECL|macro|__ARCH_ARM_OMAP_CLOCK_H
mdefine_line|#define __ARCH_ARM_OMAP_CLOCK_H
r_struct
id|module
suffix:semicolon
DECL|struct|clk
r_struct
id|clk
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|parent
r_struct
id|clk
op_star
id|parent
suffix:semicolon
DECL|member|rate
r_int
r_int
id|rate
suffix:semicolon
DECL|member|usecount
id|__s8
id|usecount
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|enable_reg
id|__u32
id|enable_reg
suffix:semicolon
DECL|member|enable_bit
id|__u8
id|enable_bit
suffix:semicolon
DECL|member|rate_offset
id|__u8
id|rate_offset
suffix:semicolon
DECL|member|recalc
r_void
(paren
op_star
id|recalc
)paren
(paren
r_struct
id|clk
op_star
)paren
suffix:semicolon
DECL|member|set_rate
r_int
(paren
op_star
id|set_rate
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|round_rate
r_int
(paren
op_star
id|round_rate
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpu_rate
r_struct
id|mpu_rate
(brace
DECL|member|rate
r_int
r_int
id|rate
suffix:semicolon
DECL|member|xtal
r_int
r_int
id|xtal
suffix:semicolon
DECL|member|pll_rate
r_int
r_int
id|pll_rate
suffix:semicolon
DECL|member|ckctl_val
id|__u16
id|ckctl_val
suffix:semicolon
DECL|member|dpllctl_val
id|__u16
id|dpllctl_val
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Clock flags */
DECL|macro|RATE_CKCTL
mdefine_line|#define RATE_CKCTL&t;&t;1
DECL|macro|RATE_FIXED
mdefine_line|#define RATE_FIXED&t;&t;2
DECL|macro|RATE_PROPAGATES
mdefine_line|#define RATE_PROPAGATES&t;&t;4
DECL|macro|VIRTUAL_CLOCK
mdefine_line|#define VIRTUAL_CLOCK&t;&t;8
DECL|macro|ALWAYS_ENABLED
mdefine_line|#define ALWAYS_ENABLED&t;&t;16
DECL|macro|ENABLE_REG_32BIT
mdefine_line|#define ENABLE_REG_32BIT&t;32
DECL|macro|CLOCK_IN_OMAP16XX
mdefine_line|#define CLOCK_IN_OMAP16XX&t;64
DECL|macro|CLOCK_IN_OMAP1510
mdefine_line|#define CLOCK_IN_OMAP1510&t;128
multiline_comment|/* ARM_CKCTL bit shifts */
DECL|macro|CKCTL_PERDIV_OFFSET
mdefine_line|#define CKCTL_PERDIV_OFFSET&t;0
DECL|macro|CKCTL_LCDDIV_OFFSET
mdefine_line|#define CKCTL_LCDDIV_OFFSET&t;2
DECL|macro|CKCTL_ARMDIV_OFFSET
mdefine_line|#define CKCTL_ARMDIV_OFFSET&t;4
DECL|macro|CKCTL_DSPDIV_OFFSET
mdefine_line|#define CKCTL_DSPDIV_OFFSET&t;6
DECL|macro|CKCTL_TCDIV_OFFSET
mdefine_line|#define CKCTL_TCDIV_OFFSET&t;8
DECL|macro|CKCTL_DSPMMUDIV_OFFSET
mdefine_line|#define CKCTL_DSPMMUDIV_OFFSET&t;10
multiline_comment|/*#define ARM_TIMXO&t;&t;12*/
DECL|macro|EN_DSPCK
mdefine_line|#define EN_DSPCK&t;&t;13
multiline_comment|/*#define ARM_INTHCK_SEL&t;14*/
multiline_comment|/* Divide-by-2 for mpu inth_ck */
multiline_comment|/* ARM_IDLECT1 bit shifts */
multiline_comment|/*#define IDLWDT_ARM&t;0*/
multiline_comment|/*#define IDLXORP_ARM&t;1*/
multiline_comment|/*#define IDLPER_ARM&t;2*/
multiline_comment|/*#define IDLLCD_ARM&t;3*/
multiline_comment|/*#define IDLLB_ARM&t;4*/
multiline_comment|/*#define IDLHSAB_ARM&t;5*/
multiline_comment|/*#define IDLIF_ARM&t;6*/
multiline_comment|/*#define IDLDPLL_ARM&t;7*/
multiline_comment|/*#define IDLAPI_ARM&t;8*/
multiline_comment|/*#define IDLTIM_ARM&t;9*/
multiline_comment|/*#define SETARM_IDLE&t;11*/
multiline_comment|/* ARM_IDLECT2 bit shifts */
DECL|macro|EN_WDTCK
mdefine_line|#define EN_WDTCK&t;0
DECL|macro|EN_XORPCK
mdefine_line|#define EN_XORPCK&t;1
DECL|macro|EN_PERCK
mdefine_line|#define EN_PERCK&t;2
DECL|macro|EN_LCDCK
mdefine_line|#define EN_LCDCK&t;3
DECL|macro|EN_LBCK
mdefine_line|#define EN_LBCK&t;&t;4 /* Not on 1610/1710 */
multiline_comment|/*#define EN_HSABCK&t;5*/
DECL|macro|EN_APICK
mdefine_line|#define EN_APICK&t;6
DECL|macro|EN_TIMCK
mdefine_line|#define EN_TIMCK&t;7
DECL|macro|DMACK_REQ
mdefine_line|#define DMACK_REQ&t;8
DECL|macro|EN_GPIOCK
mdefine_line|#define EN_GPIOCK&t;9 /* Not on 1610/1710 */
multiline_comment|/*#define EN_LBFREECK&t;10*/
DECL|macro|EN_CKOUT_ARM
mdefine_line|#define EN_CKOUT_ARM&t;11
multiline_comment|/* ARM_IDLECT3 bit shifts */
DECL|macro|EN_OCPI_CK
mdefine_line|#define EN_OCPI_CK&t;0
DECL|macro|EN_TC1_CK
mdefine_line|#define EN_TC1_CK&t;2
DECL|macro|EN_TC2_CK
mdefine_line|#define EN_TC2_CK&t;4
multiline_comment|/* Various register defines for clock controls scattered around OMAP chip */
DECL|macro|USB_MCLK_EN
mdefine_line|#define USB_MCLK_EN&t;&t;4&t;/* In ULPD_CLKC_CTRL */
DECL|macro|USB_HOST_HHC_UHOST_EN
mdefine_line|#define USB_HOST_HHC_UHOST_EN&t;9&t;/* In MOD_CONF_CTRL_0 */
r_int
id|clk_register
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
r_void
id|clk_unregister
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
r_int
id|clk_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
