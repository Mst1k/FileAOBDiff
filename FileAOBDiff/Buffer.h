#pragma once

struct Buffer {
    unsigned char* mBuff;
    size_t mSize;

    Buffer();
    ~Buffer();
};