struct DB_parameters {

    DB_parameters& SetDBName(string_view name){
        this->db_name = name;
        return *this;
    }

    DB_parameters& SetTimeOut(int time_out){
        this->time_out = time_out;
        return *this;
    }
    DB_parameters& SetEsceptions(bool allow_exceptions){
        this->allow_exceptions = allow_exceptions;
        return *this;
    }

    DB_parameters& SetDBName(const DBLogLevel& log_level){
        this->log_level = log_level;
        return *this;
    }

    string_view db_name;
    int time_out = 0;
    bool allow_exceptions;
    DBLogLevel log_level;

};

struct Person_parameters {

    Person_parameters& SetMinAge(int age){
        this->min_age = age;
        return *this;
    }

    Person_parameters& SetMaxAge(int age){
        this->max_age = age;
        return *this;
    }

    Person_parameters& SetNameFilter(int name_filter){
        this->name_filter = name_filter;
        return *this;
    }

    int min_age = 0;
    int max_age = 0;
    string_view name_filter;

};

DBHandler BuildDBHandler (const DB_parameters& db_parameters){
    DBConnector connector(db_parameters.allow_exceptions, db_parameters.log_level);
     if (db_parameters.db_name.starts_with("tmp."s)) {
        return connector.ConnectTmp(db_parameters.db_name, db_parameters.time_out);
    } else {
        return connector.Connect(db_parameters.db_name, db_parameters.time_out);
    }

}

vector<Person> LoadPersons(const DB_parameters& db_parameters, const Person_parameters person_parameters) {

    DBHandler db = BuildDBHandler(db_parameters);

    if (!db_parameters.allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << person_parameters.min_age << " and "s << person_parameters.max_age << " "s
              << "and Name like '%"s << db.Quote(person_parameters.name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}