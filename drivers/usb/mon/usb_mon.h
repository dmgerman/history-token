multiline_comment|/*&n; * The USB Monitor, inspired by Dave Harding&squot;s USBMon.&n; */
macro_line|#ifndef __USB_MON_H
DECL|macro|__USB_MON_H
mdefine_line|#define __USB_MON_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kref.h&gt;
multiline_comment|/* #include &lt;linux/usb.h&gt; */
multiline_comment|/* We use struct pointers only in this header */
DECL|macro|TAG
mdefine_line|#define TAG &quot;usbmon&quot;
DECL|struct|mon_bus
r_struct
id|mon_bus
(brace
DECL|member|bus_link
r_struct
id|list_head
id|bus_link
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|dent_s
r_struct
id|dentry
op_star
id|dent_s
suffix:semicolon
multiline_comment|/* Debugging file */
DECL|member|dent_t
r_struct
id|dentry
op_star
id|dent_t
suffix:semicolon
multiline_comment|/* Text interface file */
DECL|member|u_bus
r_struct
id|usb_bus
op_star
id|u_bus
suffix:semicolon
multiline_comment|/* Ref */
DECL|member|nreaders
r_int
id|nreaders
suffix:semicolon
multiline_comment|/* Under mon_lock AND mbus-&gt;lock */
DECL|member|r_list
r_struct
id|list_head
id|r_list
suffix:semicolon
multiline_comment|/* Chain of readers (usually one) */
DECL|member|ref
r_struct
id|kref
id|ref
suffix:semicolon
multiline_comment|/* Under mon_lock */
multiline_comment|/* Stats */
DECL|member|cnt_text_lost
r_int
r_int
id|cnt_text_lost
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * An instance of a process which opened a file (but can fork later)&n; */
DECL|struct|mon_reader
r_struct
id|mon_reader
(brace
DECL|member|r_link
r_struct
id|list_head
id|r_link
suffix:semicolon
DECL|member|m_bus
r_struct
id|mon_bus
op_star
id|m_bus
suffix:semicolon
DECL|member|r_data
r_void
op_star
id|r_data
suffix:semicolon
multiline_comment|/* Use container_of instead? */
DECL|member|rnf_submit
r_void
(paren
op_star
id|rnf_submit
)paren
(paren
r_void
op_star
id|data
comma
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
DECL|member|rnf_complete
r_void
(paren
op_star
id|rnf_complete
)paren
(paren
r_void
op_star
id|data
comma
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
)brace
suffix:semicolon
r_void
id|mon_reader_add
c_func
(paren
r_struct
id|mon_bus
op_star
id|mbus
comma
r_struct
id|mon_reader
op_star
id|r
)paren
suffix:semicolon
r_void
id|mon_reader_del
c_func
(paren
r_struct
id|mon_bus
op_star
id|mbus
comma
r_struct
id|mon_reader
op_star
id|r
)paren
suffix:semicolon
r_extern
r_struct
id|semaphore
id|mon_lock
suffix:semicolon
r_extern
r_struct
id|file_operations
id|mon_fops_text
suffix:semicolon
r_extern
r_struct
id|file_operations
id|mon_fops_stat
suffix:semicolon
macro_line|#endif /* __USB_MON_H */
eof
