macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#include &lt;linux/usb_ch9.h&gt;
multiline_comment|/*&n; * Filesystem based user-mode API to USB Gadget controller hardware&n; *&n; * Almost everything can be done with only read and write operations,&n; * on endpoint files found in one directory.  They are configured by&n; * writing descriptors, and then may be used for normal stream style&n; * i/o requests.  When ep0 is configured, the device can enumerate;&n; * when it&squot;s closed, the device disconnects from usb.&n; *&n; * Configuration and device descriptors get written to /dev/gadget/$CHIP,&n; * which may then be used to read usb_gadgetfs_event structs.  The driver&n; * may activate endpoints as it handles SET_CONFIGURATION setup events,&n; * or earlier; writing endpoint descriptors to /dev/gadget/$ENDPOINT&n; * then performing data transfers by reading or writing.&n; */
multiline_comment|/*&n; * Events are delivered on the ep0 file descriptor, if the user mode driver&n; * reads from this file descriptor after writing the descriptors.  Don&squot;t&n; * stop polling this descriptor, if you write that kind of driver.&n; */
DECL|enum|usb_gadgetfs_event_type
r_enum
id|usb_gadgetfs_event_type
(brace
DECL|enumerator|GADGETFS_NOP
id|GADGETFS_NOP
op_assign
l_int|0
comma
DECL|enumerator|GADGETFS_CONNECT
id|GADGETFS_CONNECT
comma
DECL|enumerator|GADGETFS_DISCONNECT
id|GADGETFS_DISCONNECT
comma
DECL|enumerator|GADGETFS_SETUP
id|GADGETFS_SETUP
comma
DECL|enumerator|GADGETFS_SUSPEND
id|GADGETFS_SUSPEND
comma
singleline_comment|// and likely more !
)brace
suffix:semicolon
DECL|struct|usb_gadgetfs_event
r_struct
id|usb_gadgetfs_event
(brace
DECL|member|type
r_enum
id|usb_gadgetfs_event_type
id|type
suffix:semicolon
r_union
(brace
singleline_comment|// NOP, DISCONNECT, SUSPEND: nothing
singleline_comment|// ... some hardware can&squot;t report disconnection
singleline_comment|// CONNECT: just the speed
DECL|member|speed
r_enum
id|usb_device_speed
id|speed
suffix:semicolon
singleline_comment|// SETUP: packet; DATA phase i/o precedes next event
singleline_comment|// (setup.bmRequestType &amp; USB_DIR_IN) flags direction 
singleline_comment|// ... includes SET_CONFIGURATION, SET_INTERFACE
DECL|member|setup
r_struct
id|usb_ctrlrequest
id|setup
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* endpoint ioctls */
multiline_comment|/* IN transfers may be reported to the gadget driver as complete&n; * &t;when the fifo is loaded, before the host reads the data;&n; * OUT transfers may be reported to the host&squot;s &quot;client&quot; driver as&n; * &t;complete when they&squot;re sitting in the FIFO unread.&n; * THIS returns how many bytes are &quot;unclaimed&quot; in the endpoint fifo&n; * (needed for precise fault handling, when the hardware allows it)&n; */
DECL|macro|GADGETFS_FIFO_STATUS
mdefine_line|#define&t;GADGETFS_FIFO_STATUS&t;_IO(&squot;g&squot;,1)
multiline_comment|/* discards any unclaimed data in the fifo. */
DECL|macro|GADGETFS_FIFO_FLUSH
mdefine_line|#define&t;GADGETFS_FIFO_FLUSH&t;_IO(&squot;g&squot;,2)
multiline_comment|/* resets endpoint halt+toggle; used to implement set_interface.&n; * some hardware (like pxa2xx) can&squot;t support this.&n; */
DECL|macro|GADGETFS_CLEAR_HALT
mdefine_line|#define&t;GADGETFS_CLEAR_HALT&t;_IO(&squot;g&squot;,3)
eof
