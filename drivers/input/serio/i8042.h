macro_line|#ifndef _I8042_H
DECL|macro|_I8042_H
mdefine_line|#define _I8042_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *  Copyright (c) 1999-2002 Vojtech Pavlik&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
multiline_comment|/*&n; * Arch-dependent inline functions and defines.&n; */
macro_line|#if defined(CONFIG_MACH_JAZZ)
macro_line|#include &quot;i8042-jazzio.h&quot;
macro_line|#elif defined(CONFIG_SGI_IP22)
macro_line|#include &quot;i8042-ip22io.h&quot;
macro_line|#elif defined(CONFIG_PPC)
macro_line|#include &quot;i8042-ppcio.h&quot;
macro_line|#elif defined(CONFIG_SPARC32) || defined(CONFIG_SPARC64)
macro_line|#include &quot;i8042-sparcio.h&quot;
macro_line|#elif defined(CONFIG_X86) || defined(CONFIG_IA64)
macro_line|#include &quot;i8042-x86ia64io.h&quot;
macro_line|#else
macro_line|#include &quot;i8042-io.h&quot;
macro_line|#endif
multiline_comment|/*&n; * This is in 50us units, the time we wait for the i8042 to react. This&n; * has to be long enough for the i8042 itself to timeout on sending a byte&n; * to a non-existent mouse.&n; */
DECL|macro|I8042_CTL_TIMEOUT
mdefine_line|#define I8042_CTL_TIMEOUT&t;10000
multiline_comment|/*&n; * When the device isn&squot;t opened and it&squot;s interrupts aren&squot;t used, we poll it at&n; * regular intervals to see if any characters arrived. If yes, we can start&n; * probing for any mouse / keyboard connected. This is the period of the&n; * polling.&n; */
DECL|macro|I8042_POLL_PERIOD
mdefine_line|#define I8042_POLL_PERIOD&t;HZ/20
multiline_comment|/*&n; * Status register bits.&n; */
DECL|macro|I8042_STR_PARITY
mdefine_line|#define I8042_STR_PARITY&t;0x80
DECL|macro|I8042_STR_TIMEOUT
mdefine_line|#define I8042_STR_TIMEOUT&t;0x40
DECL|macro|I8042_STR_AUXDATA
mdefine_line|#define I8042_STR_AUXDATA&t;0x20
DECL|macro|I8042_STR_KEYLOCK
mdefine_line|#define I8042_STR_KEYLOCK&t;0x10
DECL|macro|I8042_STR_CMDDAT
mdefine_line|#define I8042_STR_CMDDAT&t;0x08
DECL|macro|I8042_STR_MUXERR
mdefine_line|#define I8042_STR_MUXERR&t;0x04
DECL|macro|I8042_STR_IBF
mdefine_line|#define I8042_STR_IBF&t;&t;0x02
DECL|macro|I8042_STR_OBF
mdefine_line|#define&t;I8042_STR_OBF&t;&t;0x01
multiline_comment|/*&n; * Control register bits.&n; */
DECL|macro|I8042_CTR_KBDINT
mdefine_line|#define I8042_CTR_KBDINT&t;0x01
DECL|macro|I8042_CTR_AUXINT
mdefine_line|#define I8042_CTR_AUXINT&t;0x02
DECL|macro|I8042_CTR_IGNKEYLOCK
mdefine_line|#define I8042_CTR_IGNKEYLOCK&t;0x08
DECL|macro|I8042_CTR_KBDDIS
mdefine_line|#define I8042_CTR_KBDDIS&t;0x10
DECL|macro|I8042_CTR_AUXDIS
mdefine_line|#define I8042_CTR_AUXDIS&t;0x20
DECL|macro|I8042_CTR_XLATE
mdefine_line|#define I8042_CTR_XLATE&t;&t;0x40
multiline_comment|/*&n; * Commands.&n; */
DECL|macro|I8042_CMD_CTL_RCTR
mdefine_line|#define I8042_CMD_CTL_RCTR&t;0x0120
DECL|macro|I8042_CMD_CTL_WCTR
mdefine_line|#define I8042_CMD_CTL_WCTR&t;0x1060
DECL|macro|I8042_CMD_CTL_TEST
mdefine_line|#define I8042_CMD_CTL_TEST&t;0x01aa
DECL|macro|I8042_CMD_KBD_DISABLE
mdefine_line|#define I8042_CMD_KBD_DISABLE&t;0x00ad
DECL|macro|I8042_CMD_KBD_ENABLE
mdefine_line|#define I8042_CMD_KBD_ENABLE&t;0x00ae
DECL|macro|I8042_CMD_KBD_TEST
mdefine_line|#define I8042_CMD_KBD_TEST&t;0x01ab
DECL|macro|I8042_CMD_KBD_LOOP
mdefine_line|#define I8042_CMD_KBD_LOOP&t;0x11d2
DECL|macro|I8042_CMD_AUX_DISABLE
mdefine_line|#define I8042_CMD_AUX_DISABLE&t;0x00a7
DECL|macro|I8042_CMD_AUX_ENABLE
mdefine_line|#define I8042_CMD_AUX_ENABLE&t;0x00a8
DECL|macro|I8042_CMD_AUX_TEST
mdefine_line|#define I8042_CMD_AUX_TEST&t;0x01a9
DECL|macro|I8042_CMD_AUX_SEND
mdefine_line|#define I8042_CMD_AUX_SEND&t;0x10d4
DECL|macro|I8042_CMD_AUX_LOOP
mdefine_line|#define I8042_CMD_AUX_LOOP&t;0x11d3
DECL|macro|I8042_CMD_MUX_PFX
mdefine_line|#define I8042_CMD_MUX_PFX&t;0x0090
DECL|macro|I8042_CMD_MUX_SEND
mdefine_line|#define I8042_CMD_MUX_SEND&t;0x1090
multiline_comment|/*&n; * Return codes.&n; */
DECL|macro|I8042_RET_CTL_TEST
mdefine_line|#define I8042_RET_CTL_TEST&t;0x55
multiline_comment|/*&n; * Expected maximum internal i8042 buffer size. This is used for flushing&n; * the i8042 buffers. 32 should be more than enough.&n; */
DECL|macro|I8042_BUFFER_SIZE
mdefine_line|#define I8042_BUFFER_SIZE&t;32
multiline_comment|/*&n; * Number of AUX ports on controllers supporting active multiplexing&n; * specification&n; */
DECL|macro|I8042_NUM_MUX_PORTS
mdefine_line|#define I8042_NUM_MUX_PORTS&t;4
multiline_comment|/*&n; * Debug.&n; */
macro_line|#ifdef DEBUG
DECL|variable|i8042_start
r_static
r_int
r_int
id|i8042_start
suffix:semicolon
DECL|macro|dbg_init
mdefine_line|#define dbg_init() do { i8042_start = jiffies; } while (0)
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do { &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (i8042_debug)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(KERN_DEBUG __FILE__ &quot;: &quot; format &quot; [%d]&bslash;n&quot; ,&t;&bslash;&n;&t; &t;&t;&t;## arg, (int) (jiffies - i8042_start));&t;&t;&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|dbg_init
mdefine_line|#define dbg_init() do { } while (0)
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) do {} while (0)
macro_line|#endif
macro_line|#endif /* _I8042_H */
eof
