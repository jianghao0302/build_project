TOPDIR:=${CURDIR}
export TOPDIR

world:

include $(TOPDIR)/scripts/toolchain.mk
#include $(TOPDIR)/scripts/config.mk

#########################################################################################
#
# config target
# 
#########################################################################################
CONFIG_DIR = $(TOPDIR)/scripts/config

$(CONFIG_DIR)/%onf:
	$(MAKE) CC="$(HOSTCC)" obj=$(@D) -C $(CONFIG_DIR) -f Makefile $(@F)


xconfig: $(CONFIG_DIR)/qconf outputmakefile
	$< Config.in

gconfig: $(CONFIG_DIR)/gconf outputmakefile
	$< Config.in

menuconfig: $(CONFIG_DIR)/mconf
	$< Config.in

nconfig: $(CONFIG_DIR)/nconf outputmakefile
	$< Config.in

config: $(CONFIG_DIR)/conf
	$< Config.in

oldconfig: $(CONFIG_DIR)/conf outputmakefile
	$< --$@ Config.in

defconfig: $(CONFIG_DIR)/conf outputmakefile
	$< --defconfig$(if $(DEFCONFIG),=$(DEFCONFIG)) $(CONFIG_CONFIG_IN)

savedefconfig: $(CONFIG_DIR)//conf outputmakefile
	@$(COMMON_CONFIG_ENV) $< \
		--savedefconfig=$(if $(DEFCONFIG),$(DEFCONFIG),$(CONFIG_DIR)/defconfig) \
		$(CONFIG_CONFIG_IN)
	@$(SED) '/BR2_DEFCONFIG=/d' $(if $(DEFCONFIG),$(DEFCONFIG),$(CONFIG_DIR)/defconfig)

config-clean:

.PHONY: defconfig savedefconfig update-defconfig


#########################################################################################
#
# generate config.h
# 
#########################################################################################

include/config.h: scripts/Makeifle.autoconf	create_symlink
	$(call filechk,config_h)