macro_line|#ifndef _CSS_H
DECL|macro|_CSS_H
mdefine_line|#define _CSS_H
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/cio.h&gt;
multiline_comment|/*&n; * path grouping stuff&n; */
DECL|macro|SPID_FUNC_SINGLE_PATH
mdefine_line|#define SPID_FUNC_SINGLE_PATH&t;   0x00
DECL|macro|SPID_FUNC_MULTI_PATH
mdefine_line|#define SPID_FUNC_MULTI_PATH&t;   0x80
DECL|macro|SPID_FUNC_ESTABLISH
mdefine_line|#define SPID_FUNC_ESTABLISH&t;   0x00
DECL|macro|SPID_FUNC_RESIGN
mdefine_line|#define SPID_FUNC_RESIGN&t;   0x40
DECL|macro|SPID_FUNC_DISBAND
mdefine_line|#define SPID_FUNC_DISBAND&t;   0x20
DECL|macro|SNID_STATE1_RESET
mdefine_line|#define SNID_STATE1_RESET&t;   0
DECL|macro|SNID_STATE1_UNGROUPED
mdefine_line|#define SNID_STATE1_UNGROUPED&t;   2
DECL|macro|SNID_STATE1_GROUPED
mdefine_line|#define SNID_STATE1_GROUPED&t;   3
DECL|macro|SNID_STATE2_NOT_RESVD
mdefine_line|#define SNID_STATE2_NOT_RESVD&t;   0
DECL|macro|SNID_STATE2_RESVD_ELSE
mdefine_line|#define SNID_STATE2_RESVD_ELSE&t;   2
DECL|macro|SNID_STATE2_RESVD_SELF
mdefine_line|#define SNID_STATE2_RESVD_SELF&t;   3
DECL|macro|SNID_STATE3_MULTI_PATH
mdefine_line|#define SNID_STATE3_MULTI_PATH&t;   1
DECL|macro|SNID_STATE3_SINGLE_PATH
mdefine_line|#define SNID_STATE3_SINGLE_PATH&t;   0
DECL|struct|path_state
r_struct
id|path_state
(brace
DECL|member|state1
id|__u8
id|state1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* path state value 1 */
DECL|member|state2
id|__u8
id|state2
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* path state value 2 */
DECL|member|state3
id|__u8
id|state3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* path state value 3 */
DECL|member|resvd
id|__u8
id|resvd
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* reserved */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|pgid
r_struct
id|pgid
(brace
r_union
(brace
DECL|member|fc
id|__u8
id|fc
suffix:semicolon
multiline_comment|/* SPID function code */
DECL|member|ps
r_struct
id|path_state
id|ps
suffix:semicolon
multiline_comment|/* SNID path state */
DECL|member|inf
)brace
id|inf
suffix:semicolon
DECL|member|cpu_addr
id|__u32
id|cpu_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* CPU address */
DECL|member|cpu_id
id|__u32
id|cpu_id
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* CPU identification */
DECL|member|cpu_model
id|__u32
id|cpu_model
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* CPU model */
DECL|member|tod_high
id|__u32
id|tod_high
suffix:semicolon
multiline_comment|/* high word TOD clock */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|pgid
id|global_pgid
suffix:semicolon
DECL|macro|MAX_CIWS
mdefine_line|#define MAX_CIWS 8
multiline_comment|/*&n; * sense-id response buffer layout&n; */
DECL|struct|senseid
r_struct
id|senseid
(brace
multiline_comment|/* common part */
DECL|member|reserved
id|__u8
id|reserved
suffix:semicolon
multiline_comment|/* always 0x&squot;FF&squot; */
DECL|member|cu_type
id|__u16
id|cu_type
suffix:semicolon
multiline_comment|/* control unit type */
DECL|member|cu_model
id|__u8
id|cu_model
suffix:semicolon
multiline_comment|/* control unit model */
DECL|member|dev_type
id|__u16
id|dev_type
suffix:semicolon
multiline_comment|/* device type */
DECL|member|dev_model
id|__u8
id|dev_model
suffix:semicolon
multiline_comment|/* device model */
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
multiline_comment|/* padding byte */
multiline_comment|/* extended part */
DECL|member|ciw
r_struct
id|ciw
id|ciw
(braket
id|MAX_CIWS
)braket
suffix:semicolon
multiline_comment|/* variable # of CIWs */
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|struct|ccw_device_private
r_struct
id|ccw_device_private
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* device state */
DECL|member|onoff
id|atomic_t
id|onoff
suffix:semicolon
DECL|member|registered
r_int
r_int
id|registered
suffix:semicolon
DECL|member|devno
id|__u16
id|devno
suffix:semicolon
multiline_comment|/* device number */
DECL|member|irq
id|__u16
id|irq
suffix:semicolon
multiline_comment|/* subchannel number */
DECL|member|imask
id|__u8
id|imask
suffix:semicolon
multiline_comment|/* lpm mask for SNID/SID/SPGID */
DECL|member|iretry
r_int
id|iretry
suffix:semicolon
multiline_comment|/* retry counter SNID/SID/SPGID */
r_struct
(brace
DECL|member|fast
r_int
r_int
id|fast
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* post with &quot;channel end&quot; */
DECL|member|repall
r_int
r_int
id|repall
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* report every interrupt status */
DECL|member|pgroup
r_int
r_int
id|pgroup
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* do path grouping */
DECL|member|force
r_int
r_int
id|force
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* allow forced online */
DECL|member|options
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|options
suffix:semicolon
r_struct
(brace
DECL|member|pgid_single
r_int
r_int
id|pgid_single
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* use single path for Set PGID */
DECL|member|esid
r_int
r_int
id|esid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Ext. SenseID supported by HW */
DECL|member|dosense
r_int
r_int
id|dosense
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* delayed SENSE required */
DECL|member|doverify
r_int
r_int
id|doverify
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* delayed path verification */
DECL|member|donotify
r_int
r_int
id|donotify
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* call notify function */
DECL|member|recog_done
r_int
r_int
id|recog_done
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dev. recog. complete */
DECL|member|flags
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|flags
suffix:semicolon
DECL|member|intparm
r_int
r_int
id|intparm
suffix:semicolon
multiline_comment|/* user interruption parameter */
DECL|member|qdio_data
r_struct
id|qdio_irq
op_star
id|qdio_data
suffix:semicolon
DECL|member|irb
r_struct
id|irb
id|irb
suffix:semicolon
multiline_comment|/* device status */
DECL|member|senseid
r_struct
id|senseid
id|senseid
suffix:semicolon
multiline_comment|/* SenseID info */
DECL|member|pgid
r_struct
id|pgid
id|pgid
suffix:semicolon
multiline_comment|/* path group ID */
DECL|member|iccws
r_struct
id|ccw1
id|iccws
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ccws for SNID/SID/SPGID commands */
DECL|member|kick_work
r_struct
id|work_struct
id|kick_work
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|cmb
r_void
op_star
id|cmb
suffix:semicolon
multiline_comment|/* measurement information */
DECL|member|cmb_list
r_struct
id|list_head
id|cmb_list
suffix:semicolon
multiline_comment|/* list of measured devices */
DECL|member|cmb_start_time
id|u64
id|cmb_start_time
suffix:semicolon
multiline_comment|/* clock value of cmb reset */
DECL|member|cmb_wait
r_void
op_star
id|cmb_wait
suffix:semicolon
multiline_comment|/* deferred cmb enable/disable */
)brace
suffix:semicolon
multiline_comment|/*&n; * A css driver handles all subchannels of one type.&n; * Currently, we only care about I/O subchannels (type 0), these&n; * have a ccw_device connected to them.&n; */
DECL|struct|css_driver
r_struct
id|css_driver
(brace
DECL|member|subchannel_type
r_int
r_int
id|subchannel_type
suffix:semicolon
DECL|member|drv
r_struct
id|device_driver
id|drv
suffix:semicolon
DECL|member|irq
r_void
(paren
op_star
id|irq
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|member|notify
r_int
(paren
op_star
id|notify
)paren
(paren
r_struct
id|device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|verify
r_void
(paren
op_star
id|verify
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|member|termination
r_void
(paren
op_star
id|termination
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * all css_drivers have the css_bus_type&n; */
r_extern
r_struct
id|bus_type
id|css_bus_type
suffix:semicolon
r_extern
r_struct
id|css_driver
id|io_subchannel_driver
suffix:semicolon
r_int
id|css_probe_device
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_struct
id|subchannel
op_star
id|get_subchannel_by_schid
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
r_int
id|highest_subchannel
suffix:semicolon
r_extern
r_int
id|css_init_done
suffix:semicolon
DECL|macro|__MAX_SUBCHANNELS
mdefine_line|#define __MAX_SUBCHANNELS 65536
r_extern
r_struct
id|bus_type
id|css_bus_type
suffix:semicolon
r_extern
r_struct
id|device
id|css_bus_device
suffix:semicolon
multiline_comment|/* Some helper functions for disconnected state. */
r_int
id|device_is_disconnected
c_func
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_void
id|device_set_disconnected
c_func
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
r_void
id|device_trigger_reprobe
c_func
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
multiline_comment|/* Helper functions for vary on/off. */
r_void
id|device_set_waiting
c_func
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
multiline_comment|/* Machine check helper function. */
r_void
id|device_kill_pending_timer
c_func
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
multiline_comment|/* Helper functions to build lists for the slow path. */
r_int
id|css_enqueue_subchannel_slow
c_func
(paren
r_int
r_int
id|schid
)paren
suffix:semicolon
r_void
id|css_walk_subchannel_slow_list
c_func
(paren
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_void
id|css_clear_subchannel_slow_list
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|css_slow_subchannels_exist
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|need_rescan
suffix:semicolon
r_extern
r_struct
id|workqueue_struct
op_star
id|slow_path_wq
suffix:semicolon
r_extern
r_struct
id|work_struct
id|slow_path_work
suffix:semicolon
macro_line|#endif
eof
