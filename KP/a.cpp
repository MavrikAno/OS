#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <zmq.h>

using namespace std;

void SendMessage(void *request, const string &message) {
    zmq_msg_t req; 
    zmq_msg_init_size(&req, message.size()); 
    memcpy(zmq_msg_data(&req), message.c_str(), message.size()); 
    zmq_msg_send(&req, request, 0);
    zmq_msg_close(&req);
}

string ReceiveMessage(void *respond) {
    string result = "";
    zmq_msg_t reply;
    zmq_msg_init(&reply); 
    zmq_msg_recv(&reply, respond, 0);
    char* ptr = static_cast<char*>(zmq_msg_data(&reply));
    result = string(ptr, zmq_msg_size(&reply));
    zmq_msg_close(&reply);
    return result;
}

int main() {
    void *context_c = zmq_ctx_new();
    void *request_c = zmq_socket(context_c, ZMQ_REQ);
    zmq_connect(request_c, "tcp://localhost:9090");

    void *context_b = zmq_ctx_new();
    void *request_b = zmq_socket(context_b, ZMQ_PUSH);
    zmq_connect(request_b, "tcp://localhost:8080");

    cout << "Enter strings:" << '\n';

    while(true) {
        string str;
        getline(cin, str);
        SendMessage(request_c, str);
        SendMessage(request_b, to_string(str.size()));
        string received_message = ReceiveMessage(request_c);
    }

    zmq_close(request_c);
    zmq_ctx_destroy(context_c);
    zmq_close(request_b);
    zmq_ctx_destroy(context_b);

    return 0;
}