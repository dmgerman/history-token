multiline_comment|/*&n; *  arch/s390/kernel/s390io.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; */
macro_line|#ifndef __s390io_h
DECL|macro|__s390io_h
mdefine_line|#define __s390io_h
multiline_comment|/*&n; * IRQ data structure used by I/O subroutines&n; *&n; * Note : If bit flags are added, the &quot;unused&quot; value must be&n; *        decremented accordingly !&n; */
DECL|struct|_ioinfo
r_typedef
r_struct
id|_ioinfo
(brace
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* aka. subchannel number */
DECL|member|irq_lock
id|spinlock_t
id|irq_lock
suffix:semicolon
multiline_comment|/* irq lock */
DECL|member|prev
r_struct
id|_ioinfo
op_star
id|prev
suffix:semicolon
DECL|member|next
r_struct
id|_ioinfo
op_star
id|next
suffix:semicolon
r_union
(brace
DECL|member|info
r_int
r_int
id|info
suffix:semicolon
r_struct
(brace
DECL|member|busy
r_int
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device currently in use */
DECL|member|oper
r_int
r_int
id|oper
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device is operational */
DECL|member|fast
r_int
r_int
id|fast
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* post with &quot;channel end&quot;, ...    */
multiline_comment|/* ... don&squot;t wait for &quot;device end&quot; */
multiline_comment|/* ... from do_IO() parameters     */
DECL|member|ready
r_int
r_int
id|ready
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* interrupt handler registered */
DECL|member|haltio
r_int
r_int
id|haltio
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* halt_IO in process */
DECL|member|doio
r_int
r_int
id|doio
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* do_IO in process */
DECL|member|doio_q
r_int
r_int
id|doio_q
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* do_IO queued - only possible ... */
multiline_comment|/* ... if &squot;fast&squot; is set too */
DECL|member|w4final
r_int
r_int
id|w4final
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* wait for final status, internally */
multiline_comment|/* ... used with &squot;fast&squot; setting only */
DECL|member|repall
r_int
r_int
id|repall
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* report every interrupt status */
DECL|member|unready
r_int
r_int
id|unready
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* deregister irq handler in process */
DECL|member|d_disable
r_int
r_int
id|d_disable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* delayed disabling required */
DECL|member|w4sense
r_int
r_int
id|w4sense
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SENSE status pending */
DECL|member|syncio
r_int
r_int
id|syncio
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* synchronous I/O requested */
DECL|member|consns
r_int
r_int
id|consns
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* concurrent sense is available */
DECL|member|delsense
r_int
r_int
id|delsense
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* delayed SENSE required */
DECL|member|s_pend
r_int
r_int
id|s_pend
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* status pending condition */
DECL|member|pgid
r_int
r_int
id|pgid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* &quot;path group ID&quot; is valid */
DECL|member|pgid_supp
r_int
r_int
id|pgid_supp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* &quot;path group ID&quot; command is supported */
DECL|member|esid
r_int
r_int
id|esid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Ext. SenseID supported by HW */
DECL|member|rcd
r_int
r_int
id|rcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* RCD supported by HW */
DECL|member|repnone
r_int
r_int
id|repnone
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t call IRQ handler on interrupt */
DECL|member|newreq
r_int
r_int
id|newreq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* new register interface */
DECL|member|dval
r_int
r_int
id|dval
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device number valid */
DECL|member|unknown
r_int
r_int
id|unknown
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* unknown device - if SenseID failed */
DECL|member|unused
r_int
r_int
id|unused
suffix:colon
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
op_minus
l_int|24
)paren
suffix:semicolon
multiline_comment|/* unused */
DECL|member|flags
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|flags
suffix:semicolon
DECL|member|ui
)brace
id|ui
suffix:semicolon
DECL|member|u_intparm
r_int
r_int
id|u_intparm
suffix:semicolon
multiline_comment|/* user interruption parameter */
DECL|member|senseid
id|senseid_t
id|senseid
suffix:semicolon
multiline_comment|/* SenseID info */
DECL|member|irq_desc
id|irq_desc_t
id|irq_desc
suffix:semicolon
multiline_comment|/* irq descriptor */
DECL|member|nopfunc
id|not_oper_handler_func_t
id|nopfunc
suffix:semicolon
multiline_comment|/* not oper handler */
DECL|member|ulpm
id|__u8
id|ulpm
suffix:semicolon
multiline_comment|/* logical path mask used for I/O */
DECL|member|opm
id|__u8
id|opm
suffix:semicolon
multiline_comment|/* path mask of operational paths */
DECL|member|devno
id|__u16
id|devno
suffix:semicolon
multiline_comment|/* device number */
DECL|member|pgid
id|pgid_t
id|pgid
suffix:semicolon
multiline_comment|/* path group ID */
DECL|member|schib
id|schib_t
id|schib
suffix:semicolon
multiline_comment|/* subchannel information block */
DECL|member|orb
id|orb_t
id|orb
suffix:semicolon
multiline_comment|/* operation request block */
DECL|member|devstat
id|devstat_t
id|devstat
suffix:semicolon
multiline_comment|/* device status */
DECL|member|qcpa
id|ccw1_t
op_star
id|qcpa
suffix:semicolon
multiline_comment|/* queued channel program */
DECL|member|senseccw
id|ccw1_t
id|senseccw
suffix:semicolon
multiline_comment|/* ccw for sense command */
DECL|member|sense_data
id|__u8
id|sense_data
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* buffer for basic sense */
DECL|member|stctl
r_int
r_int
id|stctl
suffix:semicolon
multiline_comment|/* accumulated status control from irb */
DECL|member|qintparm
r_int
r_int
id|qintparm
suffix:semicolon
multiline_comment|/* queued interruption parameter  */
DECL|member|qflag
r_int
r_int
id|qflag
suffix:semicolon
multiline_comment|/* queued flags */
DECL|member|qlpm
id|__u8
id|qlpm
suffix:semicolon
multiline_comment|/* queued logical path mask */
DECL|member|syncnt
id|__u32
id|syncnt
suffix:semicolon
multiline_comment|/* sync I/O recursive usage count */
DECL|typedef|ioinfo_t
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|ioinfo_t
suffix:semicolon
DECL|macro|IOINFO_FLAGS_BUSY
mdefine_line|#define IOINFO_FLAGS_BUSY    0x80000000
DECL|macro|IOINFO_FLAGS_OPER
mdefine_line|#define IOINFO_FLAGS_OPER    0x40000000
DECL|macro|IOINFO_FLAGS_FAST
mdefine_line|#define IOINFO_FLAGS_FAST    0x20000000
DECL|macro|IOINFO_FLAGS_READY
mdefine_line|#define IOINFO_FLAGS_READY   0x10000000
DECL|macro|IOINFO_FLAGS_HALTIO
mdefine_line|#define IOINFO_FLAGS_HALTIO  0x08000000
DECL|macro|IOINFO_FLAGS_DOIO
mdefine_line|#define IOINFO_FLAGS_DOIO    0x04000000
DECL|macro|IOINFO_FLAGS_DOIO_Q
mdefine_line|#define IOINFO_FLAGS_DOIO_Q  0x02000000
DECL|macro|IOINFO_FLAGS_W4FINAL
mdefine_line|#define IOINFO_FLAGS_W4FINAL 0x01000000
DECL|macro|IOINFO_FLAGS_REPALL
mdefine_line|#define IOINFO_FLAGS_REPALL  0x00800000
r_extern
id|ioinfo_t
op_star
id|ioinfo
(braket
)braket
suffix:semicolon
macro_line|#endif  /* __s390io_h */
eof
