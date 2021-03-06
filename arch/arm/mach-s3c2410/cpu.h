multiline_comment|/* arch/arm/mach-s3c2410/cpu.h&n; *&n; * Copyright (c) 2004-2005 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Header file for S3C24XX CPU support&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     24-Aug-2004 BJD  Start of generic S3C24XX support&n; *     18-Oct-2004 BJD  Moved board struct into this file&n; *     04-Jan-2005 BJD  New uart initialisation&n; *     10-Jan-2005 BJD  Moved generic init here, specific to cpu headers&n; *     14-Jan-2005 BJD  Added s3c24xx_init_clocks() call&n; *     10-Mar-2005 LCVR Changed S3C2410_{VA,SZ} to S3C24XX_{VA,SZ} &amp; IODESC_ENT&n; *     14-Mar-2005 BJD  Updated for __iomem&n;*/
multiline_comment|/* todo - fix when rmk changes iodescs to use `void __iomem *` */
DECL|macro|IODESC_ENT
mdefine_line|#define IODESC_ENT(x) { (unsigned long)S3C24XX_VA_##x, S3C2410_PA_##x, S3C24XX_SZ_##x, MT_DEVICE }
macro_line|#ifndef MHZ
DECL|macro|MHZ
mdefine_line|#define MHZ (1000*1000)
macro_line|#endif
DECL|macro|print_mhz
mdefine_line|#define print_mhz(m) ((m) / MHZ), ((m / 1000) % 1000)
multiline_comment|/* forward declaration */
r_struct
id|s3c2410_uartcfg
suffix:semicolon
r_struct
id|map_desc
suffix:semicolon
multiline_comment|/* core initialisation functions */
r_extern
r_void
id|s3c24xx_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|s3c24xx_init_io
c_func
(paren
r_struct
id|map_desc
op_star
id|mach_desc
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|s3c24xx_init_uarts
c_func
(paren
r_struct
id|s3c2410_uartcfg
op_star
id|cfg
comma
r_int
id|no
)paren
suffix:semicolon
r_extern
r_void
id|s3c24xx_init_clocks
c_func
(paren
r_int
id|xtal
)paren
suffix:semicolon
multiline_comment|/* the board structure is used at first initialsation time&n; * to get info such as the devices to register for this&n; * board. This is done because platfrom_add_devices() cannot&n; * be called from the map_io entry.&n;*/
DECL|struct|s3c24xx_board
r_struct
id|s3c24xx_board
(brace
DECL|member|devices
r_struct
id|platform_device
op_star
op_star
id|devices
suffix:semicolon
DECL|member|devices_count
r_int
r_int
id|devices_count
suffix:semicolon
DECL|member|clocks
r_struct
id|clk
op_star
op_star
id|clocks
suffix:semicolon
DECL|member|clocks_count
r_int
r_int
id|clocks_count
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|s3c24xx_set_board
c_func
(paren
r_struct
id|s3c24xx_board
op_star
id|board
)paren
suffix:semicolon
multiline_comment|/* timer for 2410/2440 */
r_struct
id|sys_timer
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|s3c24xx_timer
suffix:semicolon
multiline_comment|/* system device classes */
r_extern
r_struct
id|sysdev_class
id|s3c2440_sysclass
suffix:semicolon
eof
