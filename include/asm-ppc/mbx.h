multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * the Motorola MBX boards.  This was originally created for the&n; * MBX860, and probably needs revisions for other boards (like the 821).&n; * When this file gets out of control, we can split it up into more&n; * meaningful pieces.&n; *&n; * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __MACH_MBX_DEFS
DECL|macro|__MACH_MBX_DEFS
mdefine_line|#define __MACH_MBX_DEFS
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* A Board Information structure that is given to a program when&n; * EPPC-Bug starts it up.&n; */
DECL|struct|bd_info
r_typedef
r_struct
id|bd_info
(brace
DECL|member|bi_tag
r_int
r_int
id|bi_tag
suffix:semicolon
multiline_comment|/* Should be 0x42444944 &quot;BDID&quot; */
DECL|member|bi_size
r_int
r_int
id|bi_size
suffix:semicolon
multiline_comment|/* Size of this structure */
DECL|member|bi_revision
r_int
r_int
id|bi_revision
suffix:semicolon
multiline_comment|/* revision of this structure */
DECL|member|bi_bdate
r_int
r_int
id|bi_bdate
suffix:semicolon
multiline_comment|/* EPPCbug date, i.e. 0x11061997 */
DECL|member|bi_memstart
r_int
r_int
id|bi_memstart
suffix:semicolon
multiline_comment|/* Memory start address */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* Memory (end) size in bytes */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Internal Freq, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus Freq, in Hz */
DECL|member|bi_clun
r_int
r_int
id|bi_clun
suffix:semicolon
multiline_comment|/* Boot device controller */
DECL|member|bi_dlun
r_int
r_int
id|bi_dlun
suffix:semicolon
multiline_comment|/* Boot device logical dev */
multiline_comment|/* These fields are not part of the board information structure&n;&t; * provided by the boot rom.  They are filled in by embed_config.c&n;&t; * so we have the information consistent with other platforms.&n;&t; */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
multiline_comment|/* Memory map for the MBX as configured by EPPC-Bug.  We could reprogram&n; * The SIU and PCI bridge, and try to use larger MMU pages, but the&n; * performance gain is not measureable and it certainly complicates the&n; * generic MMU model.&n; *&n; * In a effort to minimize memory usage for embedded applications, any&n; * PCI driver or ISA driver must request or map the region required by&n; * the device.  For convenience (and since we can map up to 4 Mbytes with&n; * a single page table page), the MMU initialization will map the&n; * NVRAM, Status/Control registers, CPM Dual Port RAM, and the PCI&n; * Bridge CSRs 1:1 into the kernel address space.&n; */
DECL|macro|PCI_ISA_IO_ADDR
mdefine_line|#define PCI_ISA_IO_ADDR&t;&t;((unsigned)0x80000000)
DECL|macro|PCI_ISA_IO_SIZE
mdefine_line|#define PCI_ISA_IO_SIZE&t;&t;((uint)(512 * 1024 * 1024))
DECL|macro|PCI_IDE_ADDR
mdefine_line|#define PCI_IDE_ADDR&t;&t;((unsigned)0x81000000)
DECL|macro|PCI_ISA_MEM_ADDR
mdefine_line|#define PCI_ISA_MEM_ADDR&t;((unsigned)0xc0000000)
DECL|macro|PCI_ISA_MEM_SIZE
mdefine_line|#define PCI_ISA_MEM_SIZE&t;((uint)(512 * 1024 * 1024))
DECL|macro|PCMCIA_MEM_ADDR
mdefine_line|#define PCMCIA_MEM_ADDR&t;&t;((uint)0xe0000000)
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;&t;((uint)(64 * 1024 * 1024))
DECL|macro|PCMCIA_DMA_ADDR
mdefine_line|#define PCMCIA_DMA_ADDR&t;&t;((uint)0xe4000000)
DECL|macro|PCMCIA_DMA_SIZE
mdefine_line|#define PCMCIA_DMA_SIZE&t;&t;((uint)(64 * 1024 * 1024))
DECL|macro|PCMCIA_ATTRB_ADDR
mdefine_line|#define PCMCIA_ATTRB_ADDR&t;((uint)0xe8000000)
DECL|macro|PCMCIA_ATTRB_SIZE
mdefine_line|#define PCMCIA_ATTRB_SIZE&t;((uint)(64 * 1024 * 1024))
DECL|macro|PCMCIA_IO_ADDR
mdefine_line|#define PCMCIA_IO_ADDR&t;&t;((uint)0xec000000)
DECL|macro|PCMCIA_IO_SIZE
mdefine_line|#define PCMCIA_IO_SIZE&t;&t;((uint)(64 * 1024 * 1024))
DECL|macro|NVRAM_ADDR
mdefine_line|#define NVRAM_ADDR&t;&t;((uint)0xfa000000)
DECL|macro|NVRAM_SIZE
mdefine_line|#define NVRAM_SIZE&t;&t;((uint)(1 * 1024 * 1024))
DECL|macro|MBX_CSR_ADDR
mdefine_line|#define MBX_CSR_ADDR&t;&t;((uint)0xfa100000)
DECL|macro|MBX_CSR_SIZE
mdefine_line|#define MBX_CSR_SIZE&t;&t;((uint)(1 * 1024 * 1024))
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;&t;((uint)0xfa200000)
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;&t;((uint)(64 * 1024))
DECL|macro|PCI_CSR_ADDR
mdefine_line|#define PCI_CSR_ADDR&t;&t;((uint)0xfa210000)
DECL|macro|PCI_CSR_SIZE
mdefine_line|#define PCI_CSR_SIZE&t;&t;((uint)(64 * 1024))
multiline_comment|/* Map additional physical space into well known virtual addresses.  Due&n; * to virtual address mapping, these physical addresses are not accessible&n; * in a 1:1 virtual to physical mapping.&n; */
DECL|macro|ISA_IO_VIRT_ADDR
mdefine_line|#define ISA_IO_VIRT_ADDR&t;((uint)0xfa220000)
DECL|macro|ISA_IO_VIRT_SIZE
mdefine_line|#define ISA_IO_VIRT_SIZE&t;((uint)64 * 1024)
multiline_comment|/* Interrupt assignments.&n; * These are defined (and fixed) by the MBX hardware implementation.&n; */
DECL|macro|POWER_FAIL_INT
mdefine_line|#define POWER_FAIL_INT&t;SIU_IRQ0&t;/* Power fail */
DECL|macro|TEMP_HILO_INT
mdefine_line|#define TEMP_HILO_INT&t;SIU_IRQ1&t;/* Temperature sensor */
DECL|macro|QSPAN_INT
mdefine_line|#define QSPAN_INT&t;SIU_IRQ2&t;/* PCI Bridge (DMA CTLR?) */
DECL|macro|ISA_BRIDGE_INT
mdefine_line|#define ISA_BRIDGE_INT&t;SIU_IRQ3&t;/* All those PC things */
DECL|macro|COMM_L_INT
mdefine_line|#define COMM_L_INT&t;SIU_IRQ6&t;/* MBX Comm expansion connector pin */
DECL|macro|STOP_ABRT_INT
mdefine_line|#define STOP_ABRT_INT&t;SIU_IRQ7&t;/* Stop/Abort header pin */
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* The MBX uses the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;16
multiline_comment|/* Generic 8xx type&n;*/
DECL|macro|_MACH_8xx
mdefine_line|#define _MACH_8xx (_MACH_mbx)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
