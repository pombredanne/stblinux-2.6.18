#
# Broadcom Settop Box build script for Big Endian
#
# With initramfs support in kernel 2.6.x,
# this build script no longer requires root access for kernel images
# However, root access is needed for building rootfs images
# and the user will be prompted ONCE for the root password
# during 'make rootfs'
#
# To build all kernels (initrd and regular kernels)
#  % make -f build.mk [platform]
#
# To build just the initrd kernel for one platform
# % make -f build.mk vmlinuz-initrd-7038b0
#
# To build just the regular kernel for one platform
# % make -f build.mk vmlinuz-7038b0
#
# Note, the % is to underline the fact that no root access is needed to build kernel images.
#
# To build rootfs images, suitable for stbutil, one will need root access
#
# To build just the rootfs images for 1 platform, after building the kernels for the 7038b0 platform
# # make -f build.mk rootfs-7038b0
#
# To build the kernel and images for all platforms:
# % make -f build.mk [ROOT=root] all
# You will be prompted one time for the root password
#
# To build the kernels non-interactively, just log on as root and do
# # make -f build.mk all
#
WHOAMI ?= $(shell who am i | cut -d" " -f1 | cut -d'!' -f2)
MYGID = $(shell id -g)
MYUID := $(shell id -u)

#On some machines, root is not just root, but a privileged account
ROOT=

# if nothing works, set it to login name
ifeq ($(strip $(WHOAMI)),)
    WHOAMI=$(LOGNAME)
endif

#BCM7XXX= 7400a0 7400a0-smp 7038 7038b0 7110 7110-docsis 7112 7115 7315 7317 7319 7320 7328 7329
#VENOM=937xx
# PLATFORMS=$(BCM7XXX) $(VENOM)

# THT For 2.6.12-0 we only support a few platforms
CHIPS=7038c0 97398 7318 7400a0 7400a0-smp 7401a0 7401b0 7401c0
PLATFORMS=$(addsuffix _be,$(CHIPS))
XFS_PLATFORMS = 7038c0_be-xfs 97398_be-xfs
ALL_PLATFORMS = $(PLATFORMS) $(XFS_PLATFORMS)

BB_PLATFORMS:=$(addprefix vmlinuz-,$(PLATFORMS))
BB_INITRD_PLATFORMS	:= $(addprefix vmlinuz-initrd-,$(PLATFORMS))

XFS_BB_PLATFORMS:=$(addprefix vmlinuz-,$(XFS_PLATFORMS))
XFS_INITRD_PLATFORMS := $(addprefix vmlinuz-initrd-,$(XFS_PLATFORMS))

KGDB_PLATFORMS := $(addprefix vmlinuz-,$(addsuffix -kgdb,$(ALL_PLATFORMS)))
# Pass this flag with a value of "y" to enable kgdb debugging
# over Single Serial Port
# make -f build.mk SINGLE_SERIAL_PORT=y vmlinuz-3560-kgdb
SINGLE_SERIAL_PORT=n

OPROF_PLATFORMS := $(addprefix vmlinuz-,$(addsuffix -opf,$(ALL_PLATFORMS)))
OPROF_INITRD_PLATFORMS := $(addprefix vmlinuz-initrd-,$(addsuffix -opf,$(ALL_PLATFORMS)))
OPROFILE_PLATFORMS := $(addsuffix -opf,$(ALL_PLATFORMS))

ROOTFS_PLATFORMS := $(addprefix rootfs-,$(ALL_PLATFORMS))
JFFS2_IMAGES := $(addsuffix .img,$(JFFS2_PLATFORMS))
CRAMFS_PLATFORMS := $(addprefix cramfs-,$(ALL_PLATFORMS))
CRAMFS_IMAGES := $(addsuffix .img,$(JFFS2_PLATFORMS))

VERSION=$(shell cat version)-be
TFTPBOOT=/tftpboot
TFTPDIR=$(TFTPBOOT)/$(VERSION)
KERNEL_DIR=linux-2.6.x
CROSS_COMPILE=mips-linux-
CC=$(CROSS_COMPILE)gcc
MAKEARCH=make ARCH=mips CROSS_COMPILE=$(CROSS_COMPILE) CC=$(CC)
#jipeng
LINUXDIR_VER=
ROOTFS_VER=
ifeq ($@,) 
	LINUXDIR_VER+=$(shell grep -as "^EXTRAVERSION" ${KERNEL_DIR}/Makefile | sed "s/[A-Za-z\= \-]//g")
	ROOTFS_VER+=$(shell cat version | sed "s/.*\-//")
