multiline_comment|/*&n; * uninorth.h: definitions for using the &quot;UniNorth&quot; host bridge chip&n; *             from Apple. This chip is used on &quot;Core99&quot; machines&n; *&t;       This also includes U2 used on more recent MacRISC2/3&n; *             machines and U3 (G5) &n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_UNINORTH_H__
DECL|macro|__ASM_UNINORTH_H__
mdefine_line|#define __ASM_UNINORTH_H__
multiline_comment|/*&n; * Uni-N and U3 config space reg. definitions&n; *&n; * (Little endian)&n; */
multiline_comment|/* Address ranges selection. This one should work with Bandit too */
multiline_comment|/* Not U3 */
DECL|macro|UNI_N_ADDR_SELECT
mdefine_line|#define UNI_N_ADDR_SELECT&t;&t;0x48
DECL|macro|UNI_N_ADDR_COARSE_MASK
mdefine_line|#define UNI_N_ADDR_COARSE_MASK&t;&t;0xffff0000&t;/* 256Mb regions at *0000000 */
DECL|macro|UNI_N_ADDR_FINE_MASK
mdefine_line|#define UNI_N_ADDR_FINE_MASK&t;&t;0x0000ffff&t;/*  16Mb regions at f*000000 */
multiline_comment|/* AGP registers */
multiline_comment|/* Not U3 */
DECL|macro|UNI_N_CFG_GART_BASE
mdefine_line|#define UNI_N_CFG_GART_BASE&t;&t;0x8c
DECL|macro|UNI_N_CFG_AGP_BASE
mdefine_line|#define UNI_N_CFG_AGP_BASE&t;&t;0x90
DECL|macro|UNI_N_CFG_GART_CTRL
mdefine_line|#define UNI_N_CFG_GART_CTRL&t;&t;0x94
DECL|macro|UNI_N_CFG_INTERNAL_STATUS
mdefine_line|#define UNI_N_CFG_INTERNAL_STATUS&t;0x98
multiline_comment|/* UNI_N_CFG_GART_CTRL bits definitions */
multiline_comment|/* Not U3 */
DECL|macro|UNI_N_CFG_GART_INVAL
mdefine_line|#define UNI_N_CFG_GART_INVAL&t;&t;0x00000001
DECL|macro|UNI_N_CFG_GART_ENABLE
mdefine_line|#define UNI_N_CFG_GART_ENABLE&t;&t;0x00000100
DECL|macro|UNI_N_CFG_GART_2xRESET
mdefine_line|#define UNI_N_CFG_GART_2xRESET&t;&t;0x00010000
DECL|macro|UNI_N_CFG_GART_DISSBADET
mdefine_line|#define UNI_N_CFG_GART_DISSBADET&t;0x00020000
multiline_comment|/* My understanding of UniNorth AGP as of UniNorth rev 1.0x,&n; * revision 1.5 (x4 AGP) may need further changes.&n; *&n; * AGP_BASE register contains the base address of the AGP aperture on&n; * the AGP bus. It doesn&squot;t seem to be visible to the CPU as of UniNorth 1.x,&n; * even if decoding of this address range is enabled in the address select&n; * register. Apparently, the only supported bases are 256Mb multiples&n; * (high 4 bits of that register).&n; *&n; * GART_BASE register appear to contain the physical address of the GART&n; * in system memory in the high address bits (page aligned), and the&n; * GART size in the low order bits (number of GART pages)&n; *&n; * The GART format itself is one 32bits word per physical memory page.&n; * This word contains, in little-endian format (!!!), the physical address&n; * of the page in the high bits, and what appears to be an &quot;enable&quot; bit&n; * in the LSB bit (0) that must be set to 1 when the entry is valid.&n; *&n; * Obviously, the GART is not cache coherent and so any change to it&n; * must be flushed to memory (or maybe just make the GART space non&n; * cachable). AGP memory itself doens&squot;t seem to be cache coherent neither.&n; *&n; * In order to invalidate the GART (which is probably necessary to inval&n; * the bridge internal TLBs), the following sequence has to be written,&n; * in order, to the GART_CTRL register:&n; *&n; *   UNI_N_CFG_GART_ENABLE | UNI_N_CFG_GART_INVAL&n; *   UNI_N_CFG_GART_ENABLE&n; *   UNI_N_CFG_GART_ENABLE | UNI_N_CFG_GART_2xRESET&n; *   UNI_N_CFG_GART_ENABLE&n; *&n; * As far as AGP &quot;features&quot; are concerned, it looks like fast write may&n; * not be supported but this has to be confirmed.&n; *&n; * Turning on AGP seem to require a double invalidate operation, one before&n; * setting the AGP command register, on after.&n; *&n; * Turning off AGP seems to require the following sequence: first wait&n; * for the AGP to be idle by reading the internal status register, then&n; * write in that order to the GART_CTRL register:&n; *&n; *   UNI_N_CFG_GART_ENABLE | UNI_N_CFG_GART_INVAL&n; *   0&n; *   UNI_N_CFG_GART_2xRESET&n; *   0&n; */
multiline_comment|/*&n; * Uni-N memory mapped reg. definitions&n; *&n; * Those registers are Big-Endian !!&n; *&n; * Their meaning come from either Darwin and/or from experiments I made with&n; * the bootrom, I&squot;m not sure about their exact meaning yet&n; *&n; */
multiline_comment|/* Version of the UniNorth chip */
DECL|macro|UNI_N_VERSION
mdefine_line|#define UNI_N_VERSION&t;&t;&t;0x0000&t;&t;/* Known versions: 3,7 and 8 */
DECL|macro|UNI_N_VERSION_107
mdefine_line|#define UNI_N_VERSION_107&t;&t;0x0003&t;&t;/* 1.0.7 */
DECL|macro|UNI_N_VERSION_10A
mdefine_line|#define UNI_N_VERSION_10A&t;&t;0x0007&t;&t;/* 1.0.10 */
DECL|macro|UNI_N_VERSION_150
mdefine_line|#define UNI_N_VERSION_150&t;&t;0x0011&t;&t;/* 1.5 */
DECL|macro|UNI_N_VERSION_200
mdefine_line|#define UNI_N_VERSION_200&t;&t;0x0024&t;&t;/* 2.0 */
DECL|macro|UNI_N_VERSION_PANGEA
mdefine_line|#define UNI_N_VERSION_PANGEA&t;&t;0x00C0&t;&t;/* Integrated U1 + K */
DECL|macro|UNI_N_VERSION_INTREPID
mdefine_line|#define UNI_N_VERSION_INTREPID&t;&t;0x00D2&t;&t;/* Integrated U2 + K */
DECL|macro|UNI_N_VERSION_300
mdefine_line|#define UNI_N_VERSION_300&t;&t;0x0030&t;&t;/* 3.0 (U3 on G5) */
multiline_comment|/* This register is used to enable/disable various clocks */
DECL|macro|UNI_N_CLOCK_CNTL
mdefine_line|#define UNI_N_CLOCK_CNTL&t;&t;0x0020
DECL|macro|UNI_N_CLOCK_CNTL_PCI
mdefine_line|#define UNI_N_CLOCK_CNTL_PCI&t;&t;0x00000001&t;/* PCI2 clock control */
DECL|macro|UNI_N_CLOCK_CNTL_GMAC
mdefine_line|#define UNI_N_CLOCK_CNTL_GMAC&t;&t;0x00000002&t;/* GMAC clock control */
DECL|macro|UNI_N_CLOCK_CNTL_FW
mdefine_line|#define UNI_N_CLOCK_CNTL_FW&t;&t;0x00000004&t;/* FireWire clock control */
DECL|macro|UNI_N_CLOCK_CNTL_ATA100
mdefine_line|#define UNI_N_CLOCK_CNTL_ATA100&t;&t;0x00000010&t;/* ATA-100 clock control (U2) */
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
multiline_comment|/* This one _might_ return the CPU number of the CPU reading it;&n; * the bootROM decides whether to boot or to sleep/spinloop depending&n; * on this register beeing 0 or not&n; */
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
multiline_comment|/* This register controls AACK delay, which is set when 2004 iBook/PowerBook&n; * is in low speed mode.&n; */
DECL|macro|UNI_N_AACK_DELAY
mdefine_line|#define UNI_N_AACK_DELAY&t;&t;0x0100
DECL|macro|UNI_N_AACK_DELAY_ENABLE
mdefine_line|#define UNI_N_AACK_DELAY_ENABLE&t;&t;0x00000001
multiline_comment|/* Clock status for Intrepid */
DECL|macro|UNI_N_CLOCK_STOP_STATUS0
mdefine_line|#define UNI_N_CLOCK_STOP_STATUS0&t;0x0150
DECL|macro|UNI_N_CLOCK_STOPPED_EXTAGP
mdefine_line|#define UNI_N_CLOCK_STOPPED_EXTAGP&t;0x00200000
DECL|macro|UNI_N_CLOCK_STOPPED_AGPDEL
mdefine_line|#define UNI_N_CLOCK_STOPPED_AGPDEL&t;0x00100000
DECL|macro|UNI_N_CLOCK_STOPPED_I2S0_45_49
mdefine_line|#define UNI_N_CLOCK_STOPPED_I2S0_45_49&t;0x00080000
DECL|macro|UNI_N_CLOCK_STOPPED_I2S0_18
mdefine_line|#define UNI_N_CLOCK_STOPPED_I2S0_18&t;0x00040000
DECL|macro|UNI_N_CLOCK_STOPPED_I2S1_45_49
mdefine_line|#define UNI_N_CLOCK_STOPPED_I2S1_45_49&t;0x00020000
DECL|macro|UNI_N_CLOCK_STOPPED_I2S1_18
mdefine_line|#define UNI_N_CLOCK_STOPPED_I2S1_18&t;0x00010000
DECL|macro|UNI_N_CLOCK_STOPPED_TIMER
mdefine_line|#define UNI_N_CLOCK_STOPPED_TIMER&t;0x00008000
DECL|macro|UNI_N_CLOCK_STOPPED_SCC_RTCLK18
mdefine_line|#define UNI_N_CLOCK_STOPPED_SCC_RTCLK18&t;0x00004000
DECL|macro|UNI_N_CLOCK_STOPPED_SCC_RTCLK32
mdefine_line|#define UNI_N_CLOCK_STOPPED_SCC_RTCLK32&t;0x00002000
DECL|macro|UNI_N_CLOCK_STOPPED_SCC_VIA32
mdefine_line|#define UNI_N_CLOCK_STOPPED_SCC_VIA32&t;0x00001000
DECL|macro|UNI_N_CLOCK_STOPPED_SCC_SLOT0
mdefine_line|#define UNI_N_CLOCK_STOPPED_SCC_SLOT0&t;0x00000800
DECL|macro|UNI_N_CLOCK_STOPPED_SCC_SLOT1
mdefine_line|#define UNI_N_CLOCK_STOPPED_SCC_SLOT1&t;0x00000400
DECL|macro|UNI_N_CLOCK_STOPPED_SCC_SLOT2
mdefine_line|#define UNI_N_CLOCK_STOPPED_SCC_SLOT2&t;0x00000200
DECL|macro|UNI_N_CLOCK_STOPPED_PCI_FBCLKO
mdefine_line|#define UNI_N_CLOCK_STOPPED_PCI_FBCLKO&t;0x00000100
DECL|macro|UNI_N_CLOCK_STOPPED_VEO0
mdefine_line|#define UNI_N_CLOCK_STOPPED_VEO0&t;0x00000080
DECL|macro|UNI_N_CLOCK_STOPPED_VEO1
mdefine_line|#define UNI_N_CLOCK_STOPPED_VEO1&t;0x00000040
DECL|macro|UNI_N_CLOCK_STOPPED_USB0
mdefine_line|#define UNI_N_CLOCK_STOPPED_USB0&t;0x00000020
DECL|macro|UNI_N_CLOCK_STOPPED_USB1
mdefine_line|#define UNI_N_CLOCK_STOPPED_USB1&t;0x00000010
DECL|macro|UNI_N_CLOCK_STOPPED_USB2
mdefine_line|#define UNI_N_CLOCK_STOPPED_USB2&t;0x00000008
DECL|macro|UNI_N_CLOCK_STOPPED_32
mdefine_line|#define UNI_N_CLOCK_STOPPED_32&t;&t;0x00000004
DECL|macro|UNI_N_CLOCK_STOPPED_45
mdefine_line|#define UNI_N_CLOCK_STOPPED_45&t;&t;0x00000002
DECL|macro|UNI_N_CLOCK_STOPPED_49
mdefine_line|#define UNI_N_CLOCK_STOPPED_49&t;&t;0x00000001
DECL|macro|UNI_N_CLOCK_STOP_STATUS1
mdefine_line|#define UNI_N_CLOCK_STOP_STATUS1&t;0x0160
DECL|macro|UNI_N_CLOCK_STOPPED_PLL4REF
mdefine_line|#define UNI_N_CLOCK_STOPPED_PLL4REF&t;0x00080000
DECL|macro|UNI_N_CLOCK_STOPPED_CPUDEL
mdefine_line|#define UNI_N_CLOCK_STOPPED_CPUDEL&t;0x00040000
DECL|macro|UNI_N_CLOCK_STOPPED_CPU
mdefine_line|#define UNI_N_CLOCK_STOPPED_CPU&t;&t;0x00020000
DECL|macro|UNI_N_CLOCK_STOPPED_BUF_REFCKO
mdefine_line|#define UNI_N_CLOCK_STOPPED_BUF_REFCKO&t;0x00010000
DECL|macro|UNI_N_CLOCK_STOPPED_PCI2
mdefine_line|#define UNI_N_CLOCK_STOPPED_PCI2&t;0x00008000
DECL|macro|UNI_N_CLOCK_STOPPED_FW
mdefine_line|#define UNI_N_CLOCK_STOPPED_FW&t;&t;0x00004000
DECL|macro|UNI_N_CLOCK_STOPPED_GB
mdefine_line|#define UNI_N_CLOCK_STOPPED_GB&t;&t;0x00002000
DECL|macro|UNI_N_CLOCK_STOPPED_ATA66
mdefine_line|#define UNI_N_CLOCK_STOPPED_ATA66&t;0x00001000
DECL|macro|UNI_N_CLOCK_STOPPED_ATA100
mdefine_line|#define UNI_N_CLOCK_STOPPED_ATA100&t;0x00000800
DECL|macro|UNI_N_CLOCK_STOPPED_MAX
mdefine_line|#define UNI_N_CLOCK_STOPPED_MAX&t;&t;0x00000400
DECL|macro|UNI_N_CLOCK_STOPPED_PCI1
mdefine_line|#define UNI_N_CLOCK_STOPPED_PCI1&t;0x00000200
DECL|macro|UNI_N_CLOCK_STOPPED_KLPCI
mdefine_line|#define UNI_N_CLOCK_STOPPED_KLPCI&t;0x00000100
DECL|macro|UNI_N_CLOCK_STOPPED_USB0PCI
mdefine_line|#define UNI_N_CLOCK_STOPPED_USB0PCI&t;0x00000080
DECL|macro|UNI_N_CLOCK_STOPPED_USB1PCI
mdefine_line|#define UNI_N_CLOCK_STOPPED_USB1PCI&t;0x00000040
DECL|macro|UNI_N_CLOCK_STOPPED_USB2PCI
mdefine_line|#define UNI_N_CLOCK_STOPPED_USB2PCI&t;0x00000020
DECL|macro|UNI_N_CLOCK_STOPPED_7PCI1
mdefine_line|#define UNI_N_CLOCK_STOPPED_7PCI1&t;0x00000008
DECL|macro|UNI_N_CLOCK_STOPPED_AGP
mdefine_line|#define UNI_N_CLOCK_STOPPED_AGP&t;&t;0x00000004
DECL|macro|UNI_N_CLOCK_STOPPED_PCI0
mdefine_line|#define UNI_N_CLOCK_STOPPED_PCI0&t;0x00000002
DECL|macro|UNI_N_CLOCK_STOPPED_18
mdefine_line|#define UNI_N_CLOCK_STOPPED_18&t;&t;0x00000001
multiline_comment|/* Intrepid registe to OF do-platform-clockspreading */
DECL|macro|UNI_N_CLOCK_SPREADING
mdefine_line|#define UNI_N_CLOCK_SPREADING&t;&t;0x190
multiline_comment|/* Uninorth 1.5 rev. has additional perf. monitor registers at 0xf00-0xf50 */
multiline_comment|/*&n; * U3 specific registers&n; */
multiline_comment|/* U3 Toggle */
DECL|macro|U3_TOGGLE_REG
mdefine_line|#define U3_TOGGLE_REG&t;&t;&t;0x00e0
DECL|macro|U3_PMC_START_STOP
mdefine_line|#define U3_PMC_START_STOP&t;&t;0x0001
DECL|macro|U3_MPIC_RESET
mdefine_line|#define U3_MPIC_RESET&t;&t;&t;0x0002
DECL|macro|U3_MPIC_OUTPUT_ENABLE
mdefine_line|#define U3_MPIC_OUTPUT_ENABLE&t;&t;0x0004
multiline_comment|/* U3 API PHY Config 1 */
DECL|macro|U3_API_PHY_CONFIG_1
mdefine_line|#define U3_API_PHY_CONFIG_1&t;&t;0x23030
multiline_comment|/* U3 HyperTransport registers */
DECL|macro|U3_HT_CONFIG_BASE
mdefine_line|#define U3_HT_CONFIG_BASE      &t;&t;0x70000
DECL|macro|U3_HT_LINK_COMMAND
mdefine_line|#define U3_HT_LINK_COMMAND&t;&t;0x100
DECL|macro|U3_HT_LINK_CONFIG
mdefine_line|#define U3_HT_LINK_CONFIG&t;&t;0x110
DECL|macro|U3_HT_LINK_FREQ
mdefine_line|#define U3_HT_LINK_FREQ&t;&t;&t;0x120
macro_line|#endif /* __ASM_UNINORTH_H__ */
macro_line|#endif /* __KERNEL__ */
eof
