#include "Bitcoin_System.h"
#define INGORE 1000000
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
            //===========================//
//==============CONSTRUCTOR-DESTRUCTOR=======================//
          //============================//


Bitcoin_System::Bitcoin_System(int bucket_size,int senders_table_size,int receivers_table_size,int bitcoin_table_size,int wallet_table_size,int bitcoin_value):bitcoin_value(bitcoin_value),bucket_size(bucket_size){

  // creating all the new elements
  this->wallets = new Hash_Table<Wallet_info*>(bucket_size,wallet_table_size);
  this->bitcoins_status = new Hash_Table<Bitcoin_Status*>(bucket_size,bitcoin_table_size);
  this->senders = new Hash_Table<senders_receivers_data*>(bucket_size,senders_table_size);
  this->receivers = new Hash_Table<senders_receivers_data*>(bucket_size,receivers_table_size);
  this->transactions = new List<Transaction_info*>();
  this->most_recent = new Date();
  this->max_transaction_id=0;


}

Bitcoin_System::~Bitcoin_System(){

  //delete all the structures
  delete this->wallets;
  delete this->bitcoins_status;
  delete this->senders;
  delete this->receivers;
  delete this->transactions;
  delete this->most_recent;
}



                //===========================//
//================PUBLIC-INITIALIZATION/BEGIN=============//
              //============================//




void Bitcoin_System::Initial_Transactions(char* transaction_file){
  Transactions_from_file(transaction_file,false);
}

void Bitcoin_System::set_max_transaction_id() {
  int max = 0;
  int current_id;
  List_node<Transaction_info*>* current = this->transactions->get_head();
  while (current!=NULL){
    current_id= atoi(current->get_item()->get_transaction_id());
    if(current_id>max)
      max = current_id;
    current = current->get_next();
  }
  this->max_transaction_id = max;
}

void Bitcoin_System::Initialize_System(char* bitcoin_balances){
  std::fstream bitcoin_file;
  char* temp_ptr;
  //initialize two hash tables for checking

  //open the file
  bitcoin_file.open(bitcoin_balances,std::fstream::in);

  if(bitcoin_file.is_open()){

    char buffer[512];

    // read line by line
    while(bitcoin_file.getline(buffer,512)){

      // get the username
      temp_ptr = strtok(buffer," ");
      char* initial_owner = (char*)malloc(sizeof(char)*(strlen(temp_ptr)+1));
      strcpy(initial_owner,temp_ptr);

      // check if the username is valid
      // if the Search returns a value different than NULL it means that the user is already in the system
      if(this->wallets->Search(temp_ptr)!=NULL){
        std::cout<<"Error the value "<<temp_ptr<<" is an invalid username and will not be inserted in the system"<<std::endl;
        continue;
      }

      // put him inside wallet,senders,receivers
      senders_receivers_data* new_sender = new senders_receivers_data(temp_ptr);
      senders_receivers_data* new_receiver = new senders_receivers_data(temp_ptr);
      Wallet_info* new_wallet = new Wallet_info(temp_ptr);
      this->senders->Insert(new_sender,new_sender->get_id());
      this->receivers->Insert(new_receiver,new_receiver->get_id());
      this->wallets->Insert(new_wallet,new_wallet->get_wallet_id());

      // read each bitcoin in the line
      while (temp_ptr!=NULL){
        temp_ptr = strtok(NULL," ");
        //each time temp_ptr gets in the loop with the old value so we need to check its value after we get the string
        if(temp_ptr!=NULL){
          //check is the bicoin id is valid

          if(this->bitcoins_status->Search(temp_ptr)!=NULL){
            std::cout<<"Error the value "<<temp_ptr<<" is an invalid bitcoin id"<<std::endl;
            exit(1);
          }

          // this objects goes to the bicoin_status Hash_Table
          Bitcoin_Status* new_bitcoin_status =  new Bitcoin_Status(this->bitcoin_value,temp_ptr,initial_owner);
          // this object goes to the Bitcoin_list in the Wallets Hash Table
          Bitcoin_in_wallet* new_bitcoin_in_wallet = new Bitcoin_in_wallet(temp_ptr,this->bitcoin_value);
          // put bitcoin in the Bitcoin_Status Hash Table
          this->bitcoins_status->Insert(new_bitcoin_status,new_bitcoin_status->get_id());
          //put the bitcoin in the users wallet
          // get the list from the wallet
          List<Bitcoin_in_wallet*>* bitcoin_list = new_wallet->get_list();
          // put the bitcoin in the list;
          // the only duplicated info is the initial value of the bitcoin (which will change in the Wallet because it represents the amount the user has)
          bitcoin_list->Push(new_bitcoin_in_wallet);
        }
      }
      //free the string
      free(initial_owner);
    }
  }
    // close the file
    bitcoin_file.close();
}