endif

INITRD_DEFCONFIG=
KERNEL_DEFCONFIG=
ifneq ($(test),) 
	INITRD_DEFCONFIG:=$(test)
	KERNEL_DEFCONFIG:=$(test)
else
	INITRD_DEFCONFIG:=vendors/$$CONFIG_VENDOR/$$CONFIG_PRODUCT/config.$$CONFIG_LINUXDIR
endif

kernels: vercheck	
	for i in $(ALL_PLATFORMS); do \
		make -f build-be.mk $$i; \
	done

all: vercheck kernels install

.PHONY: vercheck install rootfs

#jipeng - check version mismatch between rootfs and kernel source
vercheck:
	@test -f ${KERNEL_DIR}/Makefile || (echo "FATAL Error: miss ${KERNEL_DIR}/Makefile"; exit 1)
	@if [ "$(LINUXDIR_VER)" == "$(ROOTFS_VER)" ]; then	\
		echo "build binary images for version $(VERSION)";	\
	else	\
		echo "Error: Kernel version $(LINUXDIR_VER) mismatch with rootfs version $(ROOTFS_VER)"; exit 1;	\
	fi

install: rootfs

rootfs:
	# Make the rootfs images, need root access
	su -m -c '$(shell for i in $(ALL_PLATFORMS); do \
		echo "make -f build-be.mk rootfs-$$i; "; \
	done)' $(ROOT)
	# Copy to TFTP server.  Here this script assumes that only normal users
	# can write to the server (NFS mounted), your mileage may vary.
	@if [ $(MYUID) -ne 0 ]; then \
		for i in $(ALL_PLATFORMS); do \
			cp images/$$i/jffs2.img $(TFTPDIR)/jffs2-$$i.img; \
			cp images/$$i/cramfs.img $(TFTPDIR)/cramfs-$$i.img; \
		done; \
	else \
		for i in $(ALL_PLATFORMS); do \
			su -m -c "cp images/$$i/jffs2.img $(TFTPDIR)/jffs2-$$i.img && \
				cp images/$$i/cramfs.img $(TFTPDIR)/cramfs-$$i.img" $(WHOAMI); \
		done; \
	fi

.PHONY: $(ALL_PLATFORMS) $(BB_INITRD_PLATFORMS) $(BB_PLATFORMS) \
	$(ROOTFS_PLATFORMS) $(ROOTFS_IMAGES) $(CRAMFS_PLATFORMS) $(JFFS2_PLATFORMS) \
	$(OPROFILE_PLATFORMS)


$(ALL_PLATFORMS) :
	echo "Making BE uclinux-rootfs and kernels for $@ version=$(VERSION)"
	make -f build-be.mk vmlinuz-initrd-$@
	make -f build-be.mk vmlinuz-$@


$(OPROFILE_PLATFORMS) :
	echo "Making BE OPROFILE uclinux-rootfs and kernels for $@ version=$(VERSION)"
	make -f build-be.mk vmlinuz-initrd-$@
	make -f build-be.mk vmlinuz-$@
	
$(ROOTFS_PLATFORMS):
	@if [ $(MYUID) -ne 0 ]; then \
		echo "Making target $@ requires root access"; \
		exit 1; \
	else \
		echo "Making rootfs images for $@ version=$(VERSION)"; \
	fi
	# We don't check whether the image is up-todate, but assume that it has been built.
	su -m -c "cp -f defconfigs/defconfig-brcm-uclinux-rootfs-$(subst rootfs-,,$@) .config" \
		$(WHOAMI) 2>/dev/null
	su -m -c '. .config && make -C vendors/"$$CONFIG_VENDOR"/"$$CONFIG_PRODUCT" \
		ROOTDIR=$(shell pwd) \
		LINUX_CONFIG=$(shell pwd)/vendors/"$$CONFIG_VENDOR/$$CONFIG_PRODUCT"/config.linux-2.6.x \
		CONFIG_CONFIG=$(shell pwd)/vendors/"$$CONFIG_VENDOR/$$CONFIG_PRODUCT"/config.vendor-2.6.x \
		LINUXDIR=$$CONFIG_LINUXDIR\
		IMAGEDIR=$(shell pwd)/images\
		PLATFORM=$(subst rootfs-,,$@)\
		ARCH_CONFIG=$(shell pwd)/vendors/"$$CONFIG_VENDOR"/"$$CONFIG_PRODUCT"/config.arch\
		images' $(ROOT) 
	su -m -c "cp images/$(subst rootfs-,,$@)/jffs2.img $(TFTPDIR)/jffs2-$(subst rootfs-,,$@).img" $(WHOAMI)
	su -m -c "cp images/$(subst rootfs-,,$@)/cramfs.img $(TFTPDIR)/cramfs-$(subst rootfs-,,$@).img" $(WHOAMI)

