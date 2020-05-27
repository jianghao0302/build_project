




###################### config target #############################

scripts/config/mconf:
	@cd scripts/config && make all

scripts/config/qconf:
	@cd scripts config && make qconf

scripts/config/conf:
	@cd scripts config && make conf

config: scripts/config/conf FORCE


defconfig: scripts/config/conf FORCE

oldconfig: scripts/config/conf FORCE

menuconfig: scripts/config/mconf FORCE
	$< Config.in


xconfig: scripts/config/qconf FORCE


config-clean: FORCE

