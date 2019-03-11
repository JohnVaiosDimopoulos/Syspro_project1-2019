cmake_minimum_required(VERSION 3.13)
project(Project1_ver3)

set(CMAKE_CXX_STANDARD 98)

add_executable(Project1_ver3 main.cpp Bitcoin_System.cpp Bitcoin_System.h Hash_Table.h Hash_Bucket.h List.h List_node.h Wallet_info.cpp Wallet_info.h Bitcoin_in_wallet.cpp Bitcoin_in_wallet.h Bitcoin_Status.cpp Bitcoin_Status.h Transaction_tree.cpp Transaction_tree.h Transaction_info.cpp Transaction_info.h senders_receivers_data.cpp senders_receivers_data.h senders_receivers_list_data.cpp senders_receivers_list_data.h Transaction_tree_node.cpp Transaction_tree_node.h)