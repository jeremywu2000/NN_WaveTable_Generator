# NN_WaveTable_Generator

## Compiling wavae_daisy

If this is the first time building the project and have not compiled the libraries make sure to follow the next subsection.
Alternaitvely, you may execute the `build_all` task in the wavae_daisy directory through VS code.

To build wavae_daisy simply run the command `make` in it's directory.

To bootload the generated binary files to the Daisy patch sm run the command `make program-dfu`.

The build can also be cleared with the command `make clean`.

Alternatively, VS code tasks are available to perform the above.

### Compiling Libraries

Once you have the repository and the submodules (libDaisy/DaisySP) properly cloned, and the toolchain installed (for details see the [Daisy Wiki](https://github.com/electro-smith/DaisyWiki/wiki) for platform specific instructions) it's time to build the libraries.

To build both libraries at once simply run:

`./build_libs.sh`

This is the same as going to each library's directory and running `make`.

This may take a few minutes depending on your computer's hardware. But should have the following output when finished:

```sh
$ ./build_libs.sh 
building libDaisy . . .
rm -fR build
arm-none-eabi-ar: creating build/libdaisy.a
done.
building DaisySP . . .
rm -fR build
done.
```

## Updating the submodules

To pull everything for the repo and submodules:

```sh
git pull --recurse-submodules
```

to only pull changes for the submodules:

```sh
git submodule update --remote
```

Alternatively, you can simply run git commands from within the submodule and they will be treated as if you were in that repository instead of Daisy_Examples

Whenenever there are changes to the libraries (whether from pulling from git or manually editing the libraries) they will need to be rebuilt. This can be done by either running `./build_libs.sh` or entering the directory of the library with changes and running `make`.
