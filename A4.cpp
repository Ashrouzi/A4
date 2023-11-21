#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

vector<string> split(string s, char seperator) {
    int lastCut = 0;
    s.push_back(seperator);

    vector<string> res;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == seperator) {
            res.push_back(s.substr(lastCut, i - lastCut));
            lastCut = i + 1;
        }

    return res;
}

class User
{
    private:

        int user_id;
        int wallet;

    public: 

        const int getId(){
            return user_id;
        }

        const int getWallet(){
            return wallet;
        }

        bool bardasht(int val){
            if(val > wallet)
                return false;
            wallet -= val;
            return true;
        }

        User(string data){
            vector<string> seperatedData = split(data, ',');
            user_id = stoi(seperatedData[0]);
            wallet = stoi(seperatedData[1]);
        }

        User() {
            user_id = -1;
            wallet = -1;
        }

};

class Short_term
{
    private:

        int user_id;
        int money;
        int startMonth;
        int index;

    public:
    Short_term (int userId, int m, int start, int i){
        user_id = userId;
        money = m;
        startMonth = start;
        index = i;
    }
};

User& getUser(int user_id, vector<User>& users) {
    for(User& u : users) {
        if(u.getId() == user_id)
            return u;
    }

    return users[0];
}

// fix bank ID
class Bank
{
private:

    int bank_id;
    int short_term_profit_margin;
    int short_term_min_inv;
    vector<Short_term> shortTerm;

public:
    Bank() {
        bank_id = -1;
    }

    Bank(string data){
        vector<string> seperatedData = split(data, ',');
        bank_id = stoi(seperatedData[0]);
        short_term_profit_margin = stoi(seperatedData[1]);
        short_term_min_inv = stoi(seperatedData[2]);
    }

    void print(){
        cout << bank_id << " " << short_term_profit_margin << " " << short_term_min_inv << '\n';
    }

    void newShortTerm(User& u, int init_investment, int passedMonths) {
        if((u.getWallet() >= init_investment) && (init_investment > short_term_min_inv)){
            cout << shortTerm.size() << endl;
            shortTerm.push_back(Short_term(u.getId(), init_investment, passedMonths, shortTerm.size()));
            u.bardasht(init_investment);
        }
        else
            cout << "Not enough money";
    }
    
};

class Long_term
{
    private:

        int user_id;
        int year;
        int short_term_id;
        int money;
        int startMonth;

    public:

};

void readBankFile(string fileName, vector<Bank>& banks){
    string line;

    bool flagBank = false;
	fstream file (fileName, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
            if (flagBank == false)
                flagBank = true;
            else
			    banks.push_back(Bank(line));
		}
	}
}

void readUserFile(string fileName, vector<User>& users){
    string line;

    bool flaguser = false;
	fstream file (fileName, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
            if (flaguser == false)
                flaguser = true;
            else
			    users.push_back(User(line));
		}
	}
}

int main(int argc, char* argv[])
{
    int passedMonths = 0;
    vector<Bank> banks;
    vector<User> users;
    users.push_back(User());
    banks.push_back(Bank());

    readBankFile(argv[2], banks);
    readUserFile(argv[4], users);
    // banks[0].print();
    string command;
    while (cin >> command){
        if(command == "create_short_term_deposit"){
            int userId;
            int bankId;
            int init_investemnt;

            cin >> userId >> bankId >> init_investemnt;
            banks[bankId].newShortTerm(getUser(userId, users) , init_investemnt, passedMonths);
        }

        else if (command == "create_long_term_deposit"){
            int userId;
            int bankId;
            int short_term_deposit_id;
            int years;
            int init_investment;

            cin >> userId >> bankId >> short_term_deposit_id >> years >> init_investment;
        }

        else if(command == "create_gharzolhasane_deposit"){
            int userId;
            int bankId;
            int init_investemnt;

            cin >> userId >> bankId >> init_investemnt;
        }

        else if(command == "pass_time"){
            int month;

            cin >> month;
            passedMonths += month;
        }

        else if(command == "inventory_report"){
            int userId;
            int bankId;
            int short_term_deposit_id;

            cin >> userId >> bankId >> short_term_deposit_id;
        }

        else if(command == "calc_money_in_bank"){
            int userId;
            int bankId;

            cin >> userId >> bankId;
        }

        else if(command == "calc_all_money"){
            int userId;

            cin >> userId;
        }

        else {
            cout << "unknown command";
        }
    }

    return 0;
}
