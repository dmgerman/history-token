DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
multiline_comment|/*#define PSEUDO_DMA*/
multiline_comment|/*&n; * Oak Generic NCR5380 driver&n; *&n; * Copyright 1995, Russell King&n; *&n; * ALPHA RELEASE 1.&n; *&n; * For more information, please consult&n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * Options :&n; *&n; * PARITY - enable parity checking.  Not supported.&n; *&n; * SCSI2 - enable support for SCSI-II tagged queueing.  Untested.&n; *&n; * USLEEP - enable support for devices that don&squot;t disconnect.  Untested.&n; */
multiline_comment|/*&n; * $Log: oak.c,v $&n; * Revision 1.3  1998/05/03 20:45:37  alan&n; * ARM SCSI update. This adds the eesox driver and massively updates the&n; * Cumana driver. The folks who bought cumana arent anal retentive all&n; * docs are secret weenies so now there are docs ..&n; *&n; * Revision 1.2  1998/03/08 05:49:48  davem&n; * Merge to 2.1.89&n; *&n; * Revision 1.1  1998/02/23 02:45:27  davem&n; * Merge to 2.1.88&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;../../scsi/scsi.h&quot;
macro_line|#include &quot;../../scsi/hosts.h&quot;
macro_line|#include &quot;../../scsi/constants.h&quot;
DECL|macro|OAKSCSI_PUBLIC_RELEASE
mdefine_line|#define OAKSCSI_PUBLIC_RELEASE 1
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg)&t;&t;oakscsi_read(_instance, reg)
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value)&t;oakscsi_write(_instance, reg, value)
DECL|macro|do_NCR5380_intr
mdefine_line|#define do_NCR5380_intr&t;&t;&t;do_oakscsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command&t;&t;oakscsi_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort&t;&t;&t;oakscsi_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset&t;&t;&t;oakscsi_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info&t;&t;oakscsi_proc_info
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
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;&t;int port, ctrl
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;        struct Scsi_Host *_instance
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;        _instance = instance
DECL|macro|BOARD_NORMAL
mdefine_line|#define BOARD_NORMAL&t;0
DECL|macro|BOARD_NCR53C400
mdefine_line|#define BOARD_NCR53C400&t;1
macro_line|#include &quot;../../scsi/NCR5380.h&quot;
DECL|macro|START_DMA_INITIATOR_RECEIVE_REG
macro_line|#undef START_DMA_INITIATOR_RECEIVE_REG
DECL|macro|START_DMA_INITIATOR_RECEIVE_REG
mdefine_line|#define START_DMA_INITIATOR_RECEIVE_REG (7 + 128)
DECL|variable|oakscsi_cids
r_static
r_const
id|card_ids
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
DECL|macro|OAK_ADDRESS
mdefine_line|#define OAK_ADDRESS(card) (ecard_address((card), ECARD_MEMC, 0))
DECL|macro|OAK_IRQ
mdefine_line|#define OAK_IRQ(card)&t;  (IRQ_NONE)
multiline_comment|/*&n; * Function : int oakscsi_detect(Scsi_Host_Template * tpnt)&n; *&n; * Purpose : initializes oak NCR5380 driver based on the&n; *&t;command line / compile time port and irq definitions.&n; *&n; * Inputs : tpnt - template for this SCSI adapter.&n; *&n; * Returns : 1 if a host adapter was found, 0 if not.&n; *&n; */
DECL|variable|ecs
r_static
r_struct
id|expansion_card
op_star
id|ecs
(braket
l_int|4
)braket
suffix:semicolon
DECL|function|oakscsi_detect
r_int
id|oakscsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;oakscsi&quot;
suffix:semicolon
id|memset
(paren
id|ecs
comma
l_int|0
comma
r_sizeof
(paren
id|ecs
)paren
)paren
suffix:semicolon
id|ecard_startfind
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|ecs
(braket
id|count
)braket
op_assign
id|ecard_find
c_func
(paren
l_int|0
comma
id|oakscsi_cids
)paren
)paren
op_eq
l_int|NULL
)paren
r_break
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
id|instance-&gt;io_port
op_assign
id|OAK_ADDRESS
c_func
(paren
id|ecs
(braket
id|count
)braket
)paren
suffix:semicolon
id|instance-&gt;irq
op_assign
id|OAK_IRQ
c_func
(paren
id|ecs
(braket
id|count
)braket
)paren
suffix:semicolon
id|NCR5380_init
c_func
(paren
id|instance
comma
l_int|0
)paren
suffix:semicolon
id|ecard_claim
c_func
(paren
id|ecs
(braket
id|count
)braket
)paren
suffix:semicolon
id|instance-&gt;n_io_port
op_assign
l_int|255
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
(paren
id|instance-&gt;io_port
comma
id|instance-&gt;n_io_port
comma
l_string|&quot;Oak SCSI&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_ne
id|IRQ_NONE
)paren
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|instance-&gt;irq
comma
id|do_oakscsi_intr
comma
id|SA_INTERRUPT
comma
l_string|&quot;Oak SCSI&quot;
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
l_string|&quot;scsi%d: at port %lX irq&quot;
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
l_string|&quot; options CAN_QUEUE=%d  CMD_PER_LUN=%d release=%d&quot;
comma
id|tpnt-&gt;can_queue
comma
id|tpnt-&gt;cmd_per_lun
comma
id|OAKSCSI_PUBLIC_RELEASE
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
op_increment
id|count
suffix:semicolon
)brace
macro_line|#ifdef MODULE
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No oak scsi devices found&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|count
suffix:semicolon
)brace
DECL|function|oakscsi_release
r_int
id|oakscsi_release
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
(brace
r_int
id|i
suffix:semicolon
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|shpnt-&gt;io_port
op_eq
id|OAK_ADDRESS
c_func
(paren
id|ecs
(braket
id|i
)braket
)paren
)paren
id|ecard_release
(paren
id|ecs
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
macro_line|#include &quot;../../scsi/NCR5380.c&quot;
DECL|variable|oakscsi_template
r_static
id|Scsi_Host_Template
id|oakscsi_template
op_assign
(brace
id|module
suffix:colon
id|THIS_MODULE
comma
id|proc_info
suffix:colon
id|oakscsi_proc_info
comma
id|name
suffix:colon
l_string|&quot;Oak 16-bit SCSI&quot;
comma
id|detect
suffix:colon
id|oakscsi_detect
comma
id|release
suffix:colon
id|oakscsi_release
comma
id|info
suffix:colon
id|oakscsi_info
comma
id|queuecommand
suffix:colon
id|oakscsi_queue_command
comma
m_abort
suffix:colon
id|oakscsi_abort
comma
id|reset
suffix:colon
id|oakscsi_reset
comma
id|can_queue
suffix:colon
l_int|16
comma
id|this_id
suffix:colon
l_int|7
comma
id|sg_tablesize
suffix:colon
id|SG_ALL
comma
id|cmd_per_lun
suffix:colon
l_int|2
comma
id|use_clustering
suffix:colon
id|DISABLE_CLUSTERING
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
id|scsi_register_host
c_func
(paren
op_amp
id|oakscsi_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oakscsi_template.present
)paren
r_return
l_int|0
suffix:semicolon
id|scsi_unregister_host
c_func
(paren
op_amp
id|oakscsi_template
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
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
id|scsi_unregister_host
c_func
(paren
op_amp
id|oakscsi_template
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
id|EXPORT_NO_SYMBOLS
suffix:semicolon
eof
