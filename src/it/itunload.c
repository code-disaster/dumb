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
 * itunload.c - Code to free an Impulse Tracker       / / \  \
 *              module from memory.                  | <  /   \_
 *                                                   |  \/ /\   /
 * By entheh.                                         \_  /  > /
 *                                                      | \ / /
 *                                                      |  ' /
 *                                                       \__/
 */

#include <stdlib.h>

#include "dumb.h"
#include "internal/it.h"

void _dumb_it_unload_sigdata(sigdata_t *vsigdata) {
    if (vsigdata) {
        DUMB_IT_SIGDATA *sigdata = vsigdata;
        int n;

        if (sigdata->song_message)
            dumb_free(sigdata->song_message);

        if (sigdata->order)
            dumb_free(sigdata->order);

        if (sigdata->instrument)
            dumb_free(sigdata->instrument);

        if (sigdata->sample) {
            for (n = 0; n < sigdata->n_samples; n++)
                if (sigdata->sample[n].data)
                    dumb_free(sigdata->sample[n].data);

            dumb_free(sigdata->sample);
        }

        if (sigdata->pattern) {
            for (n = 0; n < sigdata->n_patterns; n++)
                if (sigdata->pattern[n].entry)
                    dumb_free(sigdata->pattern[n].entry);
            dumb_free(sigdata->pattern);
        }

        if (sigdata->midi)
            dumb_free(sigdata->midi);

        {
            IT_CHECKPOINT *checkpoint = sigdata->checkpoint;
            while (checkpoint) {
                IT_CHECKPOINT *next = checkpoint->next;
                _dumb_it_end_sigrenderer(checkpoint->sigrenderer);
                dumb_free(checkpoint);
                checkpoint = next;
            }
        }

        dumb_free(vsigdata);
    }
}
