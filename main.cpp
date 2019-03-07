#include <iostream>
#include <fstream>
#include <istream>
#include "Hash_Table.h"
#include "Wallet_info.h"
#include "Bitcoin_System.h"


static void find_total_users_and_bitcoins(int* total_users,int* total_bitcoins,char* bitcoin_balances){
  int usr =0;
  int bt =0;
  char buffer[256];
  char* temp_ptr;
  // open the balances file
  std::fstream balances_file;
  balances_file.open(bitcoin_balances,std::fstream::in);
  if(balances_file.is_open()){
    // read the file line by line
    while(balances_file.getline(buffer,256)) {
      //split each line word by word;
      temp_ptr = strtok(buffer, " ");
      (*total_users)++;
      while (temp_ptr != NULL) {
        temp_ptr = strtok(NULL, " ");
        if(temp_ptr)
          (*total_bitcoins)++;
      }
    }
  }

  balances_file.close();

}

static void calculate_tables_sizes(int* bitcoin_table_size,int* user_table_size,int total_users,int total_bitcoins,int bucket_size){

  int bitcoin_entries_per_bucket;
  int wallet_id_entries_per_bucker;

  //calculate the number of entries in each bucket
  bitcoin_entries_per_bucket = (bucket_size - (sizeof(Hash_Bucket<Bitcoin_Status*>*)+ sizeof(unsigned int)))/sizeof(Bitcoin_Status*);
  wallet_id_entries_per_bucker = (bucket_size-(sizeof(Hash_Bucket<Wallet_info*>*)+ sizeof(unsigned int)))/ sizeof(Wallet_info*);

  //in order to avoid collisions we want an average of 70% loading factor in each bucket
  //with that in mind we calculate the size of the table in order to achieve that
  *bitcoin_table_size = total_bitcoins/(0.7*bitcoin_entries_per_bucket);
  *user_table_size = total_users/(0.7*wallet_id_entries_per_bucker);

}

static void manage_inline_arguments(int argc,char** argv,int*bucket_size,int* bitcoin_val,int* sender_hash_table_entries,int* receiver_hash_table_entries,char** bitcoin_balance ,char** transaction_file) {

  if (argc != 13) {
    std::cout << "Error:Wrong number of arguments given" << std::endl;
    std::cout << "Correct input: ./bitcoin -a bitCoinBalancesFile –t transactionsFile -v bitCoinValue –h1"
                 "senderHashtableNumOfEntries –h2 receiverHashtableNumOfEntries –b bucketSize" << std::endl;
    exit(1);
  }
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-a")) {
      i++;
      *bitcoin_balance = (char*) malloc(sizeof(char) * (strlen(argv[i]) + 1));
      strcpy(*bitcoin_balance, argv[i]);

    } else if (!strcmp(argv[i], "-v")) {
      i++;
      *bitcoin_val = atoi(argv[i]);

    } else if (!strcmp(argv[i], "-h1")) {
      i++;
      *sender_hash_table_entries = atoi(argv[i]);

    } else if (!strcmp(argv[i], "-h2")) {
      i++;
      *receiver_hash_table_entries = atoi(argv[i]);

    } else if (!strcmp(argv[i], "-b")) {
      i++;
      *bucket_size = atoi(argv[i]);
    } else if (!strcmp(argv[i], "-t")) {
      i++;
      *transaction_file = (char *) malloc(sizeof(char) * (strlen(argv[i]) + 1));
      strcpy(*transaction_file, argv[i]);
    } else {
      std::cout << "Correct input: ./bitcoin -a bitCoinBalancesFile –t transactionsFile -v bitCoinValue –h1"
                   "senderHashtableNumOfEntries –h2 receiverHashtableNumOfEntries –b bucketSize" << std::endl;
      exit(1);
    }

  }
}


int main(int argc,char** argv) {

/*
  const int size = 4;

  Wallet_info user("name");
  Hash_Table<Wallet_info>* ht = new Hash_Table<Wallet_info>(10,size);
  ht->Insert(user,user.get_wallet_id());
  Wallet_info usr = ht->Search("name");
  List<Bitcoin_in_wallet*>*  list =usr.get_list();
  Bitcoin_in_wallet* coin = new Bitcoin_in_wallet("123",40);
  list->Push(coin);
  list->Delete("123");
  delete ht;

*/



  int bitcoin_val,sender_hash_table_entries,receiver_hash_table_entries,bucket_size,total_users,total_bitcoins,bitcoins_table_size,users_table_size;
  char* bitcoin_balance,*transaction_file;

   // manage inline arguments
   manage_inline_arguments(argc,argv,&bucket_size,&bitcoin_val,&sender_hash_table_entries,&receiver_hash_table_entries,&bitcoin_balance,&transaction_file);

   // read the bitcoin file and count the number of users and bitcoins in the system
   find_total_users_and_bitcoins(&total_users,&total_bitcoins,bitcoin_balance);
   //calculate the size of the bitcoin and wallet hash table
   calculate_tables_sizes(&bitcoins_table_size,&users_table_size,total_users,total_bitcoins,bucket_size);
   //initialize the system
   Bitcoin_System* system = new Bitcoin_System(bucket_size,sender_hash_table_entries,receiver_hash_table_entries,bitcoins_table_size,users_table_size,bitcoin_val);

   system->Initialize_System(bitcoin_balance);
//   system->Initial_Transactions(transaction_file);
//   system->Begin_System();

  delete system;
  free(transaction_file);
  free(bitcoin_balance);
}

