macro_line|#ifndef _ATARI_SCCSERIAL_H
DECL|macro|_ATARI_SCCSERIAL_H
mdefine_line|#define _ATARI_SCCSERIAL_H
multiline_comment|/* Special configuration ioctls for the Atari SCC5380 Serial&n; * Communications Controller&n; */
multiline_comment|/* ioctl command codes */
DECL|macro|TIOCGATSCC
mdefine_line|#define TIOCGATSCC&t;0x54c0&t;/* get SCC configuration */
DECL|macro|TIOCSATSCC
mdefine_line|#define TIOCSATSCC&t;0x54c1&t;/* set SCC configuration */
DECL|macro|TIOCDATSCC
mdefine_line|#define TIOCDATSCC&t;0x54c2&t;/* reset configuration to defaults */
multiline_comment|/* Clock sources */
DECL|macro|CLK_RTxC
mdefine_line|#define CLK_RTxC&t;0
DECL|macro|CLK_TRxC
mdefine_line|#define CLK_TRxC&t;1
DECL|macro|CLK_PCLK
mdefine_line|#define CLK_PCLK&t;2
multiline_comment|/* baud_bases for the common clocks in the Atari. These are the real&n; * frequencies divided by 16.&n; */
DECL|macro|SCC_BAUD_BASE_TIMC
mdefine_line|#define SCC_BAUD_BASE_TIMC&t;19200&t;/* 0.3072 MHz from TT-MFP, Timer C */
DECL|macro|SCC_BAUD_BASE_BCLK
mdefine_line|#define SCC_BAUD_BASE_BCLK&t;153600&t;/* 2.4576 MHz */
DECL|macro|SCC_BAUD_BASE_PCLK4
mdefine_line|#define SCC_BAUD_BASE_PCLK4&t;229500&t;/* 3.6720 MHz */
DECL|macro|SCC_BAUD_BASE_PCLK
mdefine_line|#define SCC_BAUD_BASE_PCLK&t;503374&t;/* 8.0539763 MHz */
DECL|macro|SCC_BAUD_BASE_NONE
mdefine_line|#define SCC_BAUD_BASE_NONE&t;0&t;&t;/* for not connected or unused&n;&t;&t;&t;&t;&t;&t; * clock sources */
DECL|macro|SCC_BAUD_BASE_M147_PCLK
mdefine_line|#define SCC_BAUD_BASE_M147_PCLK&t;312500&t;/* 5 MHz */
DECL|macro|SCC_BAUD_BASE_M147
mdefine_line|#define SCC_BAUD_BASE_M147&t;312500&t;/* 5 MHz */
DECL|macro|SCC_BAUD_BASE_MVME_PCLK
mdefine_line|#define SCC_BAUD_BASE_MVME_PCLK&t;781250&t;/* 12.5 MHz */
DECL|macro|SCC_BAUD_BASE_MVME
mdefine_line|#define SCC_BAUD_BASE_MVME&t;625000&t;/* 10.000 MHz */
DECL|macro|SCC_BAUD_BASE_BVME_PCLK
mdefine_line|#define SCC_BAUD_BASE_BVME_PCLK&t;781250&t;/* 12.5 MHz */   /* XXX ??? */
DECL|macro|SCC_BAUD_BASE_BVME
mdefine_line|#define SCC_BAUD_BASE_BVME&t;460800&t;/* 7.3728 MHz */
multiline_comment|/* The SCC configuration structure */
DECL|struct|atari_SCCserial
r_struct
id|atari_SCCserial
(brace
DECL|member|RTxC_base
r_int
id|RTxC_base
suffix:semicolon
multiline_comment|/* base_baud of RTxC */
DECL|member|TRxC_base
r_int
id|TRxC_base
suffix:semicolon
multiline_comment|/* base_baud of TRxC */
DECL|member|PCLK_base
r_int
id|PCLK_base
suffix:semicolon
multiline_comment|/* base_baud of PCLK, for both channels! */
r_struct
(brace
DECL|member|clksrc
r_int
id|clksrc
suffix:semicolon
multiline_comment|/* CLK_RTxC, CLK_TRxC or CLK_PCLK */
DECL|member|divisor
r_int
id|divisor
suffix:semicolon
multiline_comment|/* divisor for base baud, valid values:&n;&t;&t;&t;&t;&t; * see below */
DECL|member|baud_table
)brace
id|baud_table
(braket
l_int|17
)braket
suffix:semicolon
multiline_comment|/* For 50, 75, 110, 135, 150, 200, 300,&n;&t;&t;&t;&t;&t; * 600, 1200, 1800, 2400, 4800, 9600,&n;&t;&t;&t;&t;&t; * 19200, 38400, 57600 and 115200 bps. The&n;&t;&t;&t;&t;&t; * last two could be replaced by other&n;&t;&t;&t;&t;&t; * rates &gt; 38400 if they&squot;re not possible.&n;&t;&t;&t;&t;&t; */
)brace
suffix:semicolon
multiline_comment|/* The following divisors are valid:&n; *&n; *   - CLK_RTxC: 1 or even (1, 2 and 4 are the direct modes, &gt; 4 use&n; *               the BRG)&n; *&n; *   - CLK_TRxC: 1, 2 or 4 (no BRG, only direct modes possible)&n; *&n; *   - CLK_PCLK: &gt;= 4 and even (no direct modes, only BRG)&n; *&n; */
macro_line|#endif /* _ATARI_SCCSERIAL_H */
eof