void Bitcoin_System::Begin_System() {
  //TODO:Do the UI method
  char instruction[25],param[25];

  bool work = true;
  while(work){

    std::cout<<"Please give the instruction"<<std::endl;
    std::cin>>instruction;

    if(!strcmp(instruction,"requestTransaction")){
      Redirect_input_to_file("temp_file");
      // make the transaction from the file by also giving the transaction an id and check if the date is valid
      Transactions_from_file("temp_file", true);
      //remove the temp file

      if(remove("temp_file")!=0){
        std::cout<<"error in deleting temp file"<<std::endl;
      }
    }

    else if(!strcmp(instruction,"requestTransactions")){
      // check if our parameter is a file
      // get all the input into a file
      char* filename;
      Redirect_input_to_file("temp_file");
      if(Is_input_a_file("temp_file")){
        //get the name from the file
        std::fstream file;
        file.open("temp_file",std::fstream::in);
        char buffer[20];
        file>>buffer;
        file.close();
        Transactions_from_file(buffer, true);
      }
      // the input was from user so we have our file ready
      else{
        Transactions_from_file("temp_file", true);
      }

      //delete the file
      if(remove("temp_file")!=0){
        std::cout<<"error in deleting temp file"<<std::endl;
      }

    }

    else if((!strcmp(instruction,"findEarnings"))||(!strcmp(instruction,"findPayments"))){

      Hash_Table<senders_receivers_data*>* table;

      // choosing wheater we want the receiver or the sender table
      if(!strcmp(instruction,"findEarnings"))
        table = this->receivers;
      else
        table = this->senders;

      // these are allocated inside the get_args method
      char*time1=NULL,*time2 =NULL,*date1=NULL,*date2=NULL,*wallet_id=NULL;

      //if the arguments are correct
      if(Find_Earnings_and_Payments_get_args(&time1,&time2,&date1,&date2,&wallet_id)){
      Find_Earnings_and_Payments(table,wallet_id,time1,time2,date1,date2);
      free(time1);
      free(time2);
      free(date1);
      free(date2);
      free(wallet_id);
      }
    }

    else if(!strcmp(instruction,"walletStatus")){
      std::cin>>param;
      std::cin.ignore(INGORE,'\n');
      Wallet_Status(param);
    }

    else if(!strcmp(instruction,"bitCoinStatus")){
      std::cin>>param;
      std::cin.ignore(INGORE,'\n');
      Bitcoin_Stat(param);
    }

    else if(!strcmp(instruction,"traceCoin")) {
      std::cin>>param;
      std::cin.ignore(INGORE,'\n');
      Trace_bitcoin(param);

    }

    else if(!strcmp(instruction,"exit"))
      work= false;

    else {
      std::cout << "WRONG INSTRUCTION TRY AGAIN" << std::endl;
      std::cin.ignore(INGORE, '\n');
    }

  }


}






                            //=========================//
//============================PRIVATE-FUNCTIONALITY=========================////
                          //=========================//





