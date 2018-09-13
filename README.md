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

Hit the purple "Browse" buttons to bring up the following dialog:

![Normal file dialog](https://github.com/lllamnyp/BIGParserAndMerger/raw/master/img/normal_file_dialog.png)

and select one or more `.big`-files (or one Woollam data file). If multiple `.big`-files are being selected, it is expected, that they correspond to the same measurement, but for different polarizer azimuths.

Alternatively, you may hit the white "Browse better" button to bring up the improved file selection dialog which uses the `scandir.exe` functionality. `scandir.exe` quickly parses all of the `.big` files in a given folder using much faster C-code to bring up metadata for each `.big`-file:

![Better file dialog](https://github.com/lllamnyp/BIGParserAndMerger/raw/master/img/better_file_dialog.png)

Navigate to the desired folder using the left bar and click on the folder name (not the arrow). This will make `scandir.exe` run, check if the directory has been updated since the last access, cache its contents if that is the case, then load that from the cache and display the contents. Click on the column headings to sort by that column. Click on the filenames to add them to the list of files to load. Click on the appearing filenames in the rightmost bar to remove them from the selection.

![Ready to proceed](https://github.com/lllamnyp/BIGParserAndMerger/raw/master/img/populated.png)

After selecting files for each spectral range you may proceed, or you may also configure the compensator. The radio buttons' functionality is not implemented. Leave all buttons at "None/No Ref.". The compensator may be simulated as a constant offset for Psi and Delta across any one given spectral range. In this case, do not select any files for the compensator. Alternatively, a compensator's spectrum may be loaded from an `.epd`-file, which is basically a three-column data file (wavenumber, psi, delta), or from one or more `.big`-files generated by measuring the compensator in the straight-through configuration. Use the rightmost "Browse" buttons to select files. Afterwards hit "Next >>".

You will be taken to this dialog:

![Calibration](https://github.com/lllamnyp/BIGParserAndMerger/raw/master/img/calibration_parameters.png)

Here the errors in the polarizer and analyzer zeroes can be inputted manually for each FTIR spectral range. Additionally, the "Find P0/A0" buttons can automatically find the best parameters.

The depolarization degree field accepts either a real value in `[0, 1)` or an anonymous function such as

```mathematica
0.01 * (700 - #) / 700 &
```

In this case, the depolarization is calculated as a function of the wavenumber in `cm-1`. The above example would correspond to linearly increasing depolarization from `0` at `700 cm-1` to `0.01` at `0 cm-1`. `#` is standard Mathematica syntax to represent the argument of the function (i.e., the wavenumber).

The second part of this dialog contains the already-described P0/A0 parameters for the compensator, but also an option to "Invert delta" (i.e., does adding a compensator push Delta to higher or lower values). Finally, Delta may or may not be coerced to `[-Pi, 0]`. In a standard measurement it is impossible to determine the sign of Delta, but if it is known, that a compensator is used, it may be deduced, that Delta is positive, rather than negative. If the box is left unchecked, such deductions will be made.

After setting everything up, hit next to load all spectra and display them.

![Adjustment dialog](https://github.com/lllamnyp/BIGParserAndMerger/raw/master/img/adjustment_tab.png)
