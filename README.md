# FEUP-AED

Weekly exercises from the AED course unit at FEUP.

Exercise descriptions provided in portuguese (adapted from the given PDFs).\
Unit tests provided.

## Building and Running

This project uses [cmake](https://cmake.org/) and [googletest](https://github.com/google/googletest).

Assuming cmake is installed and properly setup:

1. Run `git submodule init && git submodule update` to download googletest.
2. Run `cmake -S . -B build` in this project's directory to generate the build system.
3. Run `cmake --build build` to actually build the project.

This will generate a bunch of binaries in the `build` directory. One for each directory with the name format `TP*`. Simply run one of these executables.

## Unit info

* **Name**: Algoritmos e Estruturas de Dados (Algorithms and Data Structures)
* **Date**: Year 2, Semester 1, 2021/22
* **See also**: [feup-aed-mooshak](https://github.com/ttoino/feup-aed-mooshak), [feup-aed-proj1](https://github.com/ttoino/feup-aed-proj1), [feup-aed-proj2](https://github.com/ttoino/feup-aed-proj2)
* [**More info**](https://sigarra.up.pt/feup/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=484404)

## Disclaimer

This repository (and all others with the name format `feup-*`) are for archival and educational purposes only.

If you don't understand some part of the code or anything else in this repo, feel free to ask (although I may not understand it myself anymore).

Keep in mind that this repo is public. If you copy any code and use it in your school projects you may be flagged for plagiarism by automated tools.
