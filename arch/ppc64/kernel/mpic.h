macro_line|#include &lt;linux/irq.h&gt;
multiline_comment|/*&n; * Global registers&n; */
DECL|macro|MPIC_GREG_BASE
mdefine_line|#define MPIC_GREG_BASE&t;&t;&t;0x01000
DECL|macro|MPIC_GREG_FEATURE_0
mdefine_line|#define MPIC_GREG_FEATURE_0&t;&t;0x00000
DECL|macro|MPIC_GREG_FEATURE_LAST_SRC_MASK
mdefine_line|#define&t;&t;MPIC_GREG_FEATURE_LAST_SRC_MASK&t;&t;0x07ff0000
DECL|macro|MPIC_GREG_FEATURE_LAST_SRC_SHIFT
mdefine_line|#define&t;&t;MPIC_GREG_FEATURE_LAST_SRC_SHIFT&t;16
DECL|macro|MPIC_GREG_FEATURE_LAST_CPU_MASK
mdefine_line|#define&t;&t;MPIC_GREG_FEATURE_LAST_CPU_MASK&t;&t;0x00001f00
DECL|macro|MPIC_GREG_FEATURE_LAST_CPU_SHIFT
mdefine_line|#define&t;&t;MPIC_GREG_FEATURE_LAST_CPU_SHIFT&t;8
DECL|macro|MPIC_GREG_FEATURE_VERSION_MASK
mdefine_line|#define&t;&t;MPIC_GREG_FEATURE_VERSION_MASK&t;&t;0xff
DECL|macro|MPIC_GREG_FEATURE_1
mdefine_line|#define MPIC_GREG_FEATURE_1&t;&t;0x00010
DECL|macro|MPIC_GREG_GLOBAL_CONF_0
mdefine_line|#define MPIC_GREG_GLOBAL_CONF_0&t;&t;0x00020
DECL|macro|MPIC_GREG_GCONF_RESET
mdefine_line|#define&t;&t;MPIC_GREG_GCONF_RESET&t;&t;&t;0x80000000
DECL|macro|MPIC_GREG_GCONF_8259_PTHROU_DIS
mdefine_line|#define&t;&t;MPIC_GREG_GCONF_8259_PTHROU_DIS&t;&t;0x20000000
DECL|macro|MPIC_GREG_GCONF_BASE_MASK
mdefine_line|#define&t;&t;MPIC_GREG_GCONF_BASE_MASK&t;&t;0x000fffff
DECL|macro|MPIC_GREG_GLOBAL_CONF_1
mdefine_line|#define MPIC_GREG_GLOBAL_CONF_1&t;&t;0x00030
DECL|macro|MPIC_GREG_VENDOR_0
mdefine_line|#define MPIC_GREG_VENDOR_0&t;&t;0x00040
DECL|macro|MPIC_GREG_VENDOR_1
mdefine_line|#define MPIC_GREG_VENDOR_1&t;&t;0x00050
DECL|macro|MPIC_GREG_VENDOR_2
mdefine_line|#define MPIC_GREG_VENDOR_2&t;&t;0x00060
DECL|macro|MPIC_GREG_VENDOR_3
mdefine_line|#define MPIC_GREG_VENDOR_3&t;&t;0x00070
DECL|macro|MPIC_GREG_VENDOR_ID
mdefine_line|#define MPIC_GREG_VENDOR_ID&t;&t;0x00080
DECL|macro|MPIC_GREG_VENDOR_ID_STEPPING_MASK
mdefine_line|#define &t;MPIC_GREG_VENDOR_ID_STEPPING_MASK&t;0x00ff0000
DECL|macro|MPIC_GREG_VENDOR_ID_STEPPING_SHIFT
mdefine_line|#define &t;MPIC_GREG_VENDOR_ID_STEPPING_SHIFT&t;16
DECL|macro|MPIC_GREG_VENDOR_ID_DEVICE_ID_MASK
mdefine_line|#define &t;MPIC_GREG_VENDOR_ID_DEVICE_ID_MASK&t;0x0000ff00
DECL|macro|MPIC_GREG_VENDOR_ID_DEVICE_ID_SHIFT
mdefine_line|#define &t;MPIC_GREG_VENDOR_ID_DEVICE_ID_SHIFT&t;8
DECL|macro|MPIC_GREG_VENDOR_ID_VENDOR_ID_MASK
mdefine_line|#define &t;MPIC_GREG_VENDOR_ID_VENDOR_ID_MASK&t;0x000000ff
DECL|macro|MPIC_GREG_PROCESSOR_INIT
mdefine_line|#define MPIC_GREG_PROCESSOR_INIT&t;0x00090
DECL|macro|MPIC_GREG_IPI_VECTOR_PRI_0
mdefine_line|#define MPIC_GREG_IPI_VECTOR_PRI_0&t;0x000a0
DECL|macro|MPIC_GREG_IPI_VECTOR_PRI_1
mdefine_line|#define MPIC_GREG_IPI_VECTOR_PRI_1&t;0x000b0
DECL|macro|MPIC_GREG_IPI_VECTOR_PRI_2
mdefine_line|#define MPIC_GREG_IPI_VECTOR_PRI_2&t;0x000c0
DECL|macro|MPIC_GREG_IPI_VECTOR_PRI_3
mdefine_line|#define MPIC_GREG_IPI_VECTOR_PRI_3&t;0x000d0
DECL|macro|MPIC_GREG_SPURIOUS
mdefine_line|#define MPIC_GREG_SPURIOUS&t;&t;0x000e0
DECL|macro|MPIC_GREG_TIMER_FREQ
mdefine_line|#define MPIC_GREG_TIMER_FREQ&t;&t;0x000f0
multiline_comment|/*&n; *&n; * Timer registers&n; */
DECL|macro|MPIC_TIMER_BASE
mdefine_line|#define MPIC_TIMER_BASE&t;&t;&t;0x01100
DECL|macro|MPIC_TIMER_STRIDE
mdefine_line|#define MPIC_TIMER_STRIDE&t;&t;0x40
DECL|macro|MPIC_TIMER_CURRENT_CNT
mdefine_line|#define MPIC_TIMER_CURRENT_CNT&t;&t;0x00000
DECL|macro|MPIC_TIMER_BASE_CNT
mdefine_line|#define MPIC_TIMER_BASE_CNT&t;&t;0x00010
DECL|macro|MPIC_TIMER_VECTOR_PRI
mdefine_line|#define MPIC_TIMER_VECTOR_PRI&t;&t;0x00020
DECL|macro|MPIC_TIMER_DESTINATION
mdefine_line|#define MPIC_TIMER_DESTINATION&t;&t;0x00030
multiline_comment|/*&n; * Per-Processor registers&n; */
DECL|macro|MPIC_CPU_THISBASE
mdefine_line|#define MPIC_CPU_THISBASE&t;&t;0x00000
DECL|macro|MPIC_CPU_BASE
mdefine_line|#define MPIC_CPU_BASE&t;&t;&t;0x20000
DECL|macro|MPIC_CPU_STRIDE
mdefine_line|#define MPIC_CPU_STRIDE&t;&t;&t;0x01000
DECL|macro|MPIC_CPU_IPI_DISPATCH_0
mdefine_line|#define MPIC_CPU_IPI_DISPATCH_0&t;&t;0x00040
DECL|macro|MPIC_CPU_IPI_DISPATCH_1
mdefine_line|#define MPIC_CPU_IPI_DISPATCH_1&t;&t;0x00050
DECL|macro|MPIC_CPU_IPI_DISPATCH_2
mdefine_line|#define MPIC_CPU_IPI_DISPATCH_2&t;&t;0x00060
DECL|macro|MPIC_CPU_IPI_DISPATCH_3
mdefine_line|#define MPIC_CPU_IPI_DISPATCH_3&t;&t;0x00070
DECL|macro|MPIC_CPU_CURRENT_TASK_PRI
mdefine_line|#define MPIC_CPU_CURRENT_TASK_PRI&t;0x00080
DECL|macro|MPIC_CPU_TASKPRI_MASK
mdefine_line|#define &t;MPIC_CPU_TASKPRI_MASK&t;&t;&t;0x0000000f
DECL|macro|MPIC_CPU_WHOAMI
mdefine_line|#define MPIC_CPU_WHOAMI&t;&t;&t;0x00090
DECL|macro|MPIC_CPU_WHOAMI_MASK
mdefine_line|#define &t;MPIC_CPU_WHOAMI_MASK&t;&t;&t;0x0000001f
DECL|macro|MPIC_CPU_INTACK
mdefine_line|#define MPIC_CPU_INTACK&t;&t;&t;0x000a0
DECL|macro|MPIC_CPU_EOI
mdefine_line|#define MPIC_CPU_EOI&t;&t;&t;0x000b0
multiline_comment|/*&n; * Per-source registers&n; */
DECL|macro|MPIC_IRQ_BASE
mdefine_line|#define MPIC_IRQ_BASE&t;&t;&t;0x10000
DECL|macro|MPIC_IRQ_STRIDE
mdefine_line|#define MPIC_IRQ_STRIDE&t;&t;&t;0x00020
DECL|macro|MPIC_IRQ_VECTOR_PRI
mdefine_line|#define MPIC_IRQ_VECTOR_PRI&t;&t;0x00000
DECL|macro|MPIC_VECPRI_MASK
mdefine_line|#define &t;MPIC_VECPRI_MASK&t;&t;&t;0x80000000
DECL|macro|MPIC_VECPRI_ACTIVITY
mdefine_line|#define &t;MPIC_VECPRI_ACTIVITY&t;&t;&t;0x40000000&t;/* Read Only */
DECL|macro|MPIC_VECPRI_PRIORITY_MASK
mdefine_line|#define &t;MPIC_VECPRI_PRIORITY_MASK&t;&t;0x000f0000
DECL|macro|MPIC_VECPRI_PRIORITY_SHIFT
mdefine_line|#define &t;MPIC_VECPRI_PRIORITY_SHIFT&t;&t;16
DECL|macro|MPIC_VECPRI_VECTOR_MASK
mdefine_line|#define &t;MPIC_VECPRI_VECTOR_MASK&t;&t;&t;0x000007ff
DECL|macro|MPIC_VECPRI_POLARITY_POSITIVE
mdefine_line|#define &t;MPIC_VECPRI_POLARITY_POSITIVE&t;&t;0x00800000
DECL|macro|MPIC_VECPRI_POLARITY_NEGATIVE
mdefine_line|#define &t;MPIC_VECPRI_POLARITY_NEGATIVE&t;&t;0x00000000
DECL|macro|MPIC_VECPRI_POLARITY_MASK
mdefine_line|#define &t;MPIC_VECPRI_POLARITY_MASK&t;&t;0x00800000
DECL|macro|MPIC_VECPRI_SENSE_LEVEL
mdefine_line|#define &t;MPIC_VECPRI_SENSE_LEVEL&t;&t;&t;0x00400000
DECL|macro|MPIC_VECPRI_SENSE_EDGE
mdefine_line|#define &t;MPIC_VECPRI_SENSE_EDGE&t;&t;&t;0x00000000
DECL|macro|MPIC_VECPRI_SENSE_MASK
mdefine_line|#define &t;MPIC_VECPRI_SENSE_MASK&t;&t;&t;0x00400000
DECL|macro|MPIC_IRQ_DESTINATION
mdefine_line|#define MPIC_IRQ_DESTINATION&t;&t;0x00010
DECL|macro|MPIC_MAX_IRQ_SOURCES
mdefine_line|#define MPIC_MAX_IRQ_SOURCES&t;2048
DECL|macro|MPIC_MAX_CPUS
mdefine_line|#define MPIC_MAX_CPUS&t;&t;32
DECL|macro|MPIC_MAX_ISU
mdefine_line|#define MPIC_MAX_ISU&t;&t;32
multiline_comment|/*&n; * Special vector numbers (internal use only)&n; */
DECL|macro|MPIC_VEC_SPURRIOUS
mdefine_line|#define MPIC_VEC_SPURRIOUS&t;255
DECL|macro|MPIC_VEC_IPI_3
mdefine_line|#define MPIC_VEC_IPI_3&t;&t;254
DECL|macro|MPIC_VEC_IPI_2
mdefine_line|#define MPIC_VEC_IPI_2&t;&t;253
DECL|macro|MPIC_VEC_IPI_1
mdefine_line|#define MPIC_VEC_IPI_1&t;&t;252
DECL|macro|MPIC_VEC_IPI_0
mdefine_line|#define MPIC_VEC_IPI_0&t;&t;251
multiline_comment|/* unused */
DECL|macro|MPIC_VEC_TIMER_3
mdefine_line|#define MPIC_VEC_TIMER_3&t;250
DECL|macro|MPIC_VEC_TIMER_2
mdefine_line|#define MPIC_VEC_TIMER_2&t;249
DECL|macro|MPIC_VEC_TIMER_1
mdefine_line|#define MPIC_VEC_TIMER_1&t;248
DECL|macro|MPIC_VEC_TIMER_0
mdefine_line|#define MPIC_VEC_TIMER_0&t;247
multiline_comment|/* Type definition of the cascade handler */
DECL|typedef|mpic_cascade_t
r_typedef
r_int
(paren
op_star
id|mpic_cascade_t
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MPIC_BROKEN_U3
multiline_comment|/* Fixup table entry */
DECL|struct|mpic_irq_fixup
r_struct
id|mpic_irq_fixup
(brace
DECL|member|base
id|u8
id|__iomem
op_star
id|base
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_MPIC_BROKEN_U3 */
multiline_comment|/* The instance data of a given MPIC */
DECL|struct|mpic
r_struct
id|mpic
(brace
multiline_comment|/* The &quot;linux&quot; controller struct */
DECL|member|hc_irq
id|hw_irq_controller
id|hc_irq
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|member|hc_ipi
id|hw_irq_controller
id|hc_ipi
suffix:semicolon
macro_line|#endif
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Flags */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* How many irq sources in a given ISU */
DECL|member|isu_size
r_int
r_int
id|isu_size
suffix:semicolon
DECL|member|isu_shift
r_int
r_int
id|isu_shift
suffix:semicolon
DECL|member|isu_mask
r_int
r_int
id|isu_mask
suffix:semicolon
multiline_comment|/* Offset of irq vector numbers */
DECL|member|irq_offset
r_int
r_int
id|irq_offset
suffix:semicolon
DECL|member|irq_count
r_int
r_int
id|irq_count
suffix:semicolon
multiline_comment|/* Offset of ipi vector numbers */
DECL|member|ipi_offset
r_int
r_int
id|ipi_offset
suffix:semicolon
multiline_comment|/* Number of sources */
DECL|member|num_sources
r_int
r_int
id|num_sources
suffix:semicolon
multiline_comment|/* Number of CPUs */
DECL|member|num_cpus
r_int
r_int
id|num_cpus
suffix:semicolon
multiline_comment|/* cascade handler */
DECL|member|cascade
id|mpic_cascade_t
id|cascade
suffix:semicolon
DECL|member|cascade_data
r_void
op_star
id|cascade_data
suffix:semicolon
DECL|member|cascade_vec
r_int
r_int
id|cascade_vec
suffix:semicolon
multiline_comment|/* senses array */
DECL|member|senses
r_int
r_char
op_star
id|senses
suffix:semicolon
DECL|member|senses_count
r_int
r_int
id|senses_count
suffix:semicolon
macro_line|#ifdef CONFIG_MPIC_BROKEN_U3
multiline_comment|/* The fixup table */
DECL|member|fixups
r_struct
id|mpic_irq_fixup
op_star
id|fixups
suffix:semicolon
DECL|member|fixup_lock
id|spinlock_t
id|fixup_lock
suffix:semicolon
macro_line|#endif
multiline_comment|/* The various ioremap&squot;ed bases */
DECL|member|gregs
r_volatile
id|u32
id|__iomem
op_star
id|gregs
suffix:semicolon
DECL|member|tmregs
r_volatile
id|u32
id|__iomem
op_star
id|tmregs
suffix:semicolon
DECL|member|cpuregs
r_volatile
id|u32
id|__iomem
op_star
id|cpuregs
(braket
id|MPIC_MAX_CPUS
)braket
suffix:semicolon
DECL|member|isus
r_volatile
id|u32
id|__iomem
op_star
id|isus
(braket
id|MPIC_MAX_ISU
)braket
suffix:semicolon
multiline_comment|/* link */
DECL|member|next
r_struct
id|mpic
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is the primary controller, only that one has IPIs and&n; * has afinity control. A non-primary MPIC always uses CPU0&n; * registers only&n; */
DECL|macro|MPIC_PRIMARY
mdefine_line|#define MPIC_PRIMARY&t;&t;&t;0x00000001
multiline_comment|/* Set this for a big-endian MPIC */
DECL|macro|MPIC_BIG_ENDIAN
mdefine_line|#define MPIC_BIG_ENDIAN&t;&t;&t;0x00000002
multiline_comment|/* Broken U3 MPIC */
DECL|macro|MPIC_BROKEN_U3
mdefine_line|#define MPIC_BROKEN_U3&t;&t;&t;0x00000004
multiline_comment|/* Broken IPI registers (autodetected) */
DECL|macro|MPIC_BROKEN_IPI
mdefine_line|#define MPIC_BROKEN_IPI&t;&t;&t;0x00000008
multiline_comment|/* MPIC wants a reset */
DECL|macro|MPIC_WANTS_RESET
mdefine_line|#define MPIC_WANTS_RESET&t;&t;0x00000010
multiline_comment|/* Allocate the controller structure and setup the linux irq descs&n; * for the range if interrupts passed in. No HW initialization is&n; * actually performed.&n; * &n; * @phys_addr:&t;physial base address of the MPIC&n; * @flags:&t;flags, see constants above&n; * @isu_size:&t;number of interrupts in an ISU. Use 0 to use a&n; *              standard ISU-less setup (aka powermac)&n; * @irq_offset: first irq number to assign to this mpic&n; * @irq_count:  number of irqs to use with this mpic IRQ sources. Pass 0&n; *&t;        to match the number of sources&n; * @ipi_offset: first irq number to assign to this mpic IPI sources,&n; *&t;&t;used only on primary mpic&n; * @senses:&t;array of sense values&n; * @senses_num: number of entries in the array&n; *&n; * Note about the sense array. If none is passed, all interrupts are&n; * setup to be level negative unless MPIC_BROKEN_U3 is set in which&n; * case they are edge positive (and the array is ignored anyway).&n; * The values in the array start at the first source of the MPIC,&n; * that is senses[0] correspond to linux irq &quot;irq_offset&quot;.&n; */
r_extern
r_struct
id|mpic
op_star
id|mpic_alloc
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|isu_size
comma
r_int
r_int
id|irq_offset
comma
r_int
r_int
id|irq_count
comma
r_int
r_int
id|ipi_offset
comma
r_int
r_char
op_star
id|senses
comma
r_int
r_int
id|senses_num
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* Assign ISUs, to call before mpic_init()&n; *&n; * @mpic:&t;controller structure as returned by mpic_alloc()&n; * @isu_num:&t;ISU number&n; * @phys_addr:&t;physical address of the ISU&n; */
r_extern
r_void
id|mpic_assign_isu
c_func
(paren
r_struct
id|mpic
op_star
id|mpic
comma
r_int
r_int
id|isu_num
comma
r_int
r_int
id|phys_addr
)paren
suffix:semicolon
multiline_comment|/* Initialize the controller. After this has been called, none of the above&n; * should be called again for this mpic&n; */
r_extern
r_void
id|mpic_init
c_func
(paren
r_struct
id|mpic
op_star
id|mpic
)paren
suffix:semicolon
multiline_comment|/* Setup a cascade. Currently, only one cascade is supported this&n; * way, though you can always do a normal request_irq() and add&n; * other cascades this way. You should call this _after_ having&n; * added all the ISUs&n; *&n; * @irq_no:&t;&quot;linux&quot; irq number of the cascade (that is offset&squot;ed vector)&n; * @handler:&t;cascade handler function&n; */
r_extern
r_void
id|mpic_setup_cascade
c_func
(paren
r_int
r_int
id|irq_no
comma
id|mpic_cascade_t
id|hanlder
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * All of the following functions must only be used after the&n; * ISUs have been assigned and the controller fully initialized&n; * with mpic_init()&n; */
multiline_comment|/* Change/Read the priority of an interrupt. Default is 8 for irqs and&n; * 10 for IPIs. You can call this on both IPIs and IRQ numbers, but the&n; * IPI number is then the offset&squot;ed (linux irq number mapped to the IPI)&n; */
r_extern
r_void
id|mpic_irq_set_priority
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|pri
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mpic_irq_get_priority
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Setup a non-boot CPU */
r_extern
r_void
id|mpic_setup_this_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Request IPIs on primary mpic */
r_extern
r_void
id|mpic_request_ipis
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Send an IPI (non offseted number 0..3) */
r_extern
r_void
id|mpic_send_ipi
c_func
(paren
r_int
r_int
id|ipi_no
comma
r_int
r_int
id|cpu_mask
)paren
suffix:semicolon
multiline_comment|/* Fetch interrupt from a given mpic */
r_extern
r_int
id|mpic_get_one_irq
c_func
(paren
r_struct
id|mpic
op_star
id|mpic
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/* This one gets to the primary mpic */
r_extern
r_int
id|mpic_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
eof
