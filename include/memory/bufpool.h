#ifndef BUFPOOL_H
#define BUFPOOL_H

#include "bufmgr.h"

/* Create the Buffer Pool. */
void CreateBufferPool();

/* Get Block*/
void *GetBufferBlock(Buffer buffer);


/* Read Buffer Block. */
void BufferReadBlock(BufferTag *tag, Buffer buffer);


/* Write Buffer Block. */
void BufferWriteBlock(Buffer buffer);

#endif
