multiline_comment|/* fcal.c: Fibre Channel Arbitrated Loop SCSI host adapter driver.&n; *&n; * Copyright (C) 1998,1999 Jakub Jelinek (jj@ultra.linux.cz)&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;../fc4/fcp_impl.h&quot;
macro_line|#include &quot;fcal.h&quot;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/* #define FCAL_DEBUG */
DECL|macro|fcal_printk
mdefine_line|#define fcal_printk printk (&quot;FCAL %s: &quot;, fc-&gt;name); printk
macro_line|#ifdef FCAL_DEBUG
DECL|macro|FCALD
mdefine_line|#define FCALD(x)  fcal_printk x;
DECL|macro|FCALND
mdefine_line|#define FCALND(x) printk (&quot;FCAL: &quot;); printk x;
macro_line|#else
DECL|macro|FCALD
mdefine_line|#define FCALD(x)
DECL|macro|FCALND
mdefine_line|#define FCALND(x)
macro_line|#endif
DECL|variable|alpa2target
r_static
r_int
r_char
id|alpa2target
(braket
)braket
op_assign
(brace
l_int|0x7e
comma
l_int|0x7d
comma
l_int|0x7c
comma
l_int|0xff
comma
l_int|0x7b
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x7a
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x79
comma
l_int|0x78
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x77
comma
l_int|0x76
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x75
comma
l_int|0xff
comma
l_int|0x74
comma
l_int|0x73
comma
l_int|0x72
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x71
comma
l_int|0xff
comma
l_int|0x70
comma
l_int|0x6f
comma
l_int|0x6e
comma
l_int|0xff
comma
l_int|0x6d
comma
l_int|0x6c
comma
l_int|0x6b
comma
l_int|0x6a
comma
l_int|0x69
comma
l_int|0x68
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x67
comma
l_int|0x66
comma
l_int|0x65
comma
l_int|0x64
comma
l_int|0x63
comma
l_int|0x62
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x61
comma
l_int|0x60
comma
l_int|0xff
comma
l_int|0x5f
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x5e
comma
l_int|0xff
comma
l_int|0x5d
comma
l_int|0x5c
comma
l_int|0x5b
comma
l_int|0xff
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x58
comma
l_int|0x57
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x54
comma
l_int|0x53
comma
l_int|0x52
comma
l_int|0x51
comma
l_int|0x50
comma
l_int|0x4f
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x4e
comma
l_int|0x4d
comma
l_int|0xff
comma
l_int|0x4c
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x4b
comma
l_int|0xff
comma
l_int|0x4a
comma
l_int|0x49
comma
l_int|0x48
comma
l_int|0xff
comma
l_int|0x47
comma
l_int|0x46
comma
l_int|0x45
comma
l_int|0x44
comma
l_int|0x43
comma
l_int|0x42
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x41
comma
l_int|0x40
comma
l_int|0x3f
comma
l_int|0x3e
comma
l_int|0x3d
comma
l_int|0x3c
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x3b
comma
l_int|0x3a
comma
l_int|0xff
comma
l_int|0x39
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x38
comma
l_int|0x37
comma
l_int|0x36
comma
l_int|0xff
comma
l_int|0x35
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x34
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x33
comma
l_int|0x32
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x31
comma
l_int|0x30
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x2f
comma
l_int|0xff
comma
l_int|0x2e
comma
l_int|0x2d
comma
l_int|0x2c
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x2b
comma
l_int|0xff
comma
l_int|0x2a
comma
l_int|0x29
comma
l_int|0x28
comma
l_int|0xff
comma
l_int|0x27
comma
l_int|0x26
comma
l_int|0x25
comma
l_int|0x24
comma
l_int|0x23
comma
l_int|0x22
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x21
comma
l_int|0x20
comma
l_int|0x1f
comma
l_int|0x1e
comma
l_int|0x1d
comma
l_int|0x1c
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x1b
comma
l_int|0x1a
comma
l_int|0xff
comma
l_int|0x19
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x18
comma
l_int|0xff
comma
l_int|0x17
comma
l_int|0x16
comma
l_int|0x15
comma
l_int|0xff
comma
l_int|0x14
comma
l_int|0x13
comma
l_int|0x12
comma
l_int|0x11
comma
l_int|0x10
comma
l_int|0x0f
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x0e
comma
l_int|0x0d
comma
l_int|0x0c
comma
l_int|0x0b
comma
l_int|0x0a
comma
l_int|0x09
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x08
comma
l_int|0x07
comma
l_int|0xff
comma
l_int|0x06
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x05
comma
l_int|0x04
comma
l_int|0x03
comma
l_int|0xff
comma
l_int|0x02
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x01
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|target2alpa
r_static
r_int
r_char
id|target2alpa
(braket
)braket
op_assign
(brace
l_int|0xef
comma
l_int|0xe8
comma
l_int|0xe4
comma
l_int|0xe2
comma
l_int|0xe1
comma
l_int|0xe0
comma
l_int|0xdc
comma
l_int|0xda
comma
l_int|0xd9
comma
l_int|0xd6
comma
l_int|0xd5
comma
l_int|0xd4
comma
l_int|0xd3
comma
l_int|0xd2
comma
l_int|0xd1
comma
l_int|0xce
comma
l_int|0xcd
comma
l_int|0xcc
comma
l_int|0xcb
comma
l_int|0xca
comma
l_int|0xc9
comma
l_int|0xc7
comma
l_int|0xc6
comma
l_int|0xc5
comma
l_int|0xc3
comma
l_int|0xbc
comma
l_int|0xba
comma
l_int|0xb9
comma
l_int|0xb6
comma
l_int|0xb5
comma
l_int|0xb4
comma
l_int|0xb3
comma
l_int|0xb2
comma
l_int|0xb1
comma
l_int|0xae
comma
l_int|0xad
comma
l_int|0xac
comma
l_int|0xab
comma
l_int|0xaa
comma
l_int|0xa9
comma
l_int|0xa7
comma
l_int|0xa6
comma
l_int|0xa5
comma
l_int|0xa3
comma
l_int|0x9f
comma
l_int|0x9e
comma
l_int|0x9d
comma
l_int|0x9b
comma
l_int|0x98
comma
l_int|0x97
comma
l_int|0x90
comma
l_int|0x8f
comma
l_int|0x88
comma
l_int|0x84
comma
l_int|0x82
comma
l_int|0x81
comma
l_int|0x80
comma
l_int|0x7c
comma
l_int|0x7a
comma
l_int|0x79
comma
l_int|0x76
comma
l_int|0x75
comma
l_int|0x74
comma
l_int|0x73
comma
l_int|0x72
comma
l_int|0x71
comma
l_int|0x6e
comma
l_int|0x6d
comma
l_int|0x6c
comma
l_int|0x6b
comma
l_int|0x6a
comma
l_int|0x69
comma
l_int|0x67
comma
l_int|0x66
comma
l_int|0x65
comma
l_int|0x63
comma
l_int|0x5c
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0x54
comma
l_int|0x53
comma
l_int|0x52
comma
l_int|0x51
comma
l_int|0x4e
comma
l_int|0x4d
comma
l_int|0x4c
comma
l_int|0x4b
comma
l_int|0x4a
comma
l_int|0x49
comma
l_int|0x47
comma
l_int|0x46
comma
l_int|0x45
comma
l_int|0x43
comma
l_int|0x3c
comma
l_int|0x3a
comma
l_int|0x39
comma
l_int|0x36
comma
l_int|0x35
comma
l_int|0x34
comma
l_int|0x33
comma
l_int|0x32
comma
l_int|0x31
comma
l_int|0x2e
comma
l_int|0x2d
comma
l_int|0x2c
comma
l_int|0x2b
comma
l_int|0x2a
comma
l_int|0x29
comma
l_int|0x27
comma
l_int|0x26
comma
l_int|0x25
comma
l_int|0x23
comma
l_int|0x1f
comma
l_int|0x1e
comma
l_int|0x1d
comma
l_int|0x1b
comma
l_int|0x18
comma
l_int|0x17
comma
l_int|0x10
comma
l_int|0x0f
comma
l_int|0x08
comma
l_int|0x04
comma
l_int|0x02
comma
l_int|0x01
comma
l_int|0x00
)brace
suffix:semicolon
r_static
r_int
id|fcal_encode_addr
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|u16
op_star
id|addr
comma
id|fc_channel
op_star
id|fc
comma
id|fcp_cmnd
op_star
id|fcmd
)paren
suffix:semicolon
DECL|function|fcal_slave_attach
r_int
id|fcal_slave_attach
c_func
(paren
id|Scsi_Device
op_star
id|device
)paren
(brace
r_int
id|depth_to_use
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;tagged_supported
)paren
id|depth_to_use
op_assign
multiline_comment|/* 254 */
l_int|8
suffix:semicolon
r_else
id|depth_to_use
op_assign
l_int|2
suffix:semicolon
id|scsi_adjust_queue_depth
c_func
(paren
id|device
comma
(paren
id|device-&gt;tagged_supported
ques
c_cond
id|MSG_SIMPLE_TAG
suffix:colon
l_int|0
)paren
comma
id|depth_to_use
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Detect all FC Arbitrated Loops attached to the machine.&n;   fc4 module has done all the work for us... */
DECL|function|fcal_detect
r_int
id|__init
id|fcal_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_int
id|nfcals
op_assign
l_int|0
suffix:semicolon
id|fc_channel
op_star
id|fc
suffix:semicolon
r_int
id|fcalcount
suffix:semicolon
r_int
id|i
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;fcal&quot;
suffix:semicolon
id|fcalcount
op_assign
l_int|0
suffix:semicolon
id|for_each_online_fc_channel
c_func
(paren
id|fc
)paren
r_if
c_cond
(paren
id|fc-&gt;posmap
)paren
id|fcalcount
op_increment
suffix:semicolon
id|FCALND
c_func
(paren
(paren
l_string|&quot;%d channels online&bslash;n&quot;
comma
id|fcalcount
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|fcalcount
)paren
(brace
macro_line|#if defined(MODULE) &amp;&amp; defined(CONFIG_FC4_SOCAL_MODULE) &amp;&amp; defined(CONFIG_KMOD)
id|request_module
c_func
(paren
l_string|&quot;socal&quot;
)paren
suffix:semicolon
id|for_each_online_fc_channel
c_func
(paren
id|fc
)paren
r_if
c_cond
(paren
id|fc-&gt;posmap
)paren
id|fcalcount
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fcalcount
)paren
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|for_each_online_fc_channel
c_func
(paren
id|fc
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_int
op_star
id|ages
suffix:semicolon
r_struct
id|fcal
op_star
id|fcal
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fc-&gt;posmap
)paren
r_continue
suffix:semicolon
multiline_comment|/* Strange, this is already registered to some other SCSI host, then it cannot be fcal */
r_if
c_cond
(paren
id|fc-&gt;scsi_name
(braket
l_int|0
)braket
)paren
r_continue
suffix:semicolon
id|memcpy
(paren
id|fc-&gt;scsi_name
comma
l_string|&quot;FCAL&quot;
comma
l_int|4
)paren
suffix:semicolon
id|fc-&gt;can_queue
op_assign
id|FCAL_CAN_QUEUE
suffix:semicolon
id|fc-&gt;rsp_size
op_assign
l_int|64
suffix:semicolon
id|fc-&gt;encode_addr
op_assign
id|fcal_encode_addr
suffix:semicolon
id|ages
op_assign
id|kmalloc
(paren
l_int|128
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ages
)paren
r_continue
suffix:semicolon
id|host
op_assign
id|scsi_register
(paren
id|tpnt
comma
r_sizeof
(paren
r_struct
id|fcal
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
(brace
id|kfree
c_func
(paren
id|ages
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|nfcals
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|fc-&gt;module
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|fc-&gt;module
)paren
suffix:semicolon
id|fcal
op_assign
(paren
r_struct
id|fcal
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|fc
op_member_access_from_pointer
id|fcp_register
c_func
(paren
id|fc
comma
id|TYPE_SCSI_FCP
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|fc-&gt;posmap-&gt;len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|status
comma
id|target
comma
id|alpa
suffix:semicolon
id|alpa
op_assign
id|fc-&gt;posmap-&gt;list
(braket
id|i
)braket
suffix:semicolon
id|FCALD
c_func
(paren
(paren
l_string|&quot;Sending PLOGI to %02x&bslash;n&quot;
comma
id|alpa
)paren
)paren
id|target
op_assign
id|alpa2target
(braket
id|alpa
)braket
suffix:semicolon
id|status
op_assign
id|fc_do_plogi
c_func
(paren
id|fc
comma
id|alpa
comma
id|fcal-&gt;node_wwn
op_plus
id|target
comma
id|fcal-&gt;nport_wwn
op_plus
id|target
)paren
suffix:semicolon
id|FCALD
c_func
(paren
(paren
l_string|&quot;PLOGI returned with status %d&bslash;n&quot;
comma
id|status
)paren
)paren
r_if
c_cond
(paren
id|status
op_ne
id|FC_STATUS_OK
)paren
r_continue
suffix:semicolon
id|FCALD
c_func
(paren
(paren
l_string|&quot;Sending PRLI to %02x&bslash;n&quot;
comma
id|alpa
)paren
)paren
id|status
op_assign
id|fc_do_prli
c_func
(paren
id|fc
comma
id|alpa
)paren
suffix:semicolon
id|FCALD
c_func
(paren
(paren
l_string|&quot;PRLI returned with status %d&bslash;n&quot;
comma
id|status
)paren
)paren
r_if
c_cond
(paren
id|status
op_eq
id|FC_STATUS_OK
)paren
id|fcal-&gt;map
(braket
id|target
)braket
op_assign
l_int|1
suffix:semicolon
)brace
id|host-&gt;max_id
op_assign
l_int|127
suffix:semicolon
id|host-&gt;irq
op_assign
id|fc-&gt;irq
suffix:semicolon
macro_line|#ifdef __sparc_v9__
id|host-&gt;unchecked_isa_dma
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|fc-&gt;channels
op_assign
l_int|1
suffix:semicolon
id|fc-&gt;targets
op_assign
l_int|127
suffix:semicolon
id|fc-&gt;ages
op_assign
id|ages
suffix:semicolon
id|memset
(paren
id|ages
comma
l_int|0
comma
l_int|128
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|fcal-&gt;fc
op_assign
id|fc
suffix:semicolon
id|FCALD
c_func
(paren
(paren
l_string|&quot;Found FCAL&bslash;n&quot;
)paren
)paren
)brace
r_if
c_cond
(paren
id|nfcals
)paren
macro_line|#ifdef __sparc__
id|printk
(paren
l_string|&quot;FCAL: Total of %d Sun Enterprise Network Array (A5000 or EX500) channels found&bslash;n&quot;
comma
id|nfcals
)paren
suffix:semicolon
macro_line|#else
id|printk
(paren
l_string|&quot;FCAL: Total of %d Fibre Channel Arbitrated Loops found&bslash;n&quot;
comma
id|nfcals
)paren
suffix:semicolon
macro_line|#endif
r_return
id|nfcals
suffix:semicolon
)brace
DECL|function|fcal_release
r_int
id|fcal_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_struct
id|fcal
op_star
id|fcal
op_assign
(paren
r_struct
id|fcal
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|fc_channel
op_star
id|fc
op_assign
id|fcal-&gt;fc
suffix:semicolon
r_if
c_cond
(paren
id|fc-&gt;module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|fc-&gt;module
)paren
suffix:semicolon
id|fc
op_member_access_from_pointer
id|fcp_register
c_func
(paren
id|fc
comma
id|TYPE_SCSI_FCP
comma
l_int|1
)paren
suffix:semicolon
id|FCALND
c_func
(paren
(paren
l_string|&quot; releasing fcal.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|kfree
(paren
id|fc-&gt;ages
)paren
suffix:semicolon
id|FCALND
c_func
(paren
(paren
l_string|&quot;released fcal!&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|SPRINTF
macro_line|#undef SPRINTF
DECL|macro|SPRINTF
mdefine_line|#define SPRINTF(args...) { if (pos &lt; (buffer + length)) pos += sprintf (pos, ## args); }
DECL|function|fcal_proc_info
r_int
id|fcal_proc_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|fcal
op_star
id|fcal
suffix:semicolon
id|fc_channel
op_star
id|fc
suffix:semicolon
r_char
op_star
id|pos
op_assign
id|buffer
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|host
op_assign
id|scsi_host_hn_get
c_func
(paren
id|hostno
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
id|inout
)paren
r_return
id|length
suffix:semicolon
id|fcal
op_assign
(paren
r_struct
id|fcal
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|fc
op_assign
id|fcal-&gt;fc
suffix:semicolon
macro_line|#ifdef __sparc__
id|SPRINTF
(paren
l_string|&quot;Sun Enterprise Network Array (A5000 or E?500) on %s PROM node %x&bslash;n&quot;
comma
id|fc-&gt;name
comma
id|fc-&gt;dev-&gt;prom_node
)paren
suffix:semicolon
macro_line|#else
id|SPRINTF
(paren
l_string|&quot;Fibre Channel Arbitrated Loop on %s&bslash;n&quot;
comma
id|fc-&gt;name
)paren
suffix:semicolon
macro_line|#endif
id|SPRINTF
(paren
l_string|&quot;Initiator AL-PA: %02x&bslash;n&quot;
comma
id|fc-&gt;sid
)paren
suffix:semicolon
id|SPRINTF
(paren
l_string|&quot;&bslash;nAttached devices: %s&bslash;n&quot;
comma
id|host-&gt;host_queue
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;none&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|fc-&gt;posmap-&gt;len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|alpa
op_assign
id|fc-&gt;posmap-&gt;list
(braket
id|i
)braket
suffix:semicolon
r_int
r_char
id|target
suffix:semicolon
id|u32
op_star
id|u1
comma
op_star
id|u2
suffix:semicolon
id|target
op_assign
id|alpa2target
(braket
id|alpa
)braket
suffix:semicolon
id|u1
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|fcal-&gt;nport_wwn
(braket
id|target
)braket
suffix:semicolon
id|u2
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|fcal-&gt;node_wwn
(braket
id|target
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|u1
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|u1
(braket
l_int|1
)braket
)paren
(brace
id|SPRINTF
(paren
l_string|&quot;  [AL-PA: %02x] Not responded to PLOGI&bslash;n&quot;
comma
id|alpa
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|fcal-&gt;map
(braket
id|target
)braket
)paren
(brace
id|SPRINTF
(paren
l_string|&quot;  [AL-PA: %02x, Port WWN: %08x%08x, Node WWN: %08x%08x] Not responded to PRLI&bslash;n&quot;
comma
id|alpa
comma
id|u1
(braket
l_int|0
)braket
comma
id|u1
(braket
l_int|1
)braket
comma
id|u2
(braket
l_int|0
)braket
comma
id|u2
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|Scsi_Device
op_star
id|scd
suffix:semicolon
r_for
c_loop
(paren
id|scd
op_assign
id|host-&gt;host_queue
suffix:semicolon
id|scd
suffix:semicolon
id|scd
op_assign
id|scd-&gt;next
)paren
r_if
c_cond
(paren
id|scd-&gt;host-&gt;host_no
op_eq
id|hostno
op_logical_and
id|scd-&gt;id
op_eq
id|target
)paren
(brace
id|SPRINTF
(paren
l_string|&quot;  [AL-PA: %02x, Id: %02d, Port WWN: %08x%08x, Node WWN: %08x%08x]  &quot;
comma
id|alpa
comma
id|target
comma
id|u1
(braket
l_int|0
)braket
comma
id|u1
(braket
l_int|1
)braket
comma
id|u2
(braket
l_int|0
)braket
comma
id|u2
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|SPRINTF
(paren
l_string|&quot;%s &quot;
comma
(paren
id|scd-&gt;type
OL
id|MAX_SCSI_DEVICE_CODE
)paren
ques
c_cond
id|scsi_device_types
(braket
(paren
r_int
)paren
id|scd-&gt;type
)braket
suffix:colon
l_string|&quot;Unknown device&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
(paren
id|j
OL
l_int|8
)paren
op_logical_and
(paren
id|scd-&gt;vendor
(braket
id|j
)braket
op_ge
l_int|0x20
)paren
suffix:semicolon
id|j
op_increment
)paren
id|SPRINTF
(paren
l_string|&quot;%c&quot;
comma
id|scd-&gt;vendor
(braket
id|j
)braket
)paren
suffix:semicolon
id|SPRINTF
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
(paren
id|j
OL
l_int|16
)paren
op_logical_and
(paren
id|scd-&gt;model
(braket
id|j
)braket
op_ge
l_int|0x20
)paren
suffix:semicolon
id|j
op_increment
)paren
id|SPRINTF
(paren
l_string|&quot;%c&quot;
comma
id|scd-&gt;model
(braket
id|j
)braket
)paren
suffix:semicolon
id|SPRINTF
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
id|SPRINTF
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pos
op_minus
id|buffer
)paren
OL
id|offset
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pos
op_minus
id|buffer
op_minus
id|offset
OL
id|length
)paren
r_return
id|pos
op_minus
id|buffer
op_minus
id|offset
suffix:semicolon
r_else
r_return
id|length
suffix:semicolon
)brace
multiline_comment|/* &n;   For FC-AL, we use a simple addressing: we have just one channel 0,&n;   and all AL-PAs are mapped to targets 0..0x7e&n; */
DECL|function|fcal_encode_addr
r_static
r_int
id|fcal_encode_addr
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|u16
op_star
id|addr
comma
id|fc_channel
op_star
id|fc
comma
id|fcp_cmnd
op_star
id|fcmd
)paren
(brace
r_struct
id|fcal
op_star
id|f
suffix:semicolon
multiline_comment|/* We don&squot;t support LUNs yet - I&squot;m not sure if LUN should be in SCSI fcp_cdb, or in second byte of addr[0] */
r_if
c_cond
(paren
id|SCpnt-&gt;cmnd
(braket
l_int|1
)braket
op_amp
l_int|0xe0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* FC-PLDA tells us... */
id|memset
c_func
(paren
id|addr
comma
l_int|0
comma
l_int|8
)paren
suffix:semicolon
id|f
op_assign
(paren
r_struct
id|fcal
op_star
)paren
id|SCpnt-&gt;host-&gt;hostdata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;map
(braket
id|SCpnt-&gt;target
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Now, determine DID: It will be Native Identifier, so we zero upper&n;&t;   2 bytes of the 3 byte DID, lowest byte will be AL-PA */
id|fcmd-&gt;did
op_assign
id|target2alpa
(braket
id|SCpnt-&gt;target
)braket
suffix:semicolon
id|FCALD
c_func
(paren
(paren
l_string|&quot;trying DID %06x&bslash;n&quot;
comma
id|fcmd-&gt;did
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|FCAL
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
