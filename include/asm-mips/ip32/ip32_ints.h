multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Harald Koerfgen&n; */
macro_line|#ifndef __ASM_IP32_INTS_H
DECL|macro|__ASM_IP32_INTS_H
mdefine_line|#define __ASM_IP32_INTS_H
multiline_comment|/*&n; * This list reflects the assignment of interrupt numbers to&n; * interrupting events.  Order is fairly irrelevant to handling&n; * priority.  This differs from irix.&n; */
multiline_comment|/* CPU */
DECL|macro|CLOCK_IRQ
mdefine_line|#define CLOCK_IRQ&t;&t;&t;0
multiline_comment|/* MACE */
DECL|macro|MACE_VID_IN1_IRQ
mdefine_line|#define MACE_VID_IN1_IRQ&t;&t;1
DECL|macro|MACE_VID_IN2_IRQ
mdefine_line|#define MACE_VID_IN2_IRQ&t;&t;2
DECL|macro|MACE_VID_OUT_IRQ
mdefine_line|#define MACE_VID_OUT_IRQ&t;&t;3
DECL|macro|MACE_ETHERNET_IRQ
mdefine_line|#define MACE_ETHERNET_IRQ&t;&t;4
multiline_comment|/* SUPERIO, MISC, and AUDIO are MACEISA */
DECL|macro|MACE_PCI_BRIDGE_IRQ
mdefine_line|#define MACE_PCI_BRIDGE_IRQ&t;&t;8
multiline_comment|/* MACEPCI */
DECL|macro|MACEPCI_SCSI0_IRQ
mdefine_line|#define MACEPCI_SCSI0_IRQ&t;&t;9
DECL|macro|MACEPCI_SCSI1_IRQ
mdefine_line|#define MACEPCI_SCSI1_IRQ&t;&t;10
DECL|macro|MACEPCI_SLOT0_IRQ
mdefine_line|#define MACEPCI_SLOT0_IRQ&t;&t;11
DECL|macro|MACEPCI_SLOT1_IRQ
mdefine_line|#define MACEPCI_SLOT1_IRQ&t;&t;12
DECL|macro|MACEPCI_SLOT2_IRQ
mdefine_line|#define MACEPCI_SLOT2_IRQ&t;&t;13
DECL|macro|MACEPCI_SHARED0_IRQ
mdefine_line|#define MACEPCI_SHARED0_IRQ&t;&t;14
DECL|macro|MACEPCI_SHARED1_IRQ
mdefine_line|#define MACEPCI_SHARED1_IRQ&t;&t;15
DECL|macro|MACEPCI_SHARED2_IRQ
mdefine_line|#define MACEPCI_SHARED2_IRQ&t;&t;16
multiline_comment|/* CRIME */
DECL|macro|CRIME_GBE0_IRQ
mdefine_line|#define CRIME_GBE0_IRQ&t;&t;&t;17
DECL|macro|CRIME_GBE1_IRQ
mdefine_line|#define CRIME_GBE1_IRQ&t;&t;&t;18
DECL|macro|CRIME_GBE2_IRQ
mdefine_line|#define CRIME_GBE2_IRQ&t;&t;&t;19
DECL|macro|CRIME_GBE3_IRQ
mdefine_line|#define CRIME_GBE3_IRQ&t;&t;&t;20
DECL|macro|CRIME_CPUERR_IRQ
mdefine_line|#define CRIME_CPUERR_IRQ&t;&t;21
DECL|macro|CRIME_MEMERR_IRQ
mdefine_line|#define CRIME_MEMERR_IRQ&t;&t;22
DECL|macro|CRIME_RE_EMPTY_E_IRQ
mdefine_line|#define CRIME_RE_EMPTY_E_IRQ&t;&t;23
DECL|macro|CRIME_RE_FULL_E_IRQ
mdefine_line|#define CRIME_RE_FULL_E_IRQ&t;&t;24
DECL|macro|CRIME_RE_IDLE_E_IRQ
mdefine_line|#define CRIME_RE_IDLE_E_IRQ&t;&t;25
DECL|macro|CRIME_RE_EMPTY_L_IRQ
mdefine_line|#define CRIME_RE_EMPTY_L_IRQ&t;&t;26
DECL|macro|CRIME_RE_FULL_L_IRQ
mdefine_line|#define CRIME_RE_FULL_L_IRQ&t;&t;27
DECL|macro|CRIME_RE_IDLE_L_IRQ
mdefine_line|#define CRIME_RE_IDLE_L_IRQ&t;&t;28
DECL|macro|CRIME_SOFT0_IRQ
mdefine_line|#define CRIME_SOFT0_IRQ&t;&t;&t;29
DECL|macro|CRIME_SOFT1_IRQ
mdefine_line|#define CRIME_SOFT1_IRQ&t;&t;&t;30
DECL|macro|CRIME_SOFT2_IRQ
mdefine_line|#define CRIME_SOFT2_IRQ&t;&t;&t;31
DECL|macro|CRIME_SYSCORERR_IRQ
mdefine_line|#define CRIME_SYSCORERR_IRQ&t;&t;CRIME_SOFT2_IRQ
DECL|macro|CRIME_VICE_IRQ
mdefine_line|#define CRIME_VICE_IRQ&t;&t;&t;32
multiline_comment|/* MACEISA */
DECL|macro|MACEISA_AUDIO_SW_IRQ
mdefine_line|#define MACEISA_AUDIO_SW_IRQ&t;&t;33
DECL|macro|MACEISA_AUDIO_SC_IRQ
mdefine_line|#define MACEISA_AUDIO_SC_IRQ&t;&t;34
DECL|macro|MACEISA_AUDIO1_DMAT_IRQ
mdefine_line|#define MACEISA_AUDIO1_DMAT_IRQ&t;&t;35
DECL|macro|MACEISA_AUDIO1_OF_IRQ
mdefine_line|#define MACEISA_AUDIO1_OF_IRQ&t;&t;36
DECL|macro|MACEISA_AUDIO2_DMAT_IRQ
mdefine_line|#define MACEISA_AUDIO2_DMAT_IRQ&t;&t;37
DECL|macro|MACEISA_AUDIO2_MERR_IRQ
mdefine_line|#define MACEISA_AUDIO2_MERR_IRQ&t;&t;38
DECL|macro|MACEISA_AUDIO3_DMAT_IRQ
mdefine_line|#define MACEISA_AUDIO3_DMAT_IRQ&t;&t;39
DECL|macro|MACEISA_AUDIO3_MERR_IRQ
mdefine_line|#define MACEISA_AUDIO3_MERR_IRQ&t;&t;40
DECL|macro|MACEISA_RTC_IRQ
mdefine_line|#define MACEISA_RTC_IRQ&t;&t;&t;41
DECL|macro|MACEISA_KEYB_IRQ
mdefine_line|#define MACEISA_KEYB_IRQ&t;&t;42
multiline_comment|/* MACEISA_KEYB_POLL is not an IRQ */
DECL|macro|MACEISA_MOUSE_IRQ
mdefine_line|#define MACEISA_MOUSE_IRQ&t;&t;44
multiline_comment|/* MACEISA_MOUSE_POLL is not an IRQ */
DECL|macro|MACEISA_TIMER0_IRQ
mdefine_line|#define MACEISA_TIMER0_IRQ&t;&t;46
DECL|macro|MACEISA_TIMER1_IRQ
mdefine_line|#define MACEISA_TIMER1_IRQ&t;&t;47
DECL|macro|MACEISA_TIMER2_IRQ
mdefine_line|#define MACEISA_TIMER2_IRQ&t;&t;48
DECL|macro|MACEISA_PARALLEL_IRQ
mdefine_line|#define MACEISA_PARALLEL_IRQ&t;&t;49
DECL|macro|MACEISA_PAR_CTXA_IRQ
mdefine_line|#define MACEISA_PAR_CTXA_IRQ&t;&t;50
DECL|macro|MACEISA_PAR_CTXB_IRQ
mdefine_line|#define MACEISA_PAR_CTXB_IRQ&t;&t;51
DECL|macro|MACEISA_PAR_MERR_IRQ
mdefine_line|#define MACEISA_PAR_MERR_IRQ&t;&t;52
DECL|macro|MACEISA_SERIAL1_IRQ
mdefine_line|#define MACEISA_SERIAL1_IRQ&t;&t;53
DECL|macro|MACEISA_SERIAL1_TDMAT_IRQ
mdefine_line|#define MACEISA_SERIAL1_TDMAT_IRQ&t;54
DECL|macro|MACEISA_SERIAL1_TDMAPR_IRQ
mdefine_line|#define MACEISA_SERIAL1_TDMAPR_IRQ&t;55
DECL|macro|MACEISA_SERIAL1_TDMAME_IRQ
mdefine_line|#define MACEISA_SERIAL1_TDMAME_IRQ&t;56
DECL|macro|MACEISA_SERIAL1_RDMAT_IRQ
mdefine_line|#define MACEISA_SERIAL1_RDMAT_IRQ&t;57
DECL|macro|MACEISA_SERIAL1_RDMAOR_IRQ
mdefine_line|#define MACEISA_SERIAL1_RDMAOR_IRQ&t;58
DECL|macro|MACEISA_SERIAL2_IRQ
mdefine_line|#define MACEISA_SERIAL2_IRQ&t;&t;59
DECL|macro|MACEISA_SERIAL2_TDMAT_IRQ
mdefine_line|#define MACEISA_SERIAL2_TDMAT_IRQ&t;60
DECL|macro|MACEISA_SERIAL2_TDMAPR_IRQ
mdefine_line|#define MACEISA_SERIAL2_TDMAPR_IRQ&t;61
DECL|macro|MACEISA_SERIAL2_TDMAME_IRQ
mdefine_line|#define MACEISA_SERIAL2_TDMAME_IRQ&t;62
DECL|macro|MACEISA_SERIAL2_RDMAT_IRQ
mdefine_line|#define MACEISA_SERIAL2_RDMAT_IRQ&t;63
DECL|macro|MACEISA_SERIAL2_RDMAOR_IRQ
mdefine_line|#define MACEISA_SERIAL2_RDMAOR_IRQ&t;64
DECL|macro|IP32_IRQ_MAX
mdefine_line|#define IP32_IRQ_MAX&t;&t;&t;MACEISA_SERIAL2_RDMAOR_IRQ
macro_line|#endif /* __ASM_IP32_INTS_H */
eof
