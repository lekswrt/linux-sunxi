/*
 * Touchscreen driver DMI based configuration code
 *
 * Copyright (c) 2017 Red Hat Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Red Hat authors:
 * Hans de Goede <hdegoede@redhat.com>
 */

#include <linux/acpi.h>
#include <linux/device.h>
#include <linux/dmi.h>
#include <linux/efi_embedded_fw.h>
#include <linux/i2c.h>
#include <linux/notifier.h>
#include <linux/property.h>
#include <linux/string.h>

struct ts_dmi_data {
	/* The EFI embedded-fw code expects this to be the first member! */
	struct efi_embedded_fw_desc embedded_fw;
	const char *acpi_name;
	const struct property_entry *properties;
};

static const struct property_entry cube_iwork8_air_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1660),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 900),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3670-cube-iwork8-air.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("efi-embedded-firmware"),
	{ }
};

static const struct ts_dmi_data cube_iwork8_air_data = {
	.embedded_fw = {
		.name	= "silead/gsl3670-cube-iwork8-air.fw",
		.prefix = { 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 },
		.length	= 38808,
		.crc	= 0xfecde51f,
	},
	.acpi_name	= "MSSL1680:00",
	.properties	= cube_iwork8_air_props,
};

static const struct property_entry jumper_ezpad_mini3_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1700),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1150),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-jumper-ezpad-mini3.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	{ }
};

static const struct ts_dmi_data jumper_ezpad_mini3_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= jumper_ezpad_mini3_props,
};

static const struct property_entry dexp_ursus_7w_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 890),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 630),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1686-dexp-ursus-7w.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	{ }
};

static const struct ts_dmi_data dexp_ursus_7w_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= dexp_ursus_7w_props,
};

static const struct property_entry surftab_twin_10_1_st10432_8_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1900),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1280),
	PROPERTY_ENTRY_U32("touchscreen-inverted-y", 1),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl3670-surftab-twin-10-1-st10432-8.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	{ }
};

static const struct ts_dmi_data surftab_twin_10_1_st10432_8_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= surftab_twin_10_1_st10432_8_props,
};

static const struct property_entry surftab_wintron70_st70416_6_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 884),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 632),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl1686-surftab-wintron70-st70416-6.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	{ }
};

static const struct ts_dmi_data surftab_wintron70_st70416_6_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= surftab_wintron70_st70416_6_props,
};

static const struct property_entry gp_electronic_t701_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 960),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 640),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl1680-gp-electronic-t701.fw"),
	{ }
};

static const struct ts_dmi_data gp_electronic_t701_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= gp_electronic_t701_props,
};

static const struct property_entry pipo_w2s_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1660),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 880),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl1680-pipo-w2s.fw"),
	PROPERTY_ENTRY_BOOL("efi-embedded-firmware"),
	{ }
};

static const struct ts_dmi_data pipo_w2s_data = {
	.embedded_fw = {
		.name	= "silead/gsl1680-pipo-w2s.fw",
		.prefix = { 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 },
		.length	= 39072,
		.crc	= 0x28d5dc6c,
	},
	.acpi_name	= "MSSL1680:00",
	.properties	= pipo_w2s_props,
};

static const struct property_entry pov_mobii_wintab_p800w_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1800),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1150),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl3692-pov-mobii-wintab-p800w.fw"),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	{ }
};

static const struct ts_dmi_data pov_mobii_wintab_p800w_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= pov_mobii_wintab_p800w_props,
};

static const struct property_entry itworks_tw891_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1600),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 890),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3670-itworks-tw891.fw"),
	{ }
};

static const struct ts_dmi_data itworks_tw891_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= itworks_tw891_props,
};

static const struct property_entry chuwi_hi8_pro_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1728),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1148),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-chuwi-hi8-pro.fw"),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	PROPERTY_ENTRY_BOOL("efi-embedded-firmware"),
	{ }
};

static const struct ts_dmi_data chuwi_hi8_pro_data = {
	.embedded_fw = {
		.name	= "silead/gsl3680-chuwi-hi8-pro.fw",
		.prefix = { 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 },
		.length	= 39864,
		.crc	= 0xfe2bedba,
	},
	.acpi_name	= "MSSL1680:00",
	.properties	= chuwi_hi8_pro_props,
};

static const struct property_entry digma_citi_e200_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1980),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1500),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl1686-digma_citi_e200.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	{ }
};

static const struct ts_dmi_data digma_citi_e200_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= digma_citi_e200_props,
};

