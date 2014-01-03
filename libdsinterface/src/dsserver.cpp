/*
Copyright (C) 2013 Tero Laitinen

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "dsserver.hpp"
#include <boost/interprocess/ipc/message_queue.hpp>
#define MSG_SIZE 1024
using namespace std;
namespace ds {

    Server::Server() {

        using namespace boost::interprocess;
        //Erase previous message queue
        message_queue::remove("ds-player");

        //Create a message_queue.
        mq.reset(new message_queue
                (create_only               //only create
                 ,"ds-player"           //name
                 ,16                       //max message number
                 ,MSG_SIZE //  max message size
                ));
    }
    Server::~Server() {
    }

    void Server::check() {
        char buf[MSG_SIZE];
        size_t recvd;
        unsigned int priority;
        if (mq->try_receive(buf, MSG_SIZE, recvd, priority)) {
            Request req;
            req.ParseFromArray(buf, recvd);
            requests.push_back(req);
        }
    }
}
