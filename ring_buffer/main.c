#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define dbg(fmt, msg)\
    printf("[%s: %d %s()]: ", __FILE__, __LINE__, __FUNCTION__);\
    printf(fmt, msg);\
    printf("\n");

enum {
    RING_BUFFER_DATA_SIZE = 5,
};

typedef struct {
    int val;
} Data;

typedef struct RingBuffer {
    Data data[RING_BUFFER_DATA_SIZE];
    int capacity;
    int last_insert;
    int next_read;
} RingBuffer;

RingBuffer *rb_init(void)
{
    RingBuffer *rb = (RingBuffer *)malloc(sizeof(RingBuffer));
    assert(rb != NULL && "ERROR: malloc failed");

    int no_insert = -1;
    rb->capacity = RING_BUFFER_DATA_SIZE;
    rb->last_insert = no_insert;
    rb->next_read = 0;
    dbg("%s", "");
    return rb;
}

void print(RingBuffer *rb)
{
    dbg("%s", "rb values:");
    for (int i = 0; i < rb->capacity; ++i) {
        dbg("%d", rb->data[i].val);
    }
    dbg("%s", "---");
}

void put(RingBuffer *rb, Data *data)
{
    rb->last_insert = (rb->last_insert + 1) % rb->capacity;
    rb->data[rb->last_insert] = *data;
    rb->next_read = rb->next_read;
    dbg("%s", "");
}

Data get(RingBuffer *rb)
{
    rb->next_read = (rb->next_read) % rb->capacity;
    Data data = rb->data[rb->next_read];
    rb->next_read += 1;
    dbg("%s", "");
    return data;
}

int main(void)
{
    dbg("%s", "");
    RingBuffer *rb = rb_init();
    Data d1 = { 11 };
    put(rb, &d1);
    print(rb);
    Data d2 = { 22 };
    put(rb, &d2);
    print(rb);
    Data d3 = { 33 };
    put(rb, &d3);
    print(rb);
    Data d4 = { 44 };
    put(rb, &d4);
    print(rb);
    Data d5 = { 55 };
    put(rb, &d5);
    print(rb);
    Data d6 = { 66 };
    put(rb, &d6);
    print(rb);

    Data g1 = get(rb);
    print(rb);
    printf("val: %d\n", g1.val);
    Data g2 = get(rb);
    printf("val: %d\n", g2.val);
    print(rb);

    Data d7 = { 77 };
    put(rb, &d7);
    print(rb);
    return 0;
}