static const struct property_entry onda_obook_20_plus_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1728),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1148),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-onda-obook-20-plus.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	{ }
};

static const struct ts_dmi_data onda_obook_20_plus_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= onda_obook_20_plus_props,
};

static const struct property_entry chuwi_hi8_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1665),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-chuwi-hi8.fw"),
	{ }
};

static const struct ts_dmi_data chuwi_hi8_data = {
	.acpi_name      = "MSSL0001:00",
	.properties     = chuwi_hi8_props,
};

static const struct property_entry chuwi_vi8_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1724),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-chuwi-vi8.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	{ }
};

static const struct ts_dmi_data chuwi_vi8_data = {
	.acpi_name      = "MSSL1680:00",
	.properties     = chuwi_vi8_props,
};

static const struct property_entry trekstor_primebook_c13_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 2624),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1920),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl1680-trekstor-primebook-c13.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	{ }
};

static const struct ts_dmi_data trekstor_primebook_c13_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= trekstor_primebook_c13_props,
};

static const struct property_entry teclast_x98plus2_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 2048),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1280),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl1686-teclast_x98plus2.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	{ }
};

static const struct ts_dmi_data teclast_x98plus2_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= teclast_x98plus2_props,
};

static const struct property_entry teclast_x3_plus_props[] = {
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1980),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1500),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-teclast-x3-plus.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	{ }
};

static const struct ts_dmi_data teclast_x3_plus_data = {
	.acpi_name	= "MSSL1680:00",
	.properties	= teclast_x3_plus_props,
};

static const struct property_entry efi_embedded_fw_props[] = {
	PROPERTY_ENTRY_BOOL("efi-embedded-firmware"),
	{ }
};

static const struct ts_dmi_data chuwi_vi8_plus_data = {
	.embedded_fw = {
		.name	= "chipone/icn8505-HAMP0002.fw",
		.prefix = { 0xb0, 0x07, 0x00, 0x00, 0xe4, 0x07, 0x00, 0x00 },
		.length	= 35012,
		.crc	= 0x74dfd3fc,
	},
	.acpi_name	= "CHPN0001:00",
	.properties	= efi_embedded_fw_props,
};

