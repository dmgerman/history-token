multiline_comment|/*&n; *  include/asm-s390/lowcore.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hpenner@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; */
macro_line|#ifndef _ASM_S390_LOWCORE_H
DECL|macro|_ASM_S390_LOWCORE_H
mdefine_line|#define _ASM_S390_LOWCORE_H
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
DECL|macro|__LC_RETURN_PSW
mdefine_line|#define __LC_RETURN_PSW                 0x0200
DECL|macro|__LC_SYNC_IO_WORD
mdefine_line|#define __LC_SYNC_IO_WORD               0x0210
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
DECL|macro|__LC_TRANS_EXC_ADDR
mdefine_line|#define __LC_TRANS_EXC_ADDR             0x0a8
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
DECL|macro|__LC_SAVE_AREA
mdefine_line|#define __LC_SAVE_AREA                  0xC00
DECL|macro|__LC_KERNEL_STACK
mdefine_line|#define __LC_KERNEL_STACK               0xD40
DECL|macro|__LC_ASYNC_STACK
mdefine_line|#define __LC_ASYNC_STACK                0xD48
DECL|macro|__LC_CPUID
mdefine_line|#define __LC_CPUID                      0xD90
DECL|macro|__LC_CPUADDR
mdefine_line|#define __LC_CPUADDR                    0xD98
DECL|macro|__LC_IPLDEV
mdefine_line|#define __LC_IPLDEV                     0xDB8
DECL|macro|__LC_JIFFY_TIMER
mdefine_line|#define __LC_JIFFY_TIMER&t;&t;0xDC0
DECL|macro|__LC_PANIC_MAGIC
mdefine_line|#define __LC_PANIC_MAGIC                0xE00
DECL|macro|__LC_AREGS_SAVE_AREA
mdefine_line|#define __LC_AREGS_SAVE_AREA            0x1340
DECL|macro|__LC_CREGS_SAVE_AREA
mdefine_line|#define __LC_CREGS_SAVE_AREA            0x1380
DECL|macro|__LC_PFAULT_INTPARM
mdefine_line|#define __LC_PFAULT_INTPARM             0x11B8
multiline_comment|/* interrupt handler start with all io, external and mcck interrupt disabled */
DECL|macro|_RESTART_PSW_MASK
mdefine_line|#define _RESTART_PSW_MASK    0x0000000180000000
DECL|macro|_EXT_PSW_MASK
mdefine_line|#define _EXT_PSW_MASK        0x0400000180000000
DECL|macro|_PGM_PSW_MASK
mdefine_line|#define _PGM_PSW_MASK        0x0400000180000000
DECL|macro|_SVC_PSW_MASK
mdefine_line|#define _SVC_PSW_MASK        0x0400000180000000
DECL|macro|_MCCK_PSW_MASK
mdefine_line|#define _MCCK_PSW_MASK       0x0400000180000000
DECL|macro|_IO_PSW_MASK
mdefine_line|#define _IO_PSW_MASK         0x0400000180000000
DECL|macro|_USER_PSW_MASK
mdefine_line|#define _USER_PSW_MASK       0x0705C00180000000
DECL|macro|_WAIT_PSW_MASK
mdefine_line|#define _WAIT_PSW_MASK       0x0706000180000000
DECL|macro|_DW_PSW_MASK
mdefine_line|#define _DW_PSW_MASK         0x0002000180000000
DECL|macro|_PRIMARY_MASK
mdefine_line|#define _PRIMARY_MASK        0x0000    /* MASK for SACF                    */
DECL|macro|_SECONDARY_MASK
mdefine_line|#define _SECONDARY_MASK      0x0100    /* MASK for SACF                    */
DECL|macro|_ACCESS_MASK
mdefine_line|#define _ACCESS_MASK         0x0200    /* MASK for SACF                    */
DECL|macro|_HOME_MASK
mdefine_line|#define _HOME_MASK           0x0300    /* MASK for SACF                    */
DECL|macro|_PSW_PRIM_SPACE_MODE
mdefine_line|#define _PSW_PRIM_SPACE_MODE 0x0000000000000000
DECL|macro|_PSW_SEC_SPACE_MODE
mdefine_line|#define _PSW_SEC_SPACE_MODE  0x0000800000000000
DECL|macro|_PSW_ACC_REG_MODE
mdefine_line|#define _PSW_ACC_REG_MODE    0x0000400000000000
DECL|macro|_PSW_HOME_SPACE_MODE
mdefine_line|#define _PSW_HOME_SPACE_MODE 0x0000C00000000000
DECL|macro|_PSW_WAIT_MASK_BIT
mdefine_line|#define _PSW_WAIT_MASK_BIT   0x0002000000000000
DECL|macro|_PSW_IO_MASK_BIT
mdefine_line|#define _PSW_IO_MASK_BIT     0x0200000000000000
DECL|macro|_PSW_IO_WAIT
mdefine_line|#define _PSW_IO_WAIT         0x0202000000000000
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
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
DECL|member|ccw1
id|__u32
id|ccw1
(braket
l_int|2
)braket
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
DECL|member|pad1
id|__u8
id|pad1
(braket
l_int|0x80
op_minus
l_int|0x18
)braket
suffix:semicolon
multiline_comment|/* 0x018 */
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
DECL|member|data_exc_code
id|__u32
id|data_exc_code
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
id|addr_t
id|per_address
suffix:semicolon
multiline_comment|/* 0x098 */
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
DECL|member|op_access_id
id|__u8
id|op_access_id
suffix:semicolon
multiline_comment|/* 0x0a2 */
DECL|member|ar_access_id
id|__u8
id|ar_access_id
suffix:semicolon
multiline_comment|/* 0x0a3 */
DECL|member|pad2
id|__u8
id|pad2
(braket
l_int|0xA8
op_minus
l_int|0xA4
)braket
suffix:semicolon
multiline_comment|/* 0x0a4 */
DECL|member|trans_exc_code
id|addr_t
id|trans_exc_code
suffix:semicolon
multiline_comment|/* 0x0A0 */
DECL|member|monitor_code
id|addr_t
id|monitor_code
suffix:semicolon
multiline_comment|/* 0x09c */
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
l_int|0xc8
op_minus
l_int|0xc4
)braket
suffix:semicolon
multiline_comment|/* 0x0c4 */
DECL|member|stfl_fac_list
id|__u32
id|stfl_fac_list
suffix:semicolon
multiline_comment|/* 0x0c8 */
DECL|member|pad4
id|__u8
id|pad4
(braket
l_int|0xe8
op_minus
l_int|0xcc
)braket
suffix:semicolon
multiline_comment|/* 0x0cc */
DECL|member|mcck_interruption_code
id|__u32
id|mcck_interruption_code
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x0e8 */
DECL|member|pad5
id|__u8
id|pad5
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
id|addr_t
id|failing_storage_address
suffix:semicolon
multiline_comment|/* 0x0f8 */
DECL|member|pad6
id|__u8
id|pad6
(braket
l_int|0x120
op_minus
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* 0x100 */
DECL|member|restart_old_psw
id|psw_t
id|restart_old_psw
suffix:semicolon
multiline_comment|/* 0x120 */
DECL|member|external_old_psw
id|psw_t
id|external_old_psw
suffix:semicolon
multiline_comment|/* 0x130 */
DECL|member|svc_old_psw
id|psw_t
id|svc_old_psw
suffix:semicolon
multiline_comment|/* 0x140 */
DECL|member|program_old_psw
id|psw_t
id|program_old_psw
suffix:semicolon
multiline_comment|/* 0x150 */
DECL|member|mcck_old_psw
id|psw_t
id|mcck_old_psw
suffix:semicolon
multiline_comment|/* 0x160 */
DECL|member|io_old_psw
id|psw_t
id|io_old_psw
suffix:semicolon
multiline_comment|/* 0x170 */
DECL|member|pad7
id|__u8
id|pad7
(braket
l_int|0x1a0
op_minus
l_int|0x180
)braket
suffix:semicolon
multiline_comment|/* 0x180 */
DECL|member|restart_psw
id|psw_t
id|restart_psw
suffix:semicolon
multiline_comment|/* 0x1a0 */
DECL|member|external_new_psw
id|psw_t
id|external_new_psw
suffix:semicolon
multiline_comment|/* 0x1b0 */
DECL|member|svc_new_psw
id|psw_t
id|svc_new_psw
suffix:semicolon
multiline_comment|/* 0x1c0 */
DECL|member|program_new_psw
id|psw_t
id|program_new_psw
suffix:semicolon
multiline_comment|/* 0x1d0 */
DECL|member|mcck_new_psw
id|psw_t
id|mcck_new_psw
suffix:semicolon
multiline_comment|/* 0x1e0 */
DECL|member|io_new_psw
id|psw_t
id|io_new_psw
suffix:semicolon
multiline_comment|/* 0x1f0 */
DECL|member|return_psw
id|psw_t
id|return_psw
suffix:semicolon
multiline_comment|/* 0x200 */
DECL|member|sync_io_word
id|__u32
id|sync_io_word
suffix:semicolon
multiline_comment|/* 0x210 */
DECL|member|pad8
id|__u8
id|pad8
(braket
l_int|0xc00
op_minus
l_int|0x214
)braket
suffix:semicolon
multiline_comment|/* 0x214 */
multiline_comment|/* System info area */
DECL|member|save_area
id|__u64
id|save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0xc00 */
DECL|member|pad9
id|__u8
id|pad9
(braket
l_int|0xd40
op_minus
l_int|0xc80
)braket
suffix:semicolon
multiline_comment|/* 0xc80 */
DECL|member|kernel_stack
id|__u64
id|kernel_stack
suffix:semicolon
multiline_comment|/* 0xd40 */
DECL|member|async_stack
id|__u64
id|async_stack
suffix:semicolon
multiline_comment|/* 0xd48 */
multiline_comment|/* entry.S sensitive area start */
DECL|member|pad10
id|__u8
id|pad10
(braket
l_int|0xd80
op_minus
l_int|0xd50
)braket
suffix:semicolon
multiline_comment|/* 0xd64 */
DECL|member|cpu_data
r_struct
id|cpuinfo_S390
id|cpu_data
suffix:semicolon
multiline_comment|/* 0xd80 */
DECL|member|ipl_device
id|__u32
id|ipl_device
suffix:semicolon
multiline_comment|/* 0xdb8 */
DECL|member|pad11
id|__u32
id|pad11
suffix:semicolon
multiline_comment|/* 0xdbc was lsw word of ipl_device until a bug was found DJB */
multiline_comment|/* entry.S sensitive area end */
multiline_comment|/* SMP info area: defined by DJB */
DECL|member|jiffy_timer
id|__u64
id|jiffy_timer
suffix:semicolon
multiline_comment|/* 0xdc0 */
DECL|member|ext_call_fast
id|__u64
id|ext_call_fast
suffix:semicolon
multiline_comment|/* 0xdc8 */
DECL|member|pad12
id|__u8
id|pad12
(braket
l_int|0xe00
op_minus
l_int|0xdd0
)braket
suffix:semicolon
multiline_comment|/* 0xdd0 */
multiline_comment|/* 0xe00 is used as indicator for dump tools */
multiline_comment|/* whether the kernel died with panic() or not */
DECL|member|panic_magic
id|__u32
id|panic_magic
suffix:semicolon
multiline_comment|/* 0xe00 */
DECL|member|pad13
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
DECL|member|floating_pt_save_area
id|__u64
id|floating_pt_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1200 */
DECL|member|gpregs_save_area
id|__u64
id|gpregs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1280 */
DECL|member|st_status_fixed_logout
id|__u32
id|st_status_fixed_logout
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x1300 */
DECL|member|pad14
id|__u8
id|pad14
(braket
l_int|0x1318
op_minus
l_int|0x1310
)braket
suffix:semicolon
multiline_comment|/* 0x1310 */
DECL|member|prefixreg_save_area
id|__u32
id|prefixreg_save_area
suffix:semicolon
multiline_comment|/* 0x1318 */
DECL|member|fpt_creg_save_area
id|__u32
id|fpt_creg_save_area
suffix:semicolon
multiline_comment|/* 0x131c */
DECL|member|pad15
id|__u8
id|pad15
(braket
l_int|0x1324
op_minus
l_int|0x1320
)braket
suffix:semicolon
multiline_comment|/* 0x1320 */
DECL|member|tod_progreg_save_area
id|__u32
id|tod_progreg_save_area
suffix:semicolon
multiline_comment|/* 0x1324 */
DECL|member|cpu_timer_save_area
id|__u32
id|cpu_timer_save_area
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x1328 */
DECL|member|clock_comp_save_area
id|__u32
id|clock_comp_save_area
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x1330 */
DECL|member|pad16
id|__u8
id|pad16
(braket
l_int|0x1340
op_minus
l_int|0x1338
)braket
suffix:semicolon
multiline_comment|/* 0x1338 */
DECL|member|access_regs_save_area
id|__u32
id|access_regs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1340 */
DECL|member|cregs_save_area
id|__u64
id|cregs_save_area
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x1380 */
multiline_comment|/* align to the top of the prefix area */
DECL|member|pad17
id|__u8
id|pad17
(braket
l_int|0x2000
op_minus
l_int|0x1400
)braket
suffix:semicolon
multiline_comment|/* 0x1400 */
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
macro_line|#ifndef CONFIG_SMP
DECL|macro|get_cpu_lowcore
mdefine_line|#define get_cpu_lowcore(cpu)      (&amp;S390_lowcore)
DECL|macro|safe_get_cpu_lowcore
mdefine_line|#define safe_get_cpu_lowcore(cpu) (&amp;S390_lowcore)
macro_line|#else
DECL|macro|get_cpu_lowcore
mdefine_line|#define get_cpu_lowcore(cpu)      (lowcore_ptr[(cpu)])
DECL|macro|safe_get_cpu_lowcore
mdefine_line|#define safe_get_cpu_lowcore(cpu) &bslash;&n;        ((cpu) == smp_processor_id() ? &amp;S390_lowcore : lowcore_ptr[(cpu)])
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|__PANIC_MAGIC
mdefine_line|#define __PANIC_MAGIC           0xDEADC0DE
macro_line|#endif
eof