# The echo Done at the end is to prevent make from reporting errors.
$(BB_INITRD_PLATFORMS) $(XFS_INITRD_PLATFORMS):
	cp -f defconfigs/defconfig-brcm-uclinux-rootfs-$(subst vmlinuz-initrd-,,$@) .config
	# Set CONFIG_INITRAMFS_ROOT_UID & GID accordingly
	(. .config; test -f "$${CONFIG_LINUXDIR}"/.config && rm -f "$${CONFIG_LINUXDIR}"/.config; \
		sed -e "s/CONFIG_INITRAMFS_ROOT_UID=0/CONFIG_INITRAMFS_ROOT_UID=$(MYUID)/"\
			${INITRD_DEFCONFIG} \
		| sed -e "s/CONFIG_INITRAMFS_ROOT_GID=0/CONFIG_INITRAMFS_ROOT_GID=$(MYGID)/" \
			> $${CONFIG_LINUXDIR}/.config; \
		cp -f vendors/$${CONFIG_VENDOR}/$${CONFIG_PRODUCT}/config.uClibc uClibc/.config; \
		cp -f vendors/$${CONFIG_VENDOR}/$${CONFIG_PRODUCT}/config.busybox user/busybox/.config; \
		cp -f vendors/$${CONFIG_VENDOR}/$${CONFIG_PRODUCT}/config.vendor-2.6.x config/.config; \
		cd $${CONFIG_LINUXDIR} && $(MAKEARCH) silentoldconfig; \
	)
	$(MAKEARCH) defaultconfig
	$(MAKEARCH) BRCM_VERSION=$(VERSION)
	test -d $(TFTPDIR) || mkdir -p $(TFTPDIR)
	if [ "$(subst vmlinuz-initrd-,,$@)" == "937xx_be" -o \
         "$(subst vmlinuz-initrd-,,$@)" == "937xx_be-xfs" ]; then \
		cp -f images/937xx_be/vmlinux $(TFTPDIR)/$(subst vmlinuz-,vmlinux-,$@) ; \
	else \
		cp -f images/$(subst vmlinuz-initrd-,,$@)/vmlinuz $(TFTPDIR)/$@ ;\
	fi
	echo "Done building $@"

$(BB_PLATFORMS) $(XFS_BB_PLATFORMS):
	if [ "x$(KERNEL_DEFCONFIG)" != "x" ]; then	\
		test -f $(KERNEL_DEFCONFIG) && 	cp $(KERNEL_DEFCONFIG) $(KERNEL_DIR)/.config	\
		|| exit 1;	\
	else	\
		if test -f $(KERNEL_DIR)/arch/mips/configs/bcm9$(subst vmlinuz-,,$@)_defconfig; then	\
			cp $(KERNEL_DIR)/arch/mips/configs/bcm9$(subst vmlinuz-,,$@)_defconfig $(KERNEL_DIR)/.config;	\
		else	\
			test -f $(KERNEL_DIR)/arch/mips/configs/bcm$(subst vmlinuz-,,$@)_defconfig	\
			&& cp $(KERNEL_DIR)/arch/mips/configs/bcm$(subst vmlinuz-,,$@)_defconfig $(KERNEL_DIR)/.config	\
			|| exit 1;	\
		fi;	\
	fi;	\
	$(MAKEARCH) -C $(KERNEL_DIR) silentoldconfig
	$(MAKEARCH) -C $(KERNEL_DIR) BRCM_VERSION=$(VERSION)
	test -d $(TFTPDIR) || mkdir -p $(TFTPDIR)
	if [ $(subst vmlinuz-,,$@) != "937xx" -a $(subst vmlinuz-,,$@) != "937xx-xfs" ]; then \
		gzip -3fc $(KERNEL_DIR)/vmlinux > $(TFTPDIR)/$@ ; \
	else \
		cp -f $(KERNEL_DIR)/vmlinux $(TFTPDIR)/$(subst vmlinuz-,vmlinux-,$@) ; \
	fi

