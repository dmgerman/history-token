multiline_comment|/* hermes.c&n; *&n; * Driver core for the &quot;Hermes&quot; wireless MAC controller, as used in&n; * the Lucent Orinoco and Cabletron RoamAbout cards. It should also&n; * work on the hfa3841 and hfa3842 MAC controller chips used in the&n; * Prism I &amp; II chipsets.&n; *&n; * This is not a complete driver, just low-level access routines for&n; * the MAC controller itself.&n; *&n; * Based on the prism2 driver from Absolute Value Systems&squot; linux-wlan&n; * project, the Linux wvlan_cs driver, Lucent&squot;s HCF-Light&n; * (wvlan_hcf.c) library, and the NetBSD wireless driver.&n; *&n; * Copyright (C) 2000, David Gibson, Linuxcare Australia &lt;hermes@gibson.dropbear.id.au&gt;&n; * &n; * This file distributed under the GPL, version 2.&n; */
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;hermes.c: 12 Dec 2000 David Gibson &lt;hermes@gibson.dropbear.id.au&gt;&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &quot;hermes.h&quot;
DECL|macro|CMD_BUSY_TIMEOUT
mdefine_line|#define CMD_BUSY_TIMEOUT (100) /* In iterations of ~1us */
DECL|macro|CMD_INIT_TIMEOUT
mdefine_line|#define CMD_INIT_TIMEOUT (50000) /* in iterations of ~10us */
DECL|macro|CMD_COMPL_TIMEOUT
mdefine_line|#define CMD_COMPL_TIMEOUT (10000) /* in iterations of ~10us */
DECL|macro|ALLOC_COMPL_TIMEOUT
mdefine_line|#define ALLOC_COMPL_TIMEOUT (1000) /* in iterations of ~10us */
DECL|macro|BAP_BUSY_TIMEOUT
mdefine_line|#define BAP_BUSY_TIMEOUT (500) /* In iterations of ~1us */
DECL|macro|BAP_ERROR_RETRY
mdefine_line|#define BAP_ERROR_RETRY (10) /* How many times to retry a BAP seek when there is an error */
DECL|macro|MAX
mdefine_line|#define MAX(a, b) ( (a) &gt; (b) ? (a) : (b) )
DECL|macro|MIN
mdefine_line|#define MIN(a, b) ( (a) &lt; (b) ? (a) : (b) )
multiline_comment|/*&n; * Debugging helpers&n; */
DECL|macro|HERMES_DEBUG
macro_line|#undef HERMES_DEBUG
macro_line|#ifdef HERMES_DEBUG
macro_line|#include &lt;stdarg.h&gt;
DECL|macro|DMSG
mdefine_line|#define DMSG(stuff...) do {printk(KERN_DEBUG &quot;hermes @ 0x%x: &quot; , hw-&gt;iobase); &bslash;&n;&t;&t;&t;printk(#stuff);} while (0)
DECL|macro|DEBUG
mdefine_line|#define DEBUG(lvl, stuff...) if ( (lvl) &lt;= HERMES_DEBUG) DMSG(#stuff)
macro_line|#else /* ! HERMES_DEBUG */
DECL|macro|DEBUG
mdefine_line|#define DEBUG(lvl, stuff...) do { } while (0)
macro_line|#endif /* ! HERMES_DEBUG */
multiline_comment|/*&n; * Prototypes&n; */
r_static
r_int
id|hermes_issue_cmd
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_uint16
id|cmd
comma
r_uint16
id|param0
)paren
suffix:semicolon
multiline_comment|/*&n; * Internal inline functions&n; */
multiline_comment|/*&n; * Internal functions&n; */
multiline_comment|/* Issue a command to the chip. Waiting for it to complete is the caller&squot;s&n;   problem.&n;&n;   Returns -EBUSY if the command register is busy, 0 on success.&n;&n;   Callable from any context.&n;*/
DECL|function|hermes_issue_cmd
r_static
r_int
id|hermes_issue_cmd
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_uint16
id|cmd
comma
r_uint16
id|param0
)paren
(brace
r_uint16
id|reg
suffix:semicolon
multiline_comment|/*  &t;unsigned long k = CMD_BUSY_TIMEOUT; */
multiline_comment|/* First check that the command register is not busy */
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
id|HERMES_CMD_BUSY
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|PARAM2
comma
l_int|0
)paren
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|PARAM1
comma
l_int|0
)paren
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|PARAM0
comma
id|param0
)paren
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|CMD
comma
id|cmd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function definitions&n; */
DECL|function|hermes_struct_init
r_void
id|hermes_struct_init
c_func
(paren
id|hermes_t
op_star
id|hw
comma
id|ushort
id|io
)paren
(brace
id|hw-&gt;iobase
op_assign
id|io
suffix:semicolon
id|hw-&gt;inten
op_assign
l_int|0x0
suffix:semicolon
)brace
DECL|function|hermes_reset
r_int
id|hermes_reset
c_func
(paren
id|hermes_t
op_star
id|hw
)paren
(brace
r_uint16
id|status
comma
id|reg
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|k
suffix:semicolon
multiline_comment|/* We don&squot;t want to be interrupted while resetting the chipset */
id|hw-&gt;inten
op_assign
l_int|0x0
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|INTEN
comma
l_int|0
)paren
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|EVACK
comma
l_int|0xffff
)paren
suffix:semicolon
multiline_comment|/* Because we hope we can reset the card even if it gets into&n;&t;   a stupid state, we actually wait to see if the command&n;&t;   register will unbusy itself */
id|k
op_assign
id|CMD_BUSY_TIMEOUT
suffix:semicolon
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|CMD
)paren
suffix:semicolon
r_while
c_loop
(paren
id|k
op_logical_and
(paren
id|reg
op_amp
id|HERMES_CMD_BUSY
)paren
)paren
(brace
r_if
c_cond
(paren
id|reg
op_eq
l_int|0xffff
)paren
multiline_comment|/* Special case - the card has probably been removed,&n;&t;&t;&t;&t;      so don&squot;t wait for the timeout */
r_return
op_minus
id|ENODEV
suffix:semicolon
id|k
op_decrement
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|CMD
)paren
suffix:semicolon
)brace
multiline_comment|/* No need to explicitly handle the timeout - hermes_issue_cmd() will&n;&t;   probably return -EBUSY */
multiline_comment|/* We don&squot;t use hermes_docmd_wait here, because the reset wipes&n;&t;   the magic constant in SWSUPPORT0 away, and it gets confused */
id|err
op_assign
id|hermes_issue_cmd
c_func
(paren
id|hw
comma
id|HERMES_CMD_INIT
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|EVSTAT
)paren
suffix:semicolon
id|k
op_assign
id|CMD_INIT_TIMEOUT
suffix:semicolon
r_while
c_loop
(paren
(paren
op_logical_neg
(paren
id|reg
op_amp
id|HERMES_EV_CMD
)paren
)paren
op_logical_and
id|k
)paren
(brace
id|k
op_decrement
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|EVSTAT
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Reset completed in %d iterations&bslash;n&quot;
comma
id|CMD_INIT_TIMEOUT
op_minus
id|k
)paren
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|SWSUPPORT0
comma
id|HERMES_MAGIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hermes_present
c_func
(paren
id|hw
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;hermes @ 0x%x: Card removed during reset.&bslash;n&quot;
comma
id|hw-&gt;iobase
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_amp
id|HERMES_EV_CMD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hermes @ 0x%x: Timeout waiting for card to reset (reg=0x%04x)!&bslash;n&quot;
comma
id|hw-&gt;iobase
comma
id|reg
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|status
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|STATUS
)paren
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|EVACK
comma
id|HERMES_EV_CMD
)paren
suffix:semicolon
id|err
op_assign
id|status
op_amp
id|HERMES_STATUS_RESULT
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Issue a command to the chip, and (busy!) wait for it to&n; * complete.&n; *&n; * Returns: &lt; 0 on internal error, 0 on success, &gt; 0 on error returned by the firmware&n; *&n; * Callable from any context, but locking is your problem. */
DECL|function|hermes_docmd_wait
r_int
id|hermes_docmd_wait
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_uint16
id|cmd
comma
r_uint16
id|parm0
comma
id|hermes_response_t
op_star
id|resp
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
id|k
suffix:semicolon
r_uint16
id|reg
suffix:semicolon
id|err
op_assign
id|hermes_issue_cmd
c_func
(paren
id|hw
comma
id|cmd
comma
id|parm0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hermes_present
c_func
(paren
id|hw
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hermes @ 0x%x: Card removed while issuing command.&bslash;n&quot;
comma
id|hw-&gt;iobase
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hermes @ 0x%x: CMD register busy in hermes_issue_command().&bslash;n&quot;
comma
id|hw-&gt;iobase
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|EVSTAT
)paren
suffix:semicolon
id|k
op_assign
id|CMD_COMPL_TIMEOUT
suffix:semicolon
r_while
c_loop
(paren
(paren
op_logical_neg
(paren
id|reg
op_amp
id|HERMES_EV_CMD
)paren
)paren
op_logical_and
id|k
)paren
(brace
id|k
op_decrement
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|EVSTAT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hermes_present
c_func
(paren
id|hw
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hermes @ 0x%x: Card removed while waiting for command completion.&bslash;n&quot;
comma
id|hw-&gt;iobase
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_amp
id|HERMES_EV_CMD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hermes @ 0x%x: Timeout waiting for command completion.&bslash;n&quot;
comma
id|hw-&gt;iobase
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|resp-&gt;status
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|STATUS
)paren
suffix:semicolon
id|resp-&gt;resp0
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|RESP0
)paren
suffix:semicolon
id|resp-&gt;resp1
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|RESP1
)paren
suffix:semicolon
id|resp-&gt;resp2
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|RESP2
)paren
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|EVACK
comma
id|HERMES_EV_CMD
)paren
suffix:semicolon
id|err
op_assign
id|resp-&gt;status
op_amp
id|HERMES_STATUS_RESULT
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|hermes_allocate
r_int
id|hermes_allocate
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_uint16
id|size
comma
r_uint16
op_star
id|fid
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|hermes_response_t
id|resp
suffix:semicolon
r_int
id|k
suffix:semicolon
r_uint16
id|reg
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
OL
id|HERMES_ALLOC_LEN_MIN
)paren
op_logical_or
(paren
id|size
OG
id|HERMES_ALLOC_LEN_MAX
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|hermes_docmd_wait
c_func
(paren
id|hw
comma
id|HERMES_CMD_ALLOC
comma
id|size
comma
op_amp
id|resp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hermes @ 0x%x: Frame allocation command failed (0x%X).&bslash;n&quot;
comma
id|hw-&gt;iobase
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|EVSTAT
)paren
suffix:semicolon
id|k
op_assign
id|ALLOC_COMPL_TIMEOUT
suffix:semicolon
r_while
c_loop
(paren
(paren
op_logical_neg
(paren
id|reg
op_amp
id|HERMES_EV_ALLOC
)paren
)paren
op_logical_and
id|k
)paren
(brace
id|k
op_decrement
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|EVSTAT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hermes_present
c_func
(paren
id|hw
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hermes @ 0x%x: Card removed waiting for frame allocation.&bslash;n&quot;
comma
id|hw-&gt;iobase
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_amp
id|HERMES_EV_ALLOC
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hermes @ 0x%x: Timeout waiting for frame allocation&bslash;n&quot;
comma
id|hw-&gt;iobase
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
op_star
id|fid
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|ALLOCFID
)paren
suffix:semicolon
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|EVACK
comma
id|HERMES_EV_ALLOC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set up a BAP to read a particular chunk of data from card&squot;s internal buffer.&n; *&n; * Returns: &lt; 0 on internal failure (errno), 0 on success, &gt;0 on error&n; * from firmware&n; *&n; * Callable from any context */
DECL|function|hermes_bap_seek
r_static
r_int
id|hermes_bap_seek
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_int
id|bap
comma
r_uint16
id|id
comma
r_uint16
id|offset
)paren
(brace
r_int
id|sreg
op_assign
id|bap
ques
c_cond
id|HERMES_SELECT1
suffix:colon
id|HERMES_SELECT0
suffix:semicolon
r_int
id|oreg
op_assign
id|bap
ques
c_cond
id|HERMES_OFFSET1
suffix:colon
id|HERMES_OFFSET0
suffix:semicolon
r_int
id|k
suffix:semicolon
r_int
id|l
op_assign
id|BAP_ERROR_RETRY
suffix:semicolon
r_uint16
id|reg
suffix:semicolon
multiline_comment|/* Paranoia.. */
r_if
c_cond
(paren
(paren
id|offset
OG
id|HERMES_BAP_OFFSET_MAX
)paren
op_logical_or
(paren
id|offset
op_mod
l_int|2
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|k
op_assign
id|BAP_BUSY_TIMEOUT
suffix:semicolon
id|reg
op_assign
id|hermes_read_reg
c_func
(paren
id|hw
comma
id|oreg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
id|HERMES_OFFSET_BUSY
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Now we actually set up the transfer */
id|retry
suffix:colon
id|hermes_write_reg
c_func
(paren
id|hw
comma
id|sreg
comma
id|id
)paren
suffix:semicolon
id|hermes_write_reg
c_func
(paren
id|hw
comma
id|oreg
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* Wait for the BAP to be ready */
id|k
op_assign
id|BAP_BUSY_TIMEOUT
suffix:semicolon
id|reg
op_assign
id|hermes_read_reg
c_func
(paren
id|hw
comma
id|oreg
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|reg
op_amp
(paren
id|HERMES_OFFSET_BUSY
op_or
id|HERMES_OFFSET_ERR
)paren
)paren
op_logical_and
id|k
)paren
(brace
id|k
op_decrement
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|reg
op_assign
id|hermes_read_reg
c_func
(paren
id|hw
comma
id|oreg
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg
op_amp
id|HERMES_OFFSET_BUSY
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
multiline_comment|/* For some reason, seeking the BAP seems to randomly fail somewhere&n;&t;   (firmware bug?). We retry a few times before giving up. */
r_if
c_cond
(paren
id|reg
op_amp
id|HERMES_OFFSET_ERR
)paren
(brace
r_if
c_cond
(paren
id|l
op_decrement
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Read a block of data from the chip&squot;s buffer, via the&n; * BAP. Synchronization/serialization is the caller&squot;s problem.  len&n; * must be even.&n; *&n; * Returns: &lt; 0 on internal failure (errno), 0 on success, &gt; 0 on error from firmware&n; */
DECL|function|hermes_bap_pread
r_int
id|hermes_bap_pread
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_int
id|bap
comma
r_void
op_star
id|buf
comma
r_uint16
id|len
comma
r_uint16
id|id
comma
r_uint16
id|offset
)paren
(brace
r_int
id|dreg
op_assign
id|bap
ques
c_cond
id|HERMES_DATA1
suffix:colon
id|HERMES_DATA0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
op_mod
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|hermes_bap_seek
c_func
(paren
id|hw
comma
id|bap
comma
id|id
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Actually do the transfer */
id|hermes_read_data
c_func
(paren
id|hw
comma
id|dreg
comma
id|buf
comma
id|len
op_div
l_int|2
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Write a block of data to the chip&squot;s buffer, via the&n; * BAP. Synchronization/serialization is the caller&squot;s problem. len&n; * must be even.&n; *&n; * Returns: &lt; 0 on internal failure (errno), 0 on success, &gt; 0 on error from firmware&n; */
DECL|function|hermes_bap_pwrite
r_int
id|hermes_bap_pwrite
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_int
id|bap
comma
r_const
r_void
op_star
id|buf
comma
r_uint16
id|len
comma
r_uint16
id|id
comma
r_uint16
id|offset
)paren
(brace
r_int
id|dreg
op_assign
id|bap
ques
c_cond
id|HERMES_DATA1
suffix:colon
id|HERMES_DATA0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
op_mod
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|hermes_bap_seek
c_func
(paren
id|hw
comma
id|bap
comma
id|id
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Actually do the transfer */
id|hermes_write_data
c_func
(paren
id|hw
comma
id|dreg
comma
id|buf
comma
id|len
op_div
l_int|2
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Read a Length-Type-Value record from the card.&n; *&n; * If length is NULL, we ignore the length read from the card, and&n; * read the entire buffer regardless. This is useful because some of&n; * the configuration records appear to have incorrect lengths in&n; * practice.&n; *&n; * Callable from user or bh context.  */
DECL|function|hermes_read_ltv
r_int
id|hermes_read_ltv
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_int
id|bap
comma
r_uint16
id|rid
comma
r_int
id|buflen
comma
r_uint16
op_star
id|length
comma
r_void
op_star
id|buf
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|dreg
op_assign
id|bap
ques
c_cond
id|HERMES_DATA1
suffix:colon
id|HERMES_DATA0
suffix:semicolon
r_uint16
id|rlength
comma
id|rtype
suffix:semicolon
id|hermes_response_t
id|resp
suffix:semicolon
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
id|buflen
op_mod
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|hermes_docmd_wait
c_func
(paren
id|hw
comma
id|HERMES_CMD_ACCESS
comma
id|rid
comma
op_amp
id|resp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|hermes_bap_seek
c_func
(paren
id|hw
comma
id|bap
comma
id|rid
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|rlength
op_assign
id|hermes_read_reg
c_func
(paren
id|hw
comma
id|dreg
)paren
suffix:semicolon
id|rtype
op_assign
id|hermes_read_reg
c_func
(paren
id|hw
comma
id|dreg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
)paren
op_star
id|length
op_assign
id|rlength
suffix:semicolon
r_if
c_cond
(paren
id|rtype
op_ne
id|rid
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hermes_read_ltv(): rid  (0x%04x) does &quot;
l_string|&quot;not match type (0x%04x)&bslash;n&quot;
comma
id|rid
comma
id|rtype
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HERMES_RECLEN_TO_BYTES
c_func
(paren
id|rlength
)paren
OG
id|buflen
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hermes @ 0x%x: Truncating LTV record from %d to %d bytes. &quot;
l_string|&quot;(rid=0x%04x, len=0x%04x)&bslash;n&quot;
comma
id|hw-&gt;iobase
comma
id|HERMES_RECLEN_TO_BYTES
c_func
(paren
id|rlength
)paren
comma
id|buflen
comma
id|rid
comma
id|rlength
)paren
suffix:semicolon
multiline_comment|/* For now we always read the whole buffer, the&n;&t;   lengths in the records seem to be wrong, frequently */
id|count
op_assign
id|buflen
op_div
l_int|2
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|length
)paren
id|count
op_assign
(paren
id|MIN
c_func
(paren
id|buflen
comma
id|rlength
)paren
op_plus
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
r_else
(brace
id|count
op_assign
id|buflen
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|rlength
op_ne
id|buflen
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hermes_read_ltv(): Incorrect &bslash;&n;record length %d instead of %d on RID 0x%04x&bslash;n&quot;
comma
id|rlength
comma
id|buflen
comma
id|rid
)paren
suffix:semicolon
)brace
macro_line|#endif
id|hermes_read_data
c_func
(paren
id|hw
comma
id|dreg
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|hermes_write_ltv
r_int
id|hermes_write_ltv
c_func
(paren
id|hermes_t
op_star
id|hw
comma
r_int
id|bap
comma
r_uint16
id|rid
comma
r_uint16
id|length
comma
r_const
r_void
op_star
id|value
)paren
(brace
r_int
id|dreg
op_assign
id|bap
ques
c_cond
id|HERMES_DATA1
suffix:colon
id|HERMES_DATA0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|hermes_response_t
id|resp
suffix:semicolon
r_int
id|count
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;write_ltv(): bap=%d rid=0x%04x length=%d (value=0x%04x)&bslash;n&quot;
comma
id|bap
comma
id|rid
comma
id|length
comma
op_star
(paren
(paren
r_uint16
op_star
)paren
id|value
)paren
)paren
suffix:semicolon
id|err
op_assign
id|hermes_bap_seek
c_func
(paren
id|hw
comma
id|bap
comma
id|rid
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|hermes_write_reg
c_func
(paren
id|hw
comma
id|dreg
comma
id|length
)paren
suffix:semicolon
id|hermes_write_reg
c_func
(paren
id|hw
comma
id|dreg
comma
id|rid
)paren
suffix:semicolon
id|count
op_assign
id|length
op_minus
l_int|1
suffix:semicolon
id|hermes_write_data
c_func
(paren
id|hw
comma
id|dreg
comma
id|value
comma
id|count
)paren
suffix:semicolon
id|err
op_assign
id|hermes_docmd_wait
c_func
(paren
id|hw
comma
id|HERMES_CMD_ACCESS
op_or
id|HERMES_CMD_WRITE
comma
id|rid
comma
op_amp
id|resp
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|hermes_struct_init
id|EXPORT_SYMBOL
c_func
(paren
id|hermes_struct_init
)paren
suffix:semicolon
DECL|variable|hermes_reset
id|EXPORT_SYMBOL
c_func
(paren
id|hermes_reset
)paren
suffix:semicolon
DECL|variable|hermes_docmd_wait
id|EXPORT_SYMBOL
c_func
(paren
id|hermes_docmd_wait
)paren
suffix:semicolon
DECL|variable|hermes_allocate
id|EXPORT_SYMBOL
c_func
(paren
id|hermes_allocate
)paren
suffix:semicolon
DECL|variable|hermes_bap_pread
id|EXPORT_SYMBOL
c_func
(paren
id|hermes_bap_pread
)paren
suffix:semicolon
DECL|variable|hermes_bap_pwrite
id|EXPORT_SYMBOL
c_func
(paren
id|hermes_bap_pwrite
)paren
suffix:semicolon
DECL|variable|hermes_read_ltv
id|EXPORT_SYMBOL
c_func
(paren
id|hermes_read_ltv
)paren
suffix:semicolon
DECL|variable|hermes_write_ltv
id|EXPORT_SYMBOL
c_func
(paren
id|hermes_write_ltv
)paren
suffix:semicolon
DECL|function|init_hermes
r_static
r_int
id|__init
id|init_hermes
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_hermes
id|module_init
c_func
(paren
id|init_hermes
)paren
suffix:semicolon
eof
