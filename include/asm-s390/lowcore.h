multiline_comment|/*&n; *  include/asm-s390/lowcore.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; */
macro_line|#ifndef _ASM_S390_LOWCORE_H
DECL|macro|_ASM_S390_LOWCORE_H
mdefine_line|#define _ASM_S390_LOWCORE_H
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
DECL|macro|__LC_EXT_PARAMS
mdefine_line|#define __LC_EXT_PARAMS                 0x080
DECL|macro|__LC_CPU_ADDRESS
mdefine_line|#define __LC_CPU_ADDRESS                0x084
DECL|macro|__LC_EXT_INT_CODE
mdefine_line|#define __LC_EXT_INT_CODE               0x086
DECL|macro|__LC_SVC_INT_CODE
mdefine_line|#define __LC_SVC_INT_CODE               0x08B
DECL|macro|__LC_PGM_ILC
mdefine_line|#define __LC_PGM_ILC                    0x08C
DECL|macro|__LC_PGM_INT_CODE
mdefine_line|#define __LC_PGM_INT_CODE               0x08E
DECL|macro|__LC_TRANS_EXC_ADDR
mdefine_line|#define __LC_TRANS_EXC_ADDR             0x090
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
DECL|macro|__LC_AREGS_SAVE_AREA
mdefine_line|#define __LC_AREGS_SAVE_AREA            0x120
DECL|macro|__LC_CREGS_SAVE_AREA
mdefine_line|#define __LC_CREGS_SAVE_AREA            0x1C0
DECL|macro|__LC_RETURN_PSW
mdefine_line|#define __LC_RETURN_PSW                 0x200
DECL|macro|__LC_SYNC_IO_WORD
mdefine_line|#define __LC_SYNC_IO_WORD               0x400
DECL|macro|__LC_SAVE_AREA
mdefine_line|#define __LC_SAVE_AREA                  0xC00
DECL|macro|__LC_KERNEL_STACK
mdefine_line|#define __LC_KERNEL_STACK               0xC40
DECL|macro|__LC_ASYNC_STACK
mdefine_line|#define __LC_ASYNC_STACK                0xC44
DECL|macro|__LC_CPUID
mdefine_line|#define __LC_CPUID                      0xC60
DECL|macro|__LC_CPUADDR
mdefine_line|#define __LC_CPUADDR                    0xC68
DECL|macro|__LC_IPLDEV
mdefine_line|#define __LC_IPLDEV                     0xC7C
DECL|macro|__LC_JIFFY_TIMER
mdefine_line|#define __LC_JIFFY_TIMER&t;&t;0xC80
DECL|macro|__LC_PANIC_MAGIC
mdefine_line|#define __LC_PANIC_MAGIC                0xE00
DECL|macro|__LC_PFAULT_INTPARM
mdefine_line|#define __LC_PFAULT_INTPARM             0x080
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
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
multiline_comment|/* 0x240 */
DECL|member|return_psw
id|psw_t
id|return_psw
suffix:semicolon
multiline_comment|/* 0x200 */
DECL|member|pad8
id|__u8
id|pad8
(braket
l_int|0x400
op_minus
l_int|0x208
)braket
suffix:semicolon
multiline_comment|/* 0x208 */
DECL|member|sync_io_word
id|__u32
id|sync_io_word
suffix:semicolon
multiline_comment|/* 0x400 */
DECL|member|pad9
id|__u8
id|pad9
(braket
l_int|0xc00
op_minus
l_int|0x404
)braket
suffix:semicolon
multiline_comment|/* 0x404 */
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
DECL|member|async_stack
id|__u32
id|async_stack
suffix:semicolon
multiline_comment|/* 0xc44 */
multiline_comment|/* entry.S sensitive area start */
DECL|member|pad10
id|__u8
id|pad10
(braket
l_int|0xc60
op_minus
l_int|0xc48
)braket
suffix:semicolon
multiline_comment|/* 0xc5c */
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
id|atomic_t
id|ext_call_fast
suffix:semicolon
multiline_comment|/* 0xc88 */
DECL|member|pad11
id|__u8
id|pad11
(braket
l_int|0xe00
op_minus
l_int|0xc8c
)braket
suffix:semicolon
multiline_comment|/* 0xc8c */
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
