multiline_comment|/*&n; *  Definitions for the SCOOP interface found on various Sharp PDAs&n; *&n; *  Copyright (c) 2004 Richard Purdie&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; *&n; */
DECL|macro|SCOOP_MCR
mdefine_line|#define SCOOP_MCR  0x00
DECL|macro|SCOOP_CDR
mdefine_line|#define SCOOP_CDR  0x04
DECL|macro|SCOOP_CSR
mdefine_line|#define SCOOP_CSR  0x08
DECL|macro|SCOOP_CPR
mdefine_line|#define SCOOP_CPR  0x0C
DECL|macro|SCOOP_CCR
mdefine_line|#define SCOOP_CCR  0x10
DECL|macro|SCOOP_IRR
mdefine_line|#define SCOOP_IRR  0x14
DECL|macro|SCOOP_IRM
mdefine_line|#define SCOOP_IRM  0x14
DECL|macro|SCOOP_IMR
mdefine_line|#define SCOOP_IMR  0x18
DECL|macro|SCOOP_ISR
mdefine_line|#define SCOOP_ISR  0x1C
DECL|macro|SCOOP_GPCR
mdefine_line|#define SCOOP_GPCR 0x20
DECL|macro|SCOOP_GPWR
mdefine_line|#define SCOOP_GPWR 0x24
DECL|macro|SCOOP_GPRR
mdefine_line|#define SCOOP_GPRR 0x28
DECL|macro|SCOOP_GPCR_PA22
mdefine_line|#define SCOOP_GPCR_PA22&t;( 1 &lt;&lt; 12 )
DECL|macro|SCOOP_GPCR_PA21
mdefine_line|#define SCOOP_GPCR_PA21&t;( 1 &lt;&lt; 11 )
DECL|macro|SCOOP_GPCR_PA20
mdefine_line|#define SCOOP_GPCR_PA20&t;( 1 &lt;&lt; 10 )
DECL|macro|SCOOP_GPCR_PA19
mdefine_line|#define SCOOP_GPCR_PA19&t;( 1 &lt;&lt; 9 )
DECL|macro|SCOOP_GPCR_PA18
mdefine_line|#define SCOOP_GPCR_PA18&t;( 1 &lt;&lt; 8 )
DECL|macro|SCOOP_GPCR_PA17
mdefine_line|#define SCOOP_GPCR_PA17&t;( 1 &lt;&lt; 7 )
DECL|macro|SCOOP_GPCR_PA16
mdefine_line|#define SCOOP_GPCR_PA16&t;( 1 &lt;&lt; 6 )
DECL|macro|SCOOP_GPCR_PA15
mdefine_line|#define SCOOP_GPCR_PA15&t;( 1 &lt;&lt; 5 )
DECL|macro|SCOOP_GPCR_PA14
mdefine_line|#define SCOOP_GPCR_PA14&t;( 1 &lt;&lt; 4 )
DECL|macro|SCOOP_GPCR_PA13
mdefine_line|#define SCOOP_GPCR_PA13&t;( 1 &lt;&lt; 3 )
DECL|macro|SCOOP_GPCR_PA12
mdefine_line|#define SCOOP_GPCR_PA12&t;( 1 &lt;&lt; 2 )
DECL|macro|SCOOP_GPCR_PA11
mdefine_line|#define SCOOP_GPCR_PA11&t;( 1 &lt;&lt; 1 )
DECL|struct|scoop_config
r_struct
id|scoop_config
(brace
DECL|member|io_out
r_int
r_int
id|io_out
suffix:semicolon
DECL|member|io_dir
r_int
r_int
id|io_dir
suffix:semicolon
)brace
suffix:semicolon
r_void
id|reset_scoop
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|set_scoop_gpio
c_func
(paren
r_int
r_int
id|bit
)paren
suffix:semicolon
r_int
r_int
id|reset_scoop_gpio
c_func
(paren
r_int
r_int
id|bit
)paren
suffix:semicolon
r_int
r_int
id|read_scoop_reg
c_func
(paren
r_int
r_int
id|reg
)paren
suffix:semicolon
r_void
id|write_scoop_reg
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|data
)paren
suffix:semicolon
eof
