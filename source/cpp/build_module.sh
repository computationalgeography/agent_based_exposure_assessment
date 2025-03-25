#!/usr/bin/env bash
set -e


mkdir -p build
cd build

PKG_CONFIG_PATH=../../osrm_shared/lib/pkgconfig/ cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/tmp/routing

cmake --build . --config Release --target all

cmake --build . --config Release --target install
