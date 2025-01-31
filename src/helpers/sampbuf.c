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
 * sampbuf.c - Helper for allocating sample           / / \  \
 *             buffers.                              | <  /   \_
 *                                                   |  \/ /\   /
 * By entheh.                                         \_  /  > /
 *                                                      | \ / /
 *                                                      |  ' /
 *                                                       \__/
 */

#include <stdlib.h>
#include "dumb.h"

sample_t **allocate_sample_buffer(int n_channels, long length) {
    int i;
    sample_t **samples = dumb_malloc(((n_channels + 1) >> 1) * sizeof(*samples));
    if (!samples)
        return NULL;
    samples[0] = dumb_malloc(n_channels * length * sizeof(*samples[0]));
    if (!samples[0]) {
        dumb_free(samples);
        return NULL;
    }
    for (i = 1; i<(n_channels + 1)>> 1; i++)
        samples[i] = samples[i - 1] + length * 2;
    return samples;
}

void destroy_sample_buffer(sample_t **samples) {
    if (samples) {
        dumb_free(samples[0]);
        dumb_free(samples);
    }
}
