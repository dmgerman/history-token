multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * mc.h: Definitions for SGI Memory Controller&n; *&n; * Copyright (C) 1996 David S. Miller&n; * Copyright (C) 1999 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _SGI_MC_H
DECL|macro|_SGI_MC_H
mdefine_line|#define _SGI_MC_H
DECL|struct|sgimc_regs
r_struct
id|sgimc_regs
(brace
DECL|member|_unused0
id|u32
id|_unused0
suffix:semicolon
DECL|member|cpuctrl0
r_volatile
id|u32
id|cpuctrl0
suffix:semicolon
multiline_comment|/* CPU control register 0, readwrite */
DECL|macro|SGIMC_CCTRL0_REFS
mdefine_line|#define SGIMC_CCTRL0_REFS&t;0x0000000f /* REFS mask */
DECL|macro|SGIMC_CCTRL0_EREFRESH
mdefine_line|#define SGIMC_CCTRL0_EREFRESH&t;0x00000010 /* Memory refresh enable */
DECL|macro|SGIMC_CCTRL0_EPERRGIO
mdefine_line|#define SGIMC_CCTRL0_EPERRGIO&t;0x00000020 /* GIO parity error enable */
DECL|macro|SGIMC_CCTRL0_EPERRMEM
mdefine_line|#define SGIMC_CCTRL0_EPERRMEM&t;0x00000040 /* Main mem parity error enable */
DECL|macro|SGIMC_CCTRL0_EPERRCPU
mdefine_line|#define SGIMC_CCTRL0_EPERRCPU&t;0x00000080 /* CPU bus parity error enable */
DECL|macro|SGIMC_CCTRL0_WDOG
mdefine_line|#define SGIMC_CCTRL0_WDOG&t;0x00000100 /* Watchdog timer enable */
DECL|macro|SGIMC_CCTRL0_SYSINIT
mdefine_line|#define SGIMC_CCTRL0_SYSINIT&t;0x00000200 /* System init bit */
DECL|macro|SGIMC_CCTRL0_GFXRESET
mdefine_line|#define SGIMC_CCTRL0_GFXRESET&t;0x00000400 /* Graphics interface reset */
DECL|macro|SGIMC_CCTRL0_EISALOCK
mdefine_line|#define SGIMC_CCTRL0_EISALOCK&t;0x00000800 /* Lock CPU from memory for EISA */
DECL|macro|SGIMC_CCTRL0_EPERRSCMD
mdefine_line|#define SGIMC_CCTRL0_EPERRSCMD&t;0x00001000 /* SysCMD bus parity error enable */
DECL|macro|SGIMC_CCTRL0_IENAB
mdefine_line|#define SGIMC_CCTRL0_IENAB&t;0x00002000 /* Allow interrupts from MC */
DECL|macro|SGIMC_CCTRL0_ESNOOP
mdefine_line|#define SGIMC_CCTRL0_ESNOOP&t;0x00004000 /* Snooping I/O enable */
DECL|macro|SGIMC_CCTRL0_EPROMWR
mdefine_line|#define SGIMC_CCTRL0_EPROMWR&t;0x00008000 /* Prom writes from cpu enable */
DECL|macro|SGIMC_CCTRL0_WRESETPMEM
mdefine_line|#define SGIMC_CCTRL0_WRESETPMEM&t;0x00010000 /* Perform warm reset, preserves mem */
DECL|macro|SGIMC_CCTRL0_LENDIAN
mdefine_line|#define SGIMC_CCTRL0_LENDIAN&t;0x00020000 /* Put MC in little-endian mode */
DECL|macro|SGIMC_CCTRL0_WRESETDMEM
mdefine_line|#define SGIMC_CCTRL0_WRESETDMEM&t;0x00040000 /* Warm reset, destroys mem contents */
DECL|macro|SGIMC_CCTRL0_CMEMBADPAR
mdefine_line|#define SGIMC_CCTRL0_CMEMBADPAR&t;0x02000000 /* Generate bad perr from cpu to mem */
DECL|macro|SGIMC_CCTRL0_R4KNOCHKPARR
mdefine_line|#define SGIMC_CCTRL0_R4KNOCHKPARR 0x04000000 /* Don&squot;t chk parity on mem data reads */
DECL|macro|SGIMC_CCTRL0_GIOBTOB
mdefine_line|#define SGIMC_CCTRL0_GIOBTOB&t;0x08000000 /* Allow GIO back to back writes */
DECL|member|_unused1
id|u32
id|_unused1
suffix:semicolon
DECL|member|cpuctrl1
r_volatile
id|u32
id|cpuctrl1
suffix:semicolon
multiline_comment|/* CPU control register 1, readwrite */
DECL|macro|SGIMC_CCTRL1_EGIOTIMEO
mdefine_line|#define SGIMC_CCTRL1_EGIOTIMEO&t;0x00000010 /* GIO bus timeout enable */
DECL|macro|SGIMC_CCTRL1_FIXEDEHPC
mdefine_line|#define SGIMC_CCTRL1_FIXEDEHPC&t;0x00001000 /* Fixed HPC endianness */
DECL|macro|SGIMC_CCTRL1_LITTLEHPC
mdefine_line|#define SGIMC_CCTRL1_LITTLEHPC&t;0x00002000 /* Little endian HPC */
DECL|macro|SGIMC_CCTRL1_FIXEDEEXP0
mdefine_line|#define SGIMC_CCTRL1_FIXEDEEXP0&t;0x00004000 /* Fixed EXP0 endianness */
DECL|macro|SGIMC_CCTRL1_LITTLEEXP0
mdefine_line|#define SGIMC_CCTRL1_LITTLEEXP0&t;0x00008000 /* Little endian EXP0 */
DECL|macro|SGIMC_CCTRL1_FIXEDEEXP1
mdefine_line|#define SGIMC_CCTRL1_FIXEDEEXP1&t;0x00010000 /* Fixed EXP1 endianness */
DECL|macro|SGIMC_CCTRL1_LITTLEEXP1
mdefine_line|#define SGIMC_CCTRL1_LITTLEEXP1&t;0x00020000 /* Little endian EXP1 */
DECL|member|_unused2
id|u32
id|_unused2
suffix:semicolon
DECL|member|watchdogt
r_volatile
id|u32
id|watchdogt
suffix:semicolon
multiline_comment|/* Watchdog reg rdonly, write clears */
DECL|member|_unused3
id|u32
id|_unused3
suffix:semicolon
DECL|member|systemid
r_volatile
id|u32
id|systemid
suffix:semicolon
multiline_comment|/* MC system ID register, readonly */
DECL|macro|SGIMC_SYSID_MASKREV
mdefine_line|#define SGIMC_SYSID_MASKREV&t;0x0000000f /* Revision of MC controller */
DECL|macro|SGIMC_SYSID_EPRESENT
mdefine_line|#define SGIMC_SYSID_EPRESENT&t;0x00000010 /* Indicates presence of EISA bus */
DECL|member|_unused4
id|u32
id|_unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|divider
r_volatile
id|u32
id|divider
suffix:semicolon
multiline_comment|/* Divider reg for RPSS */
DECL|member|_unused5
id|u32
id|_unused5
suffix:semicolon
DECL|member|eeprom
r_volatile
id|u32
id|eeprom
suffix:semicolon
multiline_comment|/* EEPROM byte reg for r4k */
DECL|macro|SGIMC_EEPROM_PRE
mdefine_line|#define SGIMC_EEPROM_PRE&t;0x00000001 /* eeprom chip PRE pin assertion */
DECL|macro|SGIMC_EEPROM_CSEL
mdefine_line|#define SGIMC_EEPROM_CSEL&t;0x00000002 /* Active high, eeprom chip select */
DECL|macro|SGIMC_EEPROM_SECLOCK
mdefine_line|#define SGIMC_EEPROM_SECLOCK&t;0x00000004 /* EEPROM serial clock */
DECL|macro|SGIMC_EEPROM_SDATAO
mdefine_line|#define SGIMC_EEPROM_SDATAO&t;0x00000008 /* Serial EEPROM data-out */
DECL|macro|SGIMC_EEPROM_SDATAI
mdefine_line|#define SGIMC_EEPROM_SDATAI&t;0x00000010 /* Serial EEPROM data-in */
DECL|member|_unused6
id|u32
id|_unused6
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|rcntpre
r_volatile
id|u32
id|rcntpre
suffix:semicolon
multiline_comment|/* Preload refresh counter */
DECL|member|_unused7
id|u32
id|_unused7
suffix:semicolon
DECL|member|rcounter
r_volatile
id|u32
id|rcounter
suffix:semicolon
multiline_comment|/* Readonly refresh counter */
DECL|member|_unused8
id|u32
id|_unused8
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|giopar
r_volatile
id|u32
id|giopar
suffix:semicolon
multiline_comment|/* Parameter word for GIO64 */
DECL|macro|SGIMC_GIOPAR_HPC64
mdefine_line|#define SGIMC_GIOPAR_HPC64&t;0x00000001 /* HPC talks to GIO using 64-bits */
DECL|macro|SGIMC_GIOPAR_GFX64
mdefine_line|#define SGIMC_GIOPAR_GFX64&t;0x00000002 /* GFX talks to GIO using 64-bits */
DECL|macro|SGIMC_GIOPAR_EXP064
mdefine_line|#define SGIMC_GIOPAR_EXP064&t;0x00000004 /* EXP(slot0) talks using 64-bits */
DECL|macro|SGIMC_GIOPAR_EXP164
mdefine_line|#define SGIMC_GIOPAR_EXP164&t;0x00000008 /* EXP(slot1) talks using 64-bits */
DECL|macro|SGIMC_GIOPAR_EISA64
mdefine_line|#define SGIMC_GIOPAR_EISA64&t;0x00000010 /* EISA bus talks 64-bits to GIO */
DECL|macro|SGIMC_GIOPAR_HPC264
mdefine_line|#define SGIMC_GIOPAR_HPC264&t;0x00000020 /* 2nd HPX talks 64-bits to GIO */
DECL|macro|SGIMC_GIOPAR_RTIMEGFX
mdefine_line|#define SGIMC_GIOPAR_RTIMEGFX&t;0x00000040 /* GFX device has realtime attr */
DECL|macro|SGIMC_GIOPAR_RTIMEEXP0
mdefine_line|#define SGIMC_GIOPAR_RTIMEEXP0&t;0x00000080 /* EXP(slot0) has realtime attr */
DECL|macro|SGIMC_GIOPAR_RTIMEEXP1
mdefine_line|#define SGIMC_GIOPAR_RTIMEEXP1&t;0x00000100 /* EXP(slot1) has realtime attr */
DECL|macro|SGIMC_GIOPAR_MASTEREISA
mdefine_line|#define SGIMC_GIOPAR_MASTEREISA&t;0x00000200 /* EISA bus can act as bus master */
DECL|macro|SGIMC_GIOPAR_ONEBUS
mdefine_line|#define SGIMC_GIOPAR_ONEBUS&t;0x00000400 /* Exists one GIO64 pipelined bus */
DECL|macro|SGIMC_GIOPAR_MASTERGFX
mdefine_line|#define SGIMC_GIOPAR_MASTERGFX&t;0x00000800 /* GFX can act as a bus master */
DECL|macro|SGIMC_GIOPAR_MASTEREXP0
mdefine_line|#define SGIMC_GIOPAR_MASTEREXP0&t;0x00001000 /* EXP(slot0) can bus master */
DECL|macro|SGIMC_GIOPAR_MASTEREXP1
mdefine_line|#define SGIMC_GIOPAR_MASTEREXP1&t;0x00002000 /* EXP(slot1) can bus master */
DECL|macro|SGIMC_GIOPAR_PLINEEXP0
mdefine_line|#define SGIMC_GIOPAR_PLINEEXP0&t;0x00004000 /* EXP(slot0) has pipeline attr */
DECL|macro|SGIMC_GIOPAR_PLINEEXP1
mdefine_line|#define SGIMC_GIOPAR_PLINEEXP1&t;0x00008000 /* EXP(slot1) has pipeline attr */
DECL|member|_unused9
id|u32
id|_unused9
suffix:semicolon
DECL|member|cputp
r_volatile
id|u32
id|cputp
suffix:semicolon
multiline_comment|/* CPU bus arb time period */
DECL|member|_unused10
id|u32
id|_unused10
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|lbursttp
r_volatile
id|u32
id|lbursttp
suffix:semicolon
multiline_comment|/* Time period for long bursts */
multiline_comment|/* MC chip can drive up to 4 bank 4 SIMMs each. All SIMMs in bank must&n;&t; * be the same size. The size encoding for supported SIMMs is bellow */
DECL|member|_unused11
id|u32
id|_unused11
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|mconfig0
r_volatile
id|u32
id|mconfig0
suffix:semicolon
multiline_comment|/* Memory config register zero */
DECL|member|_unused12
id|u32
id|_unused12
suffix:semicolon
DECL|member|mconfig1
r_volatile
id|u32
id|mconfig1
suffix:semicolon
multiline_comment|/* Memory config register one */
DECL|macro|SGIMC_MCONFIG_BASEADDR
mdefine_line|#define SGIMC_MCONFIG_BASEADDR&t;0x000000ff /* Base address of bank*/
DECL|macro|SGIMC_MCONFIG_RMASK
mdefine_line|#define SGIMC_MCONFIG_RMASK&t;0x00001f00 /* Ram config bitmask */
DECL|macro|SGIMC_MCONFIG_BVALID
mdefine_line|#define SGIMC_MCONFIG_BVALID&t;0x00002000 /* Bank is valid */
DECL|macro|SGIMC_MCONFIG_SBANKS
mdefine_line|#define SGIMC_MCONFIG_SBANKS&t;0x00004000 /* Number of subbanks */
DECL|member|_unused13
id|u32
id|_unused13
suffix:semicolon
DECL|member|cmacc
r_volatile
id|u32
id|cmacc
suffix:semicolon
multiline_comment|/* Mem access config for CPU */
DECL|member|_unused14
id|u32
id|_unused14
suffix:semicolon
DECL|member|gmacc
r_volatile
id|u32
id|gmacc
suffix:semicolon
multiline_comment|/* Mem access config for GIO */
multiline_comment|/* This define applies to both cmacc and gmacc registers above. */
DECL|macro|SGIMC_MACC_ALIASBIG
mdefine_line|#define SGIMC_MACC_ALIASBIG&t;0x20000000 /* 512MB home for alias */
multiline_comment|/* Error address/status regs from GIO and CPU perspectives. */
DECL|member|_unused15
id|u32
id|_unused15
suffix:semicolon
DECL|member|cerr
r_volatile
id|u32
id|cerr
suffix:semicolon
multiline_comment|/* Error address reg for CPU */
DECL|member|_unused16
id|u32
id|_unused16
suffix:semicolon
DECL|member|cstat
r_volatile
id|u32
id|cstat
suffix:semicolon
multiline_comment|/* Status reg for CPU */
DECL|macro|SGIMC_CSTAT_RD
mdefine_line|#define SGIMC_CSTAT_RD&t;&t;0x00000100 /* read parity error */
DECL|macro|SGIMC_CSTAT_PAR
mdefine_line|#define SGIMC_CSTAT_PAR&t;&t;0x00000200 /* CPU parity error */
DECL|macro|SGIMC_CSTAT_ADDR
mdefine_line|#define SGIMC_CSTAT_ADDR&t;0x00000400 /* memory bus error bad addr */
DECL|macro|SGIMC_CSTAT_SYSAD_PAR
mdefine_line|#define SGIMC_CSTAT_SYSAD_PAR&t;0x00000800 /* sysad parity error */
DECL|macro|SGIMC_CSTAT_SYSCMD_PAR
mdefine_line|#define SGIMC_CSTAT_SYSCMD_PAR&t;0x00001000 /* syscmd parity error */
DECL|macro|SGIMC_CSTAT_BAD_DATA
mdefine_line|#define SGIMC_CSTAT_BAD_DATA&t;0x00002000 /* bad data identifier */
DECL|macro|SGIMC_CSTAT_PAR_MASK
mdefine_line|#define SGIMC_CSTAT_PAR_MASK&t;0x00001f00 /* parity error mask */
DECL|macro|SGIMC_CSTAT_RD_PAR
mdefine_line|#define SGIMC_CSTAT_RD_PAR&t;(SGIMC_CSTAT_RD | SGIMC_CSTAT_PAR)
DECL|member|_unused17
id|u32
id|_unused17
suffix:semicolon
DECL|member|gerr
r_volatile
id|u32
id|gerr
suffix:semicolon
multiline_comment|/* Error address reg for GIO */
DECL|member|_unused18
id|u32
id|_unused18
suffix:semicolon
DECL|member|gstat
r_volatile
id|u32
id|gstat
suffix:semicolon
multiline_comment|/* Status reg for GIO */
DECL|macro|SGIMC_GSTAT_RD
mdefine_line|#define SGIMC_GSTAT_RD&t;&t;0x00000100 /* read parity error */
DECL|macro|SGIMC_GSTAT_WR
mdefine_line|#define SGIMC_GSTAT_WR&t;&t;0x00000200 /* write parity error */
DECL|macro|SGIMC_GSTAT_TIME
mdefine_line|#define SGIMC_GSTAT_TIME&t;0x00000400 /* GIO bus timed out */
DECL|macro|SGIMC_GSTAT_PROM
mdefine_line|#define SGIMC_GSTAT_PROM&t;0x00000800 /* write to PROM when PROM_EN not set */
DECL|macro|SGIMC_GSTAT_ADDR
mdefine_line|#define SGIMC_GSTAT_ADDR&t;0x00001000 /* parity error on addr cycle */
DECL|macro|SGIMC_GSTAT_BC
mdefine_line|#define SGIMC_GSTAT_BC&t;&t;0x00002000 /* parity error on byte count cycle */
DECL|macro|SGIMC_GSTAT_PIO_RD
mdefine_line|#define SGIMC_GSTAT_PIO_RD&t;0x00004000 /* read data parity on pio */
DECL|macro|SGIMC_GSTAT_PIO_WR
mdefine_line|#define SGIMC_GSTAT_PIO_WR&t;0x00008000 /* write data parity on pio */
multiline_comment|/* Special hard bus locking registers. */
DECL|member|_unused19
id|u32
id|_unused19
suffix:semicolon
DECL|member|syssembit
r_volatile
id|u32
id|syssembit
suffix:semicolon
multiline_comment|/* Uni-bit system semaphore */
DECL|member|_unused20
id|u32
id|_unused20
suffix:semicolon
DECL|member|mlock
r_volatile
id|u32
id|mlock
suffix:semicolon
multiline_comment|/* Global GIO memory access lock */
DECL|member|_unused21
id|u32
id|_unused21
suffix:semicolon
DECL|member|elock
r_volatile
id|u32
id|elock
suffix:semicolon
multiline_comment|/* Locks EISA from GIO accesses */
multiline_comment|/* GIO dma control registers. */
DECL|member|_unused22
id|u32
id|_unused22
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|gio_dma_trans
r_volatile
id|u32
id|gio_dma_trans
suffix:semicolon
multiline_comment|/* DMA mask to translation GIO addrs */
DECL|member|_unused23
id|u32
id|_unused23
suffix:semicolon
DECL|member|gio_dma_sbits
r_volatile
id|u32
id|gio_dma_sbits
suffix:semicolon
multiline_comment|/* DMA GIO addr substitution bits */
DECL|member|_unused24
id|u32
id|_unused24
suffix:semicolon
DECL|member|dma_intr_cause
r_volatile
id|u32
id|dma_intr_cause
suffix:semicolon
multiline_comment|/* DMA IRQ cause indicator bits */
DECL|member|_unused25
id|u32
id|_unused25
suffix:semicolon
DECL|member|dma_ctrl
r_volatile
id|u32
id|dma_ctrl
suffix:semicolon
multiline_comment|/* Main DMA control reg */
multiline_comment|/* DMA TLB entry 0 */
DECL|member|_unused26
id|u32
id|_unused26
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|dtlb_hi0
r_volatile
id|u32
id|dtlb_hi0
suffix:semicolon
DECL|member|_unused27
id|u32
id|_unused27
suffix:semicolon
DECL|member|dtlb_lo0
r_volatile
id|u32
id|dtlb_lo0
suffix:semicolon
multiline_comment|/* DMA TLB entry 1 */
DECL|member|_unused28
id|u32
id|_unused28
suffix:semicolon
DECL|member|dtlb_hi1
r_volatile
id|u32
id|dtlb_hi1
suffix:semicolon
DECL|member|_unused29
id|u32
id|_unused29
suffix:semicolon
DECL|member|dtlb_lo1
r_volatile
id|u32
id|dtlb_lo1
suffix:semicolon
multiline_comment|/* DMA TLB entry 2 */
DECL|member|_unused30
id|u32
id|_unused30
suffix:semicolon
DECL|member|dtlb_hi2
r_volatile
id|u32
id|dtlb_hi2
suffix:semicolon
DECL|member|_unused31
id|u32
id|_unused31
suffix:semicolon
DECL|member|dtlb_lo2
r_volatile
id|u32
id|dtlb_lo2
suffix:semicolon
multiline_comment|/* DMA TLB entry 3 */
DECL|member|_unused32
id|u32
id|_unused32
suffix:semicolon
DECL|member|dtlb_hi3
r_volatile
id|u32
id|dtlb_hi3
suffix:semicolon
DECL|member|_unused33
id|u32
id|_unused33
suffix:semicolon
DECL|member|dtlb_lo3
r_volatile
id|u32
id|dtlb_lo3
suffix:semicolon
DECL|member|_unused34
id|u32
id|_unused34
(braket
l_int|0x0392
)braket
suffix:semicolon
DECL|member|_unused35
id|u32
id|_unused35
suffix:semicolon
DECL|member|rpsscounter
r_volatile
id|u32
id|rpsscounter
suffix:semicolon
multiline_comment|/* Chirps at 100ns */
DECL|member|_unused36
id|u32
id|_unused36
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|2
op_star
l_int|4
)braket
suffix:semicolon
DECL|member|_unused37
id|u32
id|_unused37
suffix:semicolon
DECL|member|maddronly
r_volatile
id|u32
id|maddronly
suffix:semicolon
multiline_comment|/* Address DMA goes at */
DECL|member|_unused38
id|u32
id|_unused38
suffix:semicolon
DECL|member|maddrpdeflts
r_volatile
id|u32
id|maddrpdeflts
suffix:semicolon
multiline_comment|/* Same as above, plus set defaults */
DECL|member|_unused39
id|u32
id|_unused39
suffix:semicolon
DECL|member|dmasz
r_volatile
id|u32
id|dmasz
suffix:semicolon
multiline_comment|/* DMA count */
DECL|member|_unused40
id|u32
id|_unused40
suffix:semicolon
DECL|member|ssize
r_volatile
id|u32
id|ssize
suffix:semicolon
multiline_comment|/* DMA stride size */
DECL|member|_unused41
id|u32
id|_unused41
suffix:semicolon
DECL|member|gmaddronly
r_volatile
id|u32
id|gmaddronly
suffix:semicolon
multiline_comment|/* Set GIO DMA but don&squot;t start trans */
DECL|member|_unused42
id|u32
id|_unused42
suffix:semicolon
DECL|member|dmaddnpgo
r_volatile
id|u32
id|dmaddnpgo
suffix:semicolon
multiline_comment|/* Set GIO DMA addr + start transfer */
DECL|member|_unused43
id|u32
id|_unused43
suffix:semicolon
DECL|member|dmamode
r_volatile
id|u32
id|dmamode
suffix:semicolon
multiline_comment|/* DMA mode config bit settings */
DECL|member|_unused44
id|u32
id|_unused44
suffix:semicolon
DECL|member|dmaccount
r_volatile
id|u32
id|dmaccount
suffix:semicolon
multiline_comment|/* Zoom and byte count for DMA */
DECL|member|_unused45
id|u32
id|_unused45
suffix:semicolon
DECL|member|dmastart
r_volatile
id|u32
id|dmastart
suffix:semicolon
multiline_comment|/* Pedal to the metal. */
DECL|member|_unused46
id|u32
id|_unused46
suffix:semicolon
DECL|member|dmarunning
r_volatile
id|u32
id|dmarunning
suffix:semicolon
multiline_comment|/* DMA op is in progress */
DECL|member|_unused47
id|u32
id|_unused47
suffix:semicolon
DECL|member|maddrdefstart
r_volatile
id|u32
id|maddrdefstart
suffix:semicolon
multiline_comment|/* Set dma addr, defaults, and kick it */
)brace
suffix:semicolon
r_extern
r_struct
id|sgimc_regs
op_star
id|sgimc
suffix:semicolon
DECL|macro|SGIMC_BASE
mdefine_line|#define SGIMC_BASE&t;&t;0x1fa00000&t;/* physical */
multiline_comment|/* Base location of the two ram banks found in IP2[0268] machines. */
DECL|macro|SGIMC_SEG0_BADDR
mdefine_line|#define SGIMC_SEG0_BADDR&t;0x08000000
DECL|macro|SGIMC_SEG1_BADDR
mdefine_line|#define SGIMC_SEG1_BADDR&t;0x20000000
multiline_comment|/* Maximum size of the above banks are per machine. */
DECL|macro|SGIMC_SEG0_SIZE_ALL
mdefine_line|#define SGIMC_SEG0_SIZE_ALL&t;&t;0x10000000 /* 256MB */
DECL|macro|SGIMC_SEG1_SIZE_IP20_IP22
mdefine_line|#define SGIMC_SEG1_SIZE_IP20_IP22&t;0x08000000 /* 128MB */
DECL|macro|SGIMC_SEG1_SIZE_IP26_IP28
mdefine_line|#define SGIMC_SEG1_SIZE_IP26_IP28&t;0x20000000 /* 512MB */
r_extern
r_void
id|sgimc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _SGI_MC_H */
eof
