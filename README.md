# BIGParserAndMerger

MMA Package for ellipsometry data import

## Installation

Simply extract this repository to a separate folder and run `install.bat`. Correct operation requires that the working directory matches the location of the script. If for some reason this is not the case on your machine, open a terminal (`Win + R`, `cmd`), navigate to the install script (`cd /path/to/install/bat/`) and run the script from the command line.

Alternatively, you may download and run only 'install_from_hub.bat' which automatically (at the time of writing, 07.08.2018) downloads the latest files from GitHub.

**Both scripts will overwrite any existing installation!**

### Installing on non-Windows systems

**OPTIONAL:** The directory parser functionality (which is written in C and compiled for Win7x64) will not work. The source code for `scandir.exe` is available in the package and should not be difficult to modify. The `Run` commands inside the package file (`BIGParserAndMerger.m`) are likewise written with Windows filesystems in mind. The rest of the package is, to the best of my knowledge, platform-independent.

On Windows the necessary package files (`init.m`, `BIGParserAndMerger.m`, and `scandir.exe`) are placed into `%appdata%\Mathematica\Applications\BIGParserAndMerge\`. For a different OS consult the Mathematica documentation for the appropriate place to place user packages.

## Running

Open Mathematica (v10 required) and run

    << BIGParserAndMerger`
    
The package will take some time to load as many functions are being compiled to C. If a C compiler is not present on the system, warning messages will be issued and the kernel will revert to using the Wolfram Virtual Machine. This causes a slight hit to the performance, but nothing more serious.

### Running without installation

It is sufficient to download just 'BIGParserAndMerger.m' and execute

    Get["/path/to/BIGParserAndMerger.m"]
    
The `scandir` functionality, if it has also been placed in the same location, may or may not suffer (untested).

### Running without download

    Get["https://raw.githubusercontent.com/lllamnyp/BIGParserAndMerger/master/BIGParserAndMerger.m"]
    
Should also work. `scandir` functionality will certainly not work.

## Usage

After loading the package into memory by one of the methods from the previous section, run

    MergingInterface[]

The following window shall appear
