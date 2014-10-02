

#include "../include/kvesb.h"
#include "kvesb_worker.c"
int main (int argc, char *argv [])
{
    int verbose = (argc > 1 && streq (argv [1], "-v"));
    kvesb_worker_t *session = kvesb_worker_new (
        "tcp://localhost:5556", "channelA", verbose);

    while (1) {
        zmsg_t *reply_to;
        zmsg_t *request = kvesb_worker_recv (session, &reply_to);
        if (request == NULL)
            break;              //  Worker was interrupted
        //  Echo message
        kvesb_worker_send (session, &request, reply_to);
        zmsg_destroy (&reply_to);
    }
    kvesb_worker_destroy (&session);
    return 0;
}
