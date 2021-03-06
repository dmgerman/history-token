multiline_comment|/*&n; * Generic Macintosh NCR5380 driver&n; *&n; * Copyright 1998, Michael Schmitz &lt;mschmitz@lbl.gov&gt;&n; *&n; * derived in part from:&n; */
multiline_comment|/*&n; * Generic Generic NCR5380 driver&n; *&n; * Copyright 1995, Russell King&n; *&n; * ALPHA RELEASE 1.&n; *&n; * For more information, please consult&n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: mac_NCR5380.c,v $&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt;
macro_line|#include &lt;asm/macints.h&gt;
macro_line|#include &lt;asm/machw.h&gt;
macro_line|#include &lt;asm/mac_via.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;mac_scsi.h&quot;
macro_line|#include &quot;NCR5380.h&quot;
macro_line|#if 0
mdefine_line|#define NDEBUG (NDEBUG_INTR | NDEBUG_PSEUDO_DMA | NDEBUG_ARBITRATION | NDEBUG_SELECTION | NDEBUG_RESELECTION)
macro_line|#else
DECL|macro|NDEBUG
mdefine_line|#define NDEBUG (NDEBUG_ABORT)
macro_line|#endif
DECL|macro|RESET_BOOT
mdefine_line|#define RESET_BOOT
DECL|macro|DRIVER_SETUP
mdefine_line|#define DRIVER_SETUP
DECL|macro|ENABLE_IRQ
mdefine_line|#define&t;ENABLE_IRQ()&t;mac_enable_irq( IRQ_MAC_SCSI ); 
DECL|macro|DISABLE_IRQ
mdefine_line|#define&t;DISABLE_IRQ()&t;mac_disable_irq( IRQ_MAC_SCSI );
r_extern
r_void
id|via_scsi_clear
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef RESET_BOOT
r_static
r_void
id|mac_scsi_reset_boot
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|setup_called
r_static
r_int
id|setup_called
op_assign
l_int|0
suffix:semicolon
DECL|variable|setup_can_queue
r_static
r_int
id|setup_can_queue
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|setup_cmd_per_lun
r_static
r_int
id|setup_cmd_per_lun
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|setup_sg_tablesize
r_static
r_int
id|setup_sg_tablesize
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|setup_use_pdma
r_static
r_int
id|setup_use_pdma
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef SUPPORT_TAGS
DECL|variable|setup_use_tagged_queuing
r_static
r_int
id|setup_use_tagged_queuing
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
DECL|variable|setup_hostid
r_static
r_int
id|setup_hostid
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Time (in jiffies) to wait after a reset; the SCSI standard calls for 250ms,&n; * we usually do 0.5s to be on the safe side. But Toshiba CD-ROMs once more&n; * need ten times the standard value... */
DECL|macro|TOSHIBA_DELAY
mdefine_line|#define TOSHIBA_DELAY
macro_line|#ifdef TOSHIBA_DELAY
DECL|macro|AFTER_RESET_DELAY
mdefine_line|#define&t;AFTER_RESET_DELAY&t;(5*HZ/2)
macro_line|#else
DECL|macro|AFTER_RESET_DELAY
mdefine_line|#define&t;AFTER_RESET_DELAY&t;(HZ/2)
macro_line|#endif
DECL|variable|mac_scsi_regp
r_static
r_volatile
r_int
r_char
op_star
id|mac_scsi_regp
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mac_scsi_drq
r_static
r_volatile
r_int
r_char
op_star
id|mac_scsi_drq
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mac_scsi_nodrq
r_static
r_volatile
r_int
r_char
op_star
id|mac_scsi_nodrq
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * NCR 5380 register access functions&n; */
macro_line|#if 0
multiline_comment|/* Debug versions */
mdefine_line|#define CTRL(p,v) (*ctrl = (v))
r_static
r_char
id|macscsi_read
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
r_int
id|i
suffix:semicolon
r_int
op_star
id|ctrl
op_assign
op_amp
(paren
(paren
r_struct
id|NCR5380_hostdata
op_star
)paren
id|instance-&gt;hostdata
)paren
op_member_access_from_pointer
id|ctrl
suffix:semicolon
id|CTRL
c_func
(paren
id|iobase
comma
l_int|0
)paren
suffix:semicolon
id|i
op_assign
id|in_8
c_func
(paren
id|iobase
op_plus
(paren
id|reg
op_lshift
l_int|4
)paren
)paren
suffix:semicolon
id|CTRL
c_func
(paren
id|iobase
comma
l_int|0x40
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
r_static
r_void
id|macscsi_write
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
r_int
op_star
id|ctrl
op_assign
op_amp
(paren
(paren
r_struct
id|NCR5380_hostdata
op_star
)paren
id|instance-&gt;hostdata
)paren
op_member_access_from_pointer
id|ctrl
suffix:semicolon
id|CTRL
c_func
(paren
id|iobase
comma
l_int|0
)paren
suffix:semicolon
id|out_8
c_func
(paren
id|iobase
op_plus
(paren
id|reg
op_lshift
l_int|4
)paren
comma
id|value
)paren
suffix:semicolon
id|CTRL
c_func
(paren
id|iobase
comma
l_int|0x40
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* Fast versions */
DECL|function|macscsi_read
r_static
id|__inline__
r_char
id|macscsi_read
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
r_return
id|in_8
c_func
(paren
id|instance-&gt;io_port
op_plus
(paren
id|reg
op_lshift
l_int|4
)paren
)paren
suffix:semicolon
)brace
DECL|function|macscsi_write
r_static
id|__inline__
r_void
id|macscsi_write
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
id|out_8
c_func
(paren
id|instance-&gt;io_port
op_plus
(paren
id|reg
op_lshift
l_int|4
)paren
comma
id|value
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Function : mac_scsi_setup(char *str)&n; *&n; * Purpose : booter command line initialization of the overrides array,&n; *&n; * Inputs : str - comma delimited list of options&n; *&n; */
DECL|function|mac_scsi_setup
r_static
r_int
id|__init
id|mac_scsi_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
macro_line|#ifdef DRIVER_SETUP&t;
r_int
id|ints
(braket
l_int|7
)braket
suffix:semicolon
(paren
r_void
)paren
id|get_options
c_func
(paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|ints
)paren
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setup_called
op_increment
op_logical_or
id|ints
(braket
l_int|0
)braket
template_param
l_int|6
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;scsi: &lt;mac5380&gt;&quot;
l_string|&quot; Usage: mac5380=&lt;can_queue&gt;[,&lt;cmd_per_lun&gt;,&lt;sg_tablesize&gt;,&lt;hostid&gt;,&lt;use_tags&gt;,&lt;use_pdma&gt;]&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;scsi: &lt;mac5380&gt; Bad Penguin parameters?&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_ge
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|1
)braket
OG
l_int|0
)paren
multiline_comment|/* no limits on this, just &gt; 0 */
id|setup_can_queue
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_ge
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|2
)braket
OG
l_int|0
)paren
id|setup_cmd_per_lun
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_ge
l_int|3
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|3
)braket
op_ge
l_int|0
)paren
(brace
id|setup_sg_tablesize
op_assign
id|ints
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Must be &lt;= SG_ALL (255) */
r_if
c_cond
(paren
id|setup_sg_tablesize
OG
id|SG_ALL
)paren
id|setup_sg_tablesize
op_assign
id|SG_ALL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_ge
l_int|4
)paren
(brace
multiline_comment|/* Must be between 0 and 7 */
r_if
c_cond
(paren
id|ints
(braket
l_int|4
)braket
op_ge
l_int|0
op_logical_and
id|ints
(braket
l_int|4
)braket
op_le
l_int|7
)paren
id|setup_hostid
op_assign
id|ints
(braket
l_int|4
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ints
(braket
l_int|4
)braket
OG
l_int|7
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mac_scsi_setup: invalid host ID %d !&bslash;n&quot;
comma
id|ints
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef SUPPORT_TAGS&t;
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_ge
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|5
)braket
op_ge
l_int|0
)paren
id|setup_use_tagged_queuing
op_assign
op_logical_neg
op_logical_neg
id|ints
(braket
l_int|5
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_eq
l_int|6
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|6
)braket
op_ge
l_int|0
)paren
id|setup_use_pdma
op_assign
id|ints
(braket
l_int|6
)braket
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_eq
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|5
)braket
op_ge
l_int|0
)paren
id|setup_use_pdma
op_assign
id|ints
(braket
l_int|5
)braket
suffix:semicolon
)brace
macro_line|#endif /* SUPPORT_TAGS */
macro_line|#endif /* DRIVER_SETUP */
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;mac5380=&quot;
comma
id|mac_scsi_setup
)paren
suffix:semicolon
multiline_comment|/*&n; * If you want to find the instance with (k)gdb ...&n; */
macro_line|#if NDEBUG
DECL|variable|default_instance
r_static
r_struct
id|Scsi_Host
op_star
id|default_instance
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Function : int macscsi_detect(Scsi_Host_Template * tpnt)&n; *&n; * Purpose : initializes mac NCR5380 driver based on the&n; *&t;command line / compile time port and irq definitions.&n; *&n; * Inputs : tpnt - template for this SCSI adapter.&n; *&n; * Returns : 1 if a host adapter was found, 0 if not.&n; *&n; */
DECL|function|macscsi_detect
r_int
id|macscsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_static
r_int
id|called
op_assign
l_int|0
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
op_logical_or
id|called
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|macintosh_config-&gt;scsi_type
op_ne
id|MAC_SCSI_OLD
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* setup variables */
id|tpnt-&gt;can_queue
op_assign
(paren
id|setup_can_queue
OG
l_int|0
)paren
ques
c_cond
id|setup_can_queue
suffix:colon
id|CAN_QUEUE
suffix:semicolon
id|tpnt-&gt;cmd_per_lun
op_assign
(paren
id|setup_cmd_per_lun
OG
l_int|0
)paren
ques
c_cond
id|setup_cmd_per_lun
suffix:colon
id|CMD_PER_LUN
suffix:semicolon
id|tpnt-&gt;sg_tablesize
op_assign
(paren
id|setup_sg_tablesize
op_ge
l_int|0
)paren
ques
c_cond
id|setup_sg_tablesize
suffix:colon
id|SG_TABLESIZE
suffix:semicolon
r_if
c_cond
(paren
id|setup_hostid
op_ge
l_int|0
)paren
id|tpnt-&gt;this_id
op_assign
id|setup_hostid
suffix:semicolon
r_else
(brace
multiline_comment|/* use 7 as default */
id|tpnt-&gt;this_id
op_assign
l_int|7
suffix:semicolon
)brace
macro_line|#ifdef SUPPORT_TAGS
r_if
c_cond
(paren
id|setup_use_tagged_queuing
OL
l_int|0
)paren
id|setup_use_tagged_queuing
op_assign
id|USE_TAGGED_QUEUING
suffix:semicolon
macro_line|#endif
multiline_comment|/* Once we support multiple 5380s (e.g. DuoDock) we&squot;ll do&n;       something different here */
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
macro_line|#if NDEBUG
id|default_instance
op_assign
id|instance
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_IIFX
)paren
(brace
id|mac_scsi_regp
op_assign
id|via1
op_plus
l_int|0x8000
suffix:semicolon
id|mac_scsi_drq
op_assign
id|via1
op_plus
l_int|0xE000
suffix:semicolon
id|mac_scsi_nodrq
op_assign
id|via1
op_plus
l_int|0xC000
suffix:semicolon
multiline_comment|/* The IIFX should be able to do true DMA, but pseudo-dma doesn&squot;t work */
id|flags
op_assign
id|FLAG_NO_PSEUDO_DMA
suffix:semicolon
)brace
r_else
(brace
id|mac_scsi_regp
op_assign
id|via1
op_plus
l_int|0x10000
suffix:semicolon
id|mac_scsi_drq
op_assign
id|via1
op_plus
l_int|0x6000
suffix:semicolon
id|mac_scsi_nodrq
op_assign
id|via1
op_plus
l_int|0x12000
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|setup_use_pdma
)paren
id|flags
op_assign
id|FLAG_NO_PSEUDO_DMA
suffix:semicolon
id|instance-&gt;io_port
op_assign
(paren
r_int
r_int
)paren
id|mac_scsi_regp
suffix:semicolon
id|instance-&gt;irq
op_assign
id|IRQ_MAC_SCSI
suffix:semicolon
macro_line|#ifdef RESET_BOOT   
id|mac_scsi_reset_boot
c_func
(paren
id|instance
)paren
suffix:semicolon
macro_line|#endif
id|NCR5380_init
c_func
(paren
id|instance
comma
id|flags
)paren
suffix:semicolon
id|instance-&gt;n_io_port
op_assign
l_int|255
suffix:semicolon
(paren
(paren
r_struct
id|NCR5380_hostdata
op_star
)paren
id|instance-&gt;hostdata
)paren
op_member_access_from_pointer
id|ctrl
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|instance-&gt;irq
op_ne
id|SCSI_IRQ_NONE
)paren
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|instance-&gt;irq
comma
id|NCR5380_intr
comma
id|IRQ_FLG_SLOW
comma
l_string|&quot;ncr5380&quot;
comma
id|instance
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;scsi%d: IRQ%d not free, interrupts disabled&bslash;n&quot;
comma
id|instance-&gt;host_no
comma
id|instance-&gt;irq
)paren
suffix:semicolon
id|instance-&gt;irq
op_assign
id|SCSI_IRQ_NONE
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;scsi%d: generic 5380 at port %lX irq&quot;
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
id|SCSI_IRQ_NONE
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;s disabled&quot;
)paren
suffix:semicolon
r_else
id|printk
(paren
id|KERN_INFO
l_string|&quot; %d&quot;
comma
id|instance-&gt;irq
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; options CAN_QUEUE=%d CMD_PER_LUN=%d release=%d&quot;
comma
id|instance-&gt;can_queue
comma
id|instance-&gt;cmd_per_lun
comma
id|MACSCSI_PUBLIC_RELEASE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
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
id|called
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|macscsi_release
r_int
id|macscsi_release
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
id|SCSI_IRQ_NONE
)paren
id|free_irq
(paren
id|shpnt-&gt;irq
comma
id|NCR5380_intr
)paren
suffix:semicolon
id|NCR5380_exit
c_func
(paren
id|shpnt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef RESET_BOOT
multiline_comment|/*&n; * Our &squot;bus reset on boot&squot; function&n; */
DECL|function|mac_scsi_reset_boot
r_static
r_void
id|mac_scsi_reset_boot
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|NCR5380_local_declare
c_func
(paren
)paren
suffix:semicolon
id|NCR5380_setup
c_func
(paren
id|instance
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do a SCSI reset to clean up the bus during initialization. No messing&n;&t; * with the queues, interrupts, or locks necessary here.&n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Macintosh SCSI: resetting the SCSI bus...&quot;
)paren
suffix:semicolon
multiline_comment|/* switch off SCSI IRQ - catch an interrupt without IRQ bit set else */
id|mac_disable_irq
c_func
(paren
id|IRQ_MAC_SCSI
)paren
suffix:semicolon
multiline_comment|/* get in phase */
id|NCR5380_write
c_func
(paren
id|TARGET_COMMAND_REG
comma
id|PHASE_SR_TO_TCR
c_func
(paren
id|NCR5380_read
c_func
(paren
id|STATUS_REG
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* assert RST */
id|NCR5380_write
c_func
(paren
id|INITIATOR_COMMAND_REG
comma
id|ICR_BASE
op_or
id|ICR_ASSERT_RST
)paren
suffix:semicolon
multiline_comment|/* The min. reset hold time is 25us, so 40us should be enough */
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
multiline_comment|/* reset RST and interrupt */
id|NCR5380_write
c_func
(paren
id|INITIATOR_COMMAND_REG
comma
id|ICR_BASE
)paren
suffix:semicolon
id|NCR5380_read
c_func
(paren
id|RESET_PARITY_INTERRUPT_REG
)paren
suffix:semicolon
r_for
c_loop
(paren
id|end
op_assign
id|jiffies
op_plus
id|AFTER_RESET_DELAY
suffix:semicolon
id|time_before
c_func
(paren
id|jiffies
comma
id|end
)paren
suffix:semicolon
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* switch on SCSI IRQ again */
id|mac_enable_irq
c_func
(paren
id|IRQ_MAC_SCSI
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; done&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|macscsi_info
r_const
r_char
op_star
id|macscsi_info
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
multiline_comment|/* &n;   Pseudo-DMA: (Ove Edlund)&n;   The code attempts to catch bus errors that occur if one for example&n;   &quot;trips over the cable&quot;.&n;   XXX: Since bus errors in the PDMA routines never happen on my &n;   computer, the bus error code is untested. &n;   If the code works as intended, a bus error results in Pseudo-DMA &n;   beeing disabled, meaning that the driver switches to slow handshake. &n;   If bus errors are NOT extremely rare, this has to be changed. &n;*/
DECL|macro|CP_IO_TO_MEM
mdefine_line|#define CP_IO_TO_MEM(s,d,len)&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__&t;&t;&t;&t;&t;&bslash;&n;    (&quot;    cmp.w  #4,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bls    8f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;    move.w %1,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    neg.b  %%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    and.w  #3,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    sub.w  %%d0,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bra    2f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot; 1: move.b (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 2: dbf    %%d0,1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    move.w %2,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    lsr.w  #5,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bra    4f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot; 3: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;31: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;32: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;33: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;34: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;35: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;36: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;37: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 4: dbf    %%d0,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    move.w %2,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    lsr.w  #2,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    and.w  #7,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bra    6f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot; 5: move.l (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 6: dbf    %%d0,5b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    and.w  #3,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bra    8f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot; 7: move.b (%0),(%1)+&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 8: dbf    %2,7b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    moveq.l #0, %2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 9: &bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    .even&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;90: moveq.l #1, %2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    jra 9b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;     &quot;   .align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;   .long  1b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long  3b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 31b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 32b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 33b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 34b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 35b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 36b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 37b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long  5b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long  7b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;     : &quot;=a&quot;(s), &quot;=a&quot;(d), &quot;=d&quot;(len)&t;&t;&t;&bslash;&n;     : &quot;0&quot;(s), &quot;1&quot;(d), &quot;2&quot;(len)&t;&t;&t;&t;&bslash;&n;     : &quot;d0&quot;)
DECL|function|macscsi_pread
r_static
r_int
id|macscsi_pread
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
r_char
op_star
id|dst
comma
r_int
id|len
)paren
(brace
r_int
r_char
op_star
id|d
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|s
suffix:semicolon
id|NCR5380_local_declare
c_func
(paren
)paren
suffix:semicolon
id|NCR5380_setup
c_func
(paren
id|instance
)paren
suffix:semicolon
id|s
op_assign
id|mac_scsi_drq
op_plus
l_int|0x60
suffix:semicolon
id|d
op_assign
id|dst
suffix:semicolon
multiline_comment|/* These conditions are derived from MacOS */
r_while
c_loop
(paren
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|BUS_AND_STATUS_REG
)paren
op_amp
id|BASR_DRQ
)paren
op_logical_and
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|STATUS_REG
)paren
op_amp
id|SR_REQ
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|BUS_AND_STATUS_REG
)paren
op_amp
id|BASR_DRQ
)paren
op_logical_and
(paren
id|NCR5380_read
c_func
(paren
id|BUS_AND_STATUS_REG
)paren
op_amp
id|BASR_PHASE_MATCH
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Error in macscsi_pread&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|CP_IO_TO_MEM
c_func
(paren
id|s
comma
id|d
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Bus error in macscsi_pread&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|CP_MEM_TO_IO
mdefine_line|#define CP_MEM_TO_IO(s,d,len)&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__&t;&t;&t;&t;&t;&bslash;&n;    (&quot;    cmp.w  #4,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bls    8f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;    move.w %0,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    neg.b  %%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    and.w  #3,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    sub.w  %%d0,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bra    2f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot; 1: move.b (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 2: dbf    %%d0,1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    move.w %2,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    lsr.w  #5,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bra    4f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot; 3: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;31: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;32: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;33: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;34: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;35: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;36: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;37: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 4: dbf    %%d0,3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    move.w %2,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    lsr.w  #2,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    and.w  #7,%%d0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bra    6f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot; 5: move.l (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 6: dbf    %%d0,5b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    and.w  #3,%2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    bra    8f&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot; 7: move.b (%0)+,(%1)&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 8: dbf    %2,7b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    moveq.l #0, %2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot; 9: &bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    .even&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;90: moveq.l #1, %2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;    jra 9b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;     &quot;   .align 4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;     &quot;   .long  1b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long  3b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 31b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 32b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 33b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 34b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 35b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 36b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long 37b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long  5b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;   .long  7b,90b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;     &quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;     : &quot;=a&quot;(s), &quot;=a&quot;(d), &quot;=d&quot;(len)&t;&t;&t;&bslash;&n;     : &quot;0&quot;(s), &quot;1&quot;(d), &quot;2&quot;(len)&t;&t;&t;&t;&bslash;&n;     : &quot;d0&quot;)
DECL|function|macscsi_pwrite
r_static
r_int
id|macscsi_pwrite
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
r_char
op_star
id|src
comma
r_int
id|len
)paren
(brace
r_int
r_char
op_star
id|s
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|d
suffix:semicolon
id|NCR5380_local_declare
c_func
(paren
)paren
suffix:semicolon
id|NCR5380_setup
c_func
(paren
id|instance
)paren
suffix:semicolon
id|s
op_assign
id|src
suffix:semicolon
id|d
op_assign
id|mac_scsi_drq
suffix:semicolon
multiline_comment|/* These conditions are derived from MacOS */
r_while
c_loop
(paren
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|BUS_AND_STATUS_REG
)paren
op_amp
id|BASR_DRQ
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|STATUS_REG
)paren
op_amp
id|SR_REQ
)paren
op_logical_or
(paren
id|NCR5380_read
c_func
(paren
id|BUS_AND_STATUS_REG
)paren
op_amp
id|BASR_PHASE_MATCH
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|NCR5380_read
c_func
(paren
id|BUS_AND_STATUS_REG
)paren
op_amp
id|BASR_DRQ
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Error in macscsi_pwrite&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|CP_MEM_TO_IO
c_func
(paren
id|s
comma
id|d
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Bus error in macscsi_pwrite&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* These control the behaviour of the generic 5380 core */
DECL|macro|AUTOSENSE
mdefine_line|#define AUTOSENSE
DECL|macro|PSEUDO_DMA
mdefine_line|#define PSEUDO_DMA
macro_line|#include &quot;NCR5380.c&quot;
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|proc_name
op_assign
l_string|&quot;Mac5380&quot;
comma
dot
id|proc_info
op_assign
id|macscsi_proc_info
comma
dot
id|name
op_assign
l_string|&quot;Macintosh NCR5380 SCSI&quot;
comma
dot
id|detect
op_assign
id|macscsi_detect
comma
dot
id|release
op_assign
id|macscsi_release
comma
dot
id|info
op_assign
id|macscsi_info
comma
dot
id|queuecommand
op_assign
id|macscsi_queue_command
comma
dot
id|eh_abort_handler
op_assign
id|macscsi_abort
comma
dot
id|eh_bus_reset_handler
op_assign
id|macscsi_bus_reset
comma
dot
id|eh_device_reset_handler
op_assign
id|macscsi_device_reset
comma
dot
id|eh_host_reset_handler
op_assign
id|macscsi_host_reset
comma
dot
id|can_queue
op_assign
id|CAN_QUEUE
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
id|CMD_PER_LUN
comma
dot
id|unchecked_isa_dma
op_assign
l_int|0
comma
dot
id|use_clustering
op_assign
id|DISABLE_CLUSTERING
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
