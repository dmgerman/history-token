macro_line|#ifndef S390_DEVICE_H
DECL|macro|S390_DEVICE_H
mdefine_line|#define S390_DEVICE_H
multiline_comment|/*&n; * states of the device statemachine&n; */
DECL|enum|dev_state
r_enum
id|dev_state
(brace
DECL|enumerator|DEV_STATE_NOT_OPER
id|DEV_STATE_NOT_OPER
comma
DECL|enumerator|DEV_STATE_SENSE_PGID
id|DEV_STATE_SENSE_PGID
comma
DECL|enumerator|DEV_STATE_SENSE_ID
id|DEV_STATE_SENSE_ID
comma
DECL|enumerator|DEV_STATE_OFFLINE
id|DEV_STATE_OFFLINE
comma
DECL|enumerator|DEV_STATE_VERIFY
id|DEV_STATE_VERIFY
comma
DECL|enumerator|DEV_STATE_ONLINE
id|DEV_STATE_ONLINE
comma
DECL|enumerator|DEV_STATE_W4SENSE
id|DEV_STATE_W4SENSE
comma
DECL|enumerator|DEV_STATE_DISBAND_PGID
id|DEV_STATE_DISBAND_PGID
comma
DECL|enumerator|DEV_STATE_BOXED
id|DEV_STATE_BOXED
comma
multiline_comment|/* states to wait for i/o completion before doing something */
DECL|enumerator|DEV_STATE_CLEAR_VERIFY
id|DEV_STATE_CLEAR_VERIFY
comma
DECL|enumerator|DEV_STATE_TIMEOUT_KILL
id|DEV_STATE_TIMEOUT_KILL
comma
DECL|enumerator|DEV_STATE_WAIT4IO
id|DEV_STATE_WAIT4IO
comma
DECL|enumerator|DEV_STATE_QUIESCE
id|DEV_STATE_QUIESCE
comma
multiline_comment|/* special states for devices gone not operational */
DECL|enumerator|DEV_STATE_DISCONNECTED
id|DEV_STATE_DISCONNECTED
comma
DECL|enumerator|DEV_STATE_DISCONNECTED_SENSE_ID
id|DEV_STATE_DISCONNECTED_SENSE_ID
comma
DECL|enumerator|DEV_STATE_CMFCHANGE
id|DEV_STATE_CMFCHANGE
comma
multiline_comment|/* last element! */
DECL|enumerator|NR_DEV_STATES
id|NR_DEV_STATES
)brace
suffix:semicolon
multiline_comment|/*&n; * asynchronous events of the device statemachine&n; */
DECL|enum|dev_event
r_enum
id|dev_event
(brace
DECL|enumerator|DEV_EVENT_NOTOPER
id|DEV_EVENT_NOTOPER
comma
DECL|enumerator|DEV_EVENT_INTERRUPT
id|DEV_EVENT_INTERRUPT
comma
DECL|enumerator|DEV_EVENT_TIMEOUT
id|DEV_EVENT_TIMEOUT
comma
DECL|enumerator|DEV_EVENT_VERIFY
id|DEV_EVENT_VERIFY
comma
multiline_comment|/* last element! */
DECL|enumerator|NR_DEV_EVENTS
id|NR_DEV_EVENTS
)brace
suffix:semicolon
r_struct
id|ccw_device
suffix:semicolon
multiline_comment|/*&n; * action called through jumptable&n; */
DECL|typedef|fsm_func_t
r_typedef
r_void
(paren
id|fsm_func_t
)paren
(paren
r_struct
id|ccw_device
op_star
comma
r_enum
id|dev_event
)paren
suffix:semicolon
r_extern
id|fsm_func_t
op_star
id|dev_jumptable
(braket
id|NR_DEV_STATES
)braket
(braket
id|NR_DEV_EVENTS
)braket
suffix:semicolon
r_static
r_inline
r_void
DECL|function|dev_fsm_event
id|dev_fsm_event
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_enum
id|dev_event
id|dev_event
)paren
(brace
id|dev_jumptable
(braket
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
)braket
(braket
id|dev_event
)braket
(paren
id|cdev
comma
id|dev_event
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Delivers 1 if the device state is final.&n; */
r_static
r_inline
r_int
DECL|function|dev_fsm_final_state
id|dev_fsm_final_state
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_return
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_eq
id|DEV_STATE_NOT_OPER
op_logical_or
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_eq
id|DEV_STATE_OFFLINE
op_logical_or
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_eq
id|DEV_STATE_ONLINE
op_logical_or
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_eq
id|DEV_STATE_BOXED
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|workqueue_struct
op_star
id|ccw_device_work
suffix:semicolon
r_extern
r_struct
id|workqueue_struct
op_star
id|ccw_device_notify_work
suffix:semicolon
r_void
id|io_subchannel_recog_done
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
r_int
id|ccw_device_cancel_halt_clear
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_int
id|ccw_device_register
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_void
id|ccw_device_do_unreg_rereg
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|ccw_device_call_sch_unregister
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_int
id|ccw_device_recognition
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_int
id|ccw_device_online
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_int
id|ccw_device_offline
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Function prototypes for device status and basic sense stuff. */
r_void
id|ccw_device_accumulate_irb
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
r_void
id|ccw_device_accumulate_basic_sense
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
r_int
id|ccw_device_accumulate_and_sense
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
r_int
id|ccw_device_do_sense
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
multiline_comment|/* Function prototypes for sense id stuff. */
r_void
id|ccw_device_sense_id_start
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_void
id|ccw_device_sense_id_irq
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_enum
id|dev_event
)paren
suffix:semicolon
r_void
id|ccw_device_sense_id_done
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Function prototypes for path grouping stuff. */
r_void
id|ccw_device_sense_pgid_start
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_void
id|ccw_device_sense_pgid_irq
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_enum
id|dev_event
)paren
suffix:semicolon
r_void
id|ccw_device_sense_pgid_done
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|ccw_device_verify_start
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_void
id|ccw_device_verify_irq
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_enum
id|dev_event
)paren
suffix:semicolon
r_void
id|ccw_device_verify_done
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|ccw_device_disband_start
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_void
id|ccw_device_disband_irq
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_enum
id|dev_event
)paren
suffix:semicolon
r_void
id|ccw_device_disband_done
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|ccw_device_call_handler
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_int
id|ccw_device_stlck
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
multiline_comment|/* qdio needs this. */
r_void
id|ccw_device_set_timeout
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|retry_set_schib
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
macro_line|#endif
eof
