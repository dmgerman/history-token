multiline_comment|/*&n;   Copyright 2003-2004 Red Hat, Inc.  All rights reserved.&n;   Copyright 2003-2004 Jeff Garzik&n;&n;   The contents of this file are subject to the Open&n;   Software License version 1.1 that can be found at&n;   http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n;   by reference.&n;&n;   Alternatively, the contents of this file may be used under the terms&n;   of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n;   in the kernel source COPYING file, in which case the provisions of&n;   the GPL are applicable instead of the above.  If you wish to allow&n;   the use of your version of this file only under the terms of the&n;   GPL and not to allow others to use your version of this file under&n;   the OSL, indicate your decision by deleting the provisions above and&n;   replace them with the notice and other provisions required by the GPL.&n;   If you do not delete the provisions above, a recipient may use your&n;   version of this file under either the OSL or the GPL.&n;&n; */
macro_line|#ifndef __LINUX_ATA_H__
DECL|macro|__LINUX_ATA_H__
mdefine_line|#define __LINUX_ATA_H__
multiline_comment|/* defines only for the constants which don&squot;t work well as enums */
DECL|macro|ATA_DMA_BOUNDARY
mdefine_line|#define ATA_DMA_BOUNDARY&t;0xffffUL
DECL|macro|ATA_DMA_MASK
mdefine_line|#define ATA_DMA_MASK&t;&t;0xffffffffULL
r_enum
(brace
multiline_comment|/* various global constants */
DECL|enumerator|ATA_MAX_DEVICES
id|ATA_MAX_DEVICES
op_assign
l_int|2
comma
multiline_comment|/* per bus/port */
DECL|enumerator|ATA_MAX_PRD
id|ATA_MAX_PRD
op_assign
l_int|256
comma
multiline_comment|/* we could make these 256/256 */
DECL|enumerator|ATA_SECT_SIZE
id|ATA_SECT_SIZE
op_assign
l_int|512
comma
DECL|enumerator|ATA_SECT_SIZE_MASK
id|ATA_SECT_SIZE_MASK
op_assign
(paren
id|ATA_SECT_SIZE
op_minus
l_int|1
)paren
comma
DECL|enumerator|ATA_SECT_DWORDS
id|ATA_SECT_DWORDS
op_assign
id|ATA_SECT_SIZE
op_div
r_sizeof
(paren
id|u32
)paren
comma
DECL|enumerator|ATA_ID_WORDS
id|ATA_ID_WORDS
op_assign
l_int|256
comma
DECL|enumerator|ATA_ID_PROD_OFS
id|ATA_ID_PROD_OFS
op_assign
l_int|27
comma
DECL|enumerator|ATA_ID_FW_REV_OFS
id|ATA_ID_FW_REV_OFS
op_assign
l_int|23
comma
DECL|enumerator|ATA_ID_SERNO_OFS
id|ATA_ID_SERNO_OFS
op_assign
l_int|10
comma
DECL|enumerator|ATA_ID_MAJOR_VER
id|ATA_ID_MAJOR_VER
op_assign
l_int|80
comma
DECL|enumerator|ATA_ID_PIO_MODES
id|ATA_ID_PIO_MODES
op_assign
l_int|64
comma
DECL|enumerator|ATA_ID_UDMA_MODES
id|ATA_ID_UDMA_MODES
op_assign
l_int|88
comma
DECL|enumerator|ATA_ID_PIO4
id|ATA_ID_PIO4
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|ATA_PCI_CTL_OFS
id|ATA_PCI_CTL_OFS
op_assign
l_int|2
comma
DECL|enumerator|ATA_SERNO_LEN
id|ATA_SERNO_LEN
op_assign
l_int|20
comma
DECL|enumerator|ATA_UDMA0
id|ATA_UDMA0
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|ATA_UDMA1
id|ATA_UDMA1
op_assign
id|ATA_UDMA0
op_or
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|ATA_UDMA2
id|ATA_UDMA2
op_assign
id|ATA_UDMA1
op_or
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
DECL|enumerator|ATA_UDMA3
id|ATA_UDMA3
op_assign
id|ATA_UDMA2
op_or
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
DECL|enumerator|ATA_UDMA4
id|ATA_UDMA4
op_assign
id|ATA_UDMA3
op_or
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
DECL|enumerator|ATA_UDMA5
id|ATA_UDMA5
op_assign
id|ATA_UDMA4
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
DECL|enumerator|ATA_UDMA6
id|ATA_UDMA6
op_assign
id|ATA_UDMA5
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
DECL|enumerator|ATA_UDMA7
id|ATA_UDMA7
op_assign
id|ATA_UDMA6
op_or
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
multiline_comment|/* ATA_UDMA7 is just for completeness... doesn&squot;t exist (yet?).  */
DECL|enumerator|ATA_UDMA_MASK_40C
id|ATA_UDMA_MASK_40C
op_assign
id|ATA_UDMA2
comma
multiline_comment|/* udma0-2 */
multiline_comment|/* DMA-related */
DECL|enumerator|ATA_PRD_SZ
id|ATA_PRD_SZ
op_assign
l_int|8
comma
DECL|enumerator|ATA_PRD_TBL_SZ
id|ATA_PRD_TBL_SZ
op_assign
(paren
id|ATA_MAX_PRD
op_star
id|ATA_PRD_SZ
)paren
comma
DECL|enumerator|ATA_PRD_EOT
id|ATA_PRD_EOT
op_assign
(paren
l_int|1
op_lshift
l_int|31
)paren
comma
multiline_comment|/* end-of-table flag */
DECL|enumerator|ATA_DMA_TABLE_OFS
id|ATA_DMA_TABLE_OFS
op_assign
l_int|4
comma
DECL|enumerator|ATA_DMA_STATUS
id|ATA_DMA_STATUS
op_assign
l_int|2
comma
DECL|enumerator|ATA_DMA_CMD
id|ATA_DMA_CMD
op_assign
l_int|0
comma
DECL|enumerator|ATA_DMA_WR
id|ATA_DMA_WR
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
DECL|enumerator|ATA_DMA_START
id|ATA_DMA_START
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|ATA_DMA_INTR
id|ATA_DMA_INTR
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
DECL|enumerator|ATA_DMA_ERR
id|ATA_DMA_ERR
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|ATA_DMA_ACTIVE
id|ATA_DMA_ACTIVE
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* bits in ATA command block registers */
DECL|enumerator|ATA_HOB
id|ATA_HOB
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
multiline_comment|/* LBA48 selector */
DECL|enumerator|ATA_NIEN
id|ATA_NIEN
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* disable-irq flag */
DECL|enumerator|ATA_LBA
id|ATA_LBA
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
multiline_comment|/* LBA28 selector */
DECL|enumerator|ATA_DEV1
id|ATA_DEV1
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/* Select Device 1 (slave) */
DECL|enumerator|ATA_BUSY
id|ATA_BUSY
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
multiline_comment|/* BSY status bit */
DECL|enumerator|ATA_DEVICE_OBS
id|ATA_DEVICE_OBS
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
multiline_comment|/* obs bits in dev reg */
DECL|enumerator|ATA_DEVCTL_OBS
id|ATA_DEVCTL_OBS
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* obsolete bit in devctl reg */
DECL|enumerator|ATA_DRQ
id|ATA_DRQ
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* data request i/o */
DECL|enumerator|ATA_ERR
id|ATA_ERR
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* have an error */
DECL|enumerator|ATA_SRST
id|ATA_SRST
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* software reset */
DECL|enumerator|ATA_ABORTED
id|ATA_ABORTED
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* command aborted */
multiline_comment|/* ATA command block registers */
DECL|enumerator|ATA_REG_DATA
id|ATA_REG_DATA
op_assign
l_int|0x00
comma
DECL|enumerator|ATA_REG_ERR
id|ATA_REG_ERR
op_assign
l_int|0x01
comma
DECL|enumerator|ATA_REG_NSECT
id|ATA_REG_NSECT
op_assign
l_int|0x02
comma
DECL|enumerator|ATA_REG_LBAL
id|ATA_REG_LBAL
op_assign
l_int|0x03
comma
DECL|enumerator|ATA_REG_LBAM
id|ATA_REG_LBAM
op_assign
l_int|0x04
comma
DECL|enumerator|ATA_REG_LBAH
id|ATA_REG_LBAH
op_assign
l_int|0x05
comma
DECL|enumerator|ATA_REG_DEVICE
id|ATA_REG_DEVICE
op_assign
l_int|0x06
comma
DECL|enumerator|ATA_REG_STATUS
id|ATA_REG_STATUS
op_assign
l_int|0x07
comma
DECL|enumerator|ATA_REG_FEATURE
id|ATA_REG_FEATURE
op_assign
id|ATA_REG_ERR
comma
multiline_comment|/* and their aliases */
DECL|enumerator|ATA_REG_CMD
id|ATA_REG_CMD
op_assign
id|ATA_REG_STATUS
comma
DECL|enumerator|ATA_REG_BYTEL
id|ATA_REG_BYTEL
op_assign
id|ATA_REG_LBAM
comma
DECL|enumerator|ATA_REG_BYTEH
id|ATA_REG_BYTEH
op_assign
id|ATA_REG_LBAH
comma
DECL|enumerator|ATA_REG_DEVSEL
id|ATA_REG_DEVSEL
op_assign
id|ATA_REG_DEVICE
comma
DECL|enumerator|ATA_REG_IRQ
id|ATA_REG_IRQ
op_assign
id|ATA_REG_NSECT
comma
multiline_comment|/* ATA device commands */
DECL|enumerator|ATA_CMD_CHK_POWER
id|ATA_CMD_CHK_POWER
op_assign
l_int|0xE5
comma
multiline_comment|/* check power mode */
DECL|enumerator|ATA_CMD_EDD
id|ATA_CMD_EDD
op_assign
l_int|0x90
comma
multiline_comment|/* execute device diagnostic */
DECL|enumerator|ATA_CMD_FLUSH
id|ATA_CMD_FLUSH
op_assign
l_int|0xE7
comma
DECL|enumerator|ATA_CMD_FLUSH_EXT
id|ATA_CMD_FLUSH_EXT
op_assign
l_int|0xEA
comma
DECL|enumerator|ATA_CMD_ID_ATA
id|ATA_CMD_ID_ATA
op_assign
l_int|0xEC
comma
DECL|enumerator|ATA_CMD_ID_ATAPI
id|ATA_CMD_ID_ATAPI
op_assign
l_int|0xA1
comma
DECL|enumerator|ATA_CMD_READ
id|ATA_CMD_READ
op_assign
l_int|0xC8
comma
DECL|enumerator|ATA_CMD_READ_EXT
id|ATA_CMD_READ_EXT
op_assign
l_int|0x25
comma
DECL|enumerator|ATA_CMD_WRITE
id|ATA_CMD_WRITE
op_assign
l_int|0xCA
comma
DECL|enumerator|ATA_CMD_WRITE_EXT
id|ATA_CMD_WRITE_EXT
op_assign
l_int|0x35
comma
DECL|enumerator|ATA_CMD_PIO_READ
id|ATA_CMD_PIO_READ
op_assign
l_int|0x20
comma
DECL|enumerator|ATA_CMD_PIO_READ_EXT
id|ATA_CMD_PIO_READ_EXT
op_assign
l_int|0x24
comma
DECL|enumerator|ATA_CMD_PIO_WRITE
id|ATA_CMD_PIO_WRITE
op_assign
l_int|0x30
comma
DECL|enumerator|ATA_CMD_PIO_WRITE_EXT
id|ATA_CMD_PIO_WRITE_EXT
op_assign
l_int|0x34
comma
DECL|enumerator|ATA_CMD_SET_FEATURES
id|ATA_CMD_SET_FEATURES
op_assign
l_int|0xEF
comma
DECL|enumerator|ATA_CMD_PACKET
id|ATA_CMD_PACKET
op_assign
l_int|0xA0
comma
multiline_comment|/* SETFEATURES stuff */
DECL|enumerator|SETFEATURES_XFER
id|SETFEATURES_XFER
op_assign
l_int|0x03
comma
DECL|enumerator|XFER_UDMA_7
id|XFER_UDMA_7
op_assign
l_int|0x47
comma
DECL|enumerator|XFER_UDMA_6
id|XFER_UDMA_6
op_assign
l_int|0x46
comma
DECL|enumerator|XFER_UDMA_5
id|XFER_UDMA_5
op_assign
l_int|0x45
comma
DECL|enumerator|XFER_UDMA_4
id|XFER_UDMA_4
op_assign
l_int|0x44
comma
DECL|enumerator|XFER_UDMA_3
id|XFER_UDMA_3
op_assign
l_int|0x43
comma
DECL|enumerator|XFER_UDMA_2
id|XFER_UDMA_2
op_assign
l_int|0x42
comma
DECL|enumerator|XFER_UDMA_1
id|XFER_UDMA_1
op_assign
l_int|0x41
comma
DECL|enumerator|XFER_UDMA_0
id|XFER_UDMA_0
op_assign
l_int|0x40
comma
DECL|enumerator|XFER_PIO_4
id|XFER_PIO_4
op_assign
l_int|0x0C
comma
DECL|enumerator|XFER_PIO_3
id|XFER_PIO_3
op_assign
l_int|0x0B
comma
multiline_comment|/* ATAPI stuff */
DECL|enumerator|ATAPI_PKT_DMA
id|ATAPI_PKT_DMA
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|ATAPI_DMADIR
id|ATAPI_DMADIR
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* ATAPI data dir:&n;&t;&t;&t;&t;&t;&t;   0=to device, 1=to host */
multiline_comment|/* cable types */
DECL|enumerator|ATA_CBL_NONE
id|ATA_CBL_NONE
op_assign
l_int|0
comma
DECL|enumerator|ATA_CBL_PATA40
id|ATA_CBL_PATA40
op_assign
l_int|1
comma
DECL|enumerator|ATA_CBL_PATA80
id|ATA_CBL_PATA80
op_assign
l_int|2
comma
DECL|enumerator|ATA_CBL_PATA_UNK
id|ATA_CBL_PATA_UNK
op_assign
l_int|3
comma
DECL|enumerator|ATA_CBL_SATA
id|ATA_CBL_SATA
op_assign
l_int|4
comma
multiline_comment|/* SATA Status and Control Registers */
DECL|enumerator|SCR_STATUS
id|SCR_STATUS
op_assign
l_int|0
comma
DECL|enumerator|SCR_ERROR
id|SCR_ERROR
op_assign
l_int|1
comma
DECL|enumerator|SCR_CONTROL
id|SCR_CONTROL
op_assign
l_int|2
comma
DECL|enumerator|SCR_ACTIVE
id|SCR_ACTIVE
op_assign
l_int|3
comma
DECL|enumerator|SCR_NOTIFICATION
id|SCR_NOTIFICATION
op_assign
l_int|4
comma
multiline_comment|/* struct ata_taskfile flags */
DECL|enumerator|ATA_TFLAG_LBA48
id|ATA_TFLAG_LBA48
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* enable 48-bit LBA and &quot;HOB&quot; */
DECL|enumerator|ATA_TFLAG_ISADDR
id|ATA_TFLAG_ISADDR
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* enable r/w to nsect/lba regs */
DECL|enumerator|ATA_TFLAG_DEVICE
id|ATA_TFLAG_DEVICE
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* enable r/w to device reg */
DECL|enumerator|ATA_TFLAG_WRITE
id|ATA_TFLAG_WRITE
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* data dir: host-&gt;dev==1 (write) */
)brace
suffix:semicolon
DECL|enum|ata_tf_protocols
r_enum
id|ata_tf_protocols
(brace
multiline_comment|/* ATA taskfile protocols */
DECL|enumerator|ATA_PROT_UNKNOWN
id|ATA_PROT_UNKNOWN
comma
multiline_comment|/* unknown/invalid */
DECL|enumerator|ATA_PROT_NODATA
id|ATA_PROT_NODATA
comma
multiline_comment|/* no data */
DECL|enumerator|ATA_PROT_PIO
id|ATA_PROT_PIO
comma
multiline_comment|/* PIO single sector */
DECL|enumerator|ATA_PROT_PIO_MULT
id|ATA_PROT_PIO_MULT
comma
multiline_comment|/* PIO multiple sector */
DECL|enumerator|ATA_PROT_DMA
id|ATA_PROT_DMA
comma
multiline_comment|/* DMA */
DECL|enumerator|ATA_PROT_ATAPI
id|ATA_PROT_ATAPI
comma
multiline_comment|/* packet command */
DECL|enumerator|ATA_PROT_ATAPI_DMA
id|ATA_PROT_ATAPI_DMA
comma
multiline_comment|/* packet command with special DMA sauce */
)brace
suffix:semicolon
multiline_comment|/* core structures */
DECL|struct|ata_prd
r_struct
id|ata_prd
(brace
DECL|member|addr
id|u32
id|addr
suffix:semicolon
DECL|member|flags_len
id|u32
id|flags_len
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ata_taskfile
r_struct
id|ata_taskfile
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* ATA_TFLAG_xxx */
DECL|member|protocol
id|u8
id|protocol
suffix:semicolon
multiline_comment|/* ATA_PROT_xxx */
DECL|member|ctl
id|u8
id|ctl
suffix:semicolon
multiline_comment|/* control reg */
DECL|member|hob_feature
id|u8
id|hob_feature
suffix:semicolon
multiline_comment|/* additional data */
DECL|member|hob_nsect
id|u8
id|hob_nsect
suffix:semicolon
multiline_comment|/* to support LBA48 */
DECL|member|hob_lbal
id|u8
id|hob_lbal
suffix:semicolon
DECL|member|hob_lbam
id|u8
id|hob_lbam
suffix:semicolon
DECL|member|hob_lbah
id|u8
id|hob_lbah
suffix:semicolon
DECL|member|feature
id|u8
id|feature
suffix:semicolon
DECL|member|nsect
id|u8
id|nsect
suffix:semicolon
DECL|member|lbal
id|u8
id|lbal
suffix:semicolon
DECL|member|lbam
id|u8
id|lbam
suffix:semicolon
DECL|member|lbah
id|u8
id|lbah
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|command
id|u8
id|command
suffix:semicolon
multiline_comment|/* IO operation */
)brace
suffix:semicolon
DECL|macro|ata_id_is_ata
mdefine_line|#define ata_id_is_ata(dev)&t;(((dev)-&gt;id[0] &amp; (1 &lt;&lt; 15)) == 0)
DECL|macro|ata_id_wcache_enabled
mdefine_line|#define ata_id_wcache_enabled(dev) ((dev)-&gt;id[85] &amp; (1 &lt;&lt; 5))
DECL|macro|ata_id_has_lba48
mdefine_line|#define ata_id_has_lba48(dev)&t;((dev)-&gt;id[83] &amp; (1 &lt;&lt; 10))
DECL|macro|ata_id_has_wcache
mdefine_line|#define ata_id_has_wcache(dev)&t;((dev)-&gt;id[82] &amp; (1 &lt;&lt; 5))
DECL|macro|ata_id_has_pm
mdefine_line|#define ata_id_has_pm(dev)&t;((dev)-&gt;id[82] &amp; (1 &lt;&lt; 3))
DECL|macro|ata_id_has_lba
mdefine_line|#define ata_id_has_lba(dev)&t;((dev)-&gt;id[49] &amp; (1 &lt;&lt; 8))
DECL|macro|ata_id_has_dma
mdefine_line|#define ata_id_has_dma(dev)&t;((dev)-&gt;id[49] &amp; (1 &lt;&lt; 9))
DECL|macro|ata_id_removeable
mdefine_line|#define ata_id_removeable(dev)&t;((dev)-&gt;id[0] &amp; (1 &lt;&lt; 7))
DECL|macro|ata_id_u32
mdefine_line|#define ata_id_u32(dev,n)&t;&bslash;&n;&t;(((u32) (dev)-&gt;id[(n) + 1] &lt;&lt; 16) | ((u32) (dev)-&gt;id[(n)]))
DECL|macro|ata_id_u64
mdefine_line|#define ata_id_u64(dev,n)&t;&bslash;&n;&t;( ((u64) dev-&gt;id[(n) + 3] &lt;&lt; 48) |&t;&bslash;&n;&t;  ((u64) dev-&gt;id[(n) + 2] &lt;&lt; 32) |&t;&bslash;&n;&t;  ((u64) dev-&gt;id[(n) + 1] &lt;&lt; 16) |&t;&bslash;&n;&t;  ((u64) dev-&gt;id[(n) + 0]) )
macro_line|#endif /* __LINUX_ATA_H__ */
eof
