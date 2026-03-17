#include <iostream>
#include <cstring>
#include <vector>

class Team;

class Player {
    static int no_players;
    const int id;
    char* name;
    int goal_number;
    int matches_played;
    double* ratings;
    Team* team;
public:
    Player();
    Player(char *, int);
    Player(char *, int, int);
    Player(char*, int, int, double*);
    Player(char*, int, int, double*, Team*);
    Player(const Player &obj);
    ~Player();
    Player& operator=(const Player &obj);
    friend std::ostream& operator<<(std::ostream&, const Player&);
    friend std::istream& operator>>(std::istream&, Player&);
    void setName(const char*);
    const char* getName () const;
    void setTeam(Team* new_team);
    Team* getTeam() const;
};
int Player::no_players = 0;

Player::Player():id(no_players++) {
    name=strcpy(new char[4], "N/A");
    goal_number=0;
    matches_played=0;
    ratings=nullptr;
    team=nullptr;

}
Player::Player(char *name, int goal_number): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->goal_number=goal_number;
    matches_played=0;
    ratings=nullptr;
    team=nullptr;
}

Player::Player(char *name, int goal_number, int matches_played): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->goal_number=goal_number;
    this->matches_played=matches_played;
    ratings=nullptr;
    team=nullptr;
}
Player::Player(char *name, int goal_number, int matches_played, double *ratings): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->goal_number=goal_number;
    this->matches_played=matches_played;
    if (matches_played>0){
        this->ratings=new double[matches_played];
        for(int i=0;i<matches_played;i++){
            this->ratings[i]=ratings[i];
        }
    }
    else this->ratings=nullptr;
    team=nullptr;
}
Player::Player(char *name, int goal_number, int matches_played, double *ratings, Team *team): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->goal_number=goal_number;
    this->matches_played=matches_played;
    if (matches_played>0){
        this->ratings=new double[matches_played];
        for(int i=0;i<matches_played;i++){
            this->ratings[i]=ratings[i];
        }
    }
    else this->ratings=nullptr;
    this->team=team;
}

Player::Player(const Player &obj): id(no_players++)
{
    this->name=strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->goal_number=obj.goal_number;
    this->matches_played=obj.matches_played;
    if (obj.matches_played>0){
        this->ratings= new double[obj.matches_played];
        for(int i=0;i<obj.matches_played;i++){
            this->ratings[i]=obj.ratings[i];
        }
    }
    else
    {
        this->ratings=nullptr;
    }
    this->team=obj.team;
}

Player::~Player() {
    delete[] name;
    delete[] ratings;
}

Player &Player::operator=(const Player &obj) {
    if (this == &obj)
        return *this;
    delete[] name;
    delete[] ratings;
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->goal_number=obj.goal_number;
    this->matches_played=obj.matches_played;
    if (obj.matches_played>0){
        this->ratings= new double[obj.matches_played];
        for(int i=0;i<obj.matches_played;i++){
            this->ratings[i]=obj.ratings[i];
        }
    }
    else
    {
        this->ratings=nullptr;
    }
    this->team=obj.team;
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Player &obj)
{
    os<<"Id: "<<obj.id<<"\n";
    if (obj.name)
        os<<"Name: "<<obj.name<<"\n";
    os<<"Goal number: "<<obj.goal_number<<"\n";
    os<<"Matches Played: "<<obj.matches_played<<"\n";
    if (obj.ratings)
    {
        os<<"Ratings: \n" ;
        for (int i=0;i<obj.matches_played;i++)
            os<<"Match "<<i<<": "<<obj.ratings[i]<<"\n";
    }
    if (obj.team != nullptr)
        os << "Team: " << obj.team->getName() << "\n";
    else
        os << "Team: N/A\n";
    return os;
}

std::istream& operator>>(std::istream& is, Player &obj) {
    char name[256];
    int goal_number;
    int matches;
    int match_rating;
    std::cout<<"Name: ";
    is>>name;
    obj.setName(name);
    std::cout<<"\n";
    std::cout<<"Goal number: ";
    is>>goal_number;
    obj.goal_number=goal_number;
    std::cout<<"\n";
    std::cout<<"Matches Played: ";
    is>>matches;
    obj.matches_played=matches;
    std::cout<<"\n";
    std::cout<<"Ratings: \n";
    delete[] obj.ratings;
    obj.ratings = new double[obj.matches_played];
    for (int i=0; i<obj.matches_played; i++) {
        std::cout<<"Match "<<i<<": ";
        is>>match_rating;
        obj.ratings[i]=match_rating;
    }
    return is;

}

void Player::setName(const char *new_name) {
    if (new_name == nullptr) return;

    if (this->name != nullptr) {
        delete[] this->name;
    }

    this->name = new char[strlen(new_name) + 1];
    strcpy(this->name, new_name);
}

const char *Player::getName() const {
    return this->name;
}

void Player::setTeam(Team* new_team) {
    team=new_team;
}

Team* Player::getTeam() const {
    return team;
}

class Team {
private:
    char* name;
    std::vector<Player *> players;
    Coach *headCoach;
    long budget;
public:
    Team();
    Team(char*);
    Team(char*, std::vector<Player*>);
    Team(char*, std::vector<Player*>, Coach*);
    Team(char*, std::vector<Player*>, Coach*, long);
    Team(const Team &obj);
    ~Team();
    Team& operator=(const Team &obj);
    friend std::ostream& operator<<(std::ostream&, const Team&);
    friend std::istream& operator>>(std::istream&, Team&);
    void setName(const char*);
    const char* getName () const;
};

Team::Team() {
    name=strcpy(new char[4], "N/A");
    headCoach=nullptr;
    budget=0;
}

Team::Team(char *name) {
    this->name=strcpy(new char[strlen(name)+1], name);
    headCoach=nullptr;
    budget=0;
}

Team::Team(char *name, std::vector<Player *>players) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    headCoach=nullptr;
    budget=0;
}
Team::Team(char*name, std::vector<Player*>players, Coach* headCoach) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    this->headCoach=headCoach;
    budget=0;
}

Team::Team(char*name, std::vector<Player*>players, Coach* headCoach, long budget) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    this->headCoach=headCoach;
    this->budget=budget;
}

Team::Team(const Team &obj) {
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->players=obj.players;
    this->headCoach=obj.headCoach;
    this->budget=obj.budget;
}

Team::~Team() {
    delete[] name;
}

Team &Team::operator=(const Team &obj) {
    if (this==&obj) return *this;
    delete[] name;
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->players=obj.players;
    this->headCoach=obj.headCoach;
    this->budget=obj.budget;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Team& obj) {
    os<<"Name: "<<obj.name<<"\n";
    os << "Players: \n";
    for (int i = 0; i < obj.players.size(); i++)
        os << *obj.players[i] << "\n";

    if (obj.headCoach != nullptr)
        os << "Head Coach: " << obj.headCoach->getName() << "\n";
    else
        os << "Head Coach: N/A\n";
    os<<"Budget: "<<obj.budget;
    return os;
}

std::istream& operator>>(std::istream &is, Team &obj) {
    char name[256];
    long buget;
    std::cout<<"Name:";
    is>>name;
    obj.setName(name);

    std::cout<<"Budget :";
    is>>buget;
    obj.budget=buget;
    return is;
}

void Team::setName(const char* name) {
    delete[] this->name;
    this->name=strcpy(new char[strlen(name)+1], name);
}

const char* Team::getName() const{
    return this->name;
}