// manages the arguments for find earnings and payments and also checks if they are valid in case of failure it returns false
bool Bitcoin_System::Find_Earnings_and_Payments_get_args(char** time1, char** time2,char** date1,char** date2,char** wallet_id){
  // gonna put the arguments inside the table
  char arg_table[5][25];
  int arg_counter = 0;

  // read each argument
  for(int i =0;i<5;i++){
    // if we see end of line or reach the amount we want stop
    if(std::cin.get()!='\n' && arg_counter<5){
      std::cin>>arg_table[i];
      arg_counter++;
    }
    else{
    //if we reach the amount of arguments we wanted ignore the rest of the input in this line
      if(arg_counter==5)
        std::cin.ignore(INGORE,'\n');
      break;
    }
  }

  // manage the arguments
  //1.check the number
  if(arg_counter!=1 && arg_counter!=3 && arg_counter!=5){
    std::cout<<"Wrong format of arguments given"<<std::endl;
    return false;
  }
  //2.wallet_id
  //do the check fist
  if(this->wallets->Search(arg_table[0])==NULL) {
    std::cout<<"The user does not exists"<<std::endl;
    return false;
  }

  *wallet_id = (char*)malloc(sizeof(char)*(strlen(arg_table[0])+1));
  strcpy(*wallet_id,arg_table[0]);

  //3.check the  aguments in pairs of two
  for(int i=1;i<arg_counter;i+=2){

    // the third character of the string must be '-' if it is a date
    if(arg_table[i][2]=='-' && arg_table[i+1][2]=='-'){
      // get the strings
      *date1 = (char*)malloc(sizeof(char)*(strlen(arg_table[i])+1));
      *date2 = (char*)malloc(sizeof(char)*(strlen(arg_table[i+1])+1));
      strcpy(*date1,arg_table[i]);
      strcpy(*date2,arg_table[i+1]);
      // if the first pair is dates ignore the rest of the input
      // so break the for loop
      break;
    }

    //the third character of the string must bu ':' if it is a time
    else if(arg_table[i][2]==':' && arg_table[i+1][2]==':'){
      //get the strings
      *time1 = (char*)malloc(sizeof(char)*(strlen(arg_table[i])+1));
      *time2 = (char*)malloc(sizeof(char)*(strlen(arg_table[i+1])+1));
      strcpy(*time1,arg_table[i]);
      strcpy(*time2,arg_table[i+1]);
      //if the fist pair is dates ignore the rest of the input
      // so break the for loop
      break;
    }

    // in this case we have a pair of date and time
    else if(arg_table[i][2]==':' && arg_table[i+1][2]=='-'){

      if(i==1){
        //in the first loop
        *time1 = (char*)malloc(sizeof(char)*(strlen(arg_table[i])+1));
        *date1 = (char*)malloc(sizeof(char)*(strlen(arg_table[i+1])+1));
        strcpy(*time1,arg_table[i]);
        strcpy(*date1,arg_table[i+1]);
      }
      else{
        //in the second loop
        *time2 = (char*)malloc(sizeof(char)*(strlen(arg_table[i])+1));
        *date2 = (char*)malloc(sizeof(char)*(strlen(arg_table[i+1])+1));
        strcpy(*time2,arg_table[i]);
        strcpy(*date2,arg_table[i+1]);
      }
    }

    // in case of any other error
    else{
      std::cout<<"Wrong format of arguments given"<<std::endl;
      free(*wallet_id);
      //there is a case where we might get there in se second loop so we need to delete the aloccations
      if(*date1!=NULL && *time1!=NULL){
        free(date1);
        free(date2);
      }
      return false;
    }

  }
  return true;
}

