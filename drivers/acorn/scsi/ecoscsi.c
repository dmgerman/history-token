DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
multiline_comment|/* #define PSEUDO_DMA */
multiline_comment|/*&n; * EcoSCSI Generic NCR5380 driver&n; *&n; * Copyright 1995, Russell King&n; *&n; * ALPHA RELEASE 1.&n; *&n; * For more information, please consult&n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * Options :&n; *&n; * PARITY - enable parity checking.  Not supported.&n; *&n; * SCSI2 - enable support for SCSI-II tagged queueing.  Untested.&n; *&n; * USLEEP - enable support for devices that don&squot;t disconnect.  Untested.&n; */
multiline_comment|/*&n; * $Log: ecoscsi.c,v $&n; * Revision 1.2  1998/03/08 05:49:47  davem&n; * Merge to 2.1.89&n; *&n; * Revision 1.1  1998/02/23 02:45:24  davem&n; * Merge to 2.1.88&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;../../scsi/scsi.h&quot;
macro_line|#include &quot;../../scsi/hosts.h&quot;
macro_line|#include &quot;../../scsi/NCR5380.h&quot;
DECL|macro|ECOSCSI_PUBLIC_RELEASE
mdefine_line|#define ECOSCSI_PUBLIC_RELEASE 1
DECL|function|ecoscsi_read
r_static
r_char
id|ecoscsi_read
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
id|reg
)paren
(brace
r_int
id|iobase
op_assign
id|instance-&gt;io_port
suffix:semicolon
id|outb
c_func
(paren
id|reg
op_or
l_int|8
comma
id|iobase
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|iobase
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ecoscsi_write
r_static
r_void
id|ecoscsi_write
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
id|reg
comma
r_int
id|value
)paren
(brace
r_int
id|iobase
op_assign
id|instance-&gt;io_port
suffix:semicolon
id|outb
c_func
(paren
id|reg
op_or
l_int|8
comma
id|iobase
)paren
suffix:semicolon
id|outb
c_func
(paren
id|value
comma
id|iobase
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : ecoscsi_setup(char *str, int *ints)&n; *&n; * Purpose : LILO command line initialization of the overrides array,&n; *&n; * Inputs : str - unused, ints - array of integer parameters with ints[0]&n; *&t;equal to the number of ints.&n; *&n; */
DECL|function|ecoscsi_setup
r_void
id|ecoscsi_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
)brace
multiline_comment|/*&n; * Function : int ecoscsi_detect(Scsi_Host_Template * tpnt)&n; *&n; * Purpose : initializes ecoscsi NCR5380 driver based on the&n; *&t;command line / compile time port and irq definitions.&n; *&n; * Inputs : tpnt - template for this SCSI adapter.&n; *&n; * Returns : 1 if a host adapter was found, 0 if not.&n; *&n; */
DECL|function|ecoscsi_detect
r_int
id|ecoscsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;ecoscsi&quot;
suffix:semicolon
id|instance
op_assign
id|scsi_register
(paren
id|tpnt
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
id|instance
)paren
r_return
l_int|0
suffix:semicolon
id|instance-&gt;io_port
op_assign
l_int|0x80ce8000
suffix:semicolon
id|instance-&gt;n_io_port
op_assign
l_int|144
suffix:semicolon
id|instance-&gt;irq
op_assign
id|IRQ_NONE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|request_region
c_func
(paren
id|instance-&gt;io_port
comma
id|instance-&gt;n_io_port
comma
l_string|&quot;ecoscsi&quot;
)paren
)paren
)paren
r_goto
id|unregister_scsi
suffix:semicolon
id|ecoscsi_write
(paren
id|instance
comma
id|MODE_REG
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* Is it really SCSI? */
r_if
c_cond
(paren
id|ecoscsi_read
(paren
id|instance
comma
id|MODE_REG
)paren
op_ne
l_int|0x20
)paren
multiline_comment|/* Write to a reg.    */
r_goto
id|release_reg
suffix:semicolon
id|ecoscsi_write
c_func
(paren
id|instance
comma
id|MODE_REG
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* it back.&t;      */
r_if
c_cond
(paren
id|ecoscsi_read
(paren
id|instance
comma
id|MODE_REG
)paren
op_ne
l_int|0x00
)paren
r_goto
id|release_reg
suffix:semicolon
id|NCR5380_init
c_func
(paren
id|instance
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_ne
id|IRQ_NONE
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|instance-&gt;irq
comma
id|do_ecoscsi_intr
comma
id|SA_INTERRUPT
comma
l_string|&quot;ecoscsi&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: IRQ%d not free, interrupts disabled&bslash;n&quot;
comma
id|instance-&gt;host_no
comma
id|instance-&gt;irq
)paren
suffix:semicolon
id|instance-&gt;irq
op_assign
id|IRQ_NONE
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|instance-&gt;irq
op_ne
id|IRQ_NONE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: eek! Interrupts enabled, but I don&squot;t think&bslash;n&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scsi%d: that the board had an interrupt!&bslash;n&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: at port %X irq&quot;
comma
id|instance-&gt;host_no
comma
id|instance-&gt;io_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_eq
id|IRQ_NONE
)paren
id|printk
(paren
l_string|&quot;s disabled&quot;
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot; %d&quot;
comma
id|instance-&gt;irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; options CAN_QUEUE=%d CMD_PER_LUN=%d release=%d&quot;
comma
id|CAN_QUEUE
comma
id|CMD_PER_LUN
comma
id|ECOSCSI_PUBLIC_RELEASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nscsi%d:&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
id|NCR5380_print_options
c_func
(paren
id|instance
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|release_reg
suffix:colon
id|release_region
c_func
(paren
id|instance-&gt;io_port
comma
id|instance-&gt;n_io_port
)paren
suffix:semicolon
id|unregister_scsi
suffix:colon
id|scsi_unregister
c_func
(paren
id|instance
)paren
suffix:semicolon
r_return
l_int|0
)brace
DECL|function|ecoscsi_release
r_int
id|ecoscsi_release
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
(brace
r_if
c_cond
(paren
id|shpnt-&gt;irq
op_ne
id|IRQ_NONE
)paren
id|free_irq
(paren
id|shpnt-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shpnt-&gt;io_port
)paren
id|release_region
(paren
id|shpnt-&gt;io_port
comma
id|shpnt-&gt;n_io_port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ecoscsi_info
r_const
r_char
op_star
id|ecoscsi_info
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
macro_line|#if 0
mdefine_line|#define STAT(p) inw(p + 144)
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
r_int
id|iobase2
op_assign
id|instance-&gt;io_port
op_plus
l_int|0x100
suffix:semicolon
r_int
r_char
op_star
id|start
op_assign
id|addr
suffix:semicolon
r_int
id|s
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
id|outb
c_func
(paren
id|inb
c_func
(paren
id|iobase
op_plus
l_int|128
)paren
comma
id|iobase
op_plus
l_int|135
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
id|b
comma
id|i
comma
id|timeout
suffix:semicolon
id|timeout
op_assign
l_int|0x07FFFFFF
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
l_string|&quot;status = %p&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|iobase
op_plus
l_int|135
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|64
suffix:semicolon
id|i
op_increment
)paren
(brace
id|b
op_assign
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
l_int|128
suffix:semicolon
)brace
r_else
(brace
id|b
op_assign
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
id|outb
c_func
(paren
l_int|0
comma
id|iobase
op_plus
l_int|135
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;first bytes = %02X %02X %02X %20X %02X %02X %02X&bslash;n&quot;
comma
op_star
id|start
comma
id|start
(braket
l_int|1
)braket
comma
id|start
(braket
l_int|2
)braket
comma
id|start
(braket
l_int|3
)braket
comma
id|start
(braket
l_int|4
)braket
comma
id|start
(braket
l_int|5
)braket
comma
id|start
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|STAT
macro_line|#undef STAT
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    int port, ctrl
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;        struct Scsi_Host *_instance
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;        _instance = instance
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) ecoscsi_read(_instance, reg)
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) ecoscsi_write(_instance, reg, value)
DECL|macro|do_NCR5380_intr
mdefine_line|#define do_NCR5380_intr do_ecoscsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command ecoscsi_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort ecoscsi_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset ecoscsi_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info ecoscsi_proc_info
r_int
id|NCR5380_proc_info
c_func
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
suffix:semicolon
DECL|macro|BOARD_NORMAL
mdefine_line|#define BOARD_NORMAL&t;0
DECL|macro|BOARD_NCR53C400
mdefine_line|#define BOARD_NCR53C400&t;1
macro_line|#include &quot;../../scsi/NCR5380.c&quot;
DECL|variable|ecoscsi_template
r_static
id|Scsi_Host_Template
id|ecoscsi_template
op_assign
(brace
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;Serial Port EcoSCSI NCR5380&quot;
comma
dot
id|detect
op_assign
id|ecoscsi_detect
comma
dot
id|release
op_assign
id|ecoscsi_release
comma
dot
id|info
op_assign
id|ecoscsi_info
comma
dot
id|queuecommand
op_assign
id|ecoscsi_queue_command
comma
dot
m_abort
op_assign
id|ecoscsi_abort
comma
dot
id|reset
op_assign
id|ecoscsi_reset
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
)brace
suffix:semicolon
DECL|function|ecoscsi_init
r_static
r_int
id|__init
id|ecoscsi_init
c_func
(paren
r_void
)paren
(brace
id|scsi_register_host
c_func
(paren
op_amp
id|ecoscsi_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ecoscsi_template.present
)paren
r_return
l_int|0
suffix:semicolon
id|scsi_unregister_host
c_func
(paren
op_amp
id|ecoscsi_template
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|ecoscsi_exit
r_static
r_void
id|__exit
id|ecoscsi_exit
c_func
(paren
r_void
)paren
(brace
id|scsi_unregister_host
c_func
(paren
op_amp
id|ecoscsi_template
)paren
suffix:semicolon
)brace
DECL|variable|ecoscsi_init
id|module_init
c_func
(paren
id|ecoscsi_init
)paren
suffix:semicolon
DECL|variable|ecoscsi_exit
id|module_exit
c_func
(paren
id|ecoscsi_exit
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
l_string|&quot;Econet-SCSI driver for Acorn machines&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
