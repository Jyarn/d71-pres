#pragma once
struct trc_time_struct {
    long start;
};

void trc_init(struct trc_time_struct*);
void trc_tock(struct trc_time_struct*);
