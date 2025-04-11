# OpenStreetMap preprocessing 

This folder contains build and utiltiy scripts to download OpenStreetMap data, build the OSRM routing engine, and preprocess the OpenStreetMap files for routing.
The build was tailored for the OSRM version 5.27.1 using a Conda environment to build and run the exposure assessment [case study](https://github.com/computationalgeography/paper_agent_based_exposure_assessment).

> [!NOTE]
> The build scripts are mainly obsolete, build the routing engine from the main repository.

## How to build

### Build environment

Create a Conda environment from `environment/development.yaml` file and activate.

### OSRM

The utility script to build the [Open Source Routing Machine](https://github.com/Project-OSRM/osrm-backend) engine version 5.27.1.
Run `build_osrm_shared.sh` to download and build.


### OpenStreetMap data

Utility scripts to preprocess routing data.
Run `download_pbf.sh` to download Swiss and Dutch OpenStreetMap datasets, and then `create_routing_data.sh` to prepare routing for different profiles.
