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

#ifndef _ds_client_hpp_
#define _ds_client_hpp_
#include "ds.pb.h"
#include <deque>
#include <cassert>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/scoped_ptr.hpp>


namespace ds {

    class Client {
        boost::scoped_ptr<boost::interprocess::message_queue> mq;

    public:
        Client();
        ~Client();
        void sendRequest(const Request& r);
    };
}
#endif