#
# KGDB targets: will output kernel images of the form
# vmlinuz-<platform>-kgdb
# Only non-initrd images can be targets, for now.
#
# Should do a make clean manually before involking any kgdb targets.
# Omitted here since these are normally one time shot deals.
$(KGDB_PLATFORMS):
	-test -f $(KERNEL_DIR)/.config && rm -f $(KERNEL_DIR)/.config
	if [ "$(subst vmlinuz-,,$@)" == "937xx_be-kgdb" -o "$(subst vmlinuz-,,$@)" == "97398_be-kgdb" \
        "$(subst vmlinuz-,,$@)" == "937xx_be-xfs-kgdb" -o "$(subst vmlinuz-,,$@)" == "97398_be-xfs-kgdb" ]; then \
		cat $(KERNEL_DIR)/arch/mips/configs/bcm$(subst vmlinuz-,,$(subst -kgdb,,$@))_defconfig | \
			sed 's,# CONFIG_KGDB is not set,CONFIG_KGDB=y,g' | \
			sed 's,# CONFIG_DEBUG_INFO is not set,CONFIG_DEBUG_INFO=y,g' \
				> $(KERNEL_DIR)/.config; \
	else \
		cat $(KERNEL_DIR)/arch/mips/configs/bcm9$(subst vmlinuz-,,$(subst -kgdb,,$@))_defconfig | \
			sed 's,# CONFIG_KGDB is not set,CONFIG_KGDB=y,g' | \
			sed 's,# CONFIG_DEBUG_INFO is not set,CONFIG_DEBUG_INFO=y,g' \
				>  $(KERNEL_DIR)/.config; \
	fi
	if [ "$(SINGLE_SERIAL_PORT)" == "y" ]; then \
		echo "CONFIG_SINGLE_SERIAL_PORT=y" >> $(KERNEL_DIR)/.config; \
	else \
		echo "# CONFIG_SINGLE_SERIAL_PORT is not set" >> $(KERNEL_DIR)/.config; \
	fi
	$(MAKEARCH) -C $(KERNEL_DIR) silentoldconfig
	$(MAKEARCH) -C $(KERNEL_DIR) BRCM_VERSION=$(VERSION)
	test -d $(TFTPDIR) || mkdir -p $(TFTPDIR)
	if [ $(subst vmlinuz-,,$@) != "937xx_be-kgdb" -a $(subst vmlinuz-,,$@) != "937xx_be-xfs-kgdb" ]; then \
		gzip -3fc $(KERNEL_DIR)/vmlinux > $(TFTPDIR)/$@ ; \
	else \
		cp -f $(KERNEL_DIR)/vmlinux $(TFTPDIR)/$(subst vmlinuz-,vmlinux-,$@); \
	fi
	

