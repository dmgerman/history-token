multiline_comment|/*&n; * Changes:&n; * Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; 08/23/2000&n; * - get rid of some verify_areas and use __copy*user and __get/put_user&n; *   for the ones that remain&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_eh.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
macro_line|#include &lt;scsi/scsi_request.h&gt;
macro_line|#include &quot;scsi_logging.h&quot;
DECL|macro|NORMAL_RETRIES
mdefine_line|#define NORMAL_RETRIES&t;&t;&t;5
DECL|macro|IOCTL_NORMAL_TIMEOUT
mdefine_line|#define IOCTL_NORMAL_TIMEOUT&t;&t;&t;(10 * HZ)
DECL|macro|FORMAT_UNIT_TIMEOUT
mdefine_line|#define FORMAT_UNIT_TIMEOUT&t;&t;(2 * 60 * 60 * HZ)
DECL|macro|START_STOP_TIMEOUT
mdefine_line|#define START_STOP_TIMEOUT&t;&t;(60 * HZ)
DECL|macro|MOVE_MEDIUM_TIMEOUT
mdefine_line|#define MOVE_MEDIUM_TIMEOUT&t;&t;(5 * 60 * HZ)
DECL|macro|READ_ELEMENT_STATUS_TIMEOUT
mdefine_line|#define READ_ELEMENT_STATUS_TIMEOUT&t;(5 * 60 * HZ)
DECL|macro|READ_DEFECT_DATA_TIMEOUT
mdefine_line|#define READ_DEFECT_DATA_TIMEOUT&t;(60 * HZ )  /* ZIP-250 on parallel port takes as long! */
DECL|macro|MAX_BUF
mdefine_line|#define MAX_BUF PAGE_SIZE
multiline_comment|/*&n; * If we are told to probe a host, we will return 0 if  the host is not&n; * present, 1 if the host is present, and will return an identifying&n; * string at *arg, if arg is non null, filling to the length stored at&n; * (int *) arg&n; */
DECL|function|ioctl_probe
r_static
r_int
id|ioctl_probe
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
r_void
id|__user
op_star
id|buffer
)paren
(brace
r_int
r_int
id|len
comma
id|slen
suffix:semicolon
r_const
r_char
op_star
id|string
suffix:semicolon
r_int
id|temp
op_assign
id|host-&gt;hostt-&gt;present
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_logical_and
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buffer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;hostt-&gt;info
)paren
id|string
op_assign
id|host-&gt;hostt
op_member_access_from_pointer
id|info
c_func
(paren
id|host
)paren
suffix:semicolon
r_else
id|string
op_assign
id|host-&gt;hostt-&gt;name
suffix:semicolon
r_if
c_cond
(paren
id|string
)paren
(brace
id|slen
op_assign
id|strlen
c_func
(paren
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|slen
)paren
id|len
op_assign
id|slen
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|string
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_return
id|temp
suffix:semicolon
)brace
multiline_comment|/*&n;&n; * The SCSI_IOCTL_SEND_COMMAND ioctl sends a command out to the SCSI host.&n; * The IOCTL_NORMAL_TIMEOUT and NORMAL_RETRIES  variables are used.  &n; * &n; * dev is the SCSI device struct ptr, *(int *) arg is the length of the&n; * input data, if any, not including the command string &amp; counts, &n; * *((int *)arg + 1) is the output buffer size in bytes.&n; * &n; * *(char *) ((int *) arg)[2] the actual command byte.   &n; * &n; * Note that if more than MAX_BUF bytes are requested to be transferred,&n; * the ioctl will fail with error EINVAL.&n; * &n; * This size *does not* include the initial lengths that were passed.&n; * &n; * The SCSI command is read from the memory location immediately after the&n; * length words, and the input data is right after the command.  The SCSI&n; * routines know the command size based on the opcode decode.  &n; * &n; * The output area is then filled in starting from the command byte. &n; */
DECL|function|ioctl_internal_command
r_static
r_int
id|ioctl_internal_command
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_char
op_star
id|cmd
comma
r_int
id|timeout
comma
r_int
id|retries
)paren
(brace
r_struct
id|scsi_request
op_star
id|sreq
suffix:semicolon
r_int
id|result
suffix:semicolon
id|SCSI_LOG_IOCTL
c_func
(paren
l_int|1
comma
id|printk
c_func
(paren
l_string|&quot;Trying ioctl with scsi command %d&bslash;n&quot;
comma
op_star
id|cmd
)paren
)paren
suffix:semicolon
id|sreq
op_assign
id|scsi_allocate_request
c_func
(paren
id|sdev
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sreq
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SCSI internal ioctl failed, no memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|sreq-&gt;sr_data_direction
op_assign
id|DMA_NONE
suffix:semicolon
id|scsi_wait_req
c_func
(paren
id|sreq
comma
id|cmd
comma
l_int|NULL
comma
l_int|0
comma
id|timeout
comma
id|retries
)paren
suffix:semicolon
id|SCSI_LOG_IOCTL
c_func
(paren
l_int|2
comma
id|printk
c_func
(paren
l_string|&quot;Ioctl returned  0x%x&bslash;n&quot;
comma
id|sreq-&gt;sr_result
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|driver_byte
c_func
(paren
id|sreq-&gt;sr_result
)paren
)paren
(brace
r_switch
c_cond
(paren
id|sreq-&gt;sr_sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xf
)paren
(brace
r_case
id|ILLEGAL_REQUEST
suffix:colon
r_if
c_cond
(paren
id|cmd
(braket
l_int|0
)braket
op_eq
id|ALLOW_MEDIUM_REMOVAL
)paren
id|sdev-&gt;lockable
op_assign
l_int|0
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;SCSI device (ioctl) reports ILLEGAL REQUEST.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NOT_READY
suffix:colon
multiline_comment|/* This happens if there is no disc in drive */
r_if
c_cond
(paren
id|sdev-&gt;removable
op_logical_and
(paren
id|cmd
(braket
l_int|0
)braket
op_ne
id|TEST_UNIT_READY
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Device not ready.  Make sure there is a disc in the drive.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|UNIT_ATTENTION
suffix:colon
r_if
c_cond
(paren
id|sdev-&gt;removable
)paren
(brace
id|sdev-&gt;changed
op_assign
l_int|1
suffix:semicolon
id|sreq-&gt;sr_result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This is no longer considered an error */
r_break
suffix:semicolon
)brace
r_default
suffix:colon
multiline_comment|/* Fall through for non-removable media */
id|printk
c_func
(paren
l_string|&quot;SCSI error: host %d id %d lun %d return code = %x&bslash;n&quot;
comma
id|sdev-&gt;host-&gt;host_no
comma
id|sdev-&gt;id
comma
id|sdev-&gt;lun
comma
id|sreq-&gt;sr_result
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tSense class %x, sense error %x, extended sense %x&bslash;n&quot;
comma
id|sense_class
c_func
(paren
id|sreq-&gt;sr_sense_buffer
(braket
l_int|0
)braket
)paren
comma
id|sense_error
c_func
(paren
id|sreq-&gt;sr_sense_buffer
(braket
l_int|0
)braket
)paren
comma
id|sreq-&gt;sr_sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
)brace
id|result
op_assign
id|sreq-&gt;sr_result
suffix:semicolon
id|SCSI_LOG_IOCTL
c_func
(paren
l_int|2
comma
id|printk
c_func
(paren
l_string|&quot;IOCTL Releasing command&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|scsi_release_request
c_func
(paren
id|sreq
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|scsi_set_medium_removal
r_int
id|scsi_set_medium_removal
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_char
id|state
)paren
(brace
r_char
id|scsi_cmd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sdev-&gt;removable
op_logical_or
op_logical_neg
id|sdev-&gt;lockable
)paren
r_return
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|0
)braket
op_assign
id|ALLOW_MEDIUM_REMOVAL
suffix:semicolon
id|scsi_cmd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|4
)braket
op_assign
id|state
suffix:semicolon
id|scsi_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|ioctl_internal_command
c_func
(paren
id|sdev
comma
id|scsi_cmd
comma
id|IOCTL_NORMAL_TIMEOUT
comma
id|NORMAL_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|sdev-&gt;locked
op_assign
(paren
id|state
op_eq
id|SCSI_REMOVAL_PREVENT
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * This interface is deprecated - users should use the scsi generic (sg)&n; * interface instead, as this is a more flexible approach to performing&n; * generic SCSI commands on a device.&n; *&n; * The structure that we are passed should look like:&n; *&n; * struct sdata {&n; *  unsigned int inlen;      [i] Length of data to be written to device &n; *  unsigned int outlen;     [i] Length of data to be read from device &n; *  unsigned char cmd[x];    [i] SCSI command (6 &lt;= x &lt;= 12).&n; *                           [o] Data read from device starts here.&n; *                           [o] On error, sense buffer starts here.&n; *  unsigned char wdata[y];  [i] Data written to device starts here.&n; * };&n; * Notes:&n; *   -  The SCSI command length is determined by examining the 1st byte&n; *      of the given command. There is no way to override this.&n; *   -  Data transfers are limited to PAGE_SIZE (4K on i386, 8K on alpha).&n; *   -  The length (x + y) must be at least OMAX_SB_LEN bytes long to&n; *      accommodate the sense buffer when an error occurs.&n; *      The sense buffer is truncated to OMAX_SB_LEN (16) bytes so that&n; *      old code will not be surprised.&n; *   -  If a Unix error occurs (e.g. ENOMEM) then the user will receive&n; *      a negative return and the Unix error code in &squot;errno&squot;. &n; *      If the SCSI command succeeds then 0 is returned.&n; *      Positive numbers returned are the compacted SCSI error codes (4 &n; *      bytes in one int) where the lowest byte is the SCSI status.&n; *      See the drivers/scsi/scsi.h file for more information on this.&n; *&n; */
DECL|macro|OMAX_SB_LEN
mdefine_line|#define OMAX_SB_LEN 16&t;&t;/* Old sense buffer length */
DECL|function|scsi_ioctl_send_command
r_int
id|scsi_ioctl_send_command
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_struct
id|scsi_ioctl_command
id|__user
op_star
id|sic
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
r_int
r_char
id|cmd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
r_char
id|__user
op_star
id|cmd_in
suffix:semicolon
r_struct
id|scsi_request
op_star
id|sreq
suffix:semicolon
r_int
r_char
id|opcode
suffix:semicolon
r_int
r_int
id|inlen
comma
id|outlen
comma
id|cmdlen
suffix:semicolon
r_int
r_int
id|needed
comma
id|buf_needed
suffix:semicolon
r_int
id|timeout
comma
id|retries
comma
id|result
suffix:semicolon
r_int
id|data_direction
comma
id|gfp_mask
op_assign
id|GFP_KERNEL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sic
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;host-&gt;unchecked_isa_dma
)paren
id|gfp_mask
op_or_assign
id|GFP_DMA
suffix:semicolon
multiline_comment|/*&n;&t; * Verify that we can read at least this much.&n;&t; */
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|sic
comma
r_sizeof
(paren
id|Scsi_Ioctl_Command
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|inlen
comma
op_amp
id|sic-&gt;inlen
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|outlen
comma
op_amp
id|sic-&gt;outlen
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We do not transfer more than MAX_BUF with this interface.&n;&t; * If the user needs to transfer more data than this, they&n;&t; * should use scsi_generics (sg) instead.&n;&t; */
r_if
c_cond
(paren
id|inlen
OG
id|MAX_BUF
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|outlen
OG
id|MAX_BUF
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cmd_in
op_assign
id|sic-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|opcode
comma
id|cmd_in
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|needed
op_assign
id|buf_needed
op_assign
(paren
id|inlen
OG
id|outlen
ques
c_cond
id|inlen
suffix:colon
id|outlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf_needed
)paren
(brace
id|buf_needed
op_assign
(paren
id|buf_needed
op_plus
l_int|511
)paren
op_amp
op_complement
l_int|511
suffix:semicolon
r_if
c_cond
(paren
id|buf_needed
OG
id|MAX_BUF
)paren
id|buf_needed
op_assign
id|MAX_BUF
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|buf_needed
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|buf_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inlen
op_eq
l_int|0
)paren
(brace
id|data_direction
op_assign
id|DMA_FROM_DEVICE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|outlen
op_eq
l_int|0
)paren
(brace
id|data_direction
op_assign
id|DMA_TO_DEVICE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Can this ever happen?&n;&t;&t;&t; */
id|data_direction
op_assign
id|DMA_BIDIRECTIONAL
suffix:semicolon
)brace
)brace
r_else
(brace
id|buf
op_assign
l_int|NULL
suffix:semicolon
id|data_direction
op_assign
id|DMA_NONE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Obtain the command from the user&squot;s address space.&n;&t; */
id|cmdlen
op_assign
id|COMMAND_SIZE
c_func
(paren
id|opcode
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|cmd_in
comma
id|cmdlen
op_plus
id|inlen
)paren
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|cmd
comma
id|cmd_in
comma
id|cmdlen
)paren
)paren
(brace
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Obtain the data to be sent to the device (if any).&n;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|cmd_in
op_plus
id|cmdlen
comma
id|inlen
)paren
)paren
(brace
r_goto
id|error
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|SEND_DIAGNOSTIC
suffix:colon
r_case
id|FORMAT_UNIT
suffix:colon
id|timeout
op_assign
id|FORMAT_UNIT_TIMEOUT
suffix:semicolon
id|retries
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|START_STOP
suffix:colon
id|timeout
op_assign
id|START_STOP_TIMEOUT
suffix:semicolon
id|retries
op_assign
id|NORMAL_RETRIES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MOVE_MEDIUM
suffix:colon
id|timeout
op_assign
id|MOVE_MEDIUM_TIMEOUT
suffix:semicolon
id|retries
op_assign
id|NORMAL_RETRIES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_ELEMENT_STATUS
suffix:colon
id|timeout
op_assign
id|READ_ELEMENT_STATUS_TIMEOUT
suffix:semicolon
id|retries
op_assign
id|NORMAL_RETRIES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_DEFECT_DATA
suffix:colon
id|timeout
op_assign
id|READ_DEFECT_DATA_TIMEOUT
suffix:semicolon
id|retries
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|timeout
op_assign
id|IOCTL_NORMAL_TIMEOUT
suffix:semicolon
id|retries
op_assign
id|NORMAL_RETRIES
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sreq
op_assign
id|scsi_allocate_request
c_func
(paren
id|sdev
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sreq
)paren
(brace
id|result
op_assign
op_minus
id|EINTR
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|sreq-&gt;sr_data_direction
op_assign
id|data_direction
suffix:semicolon
id|scsi_wait_req
c_func
(paren
id|sreq
comma
id|cmd
comma
id|buf
comma
id|needed
comma
id|timeout
comma
id|retries
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * If there was an error condition, pass the info back to the user. &n;&t; */
id|result
op_assign
id|sreq-&gt;sr_result
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
r_int
id|sb_len
op_assign
r_sizeof
(paren
id|sreq-&gt;sr_sense_buffer
)paren
suffix:semicolon
id|sb_len
op_assign
(paren
id|sb_len
OG
id|OMAX_SB_LEN
)paren
ques
c_cond
id|OMAX_SB_LEN
suffix:colon
id|sb_len
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|cmd_in
comma
id|sreq-&gt;sr_sense_buffer
comma
id|sb_len
)paren
)paren
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|cmd_in
comma
id|buf
comma
id|outlen
)paren
)paren
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
id|scsi_release_request
c_func
(paren
id|sreq
)paren
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * The scsi_ioctl_get_pci() function places into arg the value&n; * pci_dev::slot_name (8 characters) for the PCI device (if any).&n; * Returns: 0 on success&n; *          -ENXIO if there isn&squot;t a PCI device pointer&n; *                 (could be because the SCSI driver hasn&squot;t been&n; *                  updated yet, or because it isn&squot;t a SCSI&n; *                  device)&n; *          any copy_to_user() error on failure there&n; */
DECL|function|scsi_ioctl_get_pci
r_static
r_int
id|scsi_ioctl_get_pci
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|scsi_get_device
c_func
(paren
id|sdev-&gt;host
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|arg
comma
id|dev-&gt;bus_id
comma
r_sizeof
(paren
id|dev-&gt;bus_id
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * the scsi_ioctl() function differs from most ioctls in that it does&n; * not take a major/minor number as the dev field.  Rather, it takes&n; * a pointer to a scsi_devices[] element, a structure. &n; */
DECL|function|scsi_ioctl
r_int
id|scsi_ioctl
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_char
id|scsi_cmd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
multiline_comment|/* No idea how this happens.... */
r_if
c_cond
(paren
op_logical_neg
id|sdev
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/*&n;&t; * If we are in the middle of error recovery, don&squot;t let anyone&n;&t; * else try and use this device.  Also, if error recovery fails, it&n;&t; * may try and take the device offline, in which case all further&n;&t; * access to the device is prohibited.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|scsi_block_when_processing_errors
c_func
(paren
id|sdev
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SCSI_IOCTL_GET_IDLUN
suffix:colon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|scsi_idlun
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__put_user
c_func
(paren
(paren
id|sdev-&gt;id
op_amp
l_int|0xff
)paren
op_plus
(paren
(paren
id|sdev-&gt;lun
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_plus
(paren
(paren
id|sdev-&gt;channel
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_plus
(paren
(paren
id|sdev-&gt;host-&gt;host_no
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
comma
op_amp
(paren
(paren
r_struct
id|scsi_idlun
id|__user
op_star
)paren
id|arg
)paren
op_member_access_from_pointer
id|dev_id
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|sdev-&gt;host-&gt;unique_id
comma
op_amp
(paren
(paren
r_struct
id|scsi_idlun
id|__user
op_star
)paren
id|arg
)paren
op_member_access_from_pointer
id|host_unique_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SCSI_IOCTL_GET_BUS_NUMBER
suffix:colon
r_return
id|put_user
c_func
(paren
id|sdev-&gt;host-&gt;host_no
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_PROBE_HOST
suffix:colon
r_return
id|ioctl_probe
c_func
(paren
id|sdev-&gt;host
comma
id|arg
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_SEND_COMMAND
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
op_logical_or
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_return
id|scsi_ioctl_send_command
c_func
(paren
id|sdev
comma
id|arg
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_DOORLOCK
suffix:colon
r_return
id|scsi_set_medium_removal
c_func
(paren
id|sdev
comma
id|SCSI_REMOVAL_PREVENT
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_DOORUNLOCK
suffix:colon
r_return
id|scsi_set_medium_removal
c_func
(paren
id|sdev
comma
id|SCSI_REMOVAL_ALLOW
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_TEST_UNIT_READY
suffix:colon
id|scsi_cmd
(braket
l_int|0
)braket
op_assign
id|TEST_UNIT_READY
suffix:semicolon
id|scsi_cmd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|2
)braket
op_assign
id|scsi_cmd
(braket
l_int|3
)braket
op_assign
id|scsi_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|ioctl_internal_command
c_func
(paren
id|sdev
comma
id|scsi_cmd
comma
id|IOCTL_NORMAL_TIMEOUT
comma
id|NORMAL_RETRIES
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_START_UNIT
suffix:colon
id|scsi_cmd
(braket
l_int|0
)braket
op_assign
id|START_STOP
suffix:semicolon
id|scsi_cmd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|2
)braket
op_assign
id|scsi_cmd
(braket
l_int|3
)braket
op_assign
id|scsi_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|4
)braket
op_assign
l_int|1
suffix:semicolon
r_return
id|ioctl_internal_command
c_func
(paren
id|sdev
comma
id|scsi_cmd
comma
id|START_STOP_TIMEOUT
comma
id|NORMAL_RETRIES
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_STOP_UNIT
suffix:colon
id|scsi_cmd
(braket
l_int|0
)braket
op_assign
id|START_STOP
suffix:semicolon
id|scsi_cmd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|2
)braket
op_assign
id|scsi_cmd
(braket
l_int|3
)braket
op_assign
id|scsi_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|ioctl_internal_command
c_func
(paren
id|sdev
comma
id|scsi_cmd
comma
id|START_STOP_TIMEOUT
comma
id|NORMAL_RETRIES
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_GET_PCI
suffix:colon
r_return
id|scsi_ioctl_get_pci
c_func
(paren
id|sdev
comma
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|sdev-&gt;host-&gt;hostt-&gt;ioctl
)paren
r_return
id|sdev-&gt;host-&gt;hostt
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|sdev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
