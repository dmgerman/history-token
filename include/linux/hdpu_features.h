macro_line|#include &lt;linux/spinlock.h&gt;
DECL|struct|cpustate_t
r_struct
id|cpustate_t
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|excl
r_int
id|excl
suffix:semicolon
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
DECL|member|cached_val
r_int
r_char
id|cached_val
suffix:semicolon
DECL|member|inited
r_int
id|inited
suffix:semicolon
DECL|member|set_addr
r_int
r_int
op_star
id|set_addr
suffix:semicolon
DECL|member|clr_addr
r_int
r_int
op_star
id|clr_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HDPU_CPUSTATE_NAME
mdefine_line|#define HDPU_CPUSTATE_NAME &quot;hdpu cpustate&quot;
DECL|macro|HDPU_NEXUS_NAME
mdefine_line|#define HDPU_NEXUS_NAME &quot;hdpu nexus&quot;
DECL|macro|CPUSTATE_KERNEL_MAJOR
mdefine_line|#define CPUSTATE_KERNEL_MAJOR  0x10
DECL|macro|CPUSTATE_KERNEL_INIT_DRV
mdefine_line|#define CPUSTATE_KERNEL_INIT_DRV   0 /* CPU State Driver Initialized */
DECL|macro|CPUSTATE_KERNEL_INIT_PCI
mdefine_line|#define CPUSTATE_KERNEL_INIT_PCI   1 /* 64360 PCI Busses Init */
DECL|macro|CPUSTATE_KERNEL_INIT_REG
mdefine_line|#define CPUSTATE_KERNEL_INIT_REG   2 /* 64360 Bridge Init */
DECL|macro|CPUSTATE_KERNEL_CPU1_KICK
mdefine_line|#define CPUSTATE_KERNEL_CPU1_KICK  3 /* Boot cpu 1 */
DECL|macro|CPUSTATE_KERNEL_CPU1_OK
mdefine_line|#define CPUSTATE_KERNEL_CPU1_OK    4  /* Cpu 1 has checked in */
DECL|macro|CPUSTATE_KERNEL_OK
mdefine_line|#define CPUSTATE_KERNEL_OK         5 /* Terminal state */
DECL|macro|CPUSTATE_KERNEL_RESET
mdefine_line|#define CPUSTATE_KERNEL_RESET   14 /* Board reset via SW*/
DECL|macro|CPUSTATE_KERNEL_HALT
mdefine_line|#define CPUSTATE_KERNEL_HALT   15 /* Board halted via SW*/
eof
