multiline_comment|/*&n; * arch/s390/appldata/appldata.h&n; *&n; * Definitions and interface for Linux - z/VM Monitor Stream.&n; *&n; * Copyright (C) 2003 IBM Corporation, IBM Deutschland Entwicklung GmbH.&n; *&n; * Author: Gerald Schaefer &lt;geraldsc@de.ibm.com&gt;&n; */
singleline_comment|//#define APPLDATA_DEBUG&t;&t;&t;/* Debug messages on/off */
DECL|macro|APPLDATA_MAX_REC_SIZE
mdefine_line|#define APPLDATA_MAX_REC_SIZE&t;  4024&t;/* Maximum size of the */
multiline_comment|/* data buffer */
DECL|macro|APPLDATA_MAX_PROCS
mdefine_line|#define APPLDATA_MAX_PROCS 100
DECL|macro|APPLDATA_PROC_NAME_LENGTH
mdefine_line|#define APPLDATA_PROC_NAME_LENGTH 16&t;/* Max. length of /proc name */
DECL|macro|APPLDATA_RECORD_MEM_ID
mdefine_line|#define APPLDATA_RECORD_MEM_ID&t;&t;0x01&t;/* IDs to identify the */
DECL|macro|APPLDATA_RECORD_OS_ID
mdefine_line|#define APPLDATA_RECORD_OS_ID&t;&t;0x02&t;/* individual records, */
DECL|macro|APPLDATA_RECORD_NET_SUM_ID
mdefine_line|#define APPLDATA_RECORD_NET_SUM_ID&t;0x03&t;/* must be &lt; 256 !     */
DECL|macro|APPLDATA_RECORD_PROC_ID
mdefine_line|#define APPLDATA_RECORD_PROC_ID&t;&t;0x04
DECL|macro|CTL_APPLDATA
mdefine_line|#define CTL_APPLDATA &t;&t;2120&t;/* sysctl IDs, must be unique */
DECL|macro|CTL_APPLDATA_TIMER
mdefine_line|#define CTL_APPLDATA_TIMER &t;2121
DECL|macro|CTL_APPLDATA_INTERVAL
mdefine_line|#define CTL_APPLDATA_INTERVAL &t;2122
DECL|macro|CTL_APPLDATA_MEM
mdefine_line|#define CTL_APPLDATA_MEM&t;2123
DECL|macro|CTL_APPLDATA_OS
mdefine_line|#define CTL_APPLDATA_OS&t;&t;2124
DECL|macro|CTL_APPLDATA_NET_SUM
mdefine_line|#define CTL_APPLDATA_NET_SUM&t;2125
DECL|macro|CTL_APPLDATA_PROC
mdefine_line|#define CTL_APPLDATA_PROC&t;2126
DECL|macro|P_INFO
mdefine_line|#define P_INFO(x...)&t;printk(KERN_INFO MY_PRINT_NAME &quot; info: &quot; x)
DECL|macro|P_ERROR
mdefine_line|#define P_ERROR(x...)&t;printk(KERN_ERR MY_PRINT_NAME &quot; error: &quot; x)
DECL|macro|P_WARNING
mdefine_line|#define P_WARNING(x...)&t;printk(KERN_WARNING MY_PRINT_NAME &quot; status: &quot; x)
macro_line|#ifdef APPLDATA_DEBUG
DECL|macro|P_DEBUG
mdefine_line|#define P_DEBUG(x...)   printk(KERN_DEBUG MY_PRINT_NAME &quot; debug: &quot; x)
macro_line|#else
DECL|macro|P_DEBUG
mdefine_line|#define P_DEBUG(x...)   do {} while (0)
macro_line|#endif
DECL|struct|appldata_ops
r_struct
id|appldata_ops
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|sysctl_header
r_struct
id|ctl_table_header
op_star
id|sysctl_header
suffix:semicolon
DECL|member|ctl_table
r_struct
id|ctl_table
op_star
id|ctl_table
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* monitoring status */
multiline_comment|/* fill in from here */
DECL|member|ctl_nr
r_int
r_int
id|ctl_nr
suffix:semicolon
multiline_comment|/* sysctl ID */
DECL|member|name
r_char
id|name
(braket
id|APPLDATA_PROC_NAME_LENGTH
)braket
suffix:semicolon
multiline_comment|/* name of /proc fs node */
DECL|member|record_nr
r_int
r_char
id|record_nr
suffix:semicolon
multiline_comment|/* Record Nr. for Product ID */
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* callback function */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* record data */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of record */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* THIS_MODULE */
)brace
suffix:semicolon
r_extern
r_int
id|appldata_register_ops
c_func
(paren
r_struct
id|appldata_ops
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_void
id|appldata_unregister_ops
c_func
(paren
r_struct
id|appldata_ops
op_star
id|ops
)paren
suffix:semicolon
eof