void Bitcoin_System::Find_Earnings_and_Payments(Hash_Table<senders_receivers_data*>* table,char *wallet_id, char *time1, char *time2, char *date1, char *date2){

  // only check with a ragne of time
  if(date1==NULL && date2==NULL && time1!=NULL && time2!=NULL){
  // doing the conversions
    char* hour,* min;
    hour=strtok(time1,":");
    min=strtok(NULL," ");
    Date lower_bound(0,0,0,atoi(hour),atoi(min));

    hour = strtok(time2,":");
    min = strtok(NULL," ");
    Date upper_bound(0,0,0,atoi(hour),atoi(min));
  // do the ckecking and printing
    table->Search(wallet_id)->print_in_range_of_date(lower_bound,upper_bound);

  }
  // only check with a range of date
  else if(time1==NULL && time2==NULL && date1!=NULL && date2!=NULL){
    char* year,*month,*day;

    day=strtok(date1,"-");
    month=strtok(NULL,"-");
    year=strtok(NULL," ");
    Date lower_bound(atoi(year),atoi(month),atoi(day),0,0);

    day=strtok(date2,"-");
    month=strtok(NULL,"-");
    year=strtok(NULL," ");
    Date upper_bound(atoi(year),atoi(month),atoi(day),0,0);

    table->Search(wallet_id)->print_in_range_of_date(lower_bound,upper_bound);

  }
  else if(time1!=NULL && time2!=NULL && date1!=NULL && date2!=NULL){
    char* hour,* min,* year,*month,*day;

    day=strtok(date1,"-");
    month=strtok(NULL,"-");
    year=strtok(NULL," ");
    hour=strtok(time1,":");
    min=strtok(NULL," ");
    Date lower_bound(atoi(year),atoi(month),atoi(day),atoi(hour),atoi(min));

    day=strtok(date2,"-");
    month=strtok(NULL,"-");
    year=strtok(NULL," ");
    hour=strtok(time2,":");
    min=strtok(NULL," ");
    Date upper_bound(atoi(year),atoi(month),atoi(day),atoi(hour),atoi(min));

    table->Search(wallet_id)->print_in_range_of_date(lower_bound,upper_bound);
  }
  //print all the transactions
  else{
    table->Search(wallet_id)->printList();
  }
}

void Bitcoin_System::Bitcoin_Stat(char* bitcoin_id){
  Bitcoin_Status* bitcoin = this->bitcoins_status->Search(bitcoin_id);

  //check if the bitcoin exists
  if(bitcoin==NULL){
    std::cout<<"ERROR THE BITCOIN DOES NOT EXIST"<<std::endl;
    return;
  }

  std::cout<<"ID: "<<bitcoin->get_id()<<" NUMBER OF TRANSACTIONS: "<<bitcoin->get_transactions_number()<<" UNSPEND AMOUNT"<<bitcoin->get_unspend_amount()<<std::endl;
}

void Bitcoin_System::Wallet_Status(char* wallet_id){
  Wallet_info* wallet = this->wallets->Search(wallet_id);
  //check if the id was valid
  if(wallet==NULL){
    std::cout<<"ERROR:THE USER DOES NOT EXIST"<<std::endl;
    return;
  }

  std::cout<<"USER: "<<wallet->get_wallet_id()<<std::endl;
  std::cout<<" TOTAL MONEY: "<<wallet->get_total_money()<<std::endl;
  wallet->Print_all_bitcoins();
}

void Bitcoin_System::Trace_bitcoin(char* bitcoin_id){

  Bitcoin_Status* bitcoin = this->bitcoins_status->Search(bitcoin_id);

  //check if the bitcoin exists
  if(bitcoin==NULL){
    std::cout<<"ERROR THE BITCOIN DOES NOT EXIST"<<std::endl;
    return;
  }
  bitcoin->Print_Transactions(this->bucket_size);
}

void Bitcoin_System::Get_current_date(int* year,int* month,int* day,int* hour,int* minutes){
  //set up the timer
  time_t now = time(0);
  //get the struct that holds the cuurent_time
  tm* local_time = localtime(&now);
  *year = 1900 + local_time->tm_year;
  *month=1+local_time->tm_mon;
  *day=local_time->tm_mday;
  *hour= local_time->tm_hour;
  *minutes= local_time->tm_min;

}

