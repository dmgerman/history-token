multiline_comment|/*&n;** This file is private to iosapic driver.&n;** If stuff needs to be used by another driver, move it to a common file.&n;**&n;** WARNING: fields most data structures here are ordered to make sure&n;**          they pack nicely for 64-bit compilation. (ie sizeof(long) == 8)&n;*/
multiline_comment|/*&n;** Interrupt Routing Stuff&n;** -----------------------&n;** The interrupt routing table consists of entries derived from&n;** MP Specification Draft 1.5. There is one interrupt routing &n;** table per cell.  N- and L-class consist of a single cell.&n;*/
DECL|struct|irt_entry
r_struct
id|irt_entry
(brace
multiline_comment|/* Entry Type 139 identifies an I/O SAPIC interrupt entry */
DECL|member|entry_type
id|u8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry Length 16 indicates entry is 16 bytes long */
DECL|member|entry_length
id|u8
id|entry_length
suffix:semicolon
multiline_comment|/* &n;&t;** Interrupt Type of 0 indicates a vectored interrupt, &n;&t;** all other values are reserved &n;&t;*/
DECL|member|interrupt_type
id|u8
id|interrupt_type
suffix:semicolon
multiline_comment|/* &n;&t;** PO and EL&n;&t;** Polarity of SAPIC I/O input signals: &n;&t;**    00 = Reserved &n;&t;**    01 = Active high &n;&t;**    10 = Reserved &n;&t;**    11 = Active low &n;&t;** Trigger mode of SAPIC I/O input signals: &n;&t;**    00 = Reserved &n;&t;**    01 = Edge-triggered &n;&t;**    10 = Reserved &n;&t;**    11 = Level-triggered&n;&t;*/
DECL|member|polarity_trigger
id|u8
id|polarity_trigger
suffix:semicolon
multiline_comment|/* &n;&t;** IRQ and DEVNO&n;&t;** irq identifies PCI interrupt signal where&n;&t;**    0x0 corresponds to INT_A#, &n;&t;**    0x1 corresponds to INT_B#, &n;&t;**    0x2 corresponds to INT_C# &n;&t;**    0x3 corresponds to INT_D# &n;&t;** PCI device number where interrupt originates &n;&t;*/
DECL|member|src_bus_irq_devno
id|u8
id|src_bus_irq_devno
suffix:semicolon
multiline_comment|/* Source Bus ID identifies the bus where interrupt signal comes from */
DECL|member|src_bus_id
id|u8
id|src_bus_id
suffix:semicolon
multiline_comment|/* &n;&t;** Segment ID is unique across a protection domain and&n;&t;** identifies a segment of PCI buses (reserved in &n;&t;** MP Specification Draft 1.5) &n;&t;*/
DECL|member|src_seg_id
id|u8
id|src_seg_id
suffix:semicolon
multiline_comment|/* &n;&t;** Destination I/O SAPIC INTIN# identifies the INTIN n pin &n;&t;** to which the signal is connected &n;&t;*/
DECL|member|dest_iosapic_intin
id|u8
id|dest_iosapic_intin
suffix:semicolon
multiline_comment|/* &n;&t;** Destination I/O SAPIC Address identifies the I/O SAPIC &n;&t;** to which the signal is connected &n;&t;*/
DECL|member|dest_iosapic_addr
id|u64
id|dest_iosapic_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IRT_IOSAPIC_TYPE
mdefine_line|#define IRT_IOSAPIC_TYPE   139
DECL|macro|IRT_IOSAPIC_LENGTH
mdefine_line|#define IRT_IOSAPIC_LENGTH 16
DECL|macro|IRT_VECTORED_INTR
mdefine_line|#define IRT_VECTORED_INTR  0
DECL|macro|IRT_PO_MASK
mdefine_line|#define IRT_PO_MASK        0x3
DECL|macro|IRT_ACTIVE_HI
mdefine_line|#define IRT_ACTIVE_HI      1
DECL|macro|IRT_ACTIVE_LO
mdefine_line|#define IRT_ACTIVE_LO      3
DECL|macro|IRT_EL_MASK
mdefine_line|#define IRT_EL_MASK        0x3
DECL|macro|IRT_EL_SHIFT
mdefine_line|#define IRT_EL_SHIFT       2
DECL|macro|IRT_EDGE_TRIG
mdefine_line|#define IRT_EDGE_TRIG      1
DECL|macro|IRT_LEVEL_TRIG
mdefine_line|#define IRT_LEVEL_TRIG     3
DECL|macro|IRT_IRQ_MASK
mdefine_line|#define IRT_IRQ_MASK       0x3
DECL|macro|IRT_DEV_MASK
mdefine_line|#define IRT_DEV_MASK       0x1f
DECL|macro|IRT_DEV_SHIFT
mdefine_line|#define IRT_DEV_SHIFT      2
DECL|macro|IRT_IRQ_DEVNO_MASK
mdefine_line|#define IRT_IRQ_DEVNO_MASK&t;((IRT_DEV_MASK &lt;&lt; IRT_DEV_SHIFT) | IRT_IRQ_MASK)
macro_line|#ifdef SUPPORT_MULTI_CELL
DECL|struct|iosapic_irt
r_struct
id|iosapic_irt
(brace
DECL|member|irt_next
r_struct
id|iosapic_irt
op_star
id|irt_next
suffix:semicolon
multiline_comment|/* next routing table */
DECL|member|irt_base
r_struct
id|irt_entry
op_star
id|irt_base
suffix:semicolon
multiline_comment|/* intr routing table address */
DECL|member|irte_count
r_int
id|irte_count
suffix:semicolon
multiline_comment|/* number of entries in the table */
DECL|member|irte_size
r_int
id|irte_size
suffix:semicolon
multiline_comment|/* size (bytes) of each entry */
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|vector_info
r_struct
id|vector_info
(brace
DECL|member|vi_ios
r_struct
id|iosapic_info
op_star
id|vi_ios
suffix:semicolon
multiline_comment|/* I/O SAPIC this vector is on */
DECL|member|vi_irte
r_struct
id|irt_entry
op_star
id|vi_irte
suffix:semicolon
multiline_comment|/* IRT entry */
DECL|member|vi_eoi_addr
id|u32
op_star
id|vi_eoi_addr
suffix:semicolon
multiline_comment|/* precalculate EOI reg address */
DECL|member|vi_eoi_data
id|u32
id|vi_eoi_data
suffix:semicolon
multiline_comment|/* IA64: ?       PA: swapped txn_data */
DECL|member|vi_status
id|u8
id|vi_status
suffix:semicolon
multiline_comment|/* status/flags */
DECL|member|vi_irqline
id|u8
id|vi_irqline
suffix:semicolon
multiline_comment|/* INTINn(IRQ) */
DECL|member|vi_txn_irq
r_int
id|vi_txn_irq
suffix:semicolon
multiline_comment|/* virtual IRQ number for processor */
DECL|member|vi_txn_addr
id|ulong
id|vi_txn_addr
suffix:semicolon
multiline_comment|/* IA64: id_eid  PA: partial HPA */
DECL|member|vi_txn_data
id|ulong
id|vi_txn_data
suffix:semicolon
multiline_comment|/* IA64: vector  PA: EIR bit */
)brace
suffix:semicolon
DECL|struct|iosapic_info
r_struct
id|iosapic_info
(brace
DECL|member|isi_next
r_struct
id|iosapic_info
op_star
id|isi_next
suffix:semicolon
multiline_comment|/* list of I/O SAPIC          */
DECL|member|isi_hpa
r_volatile
r_void
op_star
id|isi_hpa
suffix:semicolon
multiline_comment|/* physical base address      */
DECL|member|isi_region
r_struct
id|irq_region
op_star
id|isi_region
suffix:semicolon
multiline_comment|/* each I/O SAPIC is one region */
DECL|member|isi_vector
r_struct
id|vector_info
op_star
id|isi_vector
suffix:semicolon
multiline_comment|/* IRdT (IRQ line) array  */
DECL|member|isi_num_vectors
r_int
id|isi_num_vectors
suffix:semicolon
multiline_comment|/* size of IRdT array */
DECL|member|isi_status
r_int
id|isi_status
suffix:semicolon
multiline_comment|/* status/flags               */
DECL|member|isi_version
r_int
r_int
id|isi_version
suffix:semicolon
multiline_comment|/* DEBUG: data fr version reg */
)brace
suffix:semicolon
macro_line|#ifdef __IA64__
multiline_comment|/*&n;** PA risc does NOT have any local sapics. IA64 does.&n;** PIB (Processor Interrupt Block) is handled by Astro or Dew (Stretch CEC).&n;**&n;** PA: Get id_eid from IRT and hardcode PIB to 0xfeeNNNN0&n;**     Emulate the data on PAT platforms.&n;*/
DECL|struct|local_sapic_info
r_struct
id|local_sapic_info
(brace
DECL|member|lsi_next
r_struct
id|local_sapic_info
op_star
id|lsi_next
suffix:semicolon
multiline_comment|/* point to next CPU info */
DECL|member|lsi_cpu_id
r_int
op_star
id|lsi_cpu_id
suffix:semicolon
multiline_comment|/* point to logical CPU id */
DECL|member|lsi_id_eid
r_int
r_int
op_star
id|lsi_id_eid
suffix:semicolon
multiline_comment|/* point to IA-64 CPU id */
DECL|member|lsi_status
r_int
op_star
id|lsi_status
suffix:semicolon
multiline_comment|/* point to CPU status   */
DECL|member|lsi_private
r_void
op_star
id|lsi_private
suffix:semicolon
multiline_comment|/* point to special info */
)brace
suffix:semicolon
multiline_comment|/*&n;** &quot;root&quot; data structure which ties everything together.&n;** Should always be able to start with sapic_root and locate&n;** the desired information.&n;*/
DECL|struct|sapic_info
r_struct
id|sapic_info
(brace
DECL|member|si_next
r_struct
id|sapic_info
op_star
id|si_next
suffix:semicolon
multiline_comment|/* info is per cell */
DECL|member|si_cellid
r_int
id|si_cellid
suffix:semicolon
multiline_comment|/* cell id */
DECL|member|si_status
r_int
r_int
id|si_status
suffix:semicolon
multiline_comment|/* status  */
DECL|member|si_pib_base
r_char
op_star
id|si_pib_base
suffix:semicolon
multiline_comment|/* intr blk base address */
DECL|member|si_local_info
id|local_sapic_info_t
op_star
id|si_local_info
suffix:semicolon
DECL|member|si_io_info
id|io_sapic_info_t
op_star
id|si_io_info
suffix:semicolon
DECL|member|si_extint_info
id|extint_info_t
op_star
id|si_extint_info
suffix:semicolon
multiline_comment|/* External Intr info      */
)brace
suffix:semicolon
macro_line|#endif
eof
