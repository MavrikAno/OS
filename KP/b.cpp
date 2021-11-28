#include <iostream>
#include <string>
#include <cstring>
#include "zmq.h"

using namespace std;

int ReceiveMessage(void *socket) {
    size_t result = 0;
    zmq_msg_t reply;
    zmq_msg_init(&reply);
    zmq_msg_recv(&reply, socket, 0);
    char* ptr = static_cast<char*>(zmq_msg_data(&reply));
    result = atoi(ptr);
    return result;
}

int main() {
    void *context_a = zmq_ctx_new();
    void *socket_a = zmq_socket(context_a, ZMQ_PULL);
    zmq_bind(socket_a, "tcp://*:8080");

    void *context_c = zmq_ctx_new();
    void *socket_c = zmq_socket(context_c, ZMQ_PULL);
    zmq_bind(socket_c, "tcp://*:7070");

    bool to_stop_a = false, to_stop_c = false;
    string received_a = "Received from A: ";
    string received_c = "Received from C: ";
    int a_bytes = 0;
    int c_bytes = 0;
    for (;;) {
        if (a_bytes != -1) {
            a_bytes = ReceiveMessage(socket_a);
        }
        if (c_bytes != -1) {
            c_bytes = ReceiveMessage(socket_c);
        }

        if (!to_stop_a && !to_stop_c) {
            cout << received_a << a_bytes << '\n';
            cout << received_c << c_bytes << '\n';
        }
        else if (!to_stop_a && to_stop_c) {
            cout << received_a << a_bytes << '\n';
        }
        else {
            cout << received_c << c_bytes << '\n';
        }
    }

    zmq_close(socket_a);
    zmq_ctx_destroy(context_a);
    zmq_close(socket_c);
    zmq_ctx_destroy(context_c);

    return 0;
}