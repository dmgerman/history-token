multiline_comment|/*&n; * It&squot;s nice to have the LEDs on the GPIO pins available for debugging&n; */
DECL|function|ddb5074_fixup
r_static
r_void
id|ddb5074_fixup
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_extern
r_struct
id|pci_dev
op_star
id|pci_pmu
suffix:semicolon
id|u8
id|t8
suffix:semicolon
id|pci_pmu
op_assign
id|dev
suffix:semicolon
multiline_comment|/* for LEDs D2 and D3 */
multiline_comment|/* Program the lines for LEDs D2 and D3 to output */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x7d
comma
op_amp
id|t8
)paren
suffix:semicolon
id|t8
op_or_assign
l_int|0xc0
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x7d
comma
id|t8
)paren
suffix:semicolon
multiline_comment|/* Turn LEDs D2 and D3 off */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x7e
comma
op_amp
id|t8
)paren
suffix:semicolon
id|t8
op_or_assign
l_int|0xc0
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x7e
comma
id|t8
)paren
suffix:semicolon
)brace
id|DECLARE_PCI_FIXUP_FINAL
c_func
(paren
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M7101
comma
id|ddb5074_fixup
)paren
suffix:semicolon
eof
