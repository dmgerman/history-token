multiline_comment|/*&n;** This file is private to iosapic driver.&n;** If stuff needs to be used by another driver, move it to a common file.&n;**&n;** WARNING: fields most data structures here are ordered to make sure&n;**          they pack nicely for 64-bit compilation. (ie sizeof(long) == 8)&n;*/
multiline_comment|/*&n;** I/O SAPIC init function&n;** Caller knows where an I/O SAPIC is. LBA has an integrated I/O SAPIC.&n;** Call setup as part of per instance initialization.&n;** (ie *not* init_module() function unless only one is present.)&n;** fixup_irq is to initialize PCI IRQ line support and&n;** virtualize pcidev-&gt;irq value. To be called by pci_fixup_bus().&n;*/
r_extern
r_void
op_star
id|iosapic_register
c_func
(paren
r_void
op_star
id|hpa
)paren
suffix:semicolon
r_extern
r_int
id|iosapic_fixup_irq
c_func
(paren
r_void
op_star
id|obj
comma
r_struct
id|pci_dev
op_star
id|pcidev
)paren
suffix:semicolon
macro_line|#ifdef __IA64__
multiline_comment|/*&n;** PA: PIB (Processor Interrupt Block) is handled by Runway bus adapter.&n;**     and is hardcoded to 0xfeeNNNN0 where NNNN is id_eid field.&n;**&n;** IA64: PIB is handled by &quot;Local SAPIC&quot; (integrated in the processor).&n;*/
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
macro_line|#endif /* IA64 */
eof
