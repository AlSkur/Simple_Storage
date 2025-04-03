#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h> 

using namespace std;

class User {
public:
    string name;
    string login;
    string pass;
};

class Message {
public:
    string text;
    string sender;
    string receiver;
};

void setSecurePermissions(const string& filename) {
    chmod(filename.c_str(), 0600); 
}


void saveUsers(const vector<User>& users, const string& filename) {
    ofstream file(filename);
    setSecurePermissions(filename);

    for (const auto& user : users) {
        file << user.name << endl << user.login << endl << user.pass << endl;
    }
}


vector<User> loadUsers(const string& filename) {
    vector<User> users;
    ifstream file(filename);

    User user;
    while (getline(file, user.name) &&
        getline(file, user.login) &&
        getline(file, user.pass)) {
        users.push_back(user);
    }

    return users;
}


void saveMessages(const vector<Message>& messages, const string& filename) {
    ofstream file(filename);
    setSecurePermissions(filename);

    for (const auto& msg : messages) {
        file << msg.text << endl << msg.sender << endl << msg.receiver << endl;
    }
}

vector<Message> loadMessages(const string& filename) {
    vector<Message> messages;
    ifstream file(filename);

    Message msg;
    while (getline(file, msg.text) &&
        getline(file, msg.sender) &&
        getline(file, msg.receiver)) {
        messages.push_back(msg);
    }

    return messages;
}

int main() {
    const string userFile = "users.dat";
    const string msgFile = "messages.dat";

    
    vector<User> users = loadUsers(userFile);
    vector<Message> messages = loadMessages(msgFile);

    
    if (users.empty()) {
        users.push_back({ "Admin", "admin", "secret" });
        users.push_back({ "User", "user", "12345" });
    }

    if (messages.empty()) {
        messages.push_back({ "Hello!", "admin", "user" });
        messages.push_back({ "Hi!", "user", "admin" });
    }

    
    saveUsers(users, userFile);
    saveMessages(messages, msgFile);

    
    cout << "Users (" << users.size() << "):" << endl;
    for (const auto& user : users) {
        cout << "- " << user.name << " (" << user.login << ")" << endl;
    }

    cout << "Messages (" << messages.size() << "):" << endl;
    for (const auto& msg : messages) {
        cout << "From: " << msg.sender << " To: " << msg.receiver
            << "Text: " << msg.text << endl;
    }

    return 0;
}