multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *  linux/include/asm-arm/arch-l7200/pmpcon.h&n; *&n; *   Registers and  helper functions for the L7200 Link-Up Systems&n; *   DC/DC converter register.&n; *&n; *   (C) Copyright 2000, S A McConnell  (samcconn@cotw.com)&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
multiline_comment|/****************************************************************************/
DECL|macro|PMPCON_OFF
mdefine_line|#define PMPCON_OFF 0x00006000  /* Offset from IO_START_2. */
multiline_comment|/* IO_START_2 and IO_BASE_2 are defined in hardware.h */
DECL|macro|PMPCON_START
mdefine_line|#define PMPCON_START (IO_START_2 + PMPCON_OFF)  /* Physical address of reg. */
DECL|macro|PMPCON_BASE
mdefine_line|#define PMPCON_BASE  (IO_BASE_2  + PMPCON_OFF)  /* Virtual address of reg. */
DECL|macro|PMPCON
mdefine_line|#define PMPCON (*(volatile unsigned int *)(PMPCON_BASE))
DECL|macro|PWM2_50CYCLE
mdefine_line|#define PWM2_50CYCLE 0x800
DECL|macro|CONTRAST
mdefine_line|#define CONTRAST     0x9
DECL|macro|PWM1H
mdefine_line|#define PWM1H (CONTRAST)
DECL|macro|PWM1L
mdefine_line|#define PWM1L (CONTRAST &lt;&lt; 4)
DECL|macro|PMPCON_VALUE
mdefine_line|#define PMPCON_VALUE  (PWM2_50CYCLE | PWM1L | PWM1H) 
multiline_comment|/* PMPCON = 0x811;   // too light and fuzzy&n; * PMPCON = 0x844;   &n; * PMPCON = 0x866;   // better color poor depth&n; * PMPCON = 0x888;   // Darker but better depth &n; * PMPCON = 0x899;   // Darker even better depth&n; * PMPCON = 0x8aa;   // too dark even better depth&n; * PMPCON = 0X8cc;   // Way too dark&n; */
multiline_comment|/* As CONTRAST value increases the greater the depth perception and&n; * the darker the colors.&n; */
eof
