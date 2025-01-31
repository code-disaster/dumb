/*  _______         ____    __         ___    ___
 * \    _  \       \    /  \  /       \   \  /   /       '   '  '
 *  |  | \  \       |  |    ||         |   \/   |         .      .
 *  |  |  |  |      |  |    ||         ||\  /|  |
 *  |  |  |  |      |  |    ||         || \/ |  |         '  '  '
 *  |  |  |  |      |  |    ||         ||    |  |         .      .
 *  |  |_/  /        \  \__//          ||    |  |
 * /_______/ynamic    \____/niversal  /__\  /____\usic   /|  .  . ibliotheque
 *                                                      /  \
 *                                                     / .  \
 * readduh.c - Code to read a DUH from an open        / / \  \
 *             file.                                 | <  /   \_
 *                                                   |  \/ /\   /
 * By entheh.                                         \_  /  > /
 *                                                      | \ / /
 *                                                      |  ' /
 *                                                       \__/
 */

#include <stdlib.h>

#include "dumb.h"
#include "internal/dumb.h"

static DUH_SIGNAL *read_signal(DUH *duh, DUMBFILE *f) {
    DUH_SIGNAL *signal;
    long type;

    signal = dumb_malloc(sizeof(*signal));

    if (!signal)
        return NULL;

    type = dumbfile_mgetl(f);
    if (dumbfile_error(f)) {
        dumb_free(signal);
        return NULL;
    }

    signal->desc = _dumb_get_sigtype_desc(type);
    if (!signal->desc) {
        dumb_free(signal);
        return NULL;
    }

    if (signal->desc->load_sigdata) {
        signal->sigdata = (*signal->desc->load_sigdata)(duh, f);
        if (!signal->sigdata) {
            dumb_free(signal);
            return NULL;
        }
    } else
        signal->sigdata = NULL;

    return signal;
}

/* read_duh(): reads a DUH from an already open DUMBFILE, and returns its
 * pointer, or null on error. The file is not closed.
 */
DUH *read_duh(DUMBFILE *f) {
    DUH *duh;
    int i;

    if (dumbfile_mgetl(f) != DUH_SIGNATURE)
        return NULL;

    duh = dumb_malloc(sizeof(*duh));
    if (!duh)
        return NULL;

    duh->length = dumbfile_igetl(f);
    if (dumbfile_error(f) || duh->length <= 0) {
        dumb_free(duh);
        return NULL;
    }

    duh->n_signals = (int)dumbfile_igetl(f);
    if (dumbfile_error(f) || duh->n_signals <= 0) {
        dumb_free(duh);
        return NULL;
    }

    duh->signal = dumb_malloc(sizeof(*duh->signal) * duh->n_signals);
    if (!duh->signal) {
        dumb_free(duh);
        return NULL;
    }

    for (i = 0; i < duh->n_signals; i++)
        duh->signal[i] = NULL;

    for (i = 0; i < duh->n_signals; i++) {
        if (!(duh->signal[i] = read_signal(duh, f))) {
            unload_duh(duh);
            return NULL;
        }
    }

    return duh;
}
