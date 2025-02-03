#!/usr/bin/env bash
set -e

NR_THREADS=16
VERBOSE="WARNING"

cd data

for country in nl ch
do
  for profile in car bicycle foot train
  do
    ../osrm/bin/osrm-extract --verbosity ${VERBOSE} --threads ${NR_THREADS} --profile ../profiles/${profile}.lua ${country}_${profile}.osm.pbf
    ../osrm/bin/osrm-partition --verbosity ${VERBOSE} --threads ${NR_THREADS} ${country}_${profile}.osrm
    ../osrm/bin/osrm-customize --verbosity ${VERBOSE} --threads ${NR_THREADS} ${country}_${profile}.osrm
    ../osrm/bin/osrm-contract --verbosity ${VERBOSE} --threads ${NR_THREADS} ${country}_${profile}.osrm
  done
done
