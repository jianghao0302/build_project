################################## HOST TOOLCHAIN ############################################
# -------------------------------- start HOST info -------------------------------------------
HOSTARCH := $(shell uname -m | \
	sed -e s/i.86/x86/ \
	    -e s/sun4u/sparc64/ \
	    -e s/arm.*/arm/ \
	    -e s/sa110/arm/ \
	    -e s/ppc64/powerpc/ \
	    -e s/ppc/powerpc/ \
	    -e s/macppc/powerpc/\
	    -e s/sh.*/sh/)

HOSTOS := $(shell uname -s | tr '[:upper:]' '[:lower:]' | \
	    sed -e 's/\(cygwin\).*/cygwin/')

export	HOSTARCH HOSTOS
# -------------------------------- end HOST info -------------------------------------------

HOSTCC       = cc
HOSTCXX      = c++
HOSTCFLAGS   = -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer $(if $(CONFIG_TOOLS_DEBUG),-g)
HOSTCXXFLAGS = -O2

export HOSTCC HOSTCXX HOSTCFLAGS HOSTCXXFLAGS

################################## CROSS TOOLCHAIN ############################################
ifeq ($(HOSTARCH),$(ARCH))
CROSS_COMPILE ?=
else
CROSS_COMPILE ?=
endif

AS		= $(CROSS_COMPILE)as
# Always use GNU ld
ifneq ($(shell $(CROSS_COMPILE)ld.bfd -v 2> /dev/null),)
LD		= $(CROSS_COMPILE)ld.bfd
else
LD		= $(CROSS_COMPILE)ld
endif
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
LDR		= $(CROSS_COMPILE)ldr
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
AWK			= awk
PERL		= perl
PYTHON		= python
DTC			= dtc

CHECK		= sparse
CHECKFLAGS     := -D__linux__ -Dlinux -D__STDC__ -Dunix -D__unix__ \
		  -Wbitwise -Wno-return-void -D__CHECK_ENDIAN__ $(CF)

CPPFLAGS := -D__KERNEL__ -D__UBOOT__

CFLAGS   := -Wall -Wstrict-prototypes \
		   -Wno-format-security \
		   -fno-builtin -ffreestanding
AFLAGS   := -D__ASSEMBLY__

export ARCH
export CROSS_COMPILE AS LD CC CPP AR NM LDR STRIP OBJCOPY OBJDUMP
export CPPFLAGS CFLAGS AFLAGS
export MAKE AWK PERL PYTHON DTC CHECK CHECKFLAGS
