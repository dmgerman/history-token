multiline_comment|/* &n; * Copyright (C) 2001 David J. Mckay (david.mckay@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.                            &n; *&n; * Defintions for the ST40 PCI hardware.&n; */
macro_line|#ifndef __PCI_ST40_H__
DECL|macro|__PCI_ST40_H__
mdefine_line|#define __PCI_ST40_H__
DECL|macro|ST40PCI_VCR_STATUS
mdefine_line|#define ST40PCI_VCR_STATUS    0x00
DECL|macro|ST40PCI_VCR_VERSION
mdefine_line|#define ST40PCI_VCR_VERSION   0x08
DECL|macro|ST40PCI_CR
mdefine_line|#define ST40PCI_CR            0x10
DECL|macro|CR_SOFT_RESET
mdefine_line|#define CR_SOFT_RESET (1&lt;&lt;12)
DECL|macro|CR_PFCS
mdefine_line|#define CR_PFCS       (1&lt;&lt;11)
DECL|macro|CR_PFE
mdefine_line|#define CR_PFE        (1&lt;&lt;9)
DECL|macro|CR_BMAM
mdefine_line|#define CR_BMAM       (1&lt;&lt;6)
DECL|macro|CR_HOST
mdefine_line|#define CR_HOST       (1&lt;&lt;5)
DECL|macro|CR_CLKEN
mdefine_line|#define CR_CLKEN      (1&lt;&lt;4)
DECL|macro|CR_SOCS
mdefine_line|#define CR_SOCS       (1&lt;&lt;3)
DECL|macro|CR_IOCS
mdefine_line|#define CR_IOCS       (1&lt;&lt;2)
DECL|macro|CR_RSTCTL
mdefine_line|#define CR_RSTCTL     (1&lt;&lt;1)
DECL|macro|CR_CFINT
mdefine_line|#define CR_CFINT      (1&lt;&lt;0)
DECL|macro|CR_LOCK_MASK
mdefine_line|#define CR_LOCK_MASK  0x5a000000
DECL|macro|ST40PCI_LSR0
mdefine_line|#define ST40PCI_LSR0          0X14
DECL|macro|ST40PCI_LAR0
mdefine_line|#define ST40PCI_LAR0          0x1c
DECL|macro|ST40PCI_INT
mdefine_line|#define ST40PCI_INT           0x24
DECL|macro|INT_MNLTDIM
mdefine_line|#define INT_MNLTDIM           (1&lt;&lt;15)
DECL|macro|INT_TTADI
mdefine_line|#define INT_TTADI             (1&lt;&lt;14)
DECL|macro|INT_TMTO
mdefine_line|#define INT_TMTO              (1&lt;&lt;9)
DECL|macro|INT_MDEI
mdefine_line|#define INT_MDEI              (1&lt;&lt;8)
DECL|macro|INT_APEDI
mdefine_line|#define INT_APEDI             (1&lt;&lt;7)
DECL|macro|INT_SDI
mdefine_line|#define INT_SDI               (1&lt;&lt;6)
DECL|macro|INT_DPEITW
mdefine_line|#define INT_DPEITW            (1&lt;&lt;5)
DECL|macro|INT_PEDITR
mdefine_line|#define INT_PEDITR            (1&lt;&lt;4)
DECL|macro|INT_TADIM
mdefine_line|#define INT_TADIM             (1&lt;&lt;3)
DECL|macro|INT_MADIM
mdefine_line|#define INT_MADIM             (1&lt;&lt;2)
DECL|macro|INT_MWPDI
mdefine_line|#define INT_MWPDI             (1&lt;&lt;1)
DECL|macro|INT_MRDPEI
mdefine_line|#define INT_MRDPEI            (1&lt;&lt;0)
DECL|macro|ST40PCI_INTM
mdefine_line|#define ST40PCI_INTM          0x28
DECL|macro|ST40PCI_AIR
mdefine_line|#define ST40PCI_AIR           0x2c
DECL|macro|ST40PCI_CIR
mdefine_line|#define ST40PCI_CIR           0x30
DECL|macro|CIR_PIOTEM
mdefine_line|#define CIR_PIOTEM            (1&lt;&lt;31)
DECL|macro|CIR_RWTET
mdefine_line|#define CIR_RWTET             (1&lt;&lt;26)
DECL|macro|ST40PCI_AINT
mdefine_line|#define ST40PCI_AINT          0x40
DECL|macro|AINT_MBI
mdefine_line|#define AINT_MBI              (1&lt;&lt;13)
DECL|macro|AINT_TBTOI
mdefine_line|#define AINT_TBTOI            (1&lt;&lt;12)
DECL|macro|AINT_MBTOI
mdefine_line|#define AINT_MBTOI            (1&lt;&lt;11)
DECL|macro|AINT_TAI
mdefine_line|#define AINT_TAI              (1&lt;&lt;3)
DECL|macro|AINT_MAI
mdefine_line|#define AINT_MAI              (1&lt;&lt;2)
DECL|macro|AINT_RDPEI
mdefine_line|#define AINT_RDPEI            (1&lt;&lt;1)
DECL|macro|AINT_WDPE
mdefine_line|#define AINT_WDPE             (1&lt;&lt;0)
DECL|macro|ST40PCI_AINTM
mdefine_line|#define ST40PCI_AINTM         0x44
DECL|macro|ST40PCI_BMIR
mdefine_line|#define ST40PCI_BMIR          0x48
DECL|macro|ST40PCI_PAR
mdefine_line|#define ST40PCI_PAR           0x4c
DECL|macro|ST40PCI_MBR
mdefine_line|#define ST40PCI_MBR           0x50
DECL|macro|ST40PCI_IOBR
mdefine_line|#define ST40PCI_IOBR          0x54
DECL|macro|ST40PCI_PINT
mdefine_line|#define ST40PCI_PINT          0x58
DECL|macro|ST40PCI_PINTM
mdefine_line|#define ST40PCI_PINTM         0x5c
DECL|macro|ST40PCI_MBMR
mdefine_line|#define ST40PCI_MBMR          0x70
DECL|macro|ST40PCI_IOBMR
mdefine_line|#define ST40PCI_IOBMR         0x74
DECL|macro|ST40PCI_PDR
mdefine_line|#define ST40PCI_PDR           0x78
multiline_comment|/* H8 specific registers start here */
DECL|macro|ST40PCI_WCBAR
mdefine_line|#define ST40PCI_WCBAR         0x7c
DECL|macro|ST40PCI_LOCCFG_UNLOCK
mdefine_line|#define ST40PCI_LOCCFG_UNLOCK 0x34
DECL|macro|ST40PCI_RBAR0
mdefine_line|#define ST40PCI_RBAR0         0x100
DECL|macro|ST40PCI_RSR0
mdefine_line|#define ST40PCI_RSR0          0x104
DECL|macro|ST40PCI_RLAR0
mdefine_line|#define ST40PCI_RLAR0         0x108
DECL|macro|ST40PCI_RBAR1
mdefine_line|#define ST40PCI_RBAR1         0x110
DECL|macro|ST40PCI_RSR1
mdefine_line|#define ST40PCI_RSR1          0x114
DECL|macro|ST40PCI_RLAR1
mdefine_line|#define ST40PCI_RLAR1         0x118
DECL|macro|ST40PCI_RBAR2
mdefine_line|#define ST40PCI_RBAR2         0x120
DECL|macro|ST40PCI_RSR2
mdefine_line|#define ST40PCI_RSR2          0x124
DECL|macro|ST40PCI_RLAR2
mdefine_line|#define ST40PCI_RLAR2         0x128
DECL|macro|ST40PCI_RBAR3
mdefine_line|#define ST40PCI_RBAR3         0x130
DECL|macro|ST40PCI_RSR3
mdefine_line|#define ST40PCI_RSR3          0x134
DECL|macro|ST40PCI_RLAR3
mdefine_line|#define ST40PCI_RLAR3         0x138
DECL|macro|ST40PCI_RBAR4
mdefine_line|#define ST40PCI_RBAR4         0x140
DECL|macro|ST40PCI_RSR4
mdefine_line|#define ST40PCI_RSR4          0x144
DECL|macro|ST40PCI_RLAR4
mdefine_line|#define ST40PCI_RLAR4         0x148
DECL|macro|ST40PCI_RBAR5
mdefine_line|#define ST40PCI_RBAR5         0x150
DECL|macro|ST40PCI_RSR5
mdefine_line|#define ST40PCI_RSR5          0x154
DECL|macro|ST40PCI_RLAR5
mdefine_line|#define ST40PCI_RLAR5         0x158
DECL|macro|ST40PCI_RBAR6
mdefine_line|#define ST40PCI_RBAR6         0x160
DECL|macro|ST40PCI_RSR6
mdefine_line|#define ST40PCI_RSR6          0x164
DECL|macro|ST40PCI_RLAR6
mdefine_line|#define ST40PCI_RLAR6         0x168
DECL|macro|ST40PCI_RBAR7
mdefine_line|#define ST40PCI_RBAR7         0x170
DECL|macro|ST40PCI_RSR7
mdefine_line|#define ST40PCI_RSR7          0x174
DECL|macro|ST40PCI_RLAR7
mdefine_line|#define ST40PCI_RLAR7         0x178
DECL|macro|ST40PCI_RBAR
mdefine_line|#define ST40PCI_RBAR(n)      (0x100+(0x10*(n)))
DECL|macro|ST40PCI_RSR
mdefine_line|#define ST40PCI_RSR(n)       (0x104+(0x10*(n)))
DECL|macro|ST40PCI_RLAR
mdefine_line|#define ST40PCI_RLAR(n)      (0x108+(0x10*(n)))
DECL|macro|ST40PCI_PERF
mdefine_line|#define ST40PCI_PERF               0x80
DECL|macro|PERF_MASTER_WRITE_POSTING
mdefine_line|#define PERF_MASTER_WRITE_POSTING  (1&lt;&lt;4)
multiline_comment|/* H8 specific registers end here */
multiline_comment|/* These are configs space registers */
DECL|macro|ST40PCI_CSR_VID
mdefine_line|#define ST40PCI_CSR_VID               0x10000
DECL|macro|ST40PCI_CSR_DID
mdefine_line|#define ST40PCI_CSR_DID               0x10002
DECL|macro|ST40PCI_CSR_CMD
mdefine_line|#define ST40PCI_CSR_CMD               0x10004
DECL|macro|ST40PCI_CSR_STATUS
mdefine_line|#define ST40PCI_CSR_STATUS            0x10006
DECL|macro|ST40PCI_CSR_MBAR0
mdefine_line|#define ST40PCI_CSR_MBAR0             0x10010
DECL|macro|ST40PCI_CSR_TRDY
mdefine_line|#define ST40PCI_CSR_TRDY              0x10040
DECL|macro|ST40PCI_CSR_RETRY
mdefine_line|#define ST40PCI_CSR_RETRY             0x10041
DECL|macro|ST40PCI_CSR_MIT
mdefine_line|#define ST40PCI_CSR_MIT               0x1000d
DECL|macro|ST40_IO_ADDR
mdefine_line|#define ST40_IO_ADDR 0xb6000000       
macro_line|#endif /* __PCI_ST40_H__ */
eof
