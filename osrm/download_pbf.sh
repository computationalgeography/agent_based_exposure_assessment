#!/usr/bin/env bash
set -e


mkdir -p data
cd data

today=`date +"%Y-%m-%d"`
fname="netherlands-latest-${today}.osm.pbf"

wget -O ${fname} https://download.geofabrik.de/europe/netherlands-latest.osm.pbf

ln -s ${fname} nl_car.osm.pbf
ln -s ${fname} nl_bicycle.osm.pbf
ln -s ${fname} nl_foot.osm.pbf
ln -s ${fname} nl_train.osm.pbf

fname="switzerland-latest-${today}.osm.pbf"

wget -O ${fname} https://download.geofabrik.de/europe/switzerland-latest.osm.pbf

ln -s ${fname} ch_car.osm.pbf
ln -s ${fname} ch_bicycle.osm.pbf
ln -s ${fname} ch_foot.osm.pbf
ln -s ${fname} ch_train.osm.pbf
