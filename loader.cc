#include <bfd.h>
#include "loader.h"

int load_binary(std::string &fname, Binary* bin, Binary::BinaryType type) {
    return load_binary_bfd(fname, bin, type);
}
