macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;../../scsi/scsi.h&quot;
macro_line|#include &quot;../../scsi/hosts.h&quot;
macro_line|#include &quot;hpusbscsi.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x...) &bslash;&n;&t;printk( KERN_DEBUG x )
DECL|variable|states
r_static
r_char
op_star
id|states
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|macro|TRACE_STATE
mdefine_line|#define TRACE_STATE printk(KERN_DEBUG&quot;hpusbscsi-&gt;state = %s at line %d&bslash;n&quot;, states[hpusbscsi-&gt;state], __LINE__)
DECL|variable|hpusbscsi_scsi_host_template
r_static
id|Scsi_Host_Template
id|hpusbscsi_scsi_host_template
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
l_string|&quot;hpusbscsi&quot;
comma
dot
id|proc_name
op_assign
l_string|&quot;hpusbscsi&quot;
comma
dot
id|queuecommand
op_assign
id|hpusbscsi_scsi_queuecommand
comma
dot
id|eh_abort_handler
op_assign
id|hpusbscsi_scsi_abort
comma
dot
id|eh_host_reset_handler
op_assign
id|hpusbscsi_scsi_host_reset
comma
dot
id|sg_tablesize
op_assign
id|SG_ALL
comma
dot
id|can_queue
op_assign
l_int|1
comma
dot
id|this_id
op_assign
op_minus
l_int|1
comma
dot
id|cmd_per_lun
op_assign
l_int|1
comma
dot
id|use_clustering
op_assign
l_int|1
comma
dot
id|emulated
op_assign
l_int|1
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|hpusbscsi_usb_probe
id|hpusbscsi_usb_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|usb_host_interface
op_star
id|altsetting
op_assign
id|intf-&gt;altsetting
suffix:semicolon
r_struct
id|hpusbscsi
op_star
r_new
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_int
id|i
comma
id|result
suffix:semicolon
r_if
c_cond
(paren
id|altsetting-&gt;desc.bNumEndpoints
op_ne
l_int|3
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;Wrong number of endpoints&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hpusbscsi
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hpusbscsi
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|dataurb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
op_member_access_from_pointer
id|dataurb
)paren
r_goto
id|out_kfree
suffix:semicolon
r_new
op_member_access_from_pointer
id|controlurb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
op_member_access_from_pointer
id|controlurb
)paren
r_goto
id|out_free_dataurb
suffix:semicolon
r_new
op_member_access_from_pointer
id|dev
op_assign
id|dev
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|pending
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|deathrow
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENODEV
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
id|altsetting-&gt;desc.bNumEndpoints
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|altsetting-&gt;endpoint
(braket
id|i
)braket
dot
id|desc
dot
id|bmAttributes
op_amp
id|USB_ENDPOINT_XFERTYPE_MASK
)paren
op_eq
id|USB_ENDPOINT_XFER_BULK
)paren
(brace
r_if
c_cond
(paren
id|altsetting-&gt;endpoint
(braket
id|i
)braket
dot
id|desc
dot
id|bEndpointAddress
op_amp
id|USB_DIR_IN
)paren
(brace
r_new
op_member_access_from_pointer
id|ep_in
op_assign
id|altsetting-&gt;endpoint
(braket
id|i
)braket
dot
id|desc
dot
id|bEndpointAddress
op_amp
id|USB_ENDPOINT_NUMBER_MASK
suffix:semicolon
)brace
r_else
(brace
r_new
op_member_access_from_pointer
id|ep_out
op_assign
id|altsetting-&gt;endpoint
(braket
id|i
)braket
dot
id|desc
dot
id|bEndpointAddress
op_amp
id|USB_ENDPOINT_NUMBER_MASK
suffix:semicolon
)brace
)brace
r_else
(brace
r_new
op_member_access_from_pointer
id|ep_int
op_assign
id|altsetting-&gt;endpoint
(braket
id|i
)braket
dot
id|desc
dot
id|bEndpointAddress
op_amp
id|USB_ENDPOINT_NUMBER_MASK
suffix:semicolon
r_new
op_member_access_from_pointer
id|interrupt_interval
op_assign
id|altsetting-&gt;endpoint
(braket
id|i
)braket
dot
id|desc
dot
id|bInterval
suffix:semicolon
)brace
)brace
multiline_comment|/* USB initialisation magic for the simple case */
id|result
op_assign
id|usb_set_interface
c_func
(paren
id|dev
comma
id|altsetting-&gt;desc.bInterfaceNumber
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|result
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* no error */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unknown error %d from usb_set_interface&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_goto
id|out_free_controlurb
suffix:semicolon
)brace
multiline_comment|/* build and submit an interrupt URB for status byte handling */
id|usb_fill_int_urb
c_func
(paren
r_new
op_member_access_from_pointer
id|controlurb
comma
r_new
op_member_access_from_pointer
id|dev
comma
id|usb_rcvintpipe
c_func
(paren
r_new
op_member_access_from_pointer
id|dev
comma
r_new
op_member_access_from_pointer
id|ep_int
)paren
comma
op_amp
r_new
op_member_access_from_pointer
id|scsi_state_byte
comma
l_int|1
comma
id|control_interrupt_callback
comma
r_new
comma
r_new
op_member_access_from_pointer
id|interrupt_interval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
r_new
op_member_access_from_pointer
id|controlurb
comma
id|GFP_KERNEL
)paren
OL
l_int|0
)paren
r_goto
id|out_free_controlurb
suffix:semicolon
multiline_comment|/* In host-&gt;hostdata we store a pointer to desc */
r_new
op_member_access_from_pointer
id|host
op_assign
id|scsi_register
c_func
(paren
op_amp
id|hpusbscsi_scsi_host_template
comma
r_sizeof
(paren
r_new
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
op_member_access_from_pointer
id|host
)paren
r_goto
id|out_unlink_controlurb
suffix:semicolon
r_new
op_member_access_from_pointer
id|host-&gt;hostdata
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
r_new
suffix:semicolon
id|scsi_add_host
c_func
(paren
r_new
op_member_access_from_pointer
id|host
comma
op_amp
id|intf-&gt;dev
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|sense_command
(braket
l_int|0
)braket
op_assign
id|REQUEST_SENSE
suffix:semicolon
r_new
op_member_access_from_pointer
id|sense_command
(braket
l_int|4
)braket
op_assign
id|HPUSBSCSI_SENSE_LENGTH
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
r_new
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_unlink_controlurb
suffix:colon
id|usb_unlink_urb
c_func
(paren
r_new
op_member_access_from_pointer
id|controlurb
)paren
suffix:semicolon
id|out_free_controlurb
suffix:colon
id|usb_free_urb
c_func
(paren
r_new
op_member_access_from_pointer
id|controlurb
)paren
suffix:semicolon
id|out_free_dataurb
suffix:colon
id|usb_free_urb
c_func
(paren
r_new
op_member_access_from_pointer
id|dataurb
)paren
suffix:semicolon
id|out_kfree
suffix:colon
id|kfree
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_void
DECL|function|hpusbscsi_usb_disconnect
id|hpusbscsi_usb_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|desc
op_assign
id|usb_get_intfdata
c_func
(paren
id|intf
)paren
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
id|scsi_remove_host
c_func
(paren
id|desc-&gt;host
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|desc-&gt;controlurb
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|desc-&gt;host
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|desc-&gt;controlurb
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|desc-&gt;dataurb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|desc
)paren
suffix:semicolon
)brace
DECL|variable|hpusbscsi_usb_ids
r_static
r_struct
id|usb_device_id
id|hpusbscsi_usb_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
(paren
l_int|0x03f0
comma
l_int|0x0701
)paren
)brace
comma
multiline_comment|/* HP 53xx */
(brace
id|USB_DEVICE
(paren
l_int|0x03f0
comma
l_int|0x0801
)paren
)brace
comma
multiline_comment|/* HP 7400 */
(brace
id|USB_DEVICE
(paren
l_int|0x0638
comma
l_int|0x0268
)paren
)brace
comma
multiline_comment|/*iVina 1200U */
(brace
id|USB_DEVICE
(paren
l_int|0x0638
comma
l_int|0x026a
)paren
)brace
comma
multiline_comment|/*Scan Dual II */
(brace
id|USB_DEVICE
(paren
l_int|0x0638
comma
l_int|0x0A13
)paren
)brace
comma
multiline_comment|/*Avision AV600U */
(brace
id|USB_DEVICE
(paren
l_int|0x0638
comma
l_int|0x0A16
)paren
)brace
comma
multiline_comment|/*Avision DS610CU Scancopier */
(brace
id|USB_DEVICE
(paren
l_int|0x0638
comma
l_int|0x0A18
)paren
)brace
comma
multiline_comment|/*Avision AV600U Plus */
(brace
id|USB_DEVICE
(paren
l_int|0x0638
comma
l_int|0x0A23
)paren
)brace
comma
multiline_comment|/*Avision AV220 */
(brace
id|USB_DEVICE
(paren
l_int|0x0638
comma
l_int|0x0A24
)paren
)brace
comma
multiline_comment|/*Avision AV210 */
(brace
id|USB_DEVICE
(paren
l_int|0x0686
comma
l_int|0x4004
)paren
)brace
comma
multiline_comment|/*Minolta Elite II */
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|hpusbscsi_usb_ids
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|hpusbscsi_usb_driver
r_static
r_struct
id|usb_driver
id|hpusbscsi_usb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;hpusbscsi&quot;
comma
dot
id|probe
op_assign
id|hpusbscsi_usb_probe
comma
dot
id|disconnect
op_assign
id|hpusbscsi_usb_disconnect
comma
dot
id|id_table
op_assign
id|hpusbscsi_usb_ids
comma
)brace
suffix:semicolon
multiline_comment|/* module initialisation */
r_static
r_int
id|__init
DECL|function|hpusbscsi_init
id|hpusbscsi_init
(paren
r_void
)paren
(brace
r_return
id|usb_register
c_func
(paren
op_amp
id|hpusbscsi_usb_driver
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|hpusbscsi_exit
id|hpusbscsi_exit
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|hpusbscsi_usb_driver
)paren
suffix:semicolon
)brace
DECL|variable|hpusbscsi_init
id|module_init
(paren
id|hpusbscsi_init
)paren
suffix:semicolon
DECL|variable|hpusbscsi_exit
id|module_exit
(paren
id|hpusbscsi_exit
)paren
suffix:semicolon
DECL|function|hpusbscsi_scsi_queuecommand
r_static
r_int
id|hpusbscsi_scsi_queuecommand
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
id|scsi_callback
id|callback
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
(paren
id|srb-&gt;device-&gt;host-&gt;hostdata
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|usb_complete_t
id|usb_callback
suffix:semicolon
r_int
id|res
suffix:semicolon
multiline_comment|/* we don&squot;t answer for anything but our single device on any faked host controller */
r_if
c_cond
(paren
id|srb-&gt;device-&gt;lun
op_logical_or
id|srb-&gt;device-&gt;id
op_logical_or
id|srb-&gt;device-&gt;channel
)paren
(brace
r_if
c_cond
(paren
id|callback
)paren
(brace
id|srb-&gt;result
op_assign
id|DID_BAD_TARGET
suffix:semicolon
id|callback
c_func
(paren
id|srb
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Now we need to decide which callback to give to the urb we send the command with */
r_if
c_cond
(paren
op_logical_neg
id|srb-&gt;bufflen
)paren
(brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|REQUEST_SENSE
)paren
(brace
id|hpusbscsi-&gt;current_data_pipe
op_assign
id|usb_rcvbulkpipe
c_func
(paren
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;ep_in
)paren
suffix:semicolon
id|usb_callback
op_assign
id|request_sense_callback
suffix:semicolon
)brace
r_else
(brace
id|usb_callback
op_assign
id|simple_command_callback
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|srb-&gt;use_sg
)paren
)paren
(brace
id|usb_callback
op_assign
id|scatter_gather_callback
suffix:semicolon
id|hpusbscsi-&gt;fragment
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|usb_callback
op_assign
id|simple_payload_callback
suffix:semicolon
)brace
multiline_comment|/* Now we find out which direction data is to be transferred in */
id|hpusbscsi-&gt;current_data_pipe
op_assign
id|DIRECTION_IS_IN
c_func
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
)paren
ques
c_cond
id|usb_rcvbulkpipe
c_func
(paren
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;ep_in
)paren
suffix:colon
id|usb_sndbulkpipe
c_func
(paren
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;ep_out
)paren
suffix:semicolon
)brace
id|TRACE_STATE
suffix:semicolon
multiline_comment|/* We zero the sense buffer to avoid confusing user space */
id|memset
c_func
(paren
id|srb-&gt;sense_buffer
comma
l_int|0
comma
id|SCSI_SENSE_BUFFERSIZE
)paren
suffix:semicolon
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_BEGINNING
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
multiline_comment|/* We prepare the urb for writing out the scsi command */
id|usb_fill_bulk_urb
c_func
(paren
id|hpusbscsi-&gt;dataurb
comma
id|hpusbscsi-&gt;dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;ep_out
)paren
comma
id|srb-&gt;cmnd
comma
id|srb-&gt;cmd_len
comma
id|usb_callback
comma
id|hpusbscsi
)paren
suffix:semicolon
id|hpusbscsi-&gt;scallback
op_assign
id|callback
suffix:semicolon
id|hpusbscsi-&gt;srb
op_assign
id|srb
suffix:semicolon
id|res
op_assign
id|usb_submit_urb
c_func
(paren
id|hpusbscsi-&gt;dataurb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|res
)paren
)paren
(brace
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_FREE
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|callback
op_ne
l_int|NULL
)paren
)paren
(brace
id|srb-&gt;result
op_assign
id|DID_ERROR
suffix:semicolon
id|callback
c_func
(paren
id|srb
)paren
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpusbscsi_scsi_host_reset
r_static
r_int
id|hpusbscsi_scsi_host_reset
(paren
id|Scsi_Cmnd
op_star
id|srb
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
(paren
id|srb-&gt;device-&gt;host-&gt;hostdata
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;SCSI reset requested.&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|//usb_reset_device(hpusbscsi-&gt;dev);
singleline_comment|//printk(KERN_DEBUG&quot;SCSI reset completed.&bslash;n&quot;);
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_FREE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpusbscsi_scsi_abort
r_static
r_int
id|hpusbscsi_scsi_abort
(paren
id|Scsi_Cmnd
op_star
id|srb
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
(paren
id|srb-&gt;device-&gt;host-&gt;hostdata
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Requested is canceled.&bslash;n&quot;
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|hpusbscsi-&gt;dataurb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|hpusbscsi-&gt;controlurb
)paren
suffix:semicolon
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_FREE
suffix:semicolon
r_return
id|SCSI_ABORT_PENDING
suffix:semicolon
)brace
multiline_comment|/* usb interrupt handlers - they are all running IN INTERRUPT ! */
DECL|function|handle_usb_error
r_static
r_void
id|handle_usb_error
(paren
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|hpusbscsi-&gt;scallback
op_ne
l_int|NULL
)paren
)paren
(brace
id|hpusbscsi-&gt;srb-&gt;result
op_assign
id|DID_ERROR
suffix:semicolon
id|hpusbscsi
op_member_access_from_pointer
id|scallback
c_func
(paren
id|hpusbscsi-&gt;srb
)paren
suffix:semicolon
)brace
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_FREE
suffix:semicolon
)brace
DECL|function|control_interrupt_callback
r_static
r_void
id|control_interrupt_callback
(paren
r_struct
id|urb
op_star
id|u
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
id|u-&gt;context
suffix:semicolon
id|u8
id|scsi_state
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;Getting status byte %d &bslash;n&quot;
comma
id|hpusbscsi-&gt;scsi_state_byte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|u-&gt;status
OL
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_FREE
)paren
)paren
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|scsi_state
op_assign
id|hpusbscsi-&gt;scsi_state_byte
suffix:semicolon
r_if
c_cond
(paren
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_ERROR
)paren
(brace
id|hpusbscsi-&gt;srb-&gt;result
op_and_assign
id|SCSI_ERR_MASK
suffix:semicolon
id|hpusbscsi-&gt;srb-&gt;result
op_or_assign
id|scsi_state
suffix:semicolon
)brace
r_if
c_cond
(paren
id|scsi_state
op_eq
id|CHECK_CONDITION
op_lshift
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|hpusbscsi-&gt;state
op_eq
id|HP_STATE_WAIT
)paren
(brace
id|issue_request_sense
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* we request sense after an eventual data transfer */
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_ERROR
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|hpusbscsi-&gt;scallback
op_ne
l_int|NULL
op_logical_and
id|hpusbscsi-&gt;state
op_eq
id|HP_STATE_WAIT
op_logical_and
id|scsi_state
op_ne
id|CHECK_CONDITION
op_lshift
l_int|1
)paren
multiline_comment|/* we do a callback to the scsi layer if and only if all data has been transferred */
id|hpusbscsi
op_member_access_from_pointer
id|scallback
c_func
(paren
id|hpusbscsi-&gt;srb
)paren
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
r_switch
c_cond
(paren
id|hpusbscsi-&gt;state
)paren
(brace
r_case
id|HP_STATE_WAIT
suffix:colon
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_FREE
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HP_STATE_WORKING
suffix:colon
r_case
id|HP_STATE_BEGINNING
suffix:colon
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_PREMATURE
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HP_STATE_ERROR
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hpusbscsi: Unexpected status report.&bslash;n&quot;
)paren
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_FREE
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|simple_command_callback
r_static
r_void
id|simple_command_callback
c_func
(paren
r_struct
id|urb
op_star
id|u
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
id|u-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|u-&gt;status
OL
l_int|0
)paren
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|TRACE_STATE
suffix:semicolon
r_if
c_cond
(paren
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_PREMATURE
)paren
(brace
id|TRACE_STATE
suffix:semicolon
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_WAIT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|hpusbscsi-&gt;scallback
op_ne
l_int|NULL
)paren
)paren
id|hpusbscsi
op_member_access_from_pointer
id|scallback
c_func
(paren
id|hpusbscsi-&gt;srb
)paren
suffix:semicolon
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_FREE
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
)brace
)brace
DECL|function|scatter_gather_callback
r_static
r_void
id|scatter_gather_callback
c_func
(paren
r_struct
id|urb
op_star
id|u
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
id|u-&gt;context
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
op_assign
id|hpusbscsi-&gt;srb-&gt;buffer
suffix:semicolon
id|usb_complete_t
id|callback
suffix:semicolon
r_int
id|res
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;Going through scatter/gather&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|u-&gt;status
OL
l_int|0
)paren
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hpusbscsi-&gt;fragment
op_plus
l_int|1
op_ne
id|hpusbscsi-&gt;srb-&gt;use_sg
)paren
id|callback
op_assign
id|scatter_gather_callback
suffix:semicolon
r_else
id|callback
op_assign
id|simple_done
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
r_if
c_cond
(paren
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_PREMATURE
)paren
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_WORKING
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
id|usb_fill_bulk_urb
c_func
(paren
id|u
comma
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;current_data_pipe
comma
id|page_address
c_func
(paren
id|sg
(braket
id|hpusbscsi-&gt;fragment
)braket
dot
id|page
)paren
op_plus
id|sg
(braket
id|hpusbscsi-&gt;fragment
)braket
dot
id|offset
comma
id|sg
(braket
id|hpusbscsi-&gt;fragment
op_increment
)braket
dot
id|length
comma
id|callback
comma
id|hpusbscsi
)paren
suffix:semicolon
id|res
op_assign
id|usb_submit_urb
c_func
(paren
id|u
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|res
)paren
)paren
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
)brace
DECL|function|simple_done
r_static
r_void
id|simple_done
(paren
r_struct
id|urb
op_star
id|u
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
id|u-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|u-&gt;status
OL
l_int|0
)paren
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
l_string|&quot;Data transfer done&bslash;n&quot;
)paren
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
r_if
c_cond
(paren
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_PREMATURE
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|u-&gt;status
OL
l_int|0
)paren
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_ERROR
)paren
(brace
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_WAIT
suffix:semicolon
)brace
r_else
(brace
id|issue_request_sense
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|hpusbscsi-&gt;scallback
op_ne
l_int|NULL
)paren
)paren
id|hpusbscsi
op_member_access_from_pointer
id|scallback
c_func
(paren
id|hpusbscsi-&gt;srb
)paren
suffix:semicolon
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_FREE
suffix:semicolon
)brace
)brace
DECL|function|simple_payload_callback
r_static
r_void
id|simple_payload_callback
(paren
r_struct
id|urb
op_star
id|u
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
id|u-&gt;context
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|u-&gt;status
OL
l_int|0
)paren
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|usb_fill_bulk_urb
c_func
(paren
id|u
comma
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;current_data_pipe
comma
id|hpusbscsi-&gt;srb-&gt;buffer
comma
id|hpusbscsi-&gt;srb-&gt;bufflen
comma
id|simple_done
comma
id|hpusbscsi
)paren
suffix:semicolon
id|res
op_assign
id|usb_submit_urb
c_func
(paren
id|u
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|res
)paren
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|TRACE_STATE
suffix:semicolon
r_if
c_cond
(paren
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_PREMATURE
)paren
(brace
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_WORKING
suffix:semicolon
id|TRACE_STATE
suffix:semicolon
)brace
)brace
DECL|function|request_sense_callback
r_static
r_void
id|request_sense_callback
(paren
r_struct
id|urb
op_star
id|u
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
op_assign
(paren
r_struct
id|hpusbscsi
op_star
)paren
id|u-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|u-&gt;status
OL
l_int|0
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|usb_fill_bulk_urb
c_func
(paren
id|u
comma
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;current_data_pipe
comma
id|hpusbscsi-&gt;srb-&gt;sense_buffer
comma
id|SCSI_SENSE_BUFFERSIZE
comma
id|simple_done
comma
id|hpusbscsi
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OG
id|usb_submit_urb
c_func
(paren
id|u
comma
id|GFP_ATOMIC
)paren
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_PREMATURE
op_logical_and
id|hpusbscsi-&gt;state
op_ne
id|HP_STATE_ERROR
)paren
id|hpusbscsi-&gt;state
op_assign
id|HP_STATE_WORKING
suffix:semicolon
)brace
DECL|function|issue_request_sense
r_static
r_void
id|issue_request_sense
(paren
r_struct
id|hpusbscsi
op_star
id|hpusbscsi
)paren
(brace
id|usb_fill_bulk_urb
c_func
(paren
id|hpusbscsi-&gt;dataurb
comma
id|hpusbscsi-&gt;dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;ep_out
)paren
comma
op_amp
id|hpusbscsi-&gt;sense_command
comma
id|SENSE_COMMAND_SIZE
comma
id|request_sense_callback
comma
id|hpusbscsi
)paren
suffix:semicolon
id|hpusbscsi-&gt;current_data_pipe
op_assign
id|usb_rcvbulkpipe
c_func
(paren
id|hpusbscsi-&gt;dev
comma
id|hpusbscsi-&gt;ep_in
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OG
id|usb_submit_urb
c_func
(paren
id|hpusbscsi-&gt;dataurb
comma
id|GFP_ATOMIC
)paren
)paren
(brace
id|handle_usb_error
c_func
(paren
id|hpusbscsi
)paren
suffix:semicolon
)brace
)brace
eof
