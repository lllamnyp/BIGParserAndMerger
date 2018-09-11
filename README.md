# BIGParserAndMerger

MMA Package for ellipsometry data import

## Installation

Simply extract this repository to a separate folder and run `install.bat`. Correct operation requires that the working directory matches the location of the script. If for some reason this is not the case on your machine, open a terminal (`Win + R`, `cmd`), navigate to the install script (`cd /path/to/install/bat/`) and run the script from the command line.

Alternatively, you may download and run only `install_from_hub.bat` which automatically (at the time of writing, 07.08.2018) downloads the latest files from GitHub.

**Both scripts will overwrite any existing installation!**

### Installing on non-Windows systems

**OPTIONAL:** The directory parser functionality (which is written in C and compiled for Win7x64) will not work. The source code for `scandir.exe` is available in the package and should not be difficult to modify. The `Run` commands inside the package file (`BIGParserAndMerger.m`) are likewise written with Windows filesystems in mind. The rest of the package is, to the best of my knowledge, platform-independent.

On Windows the necessary package files (`init.m`, `BIGParserAndMerger.m`, and `scandir.exe`) are placed into `%appdata%\Mathematica\Applications\BIGParserAndMerge\`. For a different OS consult the Mathematica documentation for the appropriate place to place user packages.

## Running

Open Mathematica (v10 required) and run

```mathematica
<< BIGParserAndMerger`
```

The package will take some time to load as many functions are being compiled to C. If a C compiler is not present on the system, warning messages will be issued and the kernel will revert to using the Wolfram Virtual Machine. This causes a slight hit to the performance, but nothing more serious.

### Running without installation

It is sufficient to download just 'BIGParserAndMerger.m' and execute

```mathematica
Get["/path/to/BIGParserAndMerger.m"]
```

The `scandir` functionality, if it has also been placed in the same location, may or may not suffer (untested).

### Running without download

```mathematica
Get["https://raw.githubusercontent.com/lllamnyp/BIGParserAndMerger/master/BIGParserAndMerger.m"]
```

Should also work. `scandir` functionality will certainly not work.

## Usage

After loading the package into memory by one of the methods from the previous section, run

```mathematica
MergingInterface[]
```

### Range selection

The following window shall appear

![Range selection](https://github.com/lllamnyp/BIGParserAndMerger/raw/master/img/range_select.png)

The program was designed with the two types of experimental setups in mind: the infrared Fourier-transform ellipsometers and the near-IR to deep-UV Woolam ellipsometer. Each setup can operate in several spectral ranges. Here you must select the appropriate number of ranges (sets of measurements) to use.

For example, you have a measurement in the far-IR range, a measurement in the mid-IR range with a compensator that works well in the lower end of the mid-IR spectrum, a measurement in the mid-IR range without a compensator that works well in the higher end of the spectrum, and, finally, a measurement in the near-IR range. All are done on the Fourier-transform ellipsometers. That gives **4** FTIR .big file ranges.

On top of that you may have also performed measurements on the Woolam setup, say one with the `0.5 -- 4.0 eV` optical fiber, and another with the `0.75 -- 6.5 eV` optical fiber. This gives **2** Woolam ranges.

After setting the sliders to the appropriate positions, you may hit "Next" to specify the data files.

![File selection](https://github.com/lllamnyp/BIGParserAndMerger/raw/master/img/file_select.png)
