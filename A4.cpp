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

class Long_term
{
    private:

        int user_id;
        int year;
        int short_term_id;
        int money;
        int startMonth;

    public:

    double calculateMoney(int monthNow, double margin) {
        margin /= 100;
        // margin /= 12;
        return margin * (monthNow - startMonth) * money + money;
    }

    int getUserID() {
        return user_id;
    }
};

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

    int getUserID() {
        return user_id;
    }

    double calculateMoney(int monthNow, double margin) {
        margin /= 100;
        return margin * (monthNow - startMonth) * money + money;
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
    int long_term_profit_margin;
    vector<Short_term> shortTerm;
    vector<Long_term> longTerm;

public:
    double getUserMoney(int userID, int monthNow) {
        for (Short_term s : shortTerm) {
            if (s.getUserID() == userID)
                return s.calculateMoney(monthNow, short_term_profit_margin);
        }

        return 0;
    }

    double getUserLongTermMoney(int userID, int monthNow) {
        for (Long_term s : longTerm) {
            if (s.getUserID() == userID)
                return s.calculateMoney(monthNow, long_term_profit_margin);
        }

        return 0;
    }

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
            double sum = banks[bankId].getUserMoney(userId, passedMonths);
            sum += banks[bankId].getUserLongTermMoney(userId, passedMonths);

            cout << setprecision(2) << fixed << sum << endl;
        }

        else if(command == "calc_money_in_bank"){
            int userId;
            int bankId;

            cin >> userId >> bankId;
            cout << setprecision(2) << fixed << banks[bankId].getUserMoney(userId, passedMonths) << endl;
        }

        else if(command == "calc_all_money"){
            int userId;

            cin >> userId;

            double sum = 0;
            for (Bank b : banks) {
                sum += b.getUserMoney(userId, passedMonths);
            }

            cout << setprecision(2) << fixed << sum << endl;
        }

        else {
            cout << "unknown command";
        }
    }

    return 0;
}
