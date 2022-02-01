#include <stdio.h>
#include <stdlib.h>

#define RANGE 10000

typedef struct Cache {
    int entry[RANGE];
}Cache;

typedef struct Address {
    bool in_cache;
    int last_use;
    int req_num;
}Address;

typedef struct Request {
    int req;
    int next_use;
}Request;

Address addr[RANGE+1] = {{false, 0}};

//  return the cost of replace
int replace(Cache *cache, Request request[],  int cur_req_index, int n, int k) {
    int new_addr = request[cur_req_index].req;
    if (addr[new_addr].in_cache) {  //  no need to replace
        addr[new_addr].req_num = cur_req_index;
        return 0;
    } else {    //  need to replace
        int latest_future_use_index = 0;
        int latest_future_use = request[addr[cache->entry[0]].req_num].next_use;
        for (int i = 1; i < k; i++) {
            if (latest_future_use != -1) {
                int future_use = request[addr[cache->entry[i]].req_num].next_use;
                if (future_use == -1 || future_use > latest_future_use) {
                    latest_future_use_index = i;
                    latest_future_use = future_use;
                }
            }
        }
        int latest_future_use_addr = cache->entry[latest_future_use_index];
        addr[latest_future_use_addr].in_cache = false;
        cache->entry[latest_future_use_index] = new_addr;
        addr[new_addr].in_cache = true;
        addr[new_addr].req_num = cur_req_index;
        return 1;
    }
}

int main(void)
{
    int n = 0, k = 0;
    scanf("%d%d", &n, &k);
    Cache cache;
    Request *request = (Request *)malloc(sizeof(Request)*n);
    for (int i = 0; i < RANGE+1; i++) {
        addr[i].last_use = -1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i].req);
        request[i].next_use = -1;
        if (addr[request[i].req].last_use != -1) {
            request[addr[request[i].req].last_use].next_use = i;
        }
        addr[request[i].req].last_use = i;
    }
    int cache_miss = 0;
    int i = 0;
    int count = 0;
    for (; i < n && count < k; i++) {    //  fulfill cache
        if (addr[request[i].req].in_cache == false) {
            addr[request[i].req].in_cache = true;
            addr[request[i].req].req_num = i;
            cache.entry[count] = request[i].req;
            count++;
        } else {    //  update request number to update next use
            addr[request[i].req].req_num = i;
        }
    }
    cache_miss = count;
    for (; i < n; i++) {
        cache_miss += replace(&cache, request, i, n, k);
    }
    printf("%d", cache_miss);
    free(request);
    return 0;
}

