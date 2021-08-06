# Fast Free Fermion Compiler: F3C++ [![DOI](https://zenodo.org/badge/392768480.svg)](https://zenodo.org/badge/latestdoi/392768480)

<p align="center"><img src="doc/doxygen/images/logo200x200.png?raw=true" /></p>

F3C++ is an object-oriented, fully templated C++ package for compiling
time-evolution quantum circuits of spin Hamiltonians that can be mapped to free
fermions. F3C++ is build on top of QCLAB++ and provides I/O through openQASM
making it compatible with quantum hardware.


## How to run?

The F3C++ package uses the CMake build system (CMake version ≥ 3.16).
The recommended way of building F3C++ is as follows:

1. Install

        git clone https://github.com/QuantumComputingLab/f3cpp.git

2. CMake

        cd f3cpp
        mkdir release
        cd release
        cmake -DCMAKE_BUILD_TYPE=Release ..
        make -j8

3. Run tests

        ./test/f3c_tests

4. Examples

        ./examples/f3c_time_evolution_XY ../examples/XY.ini
        ./examples/f3c_time_evolution_TFXY ../examples/TFXY.ini
   or

        python3 python/f3c_time_evolution_XY.py ../examples/XY.ini
        python3 python/f3c_time_evolution_TFXY.py ../examples/TFXY.ini

5. Generate documentation

        doxygen doxygen.dox


## References
The F3C compiler is based on:
- An Algebraic Quantum Circuit Compression Algorithm for Hamiltonian Simulation,
  Daan Camps, Efekan K&ouml;ck&uuml;, Lindsay Bassman, Wibe A. de Jong,
  Alexander F. Kemper, and Roel Van Beeumen (2021)
- Algebraic Compression of Quantum Circuits for Hamiltonian Evolution,
  Efekan K&ouml;ck&uuml;, Daan Camps, Lindsay Bassman, J. K. Freericks,
  Wibe A. de Jong, Roel Van Beeumen, and Alexander F. Kemper (2021)


## Developers - Lawrence Berkeley National Laboratory
- [Roel Van Beeumen](http://www.roelvanbeeumen.be/) - rvanbeeumen@lbl.gov
- [Daan Camps](http://campsd.github.io/) - dcamps@lbl.gov


## Funding
The F3C++ project is supported by the Laboratory Directed Research and
Development Program of Lawrence Berkeley National Laboratory under U.S.
Department of Energy Contract No. DE-AC02-05CH11231.


## About
F3C++ Copyright (c) 2021, The Regents of the University of California,
through Lawrence Berkeley National Laboratory (subject to receipt of
any required approvals from the U.S. Dept. of Energy). All rights reserved.

If you have questions about your rights to use or distribute this software,
please contact Berkeley Lab's Intellectual Property Office at
IPO@lbl.gov.

NOTICE.  This Software was developed under funding from the U.S. Department
of Energy and the U.S. Government consequently retains certain rights. As
such, the U.S. Government has been granted for itself and others acting on
its behalf a paid-up, nonexclusive, irrevocable, worldwide license in the
Software to reproduce, distribute copies to the public, prepare derivative
works, and perform publicly and display publicly, and to permit others to do so.
