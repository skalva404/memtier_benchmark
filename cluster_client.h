/*
 * Copyright (C) 2011-2017 Redis Labs Ltd.
 *
 * This file is part of memtier_benchmark.
 *
 * memtier_benchmark is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * memtier_benchmark is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with memtier_benchmark.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MEMTIER_BENCHMARK_CLUSTER_CLIENT_H
#define MEMTIER_BENCHMARK_CLUSTER_CLIENT_H

#include <set>
#include "client.h"

typedef std::queue<unsigned long long> key_index_pool;

// forward decleration
class shard_connection;

class cluster_client : public client {
protected:
    std::vector<key_index_pool*> m_key_index_pools;
    unsigned int m_slot_to_shard[16384];

    char m_key_buffer[250];
    int m_key_len;

    virtual int connect(void);
    virtual void disconnect(void);

    shard_connection* add_shard_connection(char* address, char* port);
    bool get_key_for_conn(unsigned int conn_id, int iter, unsigned long long* key_index);

public:
    cluster_client(client_group* group);
    virtual ~cluster_client();

    // client manager api's
    virtual void handle_cluster_slots(protocol_response *r);
    virtual void create_request(struct timeval timestamp, unsigned int conn_id);
    virtual bool hold_pipeline(unsigned int conn_id);
};


#endif //MEMTIER_BENCHMARK_CLUSTER_CLIENT_H
