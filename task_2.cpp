#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <cassert>

using namespace std;

class Domain {

    public:

    Domain(const std::string& str) : domain_name_(std::string(str.rbegin(), str.rend()))
    {
    }
    
    bool operator==(const Domain& other) const {
        return this->domain_name_ == other.domain_name_;
    }

    bool operator<(const Domain& other) const {
        return std::lexicographical_compare(domain_name_.begin(), domain_name_.end(), other.domain_name_.begin(), other.domain_name_.end());
    }

    bool IsSubdomain(const Domain& other) const {
        size_t position = this->domain_name_.find(other.domain_name_, 0);
        return position == 0 && (this->domain_name_[other.domain_name_.size()] == '.' || other == *this);
    }

    private:

    std::string domain_name_;
};

class DomainChecker {
public:
    
    template <typename InputIt>
    DomainChecker(InputIt first, InputIt last) {
      forbidden_domains_ = std::vector<Domain>(first, last);
      std::sort(forbidden_domains_.begin(), forbidden_domains_.end(), [](const Domain& left, const Domain& right){ return left < right; });
      auto it = unique(forbidden_domains_.begin(), forbidden_domains_.end(), [](const Domain& left, const Domain& right){return left.IsSubdomain(right) || right.IsSubdomain(left);});
      forbidden_domains_.erase(it, forbidden_domains_.end());
    }


    bool IsForbidden(const Domain& domain){
        auto it = std::upper_bound(forbidden_domains_.begin(), forbidden_domains_.end(), domain);
        if (it == forbidden_domains_.begin()){
            return false;
        }
        return domain.IsSubdomain(*std::prev(it));
    }

    private:

    std::vector<Domain> forbidden_domains_;
};

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

std::vector<Domain> ReadDomains(istream& input, size_t number){
    std::vector<Domain> vector_domains;
    if (number == 0){
        return vector_domains;
    }
    while (number != 0){
        string str;
        input >> str;
        vector_domains.push_back({str});
        --number;
    }
    ReadNumberOnLine<size_t>(input);
    
    return vector_domains;
}

int main() {

    {
        Domain first("ab.cde.ru");
        Domain second("cde.ru");
        Domain third("abc.ru");
        assert(first.IsSubdomain(second) == true);
        assert(first.IsSubdomain(third) == false);
        assert(first.IsSubdomain(first) == true);
    }

    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));

    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());
    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}