multiline_comment|/* $Id: bbc.h,v 1.1 2001/03/24 06:03:03 davem Exp $&n; * bbc.h: Defines for BootBus Controller found on UltraSPARC-III&n; *        systems.&n; *&n; * Copyright (C) 2000 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef _SPARC64_BBC_H
DECL|macro|_SPARC64_BBC_H
mdefine_line|#define _SPARC64_BBC_H
multiline_comment|/* Register sizes are indicated by &quot;B&quot; (Byte, 1-byte),&n; * &quot;H&quot; (Half-word, 2 bytes), &quot;W&quot; (Word, 4 bytes) or&n; * &quot;Q&quot; (Quad, 8 bytes) inside brackets.&n; */
DECL|macro|BBC_AID
mdefine_line|#define BBC_AID&t;&t;0x00&t;/* [B] Agent ID&t;&t;&t;*/
DECL|macro|BBC_DEVP
mdefine_line|#define BBC_DEVP&t;0x01&t;/* [B] Device Present&t;&t;*/
DECL|macro|BBC_ARB
mdefine_line|#define BBC_ARB&t;&t;0x02&t;/* [B] Arbitration&t;&t;*/
DECL|macro|BBC_QUIESCE
mdefine_line|#define BBC_QUIESCE&t;0x03&t;/* [B] Quiesce&t;&t;&t;*/
DECL|macro|BBC_WDACTION
mdefine_line|#define BBC_WDACTION&t;0x04&t;/* [B] Watchdog Action&t;&t;*/
DECL|macro|BBC_SPG
mdefine_line|#define BBC_SPG&t;&t;0x06&t;/* [B] Soft POR Gen&t;&t;*/
DECL|macro|BBC_SXG
mdefine_line|#define BBC_SXG&t;&t;0x07&t;/* [B] Soft XIR Gen&t;&t;*/
DECL|macro|BBC_PSRC
mdefine_line|#define BBC_PSRC&t;0x08&t;/* [W] POR Source&t;&t;*/
DECL|macro|BBC_XSRC
mdefine_line|#define BBC_XSRC&t;0x0c&t;/* [B] XIR Source&t;&t;*/
DECL|macro|BBC_CSC
mdefine_line|#define BBC_CSC&t;&t;0x0d&t;/* [B] Clock Synthesizers Control*/
DECL|macro|BBC_ES_CTRL
mdefine_line|#define BBC_ES_CTRL&t;0x0e&t;/* [H] Energy Star Control&t;*/
DECL|macro|BBC_ES_ACT
mdefine_line|#define BBC_ES_ACT&t;0x10&t;/* [W] E* Assert Change Time&t;*/
DECL|macro|BBC_ES_DACT
mdefine_line|#define BBC_ES_DACT&t;0x14&t;/* [B] E* De-Assert Change Time&t;*/
DECL|macro|BBC_ES_DABT
mdefine_line|#define BBC_ES_DABT&t;0x15&t;/* [B] E* De-Assert Bypass Time&t;*/
DECL|macro|BBC_ES_ABT
mdefine_line|#define BBC_ES_ABT&t;0x16&t;/* [H] E* Assert Bypass Time&t;*/
DECL|macro|BBC_ES_PST
mdefine_line|#define BBC_ES_PST&t;0x18&t;/* [W] E* PLL Settle Time&t;*/
DECL|macro|BBC_ES_FSL
mdefine_line|#define BBC_ES_FSL&t;0x1c&t;/* [W] E* Frequency Switch Latency*/
DECL|macro|BBC_EBUST
mdefine_line|#define BBC_EBUST&t;0x20&t;/* [Q] EBUS Timing&t;&t;*/
DECL|macro|BBC_JTAG_CMD
mdefine_line|#define BBC_JTAG_CMD&t;0x28&t;/* [W] JTAG+ Command&t;&t;*/
DECL|macro|BBC_JTAG_CTRL
mdefine_line|#define BBC_JTAG_CTRL&t;0x2c&t;/* [B] JTAG+ Control&t;&t;*/
DECL|macro|BBC_I2C_SEL
mdefine_line|#define BBC_I2C_SEL&t;0x2d&t;/* [B] I2C Selection&t;&t;*/
DECL|macro|BBC_I2C_0_S1
mdefine_line|#define BBC_I2C_0_S1&t;0x2e&t;/* [B] I2C ctrlr-0 reg S1&t;*/
DECL|macro|BBC_I2C_0_S0
mdefine_line|#define BBC_I2C_0_S0&t;0x2f&t;/* [B] I2C ctrlr-0 regs S0,S0&squot;,S2,S3*/
DECL|macro|BBC_I2C_1_S1
mdefine_line|#define BBC_I2C_1_S1&t;0x30&t;/* [B] I2C ctrlr-1 reg S1&t;*/
DECL|macro|BBC_I2C_1_S0
mdefine_line|#define BBC_I2C_1_S0&t;0x31&t;/* [B] I2C ctrlr-1 regs S0,S0&squot;,S2,S3*/
DECL|macro|BBC_KBD_BEEP
mdefine_line|#define BBC_KBD_BEEP&t;0x32&t;/* [B] Keyboard Beep&t;&t;*/
DECL|macro|BBC_KBD_BCNT
mdefine_line|#define BBC_KBD_BCNT&t;0x34&t;/* [W] Keyboard Beep Counter&t;*/
DECL|macro|BBC_REGS_SIZE
mdefine_line|#define BBC_REGS_SIZE&t;0x40
multiline_comment|/* There is a 2K scratch ram area at offset 0x80000 but I doubt&n; * we will use it for anything.&n; */
multiline_comment|/* Agent ID register.  This register shows the Safari Agent ID&n; * for the processors.  The value returned depends upon which&n; * cpu is reading the register.&n; */
DECL|macro|BBC_AID_ID
mdefine_line|#define BBC_AID_ID&t;0x07&t;/* Safari ID&t;&t;*/
DECL|macro|BBC_AID_RESV
mdefine_line|#define BBC_AID_RESV&t;0xf8&t;/* Reserved&t;&t;*/
multiline_comment|/* Device Present register.  One can determine which cpus are actually&n; * present in the machine by interrogating this register.&n; */
DECL|macro|BBC_DEVP_CPU0
mdefine_line|#define BBC_DEVP_CPU0&t;0x01&t;/* Processor 0 present&t;*/
DECL|macro|BBC_DEVP_CPU1
mdefine_line|#define BBC_DEVP_CPU1&t;0x02&t;/* Processor 1 present&t;*/
DECL|macro|BBC_DEVP_CPU2
mdefine_line|#define BBC_DEVP_CPU2&t;0x04&t;/* Processor 2 present&t;*/
DECL|macro|BBC_DEVP_CPU3
mdefine_line|#define BBC_DEVP_CPU3&t;0x08&t;/* Processor 3 present&t;*/
DECL|macro|BBC_DEVP_RESV
mdefine_line|#define BBC_DEVP_RESV&t;0xf0&t;/* Reserved&t;&t;*/
multiline_comment|/* Arbitration register.  This register is used to block access to&n; * the BBC from a particular cpu.&n; */
DECL|macro|BBC_ARB_CPU0
mdefine_line|#define BBC_ARB_CPU0&t;0x01&t;/* Enable cpu 0 BBC arbitratrion */
DECL|macro|BBC_ARB_CPU1
mdefine_line|#define BBC_ARB_CPU1&t;0x02&t;/* Enable cpu 1 BBC arbitratrion */
DECL|macro|BBC_ARB_CPU2
mdefine_line|#define BBC_ARB_CPU2&t;0x04&t;/* Enable cpu 2 BBC arbitratrion */
DECL|macro|BBC_ARB_CPU3
mdefine_line|#define BBC_ARB_CPU3&t;0x08&t;/* Enable cpu 3 BBC arbitratrion */
DECL|macro|BBC_ARB_RESV
mdefine_line|#define BBC_ARB_RESV&t;0xf0&t;/* Reserved&t;&t;&t; */
multiline_comment|/* Quiesce register.  Bus and BBC segments for cpus can be disabled&n; * with this register, ie. for hot plugging.&n; */
DECL|macro|BBC_QUIESCE_S02
mdefine_line|#define BBC_QUIESCE_S02&t;0x01&t;/* Quiesce Safari segment for cpu 0 and 2 */
DECL|macro|BBC_QUIESCE_S13
mdefine_line|#define BBC_QUIESCE_S13&t;0x02&t;/* Quiesce Safari segment for cpu 1 and 3 */
DECL|macro|BBC_QUIESCE_B02
mdefine_line|#define BBC_QUIESCE_B02&t;0x04&t;/* Quiesce BBC segment for cpu 0 and 2    */
DECL|macro|BBC_QUIESCE_B13
mdefine_line|#define BBC_QUIESCE_B13&t;0x08&t;/* Quiesce BBC segment for cpu 1 and 3    */
DECL|macro|BBC_QUIESCE_FD0
mdefine_line|#define BBC_QUIESCE_FD0 0x10&t;/* Disable Fatal_Error[0] reporting&t;  */
DECL|macro|BBC_QUIESCE_FD1
mdefine_line|#define BBC_QUIESCE_FD1 0x20&t;/* Disable Fatal_Error[1] reporting&t;  */
DECL|macro|BBC_QUIESCE_FD2
mdefine_line|#define BBC_QUIESCE_FD2 0x40&t;/* Disable Fatal_Error[2] reporting&t;  */
DECL|macro|BBC_QUIESCE_FD3
mdefine_line|#define BBC_QUIESCE_FD3 0x80&t;/* Disable Fatal_Error[3] reporting&t;  */
multiline_comment|/* Watchdog Action register.  When the watchdog device timer expires&n; * a line is enabled to the BBC.  The action BBC takes when this line&n; * is asserted can be controlled by this regiser.&n; */
DECL|macro|BBC_WDACTION_RST
mdefine_line|#define BBC_WDACTION_RST  0x01&t;/* When set, watchdog causes system reset.&n;&t;&t;&t;&t; * When clear, all cpus receive XIR reset.&n;&t;&t;&t;&t; */
DECL|macro|BBC_WDACTION_RESV
mdefine_line|#define BBC_WDACTION_RESV 0xfe&t;/* Reserved */
multiline_comment|/* Soft_POR_GEN register.  The POR (Power On Reset) signal may be asserted&n; * for specific processors or all processors via this register.&n; */
DECL|macro|BBC_SPG_CPU0
mdefine_line|#define BBC_SPG_CPU0&t;0x01 /* Assert POR for processor 0&t;*/
DECL|macro|BBC_SPG_CPU1
mdefine_line|#define BBC_SPG_CPU1&t;0x02 /* Assert POR for processor 1&t;*/
DECL|macro|BBC_SPG_CPU2
mdefine_line|#define BBC_SPG_CPU2&t;0x04 /* Assert POR for processor 2&t;*/
DECL|macro|BBC_SPG_CPU3
mdefine_line|#define BBC_SPG_CPU3&t;0x08 /* Assert POR for processor 3&t;*/
DECL|macro|BBC_SPG_CPUALL
mdefine_line|#define BBC_SPG_CPUALL&t;0x10 /* Reset all processors and reset&n;&t;&t;&t;      * the entire system.&n;&t;&t;&t;      */
DECL|macro|BBC_SPG_RESV
mdefine_line|#define BBC_SPG_RESV&t;0xe0 /* Reserved&t;&t;&t;*/
multiline_comment|/* Soft_XIR_GEN register.  The XIR (eXternally Initiated Reset) signal&n; * may be asserted to specific processors via this register.&n; */
DECL|macro|BBC_SXG_CPU0
mdefine_line|#define BBC_SXG_CPU0&t;0x01 /* Assert XIR for processor 0&t;*/
DECL|macro|BBC_SXG_CPU1
mdefine_line|#define BBC_SXG_CPU1&t;0x02 /* Assert XIR for processor 1&t;*/
DECL|macro|BBC_SXG_CPU2
mdefine_line|#define BBC_SXG_CPU2&t;0x04 /* Assert XIR for processor 2&t;*/
DECL|macro|BBC_SXG_CPU3
mdefine_line|#define BBC_SXG_CPU3&t;0x08 /* Assert XIR for processor 3&t;*/
DECL|macro|BBC_SXG_RESV
mdefine_line|#define BBC_SXG_RESV&t;0xf0 /* Reserved&t;&t;&t;*/
multiline_comment|/* POR Source register.  One may identify the cause of the most recent&n; * reset by reading this register.&n; */
DECL|macro|BBC_PSRC_SPG0
mdefine_line|#define BBC_PSRC_SPG0&t;0x0001 /* CPU 0 reset via BBC_SPG register&t;*/
DECL|macro|BBC_PSRC_SPG1
mdefine_line|#define BBC_PSRC_SPG1&t;0x0002 /* CPU 1 reset via BBC_SPG register&t;*/
DECL|macro|BBC_PSRC_SPG2
mdefine_line|#define BBC_PSRC_SPG2&t;0x0004 /* CPU 2 reset via BBC_SPG register&t;*/
DECL|macro|BBC_PSRC_SPG3
mdefine_line|#define BBC_PSRC_SPG3&t;0x0008 /* CPU 3 reset via BBC_SPG register&t;*/
DECL|macro|BBC_PSRC_SPGSYS
mdefine_line|#define BBC_PSRC_SPGSYS&t;0x0010 /* System reset via BBC_SPG register&t;*/
DECL|macro|BBC_PSRC_JTAG
mdefine_line|#define BBC_PSRC_JTAG&t;0x0020 /* System reset via JTAG+&t;&t;*/
DECL|macro|BBC_PSRC_BUTTON
mdefine_line|#define BBC_PSRC_BUTTON&t;0x0040 /* System reset via push-button dongle&t;*/
DECL|macro|BBC_PSRC_PWRUP
mdefine_line|#define BBC_PSRC_PWRUP&t;0x0080 /* System reset via power-up&t;&t;*/
DECL|macro|BBC_PSRC_FE0
mdefine_line|#define BBC_PSRC_FE0&t;0x0100 /* CPU 0 reported Fatal_Error&t;&t;*/
DECL|macro|BBC_PSRC_FE1
mdefine_line|#define BBC_PSRC_FE1&t;0x0200 /* CPU 1 reported Fatal_Error&t;&t;*/
DECL|macro|BBC_PSRC_FE2
mdefine_line|#define BBC_PSRC_FE2&t;0x0400 /* CPU 2 reported Fatal_Error&t;&t;*/
DECL|macro|BBC_PSRC_FE3
mdefine_line|#define BBC_PSRC_FE3&t;0x0800 /* CPU 3 reported Fatal_Error&t;&t;*/
DECL|macro|BBC_PSRC_FE4
mdefine_line|#define BBC_PSRC_FE4&t;0x1000 /* Schizo reported Fatal_Error&t;&t;*/
DECL|macro|BBC_PSRC_FE5
mdefine_line|#define BBC_PSRC_FE5&t;0x2000 /* Safari device 5 reported Fatal_Error&t;*/
DECL|macro|BBC_PSRC_FE6
mdefine_line|#define BBC_PSRC_FE6&t;0x4000 /* CPMS reported Fatal_Error&t;&t;*/
DECL|macro|BBC_PSRC_SYNTH
mdefine_line|#define BBC_PSRC_SYNTH&t;0x8000 /* System reset when on-board clock synthesizers&n;&t;&t;&t;&t;* were updated.&n;&t;&t;&t;&t;*/
DECL|macro|BBC_PSRC_WDT
mdefine_line|#define BBC_PSRC_WDT   0x10000 /* System reset via Super I/O watchdog&t;*/
DECL|macro|BBC_PSRC_RSC
mdefine_line|#define BBC_PSRC_RSC   0x20000 /* System reset via RSC remote monitoring&n;&t;&t;&t;&t;* device&n;&t;&t;&t;&t;*/
multiline_comment|/* XIR Source register.  The source of an XIR event sent to a processor may&n; * be determined via this register.&n; */
DECL|macro|BBC_XSRC_SXG0
mdefine_line|#define BBC_XSRC_SXG0&t;0x01&t;/* CPU 0 received XIR via Soft_XIR_GEN reg */
DECL|macro|BBC_XSRC_SXG1
mdefine_line|#define BBC_XSRC_SXG1&t;0x02&t;/* CPU 1 received XIR via Soft_XIR_GEN reg */
DECL|macro|BBC_XSRC_SXG2
mdefine_line|#define BBC_XSRC_SXG2&t;0x04&t;/* CPU 2 received XIR via Soft_XIR_GEN reg */
DECL|macro|BBC_XSRC_SXG3
mdefine_line|#define BBC_XSRC_SXG3&t;0x08&t;/* CPU 3 received XIR via Soft_XIR_GEN reg */
DECL|macro|BBC_XSRC_JTAG
mdefine_line|#define BBC_XSRC_JTAG&t;0x10&t;/* All CPUs received XIR via JTAG+         */
DECL|macro|BBC_XSRC_W_OR_B
mdefine_line|#define BBC_XSRC_W_OR_B&t;0x20&t;/* All CPUs received XIR either because:&n;&t;&t;&t;&t; * a) Super I/O watchdog fired, or&n;&t;&t;&t;&t; * b) XIR push button was activated&n;&t;&t;&t;&t; */
DECL|macro|BBC_XSRC_RESV
mdefine_line|#define BBC_XSRC_RESV&t;0xc0&t;/* Reserved&t;&t;&t;&t;   */
multiline_comment|/* Clock Synthesizers Control register.  This register provides the big-bang&n; * programming interface to the two clock synthesizers of the machine.&n; */
DECL|macro|BBC_CSC_SLOAD
mdefine_line|#define BBC_CSC_SLOAD&t;0x01&t;/* Directly connected to S_LOAD pins&t;*/
DECL|macro|BBC_CSC_SDATA
mdefine_line|#define BBC_CSC_SDATA&t;0x02&t;/* Directly connected to S_DATA pins&t;*/
DECL|macro|BBC_CSC_SCLOCK
mdefine_line|#define BBC_CSC_SCLOCK&t;0x04&t;/* Directly connected to S_CLOCK pins&t;*/
DECL|macro|BBC_CSC_RESV
mdefine_line|#define BBC_CSC_RESV&t;0x78&t;/* Reserved&t;&t;&t;&t;*/
DECL|macro|BBC_CSC_RST
mdefine_line|#define BBC_CSC_RST&t;0x80&t;/* Generate system reset when S_LOAD==1&t;*/
multiline_comment|/* Energy Star Control register.  This register is used to generate the&n; * clock frequency change trigger to the main system devices (Schizo and&n; * the processors).  The transition occurs when bits in this register&n; * go from 0 to 1, only one bit must be set at once else no action&n; * occurs.  Basically the sequence of events is:&n; * a) Choose new frequency: full, 1/2 or 1/32&n; * b) Program this desired frequency into the cpus and Schizo.&n; * c) Set the same value in this register.&n; * d) 16 system clocks later, clear this register.&n; */
DECL|macro|BBC_ES_CTRL_1_1
mdefine_line|#define BBC_ES_CTRL_1_1&t;&t;0x01&t;/* Full frequency&t;*/
DECL|macro|BBC_ES_CTRL_1_2
mdefine_line|#define BBC_ES_CTRL_1_2&t;&t;0x02&t;/* 1/2 frequency&t;*/
DECL|macro|BBC_ES_CTRL_1_32
mdefine_line|#define BBC_ES_CTRL_1_32&t;0x20&t;/* 1/32 frequency&t;*/
DECL|macro|BBC_ES_RESV
mdefine_line|#define BBC_ES_RESV&t;&t;0xdc&t;/* Reserved&t;&t;*/
multiline_comment|/* Energy Star Assert Change Time register.  This determines the number&n; * of BBC clock cycles (which is half the system frequency) between&n; * the detection of FREEZE_ACK being asserted and the assertion of&n; * the CLK_CHANGE_L[2:0] signals.&n; */
DECL|macro|BBC_ES_ACT_VAL
mdefine_line|#define BBC_ES_ACT_VAL&t;0xff
multiline_comment|/* Energy Star Assert Bypass Time register.  This determines the number&n; * of BBC clock cycles (which is half the system frequency) between&n; * the assertion of the CLK_CHANGE_L[2:0] signals and the assertion of&n; * the ESTAR_PLL_BYPASS signal.&n; */
DECL|macro|BBC_ES_ABT_VAL
mdefine_line|#define BBC_ES_ABT_VAL&t;0xffff
multiline_comment|/* Energy Star PLL Settle Time register.  This determines the number of&n; * BBC clock cycles (which is half the system frequency) between the&n; * de-assertion of CLK_CHANGE_L[2:0] and the de-assertion of the FREEZE_L&n; * signal.&n; */
DECL|macro|BBC_ES_PST_VAL
mdefine_line|#define BBC_ES_PST_VAL&t;0xffffffff
multiline_comment|/* Energy Star Frequency Switch Latency register.  This is the number of&n; * BBC clocks between the de-assertion of CLK_CHANGE_L[2:0] and the first&n; * edge of the Safari clock at the new frequency.&n; */
DECL|macro|BBC_ES_FSL_VAL
mdefine_line|#define BBC_ES_FSL_VAL&t;0xffffffff
multiline_comment|/* Keyboard Beep control register.  This is a simple enabler for the audio&n; * beep sound.&n; */
DECL|macro|BBC_KBD_BEEP_ENABLE
mdefine_line|#define BBC_KBD_BEEP_ENABLE&t;0x01 /* Enable beep&t;*/
DECL|macro|BBC_KBD_BEEP_RESV
mdefine_line|#define BBC_KBD_BEEP_RESV&t;0xfe /* Reserved&t;*/
multiline_comment|/* Keyboard Beep Counter register.  There is a free-running counter inside&n; * the BBC which runs at half the system clock.  The bit set in this register&n; * determines when the audio sound is generated.  So for example if bit&n; * 10 is set, the audio beep will oscillate at 1/(2**12).  The keyboard beep&n; * generator automatically selects a different bit to use if the system clock&n; * is changed via Energy Star.&n; */
DECL|macro|BBC_KBD_BCNT_BITS
mdefine_line|#define BBC_KBD_BCNT_BITS&t;0x0007fc00
DECL|macro|BBC_KBC_BCNT_RESV
mdefine_line|#define BBC_KBC_BCNT_RESV&t;0xfff803ff
macro_line|#endif /* _SPARC64_BBC_H */
eof
