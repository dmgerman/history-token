multiline_comment|/*&n; * uninorth.h: definitions for using the &quot;UniNorth&quot; host bridge chip&n; *             from Apple. This chip is used on &quot;Core99&quot; machines&n; *&n; */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Uni-N config space reg. definitions&n; * &n; * (Little endian)&n; */
multiline_comment|/* Address ranges selection. This one should work with Bandit too */
DECL|macro|UNI_N_ADDR_SELECT
mdefine_line|#define UNI_N_ADDR_SELECT&t;&t;0x48
DECL|macro|UNI_N_ADDR_COARSE_MASK
mdefine_line|#define UNI_N_ADDR_COARSE_MASK&t;&t;0xffff0000&t;/* 256Mb regions at *0000000 */
DECL|macro|UNI_N_ADDR_FINE_MASK
mdefine_line|#define UNI_N_ADDR_FINE_MASK&t;&t;0x0000ffff&t;/*  16Mb regions at f*000000 */
multiline_comment|/* AGP registers */
DECL|macro|UNI_N_CFG_GART_BASE
mdefine_line|#define UNI_N_CFG_GART_BASE&t;&t;0x8c
DECL|macro|UNI_N_CFG_AGP_BASE
mdefine_line|#define UNI_N_CFG_AGP_BASE&t;&t;0x90
DECL|macro|UNI_N_CFG_GART_CTRL
mdefine_line|#define UNI_N_CFG_GART_CTRL&t;&t;0x94
DECL|macro|UNI_N_CFG_INTERNAL_STATUS
mdefine_line|#define UNI_N_CFG_INTERNAL_STATUS&t;0x98
multiline_comment|/* UNI_N_CFG_GART_CTRL bits definitions */
DECL|macro|UNI_N_CFG_GART_INVAL
mdefine_line|#define UNI_N_CFG_GART_INVAL&t;&t;0x00000001
DECL|macro|UNI_N_CFG_GART_ENABLE
mdefine_line|#define UNI_N_CFG_GART_ENABLE&t;&t;0x00000100
DECL|macro|UNI_N_CFG_GART_2xRESET
mdefine_line|#define UNI_N_CFG_GART_2xRESET&t;&t;0x00010000
multiline_comment|/* &n; * Uni-N memory mapped reg. definitions&n; * &n; * Those registers are Big-Endian !!&n; *&n; * Their meaning come from either Darwin and/or from experiments I made with&n; * the bootrom, I&squot;m not sure about their exact meaning yet&n; *&n; */
multiline_comment|/* Version of the UniNorth chip */
DECL|macro|UNI_N_VERSION
mdefine_line|#define UNI_N_VERSION&t;&t;&t;0x0000&t;&t;/* Known versions: 3,7 and 8 */
multiline_comment|/* This register is used to enable/disable various clocks */
DECL|macro|UNI_N_CLOCK_CNTL
mdefine_line|#define UNI_N_CLOCK_CNTL&t;&t;0x0020
DECL|macro|UNI_N_CLOCK_CNTL_PCI
mdefine_line|#define UNI_N_CLOCK_CNTL_PCI&t;&t;0x00000001&t;/* PCI2 clock control */
DECL|macro|UNI_N_CLOCK_CNTL_GMAC
mdefine_line|#define UNI_N_CLOCK_CNTL_GMAC&t;&t;0x00000002&t;/* GMAC clock control */
DECL|macro|UNI_N_CLOCK_CNTL_FW
mdefine_line|#define UNI_N_CLOCK_CNTL_FW&t;&t;0x00000004&t;/* FireWire clock control */
multiline_comment|/* Power Management control */
DECL|macro|UNI_N_POWER_MGT
mdefine_line|#define UNI_N_POWER_MGT&t;&t;&t;0x0030
DECL|macro|UNI_N_POWER_MGT_NORMAL
mdefine_line|#define UNI_N_POWER_MGT_NORMAL&t;&t;0x00
DECL|macro|UNI_N_POWER_MGT_IDLE2
mdefine_line|#define UNI_N_POWER_MGT_IDLE2&t;&t;0x01
DECL|macro|UNI_N_POWER_MGT_SLEEP
mdefine_line|#define UNI_N_POWER_MGT_SLEEP&t;&t;0x02
multiline_comment|/* This register is configured by Darwin depending on the UniN&n; * revision&n; */
DECL|macro|UNI_N_ARB_CTRL
mdefine_line|#define UNI_N_ARB_CTRL&t;&t;&t;0x0040
DECL|macro|UNI_N_ARB_CTRL_QACK_DELAY_SHIFT
mdefine_line|#define UNI_N_ARB_CTRL_QACK_DELAY_SHIFT&t;15
DECL|macro|UNI_N_ARB_CTRL_QACK_DELAY_MASK
mdefine_line|#define UNI_N_ARB_CTRL_QACK_DELAY_MASK&t;0x0e1f8000
DECL|macro|UNI_N_ARB_CTRL_QACK_DELAY
mdefine_line|#define UNI_N_ARB_CTRL_QACK_DELAY&t;0x30
DECL|macro|UNI_N_ARB_CTRL_QACK_DELAY105
mdefine_line|#define UNI_N_ARB_CTRL_QACK_DELAY105&t;0x00
multiline_comment|/* This one _might_ return the CPU number of the CPU reading it;&n; * the bootROM decides wether to boot or to sleep/spinloop depending&n; * on this register beeing 0 or not&n; */
DECL|macro|UNI_N_CPU_NUMBER
mdefine_line|#define UNI_N_CPU_NUMBER&t;&t;0x0050
multiline_comment|/* This register appear to be read by the bootROM to decide what&n; *  to do on a non-recoverable reset (powerup or wakeup)&n; */
DECL|macro|UNI_N_HWINIT_STATE
mdefine_line|#define UNI_N_HWINIT_STATE&t;&t;0x0070
DECL|macro|UNI_N_HWINIT_STATE_SLEEPING
mdefine_line|#define UNI_N_HWINIT_STATE_SLEEPING&t;0x01
DECL|macro|UNI_N_HWINIT_STATE_RUNNING
mdefine_line|#define UNI_N_HWINIT_STATE_RUNNING&t;0x02
multiline_comment|/* This last bit appear to be used by the bootROM to know the second&n; * CPU has started and will enter it&squot;s sleep loop with IP=0&n; */
DECL|macro|UNI_N_HWINIT_STATE_CPU1_FLAG
mdefine_line|#define UNI_N_HWINIT_STATE_CPU1_FLAG&t;0x10000000
multiline_comment|/* Uninorth 1.5 rev. has additional perf. monitor registers at 0xf00-0xf50 */
macro_line|#endif /* __KERNEL__ */
eof