# The echo Done at the end is to prevent make from reporting errors.
$(OPROF_INITRD_PLATFORMS) :
	cp -f defconfigs/defconfig-brcm-uclinux-rootfs-$(subst -opf,,$(subst vmlinuz-initrd-,,$@)) .config
	# Set locale stuffs.  We will need
	. .config; export LANG="C"; export LC_MESSAGES="C"; export LC_CTYPE="C"; export LC_ALL="C"; \
		test -f "$$CONFIG_LINUXDIR"/.config && rm -f "$$CONFIG_LINUXDIR"/.config; \
		sed -e "s/CONFIG_INITRAMFS_ROOT_UID=0/CONFIG_INITRAMFS_ROOT_UID=$(MYUID)/"\
			vendors/"$$CONFIG_VENDOR"/"$$CONFIG_PRODUCT"/config."$$CONFIG_LINUXDIR"  \
		| sed -e "s/CONFIG_INITRAMFS_ROOT_GID=0/CONFIG_INITRAMFS_ROOT_GID=$(MYGID)/" \
		| sed -e "s/# CONFIG_PROFILING is not set/CONFIG_PROFILING=y/" \
			> "$$CONFIG_LINUXDIR"/.config; \
		echo "CONFIG_OPROFILE=y" >> "$$CONFIG_LINUXDIR"/.config; \
		cp -f vendors/"$$CONFIG_VENDOR"/"$$CONFIG_PRODUCT"/config.uClibc uClibc/.config; \
		cp -f vendors/"$$CONFIG_VENDOR"/"$$CONFIG_PRODUCT"/config.busybox user/busybox/.config; \
		test -f config/.config && rm -f config/.config; \
		sed -e "s/# CONFIG_USER_PROFILE_OPROFILE is not set/CONFIG_USER_PROFILE_OPROFILE=y/" \
			vendors/"$$CONFIG_VENDOR"/"$$CONFIG_PRODUCT"/config.vendor-2.6.x  \
		| sed -e "s/# CONFIG_USER_PROFILE_POFT is not set/CONFIG_USER_PROFILE_POFT=y/" > config/.config; \
		(cd "$$CONFIG_LINUXDIR" && $(MAKEARCH) silentoldconfig);
	$(MAKEARCH) oprofile
	$(MAKEARCH) BRCM_VERSION=$(VERSION)
	test -d $(TFTPDIR) || mkdir -p $(TFTPDIR)
	if [ "$(subst -opf,,$(subst vmlinuz-initrd-,,$@))" == "937xx_be" -o \
       "$(subst -opf,,$(subst vmlinuz-initrd-,,$@))" == "937xx_be-xfs" ]; then \
		cp -f images/937xx/vmlinux $(TFTPDIR)/vmlinux-$(subst -opf,,$(subst vmlinuz-initrd-,,$@)) ; \
	else \
		cp -f images/$(subst -opf,,$(subst vmlinuz-initrd-,,$@))/vmlinuz $(TFTPDIR)/$@ ;\
	fi
	echo "Done building $@"

$(OPROF_PLATFORMS) :
	-test -f $(KERNEL_DIR)/.config && rm -f $(KERNEL_DIR)/.config
	if test -f $(KERNEL_DIR)/arch/mips/configs/bcm$(subst vmlinuz-,,$(subst -opf,,$@))_defconfig; then	\
		cat $(KERNEL_DIR)/arch/mips/configs/bcm$(subst vmlinuz-,,$(subst -opf,,$@))_defconfig | \
			sed 's/# CONFIG_PROFILING is not set/CONFIG_PROFILING=y/g' \
				> $(KERNEL_DIR)/.config; \
		echo "CONFIG_OPROFILE=y" >> $(KERNEL_DIR)/.config; \
	else \
		cat $(KERNEL_DIR)/arch/mips/configs/bcm9$(subst vmlinuz-,,$(subst -opf,,$@))_defconfig | \
			sed 's,# CONFIG_PROFILING is not set,CONFIG_PROFILING=y,g' \
				>  $(KERNEL_DIR)/.config; \
		echo "CONFIG_OPROFILE=y" >> $(KERNEL_DIR)/.config; \
	fi
	$(MAKEARCH) -C $(KERNEL_DIR) silentoldconfig
	$(MAKEARCH) -C $(KERNEL_DIR) BRCM_VERSION=$(VERSION)
	test -d $(TFTPDIR) || mkdir -p $(TFTPDIR)
	if [ $(subst -opf,,$(subst vmlinuz-,,$@)) != "937xx_be" -a \
     $(subst -opf,,$(subst vmlinuz-,,$@)) != "937xx_be-xfs" ]; then \
		gzip -3fc $(KERNEL_DIR)/vmlinux > $(TFTPDIR)/$@ ; \
	else \
		cp -f $(KERNEL_DIR)/vmlinux $(TFTPDIR)/$(subst vmlinuz,vmlinux,$@); \
	fi

clean:
	rm -f $(ALL_PLATFORMS) $(BB_INITRD_PLATFORMS) $(BB_PLATFORMS)
	$(MAKEARCH) $@

distclean:
	rm -f $(ALL_PLATFORMS) $(BB_INITRD_PLATFORMS) $(BB_PLATFORMS)
	# Requires root access to clean the images directory
	su -m -c '$(MAKEARCH) $@' $(ROOT)
