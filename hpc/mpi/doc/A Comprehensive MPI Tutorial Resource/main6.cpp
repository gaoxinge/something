#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <mpi.h>

using namespace std;

void decompose_domain(int domain_size, int world_rank, int world_size, int *subdomain_start, int *subdomain_size) {
    *subdomain_start = domain_size / world_size * world_rank;
    *subdomain_size = domain_size / world_size;
    if (world_rank == world_size - 1) {
        *subdomain_size += domain_size % world_size;
    }
}

typedef struct {
    int location;
    int num_steps_left_in_walk;
} Walker;

void initialize_walkers(int num_walkers_per_proc, int max_walk_size, int subdomain_start, int subdomain_size, vector<Walker> *incoming_walkers) {
    Walker walker;
    for (int i = 0; i < num_walkers_per_proc; i++) {
        walker.location = subdomain_start;
	walker.num_steps_left_in_walk = (1.0 * rand() / RAND_MAX) * max_walk_size;
	incoming_walkers->push_back(walker);
    }
}

void walk(Walker *walker, int subdomain_start, int subdomain_size, int domain_size, vector<Walker> *outgoing_walkers) {
    while (walker->num_steps_left_in_walk > 0) {
        if (walker->location == subdomain_start + subdomain_size) {
            if (walker->location == domain_size) {
                walker->location = 0;
	    }
	    outgoing_walkers->push_back(*walker);
	    break;
	} else {
	    walker->location++;
            walker->num_steps_left_in_walk--;
	}
    }
}

void send_outgoing_walkers(vector<Walker> *outgoing_walkers, int world_rank, int world_size) {
    MPI_Send(outgoing_walkers->data(), outgoing_walkers->size() * sizeof(Walker), MPI_BYTE, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    outgoing_walkers->clear();
}

void receive_incoming_walkers(vector<Walker> *incoming_walkers, int world_rank, int world_size) {
    int incoming_rank = world_rank == 0 ? world_size - 1 : world_rank - 1;
    
    MPI_Status status;
    MPI_Probe(incoming_rank, 0, MPI_COMM_WORLD, &status);

    int incoming_walkers_size;
    MPI_Get_count(&status, MPI_BYTE, &incoming_walkers_size);
    incoming_walkers->resize(incoming_walkers_size / sizeof(Walker));
    MPI_Recv(incoming_walkers->data(), incoming_walkers_size, MPI_BYTE, incoming_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

int main(int argc, char **argv) {
    int domain_size = atoi(argv[1]);
    int max_walk_size = atoi(argv[2]);
    int num_walkers_per_proc = atoi(argv[3]);

    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    srand(time(NULL) * world_rank);
    int subdomain_start, subdomain_size;
    vector<Walker> incoming_walkers, outgoing_walkers;

    decompose_domain(domain_size, world_rank, world_size, &subdomain_start, &subdomain_size);
    initialize_walkers(num_walkers_per_proc, max_walk_size, subdomain_start, subdomain_size, &incoming_walkers);
    
    cout << "Process " << world_rank << " initiated " << num_walkers_per_proc << " walkers in subdomain " << subdomain_start << " - " << subdomain_start + subdomain_size - 1 << endl;

    int maximum_sends_recvs = max_walk_size / (domain_size / world_size) + 1;
    for (int m = 0; m < maximum_sends_recvs; m++) {
        for (int i = 0; i < incoming_walkers.size(); i++) {
            walk(&incoming_walkers[i], subdomain_start, subdomain_size, domain_size, &outgoing_walkers);
	}

	cout << "Process " << world_rank << " sending " << outgoing_walkers.size() << " outgoing walkers to process " << (world_rank + 1) % world_size << endl;

	if (world_rank % 2 == 0) {
	    send_outgoing_walkers(&outgoing_walkers, world_rank, world_size);
	    receive_incoming_walkers(&incoming_walkers, world_rank, world_size);
	} else {
	    receive_incoming_walkers(&incoming_walkers, world_rank, world_size);
	    send_outgoing_walkers(&outgoing_walkers, world_rank, world_size);
	}

	cout << "Process " << world_rank << " received " << incoming_walkers.size() << " incoming walkers " << endl;
    }

    cout << "Process " << world_rank << " done" << endl;
    MPI_Finalize();
    return 0;
}
