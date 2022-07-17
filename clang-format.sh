#!/bin/bash

# run all h, c, hpp, and cpp files that are checked in under the format defined in .clang-format

dnbs=$(dirname "${BASH_SOURCE[0]}")
thisdir=$(cd "$dnbs" && pwd)
cd "${thisdir}" && clang-format -style=file -fallback-style=none -i $(git ls-files "*.[ch]" "*.[hc]pp" | tr '\r\n' ' ')