#define PACKAGE "loader"
#define PACKAGE_VERSION "1.2.3"

// GNU binutils 2.42

#include <bfd.h>
#include <string>
#include <iostream>
#include "loader.h"

static bfd* open_bfd(std::string &fname) {
    static int bfd_inited = 0;

    if (!bfd_inited) {
        bfd_init();
        bfd_inited = 1;
    }

    bfd* bfd_h = bfd_openr(fname.c_str(), NULL);
    if (!bfd_h) {
        fprintf(stderr,
                "failed to open binary '%s' (%s)\n",
                fname.c_str(), bfd_errmsg(bfd_get_error()));
        return NULL;
    }

    if (!bfd_check_format(bfd_h, bfd_object)) {
        fprintf(stderr, "file '%s' does not look like an executable (%s)\n",
            fname.c_str(), bfd_errmsg(bfd_get_error()));
        return NULL;
    }

    bfd_set_error(bfd_error_no_error);


    if (bfd_get_flavour(bfd_h) == bfd_target_unknown_flavour) {
        fprintf(stderr, "unrecognized format for binary '%s' (%s)\n",
            fname.c_str(), bfd_errmsg(bfd_get_error()));
        return NULL;
    }

    return bfd_h;
}

static int load_binary_bfd(const std::string &fname, Binary* bin,
    Binary::BinaryType type) {

    return 0;
}

int
load_binary(const std::string &fname, Binary* bin,
    Binary::BinaryType type) {

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
    std::string fname = "loader";
    bfd* p = open_bfd(fname);

    std::cout << p << std::endl;
    return 0;
}
