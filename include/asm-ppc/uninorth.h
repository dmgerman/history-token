multiline_comment|/*&n; * BK Id: SCCS/s.uninorth.h 1.11 08/19/01 22:23:04 paulus&n; */
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
multiline_comment|/* My understanding of UniNorth AGP as of UniNorth rev 1.0x,&n; * revision 1.5 (x4 AGP) may need further changes.&n; * &n; * AGP_BASE register contains the base address of the AGP aperture on&n; * the AGP bus. It doesn&squot;t seem to be visible to the CPU as of UniNorth 1.x,&n; * even if decoding of this address range is enabled in the address select&n; * register. Apparently, the only supported bases are 256Mb multiples&n; * (high 4 bits of that register).&n; * &n; * GART_BASE register appear to contain the physical address of the GART&n; * in system memory in the high address bits (page aligned), and the&n; * GART size in the low order bits (number of GART pages)&n; *&n; * The GART format itself is one 32bits word per physical memory page.&n; * This word contains, in little-endian format (!!!), the physical address&n; * of the page in the high bits, and what appears to be an &quot;enable&quot; bit&n; * in the LSB bit (0) that must be set to 1 when the entry is valid.&n; * &n; * Obviously, the GART is not cache coherent and so any change to it&n; * must be flushed to memory (or maybe just make the GART space non&n; * cachable). AGP memory itself doens&squot;t seem to be cache coherent neither.&n; * &n; * In order to invalidate the GART (which is probably necessary to inval&n; * the bridge internal TLBs), the following sequence has to be written,&n; * in order, to the GART_CTRL register:&n; * &n; *   UNI_N_CFG_GART_ENABLE | UNI_N_CFG_GART_INVAL&n; *   UNI_N_CFG_GART_ENABLE&n; *   UNI_N_CFG_GART_ENABLE | UNI_N_CFG_GART_2xRESET&n; *   UNI_N_CFG_GART_ENABLE&n; *   &n; * As far as AGP &quot;features&quot; are concerned, it looks like fast write may&n; * not be supported but this has to be confirmed.&n; * &n; * Turning on AGP seem to require a double invalidate operation, one before&n; * setting the AGP command register, on after.&n; * &n; * Turning off AGP seems to require the following sequence: first wait&n; * for the AGP to be idle by reading the internal status register, then&n; * write in that order to the GART_CTRL register:&n; * &n; *   UNI_N_CFG_GART_ENABLE | UNI_N_CFG_GART_INVAL&n; *   0&n; *   UNI_N_CFG_GART_2xRESET&n; *   0&n; */
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
