multiline_comment|/* Driver for USB Mass Storage compliant devices&n; * SCSI layer glue code&n; *&n; * $Id: scsiglue.c,v 1.26 2002/04/22 03:39:43 mdharm Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * Developed with the assistance of:&n; *   (c) 2000 David L. Brown, Jr. (usb-storage@davidb.org)&n; *   (c) 2000 Stephen J. Gowdy (SGowdy@lbl.gov)&n; *&n; * Initial work by:&n; *   (c) 1999 Michael Gee (michael@linuxspecific.com)&n; *&n; * This driver is based on the &squot;USB Mass Storage Class&squot; document. This&n; * describes in detail the protocol used to communicate with such&n; * devices.  Clearly, the designers had SCSI and ATAPI commands in&n; * mind when they created this document.  The commands are all very&n; * similar to commands in the SCSI-II and ATAPI specifications.&n; *&n; * It is important to note that in a number of cases this class&n; * exhibits class-specific exemptions from the USB specification.&n; * Notably the usage of NAK, STALL and ACK differs from the norm, in&n; * that they are used to communicate wait, failed and OK on commands.&n; *&n; * Also, for certain devices, the interrupt endpoint is used to convey&n; * status of a command.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_devinfo.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_eh.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;scsiglue.h&quot;
macro_line|#include &quot;usb.h&quot;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;protocol.h&quot;
multiline_comment|/***********************************************************************&n; * Host functions &n; ***********************************************************************/
DECL|function|host_info
r_static
r_const
r_char
op_star
id|host_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_return
l_string|&quot;SCSI emulation for USB Mass Storage devices&quot;
suffix:semicolon
)brace
DECL|function|slave_alloc
r_static
r_int
id|slave_alloc
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
multiline_comment|/*&n;&t; * Set the INQUIRY transfer length to 36.  We don&squot;t use any of&n;&t; * the extra data and many devices choke if asked for more or&n;&t; * less than 36 bytes.&n;&t; */
id|sdev-&gt;inquiry_len
op_assign
l_int|36
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|slave_configure
r_static
r_int
id|slave_configure
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_struct
id|us_data
op_star
id|us
op_assign
(paren
r_struct
id|us_data
op_star
)paren
id|sdev-&gt;host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Scatter-gather buffers (all but the last) must have a length&n;&t; * divisible by the bulk maxpacket size.  Otherwise a data packet&n;&t; * would end up being short, causing a premature end to the data&n;&t; * transfer.  Since high-speed bulk pipes have a maxpacket size&n;&t; * of 512, we&squot;ll use that as the scsi device queue&squot;s DMA alignment&n;&t; * mask.  Guaranteeing proper alignment of the first buffer will&n;&t; * have the desired effect because, except at the beginning and&n;&t; * the end, scatter-gather buffers follow page boundaries. */
id|blk_queue_dma_alignment
c_func
(paren
id|sdev-&gt;request_queue
comma
(paren
l_int|512
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the SCSI level to at least 2.  We&squot;ll leave it at 3 if that&squot;s&n;&t; * what is originally reported.  We need this to avoid confusing&n;&t; * the SCSI layer with devices that report 0 or 1, but need 10-byte&n;&t; * commands (ala ATAPI devices behind certain bridges, or devices&n;&t; * which simply have broken INQUIRY data).&n;&t; *&n;&t; * NOTE: This means /dev/sg programs (ala cdrecord) will get the&n;&t; * actual information.  This seems to be the preference for&n;&t; * programs like that.&n;&t; *&n;&t; * NOTE: This also means that /proc/scsi/scsi and sysfs may report&n;&t; * the actual value or the modified one, depending on where the&n;&t; * data comes from.&n;&t; */
r_if
c_cond
(paren
id|sdev-&gt;scsi_level
OL
id|SCSI_2
)paren
id|sdev-&gt;scsi_level
op_assign
id|SCSI_2
suffix:semicolon
multiline_comment|/* According to the technical support people at Genesys Logic,&n;&t; * devices using their chips have problems transferring more than&n;&t; * 32 KB at a time.  In practice people have found that 64 KB&n;&t; * works okay and that&squot;s what Windows does.  But we&squot;ll be&n;&t; * conservative; people can always use the sysfs interface to&n;&t; * increase max_sectors. */
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|us-&gt;pusb_dev-&gt;descriptor.idVendor
)paren
op_eq
id|USB_VENDOR_ID_GENESYS
op_logical_and
id|sdev-&gt;request_queue-&gt;max_sectors
OG
l_int|64
)paren
id|blk_queue_max_sectors
c_func
(paren
id|sdev-&gt;request_queue
comma
l_int|64
)paren
suffix:semicolon
multiline_comment|/* We can&squot;t put these settings in slave_alloc() because that gets&n;&t; * called before the device type is known.  Consequently these&n;&t; * settings can&squot;t be overridden via the scsi devinfo mechanism. */
r_if
c_cond
(paren
id|sdev-&gt;type
op_eq
id|TYPE_DISK
)paren
(brace
multiline_comment|/* Disk-type devices use MODE SENSE(6) if the protocol&n;&t;&t; * (SubClass) is Transparent SCSI, otherwise they use&n;&t;&t; * MODE SENSE(10). */
r_if
c_cond
(paren
id|us-&gt;subclass
op_ne
id|US_SC_SCSI
)paren
id|sdev-&gt;use_10_for_ms
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Many disks only accept MODE SENSE transfer lengths of&n;&t;&t; * 192 bytes (that&squot;s what Windows uses). */
id|sdev-&gt;use_192_bytes_for_3f
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* A number of devices have problems with MODE SENSE for&n;&t;&t; * page x08, so we will skip it. */
id|sdev-&gt;skip_ms_page_8
op_assign
l_int|1
suffix:semicolon
macro_line|#ifndef CONFIG_USB_STORAGE_RW_DETECT
multiline_comment|/* Some devices may not like MODE SENSE with page=0x3f.&n;&t;&t; * Now that we&squot;re using 192-byte transfers this may no&n;&t;&t; * longer be a problem.  So this will be a configuration&n;&t;&t; * option. */
id|sdev-&gt;skip_ms_page_3f
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/* Some disks return the total number of blocks in response&n;&t;&t; * to READ CAPACITY rather than the highest block number.&n;&t;&t; * If this device makes that mistake, tell the sd driver. */
r_if
c_cond
(paren
id|us-&gt;flags
op_amp
id|US_FL_FIX_CAPACITY
)paren
id|sdev-&gt;fix_capacity
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Non-disk-type devices don&squot;t need to blacklist any pages&n;&t;&t; * or to force 192-byte transfer lengths for MODE SENSE.&n;&t;&t; * But they do need to use MODE SENSE(10). */
id|sdev-&gt;use_10_for_ms
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Some devices choke when they receive a PREVENT-ALLOW MEDIUM&n;&t; * REMOVAL command, so suppress those commands. */
r_if
c_cond
(paren
id|us-&gt;flags
op_amp
id|US_FL_NOT_LOCKABLE
)paren
id|sdev-&gt;lockable
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* this is to satisfy the compiler, tho I don&squot;t think the &n;&t; * return code is ever checked anywhere. */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* queue a command */
multiline_comment|/* This is always called with scsi_lock(srb-&gt;host) held */
DECL|function|queuecommand
r_static
r_int
id|queuecommand
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|srb
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
(brace
r_struct
id|us_data
op_star
id|us
op_assign
(paren
r_struct
id|us_data
op_star
)paren
id|srb-&gt;device-&gt;host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s called&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|srb-&gt;host_scribble
op_assign
(paren
r_int
r_char
op_star
)paren
id|us
suffix:semicolon
multiline_comment|/* check for state-transition errors */
r_if
c_cond
(paren
id|us-&gt;srb
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|USB_STORAGE
l_string|&quot;Error in %s: us-&gt;srb = %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|us-&gt;srb
)paren
suffix:semicolon
r_return
id|SCSI_MLQUEUE_HOST_BUSY
suffix:semicolon
)brace
multiline_comment|/* fail the command if we are disconnecting */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|US_FLIDX_DISCONNECTING
comma
op_amp
id|us-&gt;flags
)paren
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Fail command during disconnect&bslash;n&quot;
)paren
suffix:semicolon
id|srb-&gt;result
op_assign
id|DID_NO_CONNECT
op_lshift
l_int|16
suffix:semicolon
id|done
c_func
(paren
id|srb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* enqueue the command and wake up the control thread */
id|srb-&gt;scsi_done
op_assign
id|done
suffix:semicolon
id|us-&gt;srb
op_assign
id|srb
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|us-&gt;sema
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/***********************************************************************&n; * Error handling functions&n; ***********************************************************************/
multiline_comment|/* Command timeout and abort */
multiline_comment|/* This is always called with scsi_lock(srb-&gt;host) held */
DECL|function|command_abort
r_static
r_int
id|command_abort
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|srb
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|srb-&gt;device-&gt;host
suffix:semicolon
r_struct
id|us_data
op_star
id|us
op_assign
(paren
r_struct
id|us_data
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s called&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* Is this command still active? */
r_if
c_cond
(paren
id|us-&gt;srb
op_ne
id|srb
)paren
(brace
id|US_DEBUGP
(paren
l_string|&quot;-- nothing to abort&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|FAILED
suffix:semicolon
)brace
multiline_comment|/* Set the TIMED_OUT bit.  Also set the ABORTING bit, but only if&n;&t; * a device reset isn&squot;t already in progress (to avoid interfering&n;&t; * with the reset).  To prevent races with auto-reset, we must&n;&t; * stop any ongoing USB transfers while still holding the host&n;&t; * lock. */
id|set_bit
c_func
(paren
id|US_FLIDX_TIMED_OUT
comma
op_amp
id|us-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|US_FLIDX_RESETTING
comma
op_amp
id|us-&gt;flags
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|US_FLIDX_ABORTING
comma
op_amp
id|us-&gt;flags
)paren
suffix:semicolon
id|usb_stor_stop_transport
c_func
(paren
id|us
)paren
suffix:semicolon
)brace
id|scsi_unlock
c_func
(paren
id|host
)paren
suffix:semicolon
multiline_comment|/* Wait for the aborted command to finish */
id|wait_for_completion
c_func
(paren
op_amp
id|us-&gt;notify
)paren
suffix:semicolon
multiline_comment|/* Reacquire the lock and allow USB transfers to resume */
id|scsi_lock
c_func
(paren
id|host
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|US_FLIDX_ABORTING
comma
op_amp
id|us-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|US_FLIDX_TIMED_OUT
comma
op_amp
id|us-&gt;flags
)paren
suffix:semicolon
r_return
id|SUCCESS
suffix:semicolon
)brace
multiline_comment|/* This invokes the transport reset mechanism to reset the state of the&n; * device */
multiline_comment|/* This is always called with scsi_lock(srb-&gt;host) held */
DECL|function|device_reset
r_static
r_int
id|device_reset
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|srb
)paren
(brace
r_struct
id|us_data
op_star
id|us
op_assign
(paren
r_struct
id|us_data
op_star
)paren
id|srb-&gt;device-&gt;host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|result
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s called&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|scsi_unlock
c_func
(paren
id|srb-&gt;device-&gt;host
)paren
suffix:semicolon
multiline_comment|/* lock the device pointers and do the reset */
id|down
c_func
(paren
op_amp
(paren
id|us-&gt;dev_semaphore
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|US_FLIDX_DISCONNECTING
comma
op_amp
id|us-&gt;flags
)paren
)paren
(brace
id|result
op_assign
id|FAILED
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;No reset during disconnect&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|result
op_assign
id|us
op_member_access_from_pointer
id|transport_reset
c_func
(paren
id|us
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|us-&gt;dev_semaphore
)paren
)paren
suffix:semicolon
multiline_comment|/* lock the host for the return */
id|scsi_lock
c_func
(paren
id|srb-&gt;device-&gt;host
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* This resets the device&squot;s USB port. */
multiline_comment|/* It refuses to work if there&squot;s more than one interface in&n; * the device, so that other users are not affected. */
multiline_comment|/* This is always called with scsi_lock(srb-&gt;host) held */
DECL|function|bus_reset
r_static
r_int
id|bus_reset
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|srb
)paren
(brace
r_struct
id|us_data
op_star
id|us
op_assign
(paren
r_struct
id|us_data
op_star
)paren
id|srb-&gt;device-&gt;host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|result
comma
id|rc
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s called&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|scsi_unlock
c_func
(paren
id|srb-&gt;device-&gt;host
)paren
suffix:semicolon
multiline_comment|/* The USB subsystem doesn&squot;t handle synchronisation between&n;&t; * a device&squot;s several drivers. Therefore we reset only devices&n;&t; * with just one interface, which we of course own. */
id|down
c_func
(paren
op_amp
(paren
id|us-&gt;dev_semaphore
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|US_FLIDX_DISCONNECTING
comma
op_amp
id|us-&gt;flags
)paren
)paren
(brace
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;No reset during disconnect&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|us-&gt;pusb_dev-&gt;actconfig-&gt;desc.bNumInterfaces
op_ne
l_int|1
)paren
(brace
id|result
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Refusing to reset a multi-interface device&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
id|usb_lock_device_for_reset
c_func
(paren
id|us-&gt;pusb_dev
comma
id|us-&gt;pusb_intf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;unable to lock device for reset: %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|result
op_assign
id|rc
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|usb_reset_device
c_func
(paren
id|us-&gt;pusb_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|usb_unlock_device
c_func
(paren
id|us-&gt;pusb_dev
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;usb_reset_device returns %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
(paren
id|us-&gt;dev_semaphore
)paren
)paren
suffix:semicolon
multiline_comment|/* lock the host for the return */
id|scsi_lock
c_func
(paren
id|srb-&gt;device-&gt;host
)paren
suffix:semicolon
r_return
id|result
OL
l_int|0
ques
c_cond
id|FAILED
suffix:colon
id|SUCCESS
suffix:semicolon
)brace
multiline_comment|/* Report a driver-initiated device reset to the SCSI layer.&n; * Calling this for a SCSI-initiated reset is unnecessary but harmless.&n; * The caller must own the SCSI host lock. */
DECL|function|usb_stor_report_device_reset
r_void
id|usb_stor_report_device_reset
c_func
(paren
r_struct
id|us_data
op_star
id|us
)paren
(brace
r_int
id|i
suffix:semicolon
id|scsi_report_device_reset
c_func
(paren
id|us-&gt;host
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|us-&gt;flags
op_amp
id|US_FL_SCM_MULT_TARG
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|us-&gt;host-&gt;max_id
suffix:semicolon
op_increment
id|i
)paren
id|scsi_report_device_reset
c_func
(paren
id|us-&gt;host
comma
l_int|0
comma
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/***********************************************************************&n; * /proc/scsi/ functions&n; ***********************************************************************/
multiline_comment|/* we use this macro to help us write into the buffer */
DECL|macro|SPRINTF
macro_line|#undef SPRINTF
DECL|macro|SPRINTF
mdefine_line|#define SPRINTF(args...) &bslash;&n;&t;do { if (pos &lt; buffer+length) pos += sprintf(pos, ## args); } while (0)
DECL|macro|DO_FLAG
mdefine_line|#define DO_FLAG(a) &bslash;&n;&t;do { if (us-&gt;flags &amp; US_FL_##a) pos += sprintf(pos, &quot; &quot; #a); } while(0)
DECL|function|proc_info
r_static
r_int
id|proc_info
(paren
r_struct
id|Scsi_Host
op_star
id|hostptr
comma
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
id|inout
)paren
(brace
r_struct
id|us_data
op_star
id|us
suffix:semicolon
r_char
op_star
id|pos
op_assign
id|buffer
suffix:semicolon
r_const
r_char
op_star
id|string
suffix:semicolon
multiline_comment|/* if someone is sending us data, just throw it away */
r_if
c_cond
(paren
id|inout
)paren
r_return
id|length
suffix:semicolon
id|us
op_assign
(paren
r_struct
id|us_data
op_star
)paren
id|hostptr-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* print the controller name */
id|SPRINTF
c_func
(paren
l_string|&quot;   Host scsi%d: usb-storage&bslash;n&quot;
comma
id|hostptr-&gt;host_no
)paren
suffix:semicolon
multiline_comment|/* print product, vendor, and serial number strings */
r_if
c_cond
(paren
id|us-&gt;pusb_dev-&gt;manufacturer
)paren
id|string
op_assign
id|us-&gt;pusb_dev-&gt;manufacturer
suffix:semicolon
r_else
r_if
c_cond
(paren
id|us-&gt;unusual_dev-&gt;vendorName
)paren
id|string
op_assign
id|us-&gt;unusual_dev-&gt;vendorName
suffix:semicolon
r_else
id|string
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
id|SPRINTF
c_func
(paren
l_string|&quot;       Vendor: %s&bslash;n&quot;
comma
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|us-&gt;pusb_dev-&gt;product
)paren
id|string
op_assign
id|us-&gt;pusb_dev-&gt;product
suffix:semicolon
r_else
r_if
c_cond
(paren
id|us-&gt;unusual_dev-&gt;productName
)paren
id|string
op_assign
id|us-&gt;unusual_dev-&gt;productName
suffix:semicolon
r_else
id|string
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
id|SPRINTF
c_func
(paren
l_string|&quot;      Product: %s&bslash;n&quot;
comma
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|us-&gt;pusb_dev-&gt;serial
)paren
id|string
op_assign
id|us-&gt;pusb_dev-&gt;serial
suffix:semicolon
r_else
id|string
op_assign
l_string|&quot;None&quot;
suffix:semicolon
id|SPRINTF
c_func
(paren
l_string|&quot;Serial Number: %s&bslash;n&quot;
comma
id|string
)paren
suffix:semicolon
multiline_comment|/* show the protocol and transport */
id|SPRINTF
c_func
(paren
l_string|&quot;     Protocol: %s&bslash;n&quot;
comma
id|us-&gt;protocol_name
)paren
suffix:semicolon
id|SPRINTF
c_func
(paren
l_string|&quot;    Transport: %s&bslash;n&quot;
comma
id|us-&gt;transport_name
)paren
suffix:semicolon
multiline_comment|/* show the device flags */
r_if
c_cond
(paren
id|pos
OL
id|buffer
op_plus
id|length
)paren
(brace
id|pos
op_add_assign
id|sprintf
c_func
(paren
id|pos
comma
l_string|&quot;       Quirks:&quot;
)paren
suffix:semicolon
id|DO_FLAG
c_func
(paren
id|SINGLE_LUN
)paren
suffix:semicolon
id|DO_FLAG
c_func
(paren
id|SCM_MULT_TARG
)paren
suffix:semicolon
id|DO_FLAG
c_func
(paren
id|FIX_INQUIRY
)paren
suffix:semicolon
id|DO_FLAG
c_func
(paren
id|FIX_CAPACITY
)paren
suffix:semicolon
op_star
(paren
id|pos
op_increment
)paren
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Calculate start of next buffer, and return value.&n;&t; */
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
(paren
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|pos
op_minus
id|buffer
op_minus
id|offset
)paren
OL
id|length
)paren
r_return
(paren
id|pos
op_minus
id|buffer
op_minus
id|offset
)paren
suffix:semicolon
r_else
r_return
(paren
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/***********************************************************************&n; * Sysfs interface&n; ***********************************************************************/
multiline_comment|/* Output routine for the sysfs max_sectors file */
DECL|function|show_max_sectors
r_static
id|ssize_t
id|show_max_sectors
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%u&bslash;n&quot;
comma
id|sdev-&gt;request_queue-&gt;max_sectors
)paren
suffix:semicolon
)brace
multiline_comment|/* Input routine for the sysfs max_sectors file */
DECL|function|store_max_sectors
r_static
id|ssize_t
id|store_max_sectors
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|ms
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%hu&quot;
comma
op_amp
id|ms
)paren
OG
l_int|0
op_logical_and
id|ms
op_le
id|SCSI_DEFAULT_MAX_SECTORS
)paren
(brace
id|blk_queue_max_sectors
c_func
(paren
id|sdev-&gt;request_queue
comma
id|ms
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|max_sectors
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_max_sectors
comma
id|store_max_sectors
)paren
suffix:semicolon
DECL|variable|sysfs_device_attr_list
r_static
r_struct
id|device_attribute
op_star
id|sysfs_device_attr_list
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_max_sectors
comma
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * this defines our host template, with which we&squot;ll allocate hosts&n; */
DECL|variable|usb_stor_host_template
r_struct
id|scsi_host_template
id|usb_stor_host_template
op_assign
(brace
multiline_comment|/* basic userland interface stuff */
dot
id|name
op_assign
l_string|&quot;usb-storage&quot;
comma
dot
id|proc_name
op_assign
l_string|&quot;usb-storage&quot;
comma
dot
id|proc_info
op_assign
id|proc_info
comma
dot
id|info
op_assign
id|host_info
comma
multiline_comment|/* command interface -- queued only */
dot
id|queuecommand
op_assign
id|queuecommand
comma
multiline_comment|/* error and abort handlers */
dot
id|eh_abort_handler
op_assign
id|command_abort
comma
dot
id|eh_device_reset_handler
op_assign
id|device_reset
comma
dot
id|eh_bus_reset_handler
op_assign
id|bus_reset
comma
multiline_comment|/* queue commands only, only one command per LUN */
dot
id|can_queue
op_assign
l_int|1
comma
dot
id|cmd_per_lun
op_assign
l_int|1
comma
multiline_comment|/* unknown initiator id */
dot
id|this_id
op_assign
op_minus
l_int|1
comma
dot
id|slave_alloc
op_assign
id|slave_alloc
comma
dot
id|slave_configure
op_assign
id|slave_configure
comma
multiline_comment|/* lots of sg segments can be handled */
dot
id|sg_tablesize
op_assign
id|SG_ALL
comma
multiline_comment|/* limit the total size of a transfer to 120 KB */
dot
id|max_sectors
op_assign
l_int|240
comma
multiline_comment|/* merge commands... this seems to help performance, but&n;&t; * periodically someone should test to see which setting is more&n;&t; * optimal.&n;&t; */
dot
id|use_clustering
op_assign
l_int|1
comma
multiline_comment|/* emulated HBA */
dot
id|emulated
op_assign
l_int|1
comma
multiline_comment|/* we do our own delay after a device or bus reset */
dot
id|skip_settle_delay
op_assign
l_int|1
comma
multiline_comment|/* sysfs device attributes */
dot
id|sdev_attrs
op_assign
id|sysfs_device_attr_list
comma
multiline_comment|/* module management */
dot
id|module
op_assign
id|THIS_MODULE
)brace
suffix:semicolon
multiline_comment|/* For a device that is &quot;Not Ready&quot; */
DECL|variable|usb_stor_sense_notready
r_int
r_char
id|usb_stor_sense_notready
(braket
l_int|18
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
l_int|0x70
comma
multiline_comment|/* current error */
(braket
l_int|2
)braket
op_assign
l_int|0x02
comma
multiline_comment|/* not ready */
(braket
l_int|7
)braket
op_assign
l_int|0x0a
comma
multiline_comment|/* additional length */
(braket
l_int|12
)braket
op_assign
l_int|0x04
comma
multiline_comment|/* not ready */
(braket
l_int|13
)braket
op_assign
l_int|0x03
multiline_comment|/* manual intervention */
)brace
suffix:semicolon
multiline_comment|/* To Report &quot;Illegal Request: Invalid Field in CDB */
DECL|variable|usb_stor_sense_invalidCDB
r_int
r_char
id|usb_stor_sense_invalidCDB
(braket
l_int|18
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
l_int|0x70
comma
multiline_comment|/* current error */
(braket
l_int|2
)braket
op_assign
id|ILLEGAL_REQUEST
comma
multiline_comment|/* Illegal Request = 0x05 */
(braket
l_int|7
)braket
op_assign
l_int|0x0a
comma
multiline_comment|/* additional length */
(braket
l_int|12
)braket
op_assign
l_int|0x24
multiline_comment|/* Invalid Field in CDB */
)brace
suffix:semicolon
eof
