# wavae_daisy

## Author

Alexandra Gafencu (alexandra.gafencu@mail.mcgill.ca)
Simon Nakane Marcil (simon.nakanemarcil@mail.mcgill.ca)
Jeremy Wu (jeremy.wu@mail.mcgill.ca)

## Description

Neural network wavetable generator

## Compiling wavae_daisy

If this is the first time building the project and have not compiled the libraries make sure to do so.
You can do so by running the task `build_all` in VS code.

To build wavae_daisy simply run the command `make` in it's directory.

To bootload the generated binary files to the Daisy patch sm run the command `make program-dfu`.

The build can also be cleared with the command `make clean`.

Alternatively, VS code tasks are available to perform the above.