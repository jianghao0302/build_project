




###################### config target #############################

scripts/config/mconf:
	@cd scripts/config && make all

scripts/config/qconf:
	@cd scripts config && make qconf

scripts/config/conf:
	@cd scripts config && make conf

config: scripts/config/conf


defconfig: scripts/config/conf

oldconfig: scripts/config/conf

menuconfig: scripts/config/mconf
	$< Config.in


xconfig: scripts/config/qconf


config-clean:

