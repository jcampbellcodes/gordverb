# gordverb

Simple free open-source reverb. Meant to be used to swap out early/late
reflection algorithms and compare them in performance and sound quality.

Params:
- Wet/Dry
- Reverb amount
- Enable early reflections
- Enable late reflections

Code is structured in such a way that early and late reflections algorithms can be swapped
out easily at compile time.

# How to Clone

The submodules included in the repo are needed to build.

To clone with repo along with its submodules using SSH:
```
git clone --recurse-submodules git@github.com:jcampbellcodes/gordverb.git
```

# How to build

We use CMake as the build system for this project. In order to configure and build
to a directory called `build` (which will be ignored by git), do this:

```
cd /to/gordverb/root
cmake -B build
cmake --build build
```

To generate an IDE project, for example Xcode, do this:

```
cd /to/gordverb/root
cmake -B build -G Xcode
```

and open the IDE project from the build directory at the root of the repo.

# Tests

There is a Catch2 unit test suite under the `tests` subdir. These can be run with CTest.

# Dependencies
 - clang-format
   - used for formatting source code. see `.clang-format` file in repo.
 - git-lfs
    - git lfs is needed to pull down large IR content without bloating the repo
 - catch2
   - used for unit tests
 - daisysp
   - used for additional FX algos
 - juce
   - used for plugin wrapping and gui

# TODO:
- Add more IRs
- Add more controls
- Add custom GUI
- Support MISO
- Add new reverb type (support larger sample rates)

# Attribution

IRs included with convolution portion are from the OpenAIR database.

Creative Commons Attribution 4.0 License

The Dixon Studio Theatre – University of York
https://www.openair.hosted.york.ac.uk/?page_id=452
www.openairlib.net
Ben Lavin
Darren Robinson
Ya-Hsin Chou
University of York
