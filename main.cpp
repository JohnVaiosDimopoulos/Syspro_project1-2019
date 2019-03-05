#include <iostream>
#include "Hash_Table.h"
#include "Wallet_info.h"

int main() {

  const int size = 4;

  Wallet_info* user = new Wallet_info("name");
  Hash_Table<Wallet_info*,size>* ht = new Hash_Table<Wallet_info*,size>(10);
  ht->Insert(user,user->get_wallet_id());
  Wallet_info* usr = ht->Search("name");
  List<Bitcoin_in_wallet*>*  list =usr->get_list();
  Bitcoin_in_wallet* coin = new Bitcoin_in_wallet("123",40);
  list->Push(coin);
  list->Delete("123");
  delete ht;



  /*
   int bitcoin_val,sender_hash_table_entries,receiver_hash_table_entries,bucket_size;
   char* bitcoin_balance,*transaction_file;


   if(argc!=12 ){
     std::cout<<"Error:Wrong number of arguments given"<<std::endl;
     std::cout<<"Correct input: ./bitcoin -a bitCoinBalancesFile –t transactionsFile -v bitCoinValue –h1\n"
                "senderHashtableNumOfEntries –h2 receiverHashtableNumOfEntries –b bucketSize"<<std::endl;
     exit(1);
   }
   for(int i =1;i<=argc;i++){
     if(!strcmp(argv[i],"-a")){
       i++;
       bitcoin_balance = (char*)malloc(sizeof(char)*(strlen(argv[i])+1));
       strcpy(bitcoin_balance,argv[i]);

     }else if(!strcmp(argv[i],"-v")){
       i++;
       bitcoin_val= atoi(argv[i]);

     }else if(!strcmp(argv[i],"-h1")){
       i++;
       sender_hash_table_entries = atoi(argv[i]);


     }else if(!strcmp(argv[i],"-h2")){
       i++;
       receiver_hash_table_entries = atoi(argv[i]);


     }else if(!strcmp(argv[i],"-b")) {
       i++;
       bucket_size = atoi(argv[i]);
     }
     else if(!strcmp(argv[i],"-t")) {
       i++;
       transaction_file =(char*)malloc(sizeof(char)*(strlen(argv[i])+1));
       strcpy(transaction_file,argv[i]);
     } else{
       std::cout<<"Correct input: ./bitcoin -a bitCoinBalancesFile –t transactionsFile -v bitCoinValue –h1\n"
                  "senderHashtableNumOfEntries –h2 receiverHashtableNumOfEntries –b bucketSize"<<std::endl;
       exit(1);
     }

     //-----Initialization_phase------

     //1.initialize the structures
     //just make a new Bitcoin_System object;
     //give it all the info


   }*/

}