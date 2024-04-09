#define PACKAGE "loader"
#define PACKAGE_VERSION "1.2.3"

// GNU binutils 2.42

#include <bfd.h>
#include "loader.h"

static int load_binary_bfd(const std::string &fname, Binary* bin, Binary::BinaryType type) {
    return 0;
}

int load_binary(const std::string &fname, Binary* bin, Binary::BinaryType type) {
    return load_binary_bfd(fname, bin, type);
}

void unload_binary(Binary* bin) {
    Section* sec;

    for (size_t i = 0; i < bin->sections.size(); i++) {
        sec = &bin->sections[i];

        if (sec->bytes) {
            free(sec->bytes);
        }

    }
}

int main() {
    int (*fp) (const std::string&, Binary*, Binary::BinaryType) = load_binary;
    printf("%p\n", fp);
    return 0;
}