void Bitcoin_System::Transactions_from_file(char *transaction_file, bool check_date) {
  // open the file start reading line by line

  std::fstream transactions;
  char*transaction_id,*sender,*receiver;
  int amount,day,month,year,hour,minutes;
  char* temp_ptr;
  char buffer[256];
  transactions.open(transaction_file,std::fstream::in);
  if(transactions.is_open()){

    //start reading the file line by line
    while(transactions.getline(buffer,256)){

      // get each part of the line
      // if we want to setup our own transaction_id
      if(this->max_transaction_id!=0){
        //set transaction_id = max+1
        char transaction_id_buffer[20];
        sprintf(transaction_id_buffer,"%d",this->max_transaction_id+1);
        transaction_id = transaction_id_buffer;
        //update the max_transaction_id
        this->max_transaction_id ++;
        //start reading from sender
        sender = strtok(buffer," ");

      }
      else{
        //if we want to get the transaction_id from file
        transaction_id= strtok(buffer," ");
        sender = strtok(NULL," ");
      }

      receiver = strtok(NULL," ");
      temp_ptr = strtok(NULL," ");
      amount=atoi(temp_ptr);

      // we need to check if there is an hour in the transaction
      if((temp_ptr=strtok(NULL,"-"))==NULL)
        //give the current_date
        Get_current_date(&year,&month,&day,&hour,&minutes);
      else{
        // make the day an int
        day=atoi(temp_ptr);

        //get month
        temp_ptr=strtok(NULL,"-");
        month=atoi(temp_ptr);
        //get year
        temp_ptr = strtok(NULL," ");
        year = atoi(temp_ptr);

        temp_ptr=strtok(NULL,":");
        hour=atoi(temp_ptr);

        temp_ptr=strtok(NULL," ");
        minutes=atoi(temp_ptr);

      }
      // make the transaction
      Request_Transaction(transaction_id,sender,receiver,amount,day,month,year,hour,minutes,check_date);
    }
  }
  transactions.close();
}

void Bitcoin_System::Update_tree_and_wallets(Transaction_info* transaction_info,Wallet_info* sender_wallet,Wallet_info* receiver_wallet,char* bitcoin_id, int transaction_amount){

  //create the transaction in the tree of the bitcoin
  Bitcoin_Status* bitcoin_for_transaction = bitcoins_status->Search(bitcoin_id);
  bitcoin_for_transaction->New_Transaction(transaction_info,sender_wallet->get_wallet_id(),receiver_wallet->get_wallet_id(),transaction_amount);


  //update the senders and the receivers wallet
  //keep the name of the bitcoin in case it is deleted in the senders_list
  char* bit_id = (char*)malloc(sizeof(char)*strlen(bitcoin_id)+1);
  strcpy(bit_id,bitcoin_id);
  sender_wallet->update_bitcoin_amount(bit_id,(-transaction_amount));
  receiver_wallet->update_bitcoin_amount(bit_id,transaction_amount);

  //update the bitcoin status of the bitcoin involved
  bitcoin_for_transaction->increase_transaction_number();
  if(!strcmp(sender_wallet->get_wallet_id(),bitcoin_for_transaction->get_initial_owners_id())){
    bitcoin_for_transaction->update_unspend_amount(transaction_amount);
  }

  free(bit_id);

}

