multiline_comment|/*&n; * Oak Generic NCR5380 driver&n; *&n; * Copyright 1995-2002, Russell King&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;../scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
multiline_comment|/*#define PSEUDO_DMA*/
DECL|macro|OAKSCSI_PUBLIC_RELEASE
mdefine_line|#define OAKSCSI_PUBLIC_RELEASE 1
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg)&t;&t;oakscsi_read(_instance, reg)
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value)&t;oakscsi_write(_instance, reg, value)
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr&t;&t;&t;oakscsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command&t;&t;oakscsi_queue_command
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info&t;&t;oakscsi_proc_info
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields&t;int port, ctrl
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare()&t;&t;struct Scsi_Host *_instance
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance)&t;&t;_instance = instance
DECL|macro|BOARD_NORMAL
mdefine_line|#define BOARD_NORMAL&t;0
DECL|macro|BOARD_NCR53C400
mdefine_line|#define BOARD_NCR53C400&t;1
macro_line|#include &quot;../NCR5380.h&quot;
DECL|macro|START_DMA_INITIATOR_RECEIVE_REG
macro_line|#undef START_DMA_INITIATOR_RECEIVE_REG
DECL|macro|START_DMA_INITIATOR_RECEIVE_REG
mdefine_line|#define START_DMA_INITIATOR_RECEIVE_REG (7 + 128)
DECL|function|oakscsi_info
r_const
r_char
op_star
id|oakscsi_info
(paren
r_struct
id|Scsi_Host
op_star
id|spnt
)paren
(brace
r_return
l_string|&quot;&quot;
suffix:semicolon
)brace
DECL|macro|STAT
mdefine_line|#define STAT(p)   inw(p + 144)
r_extern
r_void
id|inswb
c_func
(paren
r_int
id|from
comma
r_void
op_star
id|to
comma
r_int
id|len
)paren
suffix:semicolon
DECL|function|NCR5380_pwrite
r_static
r_inline
r_int
id|NCR5380_pwrite
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
r_char
op_star
id|addr
comma
r_int
id|len
)paren
(brace
r_int
id|iobase
op_assign
id|instance-&gt;io_port
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;writing %p len %d&bslash;n&quot;
comma
id|addr
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|status
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|status
op_assign
id|STAT
c_func
(paren
id|iobase
)paren
)paren
op_amp
l_int|0x100
)paren
op_eq
l_int|0
)paren
(brace
suffix:semicolon
)brace
)brace
)brace
DECL|function|NCR5380_pread
r_static
r_inline
r_int
id|NCR5380_pread
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
r_char
op_star
id|addr
comma
r_int
id|len
)paren
(brace
r_int
id|iobase
op_assign
id|instance-&gt;io_port
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;reading %p len %d&bslash;n&quot;
comma
id|addr
comma
id|len
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
id|status
comma
id|timeout
suffix:semicolon
r_int
r_int
id|b
suffix:semicolon
id|timeout
op_assign
l_int|0x01FFFFFF
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|status
op_assign
id|STAT
c_func
(paren
id|iobase
)paren
)paren
op_amp
l_int|0x100
)paren
op_eq
l_int|0
)paren
(brace
id|timeout
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x200
op_logical_or
op_logical_neg
id|timeout
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;status = %08X&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
op_ge
l_int|128
)paren
(brace
id|inswb
c_func
(paren
id|iobase
op_plus
l_int|136
comma
id|addr
comma
l_int|128
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|128
suffix:semicolon
id|len
op_sub_assign
l_int|128
suffix:semicolon
)brace
r_else
(brace
id|b
op_assign
(paren
r_int
r_int
)paren
id|inw
c_func
(paren
id|iobase
op_plus
l_int|136
)paren
suffix:semicolon
op_star
id|addr
op_increment
op_assign
id|b
suffix:semicolon
id|len
op_sub_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
op_star
id|addr
op_increment
op_assign
id|b
op_rshift
l_int|8
suffix:semicolon
)brace
id|len
op_sub_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|oakscsi_read
mdefine_line|#define oakscsi_read(instance,reg)&t;(inb((instance)-&gt;io_port + (reg)))
DECL|macro|oakscsi_write
mdefine_line|#define oakscsi_write(instance,reg,val)&t;(outb((val), (instance)-&gt;io_port + (reg)))
DECL|macro|STAT
macro_line|#undef STAT
macro_line|#include &quot;../NCR5380.c&quot;
DECL|variable|oakscsi_template
r_static
id|Scsi_Host_Template
id|oakscsi_template
op_assign
(brace
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|proc_info
op_assign
id|oakscsi_proc_info
comma
dot
id|name
op_assign
l_string|&quot;Oak 16-bit SCSI&quot;
comma
dot
id|info
op_assign
id|oakscsi_info
comma
dot
id|queuecommand
op_assign
id|oakscsi_queue_command
comma
dot
id|eh_abort_handler
op_assign
id|NCR5380_abort
comma
dot
id|eh_device_reset_handler
op_assign
id|NCR5380_device_reset
comma
dot
id|eh_bus_reset_handler
op_assign
id|NCR5380_bus_reset
comma
dot
id|eh_host_reset_handler
op_assign
id|NCR5380_host_reset
comma
dot
id|can_queue
op_assign
l_int|16
comma
dot
id|this_id
op_assign
l_int|7
comma
dot
id|sg_tablesize
op_assign
id|SG_ALL
comma
dot
id|cmd_per_lun
op_assign
l_int|2
comma
dot
id|use_clustering
op_assign
id|DISABLE_CLUSTERING
comma
dot
id|proc_name
op_assign
l_string|&quot;oakscsi&quot;
comma
)brace
suffix:semicolon
r_static
r_int
id|__devinit
DECL|function|oakscsi_probe
id|oakscsi_probe
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_const
r_struct
id|ecard_id
op_star
id|id
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|host
op_assign
id|scsi_host_alloc
c_func
(paren
op_amp
id|oakscsi_template
comma
r_sizeof
(paren
r_struct
id|NCR5380_hostdata
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
r_goto
id|out
suffix:semicolon
id|host-&gt;io_port
op_assign
id|ecard_address
c_func
(paren
id|ec
comma
id|ECARD_MEMC
comma
l_int|0
)paren
suffix:semicolon
id|host-&gt;irq
op_assign
id|IRQ_NONE
suffix:semicolon
id|host-&gt;n_io_port
op_assign
l_int|255
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
(paren
id|host-&gt;io_port
comma
id|host-&gt;n_io_port
comma
l_string|&quot;Oak SCSI&quot;
)paren
)paren
r_goto
id|unreg
suffix:semicolon
id|NCR5380_init
c_func
(paren
id|host
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scsi%d: at port 0x%08lx irqs disabled&quot;
comma
id|host-&gt;host_no
comma
id|host-&gt;io_port
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; options CAN_QUEUE=%d  CMD_PER_LUN=%d release=%d&quot;
comma
id|host-&gt;can_queue
comma
id|host-&gt;cmd_per_lun
comma
id|OAKSCSI_PUBLIC_RELEASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nscsi%d:&quot;
comma
id|host-&gt;host_no
)paren
suffix:semicolon
id|NCR5380_print_options
c_func
(paren
id|host
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|scsi_add_host
c_func
(paren
id|host
comma
op_amp
id|ec-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_release
suffix:semicolon
id|scsi_scan_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_release
suffix:colon
id|release_region
c_func
(paren
id|host-&gt;io_port
comma
id|host-&gt;n_io_port
)paren
suffix:semicolon
id|unreg
suffix:colon
id|scsi_host_put
c_func
(paren
id|host
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|oakscsi_remove
r_static
r_void
id|__devexit
id|oakscsi_remove
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|ecard_get_drvdata
c_func
(paren
id|ec
)paren
suffix:semicolon
id|ecard_set_drvdata
c_func
(paren
id|ec
comma
l_int|NULL
)paren
suffix:semicolon
id|scsi_remove_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|NCR5380_exit
c_func
(paren
id|host
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|host-&gt;io_port
comma
id|host-&gt;n_io_port
)paren
suffix:semicolon
id|scsi_host_put
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
DECL|variable|oakscsi_cids
r_static
r_const
r_struct
id|ecard_id
id|oakscsi_cids
(braket
)braket
op_assign
(brace
(brace
id|MANU_OAK
comma
id|PROD_OAK_SCSI
)brace
comma
(brace
l_int|0xffff
comma
l_int|0xffff
)brace
)brace
suffix:semicolon
DECL|variable|oakscsi_driver
r_static
r_struct
id|ecard_driver
id|oakscsi_driver
op_assign
(brace
dot
id|probe
op_assign
id|oakscsi_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|oakscsi_remove
)paren
comma
dot
id|id_table
op_assign
id|oakscsi_cids
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;oakscsi&quot;
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|oakscsi_init
r_static
r_int
id|__init
id|oakscsi_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ecard_register_driver
c_func
(paren
op_amp
id|oakscsi_driver
)paren
suffix:semicolon
)brace
DECL|function|oakscsi_exit
r_static
r_void
id|__exit
id|oakscsi_exit
c_func
(paren
r_void
)paren
(brace
id|ecard_remove_driver
c_func
(paren
op_amp
id|oakscsi_driver
)paren
suffix:semicolon
)brace
DECL|variable|oakscsi_init
id|module_init
c_func
(paren
id|oakscsi_init
)paren
suffix:semicolon
DECL|variable|oakscsi_exit
id|module_exit
c_func
(paren
id|oakscsi_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Oak SCSI driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
