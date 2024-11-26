//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <iostream>
#include "enet_cpp/enet.h"

namespace enet {


    ENetHost::ENetHost(const std::string &t_host, int t_port, NetworkAddressType t_addr_type) :
        m_stopFlag(false), m_workerThread(nullptr), m_socket(nullptr)
    {
        m_socket = new ENetSocket(ENetSocketNetwork(t_host, t_port, t_addr_type));
    }

    ENetHost::~ENetHost() { }

    int ENetHost::start() {

        std::cout << "Starting host server" << '\n';

        try {
            m_socket->connect();
            if (!m_socket->is_connected()) {
                std::cout << "Failed to create network socket" << '\n';
                return -1;
            }
            std::cout << "Successfully created socket" << '\n';
        }
        catch (SocketError &err) {
            std::cout << err.what() << "\n";
            return -1;
        }

//        // Setup worker thread to listen for socket events.
//        if (m_workerThread == nullptr) {
//            m_stopFlag = false;
//            m_workerThread = new std::thread(&ENetHost::workerFunction, this);
//        }
        return 0;
    }

    void ENetHost::stop() {

        std::cout << "Shutting down host server" << '\n';

//        if (m_workerThread != nullptr) {
//            std::cout << "Stopping worker thread..." << "\n";
//            m_stopFlag = true;
//            if (m_workerThread->joinable()) {
//                m_workerThread->join();  // Wait for the worker thread to finish.
//            }
//            delete m_workerThread;
//            m_workerThread = nullptr;
//        }
        if (m_socket != nullptr) {
            std::cout << "Closing host socket..." << "\n";
            m_socket->disconnect();
            delete m_socket;
            m_socket = nullptr;
        }

        std::cout << "Host server has stopped" << '\n';
    }

    bool ENetHost::is_connected() {
        return m_socket->is_connected();
    }

    // Worker function that runs in the thread.
    void ENetHost::workerFunction() {
        while (!m_stopFlag) {
            std::cout << "Worker thread is running...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work.
        }
        std::cout << "Worker thread is stopping...\n";
    }

}

