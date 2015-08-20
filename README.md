# nddl-generator-core

## General

This package is the core of the nddl-generator. It is compiled as a shared library and should then be included in the corresponding application (for example nddl-generator-cli, nddl-generator-gui or nddl-generator-core-test)

## Dependencies

### Build Artifact
 * Artifact type: *Shared library*
 * Artifact name: *nddl-generator-core*
 * Artifact extention: *so*
 * Output prefix: *lib*

### Compiler

#### Include paths (-l)
 * *path to sdformat-2.3*
 * *path to nddl-generator-core src directory*

#### Include files (-include)
 * *none*

#### Miscellaneous
 * Other flags: *-c -fmessage-length=0 -std=c++0x -fPIC*

## License

Copyright 2015 Christian Dreher (dreher@charlydelta.org)  
  
Licensed under the Apache License, Version 2.0 (the "License");  
you may not use this file except in compliance with the License.  
You may obtain a copy of the License at  
  
	http://www.apache.org/licenses/LICENSE-2.0  
  
Unless required by applicable law or agreed to in writing, software  
distributed under the License is distributed on an "AS IS" BASIS,  
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
See the License for the specific language governing permissions and  
limitations under the License.  
