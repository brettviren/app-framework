#!/bin/bash

# This script manually generates CCM configuration support code.
# Some or all of it should be incorporated in to CMake.

# NB: There is nothing magic about the locations for the generated
# code and we may certainly change them either to make the CMake
# integration easier or (eg) because we want to install the generated
# code.  This is just a first stab.
#
# HOWEVER: if we adjust the locations then we likely need to adjust
# some parameters, eg in hte *-codegen.jsonnet" we likely need to set
# "structincs" so the generated nljs.hpp file finds the generated
# structs.hpp file.

schemadir="$(dirname $(realpath $BASH_SOURCE))"
topdir="$(dirname $schemadir)"
srcdir="$topdir/src"
incdir="$topdir/include/appfwk"
tstdir="$topdir/test"

pushd $srcdir > /dev/null

render () {
    model="$1" ; shift
    templ="$1" ; shift
    out="$1" ; shift
    cmd="moo -J $schemadir -A schema=schema/avro.jsonnet render -o $out $model $templ"
    echo $cmd
    $cmd || exit -1
}

do_one () {
    local pre="$1"; shift
    local one="$1"; shift
    local dest="$1"; shift
    local ext="$1"; shift
    if [ ! -f $one ] ; then
        echo "no such file: $one" 1>&1
        return
    fi
    for tname in $@
    do
        lname=$(echo $tname | awk '{print tolower($0)}')
        local j2="${schemadir}/${lname}.${ext}.j2"
        local out="${dest}/${pre}${tname}.${ext}"
        rm -f "$out"
        render "$one" "$j2" "$out"
        chmod -w "$out"
    done
}

do_one Cmd "${schemadir}/cmd-codegen.jsonnet" "$incdir" hpp Nljs Structs
do_one App "${schemadir}/app-codegen.jsonnet" "$incdir" hpp Nljs Structs
do_one App "${schemadir}/app-codegen.jsonnet" "$srcdir" cpp CCFSM
do_one Dqm "${schemadir}/dqm-codegen.jsonnet" "$incdir" hpp Nljs Structs
do_one Test "${tstdir}/test-codegen.jsonnet" "$tstdir" hpp Nljs Structs