void Bitcoin_System::Request_Transaction(char *transaction_id,char *sender_id,char *receiver_id,int &amount,int &day,int &mounth,int &year,int &hour,int &minute,bool check_date) {

  //---1.Validation---//

  //check if the transaction_id is valid
  if((this->transactions->Search(transaction_id))!=NULL) {
    std::cout<<"For transaction with id: "<<transaction_id<<std::endl;
    std::cout<<"Invalid Transaction Id"<<std::endl;
    std::cout<<std::endl;
    return;
  }
  //check if the sender and the receiver actually exist
  // get a pointer to each wallet to avoid searching all the time
  Wallet_info* senders_wallet = this->wallets->Search(sender_id);
  Wallet_info* receivers_wallet = this->wallets->Search(receiver_id);

  if(senders_wallet==NULL||receivers_wallet==NULL){
    std::cout<<"For transaction with id: "<<transaction_id<<std::endl;
    std::cout<<"Invalid sender id: "<<sender_id<<" or receiver id: "<<receiver_id<<std::endl;
    std::cout<<std::endl;
    return;
  }

  //check if the sender is the same person as the receiver
  if(!strcmp(sender_id,receiver_id)){
    std::cout<<"For transaction with id: "<<transaction_id<<std::endl;
    std::cout<<"Sender id can't be the same with the receiver"<<std::endl;
    std::cout<<std::endl;
    return;
  }

  //check if the sender actually has the money
  if(senders_wallet->get_total_money()<amount){
    std::cout<<"For transaction with id: "<<transaction_id<<std::endl;
    std::cout<<"The sender does not have enough money to make the transaction"<<std::endl;
    std::cout<<std::endl;
    return;
  }


  //check if the hour of the transaction is vallid
  //we compare it to the last transaction make which will be the head of our list
  //the check is not happenig if we are at the initialization phase
  if(check_date){
    Date current_date(year,mounth,day,hour,minute);
    if(this->most_recent->is_after(current_date)){
      std::cout<<"For transaction with id: "<<transaction_id<<std::endl;
      std::cout<<"Invalid date"<<std::endl;
      std::cout<<"Most recent date is: ";
      this->most_recent->Print_date();
      std::cout<<std::endl;
    }
    else{
      //update the most recent date;
      delete most_recent;
      this->most_recent = new Date(year,mounth,day,hour,minute);
    }
  }



  //---2.Make the transaction info and connect it---//

  //put the transaction into the list and make the two hash_tables point to the transaction
  Transaction_info* new_transaction = new Transaction_info(sender_id,receiver_id,transaction_id,amount,year,mounth,day,hour,minute);
  this->transactions->Push(new_transaction);

  //connect the senders_hash_table
  senders_receivers_data* senders_data = this->senders->Search(sender_id);
  senders_data->Insert(new_transaction);
  //connect the receivers hash table
  senders_receivers_data* receivers_data = this->receivers->Search(receiver_id);
  receivers_data->Insert(new_transaction);




  //---3.Make the actual Transaction---//

  //-->check if the sender has a bitcoin that can make the transaction bu itself
  char* bitcoin_id = senders_wallet->Find_proper_bitcoin(amount);

  //there is such a bitcoin so we make the transaction
  if(bitcoin_id!=NULL){
    Update_tree_and_wallets(new_transaction,senders_wallet,receivers_wallet,bitcoin_id,amount);
  }


  //there is no bittcoin that can make the transaction alone
  else{
    // we will traverse through the list and get money form the bitcoins untill we are able to make the transaction

    List_node<Bitcoin_in_wallet*>* current_bitcoin = senders_wallet->get_list()->get_head();
    List_node<Bitcoin_in_wallet*>* next_bitcoin;
    int amount_left = amount;

    while (current_bitcoin!=NULL && amount_left>0){

      //the bitcoin can't fulfil the rest of the transaction by itself
      if(current_bitcoin->get_item()->get_value()<amount_left){
        //we take all the money we can from the current bitcoin
        amount_left -= current_bitcoin->get_item()->get_value();
        //keep next in case we delete the bitcoin
        next_bitcoin = current_bitcoin->get_next();
        Update_tree_and_wallets(new_transaction,senders_wallet,receivers_wallet,current_bitcoin->get_item()->get_id(),current_bitcoin->get_item()->get_value());
      }
      // the current bitcoin can fulfil the rest of the transaction
      else{
        int money_to_take = amount_left;
        //upadtae the amount
        amount_left-=current_bitcoin->get_item()->get_value();
        // keep the next node because it might be deleted in updat
        next_bitcoin = current_bitcoin->get_next();
        Update_tree_and_wallets(new_transaction,senders_wallet,receivers_wallet,current_bitcoin->get_item()->get_id(),money_to_take);
      }
      current_bitcoin = next_bitcoin;
    }

  }
}

void Bitcoin_System::Redirect_input_to_file(char *filename) const {

  char buffer[512];
  //open a temporary file
  std::fstream temp_file;
  temp_file.open(filename, std::fstream::in|std::fstream::app);
  // start reading and look for two \n
  while (std::cin.peek()!='\n'){
    // get the input into o buffer
    std::cin.getline(buffer, 512);
    if(temp_file.is_open()){
      // put the contents of the buffer in a file
      temp_file << buffer << std::endl;
    }
  }
  temp_file.close();
}

bool Bitcoin_System::Is_input_a_file(char *filename) const {

  // we check if the first line of tw file has an ";" char
  char buffer[512];
  std::fstream temp_file;
  temp_file.open(filename, std::ios_base::in);
  temp_file.getline(buffer,512);
  temp_file.close();
  char* temp_ptr;

  // if it does'nt it means the user gave a file name so we return the file name
  if((temp_ptr=strchr(buffer,';'))==NULL)
    return true;
  else
    // we found ';' so we return NULL an we will use the same file for our input
    return false;
}