macro_line|#ifndef _ASM_IA64_SN_SN_SAL_H
DECL|macro|_ASM_IA64_SN_SN_SAL_H
mdefine_line|#define _ASM_IA64_SN_SN_SAL_H
multiline_comment|/*&n; * System Abstraction Layer definitions for IA64&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
singleline_comment|// SGI Specific Calls
DECL|macro|SN_SAL_POD_MODE
mdefine_line|#define  SN_SAL_POD_MODE                           0x02000001
DECL|macro|SN_SAL_SYSTEM_RESET
mdefine_line|#define  SN_SAL_SYSTEM_RESET                       0x02000002
DECL|macro|SN_SAL_PROBE
mdefine_line|#define  SN_SAL_PROBE                              0x02000003
DECL|macro|SN_SAL_GET_MASTER_NASID
mdefine_line|#define  SN_SAL_GET_MASTER_NASID                   0x02000004
DECL|macro|SN_SAL_GET_KLCONFIG_ADDR
mdefine_line|#define&t; SN_SAL_GET_KLCONFIG_ADDR&t;&t;   0x02000005
DECL|macro|SN_SAL_LOG_CE
mdefine_line|#define  SN_SAL_LOG_CE&t;&t;&t;&t;   0x02000006
DECL|macro|SN_SAL_REGISTER_CE
mdefine_line|#define  SN_SAL_REGISTER_CE&t;&t;&t;   0x02000007
DECL|macro|SN_SAL_GET_PARTITION_ADDR
mdefine_line|#define  SN_SAL_GET_PARTITION_ADDR&t;&t;   0x02000009
DECL|macro|SN_SAL_XP_ADDR_REGION
mdefine_line|#define  SN_SAL_XP_ADDR_REGION&t;&t;&t;   0x0200000f
DECL|macro|SN_SAL_NO_FAULT_ZONE_VIRTUAL
mdefine_line|#define  SN_SAL_NO_FAULT_ZONE_VIRTUAL&t;&t;   0x02000010
DECL|macro|SN_SAL_NO_FAULT_ZONE_PHYSICAL
mdefine_line|#define  SN_SAL_NO_FAULT_ZONE_PHYSICAL&t;&t;   0x02000011
DECL|macro|SN_SAL_PRINT_ERROR
mdefine_line|#define  SN_SAL_PRINT_ERROR&t;&t;&t;   0x02000012
DECL|macro|SN_SAL_CONSOLE_PUTC
mdefine_line|#define  SN_SAL_CONSOLE_PUTC                       0x02000021
DECL|macro|SN_SAL_CONSOLE_GETC
mdefine_line|#define  SN_SAL_CONSOLE_GETC                       0x02000022
DECL|macro|SN_SAL_CONSOLE_PUTS
mdefine_line|#define  SN_SAL_CONSOLE_PUTS                       0x02000023
DECL|macro|SN_SAL_CONSOLE_GETS
mdefine_line|#define  SN_SAL_CONSOLE_GETS                       0x02000024
DECL|macro|SN_SAL_CONSOLE_GETS_TIMEOUT
mdefine_line|#define  SN_SAL_CONSOLE_GETS_TIMEOUT               0x02000025
DECL|macro|SN_SAL_CONSOLE_POLL
mdefine_line|#define  SN_SAL_CONSOLE_POLL                       0x02000026
DECL|macro|SN_SAL_CONSOLE_INTR
mdefine_line|#define  SN_SAL_CONSOLE_INTR                       0x02000027
DECL|macro|SN_SAL_CONSOLE_PUTB
mdefine_line|#define  SN_SAL_CONSOLE_PUTB&t;&t;&t;   0x02000028
DECL|macro|SN_SAL_CONSOLE_XMIT_CHARS
mdefine_line|#define  SN_SAL_CONSOLE_XMIT_CHARS&t;&t;   0x0200002a
DECL|macro|SN_SAL_CONSOLE_READC
mdefine_line|#define  SN_SAL_CONSOLE_READC&t;&t;&t;   0x0200002b
DECL|macro|SN_SAL_SYSCTL_MODID_GET
mdefine_line|#define  SN_SAL_SYSCTL_MODID_GET&t;           0x02000031
DECL|macro|SN_SAL_SYSCTL_GET
mdefine_line|#define  SN_SAL_SYSCTL_GET                         0x02000032
DECL|macro|SN_SAL_SYSCTL_IOBRICK_MODULE_GET
mdefine_line|#define  SN_SAL_SYSCTL_IOBRICK_MODULE_GET          0x02000033
DECL|macro|SN_SAL_SYSCTL_IO_PORTSPEED_GET
mdefine_line|#define  SN_SAL_SYSCTL_IO_PORTSPEED_GET            0x02000035
DECL|macro|SN_SAL_SYSCTL_SLAB_GET
mdefine_line|#define  SN_SAL_SYSCTL_SLAB_GET                    0x02000036
DECL|macro|SN_SAL_BUS_CONFIG
mdefine_line|#define  SN_SAL_BUS_CONFIG&t;&t;   &t;   0x02000037
DECL|macro|SN_SAL_SYS_SERIAL_GET
mdefine_line|#define  SN_SAL_SYS_SERIAL_GET&t;&t;&t;   0x02000038
DECL|macro|SN_SAL_PARTITION_SERIAL_GET
mdefine_line|#define  SN_SAL_PARTITION_SERIAL_GET&t;&t;   0x02000039
DECL|macro|SN_SAL_SYSCTL_PARTITION_GET
mdefine_line|#define  SN_SAL_SYSCTL_PARTITION_GET&t;&t;   0x0200003a
DECL|macro|SN_SAL_SYSTEM_POWER_DOWN
mdefine_line|#define  SN_SAL_SYSTEM_POWER_DOWN&t;&t;   0x0200003b
DECL|macro|SN_SAL_GET_MASTER_BASEIO_NASID
mdefine_line|#define  SN_SAL_GET_MASTER_BASEIO_NASID&t;&t;   0x0200003c
DECL|macro|SN_SAL_COHERENCE
mdefine_line|#define  SN_SAL_COHERENCE                          0x0200003d
DECL|macro|SN_SAL_MEMPROTECT
mdefine_line|#define  SN_SAL_MEMPROTECT                         0x0200003e
DECL|macro|SN_SAL_SYSCTL_FRU_CAPTURE
mdefine_line|#define  SN_SAL_SYSCTL_FRU_CAPTURE&t;&t;   0x0200003f
multiline_comment|/*&n; * Service-specific constants&n; */
multiline_comment|/* Console interrupt manipulation */
multiline_comment|/* action codes */
DECL|macro|SAL_CONSOLE_INTR_OFF
mdefine_line|#define SAL_CONSOLE_INTR_OFF    0       /* turn the interrupt off */
DECL|macro|SAL_CONSOLE_INTR_ON
mdefine_line|#define SAL_CONSOLE_INTR_ON     1       /* turn the interrupt on */
DECL|macro|SAL_CONSOLE_INTR_STATUS
mdefine_line|#define SAL_CONSOLE_INTR_STATUS 2&t;/* retrieve the interrupt status */
multiline_comment|/* interrupt specification &amp; status return codes */
DECL|macro|SAL_CONSOLE_INTR_XMIT
mdefine_line|#define SAL_CONSOLE_INTR_XMIT&t;1&t;/* output interrupt */
DECL|macro|SAL_CONSOLE_INTR_RECV
mdefine_line|#define SAL_CONSOLE_INTR_RECV&t;2&t;/* input interrupt */
multiline_comment|/*&n; * SN_SAL_GET_PARTITION_ADDR return constants&n; */
DECL|macro|SALRET_MORE_PASSES
mdefine_line|#define SALRET_MORE_PASSES&t;1
DECL|macro|SALRET_OK
mdefine_line|#define SALRET_OK&t;&t;0
DECL|macro|SALRET_INVALID_ARG
mdefine_line|#define SALRET_INVALID_ARG&t;-2
DECL|macro|SALRET_ERROR
mdefine_line|#define SALRET_ERROR&t;&t;-3
multiline_comment|/**&n; * sn_sal_rev_major - get the major SGI SAL revision number&n; *&n; * The SGI PROM stores its version in sal_[ab]_rev_(major|minor).&n; * This routine simply extracts the major value from the&n; * @ia64_sal_systab structure constructed by ia64_sal_init().&n; */
r_static
r_inline
r_int
DECL|function|sn_sal_rev_major
id|sn_sal_rev_major
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_systab
op_star
id|systab
op_assign
id|efi.sal_systab
suffix:semicolon
r_return
(paren
r_int
)paren
id|systab-&gt;sal_b_rev_major
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_sal_rev_minor - get the minor SGI SAL revision number&n; *&n; * The SGI PROM stores its version in sal_[ab]_rev_(major|minor).&n; * This routine simply extracts the minor value from the&n; * @ia64_sal_systab structure constructed by ia64_sal_init().&n; */
r_static
r_inline
r_int
DECL|function|sn_sal_rev_minor
id|sn_sal_rev_minor
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_systab
op_star
id|systab
op_assign
id|efi.sal_systab
suffix:semicolon
r_return
(paren
r_int
)paren
id|systab-&gt;sal_b_rev_minor
suffix:semicolon
)brace
multiline_comment|/*&n; * Specify the minimum PROM revsion required for this kernel.&n; * Note that they&squot;re stored in hex format...&n; */
DECL|macro|SN_SAL_MIN_MAJOR
mdefine_line|#define SN_SAL_MIN_MAJOR&t;0x1  /* SN2 kernels need at least PROM 1.0 */
DECL|macro|SN_SAL_MIN_MINOR
mdefine_line|#define SN_SAL_MIN_MINOR&t;0x0
id|u64
id|ia64_sn_probe_io_slot
c_func
(paren
r_int
id|paddr
comma
r_int
id|size
comma
r_void
op_star
id|data_ptr
)paren
suffix:semicolon
multiline_comment|/*&n; * Returns the master console nasid, if the call fails, return an illegal&n; * value.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_get_console_nasid
id|ia64_sn_get_console_nasid
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_GET_MASTER_NASID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_stuff.status
OL
l_int|0
)paren
r_return
id|ret_stuff.status
suffix:semicolon
multiline_comment|/* Master console nasid is in &squot;v0&squot; */
r_return
id|ret_stuff.v0
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns the master baseio nasid, if the call fails, return an illegal&n; * value.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_get_master_baseio_nasid
id|ia64_sn_get_master_baseio_nasid
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_GET_MASTER_BASEIO_NASID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_stuff.status
OL
l_int|0
)paren
r_return
id|ret_stuff.status
suffix:semicolon
multiline_comment|/* Master baseio nasid is in &squot;v0&squot; */
r_return
id|ret_stuff.v0
suffix:semicolon
)brace
r_static
r_inline
id|u64
DECL|function|ia64_sn_get_klconfig_addr
id|ia64_sn_get_klconfig_addr
c_func
(paren
id|nasid_t
id|nasid
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
r_extern
id|u64
id|klgraph_addr
(braket
)braket
suffix:semicolon
r_int
id|cnodeid
suffix:semicolon
id|cnodeid
op_assign
id|nasid_to_cnodeid
c_func
(paren
id|nasid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|klgraph_addr
(braket
id|cnodeid
)braket
op_eq
l_int|0
)paren
(brace
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_GET_KLCONFIG_ADDR
comma
(paren
id|u64
)paren
id|nasid
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; &t;* We should panic if a valid cnode nasid does not produce&n;&t; &t;* a klconfig address.&n;&t; &t;*/
r_if
c_cond
(paren
id|ret_stuff.status
op_ne
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;ia64_sn_get_klconfig_addr: Returned error %lx&bslash;n&quot;
comma
id|ret_stuff.status
)paren
suffix:semicolon
)brace
id|klgraph_addr
(braket
id|cnodeid
)braket
op_assign
id|ret_stuff.v0
suffix:semicolon
)brace
r_return
id|klgraph_addr
(braket
id|cnodeid
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns the next console character.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_console_getc
id|ia64_sn_console_getc
c_func
(paren
r_int
op_star
id|ch
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_GETC
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* character is in &squot;v0&squot; */
op_star
id|ch
op_assign
(paren
r_int
)paren
id|ret_stuff.v0
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a character from the SAL console device, after a previous interrupt&n; * or poll operation has given us to know that a character is available&n; * to be read.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_console_readc
id|ia64_sn_console_readc
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_READC
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* character is in &squot;v0&squot; */
r_return
id|ret_stuff.v0
suffix:semicolon
)brace
multiline_comment|/*&n; * Sends the given character to the console.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_console_putc
id|ia64_sn_console_putc
c_func
(paren
r_char
id|ch
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_PUTC
comma
(paren
r_uint64
)paren
id|ch
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Sends the given buffer to the console.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_console_putb
id|ia64_sn_console_putb
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_PUTB
comma
(paren
r_uint64
)paren
id|buf
comma
(paren
r_uint64
)paren
id|len
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_stuff.status
op_eq
l_int|0
)paren
(brace
r_return
id|ret_stuff.v0
suffix:semicolon
)brace
r_return
(paren
id|u64
)paren
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Print a platform error record&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_plat_specific_err_print
id|ia64_sn_plat_specific_err_print
c_func
(paren
r_int
(paren
op_star
id|hook
)paren
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
comma
r_char
op_star
id|rec
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_PRINT_ERROR
comma
(paren
r_uint64
)paren
id|hook
comma
(paren
r_uint64
)paren
id|rec
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Check for Platform errors&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_plat_cpei_handler
id|ia64_sn_plat_cpei_handler
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_LOG_CE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Checks for console input.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_console_check
id|ia64_sn_console_check
c_func
(paren
r_int
op_star
id|result
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_POLL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* result is in &squot;v0&squot; */
op_star
id|result
op_assign
(paren
r_int
)paren
id|ret_stuff.v0
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Checks console interrupt status&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_console_intr_status
id|ia64_sn_console_intr_status
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_INTR
comma
l_int|0
comma
id|SAL_CONSOLE_INTR_STATUS
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_stuff.status
op_eq
l_int|0
)paren
(brace
r_return
id|ret_stuff.v0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Enable an interrupt on the SAL console device.&n; */
r_static
r_inline
r_void
DECL|function|ia64_sn_console_intr_enable
id|ia64_sn_console_intr_enable
c_func
(paren
r_uint64
id|intr
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_INTR
comma
id|intr
comma
id|SAL_CONSOLE_INTR_ON
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Disable an interrupt on the SAL console device.&n; */
r_static
r_inline
r_void
DECL|function|ia64_sn_console_intr_disable
id|ia64_sn_console_intr_disable
c_func
(paren
r_uint64
id|intr
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_INTR
comma
id|intr
comma
id|SAL_CONSOLE_INTR_OFF
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Sends a character buffer to the console asynchronously.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_console_xmit_chars
id|ia64_sn_console_xmit_chars
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_CONSOLE_XMIT_CHARS
comma
(paren
r_uint64
)paren
id|buf
comma
(paren
r_uint64
)paren
id|len
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_stuff.status
op_eq
l_int|0
)paren
(brace
r_return
id|ret_stuff.v0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns the iobrick module Id&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_sysctl_iobrick_module_get
id|ia64_sn_sysctl_iobrick_module_get
c_func
(paren
id|nasid_t
id|nasid
comma
r_int
op_star
id|result
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v1
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v2
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_SYSCTL_IOBRICK_MODULE_GET
comma
id|nasid
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* result is in &squot;v0&squot; */
op_star
id|result
op_assign
(paren
r_int
)paren
id|ret_stuff.v0
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/**&n; * ia64_sn_pod_mode - call the SN_SAL_POD_MODE function&n; *&n; * SN_SAL_POD_MODE actually takes an argument, but it&squot;s always&n; * 0 when we call it from the kernel, so we don&squot;t have to expose&n; * it to the caller.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_pod_mode
id|ia64_sn_pod_mode
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|isrv
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|isrv
comma
id|SN_SAL_POD_MODE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isrv.status
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|isrv.v0
suffix:semicolon
)brace
multiline_comment|/*&n; * Retrieve the system serial number as an ASCII string.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_sys_serial_get
id|ia64_sn_sys_serial_get
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_SYS_SERIAL_GET
comma
id|buf
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
r_extern
r_char
id|sn_system_serial_number_string
(braket
)braket
suffix:semicolon
r_extern
id|u64
id|sn_partition_serial_number
suffix:semicolon
r_static
r_inline
r_char
op_star
DECL|function|sn_system_serial_number
id|sn_system_serial_number
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|sn_system_serial_number_string
(braket
l_int|0
)braket
)paren
(brace
r_return
id|sn_system_serial_number_string
suffix:semicolon
)brace
r_else
(brace
id|ia64_sn_sys_serial_get
c_func
(paren
id|sn_system_serial_number_string
)paren
suffix:semicolon
r_return
id|sn_system_serial_number_string
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Returns a unique id number for this system and partition (suitable for&n; * use with license managers), based in part on the system serial number.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_partition_serial_get
id|ia64_sn_partition_serial_get
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_PARTITION_SERIAL_GET
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_stuff.status
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ret_stuff.v0
suffix:semicolon
)brace
r_static
r_inline
id|u64
DECL|function|sn_partition_serial_number_val
id|sn_partition_serial_number_val
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|sn_partition_serial_number
)paren
(brace
r_return
id|sn_partition_serial_number
suffix:semicolon
)brace
r_else
(brace
r_return
id|sn_partition_serial_number
op_assign
id|ia64_sn_partition_serial_get
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Returns the partition id of the nasid passed in as an argument,&n; * or INVALID_PARTID if the partition id cannot be retrieved.&n; */
r_static
r_inline
id|partid_t
DECL|function|ia64_sn_sysctl_partition_get
id|ia64_sn_sysctl_partition_get
c_func
(paren
id|nasid_t
id|nasid
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_SYSCTL_PARTITION_GET
comma
id|nasid
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_stuff.status
op_ne
l_int|0
)paren
r_return
id|INVALID_PARTID
suffix:semicolon
r_return
(paren
(paren
id|partid_t
)paren
id|ret_stuff.v0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns the partition id of the current processor.&n; */
r_extern
id|partid_t
id|sn_partid
suffix:semicolon
r_static
r_inline
id|partid_t
DECL|function|sn_local_partid
id|sn_local_partid
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|sn_partid
OL
l_int|0
)paren
(brace
r_return
(paren
id|sn_partid
op_assign
id|ia64_sn_sysctl_partition_get
c_func
(paren
id|cpuid_to_nasid
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|sn_partid
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Register or unregister a physical address range being referenced across&n; * a partition boundary for which certain SAL errors should be scanned for,&n; * cleaned up and ignored.  This is of value for kernel partitioning code only.&n; * Values for the operation argument:&n; *&t;1 = register this address range with SAL&n; *&t;0 = unregister this address range with SAL&n; * &n; * SAL maintains a reference count on an address range in case it is registered&n; * multiple times.&n; * &n; * On success, returns the reference count of the address range after the SAL&n; * call has performed the current registration/unregistration.  Returns a&n; * negative value if an error occurred.&n; */
r_static
r_inline
r_int
DECL|function|sn_register_xp_addr_region
id|sn_register_xp_addr_region
c_func
(paren
id|u64
id|paddr
comma
id|u64
id|len
comma
r_int
id|operation
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_XP_ADDR_REGION
comma
id|paddr
comma
id|len
comma
(paren
id|u64
)paren
id|operation
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Register or unregister an instruction range for which SAL errors should&n; * be ignored.  If an error occurs while in the registered range, SAL jumps&n; * to return_addr after ignoring the error.  Values for the operation argument:&n; *&t;1 = register this instruction range with SAL&n; *&t;0 = unregister this instruction range with SAL&n; *&n; * Returns 0 on success, or a negative value if an error occurred.&n; */
r_static
r_inline
r_int
DECL|function|sn_register_nofault_code
id|sn_register_nofault_code
c_func
(paren
id|u64
id|start_addr
comma
id|u64
id|end_addr
comma
id|u64
id|return_addr
comma
r_int
r_virtual
comma
r_int
id|operation
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|u64
id|call
suffix:semicolon
r_if
c_cond
(paren
r_virtual
)paren
(brace
id|call
op_assign
id|SN_SAL_NO_FAULT_ZONE_VIRTUAL
suffix:semicolon
)brace
r_else
(brace
id|call
op_assign
id|SN_SAL_NO_FAULT_ZONE_PHYSICAL
suffix:semicolon
)brace
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|call
comma
id|start_addr
comma
id|end_addr
comma
id|return_addr
comma
(paren
id|u64
)paren
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Change or query the coherence domain for this partition. Each cpu-based&n; * nasid is represented by a bit in an array of 64-bit words:&n; *      0 = not in this partition&squot;s coherency domain&n; *      1 = in this partition&squot;s coherency domain&n; *&n; * It is not possible for the local system&squot;s nasids to be removed from&n; * the coherency domain.  Purpose of the domain arguments:&n; *      new_domain = set the coherence domain to the given nasids&n; *      old_domain = return the current coherence domain&n; *&n; * Returns 0 on success, or a negative value if an error occurred.&n; */
r_static
r_inline
r_int
DECL|function|sn_change_coherence
id|sn_change_coherence
c_func
(paren
id|u64
op_star
id|new_domain
comma
id|u64
op_star
id|old_domain
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_COHERENCE
comma
id|new_domain
comma
id|old_domain
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Change memory access protections for a physical address range.&n; * nasid_array is not used on Altix, but may be in future architectures.&n; * Available memory protection access classes are defined after the function.&n; */
r_static
r_inline
r_int
DECL|function|sn_change_memprotect
id|sn_change_memprotect
c_func
(paren
id|u64
id|paddr
comma
id|u64
id|len
comma
id|u64
id|perms
comma
id|u64
op_star
id|nasid_array
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_MEMPROTECT
comma
id|paddr
comma
id|len
comma
id|nasid_array
comma
id|perms
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
DECL|macro|SN_MEMPROT_ACCESS_CLASS_0
mdefine_line|#define SN_MEMPROT_ACCESS_CLASS_0&t;&t;0x14a080
DECL|macro|SN_MEMPROT_ACCESS_CLASS_1
mdefine_line|#define SN_MEMPROT_ACCESS_CLASS_1&t;&t;0x2520c2
DECL|macro|SN_MEMPROT_ACCESS_CLASS_2
mdefine_line|#define SN_MEMPROT_ACCESS_CLASS_2&t;&t;0x14a1ca
DECL|macro|SN_MEMPROT_ACCESS_CLASS_3
mdefine_line|#define SN_MEMPROT_ACCESS_CLASS_3&t;&t;0x14a290
DECL|macro|SN_MEMPROT_ACCESS_CLASS_6
mdefine_line|#define SN_MEMPROT_ACCESS_CLASS_6&t;&t;0x084080
DECL|macro|SN_MEMPROT_ACCESS_CLASS_7
mdefine_line|#define SN_MEMPROT_ACCESS_CLASS_7&t;&t;0x021080
multiline_comment|/*&n; * Turns off system power.&n; */
r_static
r_inline
r_void
DECL|function|ia64_sn_power_down
id|ia64_sn_power_down
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_SYSTEM_POWER_DOWN
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* never returns */
)brace
multiline_comment|/**&n; * ia64_sn_fru_capture - tell the system controller to capture hw state&n; *&n; * This routine will call the SAL which will tell the system controller(s)&n; * to capture hw mmr information from each SHub in the system.&n; */
r_static
r_inline
id|u64
DECL|function|ia64_sn_fru_capture
id|ia64_sn_fru_capture
c_func
(paren
r_void
)paren
(brace
r_struct
id|ia64_sal_retval
id|isrv
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|isrv
comma
id|SN_SAL_SYSCTL_FRU_CAPTURE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isrv.status
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|isrv.v0
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_SN_SN_SAL_H */
eof
