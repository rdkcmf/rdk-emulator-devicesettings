#!/bin/bash

#######################################
#
# Build Framework standard script for
#
# DeviceSettings component

# use -e to fail on any shell issue
# -e is the requirement from Build Framework
set -e


# default PATHs - use `man readlink` for more info
# the path to combined build
export RDK_PROJECT_ROOT_PATH=${RDK_PROJECT_ROOT_PATH-`readlink -m ..`}/
export COMBINED_ROOT=$RDK_PROJECT_ROOT_PATH

# path to build script (this script)
export RDK_SCRIPTS_PATH=${RDK_SCRIPTS_PATH-`readlink -m $0 | xargs dirname`}/

# path to components sources and target
export RDK_SOURCE_PATH=${RDK_SOURCE_PATH-`readlink -m .`}/
export RDK_TARGET_PATH=${RDK_TARGET_PATH-$RDK_SOURCE_PATH}

# fsroot and toolchain (valid for all devices)
export RDK_FSROOT_PATH=${RDK_FSROOT_PATH-`readlink -m $RDK_PROJECT_ROOT_PATH/sdk/fsroot/ramdisk`}/
export RDK_TOOLCHAIN_PATH=${RDK_TOOLCHAIN_PATH-`readlink -m $RDK_PROJECT_ROOT_PATH/sdk/toolchain/staging_dir`}/


# default component name
export RDK_COMPONENT_NAME=${RDK_COMPONENT_NAME-`basename $RDK_SOURCE_PATH`}


#RDK Emulator
ln -sf ../../platform/ds/include/dsAudioSettings.h devicesettings/ds/include/dsAudioSettings.h
ln -sf ../../platform/ds/include/dsVideoDeviceSettings.h  devicesettings/ds/include/dsVideoDeviceSettings.h
ln -sf ../../platform/ds/include/dsVideoPortSettings.h devicesettings/ds/include/dsVideoPortSettings.h
ln -sf ../../platform/ds/include/dsVideoResolutionSettings.h devicesettings/ds/include/dsVideoResolutionSettings.h
ln -sf ../platform/hal/emu devicesettings/hal/emu

# parse arguments
INITIAL_ARGS=$@

function usage()
{
    set +x
    echo "Usage: `basename $0` [-h|--help] [-v|--verbose] [action]"
    echo "    -h    --help                  : this help"
    echo "    -v    --verbose               : verbose output"
    echo "    -p    --platform  =PLATFORM   : specify platform for DeviceSettings"
    echo
    echo "Supported actions:"
    echo "      configure, clean, build (DEFAULT), rebuild, install"
}

# options may be followed by one colon to indicate they have a required argument
if ! GETOPT=$(getopt -n "build.sh" -o hvp: -l help,verbose,platform: -- "$@")
then
    usage
    exit 1
fi

eval set -- "$GETOPT"

while true; do
  case "$1" in
    -h | --help ) usage; exit 0 ;;
    -v | --verbose ) set -x ;;
    -p | --platform ) CC_PLATFORM="$2" ; shift ;;
    -- ) shift; break;;
    * ) break;;
  esac
  shift
done

ARGS=$@


# component-specific vars
CC_PATH=$RDK_SOURCE_PATH
export FSROOT=${RDK_FSROOT_PATH}
export TOOLCHAIN_DIR=${RDK_TOOLCHAIN_PATH}
export WORK_DIR=${RDK_PROJECT_ROOT_PATH}/workXI3
export BUILDS_DIR=$RDK_PROJECT_ROOT_PATH
export COMBINED_DIR=$COMBINED_ROOT


# functional modules

function configure()
{
    true #use this function to perform any pre-build configuration
}

function clean()
{
    true #use this function to provide instructions to clean workspace
}

function build()
{
    #source $RDK_PROJECT_ROOT_PATH/build_scripts/setBCMenv.sh

    DeviceSettings_PATH=${CC_PATH}
    CURR_DIR=`pwd`

    cd $DeviceSettings_PATH
    echo "Setting hal Environment variables..."
    #source $DeviceSettings_PATH/hal/src/halenv.sh
    echo "Building Device Setting libraries..."
    if [ "$BUILD_CONFIG" == "rdkemulator" ] || [ "$BUILD_CONFIG" == "mediaclient" ] || [ "$BUILD_CONFIG" == "headlessgateway" ]; then
	export SDK_ROOT=" "
    else
	export SDK_ROOT=$FSROOT
    fi
    make all

    cd $CURR_DIR
}

function rebuild()
{
    clean
    build
}

function install()
{
    DeviceSettings_PATH=${CC_PATH}

    CURR_DIR=`pwd`

    cd $DeviceSettings_PATH/install

    if [ "$BUILD_CONFIG" == "rdkemulator" ]; then
    	cd $DeviceSettings_PATH/hal/emu
    	mkdir -p ${RDK_PROJECT_ROOT_PATH}/debian/mnt/nfs/env

    	cp -f libdsHAL.so ${RDK_PROJECT_ROOT_PATH}/debian/usr/local/lib/
    	cp -f platform.cfg ${RDK_PROJECT_ROOT_PATH}/debian/mnt/nfs/env/
    	cd $DeviceSettings_PATH/install
    	rsync -rplEogDWI --force --exclude=.svn lib ${RDK_PROJECT_ROOT_PATH}/debian/usr/local/
    	rsync -rplEogDWI --force --exclude=.svn bin ${RDK_PROJECT_ROOT_PATH}/debian/usr/local/

    	cd $CURR_DIR
    else

    	if [ -d "lib" ]; then

	      sudo rsync -rplEogDWI --force --exclude=.svn lib ${RDK_FSROOT_PATH}/usr/local/

	fi


	if [ -d "bin" ]; then

      	     sudo rsync -rplEogDWI --force --exclude=.svn bin ${RDK_FSROOT_PATH}/usr/local/

    	fi

    	cd $DeviceSettings_PATH/hal/emu
    	cp -f libdsHAL.so ${RDK_FSROOT_PATH}/usr/local/lib/

        if [ "$BUILD_CONFIG" != "mediaclient" ] && [ "$BUILD_CONFIG" != "headlessgateway" ]; then
    	     #MACRO
    	     mkdir -p ${RDK_PROJECT_ROOT_PATH}/debian/mnt/nfs/env
    	     cp -f libdsHAL.so ${RDK_PROJECT_ROOT_PATH}/debian/usr/local/lib/
    	     cp -f platform.cfg ${RDK_PROJECT_ROOT_PATH}/debian/mnt/nfs/env/
    	     cd $DeviceSettings_PATH/install
    	     rsync -rplEogDWI --force --exclude=.svn lib ${RDK_PROJECT_ROOT_PATH}/debian/usr/local/
    	     rsync -rplEogDWI --force --exclude=.svn bin ${RDK_PROJECT_ROOT_PATH}/debian/usr/local/
	fi

    	cd $CURR_DIR
    fi
}


# run the logic

#these args are what left untouched after parse_args
HIT=false

for i in "$ARGS"; do
    case $i in
        configure)  HIT=true; configure ;;
        clean)      HIT=true; clean ;;
        build)      HIT=true; build ;;
        rebuild)    HIT=true; rebuild ;;
        install)    HIT=true; install ;;
        *)
            #skip unknown
        ;;
    esac
done

# if not HIT do build by default
if ! $HIT; then
  build
fi
