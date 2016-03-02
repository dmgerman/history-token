multiline_comment|/* arch/arm/mach-s3c2410/cpu.h&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Header file for S3C24XX CPU support&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     24-Aug-2004 BJD  Start of generic S3C24XX support&n; *     18-Oct-2004 BJD  Moved board struct into this file&n;*/
DECL|macro|IODESC_ENT
mdefine_line|#define IODESC_ENT(x) { S3C2410_VA_##x, S3C2410_PA_##x, S3C2410_SZ_##x, MT_DEVICE }
macro_line|#ifndef MHZ
DECL|macro|MHZ
mdefine_line|#define MHZ (1000*1000)
macro_line|#endif
DECL|macro|print_mhz
mdefine_line|#define print_mhz(m) ((m) / MHZ), ((m / 1000) % 1000)
macro_line|#ifdef CONFIG_CPU_S3C2410
r_extern
r_int
id|s3c2410_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|s3c2410_map_io
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
macro_line|#else
DECL|macro|s3c2410_map_io
mdefine_line|#define s3c2410_map_io NULL
DECL|macro|s3c2410_init
mdefine_line|#define s3c2410_init NULL
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_S3C2440
r_extern
r_int
id|s3c2440_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|s3c2440_map_io
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
macro_line|#else
DECL|macro|s3c2440_map_io
mdefine_line|#define s3c2440_map_io NULL
DECL|macro|s3c2440_init
mdefine_line|#define s3c2440_init NULL
macro_line|#endif
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
eof
