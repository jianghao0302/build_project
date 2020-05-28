TOPDIR:=${CURDIR}
export TOPDIR

world:

include $(TOPDIR)/scripts/toolchain.mk
include $(TOPDIR)/scripts/config.mk
