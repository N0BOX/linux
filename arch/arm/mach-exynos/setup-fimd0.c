/* linux/arch/arm/mach-exynos4/setup-fimd0.c
 *
 * Copyright (c) 2009-2011 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com
 *
 * Base Exynos4 FIMD 0 configuration
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/fb.h>
#include <linux/gpio.h>

#include <video/samsung_fimd.h>
#include <plat/gpio-cfg.h>

#include <mach/map.h>

static void s3cfb_gpio_setup_24bpp(unsigned int start, unsigned int size,
		unsigned int cfg, s5p_gpio_drvstr_t drvstr)
{
	// u32 reg;

	s3c_gpio_cfgrange_nopull(start, size, cfg);

	for (; size > 0; size--, start++)
		s5p_gpio_set_drvstr(start, drvstr);

	/* Set FIMD0 bypass
	 * reg = __raw_readl(S3C_VA_SYS + 0x0210);
	 * reg |= (1<<1);
	 * __raw_writel(reg, S3C_VA_SYS + 0x0210);
   */
}

void exynos4_fimd0_gpio_setup_24bpp(void)
{
	unsigned int reg;

  #ifdef CONFIG_FB_S3C_LCD_INIT_FLXODXEB
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF0(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV3);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF0(6), 2, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF1(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF1(6), 2, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF2(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF2(6), 2, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF3(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV1);
	#else
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF0(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF1(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF2(0), 8, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
		s3cfb_gpio_setup_24bpp(EXYNOS4_GPF3(0), 4, S3C_GPIO_SFN(2), S5P_GPIO_DRVSTR_LV4);
	#endif

	/*
	 * Set DISPLAY_CONTROL register for Display path selection.
	 *
	 * DISPLAY_CONTROL[1:0]
	 * ---------------------
	 *  00 | MIE
	 *  01 | MDINE
	 *  10 | FIMD : selected
	 *  11 | FIMD
	 */
	reg = __raw_readl(S3C_VA_SYS + 0x0210);
	reg |= (1 << 1);
	__raw_writel(reg, S3C_VA_SYS + 0x0210);
}
