multiline_comment|/* $Id: auxio.h,v 1.18 1997/11/07 15:01:45 jj Exp $&n; * auxio.h:  Definitions and code for the Auxiliary I/O register.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_AUXIO_H
DECL|macro|_SPARC_AUXIO_H
mdefine_line|#define _SPARC_AUXIO_H
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
multiline_comment|/* This register is an unsigned char in IO space.  It does two things.&n; * First, it is used to control the front panel LED light on machines&n; * that have it (good for testing entry points to trap handlers and irq&squot;s)&n; * Secondly, it controls various floppy drive parameters.&n; */
DECL|macro|AUXIO_ORMEIN
mdefine_line|#define AUXIO_ORMEIN      0xf0    /* All writes must set these bits. */
DECL|macro|AUXIO_ORMEIN4M
mdefine_line|#define AUXIO_ORMEIN4M    0xc0    /* sun4m - All writes must set these bits. */
DECL|macro|AUXIO_FLPY_DENS
mdefine_line|#define AUXIO_FLPY_DENS   0x20    /* Floppy density, high if set. Read only. */
DECL|macro|AUXIO_FLPY_DCHG
mdefine_line|#define AUXIO_FLPY_DCHG   0x10    /* A disk change occurred.  Read only. */
DECL|macro|AUXIO_EDGE_ON
mdefine_line|#define AUXIO_EDGE_ON     0x10    /* sun4m - On means Jumper block is in. */
DECL|macro|AUXIO_FLPY_DSEL
mdefine_line|#define AUXIO_FLPY_DSEL   0x08    /* Drive select/start-motor. Write only. */
DECL|macro|AUXIO_LINK_TEST
mdefine_line|#define AUXIO_LINK_TEST   0x08    /* sun4m - On means TPE Carrier detect. */
multiline_comment|/* Set the following to one, then zero, after doing a pseudo DMA transfer. */
DECL|macro|AUXIO_FLPY_TCNT
mdefine_line|#define AUXIO_FLPY_TCNT   0x04    /* Floppy terminal count. Write only. */
multiline_comment|/* Set the following to zero to eject the floppy. */
DECL|macro|AUXIO_FLPY_EJCT
mdefine_line|#define AUXIO_FLPY_EJCT   0x02    /* Eject floppy disk.  Write only. */
DECL|macro|AUXIO_LED
mdefine_line|#define AUXIO_LED         0x01    /* On if set, off if unset. Read/Write */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* &n; * NOTE: these routines are implementation dependent-- &n; * understand the hardware you are querying! &n; */
r_extern
r_void
id|set_auxio
c_func
(paren
r_int
r_char
id|bits_on
comma
r_int
r_char
id|bits_off
)paren
suffix:semicolon
r_extern
r_int
r_char
id|get_auxio
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* .../asm-sparc/floppy.h */
multiline_comment|/*&n; * The following routines are provided for driver-compatibility&n; * with sparc64 (primarily sunlance.c)&n; */
DECL|macro|AUXIO_LTE_ON
mdefine_line|#define AUXIO_LTE_ON    1
DECL|macro|AUXIO_LTE_OFF
mdefine_line|#define AUXIO_LTE_OFF   0
multiline_comment|/* auxio_set_lte - Set Link Test Enable (TPE Link Detect)&n; *&n; * on - AUXIO_LTE_ON or AUXIO_LTE_OFF&n; */
DECL|macro|auxio_set_lte
mdefine_line|#define auxio_set_lte(on) &bslash;&n;do { &bslash;&n;&t;if(on) { &bslash;&n;&t;&t;set_auxio(AUXIO_LINK_TEST, 0); &bslash;&n;&t;} else { &bslash;&n;&t;&t;set_auxio(0, AUXIO_LINK_TEST); &bslash;&n;&t;} &bslash;&n;} while (0)
DECL|macro|AUXIO_LED_ON
mdefine_line|#define AUXIO_LED_ON    1
DECL|macro|AUXIO_LED_OFF
mdefine_line|#define AUXIO_LED_OFF   0
multiline_comment|/* auxio_set_led - Set system front panel LED&n; *&n; * on - AUXIO_LED_ON or AUXIO_LED_OFF&n; */
DECL|macro|auxio_set_led
mdefine_line|#define auxio_set_led(on) &bslash;&n;do { &bslash;&n;&t;if(on) { &bslash;&n;&t;&t;set_auxio(AUXIO_LED, 0); &bslash;&n;&t;} else { &bslash;&n;&t;&t;set_auxio(0, AUXIO_LED); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* AUXIO2 (Power Off Control) */
r_extern
id|__volatile__
r_int
r_char
op_star
id|auxio_power_register
suffix:semicolon
DECL|macro|AUXIO_POWER_DETECT_FAILURE
mdefine_line|#define&t;AUXIO_POWER_DETECT_FAILURE&t;32
DECL|macro|AUXIO_POWER_CLEAR_FAILURE
mdefine_line|#define&t;AUXIO_POWER_CLEAR_FAILURE&t;2
DECL|macro|AUXIO_POWER_OFF
mdefine_line|#define&t;AUXIO_POWER_OFF&t;&t;&t;1
macro_line|#endif /* !(_SPARC_AUXIO_H) */
eof
