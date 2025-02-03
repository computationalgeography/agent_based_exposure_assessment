#!/usr/bin/env bash
set -e

version="5.27.1"

OSRM="v${version}.tar.gz"


if [ ! -e "$OSRM" ]
then
    wget https://github.com/Project-OSRM/osrm-backend/archive/${OSRM}
    tar -xzf ${OSRM}
fi


mkdir -p build_shared
cd build_shared

# Override optimisation flag for gcc-12 (https://github.com/Project-OSRM/osrm-backend/issues/6349)
cmake ../osrm-backend-${version} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS_RELEASE="-O2 -DNDEBUG" -DCMAKE_PREFIX_PATH=${CONDA_PREFIX}

cmake --build . --config Release --target all --parallel 2

cmake --build . --config Release --target install
