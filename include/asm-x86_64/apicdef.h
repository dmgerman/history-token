macro_line|#ifndef __ASM_APICDEF_H
DECL|macro|__ASM_APICDEF_H
mdefine_line|#define __ASM_APICDEF_H
multiline_comment|/*&n; * Constants for various Intel APICs. (local APIC, IOAPIC, etc.)&n; *&n; * Alan Cox &lt;Alan.Cox@linux.org&gt;, 1995.&n; * Ingo Molnar &lt;mingo@redhat.com&gt;, 1999, 2000&n; */
DECL|macro|APIC_DEFAULT_PHYS_BASE
mdefine_line|#define&t;&t;APIC_DEFAULT_PHYS_BASE&t;0xfee00000
DECL|macro|APIC_ID
mdefine_line|#define&t;&t;APIC_ID&t;&t;0x20
DECL|macro|APIC_ID_MASK
mdefine_line|#define&t;&t;&t;APIC_ID_MASK&t;&t;(0x0F&lt;&lt;24)
DECL|macro|GET_APIC_ID
mdefine_line|#define&t;&t;&t;GET_APIC_ID(x)&t;&t;(((x)&gt;&gt;24)&amp;0x0F)
DECL|macro|APIC_LVR
mdefine_line|#define&t;&t;APIC_LVR&t;0x30
DECL|macro|APIC_LVR_MASK
mdefine_line|#define&t;&t;&t;APIC_LVR_MASK&t;&t;0xFF00FF
DECL|macro|GET_APIC_VERSION
mdefine_line|#define&t;&t;&t;GET_APIC_VERSION(x)&t;((x)&amp;0xFF)
DECL|macro|GET_APIC_MAXLVT
mdefine_line|#define&t;&t;&t;GET_APIC_MAXLVT(x)&t;(((x)&gt;&gt;16)&amp;0xFF)
DECL|macro|APIC_INTEGRATED
mdefine_line|#define&t;&t;&t;APIC_INTEGRATED(x)&t;((x)&amp;0xF0)
DECL|macro|APIC_TASKPRI
mdefine_line|#define&t;&t;APIC_TASKPRI&t;0x80
DECL|macro|APIC_TPRI_MASK
mdefine_line|#define&t;&t;&t;APIC_TPRI_MASK&t;&t;0xFF
DECL|macro|APIC_ARBPRI
mdefine_line|#define&t;&t;APIC_ARBPRI&t;0x90
DECL|macro|APIC_ARBPRI_MASK
mdefine_line|#define&t;&t;&t;APIC_ARBPRI_MASK&t;0xFF
DECL|macro|APIC_PROCPRI
mdefine_line|#define&t;&t;APIC_PROCPRI&t;0xA0
DECL|macro|APIC_EOI
mdefine_line|#define&t;&t;APIC_EOI&t;0xB0
DECL|macro|APIC_EIO_ACK
mdefine_line|#define&t;&t;&t;APIC_EIO_ACK&t;&t;0x0&t;&t;/* Write this to the EOI register */
DECL|macro|APIC_RRR
mdefine_line|#define&t;&t;APIC_RRR&t;0xC0
DECL|macro|APIC_LDR
mdefine_line|#define&t;&t;APIC_LDR&t;0xD0
DECL|macro|APIC_LDR_MASK
mdefine_line|#define&t;&t;&t;APIC_LDR_MASK&t;&t;(0xFF&lt;&lt;24)
DECL|macro|GET_APIC_LOGICAL_ID
mdefine_line|#define&t;&t;&t;GET_APIC_LOGICAL_ID(x)&t;(((x)&gt;&gt;24)&amp;0xFF)
DECL|macro|SET_APIC_LOGICAL_ID
mdefine_line|#define&t;&t;&t;SET_APIC_LOGICAL_ID(x)&t;(((x)&lt;&lt;24))
DECL|macro|APIC_ALL_CPUS
mdefine_line|#define&t;&t;&t;APIC_ALL_CPUS&t;&t;0xFF
DECL|macro|APIC_DFR
mdefine_line|#define&t;&t;APIC_DFR&t;0xE0
DECL|macro|APIC_SPIV
mdefine_line|#define&t;&t;APIC_SPIV&t;0xF0
DECL|macro|APIC_SPIV_FOCUS_DISABLED
mdefine_line|#define&t;&t;&t;APIC_SPIV_FOCUS_DISABLED&t;(1&lt;&lt;9)
DECL|macro|APIC_SPIV_APIC_ENABLED
mdefine_line|#define&t;&t;&t;APIC_SPIV_APIC_ENABLED&t;&t;(1&lt;&lt;8)
DECL|macro|APIC_ISR
mdefine_line|#define&t;&t;APIC_ISR&t;0x100
DECL|macro|APIC_TMR
mdefine_line|#define&t;&t;APIC_TMR&t;0x180
DECL|macro|APIC_IRR
mdefine_line|#define &t;APIC_IRR&t;0x200
DECL|macro|APIC_ESR
mdefine_line|#define &t;APIC_ESR&t;0x280
DECL|macro|APIC_ESR_SEND_CS
mdefine_line|#define&t;&t;&t;APIC_ESR_SEND_CS&t;0x00001
DECL|macro|APIC_ESR_RECV_CS
mdefine_line|#define&t;&t;&t;APIC_ESR_RECV_CS&t;0x00002
DECL|macro|APIC_ESR_SEND_ACC
mdefine_line|#define&t;&t;&t;APIC_ESR_SEND_ACC&t;0x00004
DECL|macro|APIC_ESR_RECV_ACC
mdefine_line|#define&t;&t;&t;APIC_ESR_RECV_ACC&t;0x00008
DECL|macro|APIC_ESR_SENDILL
mdefine_line|#define&t;&t;&t;APIC_ESR_SENDILL&t;0x00020
DECL|macro|APIC_ESR_RECVILL
mdefine_line|#define&t;&t;&t;APIC_ESR_RECVILL&t;0x00040
DECL|macro|APIC_ESR_ILLREGA
mdefine_line|#define&t;&t;&t;APIC_ESR_ILLREGA&t;0x00080
DECL|macro|APIC_ICR
mdefine_line|#define&t;&t;APIC_ICR&t;0x300
DECL|macro|APIC_DEST_SELF
mdefine_line|#define&t;&t;&t;APIC_DEST_SELF&t;&t;0x40000
DECL|macro|APIC_DEST_ALLINC
mdefine_line|#define&t;&t;&t;APIC_DEST_ALLINC&t;0x80000
DECL|macro|APIC_DEST_ALLBUT
mdefine_line|#define&t;&t;&t;APIC_DEST_ALLBUT&t;0xC0000
DECL|macro|APIC_ICR_RR_MASK
mdefine_line|#define&t;&t;&t;APIC_ICR_RR_MASK&t;0x30000
DECL|macro|APIC_ICR_RR_INVALID
mdefine_line|#define&t;&t;&t;APIC_ICR_RR_INVALID&t;0x00000
DECL|macro|APIC_ICR_RR_INPROG
mdefine_line|#define&t;&t;&t;APIC_ICR_RR_INPROG&t;0x10000
DECL|macro|APIC_ICR_RR_VALID
mdefine_line|#define&t;&t;&t;APIC_ICR_RR_VALID&t;0x20000
DECL|macro|APIC_INT_LEVELTRIG
mdefine_line|#define&t;&t;&t;APIC_INT_LEVELTRIG&t;0x08000
DECL|macro|APIC_INT_ASSERT
mdefine_line|#define&t;&t;&t;APIC_INT_ASSERT&t;&t;0x04000
DECL|macro|APIC_ICR_BUSY
mdefine_line|#define&t;&t;&t;APIC_ICR_BUSY&t;&t;0x01000
DECL|macro|APIC_DEST_LOGICAL
mdefine_line|#define&t;&t;&t;APIC_DEST_LOGICAL&t;0x00800
DECL|macro|APIC_DM_FIXED
mdefine_line|#define&t;&t;&t;APIC_DM_FIXED&t;&t;0x00000
DECL|macro|APIC_DM_LOWEST
mdefine_line|#define&t;&t;&t;APIC_DM_LOWEST&t;&t;0x00100
DECL|macro|APIC_DM_SMI
mdefine_line|#define&t;&t;&t;APIC_DM_SMI&t;&t;0x00200
DECL|macro|APIC_DM_REMRD
mdefine_line|#define&t;&t;&t;APIC_DM_REMRD&t;&t;0x00300
DECL|macro|APIC_DM_NMI
mdefine_line|#define&t;&t;&t;APIC_DM_NMI&t;&t;0x00400
DECL|macro|APIC_DM_INIT
mdefine_line|#define&t;&t;&t;APIC_DM_INIT&t;&t;0x00500
DECL|macro|APIC_DM_STARTUP
mdefine_line|#define&t;&t;&t;APIC_DM_STARTUP&t;&t;0x00600
DECL|macro|APIC_DM_EXTINT
mdefine_line|#define&t;&t;&t;APIC_DM_EXTINT&t;&t;0x00700
DECL|macro|APIC_VECTOR_MASK
mdefine_line|#define&t;&t;&t;APIC_VECTOR_MASK&t;0x000FF
DECL|macro|APIC_ICR2
mdefine_line|#define&t;&t;APIC_ICR2&t;0x310
DECL|macro|GET_APIC_DEST_FIELD
mdefine_line|#define&t;&t;&t;GET_APIC_DEST_FIELD(x)&t;(((x)&gt;&gt;24)&amp;0xFF)
DECL|macro|SET_APIC_DEST_FIELD
mdefine_line|#define&t;&t;&t;SET_APIC_DEST_FIELD(x)&t;((x)&lt;&lt;24)
DECL|macro|APIC_LVTT
mdefine_line|#define&t;&t;APIC_LVTT&t;0x320
DECL|macro|APIC_LVTPC
mdefine_line|#define&t;&t;APIC_LVTPC&t;0x340
DECL|macro|APIC_LVT0
mdefine_line|#define&t;&t;APIC_LVT0&t;0x350
DECL|macro|APIC_LVT_TIMER_BASE_MASK
mdefine_line|#define&t;&t;&t;APIC_LVT_TIMER_BASE_MASK&t;(0x3&lt;&lt;18)
DECL|macro|GET_APIC_TIMER_BASE
mdefine_line|#define&t;&t;&t;GET_APIC_TIMER_BASE(x)&t;&t;(((x)&gt;&gt;18)&amp;0x3)
DECL|macro|SET_APIC_TIMER_BASE
mdefine_line|#define&t;&t;&t;SET_APIC_TIMER_BASE(x)&t;&t;(((x)&lt;&lt;18))
DECL|macro|APIC_TIMER_BASE_CLKIN
mdefine_line|#define&t;&t;&t;APIC_TIMER_BASE_CLKIN&t;&t;0x0
DECL|macro|APIC_TIMER_BASE_TMBASE
mdefine_line|#define&t;&t;&t;APIC_TIMER_BASE_TMBASE&t;&t;0x1
DECL|macro|APIC_TIMER_BASE_DIV
mdefine_line|#define&t;&t;&t;APIC_TIMER_BASE_DIV&t;&t;0x2
DECL|macro|APIC_LVT_TIMER_PERIODIC
mdefine_line|#define&t;&t;&t;APIC_LVT_TIMER_PERIODIC&t;&t;(1&lt;&lt;17)
DECL|macro|APIC_LVT_MASKED
mdefine_line|#define&t;&t;&t;APIC_LVT_MASKED&t;&t;&t;(1&lt;&lt;16)
DECL|macro|APIC_LVT_LEVEL_TRIGGER
mdefine_line|#define&t;&t;&t;APIC_LVT_LEVEL_TRIGGER&t;&t;(1&lt;&lt;15)
DECL|macro|APIC_LVT_REMOTE_IRR
mdefine_line|#define&t;&t;&t;APIC_LVT_REMOTE_IRR&t;&t;(1&lt;&lt;14)
DECL|macro|APIC_INPUT_POLARITY
mdefine_line|#define&t;&t;&t;APIC_INPUT_POLARITY&t;&t;(1&lt;&lt;13)
DECL|macro|APIC_SEND_PENDING
mdefine_line|#define&t;&t;&t;APIC_SEND_PENDING&t;&t;(1&lt;&lt;12)
DECL|macro|GET_APIC_DELIVERY_MODE
mdefine_line|#define&t;&t;&t;GET_APIC_DELIVERY_MODE(x)&t;(((x)&gt;&gt;8)&amp;0x7)
DECL|macro|SET_APIC_DELIVERY_MODE
mdefine_line|#define&t;&t;&t;SET_APIC_DELIVERY_MODE(x,y)&t;(((x)&amp;~0x700)|((y)&lt;&lt;8))
DECL|macro|APIC_MODE_FIXED
mdefine_line|#define&t;&t;&t;&t;APIC_MODE_FIXED&t;&t;0x0
DECL|macro|APIC_MODE_NMI
mdefine_line|#define&t;&t;&t;&t;APIC_MODE_NMI&t;&t;0x4
DECL|macro|APIC_MODE_EXINT
mdefine_line|#define&t;&t;&t;&t;APIC_MODE_EXINT&t;&t;0x7
DECL|macro|APIC_LVT1
mdefine_line|#define &t;APIC_LVT1&t;0x360
DECL|macro|APIC_LVTERR
mdefine_line|#define&t;&t;APIC_LVTERR&t;0x370
DECL|macro|APIC_TMICT
mdefine_line|#define&t;&t;APIC_TMICT&t;0x380
DECL|macro|APIC_TMCCT
mdefine_line|#define&t;&t;APIC_TMCCT&t;0x390
DECL|macro|APIC_TDCR
mdefine_line|#define&t;&t;APIC_TDCR&t;0x3E0
DECL|macro|APIC_TDR_DIV_TMBASE
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_TMBASE&t;(1&lt;&lt;2)
DECL|macro|APIC_TDR_DIV_1
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_1&t;&t;0xB
DECL|macro|APIC_TDR_DIV_2
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_2&t;&t;0x0
DECL|macro|APIC_TDR_DIV_4
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_4&t;&t;0x1
DECL|macro|APIC_TDR_DIV_8
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_8&t;&t;0x2
DECL|macro|APIC_TDR_DIV_16
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_16&t;&t;0x3
DECL|macro|APIC_TDR_DIV_32
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_32&t;&t;0x8
DECL|macro|APIC_TDR_DIV_64
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_64&t;&t;0x9
DECL|macro|APIC_TDR_DIV_128
mdefine_line|#define&t;&t;&t;APIC_TDR_DIV_128&t;0xA
DECL|macro|APIC_BASE
mdefine_line|#define APIC_BASE (fix_to_virt(FIX_APIC_BASE))
DECL|macro|MAX_IO_APICS
mdefine_line|#define MAX_IO_APICS 8
multiline_comment|/*&n; * the local APIC register structure, memory mapped. Not terribly well&n; * tested, but we might eventually use this one in the future - the&n; * problem why we cannot use it right now is the P5 APIC, it has an&n; * errata which cannot take 8-bit reads and writes, only 32-bit ones ...&n; */
DECL|macro|u32
mdefine_line|#define u32 unsigned int
DECL|macro|lapic
mdefine_line|#define lapic ((volatile struct local_apic *)APIC_BASE)
DECL|struct|local_apic
r_struct
id|local_apic
(brace
DECL|member|__reserved
DECL|member|__reserved_01
multiline_comment|/*000*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_01
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_02
multiline_comment|/*010*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_02
suffix:semicolon
multiline_comment|/*020*/
r_struct
(brace
multiline_comment|/* APIC ID Register */
DECL|member|__reserved_1
id|u32
id|__reserved_1
suffix:colon
l_int|24
comma
DECL|member|phys_apic_id
id|phys_apic_id
suffix:colon
l_int|4
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|__reserved
id|u32
id|__reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|id
)brace
id|id
suffix:semicolon
multiline_comment|/*030*/
r_const
r_struct
(brace
multiline_comment|/* APIC Version Register */
DECL|member|version
id|u32
id|version
suffix:colon
l_int|8
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|8
comma
DECL|member|max_lvt
id|max_lvt
suffix:colon
l_int|8
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|8
suffix:semicolon
DECL|member|__reserved
id|u32
id|__reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|version
)brace
id|version
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_03
multiline_comment|/*040*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_03
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_04
multiline_comment|/*050*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_04
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_05
multiline_comment|/*060*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_05
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_06
multiline_comment|/*070*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_06
suffix:semicolon
multiline_comment|/*080*/
r_struct
(brace
multiline_comment|/* Task Priority Register */
DECL|member|priority
id|u32
id|priority
suffix:colon
l_int|8
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|24
suffix:semicolon
DECL|member|__reserved_2
id|u32
id|__reserved_2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tpr
)brace
id|tpr
suffix:semicolon
multiline_comment|/*090*/
r_const
r_struct
(brace
multiline_comment|/* Arbitration Priority Register */
DECL|member|priority
id|u32
id|priority
suffix:colon
l_int|8
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|24
suffix:semicolon
DECL|member|__reserved_2
id|u32
id|__reserved_2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|apr
)brace
id|apr
suffix:semicolon
multiline_comment|/*0A0*/
r_const
r_struct
(brace
multiline_comment|/* Processor Priority Register */
DECL|member|priority
id|u32
id|priority
suffix:colon
l_int|8
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|24
suffix:semicolon
DECL|member|__reserved_2
id|u32
id|__reserved_2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ppr
)brace
id|ppr
suffix:semicolon
multiline_comment|/*0B0*/
r_struct
(brace
multiline_comment|/* End Of Interrupt Register */
DECL|member|eoi
id|u32
id|eoi
suffix:semicolon
DECL|member|__reserved
id|u32
id|__reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|eoi
)brace
id|eoi
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_07
multiline_comment|/*0C0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_07
suffix:semicolon
multiline_comment|/*0D0*/
r_struct
(brace
multiline_comment|/* Logical Destination Register */
DECL|member|__reserved_1
id|u32
id|__reserved_1
suffix:colon
l_int|24
comma
DECL|member|logical_dest
id|logical_dest
suffix:colon
l_int|8
suffix:semicolon
DECL|member|__reserved_2
id|u32
id|__reserved_2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ldr
)brace
id|ldr
suffix:semicolon
multiline_comment|/*0E0*/
r_struct
(brace
multiline_comment|/* Destination Format Register */
DECL|member|__reserved_1
id|u32
id|__reserved_1
suffix:colon
l_int|28
comma
DECL|member|model
id|model
suffix:colon
l_int|4
suffix:semicolon
DECL|member|__reserved_2
id|u32
id|__reserved_2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|dfr
)brace
id|dfr
suffix:semicolon
multiline_comment|/*0F0*/
r_struct
(brace
multiline_comment|/* Spurious Interrupt Vector Register */
DECL|member|spurious_vector
id|u32
id|spurious_vector
suffix:colon
l_int|8
comma
DECL|member|apic_enabled
id|apic_enabled
suffix:colon
l_int|1
comma
DECL|member|focus_cpu
id|focus_cpu
suffix:colon
l_int|1
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|22
suffix:semicolon
DECL|member|__reserved_3
id|u32
id|__reserved_3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|svr
)brace
id|svr
suffix:semicolon
multiline_comment|/*100*/
r_struct
(brace
multiline_comment|/* In Service Register */
DECL|member|bitfield
multiline_comment|/*170*/
id|u32
id|bitfield
suffix:semicolon
DECL|member|__reserved
id|u32
id|__reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|isr
)brace
id|isr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/*180*/
r_struct
(brace
multiline_comment|/* Trigger Mode Register */
DECL|member|bitfield
multiline_comment|/*1F0*/
id|u32
id|bitfield
suffix:semicolon
DECL|member|__reserved
id|u32
id|__reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tmr
)brace
id|tmr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/*200*/
r_struct
(brace
multiline_comment|/* Interrupt Request Register */
DECL|member|bitfield
multiline_comment|/*270*/
id|u32
id|bitfield
suffix:semicolon
DECL|member|__reserved
id|u32
id|__reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|irr
)brace
id|irr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/*280*/
r_union
(brace
multiline_comment|/* Error Status Register */
r_struct
(brace
DECL|member|send_cs_error
id|u32
id|send_cs_error
suffix:colon
l_int|1
comma
DECL|member|receive_cs_error
id|receive_cs_error
suffix:colon
l_int|1
comma
DECL|member|send_accept_error
id|send_accept_error
suffix:colon
l_int|1
comma
DECL|member|receive_accept_error
id|receive_accept_error
suffix:colon
l_int|1
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|1
comma
DECL|member|send_illegal_vector
id|send_illegal_vector
suffix:colon
l_int|1
comma
DECL|member|receive_illegal_vector
id|receive_illegal_vector
suffix:colon
l_int|1
comma
DECL|member|illegal_register_address
id|illegal_register_address
suffix:colon
l_int|1
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|24
suffix:semicolon
DECL|member|__reserved_3
id|u32
id|__reserved_3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|error_bits
)brace
id|error_bits
suffix:semicolon
r_struct
(brace
DECL|member|errors
id|u32
id|errors
suffix:semicolon
DECL|member|__reserved_3
id|u32
id|__reserved_3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|all_errors
)brace
id|all_errors
suffix:semicolon
DECL|member|esr
)brace
id|esr
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_08
multiline_comment|/*290*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_08
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_09
multiline_comment|/*2A0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_09
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_10
multiline_comment|/*2B0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_10
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_11
multiline_comment|/*2C0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_11
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_12
multiline_comment|/*2D0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_12
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_13
multiline_comment|/*2E0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_13
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_14
multiline_comment|/*2F0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_14
suffix:semicolon
multiline_comment|/*300*/
r_struct
(brace
multiline_comment|/* Interrupt Command Register 1 */
DECL|member|vector
id|u32
id|vector
suffix:colon
l_int|8
comma
DECL|member|delivery_mode
id|delivery_mode
suffix:colon
l_int|3
comma
DECL|member|destination_mode
id|destination_mode
suffix:colon
l_int|1
comma
DECL|member|delivery_status
id|delivery_status
suffix:colon
l_int|1
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|1
comma
DECL|member|level
id|level
suffix:colon
l_int|1
comma
DECL|member|trigger
id|trigger
suffix:colon
l_int|1
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|2
comma
DECL|member|shorthand
id|shorthand
suffix:colon
l_int|2
comma
DECL|member|__reserved_3
id|__reserved_3
suffix:colon
l_int|12
suffix:semicolon
DECL|member|__reserved_4
id|u32
id|__reserved_4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|icr1
)brace
id|icr1
suffix:semicolon
multiline_comment|/*310*/
r_struct
(brace
multiline_comment|/* Interrupt Command Register 2 */
r_union
(brace
id|u32
id|__reserved_1
suffix:colon
l_int|24
comma
id|phys_dest
suffix:colon
l_int|4
comma
id|__reserved_2
suffix:colon
l_int|4
suffix:semicolon
id|u32
id|__reserved_3
suffix:colon
l_int|24
comma
id|logical_dest
suffix:colon
l_int|8
suffix:semicolon
DECL|member|dest
)brace
id|dest
suffix:semicolon
DECL|member|__reserved_4
id|u32
id|__reserved_4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|icr2
)brace
id|icr2
suffix:semicolon
multiline_comment|/*320*/
r_struct
(brace
multiline_comment|/* LVT - Timer */
DECL|member|vector
id|u32
id|vector
suffix:colon
l_int|8
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|4
comma
DECL|member|delivery_status
id|delivery_status
suffix:colon
l_int|1
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|3
comma
DECL|member|mask
id|mask
suffix:colon
l_int|1
comma
DECL|member|timer_mode
id|timer_mode
suffix:colon
l_int|1
comma
DECL|member|__reserved_3
id|__reserved_3
suffix:colon
l_int|14
suffix:semicolon
DECL|member|__reserved_4
id|u32
id|__reserved_4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|lvt_timer
)brace
id|lvt_timer
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_15
multiline_comment|/*330*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_15
suffix:semicolon
multiline_comment|/*340*/
r_struct
(brace
multiline_comment|/* LVT - Performance Counter */
DECL|member|vector
id|u32
id|vector
suffix:colon
l_int|8
comma
DECL|member|delivery_mode
id|delivery_mode
suffix:colon
l_int|3
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|1
comma
DECL|member|delivery_status
id|delivery_status
suffix:colon
l_int|1
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|3
comma
DECL|member|mask
id|mask
suffix:colon
l_int|1
comma
DECL|member|__reserved_3
id|__reserved_3
suffix:colon
l_int|15
suffix:semicolon
DECL|member|__reserved_4
id|u32
id|__reserved_4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|lvt_pc
)brace
id|lvt_pc
suffix:semicolon
multiline_comment|/*350*/
r_struct
(brace
multiline_comment|/* LVT - LINT0 */
DECL|member|vector
id|u32
id|vector
suffix:colon
l_int|8
comma
DECL|member|delivery_mode
id|delivery_mode
suffix:colon
l_int|3
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|1
comma
DECL|member|delivery_status
id|delivery_status
suffix:colon
l_int|1
comma
DECL|member|polarity
id|polarity
suffix:colon
l_int|1
comma
DECL|member|remote_irr
id|remote_irr
suffix:colon
l_int|1
comma
DECL|member|trigger
id|trigger
suffix:colon
l_int|1
comma
DECL|member|mask
id|mask
suffix:colon
l_int|1
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|15
suffix:semicolon
DECL|member|__reserved_3
id|u32
id|__reserved_3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|lvt_lint0
)brace
id|lvt_lint0
suffix:semicolon
multiline_comment|/*360*/
r_struct
(brace
multiline_comment|/* LVT - LINT1 */
DECL|member|vector
id|u32
id|vector
suffix:colon
l_int|8
comma
DECL|member|delivery_mode
id|delivery_mode
suffix:colon
l_int|3
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|1
comma
DECL|member|delivery_status
id|delivery_status
suffix:colon
l_int|1
comma
DECL|member|polarity
id|polarity
suffix:colon
l_int|1
comma
DECL|member|remote_irr
id|remote_irr
suffix:colon
l_int|1
comma
DECL|member|trigger
id|trigger
suffix:colon
l_int|1
comma
DECL|member|mask
id|mask
suffix:colon
l_int|1
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|15
suffix:semicolon
DECL|member|__reserved_3
id|u32
id|__reserved_3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|lvt_lint1
)brace
id|lvt_lint1
suffix:semicolon
multiline_comment|/*370*/
r_struct
(brace
multiline_comment|/* LVT - Error */
DECL|member|vector
id|u32
id|vector
suffix:colon
l_int|8
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|4
comma
DECL|member|delivery_status
id|delivery_status
suffix:colon
l_int|1
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|3
comma
DECL|member|mask
id|mask
suffix:colon
l_int|1
comma
DECL|member|__reserved_3
id|__reserved_3
suffix:colon
l_int|15
suffix:semicolon
DECL|member|__reserved_4
id|u32
id|__reserved_4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|lvt_error
)brace
id|lvt_error
suffix:semicolon
multiline_comment|/*380*/
r_struct
(brace
multiline_comment|/* Timer Initial Count Register */
DECL|member|initial_count
id|u32
id|initial_count
suffix:semicolon
DECL|member|__reserved_2
id|u32
id|__reserved_2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|timer_icr
)brace
id|timer_icr
suffix:semicolon
multiline_comment|/*390*/
r_const
r_struct
(brace
multiline_comment|/* Timer Current Count Register */
DECL|member|curr_count
id|u32
id|curr_count
suffix:semicolon
DECL|member|__reserved_2
id|u32
id|__reserved_2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|timer_ccr
)brace
id|timer_ccr
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_16
multiline_comment|/*3A0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_16
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_17
multiline_comment|/*3B0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_17
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_18
multiline_comment|/*3C0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_18
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_19
multiline_comment|/*3D0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_19
suffix:semicolon
multiline_comment|/*3E0*/
r_struct
(brace
multiline_comment|/* Timer Divide Configuration Register */
DECL|member|divisor
id|u32
id|divisor
suffix:colon
l_int|4
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|28
suffix:semicolon
DECL|member|__reserved_2
id|u32
id|__reserved_2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|timer_dcr
)brace
id|timer_dcr
suffix:semicolon
DECL|member|__reserved
DECL|member|__reserved_20
multiline_comment|/*3F0*/
r_struct
(brace
id|u32
id|__reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__reserved_20
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|u32
macro_line|#undef u32
macro_line|#endif
eof