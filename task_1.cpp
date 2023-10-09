#include <iostream>
#include <vector>
#include <iomanip>

const int MAX_NUMBER_OF_USERS = 100000;
const int MAX_NUMBER_OF_PAGES = 1000;



class EbookAccounter {
    public:
    EbookAccounter() : users_(std::vector<int>(MAX_NUMBER_OF_USERS)), number_of_users_(std::vector<int>(MAX_NUMBER_OF_PAGES))
    {
    };
    
    void Read(int user_id, int page){
        if (users_[user_id] == 0){
            ++total_number_users_;
        }
        for (int i = users_[user_id] + 1; i <= page; ++i){
            ++number_of_users_[i];
        }
        users_[user_id] = page;   
    }
    
    void Cheer(int user_id, std::ostream& out){
        if (users_[user_id] == 0){
            out << 0 << std::endl;
        }
        else if (users_[user_id] != 0 && total_number_users_ == 1) {
            out << 1 << std::endl;
        }
        else {
            double number_of_lowers = total_number_users_ - number_of_users_[users_[user_id]];
            double result = number_of_lowers / (total_number_users_ - 1);
            out << std::setprecision(6) << result << std::endl;
        }
    }
    
    private:
    std::vector<int> users_;
    std::vector<int> number_of_users_; //Number of users that read at least N pages
    int total_number_users_ = 0;
};



int main(){
    int counter;
    EbookAccounter accounter;
    std::cin >> counter;
    while (counter != 0){
        std::string request_type;
        std::cin >> request_type;
        if (request_type == "READ"){
            int user = 0;
            int page = 0;
            std::cin >> user >> page;
            accounter.Read(user, page);
        }
        if (request_type == "CHEER"){
            int user = 0;
            std::cin >> user;
            accounter.Cheer(user, std::cout);
        }
        --counter;
    }
    return 0;
}