multiline_comment|/*&n; * Simulated SCSI driver.&n; *&n; * Copyright (C) 1999, 2001-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&n; * 02/01/15 David Mosberger&t;Updated for v2.5.1&n; * 99/12/18 David Mosberger&t;Added support for READ10/WRITE10 needed by linux v2.3.33&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;../drivers/scsi/scsi.h&quot;
macro_line|#include &quot;../drivers/scsi/sd.h&quot;
macro_line|#include &quot;../drivers/scsi/hosts.h&quot;
macro_line|#include &quot;simscsi.h&quot;
DECL|macro|DEBUG_SIMSCSI
mdefine_line|#define DEBUG_SIMSCSI&t;1
multiline_comment|/* Simulator system calls: */
DECL|macro|SSC_OPEN
mdefine_line|#define SSC_OPEN&t;&t;&t;50
DECL|macro|SSC_CLOSE
mdefine_line|#define SSC_CLOSE&t;&t;&t;51
DECL|macro|SSC_READ
mdefine_line|#define SSC_READ&t;&t;&t;52
DECL|macro|SSC_WRITE
mdefine_line|#define SSC_WRITE&t;&t;&t;53
DECL|macro|SSC_GET_COMPLETION
mdefine_line|#define SSC_GET_COMPLETION&t;&t;54
DECL|macro|SSC_WAIT_COMPLETION
mdefine_line|#define SSC_WAIT_COMPLETION&t;&t;55
DECL|macro|SSC_WRITE_ACCESS
mdefine_line|#define SSC_WRITE_ACCESS&t;&t;2
DECL|macro|SSC_READ_ACCESS
mdefine_line|#define SSC_READ_ACCESS&t;&t;&t;1
macro_line|#if DEBUG_SIMSCSI
DECL|variable|simscsi_debug
r_int
id|simscsi_debug
suffix:semicolon
DECL|macro|DBG
macro_line|# define DBG&t;simscsi_debug
macro_line|#else
DECL|macro|DBG
macro_line|# define DBG&t;0
macro_line|#endif
DECL|variable|host
r_static
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_static
r_void
id|simscsi_interrupt
(paren
r_int
r_int
id|val
)paren
suffix:semicolon
id|DECLARE_TASKLET
c_func
(paren
id|simscsi_tasklet
comma
id|simscsi_interrupt
comma
l_int|0
)paren
suffix:semicolon
DECL|struct|disk_req
r_struct
id|disk_req
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|disk_stat
r_struct
id|disk_stat
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|ia64_ssc
(paren
r_int
id|arg0
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
comma
r_int
id|nr
)paren
suffix:semicolon
DECL|variable|desc
r_static
r_int
id|desc
(braket
l_int|16
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|struct|queue_entry
r_static
r_struct
id|queue_entry
(brace
DECL|member|sc
id|Scsi_Cmnd
op_star
id|sc
suffix:semicolon
DECL|variable|queue
)brace
id|queue
(braket
id|SIMSCSI_REQ_QUEUE_LEN
)braket
suffix:semicolon
DECL|variable|rd
DECL|variable|wr
r_static
r_int
id|rd
comma
id|wr
suffix:semicolon
DECL|variable|num_reqs
r_static
id|atomic_t
id|num_reqs
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* base name for default disks */
DECL|variable|simscsi_root
r_static
r_char
op_star
id|simscsi_root
op_assign
id|DEFAULT_SIMSCSI_ROOT
suffix:semicolon
DECL|macro|MAX_ROOT_LEN
mdefine_line|#define MAX_ROOT_LEN&t;128
multiline_comment|/*&n; * used to setup a new base for disk images&n; * to use /foo/bar/disk[a-z] as disk images&n; * you have to specify simscsi=/foo/bar/disk on the command line&n; */
r_static
r_int
id|__init
DECL|function|simscsi_setup
id|simscsi_setup
(paren
r_char
op_star
id|s
)paren
(brace
multiline_comment|/* XXX Fix me we may need to strcpy() ? */
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|s
)paren
OG
id|MAX_ROOT_LEN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;simscsi_setup: prefix too long---using default %s&bslash;n&quot;
comma
id|simscsi_root
)paren
suffix:semicolon
)brace
id|simscsi_root
op_assign
id|s
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;simscsi=&quot;
comma
id|simscsi_setup
)paren
suffix:semicolon
r_static
r_void
DECL|function|simscsi_interrupt
id|simscsi_interrupt
(paren
r_int
r_int
id|val
)paren
(brace
id|Scsi_Cmnd
op_star
id|sc
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sc
op_assign
id|queue
(braket
id|rd
)braket
dot
id|sc
)paren
op_ne
l_int|0
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|num_reqs
)paren
suffix:semicolon
id|queue
(braket
id|rd
)braket
dot
id|sc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|DBG
)paren
id|printk
c_func
(paren
l_string|&quot;simscsi_interrupt: done with %ld&bslash;n&quot;
comma
id|sc-&gt;serial_number
)paren
suffix:semicolon
(paren
op_star
id|sc-&gt;scsi_done
)paren
(paren
id|sc
)paren
suffix:semicolon
id|rd
op_assign
(paren
id|rd
op_plus
l_int|1
)paren
op_mod
id|SIMSCSI_REQ_QUEUE_LEN
suffix:semicolon
)brace
)brace
r_int
DECL|function|simscsi_detect
id|simscsi_detect
(paren
id|Scsi_Host_Template
op_star
id|templ
)paren
(brace
id|templ-&gt;proc_name
op_assign
l_string|&quot;simscsi&quot;
suffix:semicolon
id|host
op_assign
id|scsi_register
c_func
(paren
id|templ
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* fake one SCSI host adapter */
)brace
r_int
DECL|function|simscsi_release
id|simscsi_release
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* this is easy...  */
)brace
r_const
r_char
op_star
DECL|function|simscsi_info
id|simscsi_info
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_return
l_string|&quot;simulated SCSI host adapter&quot;
suffix:semicolon
)brace
r_int
DECL|function|simscsi_abort
id|simscsi_abort
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
(brace
id|printk
(paren
l_string|&quot;simscsi_abort: unimplemented&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|SCSI_ABORT_SUCCESS
suffix:semicolon
)brace
r_int
DECL|function|simscsi_reset
id|simscsi_reset
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
r_int
id|reset_flags
)paren
(brace
id|printk
(paren
l_string|&quot;simscsi_reset: unimplemented&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|SCSI_RESET_SUCCESS
suffix:semicolon
)brace
r_int
DECL|function|simscsi_biosparam
id|simscsi_biosparam
(paren
id|Disk
op_star
id|disk
comma
r_struct
id|block_device
op_star
id|n
comma
r_int
id|ip
(braket
)braket
)paren
(brace
r_int
id|size
op_assign
id|disk-&gt;capacity
suffix:semicolon
id|ip
(braket
l_int|0
)braket
op_assign
l_int|64
suffix:semicolon
multiline_comment|/* heads */
id|ip
(braket
l_int|1
)braket
op_assign
l_int|32
suffix:semicolon
multiline_comment|/* sectors */
id|ip
(braket
l_int|2
)braket
op_assign
id|size
op_rshift
l_int|11
suffix:semicolon
multiline_comment|/* cylinders */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|simscsi_readwrite
id|simscsi_readwrite
(paren
id|Scsi_Cmnd
op_star
id|sc
comma
r_int
id|mode
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|disk_stat
id|stat
suffix:semicolon
r_struct
id|disk_req
id|req
suffix:semicolon
id|req.addr
op_assign
id|__pa
c_func
(paren
id|sc-&gt;request_buffer
)paren
suffix:semicolon
id|req.len
op_assign
id|len
suffix:semicolon
multiline_comment|/* # of bytes to transfer */
r_if
c_cond
(paren
id|sc-&gt;request_bufflen
OL
id|req.len
)paren
r_return
suffix:semicolon
id|stat.fd
op_assign
id|desc
(braket
id|sc-&gt;target
)braket
suffix:semicolon
r_if
c_cond
(paren
id|DBG
)paren
id|printk
c_func
(paren
l_string|&quot;simscsi_%s @ %lx (off %lx)&bslash;n&quot;
comma
id|mode
op_eq
id|SSC_READ
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;write&quot;
comma
id|req.addr
comma
id|offset
)paren
suffix:semicolon
id|ia64_ssc
c_func
(paren
id|stat.fd
comma
l_int|1
comma
id|__pa
c_func
(paren
op_amp
id|req
)paren
comma
id|offset
comma
id|mode
)paren
suffix:semicolon
id|ia64_ssc
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|stat
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_WAIT_COMPLETION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat.count
op_eq
id|req.len
)paren
(brace
id|sc-&gt;result
op_assign
id|GOOD
suffix:semicolon
)brace
r_else
(brace
id|sc-&gt;result
op_assign
id|DID_ERROR
op_lshift
l_int|16
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|simscsi_sg_readwrite
id|simscsi_sg_readwrite
(paren
id|Scsi_Cmnd
op_star
id|sc
comma
r_int
id|mode
comma
r_int
r_int
id|offset
)paren
(brace
r_int
id|list_len
op_assign
id|sc-&gt;use_sg
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sl
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|sc-&gt;buffer
suffix:semicolon
r_struct
id|disk_stat
id|stat
suffix:semicolon
r_struct
id|disk_req
id|req
suffix:semicolon
id|stat.fd
op_assign
id|desc
(braket
id|sc-&gt;target
)braket
suffix:semicolon
r_while
c_loop
(paren
id|list_len
)paren
(brace
id|req.addr
op_assign
id|__pa
c_func
(paren
id|page_address
c_func
(paren
id|sl-&gt;page
)paren
op_plus
id|sl-&gt;offset
)paren
suffix:semicolon
id|req.len
op_assign
id|sl-&gt;length
suffix:semicolon
r_if
c_cond
(paren
id|DBG
)paren
id|printk
c_func
(paren
l_string|&quot;simscsi_sg_%s @ %lx (off %lx) use_sg=%d len=%d&bslash;n&quot;
comma
id|mode
op_eq
id|SSC_READ
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;write&quot;
comma
id|req.addr
comma
id|offset
comma
id|list_len
comma
id|sl-&gt;length
)paren
suffix:semicolon
id|ia64_ssc
c_func
(paren
id|stat.fd
comma
l_int|1
comma
id|__pa
c_func
(paren
op_amp
id|req
)paren
comma
id|offset
comma
id|mode
)paren
suffix:semicolon
id|ia64_ssc
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|stat
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_WAIT_COMPLETION
)paren
suffix:semicolon
multiline_comment|/* should not happen in our case */
r_if
c_cond
(paren
id|stat.count
op_ne
id|req.len
)paren
(brace
id|sc-&gt;result
op_assign
id|DID_ERROR
op_lshift
l_int|16
suffix:semicolon
r_return
suffix:semicolon
)brace
id|offset
op_add_assign
id|sl-&gt;length
suffix:semicolon
id|sl
op_increment
suffix:semicolon
id|list_len
op_decrement
suffix:semicolon
)brace
id|sc-&gt;result
op_assign
id|GOOD
suffix:semicolon
)brace
multiline_comment|/*&n; * function handling both READ_6/WRITE_6 (non-scatter/gather mode)&n; * commands.&n; * Added 02/26/99 S.Eranian&n; */
r_static
r_void
DECL|function|simscsi_readwrite6
id|simscsi_readwrite6
(paren
id|Scsi_Cmnd
op_star
id|sc
comma
r_int
id|mode
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|offset
op_assign
(paren
(paren
(paren
id|sc-&gt;cmnd
(braket
l_int|1
)braket
op_amp
l_int|0x1f
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|sc-&gt;cmnd
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|sc-&gt;cmnd
(braket
l_int|3
)braket
)paren
op_star
l_int|512
suffix:semicolon
r_if
c_cond
(paren
id|sc-&gt;use_sg
OG
l_int|0
)paren
id|simscsi_sg_readwrite
c_func
(paren
id|sc
comma
id|mode
comma
id|offset
)paren
suffix:semicolon
r_else
id|simscsi_readwrite
c_func
(paren
id|sc
comma
id|mode
comma
id|offset
comma
id|sc-&gt;cmnd
(braket
l_int|4
)braket
op_star
l_int|512
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|simscsi_get_disk_size
id|simscsi_get_disk_size
(paren
r_int
id|fd
)paren
(brace
r_struct
id|disk_stat
id|stat
suffix:semicolon
r_int
id|bit
comma
id|sectors
op_assign
l_int|0
suffix:semicolon
r_struct
id|disk_req
id|req
suffix:semicolon
r_char
id|buf
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * This is a bit kludgey: the simulator doesn&squot;t provide a direct way of determining&n;&t; * the disk size, so we do a binary search, assuming a maximum disk size of 4GB.&n;&t; */
r_for
c_loop
(paren
id|bit
op_assign
(paren
l_int|4UL
op_lshift
l_int|30
)paren
op_div
l_int|512
suffix:semicolon
id|bit
op_ne
l_int|0
suffix:semicolon
id|bit
op_rshift_assign
l_int|1
)paren
(brace
id|req.addr
op_assign
id|__pa
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|req.len
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
id|ia64_ssc
c_func
(paren
id|fd
comma
l_int|1
comma
id|__pa
c_func
(paren
op_amp
id|req
)paren
comma
(paren
(paren
id|sectors
op_or
id|bit
)paren
op_minus
l_int|1
)paren
op_star
l_int|512
comma
id|SSC_READ
)paren
suffix:semicolon
id|stat.fd
op_assign
id|fd
suffix:semicolon
id|ia64_ssc
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|stat
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_WAIT_COMPLETION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat.count
op_eq
r_sizeof
(paren
id|buf
)paren
)paren
id|sectors
op_or_assign
id|bit
suffix:semicolon
)brace
r_return
id|sectors
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* return last valid sector number */
)brace
r_static
r_void
DECL|function|simscsi_readwrite10
id|simscsi_readwrite10
(paren
id|Scsi_Cmnd
op_star
id|sc
comma
r_int
id|mode
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|offset
op_assign
(paren
(paren
id|sc-&gt;cmnd
(braket
l_int|2
)braket
op_lshift
l_int|24
)paren
op_or
(paren
id|sc-&gt;cmnd
(braket
l_int|3
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|sc-&gt;cmnd
(braket
l_int|4
)braket
op_lshift
l_int|8
)paren
op_or
(paren
id|sc-&gt;cmnd
(braket
l_int|5
)braket
op_lshift
l_int|0
)paren
)paren
op_star
l_int|512
suffix:semicolon
r_if
c_cond
(paren
id|sc-&gt;use_sg
OG
l_int|0
)paren
id|simscsi_sg_readwrite
c_func
(paren
id|sc
comma
id|mode
comma
id|offset
)paren
suffix:semicolon
r_else
id|simscsi_readwrite
c_func
(paren
id|sc
comma
id|mode
comma
id|offset
comma
(paren
(paren
id|sc-&gt;cmnd
(braket
l_int|7
)braket
op_lshift
l_int|8
)paren
op_or
id|sc-&gt;cmnd
(braket
l_int|8
)braket
)paren
op_star
l_int|512
)paren
suffix:semicolon
)brace
r_int
DECL|function|simscsi_queuecommand
id|simscsi_queuecommand
(paren
id|Scsi_Cmnd
op_star
id|sc
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
(brace
r_char
id|fname
(braket
id|MAX_ROOT_LEN
op_plus
l_int|16
)braket
suffix:semicolon
r_int
id|disk_size
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
macro_line|#if DEBUG_SIMSCSI
r_register
r_int
id|sp
id|asm
(paren
l_string|&quot;sp&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DBG
)paren
id|printk
c_func
(paren
l_string|&quot;simscsi_queuecommand: target=%d,cmnd=%u,sc=%lu,sp=%lx,done=%p&bslash;n&quot;
comma
id|sc-&gt;target
comma
id|sc-&gt;cmnd
(braket
l_int|0
)braket
comma
id|sc-&gt;serial_number
comma
id|sp
comma
id|done
)paren
suffix:semicolon
macro_line|#endif
id|sc-&gt;result
op_assign
id|DID_BAD_TARGET
op_lshift
l_int|16
suffix:semicolon
id|sc-&gt;scsi_done
op_assign
id|done
suffix:semicolon
r_if
c_cond
(paren
id|sc-&gt;target
op_le
l_int|15
op_logical_and
id|sc-&gt;lun
op_eq
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|sc-&gt;cmnd
(braket
l_int|0
)braket
)paren
(brace
r_case
id|INQUIRY
suffix:colon
r_if
c_cond
(paren
id|sc-&gt;request_bufflen
OL
l_int|35
)paren
(brace
r_break
suffix:semicolon
)brace
id|sprintf
(paren
id|fname
comma
l_string|&quot;%s%c&quot;
comma
id|simscsi_root
comma
l_char|&squot;a&squot;
op_plus
id|sc-&gt;target
)paren
suffix:semicolon
id|desc
(braket
id|sc-&gt;target
)braket
op_assign
id|ia64_ssc
c_func
(paren
id|__pa
c_func
(paren
id|fname
)paren
comma
id|SSC_READ_ACCESS
op_or
id|SSC_WRITE_ACCESS
comma
l_int|0
comma
l_int|0
comma
id|SSC_OPEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc
(braket
id|sc-&gt;target
)braket
OL
l_int|0
)paren
(brace
multiline_comment|/* disk doesn&squot;t exist... */
r_break
suffix:semicolon
)brace
id|buf
op_assign
id|sc-&gt;request_buffer
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* magnetic disk */
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* not a removable medium */
id|buf
(braket
l_int|2
)braket
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* SCSI-2 compliant device */
id|buf
(braket
l_int|3
)braket
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* SCSI-2 response data format */
id|buf
(braket
l_int|4
)braket
op_assign
l_int|31
suffix:semicolon
multiline_comment|/* additional length (bytes) */
id|buf
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* reserved */
id|buf
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* reserved */
id|buf
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* various flags */
id|memcpy
c_func
(paren
id|buf
op_plus
l_int|8
comma
l_string|&quot;HP      SIMULATED DISK  0.00&quot;
comma
l_int|28
)paren
suffix:semicolon
id|sc-&gt;result
op_assign
id|GOOD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TEST_UNIT_READY
suffix:colon
id|sc-&gt;result
op_assign
id|GOOD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_6
suffix:colon
r_if
c_cond
(paren
id|desc
(braket
id|sc-&gt;target
)braket
OL
l_int|0
)paren
r_break
suffix:semicolon
id|simscsi_readwrite6
c_func
(paren
id|sc
comma
id|SSC_READ
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_10
suffix:colon
r_if
c_cond
(paren
id|desc
(braket
id|sc-&gt;target
)braket
OL
l_int|0
)paren
r_break
suffix:semicolon
id|simscsi_readwrite10
c_func
(paren
id|sc
comma
id|SSC_READ
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_6
suffix:colon
r_if
c_cond
(paren
id|desc
(braket
id|sc-&gt;target
)braket
OL
l_int|0
)paren
r_break
suffix:semicolon
id|simscsi_readwrite6
c_func
(paren
id|sc
comma
id|SSC_WRITE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_10
suffix:colon
r_if
c_cond
(paren
id|desc
(braket
id|sc-&gt;target
)braket
OL
l_int|0
)paren
r_break
suffix:semicolon
id|simscsi_readwrite10
c_func
(paren
id|sc
comma
id|SSC_WRITE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_CAPACITY
suffix:colon
r_if
c_cond
(paren
id|desc
(braket
id|sc-&gt;target
)braket
OL
l_int|0
op_logical_or
id|sc-&gt;request_bufflen
OL
l_int|8
)paren
(brace
r_break
suffix:semicolon
)brace
id|buf
op_assign
id|sc-&gt;request_buffer
suffix:semicolon
id|disk_size
op_assign
id|simscsi_get_disk_size
c_func
(paren
id|desc
(braket
id|sc-&gt;target
)braket
)paren
suffix:semicolon
multiline_comment|/* pretend to be a 1GB disk (partition table contains real stuff): */
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|disk_size
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|disk_size
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
(paren
id|disk_size
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
(paren
id|disk_size
op_rshift
l_int|0
)paren
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* set block size of 512 bytes: */
id|buf
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_assign
l_int|2
suffix:semicolon
id|buf
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|sc-&gt;result
op_assign
id|GOOD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MODE_SENSE
suffix:colon
multiline_comment|/* sd.c uses this to determine whether disk does write-caching. */
id|memset
c_func
(paren
id|sc-&gt;request_buffer
comma
l_int|0
comma
l_int|128
)paren
suffix:semicolon
id|sc-&gt;result
op_assign
id|GOOD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|START_STOP
suffix:colon
id|printk
c_func
(paren
l_string|&quot;START_STOP&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;simscsi: unknown SCSI command %u&bslash;n&quot;
comma
id|sc-&gt;cmnd
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sc-&gt;result
op_eq
id|DID_BAD_TARGET
)paren
(brace
id|sc-&gt;result
op_or_assign
id|DRIVER_SENSE
op_lshift
l_int|24
suffix:semicolon
id|sc-&gt;sense_buffer
(braket
l_int|0
)braket
op_assign
l_int|0x70
suffix:semicolon
id|sc-&gt;sense_buffer
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|num_reqs
)paren
op_ge
id|SIMSCSI_REQ_QUEUE_LEN
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Attempt to queue command while command is pending!!&quot;
)paren
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|num_reqs
)paren
suffix:semicolon
id|queue
(braket
id|wr
)braket
dot
id|sc
op_assign
id|sc
suffix:semicolon
id|wr
op_assign
(paren
id|wr
op_plus
l_int|1
)paren
op_mod
id|SIMSCSI_REQ_QUEUE_LEN
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|simscsi_tasklet
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|SIMSCSI
suffix:semicolon
macro_line|#include &quot;../drivers/scsi/scsi_module.c&quot;
eof
