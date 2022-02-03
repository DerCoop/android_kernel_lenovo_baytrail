apt install bc

bash scripts/build_tablet_config.sh YT2_8 .
cp arch/x86/configs/x86_64_byt_defconfig .config
make menuconfig
make -j8

