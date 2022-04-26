#ifndef PYTHON_CAPSULE_EXTENSION_H
#define PYTHON_CAPSULE_EXTENSION_H

#ifdef FEDERATED
#ifdef FEDERATED_DECENTRALIZED
#define FEDERATED_CAPSULE_EXTENSION \
    tag_t intended_tag; \
    instant_t physical_time_of_arrival;
#else // FEDERATED_CENTRALIZED
#define FEDERATED_CAPSULE_EXTENSION \
    instant_t physical_time_of_arrival;
#endif // FEDERATED_DECENTRALIZED
#else  // not FEDERATED
#define FEDERATED_CAPSULE_EXTENSION // Empty
#endif // FEDERATED

#endif