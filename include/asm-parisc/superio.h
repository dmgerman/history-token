macro_line|#ifndef _PARISC_SUPERIO_H
DECL|macro|_PARISC_SUPERIO_H
mdefine_line|#define _PARISC_SUPERIO_H
DECL|macro|IC_PIC1
mdefine_line|#define IC_PIC1    0x20&t;&t;/* PCI I/O address of master 8259 */
DECL|macro|IC_PIC2
mdefine_line|#define IC_PIC2    0xA0&t;&t;/* PCI I/O address of slave */
multiline_comment|/* Config Space Offsets to configuration and base address registers */
DECL|macro|SIO_CR
mdefine_line|#define SIO_CR     0x5A&t;&t;/* Configuration Register */
DECL|macro|SIO_ACPIBAR
mdefine_line|#define SIO_ACPIBAR 0x88&t;/* ACPI BAR */
DECL|macro|SIO_FDCBAR
mdefine_line|#define SIO_FDCBAR 0x90&t;&t;/* Floppy Disk Controller BAR */
DECL|macro|SIO_SP1BAR
mdefine_line|#define SIO_SP1BAR 0x94&t;&t;/* Serial 1 BAR */
DECL|macro|SIO_SP2BAR
mdefine_line|#define SIO_SP2BAR 0x98&t;&t;/* Serial 2 BAR */
DECL|macro|SIO_PPBAR
mdefine_line|#define SIO_PPBAR  0x9C&t;&t;/* Parallel BAR */
DECL|macro|TRIGGER_1
mdefine_line|#define TRIGGER_1  0x67&t;&t;/* Edge/level trigger register 1 */
DECL|macro|TRIGGER_2
mdefine_line|#define TRIGGER_2  0x68&t;&t;/* Edge/level trigger register 2 */
multiline_comment|/* Interrupt Routing Control registers */
DECL|macro|CFG_IR_SER
mdefine_line|#define CFG_IR_SER    0x69&t;/* Serial 1 [0:3] and Serial 2 [4:7] */
DECL|macro|CFG_IR_PFD
mdefine_line|#define CFG_IR_PFD    0x6a&t;/* Parallel [0:3] and Floppy [4:7] */
DECL|macro|CFG_IR_IDE
mdefine_line|#define CFG_IR_IDE    0x6b&t;/* IDE1     [0:3] and IDE2 [4:7] */
DECL|macro|CFG_IR_INTAB
mdefine_line|#define CFG_IR_INTAB  0x6c&t;/* PCI INTA [0:3] and INT B [4:7] */
DECL|macro|CFG_IR_INTCD
mdefine_line|#define CFG_IR_INTCD  0x6d&t;/* PCI INTC [0:3] and INT D [4:7] */
DECL|macro|CFG_IR_PS2
mdefine_line|#define CFG_IR_PS2    0x6e&t;/* PS/2 KBINT [0:3] and Mouse [4:7] */
DECL|macro|CFG_IR_FXBUS
mdefine_line|#define CFG_IR_FXBUS  0x6f&t;/* FXIRQ[0] [0:3] and FXIRQ[1] [4:7] */
DECL|macro|CFG_IR_USB
mdefine_line|#define CFG_IR_USB    0x70&t;/* FXIRQ[2] [0:3] and USB [4:7] */
DECL|macro|CFG_IR_ACPI
mdefine_line|#define CFG_IR_ACPI   0x71&t;/* ACPI SCI [0:3] and reserved [4:7] */
DECL|macro|CFG_IR_LOW
mdefine_line|#define CFG_IR_LOW     CFG_IR_SER&t;/* Lowest interrupt routing reg */
DECL|macro|CFG_IR_HIGH
mdefine_line|#define CFG_IR_HIGH    CFG_IR_ACPI&t;/* Highest interrupt routing reg */
multiline_comment|/* 8259 operational control words */
DECL|macro|OCW2_EOI
mdefine_line|#define OCW2_EOI   0x20&t;&t;/* Non-specific EOI */
DECL|macro|OCW2_SEOI
mdefine_line|#define OCW2_SEOI  0x60&t;&t;/* Specific EOI */
DECL|macro|OCW3_IIR
mdefine_line|#define OCW3_IIR   0x0A&t;&t;/* Read request register */
DECL|macro|OCW3_ISR
mdefine_line|#define OCW3_ISR   0x0B&t;&t;/* Read service register */
DECL|macro|OCW3_POLL
mdefine_line|#define OCW3_POLL  0x0C&t;&t;/* Poll the PIC for an interrupt vector */
multiline_comment|/* Interrupt lines. Only PIC1 is used */
DECL|macro|USB_IRQ
mdefine_line|#define USB_IRQ    1&t;&t;/* USB */
DECL|macro|SP1_IRQ
mdefine_line|#define SP1_IRQ    3&t;&t;/* Serial port 1 */
DECL|macro|SP2_IRQ
mdefine_line|#define SP2_IRQ    4&t;&t;/* Serial port 2 */
DECL|macro|PAR_IRQ
mdefine_line|#define PAR_IRQ    5&t;&t;/* Parallel port */
DECL|macro|FDC_IRQ
mdefine_line|#define FDC_IRQ    6&t;&t;/* Floppy controller */
DECL|macro|IDE_IRQ
mdefine_line|#define IDE_IRQ    7&t;&t;/* IDE (pri+sec) */
multiline_comment|/* ACPI registers */
DECL|macro|USB_REG_CR
mdefine_line|#define USB_REG_CR&t;0x1f&t;/* USB Regulator Control Register */
DECL|macro|SUPERIO_NIRQS
mdefine_line|#define SUPERIO_NIRQS   8
DECL|struct|superio_device
r_struct
id|superio_device
(brace
DECL|member|fdc_base
id|u32
id|fdc_base
suffix:semicolon
DECL|member|sp1_base
id|u32
id|sp1_base
suffix:semicolon
DECL|member|sp2_base
id|u32
id|sp2_base
suffix:semicolon
DECL|member|pp_base
id|u32
id|pp_base
suffix:semicolon
DECL|member|acpi_base
id|u32
id|acpi_base
suffix:semicolon
DECL|member|suckyio_irq_enabled
r_int
id|suckyio_irq_enabled
suffix:semicolon
DECL|member|irq_region
r_struct
id|irq_region
op_star
id|irq_region
suffix:semicolon
DECL|member|lio_pdev
r_struct
id|pci_dev
op_star
id|lio_pdev
suffix:semicolon
multiline_comment|/* pci device for legacy IO (fn 1) */
DECL|member|usb_pdev
r_struct
id|pci_dev
op_star
id|usb_pdev
suffix:semicolon
multiline_comment|/* pci device for USB (fn 2) */
)brace
suffix:semicolon
multiline_comment|/*&n; * Does NS make a 87415 based plug in PCI card? If so, because of this&n; * macro we currently don&squot;t support it being plugged into a machine&n; * that contains a SuperIO chip AND has CONFIG_SUPERIO enabled.&n; *&n; * This could be fixed by checking to see if function 1 exists, and&n; * if it is SuperIO Legacy IO; but really now, is this combination&n; * going to EVER happen?&n; */
DECL|macro|SUPERIO_IDE_FN
mdefine_line|#define SUPERIO_IDE_FN 0 /* Function number of IDE controller */
DECL|macro|SUPERIO_LIO_FN
mdefine_line|#define SUPERIO_LIO_FN 1 /* Function number of Legacy IO controller */
DECL|macro|SUPERIO_USB_FN
mdefine_line|#define SUPERIO_USB_FN 2 /* Function number of USB controller */
DECL|macro|is_superio_device
mdefine_line|#define is_superio_device(x) &bslash;&n;&t;(((x)-&gt;vendor == PCI_VENDOR_ID_NS) &amp;&amp; &bslash;&n;&t;(  ((x)-&gt;device == PCI_DEVICE_ID_NS_87415) &bslash;&n;&t;|| ((x)-&gt;device == PCI_DEVICE_ID_NS_87560_LIO) &bslash;&n;&t;|| ((x)-&gt;device == PCI_DEVICE_ID_NS_87560_USB) ) )
r_struct
id|hwif_s
suffix:semicolon
r_extern
r_void
id|superio_inform_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|superio_serial_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* called by rs_init() */
r_extern
r_int
id|superio_fixup_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
)paren
suffix:semicolon
multiline_comment|/* called by iosapic */
r_extern
r_void
id|superio_fixup_pci
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
macro_line|#endif /* _PARISC_SUPERIO_H */
eof
