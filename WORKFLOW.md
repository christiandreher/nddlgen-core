# NDDL generation workflow
This file describes the workflow of both model NDDL creation and initial state NDDL creation.
Let `c` be an instance of `nddlgen::Controller` initialized with a valid `nddlgen::utilities::ControllerConfig`.

## Model creation using SDF

### Parse SDF input file
`c->parseSdfInputFile()`  
The SDF input file is checked for physical existence, readability, validity. If everything is okay,
the contents of the file are parsed.

### Building domain description
`c->buildDomainDescription()`  
Builds a domain description model with the contents of the SDF input file.

### Write NDDL model file
`c->writeNddlModelFile()`  
Uses the domain description model to generate a NDDL model and writes it to a file.

## Initial state creation using SDF and ISD

### Parse SDF input file
`c->parseSdfInputFile()`  
The SDF input file is checked for physical existence, readability, validity. If everything is okay,
the contents of the file are parsed.

### Parse ISD input file
`c->parseIsdInputFile()`  
Same procedure as SDF input file parsing. This step requires, that the SDF input file was already parsed.

### Building domain description
`c->buildDomainDescription()`  
Builds a domain description model with the contents of the SDF and ISD input file.

### Write NDDL initial state file
`c->writeNddlInitialStateFile()`  
Uses the domain description model to generate a NDDL initial state and writes it to a file.

## Model and initial state creation using SDF and ISD

### Parse SDF input file
`c->parseSdfInputFile()`  
The SDF input file is checked for physical existence, readability, validity. If everything is okay,
the contents of the file are parsed.

### Parse ISD input file
`c->parseIsdInputFile()`  
Same procedure as SDF input file parsing. This step requires, that the SDF input file was already parsed.

### Building domain description
`c->buildDomainDescription()`  
Builds a domain description model with the contents of the SDF and ISD input file.

### Write NDDL model file
`c->writeNddlModelFile()`  
Uses the domain description model to generate a NDDL model and writes it to a file.

### Write NDDL initial state file
`c->writeNddlInitialStateFile()`  
Uses the domain description model to generate a NDDL initial state and writes it to a file.
