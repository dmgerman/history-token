multiline_comment|/******************************************************************************&n; *                  QLOGIC LINUX SOFTWARE&n; *&n; * QLogic ISP2x00 device driver for Linux 2.6.x&n; * Copyright (C) 2003 QLogic Corporation&n; * (www.qlogic.com)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Firmware Dump structure definition&n; */
DECL|macro|FW_DUMP_SIZE
mdefine_line|#define FW_DUMP_SIZE&t;0xBC000&t;&t;/* bytes */
DECL|struct|qla2300_fw_dump
r_struct
id|qla2300_fw_dump
(brace
DECL|member|hccr
r_uint16
id|hccr
suffix:semicolon
DECL|member|pbiu_reg
r_uint16
id|pbiu_reg
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|risc_host_reg
r_uint16
id|risc_host_reg
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|mailbox_reg
r_uint16
id|mailbox_reg
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|resp_dma_reg
r_uint16
id|resp_dma_reg
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|dma_reg
r_uint16
id|dma_reg
(braket
l_int|48
)braket
suffix:semicolon
DECL|member|risc_hdw_reg
r_uint16
id|risc_hdw_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp0_reg
r_uint16
id|risc_gp0_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp1_reg
r_uint16
id|risc_gp1_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp2_reg
r_uint16
id|risc_gp2_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp3_reg
r_uint16
id|risc_gp3_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp4_reg
r_uint16
id|risc_gp4_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp5_reg
r_uint16
id|risc_gp5_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp6_reg
r_uint16
id|risc_gp6_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp7_reg
r_uint16
id|risc_gp7_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|frame_buf_hdw_reg
r_uint16
id|frame_buf_hdw_reg
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|fpm_b0_reg
r_uint16
id|fpm_b0_reg
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|fpm_b1_reg
r_uint16
id|fpm_b1_reg
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|risc_ram
r_uint16
id|risc_ram
(braket
l_int|0xf800
)braket
suffix:semicolon
DECL|member|stack_ram
r_uint16
id|stack_ram
(braket
l_int|0x1000
)braket
suffix:semicolon
DECL|member|data_ram
r_uint16
id|data_ram
(braket
l_int|0xF000
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qla2100_fw_dump
r_struct
id|qla2100_fw_dump
(brace
DECL|member|hccr
r_uint16
id|hccr
suffix:semicolon
DECL|member|pbiu_reg
r_uint16
id|pbiu_reg
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|mailbox_reg
r_uint16
id|mailbox_reg
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|dma_reg
r_uint16
id|dma_reg
(braket
l_int|48
)braket
suffix:semicolon
DECL|member|risc_hdw_reg
r_uint16
id|risc_hdw_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp0_reg
r_uint16
id|risc_gp0_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp1_reg
r_uint16
id|risc_gp1_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp2_reg
r_uint16
id|risc_gp2_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp3_reg
r_uint16
id|risc_gp3_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp4_reg
r_uint16
id|risc_gp4_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp5_reg
r_uint16
id|risc_gp5_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp6_reg
r_uint16
id|risc_gp6_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|risc_gp7_reg
r_uint16
id|risc_gp7_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|frame_buf_hdw_reg
r_uint16
id|frame_buf_hdw_reg
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|fpm_b0_reg
r_uint16
id|fpm_b0_reg
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|fpm_b1_reg
r_uint16
id|fpm_b1_reg
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|risc_ram
r_uint16
id|risc_ram
(braket
l_int|0xf000
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Driver debug definitions.&n; */
multiline_comment|/* #define QL_DEBUG_LEVEL_1  */
multiline_comment|/* Output register accesses to COM1 */
multiline_comment|/* #define QL_DEBUG_LEVEL_2  */
multiline_comment|/* Output error msgs to COM1 */
multiline_comment|/* #define QL_DEBUG_LEVEL_3  */
multiline_comment|/* Output function trace msgs to COM1 */
multiline_comment|/* #define QL_DEBUG_LEVEL_4  */
multiline_comment|/* Output NVRAM trace msgs to COM1 */
multiline_comment|/* #define QL_DEBUG_LEVEL_5  */
multiline_comment|/* Output ring trace msgs to COM1 */
multiline_comment|/* #define QL_DEBUG_LEVEL_6  */
multiline_comment|/* Output WATCHDOG timer trace to COM1 */
multiline_comment|/* #define QL_DEBUG_LEVEL_7  */
multiline_comment|/* Output RISC load trace msgs to COM1 */
multiline_comment|/* #define QL_DEBUG_LEVEL_8  */
multiline_comment|/* Output ring saturation msgs to COM1 */
multiline_comment|/* #define QL_DEBUG_LEVEL_9  */
multiline_comment|/* Output IOCTL trace msgs */
multiline_comment|/* #define QL_DEBUG_LEVEL_10 */
multiline_comment|/* Output IOCTL error msgs */
multiline_comment|/* #define QL_DEBUG_LEVEL_11 */
multiline_comment|/* Output Mbx Cmd trace msgs */
multiline_comment|/* #define QL_DEBUG_LEVEL_12 */
multiline_comment|/* Output IP trace msgs */
multiline_comment|/* #define QL_DEBUG_LEVEL_13 */
multiline_comment|/* Output fdmi function trace msgs */
multiline_comment|/* #define QL_DEBUG_LEVEL_14 */
multiline_comment|/* Output RSCN trace msgs */
multiline_comment|/*&n; *  Local Macro Definitions.&n; */
macro_line|#if defined(QL_DEBUG_LEVEL_1)  || defined(QL_DEBUG_LEVEL_2) || &bslash;&n;    defined(QL_DEBUG_LEVEL_3)  || defined(QL_DEBUG_LEVEL_4) || &bslash;&n;    defined(QL_DEBUG_LEVEL_5)  || defined(QL_DEBUG_LEVEL_6) || &bslash;&n;    defined(QL_DEBUG_LEVEL_7)  || defined(QL_DEBUG_LEVEL_8) || &bslash;&n;    defined(QL_DEBUG_LEVEL_9)  || defined(QL_DEBUG_LEVEL_10) || &bslash;&n;    defined(QL_DEBUG_LEVEL_11) || defined(QL_DEBUG_LEVEL_12) || &bslash;&n;    defined(QL_DEBUG_LEVEL_13) || defined(QL_DEBUG_LEVEL_14)
DECL|macro|QL_DEBUG_ROUTINES
mdefine_line|#define QL_DEBUG_ROUTINES
macro_line|#endif
multiline_comment|/*&n;* Macros use for debugging the driver.&n;*/
DECL|macro|ENTER_TRACE
macro_line|#undef ENTER_TRACE
macro_line|#if defined(ENTER_TRACE)
DECL|macro|ENTER
mdefine_line|#define ENTER(x)&t;do { printk(&quot;qla2100 : Entering %s()&bslash;n&quot;, x); } while (0)
DECL|macro|LEAVE
mdefine_line|#define LEAVE(x)&t;do { printk(&quot;qla2100 : Leaving %s()&bslash;n&quot;, x);  } while (0)
DECL|macro|ENTER_INTR
mdefine_line|#define ENTER_INTR(x)&t;do { printk(&quot;qla2100 : Entering %s()&bslash;n&quot;, x); } while (0)
DECL|macro|LEAVE_INTR
mdefine_line|#define LEAVE_INTR(x)&t;do { printk(&quot;qla2100 : Leaving %s()&bslash;n&quot;, x);  } while (0)
macro_line|#else
DECL|macro|ENTER
mdefine_line|#define ENTER(x)&t;do {} while (0)
DECL|macro|LEAVE
mdefine_line|#define LEAVE(x)&t;do {} while (0)
DECL|macro|ENTER_INTR
mdefine_line|#define ENTER_INTR(x) &t;do {} while (0)
DECL|macro|LEAVE_INTR
mdefine_line|#define LEAVE_INTR(x)   do {} while (0)
macro_line|#endif
macro_line|#if  DEBUG_QLA2100
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)&t;do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)&t;do {} while (0);
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_1)
DECL|macro|DEBUG1
mdefine_line|#define DEBUG1(x)&t;do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG1
mdefine_line|#define DEBUG1(x)&t;do {} while (0);
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_2)
DECL|macro|DEBUG2
mdefine_line|#define DEBUG2(x)       do {x;} while (0);
DECL|macro|DEBUG2_3
mdefine_line|#define DEBUG2_3(x)     do {x;} while (0);
DECL|macro|DEBUG2_3_11
mdefine_line|#define DEBUG2_3_11(x)  do {x;} while (0);
DECL|macro|DEBUG2_9_10
mdefine_line|#define DEBUG2_9_10(x)    do {x;} while (0);
DECL|macro|DEBUG2_11
mdefine_line|#define DEBUG2_11(x)    do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG2
mdefine_line|#define DEBUG2(x)&t;do {} while (0);
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_3)
DECL|macro|DEBUG3
mdefine_line|#define DEBUG3(x)&t;do {x;} while (0);
DECL|macro|DEBUG2_3
mdefine_line|#define DEBUG2_3(x)&t;do {x;} while (0);
DECL|macro|DEBUG2_3_11
mdefine_line|#define DEBUG2_3_11(x)&t;do {x;} while (0);
DECL|macro|DEBUG3_11
mdefine_line|#define DEBUG3_11(x)&t;do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG3
mdefine_line|#define DEBUG3(x)&t;do {} while (0);
macro_line|#if !defined(QL_DEBUG_LEVEL_2)
DECL|macro|DEBUG2_3
mdefine_line|#define DEBUG2_3(x)&t;do {} while (0);
macro_line|#endif
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_4)
DECL|macro|DEBUG4
mdefine_line|#define DEBUG4(x)&t;do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG4
mdefine_line|#define DEBUG4(x)&t;do {} while (0);
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_5)
DECL|macro|DEBUG5
mdefine_line|#define DEBUG5(x)          do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG5
mdefine_line|#define DEBUG5(x)&t;do {} while (0);
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_7)
DECL|macro|DEBUG7
mdefine_line|#define DEBUG7(x)          do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG7
mdefine_line|#define DEBUG7(x)&t;   do {} while (0);
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_9)
DECL|macro|DEBUG9
mdefine_line|#define DEBUG9(x)       do {x;} while (0);
DECL|macro|DEBUG9_10
mdefine_line|#define DEBUG9_10(x)    do {x;} while (0);
DECL|macro|DEBUG2_9_10
mdefine_line|#define DEBUG2_9_10(x)&t;do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG9
mdefine_line|#define DEBUG9(x)&t;do {} while (0);
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_10)
DECL|macro|DEBUG10
mdefine_line|#define DEBUG10(x)      do {x;} while (0);
DECL|macro|DEBUG2_9_10
mdefine_line|#define DEBUG2_9_10(x)&t;do {x;} while (0);
DECL|macro|DEBUG9_10
mdefine_line|#define DEBUG9_10(x)&t;do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG10
mdefine_line|#define DEBUG10(x)&t;do {} while (0);
macro_line|#if !defined(DEBUG2_9_10)
DECL|macro|DEBUG2_9_10
mdefine_line|#define DEBUG2_9_10(x)&t;do {} while (0);
macro_line|#endif
macro_line|#if !defined(DEBUG9_10)
DECL|macro|DEBUG9_10
mdefine_line|#define DEBUG9_10(x)&t;do {} while (0);
macro_line|#endif
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_11)
DECL|macro|DEBUG11
mdefine_line|#define DEBUG11(x)      do{x;} while(0);
macro_line|#if !defined(DEBUG2_11)
DECL|macro|DEBUG2_11
mdefine_line|#define DEBUG2_11(x)    do{x;} while(0);
macro_line|#endif
macro_line|#if !defined(DEBUG2_3_11)
DECL|macro|DEBUG2_3_11
mdefine_line|#define DEBUG2_3_11(x)  do{x;} while(0);
macro_line|#endif
macro_line|#if !defined(DEBUG3_11)
DECL|macro|DEBUG3_11
mdefine_line|#define DEBUG3_11(x)    do{x;} while(0);
macro_line|#endif
macro_line|#else
DECL|macro|DEBUG11
mdefine_line|#define DEBUG11(x)&t;do{} while(0);
macro_line|#if !defined(QL_DEBUG_LEVEL_2)
DECL|macro|DEBUG2_11
mdefine_line|#define DEBUG2_11(x)&t;do{} while(0);
macro_line|#if !defined(QL_DEBUG_LEVEL_3)
DECL|macro|DEBUG2_3_11
mdefine_line|#define DEBUG2_3_11(x) do{} while(0);
macro_line|#endif
macro_line|#endif
macro_line|#if !defined(QL_DEBUG_LEVEL_3)
DECL|macro|DEBUG3_11
mdefine_line|#define DEBUG3_11(x)&t;do{} while(0);
macro_line|#endif
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_12)
DECL|macro|DEBUG12
mdefine_line|#define DEBUG12(x)      do {x;} while (0);
macro_line|#else
DECL|macro|DEBUG12
mdefine_line|#define DEBUG12(x)&t;do {} while (0);
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_13)
DECL|macro|DEBUG13
mdefine_line|#define DEBUG13(x)      do {x;} while (0)
macro_line|#else
DECL|macro|DEBUG13
mdefine_line|#define DEBUG13(x)&t;do {} while (0)
macro_line|#endif
macro_line|#if defined(QL_DEBUG_LEVEL_14)
DECL|macro|DEBUG14
mdefine_line|#define DEBUG14(x)      do {x;} while (0)
macro_line|#else
DECL|macro|DEBUG14
mdefine_line|#define DEBUG14(x)&t;do {} while (0)
macro_line|#endif
eof
