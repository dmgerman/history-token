multiline_comment|/*&n; *  linux/include/asm-arm/arch-omap/board.h&n; *&n; *  Information structures for board-specific data&n; *&n; *  Copyright (C) 2004&t;Nokia Corporation&n; *  Written by Juha Yrj&#xfffd;l&#xfffd; &lt;juha.yrjola@nokia.com&gt;&n; */
macro_line|#ifndef _OMAP_BOARD_H
DECL|macro|_OMAP_BOARD_H
mdefine_line|#define _OMAP_BOARD_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Different peripheral ids */
DECL|macro|OMAP_TAG_CLOCK
mdefine_line|#define OMAP_TAG_CLOCK&t;&t;0x4f01
DECL|macro|OMAP_TAG_MMC
mdefine_line|#define OMAP_TAG_MMC&t;&t;0x4f02
DECL|macro|OMAP_TAG_UART
mdefine_line|#define OMAP_TAG_UART&t;&t;0x4f03
DECL|struct|omap_clock_info
r_struct
id|omap_clock_info
(brace
multiline_comment|/* 0 for 12 MHz, 1 for 13 MHz and 2 for 19.2 MHz */
DECL|member|system_clock_type
id|u8
id|system_clock_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|omap_mmc_info
r_struct
id|omap_mmc_info
(brace
DECL|member|mmc_blocks
id|u8
id|mmc_blocks
suffix:semicolon
DECL|member|mmc1_power_pin
DECL|member|mmc2_power_pin
id|s8
id|mmc1_power_pin
comma
id|mmc2_power_pin
suffix:semicolon
DECL|member|mmc1_switch_pin
DECL|member|mmc2_switch_pin
id|s8
id|mmc1_switch_pin
comma
id|mmc2_switch_pin
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|omap_uart_info
r_struct
id|omap_uart_info
(brace
DECL|member|console_uart
id|u8
id|console_uart
suffix:semicolon
DECL|member|console_speed
id|u32
id|console_speed
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|omap_board_info_entry
r_struct
id|omap_board_info_entry
(brace
DECL|member|tag
id|u16
id|tag
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_const
r_void
op_star
id|__omap_get_per_info
c_func
(paren
id|u16
id|tag
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|omap_get_per_info
mdefine_line|#define omap_get_per_info(tag, type) &bslash;&n;&t;((const type *) __omap_get_per_info((tag), sizeof(type)))
macro_line|#endif
eof
