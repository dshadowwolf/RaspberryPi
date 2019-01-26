#define HW_REGISTER_RW(addr) (*(volatile unsigned long *)(addr))

#define GPFSEL1 HW_REGISTER_RW(0x7e200004)
#define GPSET0 HW_REGISTER_RW(0x7e20001C)
#define GPCLR0 HW_REGISTER_RW(0x7e200028)
#define GPPUD HW_REGISTER_RW(0x7e200094)
#define GPPUDCLK0 HW_REGISTER_RW(0x7e200098)

#define AUX_ENABLES HW_REGISTER_RW(0x7e215004)
#define AUX_MU_IO_REG HW_REGISTER_RW(0x7e215040)
#define AUX_MU_IER_REG HW_REGISTER_RW(0x7e215044)
#define AUX_MU_IIR_REG HW_REGISTER_RW(0x7e215048)
#define AUX_MU_LCR_REG HW_REGISTER_RW(0x7e21504C)
#define AUX_MU_MCR_REG HW_REGISTER_RW(0x7e215050)
#define AUX_MU_LSR_REG HW_REGISTER_RW(0x7e215054)
#define AUX_MU_MSR_REG HW_REGISTER_RW(0x7e215058)
#define AUX_MU_SCRATCH HW_REGISTER_RW(0x7e21505C)
#define AUX_MU_CNTL_REG HW_REGISTER_RW(0x7e215060)
#define AUX_MU_STAT_REG HW_REGISTER_RW(0x7e215064)
#define AUX_MU_BAUD_REG HW_REGISTER_RW(0x7e215068)

#define OTP_BOOTMODE_REG HW_REGISTER_RW(0x7e20f000)
#define OTP_CONFIG_REG HW_REGISTER_RW(0x7e20f004)
#define OTP_CTRL_LO_REG HW_REGISTER_RW(0x7e20f008)
#define OTP_CTRL_HI_REG HW_REGISTER_RW(0x7e20f00c)
#define OTP_STATUS_REG HW_REGISTER_RW(0x7e20f010)
#define OTP_BITSEL_REG HW_REGISTER_RW(0x7e20f014)
#define OTP_DATA_REG HW_REGISTER_RW(0x7e20f018)
#define OTP_ADDR_REG HW_REGISTER_RW(0x7e20f01c)
#define OTP_WRITE_DATA_READ_REG HW_REGISTER_RW(0x7e20f020)
#define OTP_INIT_STATUS_REG HW_REGISTER_RW(0x7e20f024)
  
#define GP_FSEL14_CLEAR 0xffff8fffU
#define GP_FSEL15_CLEAR 0xfffc7fffU
#define GP_PIN14 12
#define GP_PIN15 15
#define GP_CLK_PIN14 (1 << 14)
#define GP_CLK_PIN15 (1 << 15)
#define MASK(var, mask) (var) &= (mask)
#define ALT_FUNCTION_5 2
#define SET(var, func, pin) (var) |= ((func) << (pin))