const struct dmi_system_id touchscreen_dmi_table[] = {
	{
		/* CUBE iwork8 Air */
		.driver_data = (void *)&cube_iwork8_air_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "cube"),
			DMI_MATCH(DMI_PRODUCT_NAME, "i1-TF"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		},
	},
	{
		/* Jumper EZpad mini3 */
		.driver_data = (void *)&jumper_ezpad_mini3_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			/* jumperx.T87.KFBNEEA02 with the version-nr dropped */
			DMI_MATCH(DMI_BIOS_VERSION, "jumperx.T87.KFBNEEA"),
		},
	},
	{
		/* DEXP Ursus 7W */
		.driver_data = (void *)&dexp_ursus_7w_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "7W"),
		},
	},
	{
		/* TrekStor SurfTab twin 10.1 ST10432-8 */
		.driver_data = (void *)&surftab_twin_10_1_st10432_8_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TrekStor"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SurfTab twin 10.1"),
		},
	},
	{
		/* Trekstor Surftab Wintron 7.0 ST70416-6 */
		.driver_data = (void *)&surftab_wintron70_st70416_6_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ST70416-6"),
			/* Exact match, different versions need different fw */
			DMI_MATCH(DMI_BIOS_VERSION, "TREK.G.WI71C.JGBMRBA04"),
		},
	},
	{
		/* Trekstor Surftab Wintron 7.0 ST70416-6, newer BIOS */
		.driver_data = (void *)&surftab_wintron70_st70416_6_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TrekStor"),
			DMI_MATCH(DMI_PRODUCT_NAME,
					     "SurfTab wintron 7.0 ST70416-6"),
			/* Exact match, different versions need different fw */
			DMI_MATCH(DMI_BIOS_VERSION, "TREK.G.WI71C.JGBMRBA05"),
		},
	},
	{
		/* Ployer Momo7w (same hardware as the Trekstor ST70416-6) */
		.driver_data = (void *)&surftab_wintron70_st70416_6_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Shenzhen PLOYER"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MOMO7W"),
			/* Exact match, different versions need different fw */
			DMI_MATCH(DMI_BIOS_VERSION, "MOMO.G.WI71C.MABMRBA02"),
		},
	},
	{
		/* GP-electronic T701 */
		.driver_data = (void *)&gp_electronic_t701_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "T701"),
			DMI_MATCH(DMI_BIOS_VERSION, "BYT70A.YNCHENG.WIN.007"),
		},
	},
	{
		/* Pipo W2S */
		.driver_data = (void *)&pipo_w2s_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "PIPO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "W2S"),
		},
	},
	{
		/* Point of View mobii wintab p800w */
		.driver_data = (void *)&pov_mobii_wintab_p800w_data,
		.matches = {
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			DMI_MATCH(DMI_BIOS_VERSION, "3BAIR1013"),
			/* Above matches are too generic, add bios-date match */
			DMI_MATCH(DMI_BIOS_DATE, "08/22/2014"),
		},
	},
	{
		/* I.T.Works TW891 */
		.driver_data = (void *)&itworks_tw891_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "To be filled by O.E.M."),
			DMI_MATCH(DMI_PRODUCT_NAME, "TW891"),
		},
	},
	{
		/* Chuwi Hi8 Pro */
		.driver_data = (void *)&chuwi_hi8_pro_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X1D3_C806N"),
		},
	},
	{
		/* Digma Citi E200 */
		.driver_data = (void *)&digma_citi_e200_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Digma"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CITI E200"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		},
	},
	{
		/* Onda oBook 20 Plus */
		.driver_data = (void *)&onda_obook_20_plus_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "ONDA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "OBOOK 20 PLUS"),
		},
	},
	{
		/* Chuwi Hi8 */
		.driver_data = (void *)&chuwi_hi8_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "ilife"),
			DMI_MATCH(DMI_PRODUCT_NAME, "S806"),
		},
	},
	{
		/* Chuwi Vi8 (CWI506) */
		.driver_data = (void *)&chuwi_vi8_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "i86"),
			DMI_MATCH(DMI_BIOS_VERSION, "CHUWI.D86JLBNR"),
		},
	},
	{
		/* Trekstor Primebook C13 */
		.driver_data = (void *)&trekstor_primebook_c13_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TREKSTOR"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Primebook C13"),
		},
	},
	{
		/* Teclast X98 Plus II */
		.driver_data = (void *)&teclast_x98plus2_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X98 Plus II"),
		},
	},
	{
		/* Teclast X3 Plus */
		.driver_data = (void *)&teclast_x3_plus_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X3 Plus"),
			DMI_MATCH(DMI_BOARD_NAME, "X3 Plus"),
		},
	},
	{
		/* I.T.Works TW701 */
		.driver_data = (void *)&surftab_wintron70_st70416_6_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "i71c"),
			DMI_MATCH(DMI_BIOS_VERSION, "itWORKS.G.WI71C.JGBMRB"),
		},
	},
	{
		/* Yours Y8W81, same case and touchscreen as Chuwi Vi8 */
		.driver_data = (void *)&chuwi_vi8_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "YOURS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Y8W81"),
		},
	},
	{
		/* Chuwi Vi8 Plus (CWI506) */
		.driver_data = (void *)&chuwi_vi8_plus_data,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "D2D3_Vi8A1"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		},
	},
	{ },
};

static const struct ts_dmi_data *ts_data;

static void ts_dmi_add_props(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	int error;

	if (has_acpi_companion(dev) &&
	    !strncmp(ts_data->acpi_name, client->name, I2C_NAME_SIZE)) {
		error = device_add_properties(dev, ts_data->properties);
		if (error)
			dev_err(dev, "failed to add properties: %d\n", error);
	}
}

static int ts_dmi_notifier_call(struct notifier_block *nb,
				       unsigned long action, void *data)
{
	struct device *dev = data;
	struct i2c_client *client;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		client = i2c_verify_client(dev);
		if (client)
			ts_dmi_add_props(client);
		break;

	default:
		break;
	}

	return 0;
}

static struct notifier_block ts_dmi_notifier = {
	.notifier_call = ts_dmi_notifier_call,
};

static int __init ts_dmi_init(void)
{
	const struct dmi_system_id *dmi_id;
	int error;

	dmi_id = dmi_first_match(touchscreen_dmi_table);
	if (!dmi_id)
		return 0; /* Not an error */

	ts_data = dmi_id->driver_data;

	error = bus_register_notifier(&i2c_bus_type, &ts_dmi_notifier);
	if (error)
		pr_err("%s: failed to register i2c bus notifier: %d\n",
			__func__, error);

	return error;
}

/*
 * We are registering out notifier after i2c core is initialized and i2c bus
 * itself is ready (which happens at postcore initcall level), but before
 * ACPI starts enumerating devices (at subsys initcall level).
 */
arch_initcall(ts_dmi_init);
