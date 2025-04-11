## Agent-based exposure assessment

This repository contains building blocks for agent-based exposure assessment.
An application example is given in the [case study](https://github.com/computationalgeography/paper_agent_based_exposure_assessment) repository.

Please note that currently no installable package is available, and Linux is the only supported platform.
You can raise issues or feature requests, or contact [Oliver Schmitz](mailto:o.schmitz@uu.nl) if you have questions or need support in applying the framework.
Linux user can build the sources from the repository, other operating systems would require additional support.



### Building from source 

The instructions are tailored to Debian-based systems.
Note that a build of the project currently requires the Clang compiler.
Install the required dependencies:

```bash
apt install clang-18 ninja-build clang-18cmake liblua5.4-dev libboost-all-dev libtbb-dev nanobind-dev libbz2-dev python3-sphinx python3-pandas
```

Configure the project, e.g. with

```bash
cmake \
  -G "Ninja" \
  -D CMAKE_C_COMPILER=clang-18 \
  -D CMAKE_CXX_COMPILER=clang++-18 \
  -S paper_agent_based_exposure_assessment \
  -B /tmp/build
```

and compile

```bash
cmake --build /tmp/build --target all
```
