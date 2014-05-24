#!/bin/bash

SCRIPT=$(readlink -f "$0")
SCRIPTS_DIR=`dirname "$SCRIPT"`
export BUILDS_DIR=$SCRIPTS_DIR/../
export COMBINED_DIR=$SCRIPTS_DIR/..

buildReport=$BUILDS_DIR/../Logs/buildDeviceSettReport.txt


    echo "Setting hal Environment variables..."
#    source $PWD/hal/src/halenv.sh
    echo "Building Device Setting libraries..."

make all >> $buildReport 2>> $buildReport
if [ $? -ne 0 ] ; then
  echo "DeviceSettings Build Failed..."
  exit 1
else
  echo "DeviceSettings Build Success.."
  exit 0
fi

