# nddl-generator-core

## General

This package is the core of the nddl-generator. It is compiled as a static library and should then be included in the corresponding application (for example nddl-generator-cli, nddl-generator-gui or nddl-generator-core-test)

## Dependencies

Compiling a project with nddl-generator-core needs a linking against following libraries:
 * boost_system (part of libboost-all-dev)
 * boost_filesystem (part of libboost-all-dev)
 * sdfformat (part of libsdfformat2-dev)

## Include Paths (-l)

Following include paths need to be set for the compiler
 * /usr/include/sdformat-2.3

## License

Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.