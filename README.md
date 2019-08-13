# Machine Loader
Simple application for utilizing memory and CPU with the purpose of testing environments that should share multiple applications

# Usage
```
load [--kb|--mb|--gb <memory to use>] [--cpu <cpu percentage to use>]
```
Note that the cpu percentage must be a value between 0.0 and 1.0

# Building
Run this command in the root of the project:
```
make
```
The build binary will be located inside the _./release_ folder
