multiline_comment|/* $Id: diva_didd.c,v 1.1.2.6 2001/05/01 15:48:05 armin Exp $&n; *&n; * DIDD Interface module for Eicon active cards.&n; * &n; * Functions are in dadapter.c &n; * &n; * Copyright 2002 by Armin Schindler (mac@melware.de) &n; * Copyright 2002 Cytronics &amp; Melware (info@melware.de)&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;dadapter.h&quot;
macro_line|#include &quot;divasync.h&quot;
macro_line|#include &quot;did_vers.h&quot;
DECL|variable|main_revision
r_static
r_char
op_star
id|main_revision
op_assign
l_string|&quot;$Revision: 1.1.2.6 $&quot;
suffix:semicolon
DECL|variable|DRIVERNAME
r_static
r_char
op_star
id|DRIVERNAME
op_assign
l_string|&quot;Eicon DIVA - DIDD table (http://www.melware.net)&quot;
suffix:semicolon
DECL|variable|DRIVERLNAME
r_static
r_char
op_star
id|DRIVERLNAME
op_assign
l_string|&quot;divadidd&quot;
suffix:semicolon
DECL|variable|DRIVERRELEASE
r_char
op_star
id|DRIVERRELEASE
op_assign
l_string|&quot;2.0&quot;
suffix:semicolon
DECL|variable|dir_in_proc_net
r_static
r_char
op_star
id|dir_in_proc_net
op_assign
l_string|&quot;isdn&quot;
suffix:semicolon
DECL|variable|main_proc_dir
r_static
r_char
op_star
id|main_proc_dir
op_assign
l_string|&quot;eicon&quot;
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;DIDD table driver for diva drivers&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Cytronics &amp; Melware, Eicon Networks&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;Eicon diva drivers&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|MAX_DESCRIPTORS
mdefine_line|#define MAX_DESCRIPTORS  32
DECL|macro|DBG_MINIMUM
mdefine_line|#define DBG_MINIMUM  (DL_LOG + DL_FTL + DL_ERR)
DECL|macro|DBG_DEFAULT
mdefine_line|#define DBG_DEFAULT  (DBG_MINIMUM + DL_XLOG + DL_REG)
r_extern
r_int
id|diddfunc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|diddfunc_finit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|DIVA_DIDD_Read
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|proc_net_isdn
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_net_isdn
suffix:semicolon
DECL|variable|proc_didd
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_didd
suffix:semicolon
DECL|variable|proc_net_isdn_eicon
r_struct
id|proc_dir_entry
op_star
id|proc_net_isdn_eicon
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|DIVA_DIDD_Read
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|DIVA_DIDD_Read
)paren
suffix:semicolon
DECL|variable|proc_net_isdn_eicon
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|proc_net_isdn_eicon
)paren
suffix:semicolon
DECL|function|getrev
r_static
r_char
op_star
id|getrev
c_func
(paren
r_const
r_char
op_star
id|revision
)paren
(brace
r_char
op_star
id|rev
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
)paren
(brace
id|rev
op_assign
id|p
op_plus
l_int|2
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|rev
comma
l_char|&squot;$&squot;
)paren
suffix:semicolon
op_star
op_decrement
id|p
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|rev
op_assign
l_string|&quot;1.0&quot;
suffix:semicolon
r_return
id|rev
suffix:semicolon
)brace
r_static
r_int
DECL|function|proc_read
id|proc_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_char
id|tmprev
(braket
l_int|32
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|tmprev
comma
id|main_revision
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|DRIVERNAME
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;name     : %s&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;release  : %s&bslash;n&quot;
comma
id|DRIVERRELEASE
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;build    : %s(%s)&bslash;n&quot;
comma
id|diva_didd_common_code_build
comma
id|DIVA_BUILD
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;revision : %s&bslash;n&quot;
comma
id|getrev
c_func
(paren
id|tmprev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
op_ge
id|len
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|off
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
(paren
(paren
id|count
OL
id|len
op_minus
id|off
)paren
ques
c_cond
id|count
suffix:colon
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
DECL|function|create_proc
r_static
r_int
id|DIVA_INIT_FUNCTION
id|create_proc
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|pe
suffix:semicolon
r_for
c_loop
(paren
id|pe
op_assign
id|proc_net-&gt;subdir
suffix:semicolon
id|pe
suffix:semicolon
id|pe
op_assign
id|pe-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|dir_in_proc_net
comma
id|pe-&gt;name
comma
id|pe-&gt;namelen
)paren
)paren
(brace
id|proc_net_isdn
op_assign
id|pe
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|proc_net_isdn
)paren
(brace
id|proc_net_isdn
op_assign
id|create_proc_entry
c_func
(paren
id|dir_in_proc_net
comma
id|S_IFDIR
comma
id|proc_net
)paren
suffix:semicolon
)brace
id|proc_net_isdn_eicon
op_assign
id|create_proc_entry
c_func
(paren
id|main_proc_dir
comma
id|S_IFDIR
comma
id|proc_net_isdn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_net_isdn_eicon
)paren
(brace
r_if
c_cond
(paren
(paren
id|proc_didd
op_assign
id|create_proc_entry
c_func
(paren
id|DRIVERLNAME
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|proc_net_isdn_eicon
)paren
)paren
)paren
(brace
id|proc_didd-&gt;read_proc
op_assign
id|proc_read
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|remove_proc
r_static
r_void
id|DIVA_EXIT_FUNCTION
id|remove_proc
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|DRIVERLNAME
comma
id|proc_net_isdn_eicon
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|main_proc_dir
comma
id|proc_net_isdn
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|proc_net_isdn
)paren
op_logical_and
(paren
op_logical_neg
id|proc_net_isdn-&gt;subdir
)paren
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|dir_in_proc_net
comma
id|proc_net
)paren
suffix:semicolon
)brace
)brace
DECL|function|divadidd_init
r_static
r_int
id|DIVA_INIT_FUNCTION
id|divadidd_init
c_func
(paren
r_void
)paren
(brace
r_char
id|tmprev
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|DRIVERNAME
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Rel:%s  Rev:&quot;
comma
id|DRIVERLNAME
comma
id|DRIVERRELEASE
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tmprev
comma
id|main_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s  Build:%s(%s)&bslash;n&quot;
comma
id|getrev
c_func
(paren
id|tmprev
)paren
comma
id|diva_didd_common_code_build
comma
id|DIVA_BUILD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|create_proc
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: could not create proc entry&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|diddfunc_init
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to connect to DIDD.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
id|remove_proc
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|divadidd_exit
r_void
id|DIVA_EXIT_FUNCTION
id|divadidd_exit
c_func
(paren
r_void
)paren
(brace
id|diddfunc_finit
c_func
(paren
)paren
suffix:semicolon
id|remove_proc
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: module unloaded.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
)brace
DECL|variable|divadidd_init
id|module_init
c_func
(paren
id|divadidd_init
)paren
suffix:semicolon
DECL|variable|divadidd_exit
id|module_exit
c_func
(paren
id|divadidd_exit
)paren
suffix:semicolon
eof
