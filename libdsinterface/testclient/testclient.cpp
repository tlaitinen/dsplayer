#include "dsclient.hpp"
#include "util.hpp"
#include <boost/program_options.hpp>
using namespace std;
void usage(char** argv) {
    fprintf(stderr, "%s template PATH\n", argv[0]);
    fprintf(stderr, "%s update CONTAINER PATH\n", argv[0]);
    fprintf(stderr, "%s js DISPLAY JS\n", argv[0]);
}
int main(int argc, char** argv) {
    namespace po = boost::program_options;
    if (argc < 3) {
        usage(argv);
        return -1;
    }
    ds::Client client;
    string cmd = argv[1];
    string param1 = argv[2];
    string param2 = (argc > 3) ? argv[3] : "";
    ds::Request req;
    if (cmd == "template") {
        ds::SetTemplate* st = req.mutable_set_template();
        st->set_screen(0);
        st->set_path(param1);

    } else if (cmd == "update") {
        if (argc < 4) {
            usage(argv);
            return -1;
        }
        ds::UpdateScreen* us = req.mutable_update_screen();
        us->set_screen(0);
        us->set_container(param1);
        us->set_path(param2);
    } else if (cmd == "js") {
        ds::Evaluate* e = req.mutable_evaluate();
        e->set_screen(atoi(param1.c_str()));
        e->set_js(param2);
    } else {
        usage(argv);
        return -1;
    }
    client.sendRequest(req);
    return 0;
}
