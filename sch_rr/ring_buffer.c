/* Copyright (c) 2023 Cisco and/or its affiliates.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "ring_buffer.h"

void init_ring_buffer (ring_buffer *buf) {
    buf->begin = 0;
    buf->end = 0;
    buf->size = QUEUE_SIZE;
    buf->count = 0;
    buf->is_init = true;
}

void ring_buffer_push(ring_buffer *buf, u32 data) {
    if (buf->count < buf->size) {
        buf->buffer[buf->end] = data;
        buf->end = (buf->end+1)%buf->size;
        buf->count++;
    }
}

u32 ring_buffer_pop(ring_buffer *buf) {
    if (buf->count > 0) {
        int begin_temp = buf->begin;
        buf->begin = (buf->begin+1)%buf->size;
        buf->count--;
        return buf->buffer[begin_temp];
    }
    return ~0;
}