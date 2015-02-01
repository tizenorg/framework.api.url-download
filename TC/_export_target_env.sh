# Customize below path information 
TET_INSTALL_PATH=/mnt/dts/TETware
TET_TARGET_PATH=$TET_INSTALL_PATH/tetware-target

export ARCH=target
export TET_ROOT=$TET_TARGET_PATH
export PATH=$TET_ROOT/bin:$PATH
export LD_LIBRARY_PATH=$TET_ROOT/lib/tet3:$LD_LIBRARY_PATH
