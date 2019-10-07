#!/bin/bash
set -ex

image=$1

if [[ $image =~ ^centos:7 ]]
then
    pkgcmd="yum"
    builddep="yum-builddep"
    sed -i '/^tsflags=/d' /etc/yum.conf
    yum install -y epel-release
    yum install -y @buildsys-build
    yum install -y yum-utils
    yum install -y yum-plugin-copr
    yum install -y git
    yum copr enable -y simc/stable
elif [[ $image =~ ^centos:8 ]]
then
    pkgcmd="dnf"
    builddep="dnf builddep"
    sed -i '/^tsflags=/d' /etc/dnf/dnf.conf
    dnf install -q -y epel-release
    dnf install -q -y 'dnf-command(config-manager)'
    dnf config-manager --set-enabled PowerTools
    dnf groupinstall -q -y "Development Tools"
    dnf install -q -y 'dnf-command(builddep)'
    dnf install -q -y git
    dnf install -q -y rpmdevtools
    dnf copr enable -y simc/stable
elif [[ $image =~ ^fedora: ]]
then
    pkgcmd="dnf"
    builddep="dnf builddep"
    sed -i '/^tsflags=/d' /etc/dnf/dnf.conf
    dnf install --allowerasing -y @buildsys-build
    dnf install -y 'dnf-command(builddep)'
    dnf install -y git
    dnf copr enable -y simc/stable
fi

$builddep -y fedora/SPECS/radarlib.spec

if [[ $image =~ ^fedora: || $image =~ ^centos: ]]
then
    pkgname=radarlib-"$(rpmspec -q --qf="%{version}-%{release}\n" fedora/SPECS/radarlib.spec | head -n1)"
    mkdir -p ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
    cp fedora/SPECS/radarlib.spec ~/rpmbuild/SPECS/radarlib.spec
    git archive --prefix=$pkgname/ --format=tar HEAD | gzip -c > ~/rpmbuild/SOURCES/$pkgname.tar.gz
    rpmbuild -ba ~/rpmbuild/SPECS/radarlib.spec
    find ~/rpmbuild/{RPMS,SRPMS}/ -name "${pkgname}*rpm" -exec cp -v {} . \;
    # TODO upload ${pkgname}*.rpm to github release on deploy stage
else
    autoreconf -ifv
    ./configure
    make check
fi
