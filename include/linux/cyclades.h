multiline_comment|/* $Revision: 3.0 $$Date: 1998/11/02 14:20:59 $&n; * linux/include/linux/cyclades.h&n; *&n; * This file was initially written by&n; * Randolph Bentson &lt;bentson@grieg.seaslug.org&gt; and is maintained by&n; * Ivan Passos &lt;ivan@cyclades.com&gt;.&n; *&n; * This file contains the general definitions for the cyclades.c driver&n; *$Log: cyclades.h,v $&n; *Revision 3.1  2000/04/19 18:52:52  ivan&n; *converted address fields to unsigned long and added fields for physical&n; *addresses on cyclades_card structure;&n; *&n; *Revision 3.0  1998/11/02 14:20:59  ivan&n; *added nports field on cyclades_card structure;&n; *&n; *Revision 2.5  1998/08/03 16:57:01  ivan&n; *added cyclades_idle_stats structure;&n; * &n; *Revision 2.4  1998/06/01 12:09:53  ivan&n; *removed closing_wait2 from cyclades_port structure;&n; *&n; *Revision 2.3  1998/03/16 18:01:12  ivan&n; *changes in the cyclades_port structure to get it closer to the &n; *standard serial port structure;&n; *added constants for new ioctls;&n; *&n; *Revision 2.2  1998/02/17 16:50:00  ivan&n; *changes in the cyclades_port structure (addition of shutdown_wait and &n; *chip_rev variables);&n; *added constants for new ioctls and for CD1400 rev. numbers.&n; *&n; *Revision 2.1&t;1997/10/24 16:03:00  ivan&n; *added rflow (which allows enabling the CD1400 special flow control &n; *feature) and rtsdtr_inv (which allows DTR/RTS pin inversion) to &n; *cyclades_port structure;&n; *added Alpha support&n; *&n; *Revision 2.0  1997/06/30 10:30:00  ivan&n; *added some new doorbell command constants related to IOCTLW and&n; *UART error signaling&n; *&n; *Revision 1.8  1997/06/03 15:30:00  ivan&n; *added constant ZFIRM_HLT&n; *added constant CyPCI_Ze_win ( = 2 * Cy_PCI_Zwin)&n; *&n; *Revision 1.7  1997/03/26 10:30:00  daniel&n; *new entries at the end of cyclades_port struct to reallocate&n; *variables illegally allocated within card memory.&n; *&n; *Revision 1.6  1996/09/09 18:35:30  bentson&n; *fold in changes for Cyclom-Z -- including structures for&n; *communicating with board as well modest changes to original&n; *structures to support new features.&n; *&n; *Revision 1.5  1995/11/13 21:13:31  bentson&n; *changes suggested by Michael Chastain &lt;mec@duracef.shout.net&gt;&n; *to support use of this file in non-kernel applications&n; *&n; *&n; */
macro_line|#ifndef _LINUX_CYCLADES_H
DECL|macro|_LINUX_CYCLADES_H
mdefine_line|#define _LINUX_CYCLADES_H
DECL|struct|cyclades_monitor
r_struct
id|cyclades_monitor
(brace
DECL|member|int_count
r_int
r_int
id|int_count
suffix:semicolon
DECL|member|char_count
r_int
r_int
id|char_count
suffix:semicolon
DECL|member|char_max
r_int
r_int
id|char_max
suffix:semicolon
DECL|member|char_last
r_int
r_int
id|char_last
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * These stats all reflect activity since the device was last initialized.&n; * (i.e., since the port was opened with no other processes already having it&n; * open)&n; */
DECL|struct|cyclades_idle_stats
r_struct
id|cyclades_idle_stats
(brace
DECL|member|in_use
id|time_t
id|in_use
suffix:semicolon
multiline_comment|/* Time device has been in use (secs) */
DECL|member|recv_idle
id|time_t
id|recv_idle
suffix:semicolon
multiline_comment|/* Time since last char received (secs) */
DECL|member|xmit_idle
id|time_t
id|xmit_idle
suffix:semicolon
multiline_comment|/* Time since last char transmitted (secs) */
DECL|member|recv_bytes
r_int
r_int
id|recv_bytes
suffix:semicolon
multiline_comment|/* Bytes received */
DECL|member|xmit_bytes
r_int
r_int
id|xmit_bytes
suffix:semicolon
multiline_comment|/* Bytes transmitted */
DECL|member|overruns
r_int
r_int
id|overruns
suffix:semicolon
multiline_comment|/* Input overruns */
DECL|member|frame_errs
r_int
r_int
id|frame_errs
suffix:semicolon
multiline_comment|/* Input framing errors */
DECL|member|parity_errs
r_int
r_int
id|parity_errs
suffix:semicolon
multiline_comment|/* Input parity errors */
)brace
suffix:semicolon
DECL|macro|CYCLADES_MAGIC
mdefine_line|#define CYCLADES_MAGIC  0x4359
DECL|macro|CYGETMON
mdefine_line|#define CYGETMON                0x435901
DECL|macro|CYGETTHRESH
mdefine_line|#define CYGETTHRESH             0x435902
DECL|macro|CYSETTHRESH
mdefine_line|#define CYSETTHRESH             0x435903
DECL|macro|CYGETDEFTHRESH
mdefine_line|#define CYGETDEFTHRESH          0x435904
DECL|macro|CYSETDEFTHRESH
mdefine_line|#define CYSETDEFTHRESH          0x435905
DECL|macro|CYGETTIMEOUT
mdefine_line|#define CYGETTIMEOUT            0x435906
DECL|macro|CYSETTIMEOUT
mdefine_line|#define CYSETTIMEOUT            0x435907
DECL|macro|CYGETDEFTIMEOUT
mdefine_line|#define CYGETDEFTIMEOUT         0x435908
DECL|macro|CYSETDEFTIMEOUT
mdefine_line|#define CYSETDEFTIMEOUT         0x435909
DECL|macro|CYSETRFLOW
mdefine_line|#define CYSETRFLOW&t;&t;0x43590a
DECL|macro|CYGETRFLOW
mdefine_line|#define CYGETRFLOW&t;&t;0x43590b
DECL|macro|CYSETRTSDTR_INV
mdefine_line|#define CYSETRTSDTR_INV&t;&t;0x43590c
DECL|macro|CYGETRTSDTR_INV
mdefine_line|#define CYGETRTSDTR_INV&t;&t;0x43590d
DECL|macro|CYZSETPOLLCYCLE
mdefine_line|#define CYZSETPOLLCYCLE&t;&t;0x43590e
DECL|macro|CYZGETPOLLCYCLE
mdefine_line|#define CYZGETPOLLCYCLE&t;&t;0x43590f
DECL|macro|CYGETCD1400VER
mdefine_line|#define CYGETCD1400VER&t;&t;0x435910
DECL|macro|CYGETCARDINFO
mdefine_line|#define CYGETCARDINFO&t;&t;0x435911
DECL|macro|CYSETWAIT
mdefine_line|#define&t;CYSETWAIT&t;&t;0x435912
DECL|macro|CYGETWAIT
mdefine_line|#define&t;CYGETWAIT&t;&t;0x435913
multiline_comment|/*************** CYCLOM-Z ADDITIONS ***************/
DECL|macro|CZIOC
mdefine_line|#define CZIOC           (&squot;M&squot; &lt;&lt; 8)
DECL|macro|CZ_NBOARDS
mdefine_line|#define CZ_NBOARDS      (CZIOC|0xfa)
DECL|macro|CZ_BOOT_START
mdefine_line|#define CZ_BOOT_START   (CZIOC|0xfb)
DECL|macro|CZ_BOOT_DATA
mdefine_line|#define CZ_BOOT_DATA    (CZIOC|0xfc)
DECL|macro|CZ_BOOT_END
mdefine_line|#define CZ_BOOT_END     (CZIOC|0xfd)
DECL|macro|CZ_TEST
mdefine_line|#define CZ_TEST         (CZIOC|0xfe)
DECL|macro|CZ_DEF_POLL
mdefine_line|#define CZ_DEF_POLL&t;(HZ/25)
DECL|macro|MAX_BOARD
mdefine_line|#define MAX_BOARD       4       /* Max number of boards */
DECL|macro|MAX_DEV
mdefine_line|#define MAX_DEV         256     /* Max number of ports total */
DECL|macro|CYZ_MAX_SPEED
mdefine_line|#define&t;CYZ_MAX_SPEED&t;921600
DECL|macro|CYZ_FIFO_SIZE
mdefine_line|#define&t;CYZ_FIFO_SIZE&t;16
DECL|macro|CYZ_BOOT_NWORDS
mdefine_line|#define CYZ_BOOT_NWORDS 0x100
DECL|struct|CYZ_BOOT_CTRL
r_struct
id|CYZ_BOOT_CTRL
(brace
DECL|member|nboard
r_int
r_int
id|nboard
suffix:semicolon
DECL|member|status
r_int
id|status
(braket
id|MAX_BOARD
)braket
suffix:semicolon
DECL|member|nchannel
r_int
id|nchannel
(braket
id|MAX_BOARD
)braket
suffix:semicolon
DECL|member|fw_rev
r_int
id|fw_rev
(braket
id|MAX_BOARD
)braket
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
(braket
id|CYZ_BOOT_NWORDS
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef DP_WINDOW_SIZE
multiline_comment|/* #include &quot;cyclomz.h&quot; */
multiline_comment|/****************** ****************** *******************/
multiline_comment|/*&n; *&t;The data types defined below are used in all ZFIRM interface&n; *&t;data structures. They accomodate differences between HW&n; *&t;architectures and compilers.&n; */
macro_line|#if defined(__alpha__)
DECL|typedef|ucdouble
r_typedef
r_int
r_int
id|ucdouble
suffix:semicolon
multiline_comment|/* 64 bits, unsigned */
DECL|typedef|uclong
r_typedef
r_int
r_int
id|uclong
suffix:semicolon
multiline_comment|/* 32 bits, unsigned */
macro_line|#else
DECL|typedef|uclong
r_typedef
r_int
r_int
id|uclong
suffix:semicolon
multiline_comment|/* 32 bits, unsigned */
macro_line|#endif
DECL|typedef|ucshort
r_typedef
r_int
r_int
id|ucshort
suffix:semicolon
multiline_comment|/* 16 bits, unsigned */
DECL|typedef|ucchar
r_typedef
r_int
r_char
id|ucchar
suffix:semicolon
multiline_comment|/* 8 bits, unsigned */
multiline_comment|/*&n; *&t;Memory Window Sizes&n; */
DECL|macro|DP_WINDOW_SIZE
mdefine_line|#define&t;DP_WINDOW_SIZE&t;&t;(0x00080000)&t;/* window size 512 Kb */
DECL|macro|ZE_DP_WINDOW_SIZE
mdefine_line|#define&t;ZE_DP_WINDOW_SIZE&t;(0x00100000)&t;/* window size 1 Mb (Ze and&n;&t;&t;&t;&t;&t;&t;  8Zo V.2 */
DECL|macro|CTRL_WINDOW_SIZE
mdefine_line|#define&t;CTRL_WINDOW_SIZE&t;(0x00000080)&t;/* runtime regs 128 bytes */
multiline_comment|/*&n; *&t;CUSTOM_REG - Cyclom-Z/PCI Custom Registers Set. The driver&n; *&t;normally will access only interested on the fpga_id, fpga_version,&n; *&t;start_cpu and stop_cpu.&n; */
DECL|struct|CUSTOM_REG
r_struct
id|CUSTOM_REG
(brace
DECL|member|fpga_id
id|uclong
id|fpga_id
suffix:semicolon
multiline_comment|/* FPGA Identification Register */
DECL|member|fpga_version
id|uclong
id|fpga_version
suffix:semicolon
multiline_comment|/* FPGA Version Number Register */
DECL|member|cpu_start
id|uclong
id|cpu_start
suffix:semicolon
multiline_comment|/* CPU start Register (write) */
DECL|member|cpu_stop
id|uclong
id|cpu_stop
suffix:semicolon
multiline_comment|/* CPU stop Register (write) */
DECL|member|misc_reg
id|uclong
id|misc_reg
suffix:semicolon
multiline_comment|/* Miscelaneous Register */
DECL|member|idt_mode
id|uclong
id|idt_mode
suffix:semicolon
multiline_comment|/* IDT mode Register */
DECL|member|uart_irq_status
id|uclong
id|uart_irq_status
suffix:semicolon
multiline_comment|/* UART IRQ status Register */
DECL|member|clear_timer0_irq
id|uclong
id|clear_timer0_irq
suffix:semicolon
multiline_comment|/* Clear timer interrupt Register */
DECL|member|clear_timer1_irq
id|uclong
id|clear_timer1_irq
suffix:semicolon
multiline_comment|/* Clear timer interrupt Register */
DECL|member|clear_timer2_irq
id|uclong
id|clear_timer2_irq
suffix:semicolon
multiline_comment|/* Clear timer interrupt Register */
DECL|member|test_register
id|uclong
id|test_register
suffix:semicolon
multiline_comment|/* Test Register */
DECL|member|test_count
id|uclong
id|test_count
suffix:semicolon
multiline_comment|/* Test Count Register */
DECL|member|timer_select
id|uclong
id|timer_select
suffix:semicolon
multiline_comment|/* Timer select register */
DECL|member|pr_uart_irq_status
id|uclong
id|pr_uart_irq_status
suffix:semicolon
multiline_comment|/* Prioritized UART IRQ stat Reg */
DECL|member|ram_wait_state
id|uclong
id|ram_wait_state
suffix:semicolon
multiline_comment|/* RAM wait-state Register */
DECL|member|uart_wait_state
id|uclong
id|uart_wait_state
suffix:semicolon
multiline_comment|/* UART wait-state Register */
DECL|member|timer_wait_state
id|uclong
id|timer_wait_state
suffix:semicolon
multiline_comment|/* timer wait-state Register */
DECL|member|ack_wait_state
id|uclong
id|ack_wait_state
suffix:semicolon
multiline_comment|/* ACK wait State Register */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;RUNTIME_9060 - PLX PCI9060ES local configuration and shared runtime&n; *&t;registers. This structure can be used to access the 9060 registers&n; *&t;(memory mapped).&n; */
DECL|struct|RUNTIME_9060
r_struct
id|RUNTIME_9060
(brace
DECL|member|loc_addr_range
id|uclong
id|loc_addr_range
suffix:semicolon
multiline_comment|/* 00h - Local Address Range */
DECL|member|loc_addr_base
id|uclong
id|loc_addr_base
suffix:semicolon
multiline_comment|/* 04h - Local Address Base */
DECL|member|loc_arbitr
id|uclong
id|loc_arbitr
suffix:semicolon
multiline_comment|/* 08h - Local Arbitration */
DECL|member|endian_descr
id|uclong
id|endian_descr
suffix:semicolon
multiline_comment|/* 0Ch - Big/Little Endian Descriptor */
DECL|member|loc_rom_range
id|uclong
id|loc_rom_range
suffix:semicolon
multiline_comment|/* 10h - Local ROM Range */
DECL|member|loc_rom_base
id|uclong
id|loc_rom_base
suffix:semicolon
multiline_comment|/* 14h - Local ROM Base */
DECL|member|loc_bus_descr
id|uclong
id|loc_bus_descr
suffix:semicolon
multiline_comment|/* 18h - Local Bus descriptor */
DECL|member|loc_range_mst
id|uclong
id|loc_range_mst
suffix:semicolon
multiline_comment|/* 1Ch - Local Range for Master to PCI */
DECL|member|loc_base_mst
id|uclong
id|loc_base_mst
suffix:semicolon
multiline_comment|/* 20h - Local Base for Master PCI */
DECL|member|loc_range_io
id|uclong
id|loc_range_io
suffix:semicolon
multiline_comment|/* 24h - Local Range for Master IO */
DECL|member|pci_base_mst
id|uclong
id|pci_base_mst
suffix:semicolon
multiline_comment|/* 28h - PCI Base for Master PCI */
DECL|member|pci_conf_io
id|uclong
id|pci_conf_io
suffix:semicolon
multiline_comment|/* 2Ch - PCI configuration for Master IO */
DECL|member|filler1
id|uclong
id|filler1
suffix:semicolon
multiline_comment|/* 30h */
DECL|member|filler2
id|uclong
id|filler2
suffix:semicolon
multiline_comment|/* 34h */
DECL|member|filler3
id|uclong
id|filler3
suffix:semicolon
multiline_comment|/* 38h */
DECL|member|filler4
id|uclong
id|filler4
suffix:semicolon
multiline_comment|/* 3Ch */
DECL|member|mail_box_0
id|uclong
id|mail_box_0
suffix:semicolon
multiline_comment|/* 40h - Mail Box 0 */
DECL|member|mail_box_1
id|uclong
id|mail_box_1
suffix:semicolon
multiline_comment|/* 44h - Mail Box 1 */
DECL|member|mail_box_2
id|uclong
id|mail_box_2
suffix:semicolon
multiline_comment|/* 48h - Mail Box 2 */
DECL|member|mail_box_3
id|uclong
id|mail_box_3
suffix:semicolon
multiline_comment|/* 4Ch - Mail Box 3 */
DECL|member|filler5
id|uclong
id|filler5
suffix:semicolon
multiline_comment|/* 50h */
DECL|member|filler6
id|uclong
id|filler6
suffix:semicolon
multiline_comment|/* 54h */
DECL|member|filler7
id|uclong
id|filler7
suffix:semicolon
multiline_comment|/* 58h */
DECL|member|filler8
id|uclong
id|filler8
suffix:semicolon
multiline_comment|/* 5Ch */
DECL|member|pci_doorbell
id|uclong
id|pci_doorbell
suffix:semicolon
multiline_comment|/* 60h - PCI to Local Doorbell */
DECL|member|loc_doorbell
id|uclong
id|loc_doorbell
suffix:semicolon
multiline_comment|/* 64h - Local to PCI Doorbell */
DECL|member|intr_ctrl_stat
id|uclong
id|intr_ctrl_stat
suffix:semicolon
multiline_comment|/* 68h - Interrupt Control/Status */
DECL|member|init_ctrl
id|uclong
id|init_ctrl
suffix:semicolon
multiline_comment|/* 6Ch - EEPROM control, Init Control, etc */
)brace
suffix:semicolon
multiline_comment|/* Values for the Local Base Address re-map register */
DECL|macro|WIN_RAM
mdefine_line|#define&t;WIN_RAM&t;&t;0x00000001L&t;/* set the sliding window to RAM */
DECL|macro|WIN_CREG
mdefine_line|#define&t;WIN_CREG&t;0x14000001L&t;/* set the window to custom Registers */
multiline_comment|/* Values timer select registers */
DECL|macro|TIMER_BY_1M
mdefine_line|#define&t;TIMER_BY_1M&t;0x00&t;&t;/* clock divided by 1M */
DECL|macro|TIMER_BY_256K
mdefine_line|#define&t;TIMER_BY_256K&t;0x01&t;&t;/* clock divided by 256k */
DECL|macro|TIMER_BY_128K
mdefine_line|#define&t;TIMER_BY_128K&t;0x02&t;&t;/* clock divided by 128k */
DECL|macro|TIMER_BY_32K
mdefine_line|#define&t;TIMER_BY_32K&t;0x03&t;&t;/* clock divided by 32k */
multiline_comment|/****************** ****************** *******************/
macro_line|#endif
macro_line|#ifndef ZFIRM_ID
multiline_comment|/* #include &quot;zfwint.h&quot; */
multiline_comment|/****************** ****************** *******************/
multiline_comment|/*&n; *&t;This file contains the definitions for interfacing with the&n; *&t;Cyclom-Z ZFIRM Firmware.&n; */
multiline_comment|/* General Constant definitions */
DECL|macro|MAX_CHAN
mdefine_line|#define&t;MAX_CHAN&t;64&t;&t;/* max number of channels per board */
multiline_comment|/* firmware id structure (set after boot) */
DECL|macro|ID_ADDRESS
mdefine_line|#define ID_ADDRESS&t;0x00000180L&t;/* signature/pointer address */
DECL|macro|ZFIRM_ID
mdefine_line|#define&t;ZFIRM_ID&t;0x5557465AL&t;/* ZFIRM/U signature */
DECL|macro|ZFIRM_HLT
mdefine_line|#define&t;ZFIRM_HLT&t;0x59505B5CL&t;/* ZFIRM needs external power supply */
DECL|macro|ZFIRM_RST
mdefine_line|#define&t;ZFIRM_RST&t;0x56040674L&t;/* RST signal (due to FW reset) */
DECL|macro|ZF_TINACT_DEF
mdefine_line|#define&t;ZF_TINACT_DEF&t;1000&t;&t;/* default inactivity timeout &n;&t;&t;&t;&t;&t;   (1000 ms) */
DECL|macro|ZF_TINACT
mdefine_line|#define&t;ZF_TINACT&t;ZF_TINACT_DEF
DECL|struct|FIRM_ID
r_struct
id|FIRM_ID
(brace
DECL|member|signature
id|uclong
id|signature
suffix:semicolon
multiline_comment|/* ZFIRM/U signature */
DECL|member|zfwctrl_addr
id|uclong
id|zfwctrl_addr
suffix:semicolon
multiline_comment|/* pointer to ZFW_CTRL structure */
)brace
suffix:semicolon
multiline_comment|/* Op. System id */
DECL|macro|C_OS_LINUX
mdefine_line|#define&t;C_OS_LINUX&t;0x00000030&t;/* generic Linux system */
multiline_comment|/* channel op_mode */
DECL|macro|C_CH_DISABLE
mdefine_line|#define&t;C_CH_DISABLE&t;0x00000000&t;/* channel is disabled */
DECL|macro|C_CH_TXENABLE
mdefine_line|#define&t;C_CH_TXENABLE&t;0x00000001&t;/* channel Tx enabled */
DECL|macro|C_CH_RXENABLE
mdefine_line|#define&t;C_CH_RXENABLE&t;0x00000002&t;/* channel Rx enabled */
DECL|macro|C_CH_ENABLE
mdefine_line|#define&t;C_CH_ENABLE&t;0x00000003&t;/* channel Tx/Rx enabled */
DECL|macro|C_CH_LOOPBACK
mdefine_line|#define&t;C_CH_LOOPBACK&t;0x00000004&t;/* Loopback mode */
multiline_comment|/* comm_parity - parity */
DECL|macro|C_PR_NONE
mdefine_line|#define&t;C_PR_NONE&t;0x00000000&t;/* None */
DECL|macro|C_PR_ODD
mdefine_line|#define&t;C_PR_ODD&t;0x00000001&t;/* Odd */
DECL|macro|C_PR_EVEN
mdefine_line|#define C_PR_EVEN&t;0x00000002&t;/* Even */
DECL|macro|C_PR_MARK
mdefine_line|#define C_PR_MARK&t;0x00000004&t;/* Mark */
DECL|macro|C_PR_SPACE
mdefine_line|#define C_PR_SPACE&t;0x00000008&t;/* Space */
DECL|macro|C_PR_PARITY
mdefine_line|#define C_PR_PARITY&t;0x000000ff
DECL|macro|C_PR_DISCARD
mdefine_line|#define&t;C_PR_DISCARD&t;0x00000100&t;/* discard char with frame/par error */
DECL|macro|C_PR_IGNORE
mdefine_line|#define C_PR_IGNORE&t;0x00000200&t;/* ignore frame/par error */
multiline_comment|/* comm_data_l - data length and stop bits */
DECL|macro|C_DL_CS5
mdefine_line|#define C_DL_CS5&t;0x00000001
DECL|macro|C_DL_CS6
mdefine_line|#define C_DL_CS6&t;0x00000002
DECL|macro|C_DL_CS7
mdefine_line|#define C_DL_CS7&t;0x00000004
DECL|macro|C_DL_CS8
mdefine_line|#define C_DL_CS8&t;0x00000008
DECL|macro|C_DL_CS
mdefine_line|#define&t;C_DL_CS&t;&t;0x0000000f
DECL|macro|C_DL_1STOP
mdefine_line|#define C_DL_1STOP&t;0x00000010
DECL|macro|C_DL_15STOP
mdefine_line|#define C_DL_15STOP&t;0x00000020
DECL|macro|C_DL_2STOP
mdefine_line|#define C_DL_2STOP&t;0x00000040
DECL|macro|C_DL_STOP
mdefine_line|#define&t;C_DL_STOP&t;0x000000f0
multiline_comment|/* interrupt enabling/status */
DECL|macro|C_IN_DISABLE
mdefine_line|#define&t;C_IN_DISABLE&t;0x00000000&t;/* zero, disable interrupts */
DECL|macro|C_IN_TXBEMPTY
mdefine_line|#define&t;C_IN_TXBEMPTY&t;0x00000001&t;/* tx buffer empty */
DECL|macro|C_IN_TXLOWWM
mdefine_line|#define&t;C_IN_TXLOWWM&t;0x00000002&t;/* tx buffer below LWM */
DECL|macro|C_IN_RXHIWM
mdefine_line|#define&t;C_IN_RXHIWM&t;0x00000010&t;/* rx buffer above HWM */
DECL|macro|C_IN_RXNNDT
mdefine_line|#define&t;C_IN_RXNNDT&t;0x00000020&t;/* rx no new data timeout */
DECL|macro|C_IN_MDCD
mdefine_line|#define&t;C_IN_MDCD&t;0x00000100&t;/* modem DCD change */
DECL|macro|C_IN_MDSR
mdefine_line|#define&t;C_IN_MDSR&t;0x00000200&t;/* modem DSR change */
DECL|macro|C_IN_MRI
mdefine_line|#define&t;C_IN_MRI&t;0x00000400&t;/* modem RI change */
DECL|macro|C_IN_MCTS
mdefine_line|#define&t;C_IN_MCTS&t;0x00000800&t;/* modem CTS change */
DECL|macro|C_IN_RXBRK
mdefine_line|#define&t;C_IN_RXBRK&t;0x00001000&t;/* Break received */
DECL|macro|C_IN_PR_ERROR
mdefine_line|#define&t;C_IN_PR_ERROR&t;0x00002000&t;/* parity error */
DECL|macro|C_IN_FR_ERROR
mdefine_line|#define&t;C_IN_FR_ERROR&t;0x00004000&t;/* frame error */
DECL|macro|C_IN_OVR_ERROR
mdefine_line|#define C_IN_OVR_ERROR  0x00008000      /* overrun error */
DECL|macro|C_IN_RXOFL
mdefine_line|#define C_IN_RXOFL&t;0x00010000      /* RX buffer overflow */
DECL|macro|C_IN_IOCTLW
mdefine_line|#define C_IN_IOCTLW&t;0x00020000      /* I/O control w/ wait */
DECL|macro|C_IN_MRTS
mdefine_line|#define C_IN_MRTS&t;0x00040000&t;/* modem RTS drop */
DECL|macro|C_IN_ICHAR
mdefine_line|#define C_IN_ICHAR&t;0x00080000
multiline_comment|/* flow control */
DECL|macro|C_FL_OXX
mdefine_line|#define&t;C_FL_OXX&t;0x00000001&t;/* output Xon/Xoff flow control */
DECL|macro|C_FL_IXX
mdefine_line|#define&t;C_FL_IXX&t;0x00000002&t;/* output Xon/Xoff flow control */
DECL|macro|C_FL_OIXANY
mdefine_line|#define C_FL_OIXANY&t;0x00000004&t;/* output Xon/Xoff (any xon) */
DECL|macro|C_FL_SWFLOW
mdefine_line|#define&t;C_FL_SWFLOW&t;0x0000000f
multiline_comment|/* flow status */
DECL|macro|C_FS_TXIDLE
mdefine_line|#define&t;C_FS_TXIDLE&t;0x00000000&t;/* no Tx data in the buffer or UART */
DECL|macro|C_FS_SENDING
mdefine_line|#define&t;C_FS_SENDING&t;0x00000001&t;/* UART is sending data */
DECL|macro|C_FS_SWFLOW
mdefine_line|#define&t;C_FS_SWFLOW&t;0x00000002&t;/* Tx is stopped by received Xoff */
multiline_comment|/* rs_control/rs_status RS-232 signals */
DECL|macro|C_RS_PARAM
mdefine_line|#define C_RS_PARAM&t;0x80000000&t;/* Indicates presence of parameter in &n;&t;&t;&t;&t;&t;   IOCTLM command */
DECL|macro|C_RS_RTS
mdefine_line|#define&t;C_RS_RTS&t;0x00000001&t;/* RTS */
DECL|macro|C_RS_DTR
mdefine_line|#define&t;C_RS_DTR&t;0x00000004&t;/* DTR */
DECL|macro|C_RS_DCD
mdefine_line|#define&t;C_RS_DCD&t;0x00000100&t;/* CD */
DECL|macro|C_RS_DSR
mdefine_line|#define&t;C_RS_DSR&t;0x00000200&t;/* DSR */
DECL|macro|C_RS_RI
mdefine_line|#define&t;C_RS_RI&t;&t;0x00000400&t;/* RI */
DECL|macro|C_RS_CTS
mdefine_line|#define&t;C_RS_CTS&t;0x00000800&t;/* CTS */
multiline_comment|/* commands Host &lt;-&gt; Board */
DECL|macro|C_CM_RESET
mdefine_line|#define&t;C_CM_RESET&t;0x01&t;&t;/* reset/flush buffers */
DECL|macro|C_CM_IOCTL
mdefine_line|#define&t;C_CM_IOCTL&t;0x02&t;&t;/* re-read CH_CTRL */
DECL|macro|C_CM_IOCTLW
mdefine_line|#define&t;C_CM_IOCTLW&t;0x03&t;&t;/* re-read CH_CTRL, intr when done */
DECL|macro|C_CM_IOCTLM
mdefine_line|#define&t;C_CM_IOCTLM&t;0x04&t;&t;/* RS-232 outputs change */
DECL|macro|C_CM_SENDXOFF
mdefine_line|#define&t;C_CM_SENDXOFF&t;0x10&t;&t;/* send Xoff */
DECL|macro|C_CM_SENDXON
mdefine_line|#define&t;C_CM_SENDXON&t;0x11&t;&t;/* send Xon */
DECL|macro|C_CM_CLFLOW
mdefine_line|#define C_CM_CLFLOW&t;0x12&t;&t;/* Clear flow control (resume) */
DECL|macro|C_CM_SENDBRK
mdefine_line|#define&t;C_CM_SENDBRK&t;0x41&t;&t;/* send break */
DECL|macro|C_CM_INTBACK
mdefine_line|#define&t;C_CM_INTBACK&t;0x42&t;&t;/* Interrupt back */
DECL|macro|C_CM_SET_BREAK
mdefine_line|#define&t;C_CM_SET_BREAK&t;0x43&t;&t;/* Tx break on */
DECL|macro|C_CM_CLR_BREAK
mdefine_line|#define&t;C_CM_CLR_BREAK&t;0x44&t;&t;/* Tx break off */
DECL|macro|C_CM_CMD_DONE
mdefine_line|#define&t;C_CM_CMD_DONE&t;0x45&t;&t;/* Previous command done */
DECL|macro|C_CM_INTBACK2
mdefine_line|#define C_CM_INTBACK2&t;0x46&t;&t;/* Alternate Interrupt back */
DECL|macro|C_CM_TINACT
mdefine_line|#define&t;C_CM_TINACT&t;0x51&t;&t;/* set inactivity detection */
DECL|macro|C_CM_IRQ_ENBL
mdefine_line|#define&t;C_CM_IRQ_ENBL&t;0x52&t;&t;/* enable generation of interrupts */
DECL|macro|C_CM_IRQ_DSBL
mdefine_line|#define&t;C_CM_IRQ_DSBL&t;0x53&t;&t;/* disable generation of interrupts */
DECL|macro|C_CM_ACK_ENBL
mdefine_line|#define&t;C_CM_ACK_ENBL&t;0x54&t;&t;/* enable acknowledged interrupt mode */
DECL|macro|C_CM_ACK_DSBL
mdefine_line|#define&t;C_CM_ACK_DSBL&t;0x55&t;&t;/* disable acknowledged intr mode */
DECL|macro|C_CM_FLUSH_RX
mdefine_line|#define&t;C_CM_FLUSH_RX&t;0x56&t;&t;/* flushes Rx buffer */
DECL|macro|C_CM_FLUSH_TX
mdefine_line|#define&t;C_CM_FLUSH_TX&t;0x57&t;&t;/* flushes Tx buffer */
DECL|macro|C_CM_Q_ENABLE
mdefine_line|#define C_CM_Q_ENABLE&t;0x58&t;&t;/* enables queue access from the &n;&t;&t;&t;&t;&t;   driver */
DECL|macro|C_CM_Q_DISABLE
mdefine_line|#define C_CM_Q_DISABLE  0x59            /* disables queue access from the &n;&t;&t;&t;&t;&t;   driver */
DECL|macro|C_CM_TXBEMPTY
mdefine_line|#define&t;C_CM_TXBEMPTY&t;0x60&t;&t;/* Tx buffer is empty */
DECL|macro|C_CM_TXLOWWM
mdefine_line|#define&t;C_CM_TXLOWWM&t;0x61&t;&t;/* Tx buffer low water mark */
DECL|macro|C_CM_RXHIWM
mdefine_line|#define&t;C_CM_RXHIWM&t;0x62&t;&t;/* Rx buffer high water mark */
DECL|macro|C_CM_RXNNDT
mdefine_line|#define&t;C_CM_RXNNDT&t;0x63&t;&t;/* rx no new data timeout */
DECL|macro|C_CM_TXFEMPTY
mdefine_line|#define&t;C_CM_TXFEMPTY&t;0x64
DECL|macro|C_CM_ICHAR
mdefine_line|#define&t;C_CM_ICHAR&t;0x65
DECL|macro|C_CM_MDCD
mdefine_line|#define&t;C_CM_MDCD&t;0x70&t;&t;/* modem DCD change */
DECL|macro|C_CM_MDSR
mdefine_line|#define&t;C_CM_MDSR&t;0x71&t;&t;/* modem DSR change */
DECL|macro|C_CM_MRI
mdefine_line|#define&t;C_CM_MRI&t;0x72&t;&t;/* modem RI change */
DECL|macro|C_CM_MCTS
mdefine_line|#define&t;C_CM_MCTS&t;0x73&t;&t;/* modem CTS change */
DECL|macro|C_CM_MRTS
mdefine_line|#define C_CM_MRTS&t;0x74&t;&t;/* modem RTS drop */
DECL|macro|C_CM_RXBRK
mdefine_line|#define&t;C_CM_RXBRK&t;0x84&t;&t;/* Break received */
DECL|macro|C_CM_PR_ERROR
mdefine_line|#define&t;C_CM_PR_ERROR&t;0x85&t;&t;/* Parity error */
DECL|macro|C_CM_FR_ERROR
mdefine_line|#define&t;C_CM_FR_ERROR&t;0x86&t;&t;/* Frame error */
DECL|macro|C_CM_OVR_ERROR
mdefine_line|#define C_CM_OVR_ERROR  0x87            /* Overrun error */
DECL|macro|C_CM_RXOFL
mdefine_line|#define C_CM_RXOFL&t;0x88            /* RX buffer overflow */
DECL|macro|C_CM_CMDERROR
mdefine_line|#define&t;C_CM_CMDERROR&t;0x90&t;&t;/* command error */
DECL|macro|C_CM_FATAL
mdefine_line|#define&t;C_CM_FATAL&t;0x91&t;&t;/* fatal error */
DECL|macro|C_CM_HW_RESET
mdefine_line|#define&t;C_CM_HW_RESET&t;0x92&t;&t;/* reset board */
multiline_comment|/*&n; *&t;CH_CTRL - This per port structure contains all parameters&n; *&t;that control an specific port. It can be seen as the&n; *&t;configuration registers of a &quot;super-serial-controller&quot;.&n; */
DECL|struct|CH_CTRL
r_struct
id|CH_CTRL
(brace
DECL|member|op_mode
id|uclong
id|op_mode
suffix:semicolon
multiline_comment|/* operation mode */
DECL|member|intr_enable
id|uclong
id|intr_enable
suffix:semicolon
multiline_comment|/* interrupt masking */
DECL|member|sw_flow
id|uclong
id|sw_flow
suffix:semicolon
multiline_comment|/* SW flow control */
DECL|member|flow_status
id|uclong
id|flow_status
suffix:semicolon
multiline_comment|/* output flow status */
DECL|member|comm_baud
id|uclong
id|comm_baud
suffix:semicolon
multiline_comment|/* baud rate  - numerically specified */
DECL|member|comm_parity
id|uclong
id|comm_parity
suffix:semicolon
multiline_comment|/* parity */
DECL|member|comm_data_l
id|uclong
id|comm_data_l
suffix:semicolon
multiline_comment|/* data length/stop */
DECL|member|comm_flags
id|uclong
id|comm_flags
suffix:semicolon
multiline_comment|/* other flags */
DECL|member|hw_flow
id|uclong
id|hw_flow
suffix:semicolon
multiline_comment|/* HW flow control */
DECL|member|rs_control
id|uclong
id|rs_control
suffix:semicolon
multiline_comment|/* RS-232 outputs */
DECL|member|rs_status
id|uclong
id|rs_status
suffix:semicolon
multiline_comment|/* RS-232 inputs */
DECL|member|flow_xon
id|uclong
id|flow_xon
suffix:semicolon
multiline_comment|/* xon char */
DECL|member|flow_xoff
id|uclong
id|flow_xoff
suffix:semicolon
multiline_comment|/* xoff char */
DECL|member|hw_overflow
id|uclong
id|hw_overflow
suffix:semicolon
multiline_comment|/* hw overflow counter */
DECL|member|sw_overflow
id|uclong
id|sw_overflow
suffix:semicolon
multiline_comment|/* sw overflow counter */
DECL|member|comm_error
id|uclong
id|comm_error
suffix:semicolon
multiline_comment|/* frame/parity error counter */
DECL|member|ichar
id|uclong
id|ichar
suffix:semicolon
DECL|member|filler
id|uclong
id|filler
(braket
l_int|7
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;BUF_CTRL - This per channel structure contains&n; *&t;all Tx and Rx buffer control for a given channel.&n; */
DECL|struct|BUF_CTRL
r_struct
id|BUF_CTRL
(brace
DECL|member|flag_dma
id|uclong
id|flag_dma
suffix:semicolon
multiline_comment|/* buffers are in Host memory */
DECL|member|tx_bufaddr
id|uclong
id|tx_bufaddr
suffix:semicolon
multiline_comment|/* address of the tx buffer */
DECL|member|tx_bufsize
id|uclong
id|tx_bufsize
suffix:semicolon
multiline_comment|/* tx buffer size */
DECL|member|tx_threshold
id|uclong
id|tx_threshold
suffix:semicolon
multiline_comment|/* tx low water mark */
DECL|member|tx_get
id|uclong
id|tx_get
suffix:semicolon
multiline_comment|/* tail index tx buf */
DECL|member|tx_put
id|uclong
id|tx_put
suffix:semicolon
multiline_comment|/* head index tx buf */
DECL|member|rx_bufaddr
id|uclong
id|rx_bufaddr
suffix:semicolon
multiline_comment|/* address of the rx buffer */
DECL|member|rx_bufsize
id|uclong
id|rx_bufsize
suffix:semicolon
multiline_comment|/* rx buffer size */
DECL|member|rx_threshold
id|uclong
id|rx_threshold
suffix:semicolon
multiline_comment|/* rx high water mark */
DECL|member|rx_get
id|uclong
id|rx_get
suffix:semicolon
multiline_comment|/* tail index rx buf */
DECL|member|rx_put
id|uclong
id|rx_put
suffix:semicolon
multiline_comment|/* head index rx buf */
DECL|member|filler
id|uclong
id|filler
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* filler to align structures */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;BOARD_CTRL - This per board structure contains all global &n; *&t;control fields related to the board.&n; */
DECL|struct|BOARD_CTRL
r_struct
id|BOARD_CTRL
(brace
multiline_comment|/* static info provided by the on-board CPU */
DECL|member|n_channel
id|uclong
id|n_channel
suffix:semicolon
multiline_comment|/* number of channels */
DECL|member|fw_version
id|uclong
id|fw_version
suffix:semicolon
multiline_comment|/* firmware version */
multiline_comment|/* static info provided by the driver */
DECL|member|op_system
id|uclong
id|op_system
suffix:semicolon
multiline_comment|/* op_system id */
DECL|member|dr_version
id|uclong
id|dr_version
suffix:semicolon
multiline_comment|/* driver version */
multiline_comment|/* board control area */
DECL|member|inactivity
id|uclong
id|inactivity
suffix:semicolon
multiline_comment|/* inactivity control */
multiline_comment|/* host to FW commands */
DECL|member|hcmd_channel
id|uclong
id|hcmd_channel
suffix:semicolon
multiline_comment|/* channel number */
DECL|member|hcmd_param
id|uclong
id|hcmd_param
suffix:semicolon
multiline_comment|/* pointer to parameters */
multiline_comment|/* FW to Host commands */
DECL|member|fwcmd_channel
id|uclong
id|fwcmd_channel
suffix:semicolon
multiline_comment|/* channel number */
DECL|member|fwcmd_param
id|uclong
id|fwcmd_param
suffix:semicolon
multiline_comment|/* pointer to parameters */
DECL|member|zf_int_queue_addr
id|uclong
id|zf_int_queue_addr
suffix:semicolon
multiline_comment|/* offset for INT_QUEUE structure */
multiline_comment|/* filler so the structures are aligned */
DECL|member|filler
id|uclong
id|filler
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Host Interrupt Queue */
DECL|macro|QUEUE_SIZE
mdefine_line|#define QUEUE_SIZE&t;(10*MAX_CHAN)
DECL|struct|INT_QUEUE
r_struct
id|INT_QUEUE
(brace
DECL|member|intr_code
r_int
r_char
id|intr_code
(braket
id|QUEUE_SIZE
)braket
suffix:semicolon
DECL|member|channel
r_int
r_int
id|channel
(braket
id|QUEUE_SIZE
)braket
suffix:semicolon
DECL|member|param
r_int
r_int
id|param
(braket
id|QUEUE_SIZE
)braket
suffix:semicolon
DECL|member|put
r_int
r_int
id|put
suffix:semicolon
DECL|member|get
r_int
r_int
id|get
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;ZFW_CTRL - This is the data structure that includes all other&n; *&t;data structures used by the Firmware.&n; */
DECL|struct|ZFW_CTRL
r_struct
id|ZFW_CTRL
(brace
DECL|member|board_ctrl
r_struct
id|BOARD_CTRL
id|board_ctrl
suffix:semicolon
DECL|member|ch_ctrl
r_struct
id|CH_CTRL
id|ch_ctrl
(braket
id|MAX_CHAN
)braket
suffix:semicolon
DECL|member|buf_ctrl
r_struct
id|BUF_CTRL
id|buf_ctrl
(braket
id|MAX_CHAN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****************** ****************** *******************/
macro_line|#endif
multiline_comment|/* Per card data structure */
DECL|struct|cyclades_card
r_struct
id|cyclades_card
(brace
DECL|member|base_phys
r_int
r_int
id|base_phys
suffix:semicolon
DECL|member|ctl_phys
r_int
r_int
id|ctl_phys
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|ctl_addr
r_int
r_int
id|ctl_addr
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|num_chips
r_int
id|num_chips
suffix:semicolon
multiline_comment|/* 0 if card absent, -1 if Z/PCI, else Y */
DECL|member|first_line
r_int
id|first_line
suffix:semicolon
multiline_comment|/* minor number of first channel on card */
DECL|member|nports
r_int
id|nports
suffix:semicolon
multiline_comment|/* Number of ports in the card */
DECL|member|bus_index
r_int
id|bus_index
suffix:semicolon
multiline_comment|/* address shift - 0 for ISA, 1 for PCI */
DECL|member|intr_enabled
r_int
id|intr_enabled
suffix:semicolon
multiline_comment|/* FW Interrupt flag - 0 disabled, 1 enabled */
macro_line|#ifdef __KERNEL__
DECL|member|card_lock
id|spinlock_t
id|card_lock
suffix:semicolon
macro_line|#else
DECL|member|filler
id|uclong
id|filler
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|cyclades_chip
r_struct
id|cyclades_chip
(brace
DECL|member|filler
r_int
id|filler
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/***************************************&n; * Memory access functions/macros      *&n; * (required to support Alpha systems) *&n; ***************************************/
DECL|macro|cy_writeb
mdefine_line|#define cy_writeb(port,val)     {writeb((ucchar)(val),(ulong)(port)); mb();}
DECL|macro|cy_writew
mdefine_line|#define cy_writew(port,val)     {writew((ushort)(val),(ulong)(port)); mb();}
DECL|macro|cy_writel
mdefine_line|#define cy_writel(port,val)     {writel((uclong)(val),(ulong)(port)); mb();}
DECL|macro|cy_readb
mdefine_line|#define cy_readb(port)  readb(port)
DECL|macro|cy_readw
mdefine_line|#define cy_readw(port)  readw(port)
DECL|macro|cy_readl
mdefine_line|#define cy_readl(port)  readl(port)
multiline_comment|/*&n; * Statistics counters&n; */
DECL|struct|cyclades_icount
r_struct
id|cyclades_icount
(brace
DECL|member|cts
DECL|member|dsr
DECL|member|rng
DECL|member|dcd
DECL|member|tx
DECL|member|rx
id|__u32
id|cts
comma
id|dsr
comma
id|rng
comma
id|dcd
comma
id|tx
comma
id|rx
suffix:semicolon
DECL|member|frame
DECL|member|parity
DECL|member|overrun
DECL|member|brk
id|__u32
id|frame
comma
id|parity
comma
id|overrun
comma
id|brk
suffix:semicolon
DECL|member|buf_overrun
id|__u32
id|buf_overrun
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * &n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * For definitions of the flags field, see tty.h&n; */
DECL|struct|cyclades_port
r_struct
id|cyclades_port
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|card
r_int
id|card
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* UART type */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|cor1
DECL|member|cor2
DECL|member|cor3
DECL|member|cor4
DECL|member|cor5
r_int
id|cor1
comma
id|cor2
comma
id|cor3
comma
id|cor4
comma
id|cor5
suffix:semicolon
DECL|member|tbpr
DECL|member|tco
DECL|member|rbpr
DECL|member|rco
r_int
id|tbpr
comma
id|tco
comma
id|rbpr
comma
id|rco
suffix:semicolon
DECL|member|baud
r_int
id|baud
suffix:semicolon
DECL|member|rflow
r_int
id|rflow
suffix:semicolon
DECL|member|rtsdtr_inv
r_int
id|rtsdtr_inv
suffix:semicolon
DECL|member|chip_rev
r_int
id|chip_rev
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* to be pushed out ASAP */
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|last_active
r_int
r_int
id|last_active
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* # of fd on device */
DECL|member|breakon
r_int
id|breakon
suffix:semicolon
DECL|member|breakoff
r_int
id|breakoff
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
DECL|member|default_threshold
r_int
id|default_threshold
suffix:semicolon
DECL|member|default_timeout
r_int
id|default_timeout
suffix:semicolon
DECL|member|jiffies
r_int
r_int
id|jiffies
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|rflush_count
r_int
r_int
id|rflush_count
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|mon
r_struct
id|cyclades_monitor
id|mon
suffix:semicolon
DECL|member|idle_stats
r_struct
id|cyclades_idle_stats
id|idle_stats
suffix:semicolon
DECL|member|icount
r_struct
id|cyclades_icount
id|icount
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|shutdown_wait
id|wait_queue_head_t
id|shutdown_wait
suffix:semicolon
DECL|member|delta_msr_wait
id|wait_queue_head_t
id|delta_msr_wait
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at cy interrupt time.&n; */
DECL|macro|Cy_EVENT_READ_PROCESS
mdefine_line|#define Cy_EVENT_READ_PROCESS&t;&t;0
DECL|macro|Cy_EVENT_WRITE_WAKEUP
mdefine_line|#define Cy_EVENT_WRITE_WAKEUP&t;&t;1
DECL|macro|Cy_EVENT_HANGUP
mdefine_line|#define Cy_EVENT_HANGUP&t;&t;&t;2
DECL|macro|Cy_EVENT_BREAK
mdefine_line|#define Cy_EVENT_BREAK&t;&t;&t;3
DECL|macro|Cy_EVENT_OPEN_WAKEUP
mdefine_line|#define Cy_EVENT_OPEN_WAKEUP&t;&t;4
DECL|macro|Cy_EVENT_SHUTDOWN_WAKEUP
mdefine_line|#define Cy_EVENT_SHUTDOWN_WAKEUP&t;5
DECL|macro|Cy_EVENT_DELTA_WAKEUP
mdefine_line|#define&t;Cy_EVENT_DELTA_WAKEUP&t;&t;6
DECL|macro|Cy_EVENT_Z_RX_FULL
mdefine_line|#define&t;Cy_EVENT_Z_RX_FULL&t;&t;7
DECL|macro|CLOSING_WAIT_DELAY
mdefine_line|#define&t;CLOSING_WAIT_DELAY&t;30*HZ
DECL|macro|CY_CLOSING_WAIT_NONE
mdefine_line|#define CY_CLOSING_WAIT_NONE&t;65535
DECL|macro|CY_CLOSING_WAIT_INF
mdefine_line|#define CY_CLOSING_WAIT_INF&t;0
DECL|macro|CyMAX_CHIPS_PER_CARD
mdefine_line|#define CyMAX_CHIPS_PER_CARD&t;8
DECL|macro|CyMAX_CHAR_FIFO
mdefine_line|#define CyMAX_CHAR_FIFO&t;&t;12
DECL|macro|CyPORTS_PER_CHIP
mdefine_line|#define CyPORTS_PER_CHIP&t;4
DECL|macro|CD1400_MAX_SPEED
mdefine_line|#define&t;CD1400_MAX_SPEED&t;115200
DECL|macro|CyISA_Ywin
mdefine_line|#define&t;CyISA_Ywin&t;0x2000
DECL|macro|CyPCI_Ywin
mdefine_line|#define CyPCI_Ywin &t;0x4000
DECL|macro|CyPCI_Yctl
mdefine_line|#define CyPCI_Yctl &t;0x80
DECL|macro|CyPCI_Zctl
mdefine_line|#define CyPCI_Zctl &t;CTRL_WINDOW_SIZE
DECL|macro|CyPCI_Zwin
mdefine_line|#define CyPCI_Zwin &t;0x80000
DECL|macro|CyPCI_Ze_win
mdefine_line|#define CyPCI_Ze_win &t;(2 * CyPCI_Zwin)
DECL|macro|PCI_DEVICE_ID_MASK
mdefine_line|#define PCI_DEVICE_ID_MASK&t;0x06
multiline_comment|/**** CD1400 registers ****/
DECL|macro|CD1400_REV_G
mdefine_line|#define CD1400_REV_G&t;0x46
DECL|macro|CD1400_REV_J
mdefine_line|#define CD1400_REV_J&t;0x48
DECL|macro|CyRegSize
mdefine_line|#define CyRegSize  &t;0x0400
DECL|macro|Cy_HwReset
mdefine_line|#define Cy_HwReset &t;0x1400
DECL|macro|Cy_ClrIntr
mdefine_line|#define Cy_ClrIntr &t;0x1800
DECL|macro|Cy_EpldRev
mdefine_line|#define Cy_EpldRev &t;0x1e00
multiline_comment|/* Global Registers */
DECL|macro|CyGFRCR
mdefine_line|#define CyGFRCR&t;&t;(0x40*2)
DECL|macro|CyRevE
mdefine_line|#define      CyRevE&t;&t;(44)
DECL|macro|CyCAR
mdefine_line|#define CyCAR&t;&t;(0x68*2)
DECL|macro|CyCHAN_0
mdefine_line|#define      CyCHAN_0&t;&t;(0x00)
DECL|macro|CyCHAN_1
mdefine_line|#define      CyCHAN_1&t;&t;(0x01)
DECL|macro|CyCHAN_2
mdefine_line|#define      CyCHAN_2&t;&t;(0x02)
DECL|macro|CyCHAN_3
mdefine_line|#define      CyCHAN_3&t;&t;(0x03)
DECL|macro|CyGCR
mdefine_line|#define CyGCR&t;&t;(0x4B*2)
DECL|macro|CyCH0_SERIAL
mdefine_line|#define      CyCH0_SERIAL&t;(0x00)
DECL|macro|CyCH0_PARALLEL
mdefine_line|#define      CyCH0_PARALLEL&t;(0x80)
DECL|macro|CySVRR
mdefine_line|#define CySVRR&t;&t;(0x67*2)
DECL|macro|CySRModem
mdefine_line|#define      CySRModem&t;&t;(0x04)
DECL|macro|CySRTransmit
mdefine_line|#define      CySRTransmit&t;(0x02)
DECL|macro|CySRReceive
mdefine_line|#define      CySRReceive&t;(0x01)
DECL|macro|CyRICR
mdefine_line|#define CyRICR&t;&t;(0x44*2)
DECL|macro|CyTICR
mdefine_line|#define CyTICR&t;&t;(0x45*2)
DECL|macro|CyMICR
mdefine_line|#define CyMICR&t;&t;(0x46*2)
DECL|macro|CyICR0
mdefine_line|#define      CyICR0&t;&t;(0x00)
DECL|macro|CyICR1
mdefine_line|#define      CyICR1&t;&t;(0x01)
DECL|macro|CyICR2
mdefine_line|#define      CyICR2&t;&t;(0x02)
DECL|macro|CyICR3
mdefine_line|#define      CyICR3&t;&t;(0x03)
DECL|macro|CyRIR
mdefine_line|#define CyRIR&t;&t;(0x6B*2)
DECL|macro|CyTIR
mdefine_line|#define CyTIR&t;&t;(0x6A*2)
DECL|macro|CyMIR
mdefine_line|#define CyMIR&t;&t;(0x69*2)
DECL|macro|CyIRDirEq
mdefine_line|#define      CyIRDirEq&t;&t;(0x80)
DECL|macro|CyIRBusy
mdefine_line|#define      CyIRBusy&t;&t;(0x40)
DECL|macro|CyIRUnfair
mdefine_line|#define      CyIRUnfair&t;&t;(0x20)
DECL|macro|CyIRContext
mdefine_line|#define      CyIRContext&t;(0x1C)
DECL|macro|CyIRChannel
mdefine_line|#define      CyIRChannel&t;(0x03)
DECL|macro|CyPPR
mdefine_line|#define CyPPR &t;&t;(0x7E*2)
DECL|macro|CyCLOCK_20_1MS
mdefine_line|#define      CyCLOCK_20_1MS&t;(0x27)
DECL|macro|CyCLOCK_25_1MS
mdefine_line|#define      CyCLOCK_25_1MS&t;(0x31)
DECL|macro|CyCLOCK_25_5MS
mdefine_line|#define      CyCLOCK_25_5MS&t;(0xf4)
DECL|macro|CyCLOCK_60_1MS
mdefine_line|#define      CyCLOCK_60_1MS&t;(0x75)
DECL|macro|CyCLOCK_60_2MS
mdefine_line|#define      CyCLOCK_60_2MS&t;(0xea)
multiline_comment|/* Virtual Registers */
DECL|macro|CyRIVR
mdefine_line|#define CyRIVR&t;&t;(0x43*2)
DECL|macro|CyTIVR
mdefine_line|#define CyTIVR&t;&t;(0x42*2)
DECL|macro|CyMIVR
mdefine_line|#define CyMIVR&t;&t;(0x41*2)
DECL|macro|CyIVRMask
mdefine_line|#define      CyIVRMask (0x07)
DECL|macro|CyIVRRxEx
mdefine_line|#define      CyIVRRxEx (0x07)
DECL|macro|CyIVRRxOK
mdefine_line|#define      CyIVRRxOK (0x03)
DECL|macro|CyIVRTxOK
mdefine_line|#define      CyIVRTxOK (0x02)
DECL|macro|CyIVRMdmOK
mdefine_line|#define      CyIVRMdmOK (0x01)
DECL|macro|CyTDR
mdefine_line|#define CyTDR&t;&t;(0x63*2)
DECL|macro|CyRDSR
mdefine_line|#define CyRDSR&t;&t;(0x62*2)
DECL|macro|CyTIMEOUT
mdefine_line|#define      CyTIMEOUT&t;&t;(0x80)
DECL|macro|CySPECHAR
mdefine_line|#define      CySPECHAR&t;&t;(0x70)
DECL|macro|CyBREAK
mdefine_line|#define      CyBREAK&t;&t;(0x08)
DECL|macro|CyPARITY
mdefine_line|#define      CyPARITY&t;&t;(0x04)
DECL|macro|CyFRAME
mdefine_line|#define      CyFRAME&t;&t;(0x02)
DECL|macro|CyOVERRUN
mdefine_line|#define      CyOVERRUN&t;&t;(0x01)
DECL|macro|CyMISR
mdefine_line|#define CyMISR&t;&t;(0x4C*2)
multiline_comment|/* see CyMCOR_ and CyMSVR_ for bits*/
DECL|macro|CyEOSRR
mdefine_line|#define CyEOSRR&t;&t;(0x60*2)
multiline_comment|/* Channel Registers */
DECL|macro|CyLIVR
mdefine_line|#define CyLIVR&t;&t;(0x18*2)
DECL|macro|CyMscsr
mdefine_line|#define      CyMscsr&t;&t;(0x01)
DECL|macro|CyTdsr
mdefine_line|#define      CyTdsr&t;&t;(0x02)
DECL|macro|CyRgdsr
mdefine_line|#define      CyRgdsr&t;&t;(0x03)
DECL|macro|CyRedsr
mdefine_line|#define      CyRedsr&t;&t;(0x07)
DECL|macro|CyCCR
mdefine_line|#define CyCCR&t;&t;(0x05*2)
multiline_comment|/* Format 1 */
DECL|macro|CyCHAN_RESET
mdefine_line|#define      CyCHAN_RESET&t;(0x80)
DECL|macro|CyCHIP_RESET
mdefine_line|#define      CyCHIP_RESET&t;(0x81)
DECL|macro|CyFlushTransFIFO
mdefine_line|#define      CyFlushTransFIFO&t;(0x82)
multiline_comment|/* Format 2 */
DECL|macro|CyCOR_CHANGE
mdefine_line|#define      CyCOR_CHANGE&t;(0x40)
DECL|macro|CyCOR1ch
mdefine_line|#define      CyCOR1ch&t;&t;(0x02)
DECL|macro|CyCOR2ch
mdefine_line|#define      CyCOR2ch&t;&t;(0x04)
DECL|macro|CyCOR3ch
mdefine_line|#define      CyCOR3ch&t;&t;(0x08)
multiline_comment|/* Format 3 */
DECL|macro|CySEND_SPEC_1
mdefine_line|#define      CySEND_SPEC_1&t;(0x21)
DECL|macro|CySEND_SPEC_2
mdefine_line|#define      CySEND_SPEC_2&t;(0x22)
DECL|macro|CySEND_SPEC_3
mdefine_line|#define      CySEND_SPEC_3&t;(0x23)
DECL|macro|CySEND_SPEC_4
mdefine_line|#define      CySEND_SPEC_4&t;(0x24)
multiline_comment|/* Format 4 */
DECL|macro|CyCHAN_CTL
mdefine_line|#define      CyCHAN_CTL&t;&t;(0x10)
DECL|macro|CyDIS_RCVR
mdefine_line|#define      CyDIS_RCVR&t;&t;(0x01)
DECL|macro|CyENB_RCVR
mdefine_line|#define      CyENB_RCVR&t;&t;(0x02)
DECL|macro|CyDIS_XMTR
mdefine_line|#define      CyDIS_XMTR&t;&t;(0x04)
DECL|macro|CyENB_XMTR
mdefine_line|#define      CyENB_XMTR&t;&t;(0x08)
DECL|macro|CySRER
mdefine_line|#define CySRER&t;&t;(0x06*2)
DECL|macro|CyMdmCh
mdefine_line|#define      CyMdmCh&t;&t;(0x80)
DECL|macro|CyRxData
mdefine_line|#define      CyRxData&t;&t;(0x10)
DECL|macro|CyTxRdy
mdefine_line|#define      CyTxRdy&t;&t;(0x04)
DECL|macro|CyTxMpty
mdefine_line|#define      CyTxMpty&t;&t;(0x02)
DECL|macro|CyNNDT
mdefine_line|#define      CyNNDT&t;&t;(0x01)
DECL|macro|CyCOR1
mdefine_line|#define CyCOR1&t;&t;(0x08*2)
DECL|macro|CyPARITY_NONE
mdefine_line|#define      CyPARITY_NONE&t;(0x00)
DECL|macro|CyPARITY_0
mdefine_line|#define      CyPARITY_0&t;&t;(0x20)
DECL|macro|CyPARITY_1
mdefine_line|#define      CyPARITY_1&t;&t;(0xA0)
DECL|macro|CyPARITY_E
mdefine_line|#define      CyPARITY_E&t;&t;(0x40)
DECL|macro|CyPARITY_O
mdefine_line|#define      CyPARITY_O&t;&t;(0xC0)
DECL|macro|Cy_1_STOP
mdefine_line|#define      Cy_1_STOP&t;&t;(0x00)
DECL|macro|Cy_1_5_STOP
mdefine_line|#define      Cy_1_5_STOP&t;(0x04)
DECL|macro|Cy_2_STOP
mdefine_line|#define      Cy_2_STOP&t;&t;(0x08)
DECL|macro|Cy_5_BITS
mdefine_line|#define      Cy_5_BITS&t;&t;(0x00)
DECL|macro|Cy_6_BITS
mdefine_line|#define      Cy_6_BITS&t;&t;(0x01)
DECL|macro|Cy_7_BITS
mdefine_line|#define      Cy_7_BITS&t;&t;(0x02)
DECL|macro|Cy_8_BITS
mdefine_line|#define      Cy_8_BITS&t;&t;(0x03)
DECL|macro|CyCOR2
mdefine_line|#define CyCOR2&t;&t;(0x09*2)
DECL|macro|CyIXM
mdefine_line|#define      CyIXM&t;&t;(0x80)
DECL|macro|CyTxIBE
mdefine_line|#define      CyTxIBE&t;&t;(0x40)
DECL|macro|CyETC
mdefine_line|#define      CyETC&t;&t;(0x20)
DECL|macro|CyAUTO_TXFL
mdefine_line|#define      CyAUTO_TXFL&t;(0x60)
DECL|macro|CyLLM
mdefine_line|#define      CyLLM&t;&t;(0x10)
DECL|macro|CyRLM
mdefine_line|#define      CyRLM&t;&t;(0x08)
DECL|macro|CyRtsAO
mdefine_line|#define      CyRtsAO&t;&t;(0x04)
DECL|macro|CyCtsAE
mdefine_line|#define      CyCtsAE&t;&t;(0x02)
DECL|macro|CyDsrAE
mdefine_line|#define      CyDsrAE&t;&t;(0x01)
DECL|macro|CyCOR3
mdefine_line|#define CyCOR3&t;&t;(0x0A*2)
DECL|macro|CySPL_CH_DRANGE
mdefine_line|#define      CySPL_CH_DRANGE&t;(0x80)  /* special character detect range */
DECL|macro|CySPL_CH_DET1
mdefine_line|#define      CySPL_CH_DET1&t;(0x40)  /* enable special character detection&n;                                                               on SCHR4-SCHR3 */
DECL|macro|CyFL_CTRL_TRNSP
mdefine_line|#define      CyFL_CTRL_TRNSP&t;(0x20)  /* Flow Control Transparency */
DECL|macro|CySPL_CH_DET2
mdefine_line|#define      CySPL_CH_DET2&t;(0x10)  /* Enable special character detection&n;                                                               on SCHR2-SCHR1 */
DECL|macro|CyREC_FIFO
mdefine_line|#define      CyREC_FIFO&t;&t;(0x0F)  /* Receive FIFO threshold */
DECL|macro|CyCOR4
mdefine_line|#define CyCOR4&t;&t;(0x1E*2)
DECL|macro|CyCOR5
mdefine_line|#define CyCOR5&t;&t;(0x1F*2)
DECL|macro|CyCCSR
mdefine_line|#define CyCCSR&t;&t;(0x0B*2)
DECL|macro|CyRxEN
mdefine_line|#define      CyRxEN&t;&t;(0x80)
DECL|macro|CyRxFloff
mdefine_line|#define      CyRxFloff&t;&t;(0x40)
DECL|macro|CyRxFlon
mdefine_line|#define      CyRxFlon&t;&t;(0x20)
DECL|macro|CyTxEN
mdefine_line|#define      CyTxEN&t;&t;(0x08)
DECL|macro|CyTxFloff
mdefine_line|#define      CyTxFloff&t;&t;(0x04)
DECL|macro|CyTxFlon
mdefine_line|#define      CyTxFlon&t;&t;(0x02)
DECL|macro|CyRDCR
mdefine_line|#define CyRDCR&t;&t;(0x0E*2)
DECL|macro|CySCHR1
mdefine_line|#define CySCHR1&t;&t;(0x1A*2)
DECL|macro|CySCHR2
mdefine_line|#define CySCHR2 &t;(0x1B*2)
DECL|macro|CySCHR3
mdefine_line|#define CySCHR3&t;&t;(0x1C*2)
DECL|macro|CySCHR4
mdefine_line|#define CySCHR4&t;&t;(0x1D*2)
DECL|macro|CySCRL
mdefine_line|#define CySCRL&t;&t;(0x22*2)
DECL|macro|CySCRH
mdefine_line|#define CySCRH&t;&t;(0x23*2)
DECL|macro|CyLNC
mdefine_line|#define CyLNC&t;&t;(0x24*2)
DECL|macro|CyMCOR1
mdefine_line|#define CyMCOR1 &t;(0x15*2)
DECL|macro|CyMCOR2
mdefine_line|#define CyMCOR2&t;&t;(0x16*2)
DECL|macro|CyRTPR
mdefine_line|#define CyRTPR&t;&t;(0x21*2)
DECL|macro|CyMSVR1
mdefine_line|#define CyMSVR1&t;&t;(0x6C*2)
DECL|macro|CyMSVR2
mdefine_line|#define CyMSVR2&t;&t;(0x6D*2)
DECL|macro|CyANY_DELTA
mdefine_line|#define      CyANY_DELTA&t;(0xF0)
DECL|macro|CyDSR
mdefine_line|#define      CyDSR&t;&t;(0x80)
DECL|macro|CyCTS
mdefine_line|#define      CyCTS&t;&t;(0x40)
DECL|macro|CyRI
mdefine_line|#define      CyRI&t;&t;(0x20)
DECL|macro|CyDCD
mdefine_line|#define      CyDCD&t;&t;(0x10)
DECL|macro|CyDTR
mdefine_line|#define      CyDTR              (0x02)
DECL|macro|CyRTS
mdefine_line|#define      CyRTS              (0x01)
DECL|macro|CyPVSR
mdefine_line|#define CyPVSR&t;&t;(0x6F*2)
DECL|macro|CyRBPR
mdefine_line|#define CyRBPR&t;&t;(0x78*2)
DECL|macro|CyRCOR
mdefine_line|#define CyRCOR&t;&t;(0x7C*2)
DECL|macro|CyTBPR
mdefine_line|#define CyTBPR&t;&t;(0x72*2)
DECL|macro|CyTCOR
mdefine_line|#define CyTCOR&t;&t;(0x76*2)
multiline_comment|/* Custom Registers */
DECL|macro|CyPLX_VER
mdefine_line|#define&t;CyPLX_VER&t;(0x3400)
DECL|macro|PLX_9050
mdefine_line|#define&t;PLX_9050&t;0x0b
DECL|macro|PLX_9060
mdefine_line|#define&t;PLX_9060&t;0x0c
DECL|macro|PLX_9080
mdefine_line|#define&t;PLX_9080&t;0x0d
multiline_comment|/***************************************************************************/
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_CYCLADES_H */
eof
