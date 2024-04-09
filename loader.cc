#include <bfd.h>
#include <string>
#include <iostream>
#include "loader.h"

static int load_symbols_bfd(bfd* bfd_h, Binary* bin) {
    asymbol** bfd_symtab = NULL;
    long ret;

    long n = bfd_get_symtab_upper_bound(bfd_h);
    if (n < 0) {
        fprintf(stderr, "failed to read symtab (%s)\n",
        bfd_errmsg(bfd_get_error()));
        goto fail;
    } else if (n) {
        bfd_symtab = (asymbol**)malloc(n);
        if(!bfd_symtab) {
            fprintf(stderr, "out of memory\n");
            goto fail;
        }

        long nsyms = bfd_canonicalize_symtab(bfd_h, bfd_symtab);

        if(nsyms < 0) {
            fprintf(stderr, "failed to read symtab (%s)\n",
            bfd_errmsg(bfd_get_error()));
            goto fail;
        }

        Symbol* sym;
        for(int i = 0; i < nsyms; i++) {
            if(bfd_symtab[i]->flags & BSF_FUNCTION) {
                bin->symbols.push_back(Symbol());
                sym = &bin->symbols.back();
                sym->type = Symbol::SYM_TYPE_FUNC;
                sym->name = std::string(bfd_symtab[i]->name);
                sym->addr = bfd_asymbol_value(bfd_symtab[i]);
            }
        }
    }

    ret = 0;
    goto cleanup;

fail:
    ret = -1;

cleanup:
    if (bfd_symtab) free(bfd_symtab);

    return ret;
}

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
