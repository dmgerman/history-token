multiline_comment|/*&n; *  include/asm-s390/lowcore.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; */
macro_line|#ifndef _ASM_S390_LOWCORE_H
DECL|macro|_ASM_S390_LOWCORE_H
mdefine_line|#define _ASM_S390_LOWCORE_H
macro_line|#ifndef __s390x__
DECL|macro|__LC_EXT_OLD_PSW
mdefine_line|#define __LC_EXT_OLD_PSW                0x018
DECL|macro|__LC_SVC_OLD_PSW
mdefine_line|#define __LC_SVC_OLD_PSW                0x020
DECL|macro|__LC_PGM_OLD_PSW
mdefine_line|#define __LC_PGM_OLD_PSW                0x028
DECL|macro|__LC_MCK_OLD_PSW
mdefine_line|#define __LC_MCK_OLD_PSW                0x030
DECL|macro|__LC_IO_OLD_PSW
mdefine_line|#define __LC_IO_OLD_PSW                 0x038
DECL|macro|__LC_EXT_NEW_PSW
mdefine_line|#define __LC_EXT_NEW_PSW                0x058
DECL|macro|__LC_SVC_NEW_PSW
mdefine_line|#define __LC_SVC_NEW_PSW                0x060
DECL|macro|__LC_PGM_NEW_PSW
mdefine_line|#define __LC_PGM_NEW_PSW                0x068
DECL|macro|__LC_MCK_NEW_PSW
mdefine_line|#define __LC_MCK_NEW_PSW                0x070
DECL|macro|__LC_IO_NEW_PSW
mdefine_line|#define __LC_IO_NEW_PSW                 0x078
macro_line|#else /* !__s390x__ */
DECL|macro|__LC_EXT_OLD_PSW
mdefine_line|#define __LC_EXT_OLD_PSW                0x0130
DECL|macro|__LC_SVC_OLD_PSW
mdefine_line|#define __LC_SVC_OLD_PSW                0x0140
DECL|macro|__LC_PGM_OLD_PSW
mdefine_line|#define __LC_PGM_OLD_PSW                0x0150
DECL|macro|__LC_MCK_OLD_PSW
mdefine_line|#define __LC_MCK_OLD_PSW                0x0160
DECL|macro|__LC_IO_OLD_PSW
mdefine_line|#define __LC_IO_OLD_PSW                 0x0170
DECL|macro|__LC_EXT_NEW_PSW
mdefine_line|#define __LC_EXT_NEW_PSW                0x01b0
DECL|macro|__LC_SVC_NEW_PSW
mdefine_line|#define __LC_SVC_NEW_PSW                0x01c0
DECL|macro|__LC_PGM_NEW_PSW
mdefine_line|#define __LC_PGM_NEW_PSW                0x01d0
DECL|macro|__LC_MCK_NEW_PSW
mdefine_line|#define __LC_MCK_NEW_PSW                0x01e0
DECL|macro|__LC_IO_NEW_PSW
mdefine_line|#define __LC_IO_NEW_PSW                 0x01f0
macro_line|#endif /* !__s390x__ */
DECL|macro|__LC_EXT_PARAMS
mdefine_line|#define __LC_EXT_PARAMS                 0x080
DECL|macro|__LC_CPU_ADDRESS
mdefine_line|#define __LC_CPU_ADDRESS                0x084
DECL|macro|__LC_EXT_INT_CODE
mdefine_line|#define __LC_EXT_INT_CODE               0x086
DECL|macro|__LC_SVC_ILC
mdefine_line|#define __LC_SVC_ILC                    0x088
DECL|macro|__LC_SVC_INT_CODE
mdefine_line|#define __LC_SVC_INT_CODE               0x08A
DECL|macro|__LC_PGM_ILC
mdefine_line|#define __LC_PGM_ILC                    0x08C
DECL|macro|__LC_PGM_INT_CODE
mdefine_line|#define __LC_PGM_INT_CODE               0x08E
DECL|macro|__LC_PER_ATMID
mdefine_line|#define __LC_PER_ATMID&t;&t;&t;0x096
DECL|macro|__LC_PER_ADDRESS
mdefine_line|#define __LC_PER_ADDRESS&t;&t;0x098
DECL|macro|__LC_PER_ACCESS_ID
mdefine_line|#define __LC_PER_ACCESS_ID&t;&t;0x0A1
DECL|macro|__LC_SUBCHANNEL_ID
mdefine_line|#define __LC_SUBCHANNEL_ID              0x0B8
DECL|macro|__LC_SUBCHANNEL_NR
mdefine_line|#define __LC_SUBCHANNEL_NR              0x0BA
DECL|macro|__LC_IO_INT_PARM
mdefine_line|#define __LC_IO_INT_PARM                0x0BC
DECL|macro|__LC_IO_INT_WORD
mdefine_line|#define __LC_IO_INT_WORD                0x0C0
DECL|macro|__LC_MCCK_CODE
mdefine_line|#define __LC_MCCK_CODE                  0x0E8
DECL|macro|__LC_RETURN_PSW
mdefine_line|#define __LC_RETURN_PSW                 0x200
DECL|macro|__LC_SAVE_AREA
mdefine_line|#define __LC_SAVE_AREA                  0xC00
macro_line|#ifndef __s390x__
DECL|macro|__LC_IRB
mdefine_line|#define __LC_IRB&t;&t;&t;0x208
DECL|macro|__LC_SYNC_ENTER_TIMER
mdefine_line|#define __LC_SYNC_ENTER_TIMER&t;&t;0x248
DECL|macro|__LC_ASYNC_ENTER_TIMER
mdefine_line|#define __LC_ASYNC_ENTER_TIMER&t;&t;0x250
DECL|macro|__LC_EXIT_TIMER
mdefine_line|#define __LC_EXIT_TIMER&t;&t;&t;0x258
DECL|macro|__LC_LAST_UPDATE_TIMER
mdefine_line|#define __LC_LAST_UPDATE_TIMER&t;&t;0x260
DECL|macro|__LC_USER_TIMER
mdefine_line|#define __LC_USER_TIMER&t;&t;&t;0x268
DECL|macro|__LC_SYSTEM_TIMER
mdefine_line|#define __LC_SYSTEM_TIMER&t;&t;0x270
DECL|macro|__LC_LAST_UPDATE_CLOCK
mdefine_line|#define __LC_LAST_UPDATE_CLOCK&t;&t;0x278
DECL|macro|__LC_STEAL_CLOCK
mdefine_line|#define __LC_STEAL_CLOCK&t;&t;0x280
DECL|macro|__LC_KERNEL_STACK
mdefine_line|#define __LC_KERNEL_STACK               0xC40
DECL|macro|__LC_THREAD_INFO
mdefine_line|#define __LC_THREAD_INFO&t;&t;0xC44
DECL|macro|__LC_ASYNC_STACK
mdefine_line|#define __LC_ASYNC_STACK                0xC48
DECL|macro|__LC_KERNEL_ASCE
mdefine_line|#define __LC_KERNEL_ASCE&t;&t;0xC4C
DECL|macro|__LC_USER_ASCE
mdefine_line|#define __LC_USER_ASCE&t;&t;&t;0xC50
DECL|macro|__LC_PANIC_STACK
mdefine_line|#define __LC_PANIC_STACK                0xC54
DECL|macro|__LC_CPUID
mdefine_line|#define __LC_CPUID                      0xC60
DECL|macro|__LC_CPUADDR
mdefine_line|#define __LC_CPUADDR                    0xC68
DECL|macro|__LC_IPLDEV
mdefine_line|#define __LC_IPLDEV                     0xC7C
DECL|macro|__LC_JIFFY_TIMER
mdefine_line|#define __LC_JIFFY_TIMER&t;&t;0xC80
DECL|macro|__LC_CURRENT
mdefine_line|#define __LC_CURRENT&t;&t;&t;0xC90
DECL|macro|__LC_INT_CLOCK
mdefine_line|#define __LC_INT_CLOCK&t;&t;&t;0xC98
macro_line|#else /* __s390x__ */
DECL|macro|__LC_IRB
mdefine_line|#define __LC_IRB&t;&t;&t;0x210
DECL|macro|__LC_SYNC_ENTER_TIMER
mdefine_line|#define __LC_SYNC_ENTER_TIMER&t;&t;0x250
DECL|macro|__LC_ASYNC_ENTER_TIMER
mdefine_line|#define __LC_ASYNC_ENTER_TIMER&t;&t;0x258
DECL|macro|__LC_EXIT_TIMER
mdefine_line|#define __LC_EXIT_TIMER&t;&t;&t;0x260
DECL|macro|__LC_LAST_UPDATE_TIMER
mdefine_line|#define __LC_LAST_UPDATE_TIMER&t;&t;0x268
DECL|macro|__LC_USER_TIMER
mdefine_line|#define __LC_USER_TIMER&t;&t;&t;0x270
DECL|macro|__LC_SYSTEM_TIMER
mdefine_line|#define __LC_SYSTEM_TIMER&t;&t;0x278
DECL|macro|__LC_LAST_UPDATE_CLOCK
mdefine_line|#define __LC_LAST_UPDATE_CLOCK&t;&t;0x280
DECL|macro|__LC_STEAL_CLOCK
mdefine_line|#define __LC_STEAL_CLOCK&t;&t;0x288
DECL|macro|__LC_DIAG44_OPCODE
mdefine_line|#define __LC_DIAG44_OPCODE&t;&t;0x290
DECL|macro|__LC_KERNEL_STACK
mdefine_line|#define __LC_KERNEL_STACK               0xD40
DECL|macro|__LC_THREAD_INFO
mdefine_line|#define __LC_THREAD_INFO&t;&t;0xD48
DECL|macro|__LC_ASYNC_STACK
mdefine_line|#define __LC_ASYNC_STACK                0xD50
DECL|macro|__LC_KERNEL_ASCE
mdefine_line|#define __LC_KERNEL_ASCE&t;&t;0xD58
DECL|macro|__LC_USER_ASCE
mdefine_line|#define __LC_USER_ASCE&t;&t;&t;0xD60
DECL|macro|__LC_PANIC_STACK
mdefine_line|#define __LC_PANIC_STACK                0xD68
DECL|macro|__LC_CPUID
mdefine_line|#define __LC_CPUID                      0xD90
DECL|macro|__LC_CPUADDR
mdefine_line|#define __LC_CPUADDR                    0xD98
DECL|macro|__LC_IPLDEV
mdefine_line|#define __LC_IPLDEV                     0xDB8
DECL|macro|__LC_JIFFY_TIMER
mdefine_line|#define __LC_JIFFY_TIMER&t;&t;0xDC0
DECL|macro|__LC_CURRENT
mdefine_line|#define __LC_CURRENT&t;&t;&t;0xDD8
DECL|macro|__LC_INT_CLOCK
mdefine_line|#define __LC_INT_CLOCK&t;&t;&t;0xDE8
macro_line|#endif /* __s390x__ */
DECL|macro|__LC_PANIC_MAGIC
mdefine_line|#define __LC_PANIC_MAGIC                0xE00
macro_line|#ifndef __s390x__
DECL|macro|__LC_PFAULT_INTPARM
mdefine_line|#define __LC_PFAULT_INTPARM             0x080
DECL|macro|__LC_AREGS_SAVE_AREA
mdefine_line|#define __LC_AREGS_SAVE_AREA            0x120
DECL|macro|__LC_CREGS_SAVE_AREA
mdefine_line|#define __LC_CREGS_SAVE_AREA            0x1C0
macro_line|#else /* __s390x__ */
DECL|macro|__LC_PFAULT_INTPARM
mdefine_line|#define __LC_PFAULT_INTPARM             0x11B8
DECL|macro|__LC_AREGS_SAVE_AREA
mdefine_line|#define __LC_AREGS_SAVE_AREA            0x1340
DECL|macro|__LC_CREGS_SAVE_AREA
mdefine_line|#define __LC_CREGS_SAVE_AREA            0x1380
macro_line|#endif /* __s390x__ */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sigp.h&gt;
r_void
id|restart_int_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ext_int_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|system_call
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pgm_check_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|mcck_int_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|io_int_handler
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|struct|_lowcore
r_struct
id|_lowcore
(brace
macro_line|#ifndef __s390x__
multiline_comment|/* prefix area: defined by architecture */
DECL|member|restart_psw
id|psw_t
id|restart_psw
suffix:semicolon
multiline_comment|/* 0x000 */
DECL|member|ccw2
id|__u32
id|ccw2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x008 */
DECL|member|external_old_psw
id|psw_t
id|external_old_psw
suffix:semicolon
multiline_comment|/* 0x018 */
DECL|member|svc_old_psw
id|psw_t
id|svc_old_psw
suffix:semicolon
multiline_comment|/* 0x020 */
DECL|member|program_old_psw
id|psw_t
id|program_old_psw
suffix:semicolon
multiline_comment|/* 0x028 */
DECL|member|mcck_old_psw
id|psw_t
id|mcck_old_psw
suffix:semicolon
multiline_comment|/* 0x030 */
DECL|member|io_old_psw
id|psw_t
id|io_old_psw
suffix:semicolon
multiline_comment|/* 0x038 */
DECL|member|pad1
id|__u8
id|pad1
(braket
l_int|0x58
op_minus
l_int|0x40
)braket
suffix:semicolon
multiline_comment|/* 0x040 */
DECL|member|external_new_psw
id|psw_t
id|external_new_psw
suffix:semicolon
multiline_comment|/* 0x058 */
DECL|member|svc_new_psw
id|psw_t
id|svc_new_psw
suffix:semicolon
multiline_comment|/* 0x060 */
DECL|member|program_new_psw
id|psw_t
id|program_new_psw
suffix:semicolon
multiline_comment|/* 0x068 */
DECL|member|mcck_new_psw
id|psw_t
id|mcck_new_psw
suffix:semicolon
multiline_comment|/* 0x070 */
DECL|member|io_new_psw
id|psw_t
id|io_new_psw
suffix:semicolon
multiline_comment|/* 0x078 */
DECL|member|ext_params
id|__u32
id|ext_params
suffix:semicolon
multiline_comment|/* 0x080 */
DECL|member|cpu_addr
id|__u16
id|cpu_addr
suffix:semicolon
multiline_comment|/* 0x084 */
DECL|member|ext_int_code
id|__u16
id|ext_int_code
suffix:semicolon
multiline_comment|/* 0x086 */
DECL|member|svc_ilc
id|__u16
id|svc_ilc
suffix:semicolon
multiline_comment|/* 0x088 */
DECL|member|svc_code
id|__u16
id|svc_code
suffix:semicolon
multiline_comment|/* 0x08a */
DECL|member|pgm_ilc
id|__u16
id|pgm_ilc
suffix:semicolon
multiline_comment|/* 0x08c */
DECL|member|pgm_code
id|__u16
id|pgm_code
suffix:semicolon
multiline_comment|/* 0x08e */
DECL|member|trans_exc_code
id|__u32
id|trans_exc_code
suffix:semicolon
multiline_comment|/* 0x090 */
DECL|member|mon_class_num
id|__u16
id|mon_class_num
suffix:semicolon
multiline_comment|/* 0x094 */
DECL|member|per_perc_atmid
id|__u16
id|per_perc_atmid
suffix:semicolon
multiline_comment|/* 0x096 */
DECL|member|per_address
id|__u32
id|per_address
suffix:semicolon
multiline_comment|/* 0x098 */
DECL|member|monitor_code
id|__u32
id|monitor_code
suffix:semicolon
multiline_comment|/* 0x09c */
DECL|member|exc_access_id
id|__u8
id|exc_access_id
suffix:semicolon
multiline_comment|/* 0x0a0 */
DECL|member|per_access_id
id|__u8
id|per_access_id
suffix:semicolon
multiline_comment|/* 0x0a1 */
DECL|member|pad2
id|__u8
id|pad2
(braket
l_int|0xB8
op_minus
l_int|0xA2
)braket
suffix:semicolon
multiline_comment|/* 0x0a2 */
DECL|member|subchannel_id
id|__u16
id|subchannel_id
suffix:semicolon
multiline_comment|/* 0x0b8 */
DECL|member|subchannel_nr
id|__u16
id|subchannel_nr
suffix:semicolon
multiline_comment|/* 0x0ba */
DECL|member|io_int_parm
id|__u32
id|io_int_parm
suffix:semicolon
multiline_comment|/* 0x0bc */
DECL|member|io_int_word
id|__u32
id|io_int_word
suffix:semicolon
multiline_comment|/* 0x0c0 */
DECL|member|pad3
id|__u8
id|pad3
(braket
l_int|0xD8
op_minus
l_int|0xC4
)braket
suffix:semicolon
multiline_comment|/* 0x0c4 */
DECL|member|cpu_timer_save_area
id|__u32
id|cpu_timer_save_area
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x0d8 */
DECL|member|clock_comp_save_area
id|__u32
id|clock_comp_save_area
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x0e0 */
DECL|member|mcck_interruption_code
id|__u32
id|mcck_interruption_code
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x0e8 */
DECL|member|pad4
id|__u8
id|pad4
(braket
l_int|0xf4
op_minus
l_int|0xf0
)braket
suffix:semicolon
multiline_comment|/* 0x0f0 */
DECL|member|external_damage_code
id|__u32
id|external_damage_code
suffix:semicolon
multiline_comment|/* 0x0f4 */
DECL|member|failing_storage_address
id|__u32
id|failing_storage_address
suffix:semicolon
multiline_comment|/* 0x0f8 */
DECL|member|pad5
id|__u8
id|pad5
(braket
l_int|0x100
op_minus
l_int|0xfc
)braket
suffix:semicolon
multiline_comment|/* 0x0fc */
DECL|member|st_status_fixed_logout
id|__u32
id|st_status_fixed_logout
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x100 */
DECL|member|pad6
id|__u8
id|pad6
(braket
l_int|0x120
op_minus
l_int|0x110
)braket
suffix:semicolon
multiline_comment|/* 0x110 */
DECL|member|access_regs_save_area
id|__u32
id|access_regs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x120 */
DECL|member|floating_pt_save_area
id|__u32
id|floating_pt_save_area
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x160 */
DECL|member|gpregs_save_area
id|__u32
id|gpregs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x180 */
DECL|member|cregs_save_area
id|__u32
id|cregs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1c0 */
DECL|member|return_psw
id|psw_t
id|return_psw
suffix:semicolon
multiline_comment|/* 0x200 */
DECL|member|irb
id|__u8
id|irb
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* 0x208 */
DECL|member|sync_enter_timer
id|__u64
id|sync_enter_timer
suffix:semicolon
multiline_comment|/* 0x248 */
DECL|member|async_enter_timer
id|__u64
id|async_enter_timer
suffix:semicolon
multiline_comment|/* 0x250 */
DECL|member|exit_timer
id|__u64
id|exit_timer
suffix:semicolon
multiline_comment|/* 0x258 */
DECL|member|last_update_timer
id|__u64
id|last_update_timer
suffix:semicolon
multiline_comment|/* 0x260 */
DECL|member|user_timer
id|__u64
id|user_timer
suffix:semicolon
multiline_comment|/* 0x268 */
DECL|member|system_timer
id|__u64
id|system_timer
suffix:semicolon
multiline_comment|/* 0x270 */
DECL|member|last_update_clock
id|__u64
id|last_update_clock
suffix:semicolon
multiline_comment|/* 0x278 */
DECL|member|steal_clock
id|__u64
id|steal_clock
suffix:semicolon
multiline_comment|/* 0x280 */
DECL|member|pad8
id|__u8
id|pad8
(braket
l_int|0xc00
op_minus
l_int|0x288
)braket
suffix:semicolon
multiline_comment|/* 0x288 */
multiline_comment|/* System info area */
DECL|member|save_area
id|__u32
id|save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0xc00 */
DECL|member|kernel_stack
id|__u32
id|kernel_stack
suffix:semicolon
multiline_comment|/* 0xc40 */
DECL|member|thread_info
id|__u32
id|thread_info
suffix:semicolon
multiline_comment|/* 0xc44 */
DECL|member|async_stack
id|__u32
id|async_stack
suffix:semicolon
multiline_comment|/* 0xc48 */
DECL|member|kernel_asce
id|__u32
id|kernel_asce
suffix:semicolon
multiline_comment|/* 0xc4c */
DECL|member|user_asce
id|__u32
id|user_asce
suffix:semicolon
multiline_comment|/* 0xc50 */
DECL|member|panic_stack
id|__u32
id|panic_stack
suffix:semicolon
multiline_comment|/* 0xc54 */
DECL|member|pad10
id|__u8
id|pad10
(braket
l_int|0xc60
op_minus
l_int|0xc58
)braket
suffix:semicolon
multiline_comment|/* 0xc58 */
multiline_comment|/* entry.S sensitive area start */
DECL|member|cpu_data
r_struct
id|cpuinfo_S390
id|cpu_data
suffix:semicolon
multiline_comment|/* 0xc60 */
DECL|member|ipl_device
id|__u32
id|ipl_device
suffix:semicolon
multiline_comment|/* 0xc7c */
multiline_comment|/* entry.S sensitive area end */
multiline_comment|/* SMP info area: defined by DJB */
DECL|member|jiffy_timer
id|__u64
id|jiffy_timer
suffix:semicolon
multiline_comment|/* 0xc80 */
DECL|member|ext_call_fast
id|__u32
id|ext_call_fast
suffix:semicolon
multiline_comment|/* 0xc88 */
DECL|member|percpu_offset
id|__u32
id|percpu_offset
suffix:semicolon
multiline_comment|/* 0xc8c */
DECL|member|current_task
id|__u32
id|current_task
suffix:semicolon
multiline_comment|/* 0xc90 */
DECL|member|softirq_pending
id|__u32
id|softirq_pending
suffix:semicolon
multiline_comment|/* 0xc94 */
DECL|member|int_clock
id|__u64
id|int_clock
suffix:semicolon
multiline_comment|/* 0xc98 */
DECL|member|pad11
id|__u8
id|pad11
(braket
l_int|0xe00
op_minus
l_int|0xca0
)braket
suffix:semicolon
multiline_comment|/* 0xca0 */
multiline_comment|/* 0xe00 is used as indicator for dump tools */
multiline_comment|/* whether the kernel died with panic() or not */
DECL|member|panic_magic
id|__u32
id|panic_magic
suffix:semicolon
multiline_comment|/* 0xe00 */
multiline_comment|/* Align to the top 1k of prefix area */
DECL|member|pad12
id|__u8
id|pad12
(braket
l_int|0x1000
op_minus
l_int|0xe04
)braket
suffix:semicolon
multiline_comment|/* 0xe04 */
macro_line|#else /* !__s390x__ */
multiline_comment|/* prefix area: defined by architecture */
id|__u32
id|ccw1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x000 */
id|__u32
id|ccw2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x008 */
id|__u8
id|pad1
(braket
l_int|0x80
op_minus
l_int|0x18
)braket
suffix:semicolon
multiline_comment|/* 0x018 */
id|__u32
id|ext_params
suffix:semicolon
multiline_comment|/* 0x080 */
id|__u16
id|cpu_addr
suffix:semicolon
multiline_comment|/* 0x084 */
id|__u16
id|ext_int_code
suffix:semicolon
multiline_comment|/* 0x086 */
id|__u16
id|svc_ilc
suffix:semicolon
multiline_comment|/* 0x088 */
id|__u16
id|svc_code
suffix:semicolon
multiline_comment|/* 0x08a */
id|__u16
id|pgm_ilc
suffix:semicolon
multiline_comment|/* 0x08c */
id|__u16
id|pgm_code
suffix:semicolon
multiline_comment|/* 0x08e */
id|__u32
id|data_exc_code
suffix:semicolon
multiline_comment|/* 0x090 */
id|__u16
id|mon_class_num
suffix:semicolon
multiline_comment|/* 0x094 */
id|__u16
id|per_perc_atmid
suffix:semicolon
multiline_comment|/* 0x096 */
id|addr_t
id|per_address
suffix:semicolon
multiline_comment|/* 0x098 */
id|__u8
id|exc_access_id
suffix:semicolon
multiline_comment|/* 0x0a0 */
id|__u8
id|per_access_id
suffix:semicolon
multiline_comment|/* 0x0a1 */
id|__u8
id|op_access_id
suffix:semicolon
multiline_comment|/* 0x0a2 */
id|__u8
id|ar_access_id
suffix:semicolon
multiline_comment|/* 0x0a3 */
id|__u8
id|pad2
(braket
l_int|0xA8
op_minus
l_int|0xA4
)braket
suffix:semicolon
multiline_comment|/* 0x0a4 */
id|addr_t
id|trans_exc_code
suffix:semicolon
multiline_comment|/* 0x0A0 */
id|addr_t
id|monitor_code
suffix:semicolon
multiline_comment|/* 0x09c */
id|__u16
id|subchannel_id
suffix:semicolon
multiline_comment|/* 0x0b8 */
id|__u16
id|subchannel_nr
suffix:semicolon
multiline_comment|/* 0x0ba */
id|__u32
id|io_int_parm
suffix:semicolon
multiline_comment|/* 0x0bc */
id|__u32
id|io_int_word
suffix:semicolon
multiline_comment|/* 0x0c0 */
id|__u8
id|pad3
(braket
l_int|0xc8
op_minus
l_int|0xc4
)braket
suffix:semicolon
multiline_comment|/* 0x0c4 */
id|__u32
id|stfl_fac_list
suffix:semicolon
multiline_comment|/* 0x0c8 */
id|__u8
id|pad4
(braket
l_int|0xe8
op_minus
l_int|0xcc
)braket
suffix:semicolon
multiline_comment|/* 0x0cc */
id|__u32
id|mcck_interruption_code
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x0e8 */
id|__u8
id|pad5
(braket
l_int|0xf4
op_minus
l_int|0xf0
)braket
suffix:semicolon
multiline_comment|/* 0x0f0 */
id|__u32
id|external_damage_code
suffix:semicolon
multiline_comment|/* 0x0f4 */
id|addr_t
id|failing_storage_address
suffix:semicolon
multiline_comment|/* 0x0f8 */
id|__u8
id|pad6
(braket
l_int|0x120
op_minus
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* 0x100 */
id|psw_t
id|restart_old_psw
suffix:semicolon
multiline_comment|/* 0x120 */
id|psw_t
id|external_old_psw
suffix:semicolon
multiline_comment|/* 0x130 */
id|psw_t
id|svc_old_psw
suffix:semicolon
multiline_comment|/* 0x140 */
id|psw_t
id|program_old_psw
suffix:semicolon
multiline_comment|/* 0x150 */
id|psw_t
id|mcck_old_psw
suffix:semicolon
multiline_comment|/* 0x160 */
id|psw_t
id|io_old_psw
suffix:semicolon
multiline_comment|/* 0x170 */
id|__u8
id|pad7
(braket
l_int|0x1a0
op_minus
l_int|0x180
)braket
suffix:semicolon
multiline_comment|/* 0x180 */
id|psw_t
id|restart_psw
suffix:semicolon
multiline_comment|/* 0x1a0 */
id|psw_t
id|external_new_psw
suffix:semicolon
multiline_comment|/* 0x1b0 */
id|psw_t
id|svc_new_psw
suffix:semicolon
multiline_comment|/* 0x1c0 */
id|psw_t
id|program_new_psw
suffix:semicolon
multiline_comment|/* 0x1d0 */
id|psw_t
id|mcck_new_psw
suffix:semicolon
multiline_comment|/* 0x1e0 */
id|psw_t
id|io_new_psw
suffix:semicolon
multiline_comment|/* 0x1f0 */
id|psw_t
id|return_psw
suffix:semicolon
multiline_comment|/* 0x200 */
id|__u8
id|irb
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* 0x210 */
id|__u64
id|sync_enter_timer
suffix:semicolon
multiline_comment|/* 0x250 */
id|__u64
id|async_enter_timer
suffix:semicolon
multiline_comment|/* 0x258 */
id|__u64
id|exit_timer
suffix:semicolon
multiline_comment|/* 0x260 */
id|__u64
id|last_update_timer
suffix:semicolon
multiline_comment|/* 0x268 */
id|__u64
id|user_timer
suffix:semicolon
multiline_comment|/* 0x270 */
id|__u64
id|system_timer
suffix:semicolon
multiline_comment|/* 0x278 */
id|__u64
id|last_update_clock
suffix:semicolon
multiline_comment|/* 0x280 */
id|__u64
id|steal_clock
suffix:semicolon
multiline_comment|/* 0x288 */
id|__u32
id|diag44_opcode
suffix:semicolon
multiline_comment|/* 0x290 */
id|__u8
id|pad8
(braket
l_int|0xc00
op_minus
l_int|0x294
)braket
suffix:semicolon
multiline_comment|/* 0x294 */
multiline_comment|/* System info area */
id|__u64
id|save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0xc00 */
id|__u8
id|pad9
(braket
l_int|0xd40
op_minus
l_int|0xc80
)braket
suffix:semicolon
multiline_comment|/* 0xc80 */
id|__u64
id|kernel_stack
suffix:semicolon
multiline_comment|/* 0xd40 */
id|__u64
id|thread_info
suffix:semicolon
multiline_comment|/* 0xd48 */
id|__u64
id|async_stack
suffix:semicolon
multiline_comment|/* 0xd50 */
id|__u64
id|kernel_asce
suffix:semicolon
multiline_comment|/* 0xd58 */
id|__u64
id|user_asce
suffix:semicolon
multiline_comment|/* 0xd60 */
id|__u64
id|panic_stack
suffix:semicolon
multiline_comment|/* 0xd68 */
id|__u8
id|pad10
(braket
l_int|0xd80
op_minus
l_int|0xd70
)braket
suffix:semicolon
multiline_comment|/* 0xd70 */
multiline_comment|/* entry.S sensitive area start */
r_struct
id|cpuinfo_S390
id|cpu_data
suffix:semicolon
multiline_comment|/* 0xd80 */
id|__u32
id|ipl_device
suffix:semicolon
multiline_comment|/* 0xdb8 */
id|__u32
id|pad11
suffix:semicolon
multiline_comment|/* 0xdbc */
multiline_comment|/* entry.S sensitive area end */
multiline_comment|/* SMP info area: defined by DJB */
id|__u64
id|jiffy_timer
suffix:semicolon
multiline_comment|/* 0xdc0 */
id|__u64
id|ext_call_fast
suffix:semicolon
multiline_comment|/* 0xdc8 */
id|__u64
id|percpu_offset
suffix:semicolon
multiline_comment|/* 0xdd0 */
id|__u64
id|current_task
suffix:semicolon
multiline_comment|/* 0xdd8 */
id|__u64
id|softirq_pending
suffix:semicolon
multiline_comment|/* 0xde0 */
id|__u64
id|int_clock
suffix:semicolon
multiline_comment|/* 0xde8 */
id|__u8
id|pad12
(braket
l_int|0xe00
op_minus
l_int|0xdf0
)braket
suffix:semicolon
multiline_comment|/* 0xdf0 */
multiline_comment|/* 0xe00 is used as indicator for dump tools */
multiline_comment|/* whether the kernel died with panic() or not */
id|__u32
id|panic_magic
suffix:semicolon
multiline_comment|/* 0xe00 */
id|__u8
id|pad13
(braket
l_int|0x1200
op_minus
l_int|0xe04
)braket
suffix:semicolon
multiline_comment|/* 0xe04 */
multiline_comment|/* System info area */
id|__u64
id|floating_pt_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1200 */
id|__u64
id|gpregs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1280 */
id|__u32
id|st_status_fixed_logout
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x1300 */
id|__u8
id|pad14
(braket
l_int|0x1318
op_minus
l_int|0x1310
)braket
suffix:semicolon
multiline_comment|/* 0x1310 */
id|__u32
id|prefixreg_save_area
suffix:semicolon
multiline_comment|/* 0x1318 */
id|__u32
id|fpt_creg_save_area
suffix:semicolon
multiline_comment|/* 0x131c */
id|__u8
id|pad15
(braket
l_int|0x1324
op_minus
l_int|0x1320
)braket
suffix:semicolon
multiline_comment|/* 0x1320 */
id|__u32
id|tod_progreg_save_area
suffix:semicolon
multiline_comment|/* 0x1324 */
id|__u32
id|cpu_timer_save_area
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x1328 */
id|__u32
id|clock_comp_save_area
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x1330 */
id|__u8
id|pad16
(braket
l_int|0x1340
op_minus
l_int|0x1338
)braket
suffix:semicolon
multiline_comment|/* 0x1338 */
id|__u32
id|access_regs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1340 */
id|__u64
id|cregs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1380 */
multiline_comment|/* align to the top of the prefix area */
id|__u8
id|pad17
(braket
l_int|0x2000
op_minus
l_int|0x1400
)braket
suffix:semicolon
multiline_comment|/* 0x1400 */
macro_line|#endif /* !__s390x__ */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* End structure*/
DECL|macro|S390_lowcore
mdefine_line|#define S390_lowcore (*((struct _lowcore *) 0))
r_extern
r_struct
id|_lowcore
op_star
id|lowcore_ptr
(braket
)braket
suffix:semicolon
DECL|function|set_prefix
r_extern
id|__inline__
r_void
id|set_prefix
c_func
(paren
id|__u32
id|address
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;spx %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|address
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__PANIC_MAGIC
mdefine_line|#define __PANIC_MAGIC           0xDEADC0DE
macro_line|#endif
macro_line|#endif
eof
